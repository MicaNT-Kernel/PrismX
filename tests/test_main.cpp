// ============================================================================
// PrismX: Standalone Unit & Integration Test Suite
// 
// Validates DXGI, Direct3D 11, Direct3D 12, ShaderVM, and Vulkan 1.3 Pipelines
// Pure ISO C++23. Zero External Dependencies.
// ============================================================================

#include "prismx.hpp"
#include <iostream>
#include <cassert>
#include <vector>
#include <string>
#include <cmath>

#define PRISMX_TEST(name) \
    std::cout << " [RUN]  " << name << " ... "; \
    try {

#define PRISMX_PASS() \
        std::cout << "[PASS]\n"; \
    } catch (const std::exception& e) { \
        std::cout << "[FAIL] (" << e.what() << ")\n"; \
        return 1; \
    } catch (...) { \
        std::cout << "[FAIL] (Unknown exception)\n"; \
        return 1; \
    }

#define PRISMX_ASSERT(cond) \
    if (!(cond)) { \
        throw std::runtime_error("Assertion failed: " #cond); \
    }

using namespace prismx;

int Test_DXGI_Infrastructure() {
    PRISMX_TEST("Test_DXGI_Infrastructure")
        ComPtr<IDXGIFactory1> factory;
        HRESULT hr = CreateDXGIFactory1(IID_IDXGIFactory1, factory.PutVoid());
        PRISMX_ASSERT(SUCCEEDED(hr));
        PRISMX_ASSERT(factory.Get() != nullptr);

        // Enumerate Adapters
        ComPtr<IDXGIAdapter1> adapter;
        hr = factory->EnumAdapters1(0, adapter.ReleaseAndGetAddressOf());
        PRISMX_ASSERT(SUCCEEDED(hr));

        DXGI_ADAPTER_DESC1 desc{};
        hr = adapter->GetDesc1(&desc);
        PRISMX_ASSERT(SUCCEEDED(hr));
        PRISMX_ASSERT(desc.DedicatedVideoMemory > 0);

        // Enumerate Output Monitor
        ComPtr<IDXGIOutput> output;
        hr = adapter->EnumOutputs(0, output.ReleaseAndGetAddressOf());
        PRISMX_ASSERT(SUCCEEDED(hr));

        uint32_t numModes = 0;
        hr = output->GetDisplayModeList(DXGI_FORMAT_B8G8R8A8_UNORM, 0, &numModes, nullptr);
        PRISMX_ASSERT(SUCCEEDED(hr));
        PRISMX_ASSERT(numModes >= 3);

        // Create SwapChain
        DXGI_SWAP_CHAIN_DESC scDesc{};
        scDesc.BufferDesc.Width = 800;
        scDesc.BufferDesc.Height = 600;
        scDesc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
        scDesc.BufferCount = 2;
        scDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;

        ComPtr<IDXGISwapChain> swapChain;
        hr = factory->CreateSwapChain(nullptr, &scDesc, swapChain.ReleaseAndGetAddressOf());
        PRISMX_ASSERT(SUCCEEDED(hr));

        // Present Frame
        hr = swapChain->Present(1, 0);
        PRISMX_ASSERT(SUCCEEDED(hr));

        uint32_t presentCount = 0;
        hr = swapChain->GetLastPresentCount(&presentCount);
        PRISMX_ASSERT(SUCCEEDED(hr));
        PRISMX_ASSERT(presentCount == 1);
    PRISMX_PASS()
    return 0;
}

int Test_Direct3D11_SoftwareRasterizer() {
    PRISMX_TEST("Test_Direct3D11_SoftwareRasterizer")
        DXGI_SWAP_CHAIN_DESC scDesc{};
        scDesc.BufferDesc.Width = 64;
        scDesc.BufferDesc.Height = 64;
        scDesc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
        scDesc.BufferCount = 1;

        ComPtr<ID3D11Device> device;
        ComPtr<ID3D11DeviceContext> context;
        ComPtr<IDXGISwapChain> swapChain;

        HRESULT hr = D3D11CreateDeviceAndSwapChain(
            nullptr,
            D3D_DRIVER_TYPE_HARDWARE,
            nullptr,
            0,
            nullptr,
            0,
            7, // D3D11_SDK_VERSION
            &scDesc,
            swapChain.ReleaseAndGetAddressOf(),
            device.ReleaseAndGetAddressOf(),
            nullptr,
            context.ReleaseAndGetAddressOf()
        );
        PRISMX_ASSERT(SUCCEEDED(hr));
        PRISMX_ASSERT(device.Get() && context.Get() && swapChain.Get());

        // Get Backbuffer and Create RTV
        ComPtr<ID3D11Texture2D> backBuffer;
        hr = swapChain->GetBuffer(0, IID_IDXGISurface, backBuffer.PutVoid());
        PRISMX_ASSERT(SUCCEEDED(hr));

        ComPtr<ID3D11RenderTargetView> rtv;
        hr = device->CreateRenderTargetView(backBuffer.Get(), nullptr, rtv.ReleaseAndGetAddressOf());
        PRISMX_ASSERT(SUCCEEDED(hr));

        // Clear RTV
        float clearColor[4] = { 0.1f, 0.2f, 0.3f, 1.0f };
        context->ClearRenderTargetView(rtv.Get(), clearColor);

        // Viewport
        D3D11_VIEWPORT vp{};
        vp.Width = 64.0f;
        vp.Height = 64.0f;
        vp.MinDepth = 0.0f;
        vp.MaxDepth = 1.0f;
        context->RSSetViewports(1, &vp);

        // Render triangle
        struct SimpleVertex {
            float x, y, z;
            float r, g, b, a;
        };

        SimpleVertex vertices[] = {
            {  0.0f,  0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f },
            {  0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f },
            { -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f }
        };

        D3D11_BUFFER_DESC vbDesc{};
        vbDesc.ByteWidth = sizeof(vertices);
        vbDesc.Usage = D3D11_USAGE_DEFAULT;
        vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

        D3D11_SUBRESOURCE_DATA vbInit{};
        vbInit.pSysMem = vertices;

        ComPtr<ID3D11Buffer> vertexBuffer;
        hr = device->CreateBuffer(&vbDesc, &vbInit, vertexBuffer.ReleaseAndGetAddressOf());
        PRISMX_ASSERT(SUCCEEDED(hr));

        uint32_t stride = sizeof(SimpleVertex);
        uint32_t offset = 0;
        ID3D11Buffer* vbs[] = { vertexBuffer.Get() };
        context->IASetVertexBuffers(0, 1, vbs, &stride, &offset);
        context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

        ID3D11RenderTargetView* rtvs[] = { rtv.Get() };
        context->OMSetRenderTargets(1, rtvs, nullptr);

        context->Draw(3, 0);

        hr = swapChain->Present(0, 0);
        PRISMX_ASSERT(SUCCEEDED(hr));
    PRISMX_PASS()
    return 0;
}

int Test_Direct3D12_LowLevelPipeline() {
    PRISMX_TEST("Test_Direct3D12_LowLevelPipeline")
        ComPtr<ID3D12Device> device;
        HRESULT hr = D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_12_0, IID_ID3D12Device, device.PutVoid());
        PRISMX_ASSERT(SUCCEEDED(hr));
        PRISMX_ASSERT(device.Get() != nullptr);

        // Command Queue
        D3D12_COMMAND_QUEUE_DESC qDesc{};
        qDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
        ComPtr<ID3D12CommandQueue> commandQueue;
        hr = device->CreateCommandQueue(&qDesc, IID_ID3D12CommandQueue, commandQueue.PutVoid());
        PRISMX_ASSERT(SUCCEEDED(hr));

        // Command Allocator
        ComPtr<ID3D12CommandAllocator> commandAlloc;
        hr = device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_ID3D12CommandAllocator, commandAlloc.PutVoid());
        PRISMX_ASSERT(SUCCEEDED(hr));

        // Command List
        ComPtr<ID3D12GraphicsCommandList> commandList;
        hr = device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, commandAlloc.Get(), nullptr, IID_ID3D12GraphicsCommandList, commandList.PutVoid());
        PRISMX_ASSERT(SUCCEEDED(hr));

        // Fence
        ComPtr<ID3D12Fence> fence;
        hr = device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_ID3D12Fence, fence.PutVoid());
        PRISMX_ASSERT(SUCCEEDED(hr));
        PRISMX_ASSERT(fence->GetCompletedValue() == 0);

        // Descriptor Heap (RTV)
        D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc{};
        rtvHeapDesc.NumDescriptors = 2;
        rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
        ComPtr<ID3D12DescriptorHeap> rtvHeap;
        hr = device->CreateDescriptorHeap(&rtvHeapDesc, IID_ID3D12DescriptorHeap, rtvHeap.PutVoid());
        PRISMX_ASSERT(SUCCEEDED(hr));

        // Committed Resource (Back Buffer)
        D3D12_HEAP_PROPERTIES heapProps{};
        heapProps.Type = D3D12_HEAP_TYPE_DEFAULT;

        D3D12_RESOURCE_DESC resDesc{};
        resDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
        resDesc.Width = 64;
        resDesc.Height = 64;
        resDesc.DepthOrArraySize = 1;
        resDesc.MipLevels = 1;
        resDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
        resDesc.SampleDesc = { 1, 0 };
        resDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET;

        ComPtr<ID3D12Resource> renderTarget;
        hr = device->CreateCommittedResource(
            &heapProps,
            D3D12_HEAP_FLAG_NONE,
            &resDesc,
            D3D12_RESOURCE_STATE_PRESENT,
            nullptr,
            IID_ID3D12Resource,
            renderTarget.PutVoid()
        );
        PRISMX_ASSERT(SUCCEEDED(hr));

        // Record Barrier Transition & Clear
        D3D12_RESOURCE_BARRIER barrier{};
        barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
        barrier.Transition.pResource = renderTarget.Get();
        barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
        barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
        commandList->ResourceBarrier(1, &barrier);

        float clearColor[4] = { 0.0f, 0.4f, 0.8f, 1.0f };
        D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle{ 0x1000 };
        commandList->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);

        barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
        barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
        commandList->ResourceBarrier(1, &barrier);

        hr = commandList->Close();
        PRISMX_ASSERT(SUCCEEDED(hr));

        // Execute Command List
        ID3D12CommandList* const ppCmdLists[] = { commandList.Get() };
        commandQueue->ExecuteCommandLists(1, ppCmdLists);

        // Synchronize via Fence
        hr = commandQueue->Signal(fence.Get(), 100);
        PRISMX_ASSERT(SUCCEEDED(hr));
        PRISMX_ASSERT(fence->GetCompletedValue() == 100);
    PRISMX_PASS()
    return 0;
}

int Test_PrismShaderVM_SIMD() {
    PRISMX_TEST("Test_PrismShaderVM_SIMD")
        // 1. Build and validate MVP Transform Vertex Shader
        auto vsProg = PrismShaderVM::BuildMVPTransformVS();
        PRISMX_ASSERT(vsProg.InstructionCount() >= 5);

        VectorRegister inPos(2.0f, 3.0f, 4.0f, 1.0f);
        VectorRegister inCol(0.9f, 0.7f, 0.5f, 1.0f);
        VectorRegister inUV(0.25f, 0.75f, 0.0f, 0.0f);
        VectorRegister inNorm(0.0f, 1.0f, 0.0f, 0.0f);

        std::array<VectorRegister, 16> consts{};
        consts[0] = VectorRegister(2.0f, 0.0f, 0.0f, 0.0f);
        consts[1] = VectorRegister(0.0f, 3.0f, 0.0f, 0.0f);
        consts[2] = VectorRegister(0.0f, 0.0f, 4.0f, 0.0f);
        consts[3] = VectorRegister(0.0f, 0.0f, 0.0f, 1.0f);

        VectorRegister outPos, outCol;
        PrismShaderVM::ExecuteVertexShader(vsProg, inPos, inCol, inUV, inNorm, consts, outPos, outCol);

        PRISMX_ASSERT(outPos.x() == 4.0f);
        PRISMX_ASSERT(outPos.y() == 9.0f);
        PRISMX_ASSERT(outPos.z() == 16.0f);
        PRISMX_ASSERT(outPos.w() == 1.0f);
        PRISMX_ASSERT(outCol.x() == 0.9f && outCol.y() == 0.7f);

        // 2. Build and validate Texture Modulation Pixel Shader
        auto psProg = PrismShaderVM::BuildTexturedModulatePS();
        auto samplerFn = [](uint8_t, float u, float v) -> VectorRegister {
            return VectorRegister(u, v, 0.5f, 1.0f);
        };

        VectorRegister psOutCol;
        PrismShaderVM::ExecutePixelShader(psProg, outPos, inCol, inUV, inNorm, consts, samplerFn, psOutCol);
        PRISMX_ASSERT(std::abs(psOutCol.x() - (0.9f * 0.25f)) < 1e-4f);
        PRISMX_ASSERT(std::abs(psOutCol.y() - (0.7f * 0.75f)) < 1e-4f);

        // 3. Directional Lighting Pixel Shader
        auto lightProg = PrismShaderVM::BuildDirectionalLightingPS();
        consts[0] = VectorRegister(0.0f, 1.0f, 0.0f, 0.0f); // Light Dir: +Y
        consts[1] = VectorRegister(0.1f, 0.1f, 0.1f, 1.0f); // Ambient: 0.1
        consts[2] = VectorRegister(0.8f, 0.8f, 0.8f, 1.0f); // Diffuse: 0.8
        consts[4] = VectorRegister(0.0f, 0.0f, 0.0f, 0.0f); // Zero vector

        VectorRegister litCol;
        PrismShaderVM::ExecutePixelShader(lightProg, outPos, VectorRegister(1.0f, 1.0f, 1.0f, 1.0f), inUV, inNorm, consts, nullptr, litCol);
        PRISMX_ASSERT(std::abs(litCol.x() - 0.9f) < 1e-4f);
    PRISMX_PASS()
    return 0;
}

int Test_Vulkan13_ICD_Driver() {
    PRISMX_TEST("Test_Vulkan13_ICD_Driver")
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "PrismX Standalone Test";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "PrismX";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 3, 0);
        appInfo.apiVersion = VK_API_VERSION_1_3;

        VkInstanceCreateInfo instInfo{};
        instInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        instInfo.pApplicationInfo = &appInfo;

        VkInstance instance = VK_NULL_HANDLE;
        VkResult res = vkCreateInstance(&instInfo, nullptr, &instance);
        PRISMX_ASSERT(res == VK_SUCCESS);
        PRISMX_ASSERT(instance != VK_NULL_HANDLE);

        // Physical Devices
        uint32_t deviceCount = 0;
        res = vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
        PRISMX_ASSERT(res == VK_SUCCESS);
        PRISMX_ASSERT(deviceCount > 0);

        std::vector<VkPhysicalDevice> devices(deviceCount);
        res = vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());
        PRISMX_ASSERT(res == VK_SUCCESS);

        VkPhysicalDeviceProperties props{};
        vkGetPhysicalDeviceProperties(devices[0], &props);
        PRISMX_ASSERT(props.apiVersion == VK_API_VERSION_1_3);

        // Create Logical Device
        float queuePriority = 1.0f;
        VkDeviceQueueCreateInfo queueInfo{};
        queueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueInfo.queueCount = 1;
        queueInfo.pQueuePriorities = &queuePriority;

        VkDeviceCreateInfo devInfo{};
        devInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        devInfo.queueCreateInfoCount = 1;
        devInfo.pQueueCreateInfos = &queueInfo;

        VkDevice device = VK_NULL_HANDLE;
        res = vkCreateDevice(devices[0], &devInfo, nullptr, &device);
        PRISMX_ASSERT(res == VK_SUCCESS);
        PRISMX_ASSERT(device != VK_NULL_HANDLE);

        VkQueue queue = VK_NULL_HANDLE;
        vkGetDeviceQueue(device, 0, 0, &queue);
        PRISMX_ASSERT(queue != VK_NULL_HANDLE);

        vkDestroyDevice(device, nullptr);
        vkDestroyInstance(instance, nullptr);
    PRISMX_PASS()
    return 0;
}

int Test_DirectX_Audio_And_Input() {
    PRISMX_TEST("Test_DirectX_Audio_And_Input")
        using namespace prismx::audio;
        using namespace prismx::hid;

        // 1. Audio Engine and Mastering Voice
        ComPtr<IXAudio2> audioEngine;
        int32_t hr = XAudio2Create(audioEngine.ReleaseAndGetAddressOf(), 0, 0);
        PRISMX_ASSERT(hr == 0);
        PRISMX_ASSERT(audioEngine.Get() != nullptr);

        IXAudio2MasteringVoice* masteringVoice = nullptr;
        hr = audioEngine->CreateMasteringVoice(&masteringVoice, 2, 48000, 0);
        PRISMX_ASSERT(hr == 0 && masteringVoice != nullptr);

        uint32_t channelMask = 0;
        masteringVoice->GetChannelMask(&channelMask);
        PRISMX_ASSERT(channelMask == 0x3);

        // 2. Source Voice & Procedural Synthesis
        WAVEFORMATEX fmt{};
        fmt.wFormatTag = WAVE_FORMAT_PCM;
        fmt.nChannels = 2;
        fmt.nSamplesPerSec = 48000;
        fmt.wBitsPerSample = 16;
        fmt.nBlockAlign = 4;
        fmt.nAvgBytesPerSec = 48000 * 4;

        IXAudio2SourceVoice* sourceVoice = nullptr;
        hr = audioEngine->CreateSourceVoice(&sourceVoice, &fmt);
        PRISMX_ASSERT(hr == 0 && sourceVoice != nullptr);

        std::vector<uint8_t> monoTone = PrismAudioEngineImpl::SynthesizeTone(
            PrismAudioEngineImpl::ToneType::Sine, 440.0f, 0.05f, 48000, 0.8f
        );
        PRISMX_ASSERT(!monoTone.empty());

        size_t samples = monoTone.size() / sizeof(int16_t);
        std::vector<int16_t> stereoTone(samples * 2);
        const int16_t* pMono = reinterpret_cast<const int16_t*>(monoTone.data());
        for (size_t i = 0; i < samples; ++i) {
            stereoTone[i * 2 + 0] = pMono[i];
            stereoTone[i * 2 + 1] = pMono[i];
        }

        XAUDIO2_BUFFER buf{};
        buf.AudioBytes = static_cast<uint32_t>(stereoTone.size() * sizeof(int16_t));
        buf.pAudioData = reinterpret_cast<const uint8_t*>(stereoTone.data());

        hr = sourceVoice->SubmitSourceBuffer(&buf);
        PRISMX_ASSERT(hr == 0);
        hr = sourceVoice->Start(0);
        PRISMX_ASSERT(hr == 0);

        // Mixing cycle
        auto* rawEngine = static_cast<PrismAudioEngineImpl*>(audioEngine.Get());
        std::vector<float> mixedAudio;
        rawEngine->ProcessMixingCycle(480, mixedAudio);
        PRISMX_ASSERT(mixedAudio.size() == 960);

        float maxAmp = 0.0f;
        for (float s : mixedAudio) {
            maxAmp = std::max(maxAmp, std::abs(s));
        }
        PRISMX_ASSERT(maxAmp > 0.1f);

        // 3. 3D Spatial Calculation
        AudioListener listener{};
        AudioEmitter emitterNear{}, emitterFar{};
        emitterNear.position = { 0.0f, 0.0f, 5.0f };
        emitterFar.position = { 0.0f, 0.0f, 40.0f };

        float volNear = 0.0f, panLNear = 0.0f, panRNear = 0.0f;
        float volFar = 0.0f, panLFar = 0.0f, panRFar = 0.0f;
        PrismAudioEngineImpl::Calculate3DSpatial(listener, emitterNear, volNear, panLNear, panRNear);
        PrismAudioEngineImpl::Calculate3DSpatial(listener, emitterFar, volFar, panLFar, panRFar);
        PRISMX_ASSERT(volNear > volFar);

        // 4. Controller Input
        ControllerManager::get().SetSlotConnected(1, true);
        XINPUT_GAMEPAD simPad{};
        simPad.wButtons = XINPUT_GAMEPAD_A | XINPUT_GAMEPAD_START;
        simPad.bLeftTrigger = 200;
        ControllerManager::get().SetSlotState(1, simPad);

        XINPUT_STATE padState{};
        uint32_t err = XInputGetState(1, &padState);
        PRISMX_ASSERT(err == ERROR_SUCCESS);
        PRISMX_ASSERT(padState.Gamepad.wButtons == (XINPUT_GAMEPAD_A | XINPUT_GAMEPAD_START));
        PRISMX_ASSERT(padState.Gamepad.bLeftTrigger == 200);

        // Deadzone normalization
        float normX = 0.0f, normY = 0.0f;
        ControllerManager::NormalizeThumbstick(3000, 3000, XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE, normX, normY);
        PRISMX_ASSERT(normX == 0.0f && normY == 0.0f);

        sourceVoice->DestroyVoice();
        masteringVoice->DestroyVoice();
    PRISMX_PASS()
    return 0;
}

int Test_3DMath_And_Transformations() {
    PRISMX_TEST("Test_3DMath_And_Transformations")
        using namespace prismx::math;

        // 1. Vector Operations
        Vector2 v2a(3.0f, 4.0f);
        PRISMX_ASSERT(std::abs(v2a.Length() - 5.0f) < 0.0001f);
        Vector2 v2Norm = v2a.Normalized();
        PRISMX_ASSERT(std::abs(v2Norm.Length() - 1.0f) < 0.0001f);

        Vector3 v3a(1.0f, 0.0f, 0.0f);
        Vector3 v3b(0.0f, 1.0f, 0.0f);
        Vector3 cross = v3a.Cross(v3b);
        PRISMX_ASSERT(cross == Vector3::UnitZ);
        PRISMX_ASSERT(std::abs(v3a.Dot(v3b)) < 0.0001f);

        Vector3 lerped = Vector3::Lerp(Vector3(0.0f, 0.0f, 0.0f), Vector3(10.0f, 20.0f, 30.0f), 0.5f);
        PRISMX_ASSERT(lerped.x == 5.0f && lerped.y == 10.0f && lerped.z == 15.0f);

        // 2. Matrix Transformations: Translation, Scale, Rotation
        Matrix matTrans = Matrix::CreateTranslation(10.0f, -5.0f, 25.0f);
        Vector3 pt0(0.0f, 0.0f, 0.0f);
        Vector3 transPt = matTrans.TransformCoord(pt0);
        PRISMX_ASSERT(std::abs(transPt.x - 10.0f) < 0.0001f);
        PRISMX_ASSERT(std::abs(transPt.y - (-5.0f)) < 0.0001f);
        PRISMX_ASSERT(std::abs(transPt.z - 25.0f) < 0.0001f);

        Matrix matScale = Matrix::CreateScale(2.0f, 3.0f, 4.0f);
        Vector3 scaledPt = matScale.TransformCoord(Vector3(1.0f, 1.0f, 1.0f));
        PRISMX_ASSERT(std::abs(scaledPt.x - 2.0f) < 0.0001f);
        PRISMX_ASSERT(std::abs(scaledPt.y - 3.0f) < 0.0001f);
        PRISMX_ASSERT(std::abs(scaledPt.z - 4.0f) < 0.0001f);

        // 3. Left-Handed Camera LookAt Matrix
        Vector3 eye(0.0f, 0.0f, -10.0f);
        Vector3 target(0.0f, 0.0f, 0.0f);
        Vector3 up(0.0f, 1.0f, 0.0f);
        Matrix matView = Matrix::CreateLookAtLH(eye, target, up);

        // In view space, target (0,0,0) should be at distance 10 along +Z forward
        Vector3 viewTarget = matView.TransformCoord(target);
        PRISMX_ASSERT(std::abs(viewTarget.x) < 0.0001f);
        PRISMX_ASSERT(std::abs(viewTarget.y) < 0.0001f);
        PRISMX_ASSERT(std::abs(viewTarget.z - 10.0f) < 0.0001f);

        // 4. Left-Handed Perspective Field-of-View Projection Matrix
        float fovY = std::numbers::pi_v<float> / 4.0f; // 45 degrees
        float aspect = 16.0f / 9.0f;
        float nearZ = 1.0f;
        float farZ = 100.0f;
        Matrix matProj = Matrix::CreatePerspectiveFovLH(fovY, aspect, nearZ, farZ);

        // Verify DirectX nearZ (depth -> 0.0) and farZ (depth -> 1.0)
        Vector3 pNear(0.0f, 0.0f, nearZ);
        Vector3 pFar(0.0f, 0.0f, farZ);
        Vector3 projNear = matProj.TransformCoord(pNear);
        Vector3 projFar = matProj.TransformCoord(pFar);
        PRISMX_ASSERT(std::abs(projNear.z) < 0.0001f);
        PRISMX_ASSERT(std::abs(projFar.z - 1.0f) < 0.0001f);

        // 5. Composite MVP Pipeline Matrix Multiplication
        Matrix matWorld = Matrix::CreateRotationY(0.0f) * Matrix::CreateTranslation(0.0f, 0.0f, 50.0f);
        Matrix matWVP = matWorld * matView * matProj;
        Vector3 crystalVertex(0.0f, 0.0f, 0.0f);
        Vector3 projectedCrystal = matWVP.TransformCoord(crystalVertex);
        // Crystal should be projected into valid NDC depth [0, 1]
        PRISMX_ASSERT(projectedCrystal.z >= 0.0f && projectedCrystal.z <= 1.0f);

        // 6. Color Format Packing (BGRA8888)
        Color cyan(0.0f, 1.0f, 1.0f, 1.0f);
        uint32_t bgraCyan = cyan.ToBgra8888();
        PRISMX_ASSERT(bgraCyan == 0xFF00FFFF);
    PRISMX_PASS()
    return 0;
}

int Test_DirectX_Raytracing_And_MeshShaders() {
    PRISMX_TEST("Test_DirectX_Raytracing_And_MeshShaders")
        // 1. Create DXR Raytracing Device (Tier 1.1 / FL 12_2)
        ComPtr<ID3D12Device5> device5;
        HRESULT hr = D3D12CreateRaytracingDevice(
            nullptr,
            D3D_FEATURE_LEVEL_12_2,
            IID_ID3D12Device5,
            device5.PutVoid()
        );
        PRISMX_ASSERT(SUCCEEDED(hr));
        PRISMX_ASSERT(device5.Get() != nullptr);

        // 2. Feature Queries: DXR Tier 1.1 & Mesh Shader Tier 1
        D3D12_FEATURE_DATA_D3D12_OPTIONS5 opts5{};
        hr = device5->CheckFeatureSupport(27, &opts5, sizeof(opts5));
        PRISMX_ASSERT(SUCCEEDED(hr));
        PRISMX_ASSERT(opts5.RaytracingTier == D3D12_RAYTRACING_TIER_1_1);

        D3D12_FEATURE_DATA_D3D12_OPTIONS7 opts7{};
        hr = device5->CheckFeatureSupport(32, &opts7, sizeof(opts7));
        PRISMX_ASSERT(SUCCEEDED(hr));
        PRISMX_ASSERT(opts7.MeshShaderTier == D3D12_MESH_SHADER_TIER_1);

        // 3. Acceleration Structure Prebuild Queries (BLAS & TLAS)
        D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_INPUTS blasInputs{};
        blasInputs.Type = D3D12_RAYTRACING_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL;
        blasInputs.Flags = D3D12_RAYTRACING_ACCELERATION_STRUCTURE_BUILD_FLAG_PREFER_FAST_TRACE;
        blasInputs.NumDescs = 64; // 64 Triangles
        D3D12_RAYTRACING_ACCELERATION_STRUCTURE_PREBUILD_INFO blasPrebuild{};
        device5->GetRaytracingAccelerationStructurePrebuildInfo(&blasInputs, &blasPrebuild);
        PRISMX_ASSERT(blasPrebuild.ResultDataMaxSizeInBytes > 0);
        PRISMX_ASSERT(blasPrebuild.ScratchDataSizeInBytes > 0);

        D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_INPUTS tlasInputs{};
        tlasInputs.Type = D3D12_RAYTRACING_ACCELERATION_STRUCTURE_TYPE_TOP_LEVEL;
        tlasInputs.Flags = D3D12_RAYTRACING_ACCELERATION_STRUCTURE_BUILD_FLAG_PREFER_FAST_TRACE;
        tlasInputs.NumDescs = 16; // 16 Instances
        D3D12_RAYTRACING_ACCELERATION_STRUCTURE_PREBUILD_INFO tlasPrebuild{};
        device5->GetRaytracingAccelerationStructurePrebuildInfo(&tlasInputs, &tlasPrebuild);
        PRISMX_ASSERT(tlasPrebuild.ResultDataMaxSizeInBytes > 0);
        PRISMX_ASSERT(tlasPrebuild.ScratchDataSizeInBytes > 0);

        // 4. Command Allocator and Command List 4/6
        ComPtr<ID3D12CommandAllocator> alloc;
        hr = device5->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_ID3D12CommandAllocator, alloc.PutVoid());
        PRISMX_ASSERT(SUCCEEDED(hr));

        ComPtr<ID3D12GraphicsCommandList4> cmdList4;
        hr = device5->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, alloc.Get(), nullptr, IID_ID3D12GraphicsCommandList4, cmdList4.PutVoid());
        PRISMX_ASSERT(SUCCEEDED(hr));
        PRISMX_ASSERT(cmdList4.Get() != nullptr);

        ComPtr<ID3D12GraphicsCommandList6> cmdList6;
        hr = cmdList4->QueryInterface(IID_ID3D12GraphicsCommandList6, cmdList6.PutVoid());
        PRISMX_ASSERT(SUCCEEDED(hr));
        PRISMX_ASSERT(cmdList6.Get() != nullptr);

        // 5. Build Acceleration Structures
        D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_DESC blasDesc{};
        blasDesc.Inputs = blasInputs;
        blasDesc.DestAccelerationStructureData = 0x10000;
        cmdList4->BuildRaytracingAccelerationStructure(&blasDesc, 0, nullptr);

        D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_DESC tlasDesc{};
        tlasDesc.Inputs = tlasInputs;
        tlasDesc.DestAccelerationStructureData = 0x20000;
        cmdList4->BuildRaytracingAccelerationStructure(&tlasDesc, 0, nullptr);

        auto* pCmdImpl = static_cast<Prism3D12GraphicsCommandListRaytracingImpl*>(cmdList4.Get());
        PRISMX_ASSERT(pCmdImpl->getBlasBuilds() == 1);
        PRISMX_ASSERT(pCmdImpl->getTlasBuilds() == 1);

        // 6. Raytracing State Object & Shader Identifier Inspection
        D3D12_HIT_GROUP_DESC hitGroup{};
        hitGroup.HitGroupExport = L"HitGroupAlpha";
        hitGroup.Type = D3D12_HIT_GROUP_TYPE_TRIANGLES;
        hitGroup.ClosestHitShaderImport = L"ClosestHitMain";

        D3D12_RAYTRACING_PIPELINE_CONFIG pipeCfg{};
        pipeCfg.MaxTraceRecursionDepth = 4;

        D3D12_STATE_SUBOBJECT subobjects[2]{};
        subobjects[0].Type = D3D12_STATE_SUBOBJECT_TYPE_HIT_GROUP;
        subobjects[0].pDesc = &hitGroup;
        subobjects[1].Type = D3D12_STATE_SUBOBJECT_TYPE_RAYTRACING_PIPELINE_CONFIG;
        subobjects[1].pDesc = &pipeCfg;

        D3D12_STATE_OBJECT_DESC soDesc{};
        soDesc.Type = D3D12_STATE_OBJECT_TYPE_RAYTRACING_PIPELINE;
        soDesc.NumSubobjects = 2;
        soDesc.pSubobjects = subobjects;

        ComPtr<ID3D12StateObject> stateObject;
        hr = device5->CreateStateObject(&soDesc, IID_ID3D12StateObject, stateObject.PutVoid());
        PRISMX_ASSERT(SUCCEEDED(hr));

        ComPtr<ID3D12StateObjectProperties> props;
        hr = stateObject->QueryInterface(IID_ID3D12StateObjectProperties, props.PutVoid());
        PRISMX_ASSERT(SUCCEEDED(hr));

        void* pHitId = props->GetShaderIdentifier(L"HitGroupAlpha");
        PRISMX_ASSERT(pHitId != nullptr);

        props->SetPipelineStackSize(16384);
        PRISMX_ASSERT(props->GetPipelineStackSize() == 16384);

        // 7. DispatchRays Execution & Möller-Trumbore Ray Intersections
        cmdList4->SetPipelineState1(stateObject.Get());

        D3D12_DISPATCH_RAYS_DESC dispatchDesc{};
        dispatchDesc.Width = 32;
        dispatchDesc.Height = 32;
        dispatchDesc.Depth = 1;
        cmdList4->DispatchRays(&dispatchDesc);
        PRISMX_ASSERT(pCmdImpl->getRaysDispatched() == 1024);
        PRISMX_ASSERT(pCmdImpl->getRaysHit() > 0);

        // 8. DispatchMesh Amplification Pipeline
        cmdList6->DispatchMesh(8, 2, 1);
        PRISMX_ASSERT(pCmdImpl->getMeshDispatches() == 1);
        PRISMX_ASSERT(pCmdImpl->getMeshAmplifiedPrimitives() == 1024);
    PRISMX_PASS()
    return 0;
}

int main() {
    std::cout << "========================================================\n";
    std::cout << "     PrismX Sovereign Graphics Architecture Tests     \n";
    std::cout << "========================================================\n";

    if (Test_DXGI_Infrastructure() != 0) return 1;
    if (Test_Direct3D11_SoftwareRasterizer() != 0) return 1;
    if (Test_Direct3D12_LowLevelPipeline() != 0) return 1;
    if (Test_PrismShaderVM_SIMD() != 0) return 1;
    if (Test_Vulkan13_ICD_Driver() != 0) return 1;
    if (Test_DirectX_Audio_And_Input() != 0) return 1;
    if (Test_3DMath_And_Transformations() != 0) return 1;
    if (Test_DirectX_Raytracing_And_MeshShaders() != 0) return 1;

    std::cout << "========================================================\n";
    std::cout << " ALL PRISMX GRAPHICS SUBSYSTEM TESTS PASSED! (8/8 PASS) \n";
    std::cout << "========================================================\n";
    return 0;
}

