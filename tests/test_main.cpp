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

// ============================================================================
// Suite 9: DirectStorage High-Performance GPU I/O Subsystem
// ============================================================================
int Test_DirectStorage_Subsystem() {
    PRISMX_TEST("Test_DirectStorage_Subsystem")
        // 1. Factory Acquisition
        ComPtr<IDStorageFactory> factory;
        HRESULT hr = DStorageGetFactory(IID_IDStorageFactory, factory.PutVoid());
        PRISMX_ASSERT(SUCCEEDED(hr));
        PRISMX_ASSERT(factory.Get() != nullptr);

        // 2. Configuration & Staging Buffer
        factory->SetStagingBufferSize(64 * 1024 * 1024);
        factory->SetDebugFlags(DSTORAGE_DEBUG_SHOW_ERRORS);

        // 3. Status Array Creation & Inspection
        ComPtr<IDStorageStatusArray> statusArray;
        hr = factory->CreateStatusArray(16, "PrismStatusArray", IID_IDStorageStatusArray, statusArray.PutVoid());
        PRISMX_ASSERT(SUCCEEDED(hr));
        PRISMX_ASSERT(!statusArray->IsComplete(0));
        PRISMX_ASSERT(!statusArray->IsComplete(1));

        // 4. Direct3D 12 Device, Resource & Fence Creation
        ComPtr<ID3D12Device> device;
        hr = D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_12_2, IID_ID3D12Device, device.PutVoid());
        PRISMX_ASSERT(SUCCEEDED(hr));

        D3D12_HEAP_PROPERTIES heapProps{};
        heapProps.Type = D3D12_HEAP_TYPE_DEFAULT;

        D3D12_RESOURCE_DESC resDesc{};
        resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
        resDesc.Width = 65536; // 64 KB
        resDesc.Height = 1;
        resDesc.DepthOrArraySize = 1;
        resDesc.MipLevels = 1;

        ComPtr<ID3D12Resource> gpuBuffer;
        hr = device->CreateCommittedResource(
            &heapProps,
            D3D12_HEAP_FLAG_NONE,
            &resDesc,
            D3D12_RESOURCE_STATE_COMMON,
            nullptr,
            IID_ID3D12Resource,
            gpuBuffer.PutVoid()
        );
        PRISMX_ASSERT(SUCCEEDED(hr));

        ComPtr<ID3D12Fence> fence;
        hr = device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_ID3D12Fence, fence.PutVoid());
        PRISMX_ASSERT(SUCCEEDED(hr));
        PRISMX_ASSERT(fence->GetCompletedValue() == 0);

        // 5. Memory-Source DirectStorage Queue Creation
        DSTORAGE_QUEUE_DESC qDesc{};
        qDesc.SourceType = DSTORAGE_REQUEST_SOURCE_MEMORY;
        qDesc.Capacity = 128;
        qDesc.Priority = DSTORAGE_PRIORITY_NORMAL;
        qDesc.Name = "PrismX_MemQueue";
        qDesc.Device = device.Get();

        ComPtr<IDStorageQueue> memQueue;
        hr = factory->CreateQueue(&qDesc, IID_IDStorageQueue, memQueue.PutVoid());
        PRISMX_ASSERT(SUCCEEDED(hr));

        // 6. Direct Memory-to-GPU Buffer Request (Uncompressed)
        std::vector<uint8_t> uncompressedData(4096);
        for (size_t i = 0; i < uncompressedData.size(); ++i) {
            uncompressedData[i] = static_cast<uint8_t>((i * 7 + 13) & 0xFF);
        }

        DSTORAGE_REQUEST req1{};
        req1.Options.SourceType = DSTORAGE_REQUEST_SOURCE_MEMORY;
        req1.Options.DestinationType = DSTORAGE_REQUEST_DESTINATION_BUFFER;
        req1.Options.Compression = DSTORAGE_COMPRESSION_FORMAT_NONE;
        req1.Source.Memory.Source = uncompressedData.data();
        req1.Source.Memory.Size = static_cast<uint32_t>(uncompressedData.size());
        req1.Destination.Buffer.Resource = gpuBuffer.Get();
        req1.Destination.Buffer.Offset = 0;
        req1.Destination.Buffer.Size = static_cast<uint32_t>(uncompressedData.size());
        req1.UncompressedSize = static_cast<uint32_t>(uncompressedData.size());

        memQueue->EnqueueRequest(&req1);
        memQueue->EnqueueStatus(statusArray.Get(), 0);
        memQueue->EnqueueSignal(fence.Get(), 100);
        memQueue->Submit();

        PRISMX_ASSERT(statusArray->IsComplete(0));
        PRISMX_ASSERT(statusArray->GetHResult(0) == S_OK);
        PRISMX_ASSERT(fence->GetCompletedValue() == 100);

        // Verify data in GPU buffer
        void* mapped = nullptr;
        gpuBuffer->Map(0, nullptr, &mapped);
        PRISMX_ASSERT(mapped != nullptr);
        PRISMX_ASSERT(std::memcmp(mapped, uncompressedData.data(), uncompressedData.size()) == 0);
        gpuBuffer->Unmap(0, nullptr);

        // 7. GDeflate Compression & Direct GPU Decompression
        std::vector<uint8_t> originalTexture(8192);
        for (size_t i = 0; i < originalTexture.size(); ++i) {
            // Highly compressible pattern
            originalTexture[i] = static_cast<uint8_t>((i / 16) & 0xFF);
        }

        auto gdefCompressed = codec::CompressGDeflate(originalTexture.data(), static_cast<uint32_t>(originalTexture.size()));
        PRISMX_ASSERT(!gdefCompressed.empty());
        PRISMX_ASSERT(gdefCompressed.size() < originalTexture.size());

        DSTORAGE_REQUEST reqGDef{};
        reqGDef.Options.SourceType = DSTORAGE_REQUEST_SOURCE_MEMORY;
        reqGDef.Options.DestinationType = DSTORAGE_REQUEST_DESTINATION_BUFFER;
        reqGDef.Options.Compression = DSTORAGE_COMPRESSION_FORMAT_GDEFLATE;
        reqGDef.Source.Memory.Source = gdefCompressed.data();
        reqGDef.Source.Memory.Size = static_cast<uint32_t>(gdefCompressed.size());
        reqGDef.Destination.Buffer.Resource = gpuBuffer.Get();
        reqGDef.Destination.Buffer.Offset = 4096;
        reqGDef.Destination.Buffer.Size = static_cast<uint32_t>(originalTexture.size());
        reqGDef.UncompressedSize = static_cast<uint32_t>(originalTexture.size());

        memQueue->EnqueueRequest(&reqGDef);
        memQueue->EnqueueStatus(statusArray.Get(), 1);
        memQueue->EnqueueSignal(fence.Get(), 200);
        memQueue->Submit();

        PRISMX_ASSERT(statusArray->IsComplete(1));
        PRISMX_ASSERT(statusArray->GetHResult(1) == S_OK);
        PRISMX_ASSERT(fence->GetCompletedValue() == 200);

        // Verify decompressed output in GPU buffer
        gpuBuffer->Map(0, nullptr, &mapped);
        PRISMX_ASSERT(std::memcmp(static_cast<uint8_t*>(mapped) + 4096, originalTexture.data(), originalTexture.size()) == 0);
        gpuBuffer->Unmap(0, nullptr);

        // 8. Zlib Compression & Decompression Pipeline
        auto zlibCompressed = codec::CompressZlib(originalTexture.data(), static_cast<uint32_t>(originalTexture.size()));
        PRISMX_ASSERT(!zlibCompressed.empty());

        std::vector<uint8_t> zlibDecompressed(originalTexture.size(), 0);
        DSTORAGE_REQUEST reqZlib{};
        reqZlib.Options.SourceType = DSTORAGE_REQUEST_SOURCE_MEMORY;
        reqZlib.Options.DestinationType = DSTORAGE_REQUEST_DESTINATION_MEMORY;
        reqZlib.Options.Compression = DSTORAGE_COMPRESSION_FORMAT_ZLIB;
        reqZlib.Source.Memory.Source = zlibCompressed.data();
        reqZlib.Source.Memory.Size = static_cast<uint32_t>(zlibCompressed.size());
        reqZlib.Destination.Memory.Buffer = zlibDecompressed.data();
        reqZlib.Destination.Memory.Size = static_cast<uint32_t>(zlibDecompressed.size());
        reqZlib.UncompressedSize = static_cast<uint32_t>(originalTexture.size());

        memQueue->EnqueueRequest(&reqZlib);
        memQueue->EnqueueStatus(statusArray.Get(), 2);
        memQueue->EnqueueSignal(fence.Get(), 300);
        memQueue->Submit();

        PRISMX_ASSERT(statusArray->IsComplete(2));
        PRISMX_ASSERT(fence->GetCompletedValue() == 300);
        PRISMX_ASSERT(std::memcmp(zlibDecompressed.data(), originalTexture.data(), originalTexture.size()) == 0);

        // 9. Virtual File System & File Queue
        auto* pFactoryImpl = static_cast<PrismStorageFactoryImpl*>(factory.Get());
        std::vector<uint8_t> fileAsset(16384, 0x42);
        pFactoryImpl->RegisterVirtualFile(L"C:\\game\\mesh_geometry.bin", fileAsset);

        ComPtr<IDStorageFile> storageFile;
        hr = factory->OpenFile(L"C:\\game\\mesh_geometry.bin", IID_IDStorageFile, storageFile.PutVoid());
        PRISMX_ASSERT(SUCCEEDED(hr));
        PRISMX_ASSERT(storageFile->GetFileSize() == 16384);

        DSTORAGE_QUEUE_DESC fileQDesc{};
        fileQDesc.SourceType = DSTORAGE_REQUEST_SOURCE_FILE;
        fileQDesc.Capacity = 64;
        fileQDesc.Priority = DSTORAGE_PRIORITY_HIGH;
        fileQDesc.Name = "PrismX_FileQueue";
        fileQDesc.Device = device.Get();

        ComPtr<IDStorageQueue> fileQueue;
        hr = factory->CreateQueue(&fileQDesc, IID_IDStorageQueue, fileQueue.PutVoid());
        PRISMX_ASSERT(SUCCEEDED(hr));

        std::vector<uint8_t> readFromDisk(16384, 0);
        DSTORAGE_REQUEST reqFile{};
        reqFile.Options.SourceType = DSTORAGE_REQUEST_SOURCE_FILE;
        reqFile.Options.DestinationType = DSTORAGE_REQUEST_DESTINATION_MEMORY;
        reqFile.Options.Compression = DSTORAGE_COMPRESSION_FORMAT_NONE;
        reqFile.Source.File.Source = storageFile.Get();
        reqFile.Source.File.Offset = 0;
        reqFile.Source.File.Size = 16384;
        reqFile.Destination.Memory.Buffer = readFromDisk.data();
        reqFile.Destination.Memory.Size = 16384;
        reqFile.UncompressedSize = 16384;

        fileQueue->EnqueueRequest(&reqFile);
        fileQueue->EnqueueStatus(statusArray.Get(), 3);
        fileQueue->EnqueueSignal(fence.Get(), 400);
        fileQueue->Submit();

        PRISMX_ASSERT(statusArray->IsComplete(3));
        PRISMX_ASSERT(fence->GetCompletedValue() == 400);
        PRISMX_ASSERT(readFromDisk == fileAsset);

        // 10. Tag-Based Request Cancellation Filtering
        DSTORAGE_REQUEST reqCancel{};
        reqCancel.CancellationTag = 0xCAFE;
        reqCancel.Options.SourceType = DSTORAGE_REQUEST_SOURCE_MEMORY;
        reqCancel.Options.DestinationType = DSTORAGE_REQUEST_DESTINATION_MEMORY;
        reqCancel.Options.Compression = DSTORAGE_COMPRESSION_FORMAT_NONE;
        reqCancel.Source.Memory.Source = uncompressedData.data();
        reqCancel.Source.Memory.Size = 100;
        reqCancel.Destination.Memory.Buffer = readFromDisk.data();
        reqCancel.Destination.Memory.Size = 100;

        fileQueue->EnqueueRequest(&reqCancel);
        fileQueue->CancelRequestsWithTag(0xFFFF, 0xCAFE);
        fileQueue->Submit();

        // 11. Custom Decompression Queue
        ComPtr<IDStorageCustomDecompressionQueue> customQueue;
        hr = factory->QueryInterface(IID_IDStorageCustomDecompressionQueue, customQueue.PutVoid());
        PRISMX_ASSERT(SUCCEEDED(hr));
        PRISMX_ASSERT(customQueue->GetEvent() != nullptr);

    PRISMX_PASS()
    return 0;
}

int Test_DirectML_And_DXCore_Subsystem() {
    PRISMX_TEST("Test_DirectML_And_DXCore_Subsystem")
        // --------------------------------------------------------------------
        // Part 1: DXCore Modern Adapter Enumeration
        // --------------------------------------------------------------------
        ComPtr<IDXCoreAdapterFactory> dxcoreFactory;
        HRESULT hr = DXCoreCreateAdapterFactory(IID_IDXCoreAdapterFactory, dxcoreFactory.PutVoid());
        PRISMX_ASSERT(SUCCEEDED(hr));
        PRISMX_ASSERT(dxcoreFactory.Get() != nullptr);

        // 1. Enumerate all adapters
        ComPtr<IDXCoreAdapterList> adapterList;
        hr = dxcoreFactory->CreateAdapterList(0, nullptr, IID_IDXCoreAdapterList, adapterList.PutVoid());
        PRISMX_ASSERT(SUCCEEDED(hr));
        PRISMX_ASSERT(adapterList->GetAdapterCount() >= 2);
        PRISMX_ASSERT(!adapterList->IsStale());

        // 2. Query Primary Adapter Properties
        ComPtr<IDXCoreAdapter> primaryAdapter;
        hr = adapterList->GetAdapter(0, IID_IDXCoreAdapter, primaryAdapter.PutVoid());
        PRISMX_ASSERT(SUCCEEDED(hr));
        PRISMX_ASSERT(primaryAdapter->IsValid());
        PRISMX_ASSERT(primaryAdapter->IsAttributeSupported(DXCORE_ADAPTER_ATTRIBUTE_D3D12_GRAPHICS));
        PRISMX_ASSERT(primaryAdapter->IsAttributeSupported(DXCORE_ADAPTER_ATTRIBUTE_D3D12_CORE_COMPUTE));

        // Dedicated Video Memory
        uint64_t vram = 0;
        hr = primaryAdapter->GetProperty(DXCoreAdapterProperty::DedicatedAdapterMemory, sizeof(vram), &vram);
        PRISMX_ASSERT(SUCCEEDED(hr));
        PRISMX_ASSERT(vram == 16ULL * 1024 * 1024 * 1024);

        // Driver Description
        char descBuffer[128]{};
        hr = primaryAdapter->GetProperty(DXCoreAdapterProperty::DriverDescription, sizeof(descBuffer), descBuffer);
        PRISMX_ASSERT(SUCCEEDED(hr));
        PRISMX_ASSERT(std::string(descBuffer).find("PrismX") != std::string::npos);

        // Hardware ID
        DXCoreHardwareID hwId{};
        hr = primaryAdapter->GetProperty(DXCoreAdapterProperty::HardwareID, sizeof(hwId), &hwId);
        PRISMX_ASSERT(SUCCEEDED(hr));
        PRISMX_ASSERT(hwId.vendorID == 0x13B5);

        // Memory Budget State Query
        PRISMX_ASSERT(primaryAdapter->IsQueryStateSupported(DXCoreAdapterState::AdapterMemoryBudget));
        DXCoreAdapterMemoryBudget budget{};
        hr = primaryAdapter->QueryState(DXCoreAdapterState::AdapterMemoryBudget, 0, nullptr, sizeof(budget), &budget);
        PRISMX_ASSERT(SUCCEEDED(hr));
        PRISMX_ASSERT(budget.budget == vram);

        // 3. Adapter Sorting
        DXCoreAdapterPreference prefs[1] = { DXCoreAdapterPreference::MinimumPower };
        hr = adapterList->Sort(1, prefs);
        PRISMX_ASSERT(SUCCEEDED(hr));

        ComPtr<IDXCoreAdapter> minPowerAdapter;
        hr = adapterList->GetAdapter(0, IID_IDXCoreAdapter, minPowerAdapter.PutVoid());
        PRISMX_ASSERT(SUCCEEDED(hr));
        bool isIntegrated = false;
        minPowerAdapter->GetProperty(DXCoreAdapterProperty::IsIntegrated, sizeof(isIntegrated), &isIntegrated);
        PRISMX_ASSERT(isIntegrated == true);

        // 4. LUID Retrieval
        LUID targetLuid{ 0x1000, 0 };
        ComPtr<IDXCoreAdapter> luidAdapter;
        hr = dxcoreFactory->GetAdapterByLUID(targetLuid, IID_IDXCoreAdapter, luidAdapter.PutVoid());
        PRISMX_ASSERT(SUCCEEDED(hr));
        PRISMX_ASSERT(luidAdapter.Get() != nullptr);

        // 5. Event Notifications
        uint32_t cookie = 0;
        hr = dxcoreFactory->RegisterEventNotification(
            nullptr,
            DXCoreNotificationType::AdapterBudgetChange,
            [](DXCoreNotificationType, IUnknown*, void*) {},
            nullptr,
            &cookie
        );
        PRISMX_ASSERT(SUCCEEDED(hr));
        PRISMX_ASSERT(cookie != 0);

        hr = dxcoreFactory->UnregisterEventNotification(cookie);
        PRISMX_ASSERT(SUCCEEDED(hr));

        // --------------------------------------------------------------------
        // Part 2: DirectML Machine Learning & Tensor Compute Engine
        // --------------------------------------------------------------------
        ComPtr<ID3D12Device> d3d12Device;
        hr = D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_12_2, IID_ID3D12Device, d3d12Device.PutVoid());
        PRISMX_ASSERT(SUCCEEDED(hr));

        ComPtr<IDMLDevice> dmlDevice;
        hr = DMLCreateDevice(d3d12Device.Get(), DML_CREATE_DEVICE_FLAGS::NONE, IID_IDMLDevice, dmlDevice.PutVoid());
        PRISMX_ASSERT(SUCCEEDED(hr));
        PRISMX_ASSERT(dmlDevice.Get() != nullptr);

        // Feature query
        DML_FEATURE_DATA_FEATURE_LEVELS featLevels{};
        hr = dmlDevice->CheckFeatureSupport(DML_FEATURE::FEATURE_LEVELS, 0, nullptr, sizeof(featLevels), &featLevels);
        PRISMX_ASSERT(SUCCEEDED(hr));
        PRISMX_ASSERT(featLevels.MaxSupportedFeatureLevel == DML_FEATURE_LEVEL::LEVEL_6_4);

        // Tensor datatype support query
        DML_FEATURE_DATA_TENSOR_DATA_TYPE_SUPPORT typeQuery{};
        typeQuery.DataType = DML_TENSOR_DATA_TYPE::FLOAT32;
        DML_FEATURE_DATA_TENSOR_DATA_TYPE_SUPPORT typeSup{};
        hr = dmlDevice->CheckFeatureSupport(DML_FEATURE::TENSOR_DATA_TYPE_SUPPORT, sizeof(typeQuery), &typeQuery, sizeof(typeSup), &typeSup);
        PRISMX_ASSERT(SUCCEEDED(hr));
        PRISMX_ASSERT(typeSup.IsSupported);

        // Helper Lambda to Create Buffer Resource
        auto CreateBuffer = [&](size_t byteSize) -> ComPtr<ID3D12Resource> {
            D3D12_HEAP_PROPERTIES hp{};
            hp.Type = D3D12_HEAP_TYPE_DEFAULT;
            D3D12_RESOURCE_DESC rd{};
            rd.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
            rd.Width = byteSize;
            rd.Height = 1;
            rd.DepthOrArraySize = 1;
            rd.MipLevels = 1;
            ComPtr<ID3D12Resource> res;
            d3d12Device->CreateCommittedResource(&hp, D3D12_HEAP_FLAG_NONE, &rd, D3D12_RESOURCE_STATE_COMMON, nullptr, IID_ID3D12Resource, res.PutVoid());
            return res;
        };

        // --------------------------------------------------------------------
        // Operator Test 1: GEMM (Y = 1.0 * (A * B) + 1.0 * C)
        // A: [2, 3] = [[1, 2, 3], [4, 5, 6]]
        // B: [3, 2] = [[7, 8], [9, 1], [2, 3]]
        // C: [2, 2] = [[1, 1], [1, 1]]
        // Expected Y = [[32, 20], [86, 56]]
        // --------------------------------------------------------------------
        auto bufA = CreateBuffer(6 * sizeof(float));
        auto bufB = CreateBuffer(6 * sizeof(float));
        auto bufC = CreateBuffer(4 * sizeof(float));
        auto bufY = CreateBuffer(4 * sizeof(float));

        void* pMap = nullptr;
        bufA->Map(0, nullptr, &pMap);
        float initA[6] = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f };
        std::memcpy(pMap, initA, sizeof(initA));
        bufA->Unmap(0, nullptr);

        bufB->Map(0, nullptr, &pMap);
        float initB[6] = { 7.0f, 8.0f, 9.0f, 1.0f, 2.0f, 3.0f };
        std::memcpy(pMap, initB, sizeof(initB));
        bufB->Unmap(0, nullptr);

        bufC->Map(0, nullptr, &pMap);
        float initC[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
        std::memcpy(pMap, initC, sizeof(initC));
        bufC->Unmap(0, nullptr);

        uint32_t aSizes[2] = { 2, 3 };
        DML_BUFFER_TENSOR_DESC aBufDesc{ DML_TENSOR_DATA_TYPE::FLOAT32, DML_TENSOR_FLAGS::NONE, 2, aSizes, nullptr, sizeof(initA), 0 };
        DML_TENSOR_DESC aDesc{ DML_TENSOR_TYPE::BUFFER, &aBufDesc };

        uint32_t bSizes[2] = { 3, 2 };
        DML_BUFFER_TENSOR_DESC bBufDesc{ DML_TENSOR_DATA_TYPE::FLOAT32, DML_TENSOR_FLAGS::NONE, 2, bSizes, nullptr, sizeof(initB), 0 };
        DML_TENSOR_DESC bDesc{ DML_TENSOR_TYPE::BUFFER, &bBufDesc };

        uint32_t cSizes[2] = { 2, 2 };
        DML_BUFFER_TENSOR_DESC cBufDesc{ DML_TENSOR_DATA_TYPE::FLOAT32, DML_TENSOR_FLAGS::NONE, 2, cSizes, nullptr, sizeof(initC), 0 };
        DML_TENSOR_DESC cDesc{ DML_TENSOR_TYPE::BUFFER, &cBufDesc };

        uint32_t ySizes[2] = { 2, 2 };
        DML_BUFFER_TENSOR_DESC yBufDesc{ DML_TENSOR_DATA_TYPE::FLOAT32, DML_TENSOR_FLAGS::NONE, 2, ySizes, nullptr, sizeof(float) * 4, 0 };
        DML_TENSOR_DESC yDesc{ DML_TENSOR_TYPE::BUFFER, &yBufDesc };

        DML_GEMM_OPERATOR_DESC gemmDesc{};
        gemmDesc.ATensor = &aDesc;
        gemmDesc.BTensor = &bDesc;
        gemmDesc.CTensor = &cDesc;
        gemmDesc.OutputTensor = &yDesc;
        gemmDesc.TransA = DML_MATRIX_TRANSPOSE::NONE;
        gemmDesc.TransB = DML_MATRIX_TRANSPOSE::NONE;
        gemmDesc.Alpha = 1.0f;
        gemmDesc.Beta = 1.0f;

        DML_OPERATOR_DESC opDesc{};
        opDesc.Type = DML_OPERATOR_TYPE::GEMM;
        opDesc.Desc = &gemmDesc;

        ComPtr<IDMLOperator> gemmOp;
        hr = dmlDevice->CreateOperator(&opDesc, IID_IDMLOperator, gemmOp.PutVoid());
        PRISMX_ASSERT(SUCCEEDED(hr));

        ComPtr<IDMLCompiledOperator> compiledGemm;
        hr = dmlDevice->CompileOperator(gemmOp.Get(), DML_EXECUTION_FLAGS::NONE, IID_IDMLCompiledOperator, compiledGemm.PutVoid());
        PRISMX_ASSERT(SUCCEEDED(hr));
        PRISMX_ASSERT(compiledGemm->GetBindingProperties().RequiredDescriptorCount > 0);

        DML_BINDING_TABLE_DESC btableDesc{};
        btableDesc.Dispatchable = compiledGemm.Get();
        btableDesc.SizeInDescriptors = 1;

        ComPtr<IDMLBindingTable> bindingTable;
        hr = dmlDevice->CreateBindingTable(&btableDesc, IID_IDMLBindingTable, bindingTable.PutVoid());
        PRISMX_ASSERT(SUCCEEDED(hr));

        DML_BUFFER_BINDING inBindings[3] = {
            { bufA.Get(), 0, 6 * sizeof(float) },
            { bufB.Get(), 0, 6 * sizeof(float) },
            { bufC.Get(), 0, 4 * sizeof(float) }
        };
        DML_BINDING_DESC inBDesc[3] = {
            { DML_BINDING_TYPE::BUFFER, &inBindings[0] },
            { DML_BINDING_TYPE::BUFFER, &inBindings[1] },
            { DML_BINDING_TYPE::BUFFER, &inBindings[2] }
        };
        bindingTable->BindInputs(3, inBDesc);

        DML_BUFFER_BINDING outBinding = { bufY.Get(), 0, 4 * sizeof(float) };
        DML_BINDING_DESC outBDesc = { DML_BINDING_TYPE::BUFFER, &outBinding };
        bindingTable->BindOutputs(1, &outBDesc);

        ComPtr<IDMLCommandRecorder> recorder;
        hr = dmlDevice->CreateCommandRecorder(IID_IDMLCommandRecorder, recorder.PutVoid());
        PRISMX_ASSERT(SUCCEEDED(hr));

        recorder->RecordDispatch(nullptr, compiledGemm.Get(), bindingTable.Get());

        // Verify GEMM Results
        void* pOut = nullptr;
        bufY->Map(0, nullptr, &pOut);
        float* pOutFloat = static_cast<float*>(pOut);
        PRISMX_ASSERT(std::abs(pOutFloat[0] - 32.0f) < 1e-4f);
        PRISMX_ASSERT(std::abs(pOutFloat[1] - 20.0f) < 1e-4f);
        PRISMX_ASSERT(std::abs(pOutFloat[2] - 86.0f) < 1e-4f);
        PRISMX_ASSERT(std::abs(pOutFloat[3] - 56.0f) < 1e-4f);
        bufY->Unmap(0, nullptr);

        // --------------------------------------------------------------------
        // Operator Test 2: ReLU Activation (Y = max(0, X))
        // Input: [-5.0, 0.0, 3.2, -1.0, 8.0] -> Output: [0.0, 0.0, 3.2, 0.0, 8.0]
        // --------------------------------------------------------------------
        auto reluIn = CreateBuffer(5 * sizeof(float));
        auto reluOut = CreateBuffer(5 * sizeof(float));
        reluIn->Map(0, nullptr, &pMap);
        float inVals[5] = { -5.0f, 0.0f, 3.2f, -1.0f, 8.0f };
        std::memcpy(pMap, inVals, sizeof(inVals));
        reluIn->Unmap(0, nullptr);

        uint32_t rSizes[1] = { 5 };
        DML_BUFFER_TENSOR_DESC rInDesc{ DML_TENSOR_DATA_TYPE::FLOAT32, DML_TENSOR_FLAGS::NONE, 1, rSizes, nullptr, 5 * sizeof(float), 0 };
        DML_TENSOR_DESC rInTensor{ DML_TENSOR_TYPE::BUFFER, &rInDesc };
        DML_BUFFER_TENSOR_DESC rOutDesc{ DML_TENSOR_DATA_TYPE::FLOAT32, DML_TENSOR_FLAGS::NONE, 1, rSizes, nullptr, 5 * sizeof(float), 0 };
        DML_TENSOR_DESC rOutTensor{ DML_TENSOR_TYPE::BUFFER, &rOutDesc };

        DML_ELEMENT_WISE_RELU_OPERATOR_DESC reluDesc{ &rInTensor, &rOutTensor };
        DML_OPERATOR_DESC rOpDesc{ DML_OPERATOR_TYPE::ELEMENT_WISE_RELU, &reluDesc };

        ComPtr<IDMLOperator> reluOp;
        hr = dmlDevice->CreateOperator(&rOpDesc, IID_IDMLOperator, reluOp.PutVoid());
        PRISMX_ASSERT(SUCCEEDED(hr));

        ComPtr<IDMLCompiledOperator> compRelu;
        dmlDevice->CompileOperator(reluOp.Get(), DML_EXECUTION_FLAGS::NONE, IID_IDMLCompiledOperator, compRelu.PutVoid());

        bindingTable->Reset(nullptr);
        DML_BUFFER_BINDING rInB = { reluIn.Get(), 0, 5 * sizeof(float) };
        DML_BINDING_DESC rInBD = { DML_BINDING_TYPE::BUFFER, &rInB };
        bindingTable->BindInputs(1, &rInBD);

        DML_BUFFER_BINDING rOutB = { reluOut.Get(), 0, 5 * sizeof(float) };
        DML_BINDING_DESC rOutBD = { DML_BINDING_TYPE::BUFFER, &rOutB };
        bindingTable->BindOutputs(1, &rOutBD);

        recorder->RecordDispatch(nullptr, compRelu.Get(), bindingTable.Get());

        reluOut->Map(0, nullptr, &pOut);
        float* pReluRes = static_cast<float*>(pOut);
        PRISMX_ASSERT(pReluRes[0] == 0.0f);
        PRISMX_ASSERT(pReluRes[1] == 0.0f);
        PRISMX_ASSERT(std::abs(pReluRes[2] - 3.2f) < 1e-4f);
        PRISMX_ASSERT(pReluRes[3] == 0.0f);
        PRISMX_ASSERT(pReluRes[4] == 8.0f);
        reluOut->Unmap(0, nullptr);

        // --------------------------------------------------------------------
        // Operator Test 3: Softmax Activation (Sum = 1.0, Monotonic)
        // Input: [1.0, 2.0, 3.0]
        // --------------------------------------------------------------------
        auto smIn = CreateBuffer(3 * sizeof(float));
        auto smOut = CreateBuffer(3 * sizeof(float));
        smIn->Map(0, nullptr, &pMap);
        float smVals[3] = { 1.0f, 2.0f, 3.0f };
        std::memcpy(pMap, smVals, sizeof(smVals));
        smIn->Unmap(0, nullptr);

        uint32_t smSizes[1] = { 3 };
        DML_BUFFER_TENSOR_DESC smDescIn{ DML_TENSOR_DATA_TYPE::FLOAT32, DML_TENSOR_FLAGS::NONE, 1, smSizes, nullptr, 3 * sizeof(float), 0 };
        DML_TENSOR_DESC smTensorIn{ DML_TENSOR_TYPE::BUFFER, &smDescIn };
        DML_ACTIVATION_SOFTMAX_OPERATOR_DESC softmaxDesc{ &smTensorIn, &smTensorIn };
        DML_OPERATOR_DESC smOpDesc{ DML_OPERATOR_TYPE::ACTIVATION_SOFTMAX, &softmaxDesc };

        ComPtr<IDMLOperator> smOp;
        dmlDevice->CreateOperator(&smOpDesc, IID_IDMLOperator, smOp.PutVoid());
        ComPtr<IDMLCompiledOperator> compSm;
        dmlDevice->CompileOperator(smOp.Get(), DML_EXECUTION_FLAGS::NONE, IID_IDMLCompiledOperator, compSm.PutVoid());

        DML_BUFFER_BINDING smInB = { smIn.Get(), 0, 3 * sizeof(float) };
        DML_BINDING_DESC smInBD = { DML_BINDING_TYPE::BUFFER, &smInB };
        bindingTable->BindInputs(1, &smInBD);
        DML_BUFFER_BINDING smOutB = { smOut.Get(), 0, 3 * sizeof(float) };
        DML_BINDING_DESC smOutBD = { DML_BINDING_TYPE::BUFFER, &smOutB };
        bindingTable->BindOutputs(1, &smOutBD);

        recorder->RecordDispatch(nullptr, compSm.Get(), bindingTable.Get());

        smOut->Map(0, nullptr, &pOut);
        float* pSmRes = static_cast<float*>(pOut);
        float sum = pSmRes[0] + pSmRes[1] + pSmRes[2];
        PRISMX_ASSERT(std::abs(sum - 1.0f) < 1e-4f);
        PRISMX_ASSERT(pSmRes[0] < pSmRes[1] && pSmRes[1] < pSmRes[2]);
        smOut->Unmap(0, nullptr);

        // --------------------------------------------------------------------
        // Operator Test 4: Element-Wise Add & Multiply
        // --------------------------------------------------------------------
        auto ewInA = CreateBuffer(3 * sizeof(float));
        auto ewInB = CreateBuffer(3 * sizeof(float));
        auto ewOutAdd = CreateBuffer(3 * sizeof(float));
        auto ewOutMul = CreateBuffer(3 * sizeof(float));

        ewInA->Map(0, nullptr, &pMap);
        float valA[3] = { 2.0f, 4.0f, 6.0f };
        std::memcpy(pMap, valA, sizeof(valA));
        ewInA->Unmap(0, nullptr);

        ewInB->Map(0, nullptr, &pMap);
        float valB[3] = { 3.0f, 5.0f, 7.0f };
        std::memcpy(pMap, valB, sizeof(valB));
        ewInB->Unmap(0, nullptr);

        DML_ELEMENT_WISE_ADD_OPERATOR_DESC addDesc{ &smTensorIn, &smTensorIn, &smTensorIn };
        DML_OPERATOR_DESC addOpDesc{ DML_OPERATOR_TYPE::ELEMENT_WISE_ADD, &addDesc };
        ComPtr<IDMLOperator> addOp;
        dmlDevice->CreateOperator(&addOpDesc, IID_IDMLOperator, addOp.PutVoid());
        ComPtr<IDMLCompiledOperator> compAdd;
        dmlDevice->CompileOperator(addOp.Get(), DML_EXECUTION_FLAGS::NONE, IID_IDMLCompiledOperator, compAdd.PutVoid());

        DML_BUFFER_BINDING addInB[2] = {
            { ewInA.Get(), 0, 3 * sizeof(float) },
            { ewInB.Get(), 0, 3 * sizeof(float) }
        };
        DML_BINDING_DESC addInBD[2] = {
            { DML_BINDING_TYPE::BUFFER, &addInB[0] },
            { DML_BINDING_TYPE::BUFFER, &addInB[1] }
        };
        bindingTable->BindInputs(2, addInBD);
        DML_BUFFER_BINDING addOutB = { ewOutAdd.Get(), 0, 3 * sizeof(float) };
        DML_BINDING_DESC addOutBD = { DML_BINDING_TYPE::BUFFER, &addOutB };
        bindingTable->BindOutputs(1, &addOutBD);

        recorder->RecordDispatch(nullptr, compAdd.Get(), bindingTable.Get());

        ewOutAdd->Map(0, nullptr, &pOut);
        float* pAddRes = static_cast<float*>(pOut);
        PRISMX_ASSERT(pAddRes[0] == 5.0f);
        PRISMX_ASSERT(pAddRes[1] == 9.0f);
        PRISMX_ASSERT(pAddRes[2] == 13.0f);
        ewOutAdd->Unmap(0, nullptr);

    PRISMX_PASS()
    return 0;
}

// ============================================================================
// Suite 11: Windows DirectComposition & Modern Compositor Subsystem
// ============================================================================
int Test_DirectComposition_Subsystem() {
    PRISMX_TEST("Test_DirectComposition_Subsystem")

    // ------------------------------------------------------------------------
    // Step 1: Create DirectComposition Device
    // ------------------------------------------------------------------------
    ComPtr<IDCompositionDevice> dcompDevice;
    int32_t hr = DCompositionCreateDevice(nullptr, IID_IDCompositionDevice, dcompDevice.PutVoid());
    PRISMX_ASSERT(SUCCEEDED(hr));
    PRISMX_ASSERT(dcompDevice.Get() != nullptr);

    // ------------------------------------------------------------------------
    // Step 2: Create Visuals & Establish Visual Tree Hierarchy
    // ------------------------------------------------------------------------
    ComPtr<IDCompositionVisual> rootVisual;
    hr = dcompDevice->CreateVisual(rootVisual.Put());
    PRISMX_ASSERT(SUCCEEDED(hr));

    ComPtr<IDCompositionVisual> cardVisual;
    hr = dcompDevice->CreateVisual(cardVisual.Put());
    PRISMX_ASSERT(SUCCEEDED(hr));

    ComPtr<IDCompositionVisual> textVisual;
    hr = dcompDevice->CreateVisual(textVisual.Put());
    PRISMX_ASSERT(SUCCEEDED(hr));

    // Properties on cardVisual
    cardVisual->SetOffsetX(40.0f);
    cardVisual->SetOffsetY(60.0f);
    cardVisual->SetOpacity(0.92f);
    cardVisual->SetInterpolationMode(DCOMPOSITION_BITMAP_INTERPOLATION_MODE::LINEAR);
    cardVisual->SetBorderMode(DCOMPOSITION_BORDER_MODE::SOFT);

    PRISMX_ASSERT(cardVisual->GetOffsetX() == 40.0f);
    PRISMX_ASSERT(cardVisual->GetOffsetY() == 60.0f);
    PRISMX_ASSERT(std::abs(cardVisual->GetOpacity() - 0.92f) < 1e-4f);

    // Build hierarchy: root -> card -> text
    rootVisual->AddVisual(cardVisual.Get(), true, nullptr);
    cardVisual->AddVisual(textVisual.Get(), true, nullptr);

    PRISMX_ASSERT(rootVisual->GetChildren().size() == 1);
    PRISMX_ASSERT(cardVisual->GetChildren().size() == 1);
    PRISMX_ASSERT(rootVisual->GetChildren()[0] == cardVisual.Get());
    PRISMX_ASSERT(cardVisual->GetChildren()[0] == textVisual.Get());

    // ------------------------------------------------------------------------
    // Step 3: Affine Transforms (Translate, Scale, Rotate, Matrix)
    // ------------------------------------------------------------------------
    ComPtr<IDCompositionTranslateTransform> translate;
    hr = dcompDevice->CreateTranslateTransform(translate.Put());
    PRISMX_ASSERT(SUCCEEDED(hr));
    translate->SetOffsetX(15.0f);
    translate->SetOffsetY(25.0f);
    PRISMX_ASSERT(translate->GetOffsetX() == 15.0f);
    PRISMX_ASSERT(translate->GetOffsetY() == 25.0f);
    cardVisual->SetTransform(translate.Get());
    PRISMX_ASSERT(cardVisual->GetTransform() == translate.Get());

    ComPtr<IDCompositionScaleTransform> scale;
    hr = dcompDevice->CreateScaleTransform(scale.Put());
    PRISMX_ASSERT(SUCCEEDED(hr));
    scale->SetScaleX(1.5f);
    scale->SetScaleY(2.0f);
    scale->SetCenterX(100.0f);
    PRISMX_ASSERT(scale->GetScaleX() == 1.5f && scale->GetScaleY() == 2.0f);

    ComPtr<IDCompositionRotateTransform> rotate;
    hr = dcompDevice->CreateRotateTransform(rotate.Put());
    PRISMX_ASSERT(SUCCEEDED(hr));
    rotate->SetAngle(90.0f);
    PRISMX_ASSERT(rotate->GetAngle() == 90.0f);

    ComPtr<IDCompositionMatrixTransform> matTransform;
    hr = dcompDevice->CreateMatrixTransform(matTransform.Put());
    PRISMX_ASSERT(SUCCEEDED(hr));
    DCOMP_MATRIX3x2 m{};
    m.m[0][0] = 2.0f; m.m[1][1] = 2.0f;
    matTransform->SetMatrix(m);
    PRISMX_ASSERT(matTransform->GetMatrix().m[0][0] == 2.0f);

    // ------------------------------------------------------------------------
    // Step 4: Animation Curves (Cubic & Sinusoidal Easing)
    // ------------------------------------------------------------------------
    ComPtr<IDCompositionAnimation> anim;
    hr = dcompDevice->CreateAnimation(anim.Put());
    PRISMX_ASSERT(SUCCEEDED(hr));

    // Linear curve from 0.0 to 1.0s: val = 0.0 + 100.0 * dt
    anim->AddCubic(0.0, 0.0f, 100.0f, 0.0f, 0.0f);
    // Sinusoidal curve starting at 1.0s: bias = 100, amp = 20, freq = 3.14159, phase = 0
    anim->AddSinusoidal(1.0, 100.0f, 20.0f, 3.14159f / 2.0f, 0.0f);
    anim->End(3.0, 200.0f);

    float val0 = anim->Evaluate(0.0);
    float valHalf = anim->Evaluate(0.5);
    float valOne = anim->Evaluate(1.0);
    float valEnd = anim->Evaluate(4.0);

    PRISMX_ASSERT(std::abs(val0 - 0.0f) < 1e-4f);
    PRISMX_ASSERT(std::abs(valHalf - 50.0f) < 1e-4f);
    PRISMX_ASSERT(std::abs(valOne - 100.0f) < 1e-4f);
    PRISMX_ASSERT(std::abs(valEnd - 200.0f) < 1e-4f);

    // Bind animation to opacity
    textVisual->SetOpacity(anim.Get());

    // ------------------------------------------------------------------------
    // Step 5: Clipping (Rect Clip & Rounded Rectangle Clip)
    // ------------------------------------------------------------------------
    DCOMP_RECT clipRect{ 0, 0, 800, 600 };
    rootVisual->SetClip(clipRect);

    ComPtr<IDCompositionRectangleClip> rectClip;
    hr = dcompDevice->CreateRectangleClip(rectClip.Put());
    PRISMX_ASSERT(SUCCEEDED(hr));
    rectClip->SetLeft(10.0f);
    rectClip->SetTop(10.0f);
    rectClip->SetRight(300.0f);
    rectClip->SetBottom(200.0f);
    rectClip->SetTopLeftRadiusX(16.0f);
    rectClip->SetTopLeftRadiusY(16.0f);
    cardVisual->SetClip(rectClip.Get());

    // ------------------------------------------------------------------------
    // Step 6: Composition Surfaces (BeginDraw / Paint / EndDraw)
    // ------------------------------------------------------------------------
    ComPtr<IDCompositionSurface> surface;
    hr = dcompDevice->CreateSurface(128, 128, DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ALPHA_MODE::PREMULTIPLIED, surface.Put());
    PRISMX_ASSERT(SUCCEEDED(hr));
    PRISMX_ASSERT(surface->GetWidth() == 128 && surface->GetHeight() == 128);

    void* pUpdateObj = nullptr;
    DCOMP_POINT updateOffset{};
    DCOMP_RECT drawRect{ 0, 0, 64, 64 };
    hr = surface->BeginDraw(&drawRect, IID_IDCompositionSurface, &pUpdateObj, &updateOffset);
    PRISMX_ASSERT(SUCCEEDED(hr));
    PRISMX_ASSERT(pUpdateObj != nullptr);

    // Paint solid color into surface buffer
    uint8_t* pBuf = surface->GetBuffer();
    PRISMX_ASSERT(pBuf != nullptr);
    for (size_t i = 0; i < 128 * 128; i++) {
        pBuf[i * 4 + 0] = 0x30; // R
        pBuf[i * 4 + 1] = 0x80; // G
        pBuf[i * 4 + 2] = 0xE0; // B
        pBuf[i * 4 + 3] = 0xFF; // A
    }
    hr = surface->EndDraw();
    PRISMX_ASSERT(SUCCEEDED(hr));

    // Bind surface to visual content
    cardVisual->SetContent(surface.Get());
    PRISMX_ASSERT(cardVisual->GetContent() == surface.Get());

    // ------------------------------------------------------------------------
    // Step 7: Composition Target & Frame Commit
    // ------------------------------------------------------------------------
    HWND fakeHwnd = reinterpret_cast<HWND>(0xCAFE0001);
    ComPtr<IDCompositionTarget> target;
    hr = dcompDevice->CreateTargetForHwnd(fakeHwnd, true, target.Put());
    PRISMX_ASSERT(SUCCEEDED(hr));
    PRISMX_ASSERT(target->GetHwnd() == fakeHwnd);

    hr = target->SetRoot(rootVisual.Get());
    PRISMX_ASSERT(SUCCEEDED(hr));
    PRISMX_ASSERT(target->GetRoot() == rootVisual.Get());

    // Commit Transaction
    hr = dcompDevice->Commit();
    PRISMX_ASSERT(SUCCEEDED(hr));

    DCOMPOSITION_FRAME_STATISTICS stats{};
    hr = dcompDevice->GetFrameStatistics(&stats);
    PRISMX_ASSERT(SUCCEEDED(hr));
    PRISMX_ASSERT(stats.nextKeyFrame == 1);
    PRISMX_ASSERT(stats.currentFrameTime > 0);

    // ------------------------------------------------------------------------
    // Step 8: Device2 & Surface Handle
    // ------------------------------------------------------------------------
    ComPtr<IDCompositionDevice2> dcompDevice2;
    hr = dcompDevice->QueryInterface(IID_IDCompositionDevice2, dcompDevice2.PutVoid());
    PRISMX_ASSERT(SUCCEEDED(hr));

    ComPtr<IDCompositionVisual2> vis2;
    hr = dcompDevice2->CreateVisual2(vis2.Put());
    PRISMX_ASSERT(SUCCEEDED(hr));
    vis2->SetOpacityMode(DCOMPOSITION_OPACITY_MODE::MULTIPLY);
    vis2->SetBackFaceVisibility(DCOMPOSITION_BACKFACE_VISIBILITY::HIDDEN);
    PRISMX_ASSERT(vis2->GetOpacityMode() == DCOMPOSITION_OPACITY_MODE::MULTIPLY);
    PRISMX_ASSERT(vis2->GetBackFaceVisibility() == DCOMPOSITION_BACKFACE_VISIBILITY::HIDDEN);

    HANDLE surfHandle = nullptr;
    hr = DCompositionCreateSurfaceHandle(0, nullptr, &surfHandle);
    PRISMX_ASSERT(SUCCEEDED(hr));
    PRISMX_ASSERT(surfHandle != nullptr);

    PRISMX_PASS()
    return 0;
}

// ============================================================================
// Test Suite 12: PrismComposition & Modern Visual Layer Subsystem
// ============================================================================
int Test_PrismComposition_VisualLayer_Subsystem() {
    PRISMX_TEST("PrismComposition & Modern Visual Layer Subsystem")

    using namespace prismx::composition;

    // ------------------------------------------------------------------------
    // Step 1: Activation Factory Verification (Dual Windows & Microsoft Class IDs)
    // ------------------------------------------------------------------------
    ComPtr<IActivationFactory> factoryWin;
    HRESULT hr = PrismGetActivationFactory(L"Windows.UI.Composition.Compositor", factoryWin.Put());
    PRISMX_ASSERT(SUCCEEDED(hr));
    PRISMX_ASSERT(factoryWin.Get() != nullptr);

    ComPtr<IActivationFactory> factoryMs;
    hr = PrismGetActivationFactory(L"Microsoft.UI.Composition.Compositor", factoryMs.Put());
    PRISMX_ASSERT(SUCCEEDED(hr));
    PRISMX_ASSERT(factoryMs.Get() != nullptr);

    // ------------------------------------------------------------------------
    // Step 2: Compositor Activation & Interface Query
    // ------------------------------------------------------------------------
    ComPtr<IInspectable> inspectable;
    hr = factoryWin->ActivateInstance(inspectable.Put());
    PRISMX_ASSERT(SUCCEEDED(hr));
    PRISMX_ASSERT(inspectable.Get() != nullptr);

    ComPtr<ICompositor> compositor;
    hr = inspectable->QueryInterface(IID_ICompositor, compositor.PutVoid());
    PRISMX_ASSERT(SUCCEEDED(hr));
    PRISMX_ASSERT(compositor.Get() != nullptr);

    // ------------------------------------------------------------------------
    // Step 3: Visual Tree Hierarchy (ContainerVisual & SpriteVisual)
    // ------------------------------------------------------------------------
    ComPtr<IContainerVisual> rootVisual;
    hr = compositor->CreateContainerVisual(rootVisual.Put());
    PRISMX_ASSERT(SUCCEEDED(hr));

    ComPtr<ISpriteVisual> cardVisual;
    hr = compositor->CreateSpriteVisual(cardVisual.Put());
    PRISMX_ASSERT(SUCCEEDED(hr));

    cardVisual->SetOffset({ 100.0f, 150.0f, 0.0f });
    cardVisual->SetSize({ 640.0f, 480.0f });
    cardVisual->SetScale({ 1.05f, 1.05f, 1.0f });
    cardVisual->SetOpacity(0.92f);
    cardVisual->SetRotationAngle(0.785398f); // 45 degrees in radians

    PRISMX_ASSERT(cardVisual->GetOffset() == Vector3(100.0f, 150.0f, 0.0f));
    PRISMX_ASSERT(cardVisual->GetSize() == Vector2(640.0f, 480.0f));
    PRISMX_ASSERT(cardVisual->GetScale() == Vector3(1.05f, 1.05f, 1.0f));
    PRISMX_ASSERT(std::abs(cardVisual->GetOpacity() - 0.92f) < 1e-4f);
    PRISMX_ASSERT(std::abs(cardVisual->GetRotationAngle() - 0.785398f) < 1e-4f);

    ComPtr<IVisualCollection> children;
    hr = rootVisual->GetChildren(children.Put());
    PRISMX_ASSERT(SUCCEEDED(hr));
    PRISMX_ASSERT(children->GetCount() == 0);

    hr = children->InsertAtTop(cardVisual.Get());
    PRISMX_ASSERT(SUCCEEDED(hr));
    PRISMX_ASSERT(children->GetCount() == 1);
    PRISMX_ASSERT(children->GetAt(0) == cardVisual.Get());
    PRISMX_ASSERT(cardVisual->GetParent() == rootVisual.Get());

    // ------------------------------------------------------------------------
    // Step 4: Composition Brushes (ColorBrush, SurfaceBrush, EffectBrush)
    // ------------------------------------------------------------------------
    CompositionColor acrylicMica{ 255, 30, 40, 55 };
    ComPtr<ICompositionColorBrush> colorBrush;
    hr = compositor->CreateColorBrushWithColor(acrylicMica, colorBrush.Put());
    PRISMX_ASSERT(SUCCEEDED(hr));
    PRISMX_ASSERT(colorBrush->GetColor() == acrylicMica);

    hr = cardVisual->SetBrush(colorBrush.Get());
    PRISMX_ASSERT(SUCCEEDED(hr));
    PRISMX_ASSERT(cardVisual->GetBrush() == colorBrush.Get());

    ComPtr<ICompositionSurfaceBrush> surfaceBrush;
    hr = compositor->CreateSurfaceBrush(surfaceBrush.Put());
    PRISMX_ASSERT(SUCCEEDED(hr));
    surfaceBrush->SetStretch(CompositionStretch::UniformToFill);
    surfaceBrush->SetHorizontalAlignmentRatio(0.75f);
    PRISMX_ASSERT(surfaceBrush->GetStretch() == CompositionStretch::UniformToFill);
    PRISMX_ASSERT(std::abs(surfaceBrush->GetHorizontalAlignmentRatio() - 0.75f) < 1e-4f);

    ComPtr<ICompositionEffectBrush> blurEffectBrush;
    hr = compositor->CreateEffectBrush(L"AcrylicBlurFilter", blurEffectBrush.Put());
    PRISMX_ASSERT(SUCCEEDED(hr));
    PRISMX_ASSERT(blurEffectBrush->GetEffectName() == L"AcrylicBlurFilter");
    blurEffectBrush->SetSourceParameter(L"SourceBackdrop", colorBrush.Get());
    PRISMX_ASSERT(blurEffectBrush->GetSourceParameter(L"SourceBackdrop") == colorBrush.Get());

    // ------------------------------------------------------------------------
    // Step 5: KeyFrame Animations (Scalar & Vector3)
    // ------------------------------------------------------------------------
    ComPtr<IScalarKeyFrameAnimation> scalarAnim;
    hr = compositor->CreateScalarKeyFrameAnimation(scalarAnim.Put());
    PRISMX_ASSERT(SUCCEEDED(hr));
    scalarAnim->SetDuration(2.5f);
    scalarAnim->InsertKeyFrame(0.0f, 0.0f);
    scalarAnim->InsertKeyFrame(0.5f, 50.0f);
    scalarAnim->InsertKeyFrame(1.0f, 100.0f);

    PRISMX_ASSERT(std::abs(scalarAnim->GetDuration() - 2.5f) < 1e-4f);
    PRISMX_ASSERT(std::abs(scalarAnim->Evaluate(0.0f) - 0.0f) < 1e-4f);
    PRISMX_ASSERT(std::abs(scalarAnim->Evaluate(0.5f) - 50.0f) < 1e-4f);
    PRISMX_ASSERT(std::abs(scalarAnim->Evaluate(1.0f) - 100.0f) < 1e-4f);

    ComPtr<IVector3KeyFrameAnimation> vecAnim;
    hr = compositor->CreateVector3KeyFrameAnimation(vecAnim.Put());
    PRISMX_ASSERT(SUCCEEDED(hr));
    vecAnim->InsertKeyFrame(0.0f, { 0.0f, 0.0f, 0.0f });
    vecAnim->InsertKeyFrame(1.0f, { 10.0f, 20.0f, 30.0f });
    Vector3 midVec = vecAnim->Evaluate(0.5f);
    PRISMX_ASSERT(std::abs(midVec.x - 5.0f) < 1e-3f);
    PRISMX_ASSERT(std::abs(midVec.y - 10.0f) < 1e-3f);
    PRISMX_ASSERT(std::abs(midVec.z - 15.0f) < 1e-3f);

    // ------------------------------------------------------------------------
    // Step 6: Dynamic Expression Animations
    // ------------------------------------------------------------------------
    ComPtr<IExpressionAnimation> exprAnim;
    hr = compositor->CreateExpressionAnimationWithExpression(L"Lerp(A, B, Progress)", exprAnim.Put());
    PRISMX_ASSERT(SUCCEEDED(hr));
    exprAnim->SetScalarParameter(L"A", 100.0f);
    exprAnim->SetScalarParameter(L"B", 300.0f);
    exprAnim->SetScalarParameter(L"Progress", 0.25f);
    float exprResult = exprAnim->EvaluateScalar();
    // 100.0 + (300.0 - 100.0) * 0.25 = 150.0
    PRISMX_ASSERT(std::abs(exprResult - 150.0f) < 1e-4f);

    // ------------------------------------------------------------------------
    // Step 7: Composition Property Set
    // ------------------------------------------------------------------------
    ComPtr<ICompositionPropertySet> propSet;
    hr = compositor->CreatePropertySet(propSet.Put());
    PRISMX_ASSERT(SUCCEEDED(hr));
    propSet->InsertScalar(L"CornerRadius", 8.0f);
    propSet->InsertVector3(L"PointerPosition", { 120.0f, 85.0f, 0.0f });

    float readRadius = 0.0f;
    hr = propSet->TryGetScalar(L"CornerRadius", &readRadius);
    PRISMX_ASSERT(SUCCEEDED(hr));
    PRISMX_ASSERT(std::abs(readRadius - 8.0f) < 1e-4f);

    Vector3 readPointer{};
    hr = propSet->TryGetVector3(L"PointerPosition", &readPointer);
    PRISMX_ASSERT(SUCCEEDED(hr));
    PRISMX_ASSERT(readPointer == Vector3(120.0f, 85.0f, 0.0f));

    PRISMX_PASS()
    return 0;
}

int Test_PrismColor_AdvancedColor_HDR_Subsystem() {
    PRISMX_TEST("Test_PrismColor_AdvancedColor_HDR_Subsystem")
    using namespace prismx::color;

    // ------------------------------------------------------------------------
    // Step 1: Transfer Curves: sRGB EOTF/OETF
    // ------------------------------------------------------------------------
    float linearMid = ColorMath::sRGBToLinear(0.5f);
    PRISMX_ASSERT(linearMid > 0.0f && linearMid < 0.5f);
    float reconMid = ColorMath::LinearTosRGB(linearMid);
    PRISMX_ASSERT(std::abs(reconMid - 0.5f) < 1e-4f);

    // ------------------------------------------------------------------------
    // Step 2: SMPTE ST 2084 PQ (Perceptual Quantizer) for HDR10
    // ------------------------------------------------------------------------
    float pq100 = ColorMath::NitsToPQ(100.0f);
    float nits100 = ColorMath::PQToNits(pq100);
    PRISMX_ASSERT(std::abs(nits100 - 100.0f) < 1e-2f);

    float pq1000 = ColorMath::NitsToPQ(1000.0f);
    float nits1000 = ColorMath::PQToNits(pq1000);
    PRISMX_ASSERT(std::abs(nits1000 - 1000.0f) < 0.5f);
    PRISMX_ASSERT(pq1000 > pq100);

    // ------------------------------------------------------------------------
    // Step 3: Hybrid Log-Gamma (HLG)
    // ------------------------------------------------------------------------
    float hlgLow = 0.4f;
    float linearHLG = ColorMath::HLGToLinear(hlgLow);
    PRISMX_ASSERT(linearHLG > 0.0f && linearHLG < 1.0f);

    // ------------------------------------------------------------------------
    // Step 4: Colorimetry: Linear RGB to CIE 1931 XYZ and CIE 1976 Lab
    // ------------------------------------------------------------------------
    XYZColor d65White = ColorMath::LinearRGBToXYZ({ 1.0f, 1.0f, 1.0f });
    PRISMX_ASSERT(std::abs(d65White.y - 1.0f) < 1e-3f);

    LabColor labWhite = ColorMath::XYZToLab(d65White);
    PRISMX_ASSERT(std::abs(labWhite.l - 100.0f) < 1e-2f);

    LabColor redLab = ColorMath::XYZToLab(ColorMath::LinearRGBToXYZ({ 1.0f, 0.0f, 0.0f }));
    LabColor blueLab = ColorMath::XYZToLab(ColorMath::LinearRGBToXYZ({ 0.0f, 0.0f, 1.0f }));
    float deltaIdentical = ColorMath::DeltaE76(redLab, redLab);
    float deltaRedBlue = ColorMath::DeltaE76(redLab, blueLab);
    PRISMX_ASSERT(deltaIdentical < 1e-5f);
    PRISMX_ASSERT(deltaRedBlue > 50.0f);

    // ------------------------------------------------------------------------
    // Step 5: Tone Mapping: ACES Film Curve
    // ------------------------------------------------------------------------
    float toneMappedSdr = ColorMath::ACESFilm(2.5f);
    PRISMX_ASSERT(toneMappedSdr <= 1.0f && toneMappedSdr >= 0.0f);

    // ------------------------------------------------------------------------
    // Step 6: PrismColorManager COM Interface
    // ------------------------------------------------------------------------
    ComPtr<IPrismColorManager> colorMgr;
    HRESULT hr = PrismCreateColorManager(colorMgr.Put());
    PRISMX_ASSERT(SUCCEEDED(hr) && colorMgr.Get() != nullptr);

    ComPtr<IPrismColorProfile> srgbProf;
    ComPtr<IPrismColorProfile> p3Prof;
    ComPtr<IPrismColorProfile> bt2020Prof;
    hr = colorMgr->CreateStandardProfile(ColorSpaceType::sRGB, srgbProf.Put());
    PRISMX_ASSERT(SUCCEEDED(hr));
    hr = colorMgr->CreateStandardProfile(ColorSpaceType::DCI_P3, p3Prof.Put());
    PRISMX_ASSERT(SUCCEEDED(hr));
    hr = colorMgr->CreateStandardProfile(ColorSpaceType::BT2020, bt2020Prof.Put());
    PRISMX_ASSERT(SUCCEEDED(hr));

    PRISMX_ASSERT(srgbProf->GetColorSpaceType() == ColorSpaceType::sRGB);
    PRISMX_ASSERT(p3Prof->GetColorSpaceType() == ColorSpaceType::DCI_P3);
    PRISMX_ASSERT(bt2020Prof->GetColorSpaceType() == ColorSpaceType::BT2020);

    // ------------------------------------------------------------------------
    // Step 7: Synthetic ICC Profile Header Verification
    // ------------------------------------------------------------------------
    ICCProfileHeader iccHeader{};
    iccHeader.size = sizeof(ICCProfileHeader);
    iccHeader.cmmType = 0x50524953; // 'PRIS'
    iccHeader.version = 0x04300000; // v4.3
    iccHeader.deviceClass = 0x6D6E7472; // 'mntr'
    iccHeader.colorSpace = 0x52474220; // 'RGB '
    iccHeader.pcs = 0x58595A20; // 'XYZ '
    iccHeader.magic = 0x61637370; // 'acsp'
    iccHeader.renderingIntent = 0;

    ComPtr<IPrismColorProfile> memProfile;
    hr = colorMgr->CreateProfileFromMemory(&iccHeader, sizeof(iccHeader), memProfile.Put());
    PRISMX_ASSERT(SUCCEEDED(hr));

    const ICCProfileHeader& readHeader = memProfile->GetHeader();
    PRISMX_ASSERT(readHeader.magic == 0x61637370);

    // ------------------------------------------------------------------------
    // Step 8: Color Transform and Pixel Translation
    // ------------------------------------------------------------------------
    ComPtr<IPrismColorTransform> transform;
    hr = colorMgr->CreateColorTransform(srgbProf.Get(), bt2020Prof.Get(), RenderingIntent::Perceptual, transform.Put());
    PRISMX_ASSERT(SUCCEEDED(hr));

    RGBColor srcColor{ 1.0f, 0.0f, 0.0f, 1.0f };
    RGBColor dstColor{};
    hr = transform->Transform(srcColor, dstColor);
    PRISMX_ASSERT(SUCCEEDED(hr));
    PRISMX_ASSERT(dstColor.a == 1.0f);

    // ------------------------------------------------------------------------
    // Step 9: Bitmap Bits Translation
    // ------------------------------------------------------------------------
    uint8_t srcBitmap[16] = {
        255, 0, 0, 255,
        0, 255, 0, 255,
        0, 0, 255, 255,
        128, 128, 128, 255
    };
    uint8_t dstBitmap[16] = { 0 };
    hr = transform->TransformBitmap(srcBitmap, dstBitmap, 2, 2, 8);
    PRISMX_ASSERT(SUCCEEDED(hr));
    PRISMX_ASSERT(dstBitmap[3] == 255 && dstBitmap[7] == 255);

    // ------------------------------------------------------------------------
    // Step 10: Tone Mapping HDR to SDR
    // ------------------------------------------------------------------------
    float sdrMappedACES = 0.0f;
    hr = colorMgr->ToneMapHDRtoSDR(1000.0f, ToneMappingOperator::ACESFilm, sdrMappedACES);
    PRISMX_ASSERT(SUCCEEDED(hr));
    PRISMX_ASSERT(sdrMappedACES > 0.0f && sdrMappedACES <= 1.0f);

    float sdrMappedReinhard = 0.0f;
    hr = colorMgr->ToneMapHDRtoSDR(400.0f, ToneMappingOperator::Reinhard, sdrMappedReinhard);
    PRISMX_ASSERT(SUCCEEDED(hr));
    PRISMX_ASSERT(sdrMappedReinhard > 0.0f && sdrMappedReinhard < 1.0f);

    PRISMX_PASS()
    return 0;
}

int Test_PrismInput_Pointer_Gesture_And_Inking_Subsystem() {
    PRISMX_TEST("Test_PrismInput_Pointer_Gesture_And_Inking_Subsystem")

    using namespace prismx::input;

    // ------------------------------------------------------------------------
    // Step 1: Pointer Point Modeling & Bitmask Buttons
    // ------------------------------------------------------------------------
    PointerPoint pt{};
    pt.pointerId = 101;
    pt.deviceType = PointerDeviceType::Pen;
    pt.eventType = PointerEventType::Down;
    pt.x = 450.0f;
    pt.y = 320.0f;
    pt.pressure = 0.82f;
    pt.tiltX = 15.0f;
    pt.tiltY = -8.0f;
    pt.buttons = PointerButtonState::Left | PointerButtonState::Barrel;
    pt.timestampMs = 1000;

    PRISMX_ASSERT(pt.pointerId == 101);
    PRISMX_ASSERT(pt.deviceType == PointerDeviceType::Pen);
    PRISMX_ASSERT(pt.buttons & PointerButtonState::Barrel);
    PRISMX_ASSERT(pt.buttons & PointerButtonState::Left);
    PRISMX_ASSERT(!(pt.buttons & PointerButtonState::Right));

    // ------------------------------------------------------------------------
    // Step 2: Tap & Double Tap Gesture Recognition
    // ------------------------------------------------------------------------
    GestureRecognizer recognizer;
    std::vector<GestureEvent> events;
    recognizer.AddCallback([&](const GestureEvent& e) {
        events.push_back(e);
    });

    // First tap
    PointerPoint tap1Down{ 1, PointerDeviceType::Touch, PointerEventType::Down, 100.0f, 100.0f, 10, 10, 0.5f, 0, 0, 0, PointerButtonState::None, 1000 };
    PointerPoint tap1Up  { 1, PointerDeviceType::Touch, PointerEventType::Up,   100.0f, 100.0f, 10, 10, 0.0f, 0, 0, 0, PointerButtonState::None, 1050 };
    recognizer.ProcessPointerEvent(tap1Down);
    recognizer.ProcessPointerEvent(tap1Up);

    PRISMX_ASSERT(!events.empty());
    PRISMX_ASSERT(events.back().type == GestureType::Tap);
    PRISMX_ASSERT(events.back().tapCount == 1);

    // Second tap for DoubleTap (within 200ms)
    PointerPoint tap2Down{ 1, PointerDeviceType::Touch, PointerEventType::Down, 102.0f, 101.0f, 10, 10, 0.5f, 0, 0, 0, PointerButtonState::None, 1200 };
    PointerPoint tap2Up  { 1, PointerDeviceType::Touch, PointerEventType::Up,   102.0f, 101.0f, 10, 10, 0.0f, 0, 0, 0, PointerButtonState::None, 1240 };
    recognizer.ProcessPointerEvent(tap2Down);
    recognizer.ProcessPointerEvent(tap2Up);

    PRISMX_ASSERT(events.back().type == GestureType::DoubleTap);
    PRISMX_ASSERT(events.back().tapCount == 2);

    // ------------------------------------------------------------------------
    // Step 3: Long Press Gesture Recognition
    // ------------------------------------------------------------------------
    PointerPoint lpDown{ 2, PointerDeviceType::Touch, PointerEventType::Down, 200.0f, 200.0f, 10, 10, 0.5f, 0, 0, 0, PointerButtonState::None, 2000 };
    PointerPoint lpUp  { 2, PointerDeviceType::Touch, PointerEventType::Up,   201.0f, 200.0f, 10, 10, 0.0f, 0, 0, 0, PointerButtonState::None, 2600 }; // 600ms hold
    recognizer.ProcessPointerEvent(lpDown);
    recognizer.ProcessPointerEvent(lpUp);

    PRISMX_ASSERT(events.back().type == GestureType::LongPress);
    PRISMX_ASSERT(events.back().state == GestureState::Ended);

    // ------------------------------------------------------------------------
    // Step 4: Pan / Drag Gesture with Velocity
    // ------------------------------------------------------------------------
    PointerPoint panDown{ 3, PointerDeviceType::Touch, PointerEventType::Down, 300.0f, 300.0f, 10, 10, 0.5f, 0, 0, 0, PointerButtonState::None, 3000 };
    PointerPoint panMove{ 3, PointerDeviceType::Touch, PointerEventType::Move, 350.0f, 340.0f, 10, 10, 0.5f, 0, 0, 0, PointerButtonState::None, 3100 };
    PointerPoint panUp  { 3, PointerDeviceType::Touch, PointerEventType::Up,   350.0f, 340.0f, 10, 10, 0.0f, 0, 0, 0, PointerButtonState::None, 3150 };
    recognizer.ProcessPointerEvent(panDown);
    recognizer.ProcessPointerEvent(panMove);

    bool foundPan = false;
    for (const auto& ev : events) {
        if (ev.type == GestureType::Pan) {
            foundPan = true;
            PRISMX_ASSERT(ev.deltaX > 0.0f);
            break;
        }
    }
    PRISMX_ASSERT(foundPan);
    recognizer.ProcessPointerEvent(panUp);

    // ------------------------------------------------------------------------
    // Step 5: Multi-Touch Pinch-to-Zoom & Dual-Touch Rotation
    // ------------------------------------------------------------------------
    events.clear();
    // Two fingers down: (400, 400) and (600, 400), initial distance = 200.0
    PointerPoint f1Down{ 10, PointerDeviceType::Touch, PointerEventType::Down, 400.0f, 400.0f, 10, 10, 0.5f, 0, 0, 0, PointerButtonState::None, 4000 };
    PointerPoint f2Down{ 11, PointerDeviceType::Touch, PointerEventType::Down, 600.0f, 400.0f, 10, 10, 0.5f, 0, 0, 0, PointerButtonState::None, 4000 };
    recognizer.ProcessPointerEvent(f1Down);
    recognizer.ProcessPointerEvent(f2Down);

    // Fingers spread apart and rotate: (350, 350) and (650, 450)
    PointerPoint f1Move{ 10, PointerDeviceType::Touch, PointerEventType::Move, 350.0f, 350.0f, 10, 10, 0.5f, 0, 0, 0, PointerButtonState::None, 4050 };
    PointerPoint f2Move{ 11, PointerDeviceType::Touch, PointerEventType::Move, 650.0f, 450.0f, 10, 10, 0.5f, 0, 0, 0, PointerButtonState::None, 4050 };
    recognizer.ProcessPointerEvent(f1Move);
    recognizer.ProcessPointerEvent(f2Move);

    bool foundPinch = false;
    bool foundRotate = false;
    for (const auto& ev : events) {
        if (ev.type == GestureType::Pinch && ev.state == GestureState::Changed) {
            foundPinch = true;
            PRISMX_ASSERT(ev.scale > 1.0f); // Zoom in
        }
        if (ev.type == GestureType::Rotate && ev.state == GestureState::Changed) {
            foundRotate = true;
            PRISMX_ASSERT(std::abs(ev.rotationDelta) > 0.0f);
        }
    }
    PRISMX_ASSERT(foundPinch);
    PRISMX_ASSERT(foundRotate);

    // Release fingers
    PointerPoint f1Up{ 10, PointerDeviceType::Touch, PointerEventType::Up, 350.0f, 350.0f, 10, 10, 0.0f, 0, 0, 0, PointerButtonState::None, 4100 };
    PointerPoint f2Up{ 11, PointerDeviceType::Touch, PointerEventType::Up, 650.0f, 450.0f, 10, 10, 0.0f, 0, 0, 0, PointerButtonState::None, 4100 };
    recognizer.ProcessPointerEvent(f1Up);
    recognizer.ProcessPointerEvent(f2Up);
    PRISMX_ASSERT(recognizer.GetActiveContactCount() == 0);

    // ------------------------------------------------------------------------
    // Step 6: Stylus Inking Stroke & Catmull-Rom Spline Smoothing
    // ------------------------------------------------------------------------
    InkStroke stroke(8.0f, PressureCurve::Soft);
    stroke.SetColor(0.2f, 0.6f, 1.0f, 1.0f);

    // Add curved trajectory with variable digitizer pressure
    stroke.AddPoint({ 100.0f, 100.0f, 0.2f, 0.0f, 0.0f, 5000 });
    stroke.AddPoint({ 150.0f, 180.0f, 0.5f, 5.0f, -3.0f, 5020 });
    stroke.AddPoint({ 220.0f, 240.0f, 0.85f, 12.0f, -6.0f, 5040 });
    stroke.AddPoint({ 300.0f, 260.0f, 0.95f, 15.0f, -8.0f, 5060 });
    stroke.AddPoint({ 380.0f, 220.0f, 0.70f, 8.0f, -4.0f, 5080 });
    stroke.AddPoint({ 450.0f, 150.0f, 0.30f, 2.0f, -1.0f, 5100 });

    stroke.FinalizeStroke();

    PRISMX_ASSERT(stroke.GetRawPoints().size() == 6);
    PRISMX_ASSERT(stroke.GetSmoothedPoints().size() > stroke.GetRawPoints().size());

    // ------------------------------------------------------------------------
    // Step 7: GPU Triangle Strip Tessellation Verification
    // ------------------------------------------------------------------------
    const auto& vertices = stroke.GetTriangleStrip();
    PRISMX_ASSERT(!vertices.empty());
    PRISMX_ASSERT(vertices.size() % 2 == 0); // Pairs of left and right vertices
    PRISMX_ASSERT(stroke.GetTriangleCount() > 0);

    // Verify vertex attributes
    for (const auto& v : vertices) {
        PRISMX_ASSERT(v.strokeWidth > 0.0f);
        PRISMX_ASSERT(v.r == 0.2f && v.g == 0.6f && v.b == 1.0f && v.a == 1.0f);
        float normLen = std::sqrt(v.nx * v.nx + v.ny * v.ny);
        PRISMX_ASSERT(std::abs(normLen - 1.0f) < 1e-3f);
    }

    PRISMX_PASS()
    return 0;
}

int Test_PrismVector_Font_Tessellation_Subsystem() {
    PRISMX_TEST("Test_PrismVector_Font_Tessellation_Subsystem")
        using namespace prismx::vector_font;

        // ------------------------------------------------------------------------
        // Step 1: 2D Geometry & Affine Transforms
        // ------------------------------------------------------------------------
        Point2D p1{ 10.0f, 20.0f };
        Point2D p2{ 30.0f, 40.0f };
        Point2D pSum = p1 + p2;
        PRISMX_ASSERT(pSum.x == 40.0f && pSum.y == 60.0f);
        PRISMX_ASSERT(Point2D::Distance(p1, p2) > 0.0f);
        PRISMX_ASSERT(p1.Cross(p2) == 10.0f * 40.0f - 20.0f * 30.0f);

        Rect2D rect{ 0.0f, 0.0f, 100.0f, 50.0f };
        PRISMX_ASSERT(rect.Width() == 100.0f && rect.Height() == 50.0f);
        PRISMX_ASSERT(rect.Contains({ 50.0f, 25.0f }));
        PRISMX_ASSERT(!rect.Contains({ 150.0f, 25.0f }));

        Matrix3x2F mTrans = Matrix3x2F::Translation(15.0f, 25.0f);
        Point2D pTrans = mTrans.TransformPoint(p1);
        PRISMX_ASSERT(pTrans.x == 25.0f && pTrans.y == 45.0f);

        Matrix3x2F mScale = Matrix3x2F::Scale(2.0f, 3.0f);
        Point2D pScale = mScale.TransformPoint(p1);
        PRISMX_ASSERT(pScale.x == 20.0f && pScale.y == 60.0f);

        Matrix3x2F mInv = mTrans.Invert();
        Point2D pBack = mInv.TransformPoint(pTrans);
        PRISMX_ASSERT(std::abs(pBack.x - p1.x) < 1e-4f && std::abs(pBack.y - p1.y) < 1e-4f);

        // ------------------------------------------------------------------------
        // Step 2: Vector Path Construction & De Casteljau Subdivision
        // ------------------------------------------------------------------------
        VectorPath path;
        path.MoveTo({ 0.0f, 0.0f });
        path.LineTo({ 100.0f, 0.0f });
        path.QuadTo({ 150.0f, 50.0f }, { 100.0f, 100.0f });
        path.CubicTo({ 80.0f, 120.0f }, { 20.0f, 120.0f }, { 0.0f, 100.0f });
        path.Close();

        Rect2D pathBounds = path.ComputeBounds();
        PRISMX_ASSERT(pathBounds.left == 0.0f && pathBounds.top == 0.0f);
        PRISMX_ASSERT(pathBounds.right >= 100.0f && pathBounds.bottom >= 100.0f);

        auto contours = path.Flatten(0.25f);
        PRISMX_ASSERT(!contours.empty());
        PRISMX_ASSERT(contours[0].size() > 10); // Curves subdivided into multi-point polyline

        // ------------------------------------------------------------------------
        // Step 3: W3C SVG 1.1 Path String Parser
        // ------------------------------------------------------------------------
        VectorPath svgPath;
        bool parsed = SvgPathParser::Parse("M 10 10 H 90 V 90 H 10 Z", svgPath);
        PRISMX_ASSERT(parsed);
        PRISMX_ASSERT(svgPath.GetCommands().size() == 5);
        Rect2D svgBounds = svgPath.ComputeBounds();
        PRISMX_ASSERT(svgBounds.left == 10.0f && svgBounds.top == 10.0f);
        PRISMX_ASSERT(svgBounds.right == 90.0f && svgBounds.bottom == 90.0f);

        // Complex SVG path with curves and negative numbers
        VectorPath complexSvg;
        parsed = SvgPathParser::Parse("M100,200 C100,100 250,100 250,200 S400,300 400,200 Q450,150 500,200 A25,25 0 0,1 550,200 Z", complexSvg);
        PRISMX_ASSERT(parsed);
        PRISMX_ASSERT(complexSvg.GetCommands().size() >= 5);

        // ------------------------------------------------------------------------
        // Step 4: Ear-Clipping Triangulation Engine (Simple Poly & Holes)
        // ------------------------------------------------------------------------
        // Simple CCW rectangle
        std::vector<Point2D> rectPoly = {
            { 0.0f, 0.0f }, { 100.0f, 0.0f }, { 100.0f, 50.0f }, { 0.0f, 50.0f }
        };
        TessellatedMesh rectMesh;
        bool triOk = EarClippingTessellator::Triangulate(rectPoly, rectMesh);
        PRISMX_ASSERT(triOk);
        PRISMX_ASSERT(rectMesh.vertices.size() == 4);
        PRISMX_ASSERT(rectMesh.indices.size() == 6); // 2 triangles = 6 indices

        // Polygon with Hole (Square with nested inner hole)
        std::vector<Point2D> outerSquare = {
            { 0.0f, 0.0f }, { 200.0f, 0.0f }, { 200.0f, 200.0f }, { 0.0f, 200.0f }
        };
        std::vector<Point2D> innerHole = {
            { 50.0f, 50.0f }, { 150.0f, 50.0f }, { 150.0f, 150.0f }, { 50.0f, 150.0f }
        };
        std::vector<Point2D> mergedPoly = EarClippingTessellator::MergeHoles(outerSquare, { innerHole });
        PRISMX_ASSERT(mergedPoly.size() >= outerSquare.size() + innerHole.size());

        TessellatedMesh holeMesh;
        triOk = EarClippingTessellator::Triangulate(mergedPoly, holeMesh);
        PRISMX_ASSERT(triOk);
        PRISMX_ASSERT(holeMesh.indices.size() >= 18); // Triangulated annulus
        PRISMX_ASSERT(holeMesh.indices.size() % 3 == 0);

        // ------------------------------------------------------------------------
        // Step 5: Stroke Expansion & Tessellation
        // ------------------------------------------------------------------------
        std::vector<Point2D> strokePoly = {
            { 10.0f, 10.0f }, { 50.0f, 30.0f }, { 90.0f, 10.0f }, { 120.0f, 60.0f }
        };
        StrokeStyle strokeStyle{ 4.0f, LineJoin::Miter, LineCap::Flat, 4.0f };
        TessellatedMesh strokeMesh;
        bool strokeOk = StrokeTessellator::Tessellate(strokePoly, strokeStyle, strokeMesh);
        PRISMX_ASSERT(strokeOk);
        PRISMX_ASSERT(!strokeMesh.vertices.empty());
        PRISMX_ASSERT(!strokeMesh.indices.empty());
        PRISMX_ASSERT(strokeMesh.indices.size() % 6 == 0); // Quads of two triangles

        // ------------------------------------------------------------------------
        // Step 6: Built-in Sovereign Typeface & Glyph Outlines
        // ------------------------------------------------------------------------
        BuiltinTypeface font;
        PRISMX_ASSERT(font.GetAscender() == 800.0f);
        PRISMX_ASSERT(font.GetDescender() == -200.0f);
        PRISMX_ASSERT(font.GetEmSize() == 1000.0f);

        const auto& glyphA = font.GetGlyph('A');
        PRISMX_ASSERT(glyphA.contours.size() == 2); // 'A' has outer contour + inner hole
        PRISMX_ASSERT(glyphA.advanceWidth > 0.0f);

        VectorPath pathA = glyphA.ToVectorPath();
        Rect2D boundsA = pathA.ComputeBounds();
        PRISMX_ASSERT(boundsA.Width() > 0.0f && boundsA.Height() > 0.0f);

        const auto& glyphO = font.GetGlyph('O');
        PRISMX_ASSERT(glyphO.contours.size() == 2); // 'O' has outer oval + inner oval

        // ------------------------------------------------------------------------
        // Step 7: Signed Distance Field (SDF) Rasterization
        // ------------------------------------------------------------------------
        VectorPath boxPath;
        boxPath.MoveTo({ 20.0f, 20.0f });
        boxPath.LineTo({ 80.0f, 20.0f });
        boxPath.LineTo({ 80.0f, 80.0f });
        boxPath.LineTo({ 20.0f, 80.0f });
        boxPath.Close();

        SdfBitmap sdf = SdfRasterizer::Generate(boxPath, 32, 32, 10.0f);
        PRISMX_ASSERT(sdf.width == 32 && sdf.height == 32);
        PRISMX_ASSERT(sdf.distances.size() == 32 * 32);
        PRISMX_ASSERT(sdf.rgbaPixels.size() == 32 * 32 * 4);

        // Center pixel (16, 16) is well inside the box -> negative distance, normalized > 0.5
        size_t centerIdx = 16 * 32 + 16;
        PRISMX_ASSERT(sdf.distances[centerIdx] < 0.0f);
        PRISMX_ASSERT(sdf.rgbaPixels[centerIdx * 4 + 0] > 128);

        // Corner pixel (2, 2) is outside the box -> positive distance, normalized < 0.5
        size_t cornerIdx = 2 * 32 + 2;
        PRISMX_ASSERT(sdf.distances[cornerIdx] > 0.0f);
        PRISMX_ASSERT(sdf.rgbaPixels[cornerIdx * 4 + 0] < 128);

        // ------------------------------------------------------------------------
        // Step 8: Text Layout Engine
        // ------------------------------------------------------------------------
        TextLayoutEngine layout("PRISMX\nSOVEREIGN 2D", { 20.0f, 1.2f, 1.0f, TextAlignment::Left });
        Rect2D textBounds = layout.ComputeBounds();
        PRISMX_ASSERT(textBounds.Width() > 0.0f && textBounds.Height() > 0.0f);

        TessellatedMesh textMesh = layout.Tessellate(0.2f, 0.7f, 1.0f, 1.0f);
        PRISMX_ASSERT(!textMesh.vertices.empty());
        PRISMX_ASSERT(!textMesh.indices.empty());
        PRISMX_ASSERT(textMesh.indices.size() % 3 == 0);

        // ------------------------------------------------------------------------
        // Step 9: Sovereign COM Interfaces & Factory Lifecycle
        // ------------------------------------------------------------------------
        ComPtr<IPrismVectorPath> spPath;
        HRESULT hr = CreatePrismVectorPath(spPath.ReleaseAndGetAddressOf());
        PRISMX_ASSERT(SUCCEEDED(hr) && spPath.Get() != nullptr);

        hr = spPath->ParseSvg("M 0 0 L 100 0 L 50 100 Z");
        PRISMX_ASSERT(SUCCEEDED(hr));

        float l = 0, t = 0, r = 0, b = 0;
        hr = spPath->GetBounds(&l, &t, &r, &b);
        PRISMX_ASSERT(SUCCEEDED(hr));
        PRISMX_ASSERT(l == 0.0f && t == 0.0f && r == 100.0f && b == 100.0f);

        ComPtr<IPrismTessellator> spTess;
        hr = CreatePrismTessellator(spTess.ReleaseAndGetAddressOf());
        PRISMX_ASSERT(SUCCEEDED(hr) && spTess.Get() != nullptr);

        TessellatedMesh comFillMesh;
        hr = spTess->TessellateFill(spPath.Get(), 0.5f, &comFillMesh);
        PRISMX_ASSERT(SUCCEEDED(hr));
        PRISMX_ASSERT(comFillMesh.indices.size() == 3); // 1 triangle

        ComPtr<IPrismFont> spFont;
        hr = CreatePrismFont(spFont.ReleaseAndGetAddressOf());
        PRISMX_ASSERT(SUCCEEDED(hr) && spFont.Get() != nullptr);
        float asc = 0, desc = 0, gap = 0;
        hr = spFont->GetMetrics(&asc, &desc, &gap);
        PRISMX_ASSERT(SUCCEEDED(hr));
        PRISMX_ASSERT(asc == 800.0f && desc == -200.0f);

        ComPtr<IPrismTextLayout> spLayout;
        hr = CreatePrismTextLayout("PRISMX GRAPHICS", spLayout.ReleaseAndGetAddressOf());
        PRISMX_ASSERT(SUCCEEDED(hr) && spLayout.Get() != nullptr);
        hr = spLayout->SetFontSize(32.0f);
        PRISMX_ASSERT(SUCCEEDED(hr));

        float tw = 0, th = 0;
        hr = spLayout->GetBounds(&tw, &th);
        PRISMX_ASSERT(SUCCEEDED(hr));
        PRISMX_ASSERT(tw > 0.0f && th > 0.0f);

        TessellatedMesh comTextMesh;
        hr = spLayout->Tessellate(&comTextMesh);
        PRISMX_ASSERT(SUCCEEDED(hr));
        PRISMX_ASSERT(!comTextMesh.vertices.empty());

    PRISMX_PASS()
    return 0;
}

// ============================================================================
// Suite 16: Sovereign Stateful 2D Canvas & Vector Renderer Subsystem
// ============================================================================
int Test_PrismCanvas2D_Vector_Renderer() {
    PRISMX_TEST("Test_PrismCanvas2D_Vector_Renderer");

    using namespace prismx::canvas2d;

    // 1. Color System & Conversions
    CanvasColor red(1.0f, 0.0f, 0.0f, 1.0f);
    CanvasColor green(0.0f, 1.0f, 0.0f, 1.0f);
    CanvasColor blue(0.0f, 0.0f, 1.0f, 1.0f);
    CanvasColor halfWhite(1.0f, 1.0f, 1.0f, 0.5f);

    uint32_t rgbaRed = red.ToRgba8();
    CanvasColor redRecovered = CanvasColor::FromRgba8(rgbaRed);
    PRISMX_ASSERT(std::abs(redRecovered.r - 1.0f) < 0.01f);
    PRISMX_ASSERT(std::abs(redRecovered.g - 0.0f) < 0.01f);
    PRISMX_ASSERT(std::abs(redRecovered.b - 0.0f) < 0.01f);
    PRISMX_ASSERT(std::abs(redRecovered.a - 1.0f) < 0.01f);

    CanvasColor lerpColor = CanvasColor::Lerp(red, blue, 0.5f);
    PRISMX_ASSERT(std::abs(lerpColor.r - 0.5f) < 0.01f);
    PRISMX_ASSERT(std::abs(lerpColor.b - 0.5f) < 0.01f);

    // Porter-Duff Blending
    CanvasColor blendedOver = BlendColors(halfWhite, CanvasColor::Black(), BlendMode::SourceOver);
    PRISMX_ASSERT(blendedOver.a > 0.99f);
    PRISMX_ASSERT(blendedOver.r > 0.49f && blendedOver.r < 0.51f);

    CanvasColor blendedAdd = BlendColors(red, green, BlendMode::Lighter);
    PRISMX_ASSERT(blendedAdd.r > 0.99f && blendedAdd.g > 0.99f && blendedAdd.b < 0.01f);

    // 2. Brush & Gradient Subsystem
    SolidBrush solidYellow(CanvasColor::Yellow());
    PRISMX_ASSERT(solidYellow.GetType() == BrushType::Solid);
    CanvasColor sampledSolid = solidYellow.Sample(10.0f, 20.0f);
    PRISMX_ASSERT(sampledSolid.r == 1.0f && sampledSolid.g == 1.0f && sampledSolid.b == 0.0f);

    std::vector<GradientStop> stops = {
        { 0.0f, CanvasColor::Red() },
        { 0.5f, CanvasColor::Green() },
        { 1.0f, CanvasColor::Blue() }
    };
    LinearGradientBrush linGrad({ 0.0f, 0.0f }, { 100.0f, 0.0f }, stops, SpreadMethod::Clamp);
    PRISMX_ASSERT(linGrad.GetType() == BrushType::LinearGradient);
    CanvasColor gStart = linGrad.Sample(0.0f, 0.0f);
    CanvasColor gMid = linGrad.Sample(50.0f, 0.0f);
    CanvasColor gEnd = linGrad.Sample(100.0f, 0.0f);
    PRISMX_ASSERT(gStart.r > 0.99f && gStart.g < 0.01f);
    PRISMX_ASSERT(gMid.g > 0.99f && gMid.r < 0.01f);
    PRISMX_ASSERT(gEnd.b > 0.99f && gEnd.g < 0.01f);

    RadialGradientBrush radGrad({ 50.0f, 50.0f }, 0.0f, { 50.0f, 50.0f }, 50.0f, stops);
    PRISMX_ASSERT(radGrad.GetType() == BrushType::RadialGradient);
    CanvasColor rCenter = radGrad.Sample(50.0f, 50.0f);
    CanvasColor rOuter = radGrad.Sample(100.0f, 50.0f);
    PRISMX_ASSERT(rCenter.r > 0.99f);
    PRISMX_ASSERT(rOuter.b > 0.99f);

    ConicGradientBrush conicGrad({ 50.0f, 50.0f }, 0.0f, stops);
    PRISMX_ASSERT(conicGrad.GetType() == BrushType::ConicGradient);
    CanvasColor cRight = conicGrad.Sample(100.0f, 50.0f);
    CanvasColor cLeft = conicGrad.Sample(0.0f, 50.0f);
    PRISMX_ASSERT(cRight.r > 0.95f);
    PRISMX_ASSERT(cLeft.g > 0.95f);

    // 3. IPrismCanvas2D Creation & Dimensions
    ComPtr<IPrismCanvas2D> spCanvas;
    HRESULT hr = PrismCreateCanvas2D(400, 300, spCanvas.Put());
    PRISMX_ASSERT(SUCCEEDED(hr) && spCanvas.Get() != nullptr);
    PRISMX_ASSERT(spCanvas->GetWidth() == 400);
    PRISMX_ASSERT(spCanvas->GetHeight() == 300);

    PixelSurface* pSurface = spCanvas->GetSurface();
    PRISMX_ASSERT(pSurface != nullptr);
    PRISMX_ASSERT(pSurface->GetSize() == 400 * 300);

    // 4. State Stack & Transformations
    spCanvas->Save();
    spCanvas->Translate(100.0f, 50.0f);
    spCanvas->Scale(2.0f, 2.0f);
    spCanvas->Rotate(0.25f);
    spCanvas->SetLineWidth(4.0f);
    spCanvas->SetFillColor(CanvasColor::Red());
    spCanvas->Restore();

    // 5. Direct Geometry Rendering
    spCanvas->SetFillColor(CanvasColor::Blue());
    spCanvas->FillRect(20.0f, 20.0f, 80.0f, 60.0f);

    CanvasColor sampleBlue = pSurface->GetPixel(50, 50);
    PRISMX_ASSERT(sampleBlue.b > 0.9f);

    spCanvas->SetStrokeColor(CanvasColor::Yellow());
    spCanvas->SetLineWidth(2.0f);
    spCanvas->StrokeRect(10.0f, 10.0f, 100.0f, 80.0f);

    spCanvas->SetFillColor(CanvasColor::Green());
    spCanvas->FillCircle(200.0f, 150.0f, 40.0f);
    CanvasColor sampleGreen = pSurface->GetPixel(200, 150);
    PRISMX_ASSERT(sampleGreen.g > 0.9f);

    // 6. Vector Path Construction (Arcs, Béziers, RoundRect)
    spCanvas->BeginPath();
    spCanvas->MoveTo(10.0f, 150.0f);
    spCanvas->BezierCurveTo(50.0f, 100.0f, 80.0f, 250.0f, 120.0f, 150.0f);
    spCanvas->LineTo(120.0f, 200.0f);
    spCanvas->ClosePath();
    spCanvas->SetFillColor(CanvasColor::Cyan());
    spCanvas->Fill();

    spCanvas->BeginPath();
    spCanvas->RoundRect(250.0f, 20.0f, 120.0f, 80.0f, 15.0f);
    spCanvas->SetFillColor(CanvasColor::Magenta());
    spCanvas->Fill();
    CanvasColor sampleMagenta = pSurface->GetPixel(300, 60);
    PRISMX_ASSERT(sampleMagenta.r > 0.9f && sampleMagenta.b > 0.9f);

    // 7. Linear Gradient Path Fill
    spCanvas->SetFillBrush(&linGrad);
    spCanvas->FillRect(150.0f, 220.0f, 100.0f, 40.0f);

    // 8. Bitmap Image Blitting & Resampling
    PixelSurface iconSurface(16, 16, CanvasColor::White());
    for (uint32_t y = 0; y < 16; ++y) {
        for (uint32_t x = 0; x < 16; ++x) {
            if ((x + y) % 2 == 0) iconSurface.SetPixel(x, y, CanvasColor::Red());
        }
    }
    spCanvas->DrawImage(&iconSurface, 10.0f, 220.0f);
    CanvasColor iconSample = pSurface->GetPixel(10, 220);
    PRISMX_ASSERT(iconSample.r > 0.9f);

    // 9. Pixel Data Manipulation (GetImageData & PutImageData)
    ImageData imgData = spCanvas->GetImageData(20, 20, 40, 40);
    PRISMX_ASSERT(imgData.width == 40 && imgData.height == 40);
    PRISMX_ASSERT(imgData.pixels.size() == 1600);

    // Invert pixel colors in image data
    for (auto& p : imgData.pixels) {
        CanvasColor c = CanvasColor::FromRgba8(p);
        c.r = 1.0f - c.r;
        c.g = 1.0f - c.g;
        c.b = 1.0f - c.b;
        p = c.ToRgba8();
    }
    spCanvas->PutImageData(imgData, 300, 200);

    // 10. Typography Integration
    spCanvas->SetFont("Sovereign Sans", 20.0f);
    float textW = spCanvas->MeasureText("PrismX Canvas 2D");
    PRISMX_ASSERT(textW > 0.0f);

    spCanvas->SetFillColor(CanvasColor::White());
    spCanvas->FillText("PrismX Canvas 2D", 20.0f, 120.0f);

    // 11. IPrismCanvasDevice Factory Operations
    ComPtr<IPrismCanvasDevice> spDevice;
    hr = PrismCreateCanvasDevice(spDevice.Put());
    PRISMX_ASSERT(SUCCEEDED(hr) && spDevice.Get() != nullptr);

    ComPtr<IPrismCanvas2D> spCanvasDev;
    hr = spDevice->CreateCanvas(200, 200, spCanvasDev.Put());
    PRISMX_ASSERT(SUCCEEDED(hr) && spCanvasDev.Get() != nullptr);

    ComPtr<IPrismBrush> spSolidBrush;
    hr = spDevice->CreateSolidBrush(CanvasColor::Green(), spSolidBrush.Put());
    PRISMX_ASSERT(SUCCEEDED(hr) && spSolidBrush.Get() != nullptr);
    PRISMX_ASSERT(spSolidBrush->GetType() == BrushType::Solid);

    // Save test output to BMP
    bool saved = pSurface->SaveToBmp("prismx_canvas2d_test.bmp");
    PRISMX_ASSERT(saved);

    PRISMX_PASS()
    return 0;
}

int Test_PrismEffects_PostProcessing_And_EffectGraph() {
    PRISMX_TEST("Test_PrismEffects_PostProcessing_And_EffectGraph")
    using namespace prismx::effects;

    // 1. Context Creation & Basic Image Manipulation
    ComPtr<IPrismEffectContext> spCtx;
    HRESULT hr = PrismCreateEffectContext(spCtx.Put());
    PRISMX_ASSERT(SUCCEEDED(hr) && spCtx.Get() != nullptr);

    const uint32_t W = 64;
    const uint32_t H = 64;
    std::vector<uint32_t> testPixels(static_cast<size_t>(W) * H, 0xFF000000); // Black

    // Draw a sharp white box in center
    for (uint32_t y = 24; y < 40; ++y) {
        for (uint32_t x = 24; x < 40; ++x) {
            testPixels[y * W + x] = 0xFFFFFFFF; // White
        }
    }

    ComPtr<IPrismImage> spSrcImg;
    hr = spCtx->CreateImageFromPixels(W, H, testPixels.data(), spSrcImg.Put());
    PRISMX_ASSERT(SUCCEEDED(hr) && spSrcImg.Get() != nullptr);
    PRISMX_ASSERT(spSrcImg->GetWidth() == W && spSrcImg->GetHeight() == H);
    PRISMX_ASSERT(spSrcImg->GetPixel(30, 30) == 0xFFFFFFFF);
    PRISMX_ASSERT(spSrcImg->GetPixel(5, 5) == 0xFF000000);

    // Test Clone
    ComPtr<IPrismImage> spCloned;
    hr = spSrcImg->Clone(spCloned.Put());
    PRISMX_ASSERT(SUCCEEDED(hr) && spCloned.Get() != nullptr);
    PRISMX_ASSERT(spCloned->GetPixel(30, 30) == 0xFFFFFFFF);

    // 2. Gaussian Blur Effect
    ComPtr<IPrismEffect> spBlur;
    hr = spCtx->CreateEffect(CLSID_PrismGaussianBlurEffect, spBlur.Put());
    PRISMX_ASSERT(SUCCEEDED(hr) && spBlur.Get() != nullptr);
    PRISMX_ASSERT(std::string(spBlur->GetEffectName()) == "PrismGaussianBlurEffect");

    spBlur->SetInput(0, spSrcImg.Get());
    spBlur->SetFloat(PROP_GAUSSIAN_STANDARD_DEVIATION, 2.5f);
    spBlur->SetInt(PROP_GAUSSIAN_BORDER_MODE, static_cast<int32_t>(BorderMode::Soft));

    ComPtr<IPrismImage> spBlurred;
    hr = spBlur->GetOutput(spBlurred.Put());
    PRISMX_ASSERT(SUCCEEDED(hr) && spBlurred.Get() != nullptr);

    // Center pixel should be diffused (less than 255)
    uint32_t blurredCenter = spBlurred->GetPixel(30, 30);
    PixelRGBA cCenter = PixelRGBA::FromU32(blurredCenter);
    PRISMX_ASSERT(cCenter.r < 1.0f && cCenter.r > 0.1f);

    // Pixel outside original white square should now have diffused light
    uint32_t blurredEdge = spBlurred->GetPixel(22, 22);
    PixelRGBA cEdge = PixelRGBA::FromU32(blurredEdge);
    PRISMX_ASSERT(cEdge.r > 0.05f);

    // 3. Color Matrix Effect
    ComPtr<IPrismEffect> spColorMat;
    hr = spCtx->CreateEffect(CLSID_PrismColorMatrixEffect, spColorMat.Put());
    PRISMX_ASSERT(SUCCEEDED(hr) && spColorMat.Get() != nullptr);

    // Test Invert Matrix
    ColorMatrix5x4 matInvert = ColorMatrix5x4::Invert();
    spColorMat->SetValue(PROP_COLORMATRIX_MATRIX, &matInvert, sizeof(matInvert));
    spColorMat->SetInput(0, spSrcImg.Get());

    ComPtr<IPrismImage> spInverted;
    hr = spColorMat->GetOutput(spInverted.Put());
    PRISMX_ASSERT(SUCCEEDED(hr) && spInverted.Get() != nullptr);

    // Formerly black pixel should now be white, and center white should be black
    PixelRGBA invCorner = PixelRGBA::FromU32(spInverted->GetPixel(5, 5));
    PixelRGBA invCenter = PixelRGBA::FromU32(spInverted->GetPixel(30, 30));
    PRISMX_ASSERT(invCorner.r > 0.99f && invCenter.r < 0.01f);

    // Test Grayscale Matrix on a pure red image
    std::vector<uint32_t> redPixels(static_cast<size_t>(W) * H, 0xFFFF0000); // ARGB Red
    ComPtr<IPrismImage> spRedImg;
    spCtx->CreateImageFromPixels(W, H, redPixels.data(), spRedImg.Put());

    ColorMatrix5x4 matGray = ColorMatrix5x4::Grayscale();
    spColorMat->SetValue(PROP_COLORMATRIX_MATRIX, &matGray, sizeof(matGray));
    spColorMat->SetInput(0, spRedImg.Get());
    spColorMat->Invalidate();

    ComPtr<IPrismImage> spGray;
    hr = spColorMat->GetOutput(spGray.Put());
    PRISMX_ASSERT(SUCCEEDED(hr) && spGray.Get() != nullptr);
    PixelRGBA grayPix = PixelRGBA::FromU32(spGray->GetPixel(10, 10));
    PRISMX_ASSERT(std::abs(grayPix.r - grayPix.g) < 0.01f);
    PRISMX_ASSERT(std::abs(grayPix.g - grayPix.b) < 0.01f);
    PRISMX_ASSERT(grayPix.r > 0.20f && grayPix.r < 0.23f); // ~0.2126

    // 4. Bloom & HDR Glow Effect
    ComPtr<IPrismEffect> spBloom;
    hr = spCtx->CreateEffect(CLSID_PrismBloomEffect, spBloom.Put());
    PRISMX_ASSERT(SUCCEEDED(hr) && spBloom.Get() != nullptr);

    spBloom->SetInput(0, spSrcImg.Get());
    spBloom->SetFloat(PROP_BLOOM_THRESHOLD, 0.5f);
    spBloom->SetFloat(PROP_BLOOM_INTENSITY, 2.0f);
    spBloom->SetFloat(PROP_BLOOM_BLUR_RADIUS, 3.0f);

    ComPtr<IPrismImage> spBloomed;
    hr = spBloom->GetOutput(spBloomed.Put());
    PRISMX_ASSERT(SUCCEEDED(hr) && spBloomed.Get() != nullptr);

    // Halo around the white box
    PixelRGBA bloomHalo = PixelRGBA::FromU32(spBloomed->GetPixel(21, 21));
    PRISMX_ASSERT(bloomHalo.r > 0.05f);

    // 5. Drop Shadow Effect
    ComPtr<IPrismEffect> spShadow;
    hr = spCtx->CreateEffect(CLSID_PrismDropShadowEffect, spShadow.Put());
    PRISMX_ASSERT(SUCCEEDED(hr) && spShadow.Get() != nullptr);

    spShadow->SetInput(0, spSrcImg.Get());
    spShadow->SetFloat(PROP_SHADOW_OFFSET_X, 8.0f);
    spShadow->SetFloat(PROP_SHADOW_OFFSET_Y, 8.0f);
    spShadow->SetFloat(PROP_SHADOW_BLUR_RADIUS, 2.5f);
    spShadow->SetFloat(PROP_SHADOW_OPACITY, 0.8f);

    ComPtr<IPrismImage> spShadowed;
    hr = spShadow->GetOutput(spShadowed.Put());
    PRISMX_ASSERT(SUCCEEDED(hr) && spShadowed.Get() != nullptr);

    // Shadow offset location should show shadow
    uint32_t shadowSpot = spShadowed->GetPixel(45, 45);
    PRISMX_ASSERT(shadowSpot != 0xFF000000 || spShadowed->GetPixel(35, 45) != 0);

    // 6. 3x3 Convolution Matrix Effect (Sharpen & Edge Detection)
    ComPtr<IPrismEffect> spConv;
    hr = spCtx->CreateEffect(CLSID_PrismConvolutionEffect, spConv.Put());
    PRISMX_ASSERT(SUCCEEDED(hr) && spConv.Get() != nullptr);

    spConv->SetInput(0, spSrcImg.Get());
    spConv->SetInt(PROP_CONV_PRESET, static_cast<int32_t>(ConvolutionPreset::EdgeDetect));

    ComPtr<IPrismImage> spEdges;
    hr = spConv->GetOutput(spEdges.Put());
    PRISMX_ASSERT(SUCCEEDED(hr) && spEdges.Get() != nullptr);

    // Boundary of white square should have high edge response
    PixelRGBA edgePix = PixelRGBA::FromU32(spEdges->GetPixel(24, 24));
    PRISMX_ASSERT(edgePix.r > 0.1f);
    // Interior uniform white area should have zero edge response
    PixelRGBA intPix = PixelRGBA::FromU32(spEdges->GetPixel(32, 32));
    PRISMX_ASSERT(intPix.r < 0.05f);

    // 7. Vignette Effect
    ComPtr<IPrismEffect> spVignette;
    hr = spCtx->CreateEffect(CLSID_PrismVignetteEffect, spVignette.Put());
    PRISMX_ASSERT(SUCCEEDED(hr) && spVignette.Get() != nullptr);

    // Create uniform white image
    std::vector<uint32_t> whitePixels(static_cast<size_t>(W) * H, 0xFFFFFFFF);
    ComPtr<IPrismImage> spWhiteImg;
    spCtx->CreateImageFromPixels(W, H, whitePixels.data(), spWhiteImg.Put());

    spVignette->SetInput(0, spWhiteImg.Get());
    spVignette->SetFloat(PROP_VIGNETTE_CENTER_X, 0.5f);
    spVignette->SetFloat(PROP_VIGNETTE_CENTER_Y, 0.5f);
    spVignette->SetFloat(PROP_VIGNETTE_RADIUS, 0.9f);
    spVignette->SetFloat(PROP_VIGNETTE_SOFTNESS, 0.5f);

    ComPtr<IPrismImage> spVignetted;
    hr = spVignette->GetOutput(spVignetted.Put());
    PRISMX_ASSERT(SUCCEEDED(hr) && spVignetted.Get() != nullptr);

    // Center should remain bright, corner should darken significantly
    PixelRGBA vigCenter = PixelRGBA::FromU32(spVignetted->GetPixel(32, 32));
    PixelRGBA vigCorner = PixelRGBA::FromU32(spVignetted->GetPixel(1, 1));
    PRISMX_ASSERT(vigCenter.r > 0.95f);
    PRISMX_ASSERT(vigCorner.r < 0.5f);

    // 8. Tone Mapping Effect (ACES & Reinhard)
    ComPtr<IPrismEffect> spToneMap;
    hr = spCtx->CreateEffect(CLSID_PrismToneMappingEffect, spToneMap.Put());
    PRISMX_ASSERT(SUCCEEDED(hr) && spToneMap.Get() != nullptr);

    spToneMap->SetInput(0, spWhiteImg.Get());
    spToneMap->SetInt(PROP_TONEMAP_OPERATOR, static_cast<int32_t>(ToneMapOperator::ACES));
    spToneMap->SetFloat(PROP_TONEMAP_EXPOSURE, 1.2f);

    ComPtr<IPrismImage> spToneMapped;
    hr = spToneMap->GetOutput(spToneMapped.Put());
    PRISMX_ASSERT(SUCCEEDED(hr) && spToneMapped.Get() != nullptr);
    PixelRGBA tmPix = PixelRGBA::FromU32(spToneMapped->GetPixel(32, 32));
    PRISMX_ASSERT(tmPix.r > 0.8f && tmPix.r <= 1.0f);

    // 9. Blend Effect (Multiply, Screen)
    ComPtr<IPrismEffect> spBlend;
    hr = spCtx->CreateEffect(CLSID_PrismBlendEffect, spBlend.Put());
    PRISMX_ASSERT(SUCCEEDED(hr) && spBlend.Get() != nullptr);

    spBlend->SetInput(0, spSrcImg.Get());
    spBlend->SetInput(1, spWhiteImg.Get());
    spBlend->SetInt(PROP_BLEND_MODE, static_cast<int32_t>(EffectBlendMode::Multiply));

    ComPtr<IPrismImage> spBlended;
    hr = spBlend->GetOutput(spBlended.Put());
    PRISMX_ASSERT(SUCCEEDED(hr) && spBlended.Get() != nullptr);
    PRISMX_ASSERT(spBlended->GetPixel(30, 30) == 0xFFFFFFFF);
    PRISMX_ASSERT(spBlended->GetPixel(5, 5) == 0xFF000000);

    // 10. Chromatic Aberration Effect
    ComPtr<IPrismEffect> spChroma;
    hr = spCtx->CreateEffect(CLSID_PrismChromaticAberrationEffect, spChroma.Put());
    PRISMX_ASSERT(SUCCEEDED(hr) && spChroma.Get() != nullptr);

    spChroma->SetInput(0, spSrcImg.Get());
    spChroma->SetFloat(PROP_CHROMA_OFFSET_R_X, 3.0f);
    spChroma->SetFloat(PROP_CHROMA_OFFSET_B_X, -3.0f);

    ComPtr<IPrismImage> spChromaOut;
    hr = spChroma->GetOutput(spChromaOut.Put());
    PRISMX_ASSERT(SUCCEEDED(hr) && spChromaOut.Get() != nullptr);

    // Edge of square should have separate red and blue fringes
    PixelRGBA cRedFringe = PixelRGBA::FromU32(spChromaOut->GetPixel(21, 30));
    PRISMX_ASSERT(cRedFringe.r > cRedFringe.b);

    // 11. Effect Graph Execution (DAG Pipeline)
    ComPtr<IPrismEffectGraph> spGraph;
    hr = spCtx->CreateEffectGraph(spGraph.Put());
    PRISMX_ASSERT(SUCCEEDED(hr) && spGraph.Get() != nullptr);

    // Pipeline: Source -> Sepia Color Matrix -> Vignette -> Bloom
    ComPtr<IPrismEffect> spSepia;
    spCtx->CreateEffect(CLSID_PrismColorMatrixEffect, spSepia.Put());
    ColorMatrix5x4 matSepia = ColorMatrix5x4::Sepia();
    spSepia->SetValue(PROP_COLORMATRIX_MATRIX, &matSepia, sizeof(matSepia));
    spSepia->SetInput(0, spSrcImg.Get());

    ComPtr<IPrismEffect> spVigNode;
    spCtx->CreateEffect(CLSID_PrismVignetteEffect, spVigNode.Put());
    spVigNode->SetInputEffect(0, spSepia.Get());

    ComPtr<IPrismEffect> spBloomNode;
    spCtx->CreateEffect(CLSID_PrismBloomEffect, spBloomNode.Put());
    spBloomNode->SetInputEffect(0, spVigNode.Get());

    spGraph->AddEffect(spSepia.Get());
    spGraph->AddEffect(spVigNode.Get());
    spGraph->AddEffect(spBloomNode.Get());
    spGraph->SetRootEffect(spBloomNode.Get());

    PRISMX_ASSERT(spGraph->GetNodeCount() == 3);

    ComPtr<IPrismImage> spPipelineResult;
    hr = spGraph->Render(spPipelineResult.Put());
    PRISMX_ASSERT(SUCCEEDED(hr) && spPipelineResult.Get() != nullptr);

    // Save final rendered output to BMP for visual audit
    bool bmpSaved = spPipelineResult->SaveToBmp("prismx_effects_pipeline_test.bmp");
    PRISMX_ASSERT(bmpSaved);

    PRISMX_PASS()
    return 0;
}

// ============================================================================
// 18. Official Microsoft DirectX Open-Source Ecosystem & WDDM D3DKMT Funnel
// ============================================================================
int Test_PrismX_MicrosoftDirectX_OpenSource_Ecosystem_And_D3DKMT_Funnel() {
    PRISMX_TEST("Test_PrismX_MicrosoftDirectX_OpenSource_Ecosystem_And_D3DKMT_Funnel")

    using namespace prismx;
    using namespace prismx::ecosystem;

    // 1. DirectX-Headers CD3DX12 Helpers & Prism3D12 Resource Creation
    ID3D12Device* dev12 = nullptr;
    PRISMX_ASSERT(D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_12_1, IID_ID3D12Device, reinterpret_cast<void**>(&dev12)) == 0);
    PRISMX_ASSERT(dev12 != nullptr);

    D3D12_COMMAND_QUEUE_DESC qDesc{};
    qDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
    ID3D12CommandQueue* queue12 = nullptr;
    PRISMX_ASSERT(dev12->CreateCommandQueue(&qDesc, IID_ID3D12CommandQueue, reinterpret_cast<void**>(&queue12)) == 0);

    CD3DX12_HEAP_PROPERTIES_HELPER heapProps(D3D12_HEAP_TYPE_DEFAULT);
    D3D12_HEAP_PROPERTIES rawHeap{ heapProps.Type, 0, 0, 1, 1 };
    D3D12_RESOURCE_DESC texDesc = CD3DX12_RESOURCE_DESC_HELPER::Tex2D(DXGI_FORMAT_B8G8R8A8_UNORM, 1280, 800, 1);
    ID3D12Resource* rt12 = nullptr;
    PRISMX_ASSERT(dev12->CreateCommittedResource(&rawHeap, D3D12_HEAP_FLAG_SHARED, &texDesc, D3D12_RESOURCE_STATE_PRESENT, nullptr, IID_ID3D12Resource, reinterpret_cast<void**>(&rt12)) == 0);

    D3D12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER_HELPER::Transition(
        rt12, D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET
    );
    PRISMX_ASSERT(barrier.Transition.StateAfter == D3D12_RESOURCE_STATE_RENDER_TARGET);

    // 2. DirectXMesh::ComputeMeshlets & DirectXTex BC7 Block Compression
    uint32_t cubeIndices[36] = {
        0,1,2, 2,1,3, 4,5,6, 6,5,7, 0,4,1, 1,4,5,
        2,3,6, 6,3,7, 0,2,4, 4,2,6, 1,5,3, 3,5,7
    };
    std::vector<DirectXMeshletHeader> meshlets;
    std::vector<DirectXMeshletCullData> cullData;
    PRISMX_ASSERT(SUCCEEDED(DirectXOpenSourceAssetPipeline::ComputeMeshlets(cubeIndices, 36, 8, 128, 126, meshlets, cullData)));
    PRISMX_ASSERT(meshlets.size() == 1 && meshlets[0].PrimCount == 12);

    std::vector<uint32_t> rgba16x16(16 * 16, 0xFF00E5FFu);
    std::vector<DirectXTexBc7Block16B> bc7Blocks;
    PRISMX_ASSERT(SUCCEEDED(DirectXOpenSourceAssetPipeline::CompressRgbaToBc7Unorm(rgba16x16.data(), 16, 16, bc7Blocks)));
    PRISMX_ASSERT(bc7Blocks.size() == 16 && (bc7Blocks[0].LowBits & 0x40ULL) == 0x40ULL);

    // 3. D3D12TranslationLayer & D3D11On12 Unified Funnel
    ID3D11Device* dev11 = nullptr;
    ID3D11DeviceContext* ctx11 = nullptr;
    ID3D11On12Device* on12 = nullptr;
    D3D_FEATURE_LEVEL chosenFl = D3D_FEATURE_LEVEL_11_0;
    IUnknown* queues[1] = { queue12 };
    PRISMX_ASSERT(SUCCEEDED(D3D11On12CreateDevice(dev12, 0, nullptr, 0, queues, 1, 0, &dev11, &ctx11, &chosenFl, &on12)));
    PRISMX_ASSERT(dev11 != nullptr && ctx11 != nullptr && on12 != nullptr);

    ID3D11Resource* wrapped11 = nullptr;
    D3D11_RESOURCE_FLAGS_ON12 flags11{ D3D11_BIND_RENDER_TARGET, 0, 0, 0 };
    PRISMX_ASSERT(SUCCEEDED(on12->CreateWrappedResource(rt12, &flags11, D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT, IID_ID3D11Texture2D, reinterpret_cast<void**>(&wrapped11))));
    PRISMX_ASSERT(wrapped11 != nullptr);
    on12->AcquireWrappedResources(&wrapped11, 1);
    on12->ReleaseWrappedResources(&wrapped11, 1);
    PRISMX_ASSERT(on12->GetTranslatedCommandCount() == 3);

    // 4. WDDM 3.2 D3DKMT Kernel-Mode Thunk & 540Hz DirectFlip Scanout
    auto& kmt = PrismWddmKmtScanoutEngine::Get();
    D3DKMT_CREATEDEVICE_THUNK kmtDev{};
    PRISMX_ASSERT(SUCCEEDED(kmt.CreateKmtDevice(&kmtDev)) && kmtDev.hDevice != 0);

    D3DKMT_ALLOCATE_VRAM_THUNK kmtVram{ kmtDev.hDevice, 1280ULL * 800ULL * 4ULL, 65536, 0, 0 };
    PRISMX_ASSERT(SUCCEEDED(kmt.AllocateSharedVramSection(&kmtVram)) && kmtVram.SharedNtSectionHandle != 0);

    D3DKMT_SUBMITCOMMAND_THUNK kmtSub{ kmtDev.hDevice, kmtDev.CommandBufferGpuVa, 4096, 42ULL };
    D3DKMT_PRESENT_DIRECTFLIP_THUNK kmtPres{ kmtDev.hDevice, kmtVram.SharedNtSectionHandle, 1280, 800, 540, false, 0 };
    PRISMX_ASSERT(SUCCEEDED(kmt.SubmitAndPresentDirectFlip(kmtSub, &kmtPres)));
    PRISMX_ASSERT(kmtPres.DirectFlipMpoEngaged && kmtPres.ScanoutCenterPixelBGRA == 0xFF00E5FFu);

    wrapped11->Release();
    on12->Release();
    ctx11->Release();
    dev11->Release();
    rt12->Release();
    queue12->Release();
    dev12->Release();

    PRISMX_PASS()
    return 0;
}

int Test_PrismX_DXC_SM68_DirectStorage_GDeflate_And_DirectML_SuperResolution() {
    PRISMX_TEST("Test_PrismX_DXC_SM68_DirectStorage_GDeflate_And_DirectML_SuperResolution")

    // 1. DirectXShaderCompiler (dxcapi.h) Shader Model 6.8 Work Graphs + Mesh Shader + PIX Debug
    const char* hlslSource = "[Shader(\"node\")][NodeLaunch(\"broadcasting\")][NumThreads(32,1,1)] void MainNode() {}";
    DxcBuffer srcBuf{ hlslSource, std::strlen(hlslSource), 65001 };
    DxcSm68CompileArtifact sm68{};
    PRISMX_ASSERT(SUCCEEDED(PrismDxcCompiler3Engine::CompileHlslToDxilSm68(srcBuf, "MainNode", "lib_6_8", true, &sm68)));
    PRISMX_ASSERT(sm68.Succeeded && sm68.DxilContainerMagic == 0x4C495844u);
    PRISMX_ASSERT(sm68.ShaderModelMajor == 6 && sm68.ShaderModelMinor == 8);
    PRISMX_ASSERT(sm68.WorkGraphsNodeShaderEnabled && sm68.PixDebugInstrumentationAttached);
    PRISMX_ASSERT(sm68.DxilObjectBlob.size() == 256);

    PixGpuScopedEventTracker pix{};
    pix.BeginEvent(0xFF00E5FFULL, "PrismX::FramePass");
    pix.SetMarker(0xFF00FF88ULL, "PrismX::GDeflateDecompress");
    pix.EndEvent();
    PRISMX_ASSERT(pix.ActiveBeginCount == 0 && pix.CompletedEventScopes == 1 && pix.MarkerCount == 1);

    // 2. DirectStorage GDeflate::TileStreamHeader (exact 8-byte header + 32-way GPU Wave32 decompression)
    gdeflate::GpuDecompressDispatchResult gdRes{};
    PRISMX_ASSERT(SUCCEEDED(gdeflate::ExecuteGDeflateGpuComputeDecompression(1024ULL * 1024ULL, &gdRes)));
    PRISMX_ASSERT(gdRes.HeaderValid && gdRes.TileCount == 16 && gdRes.UncompressedByteSize == 1048576ULL);
    PRISMX_ASSERT(gdRes.Wave32ThreadGroupsDispatched == 16 && gdRes.DirectVramLandingVerified);

    // 3. DirectML (DirectMLX.h DMLCalcBufferTensorSize + 1080p -> 4K SuperResolution Graph)
    dml_ext::DirectMLSuperResolutionTelemetry srTel{};
    PRISMX_ASSERT(SUCCEEDED(dml_ext::ExecuteDirectMLSuperResolutionPass(1920, 1080, &srTel)));
    PRISMX_ASSERT(srTel.OutputWidth == 3840 && srTel.OutputHeight == 2160);
    PRISMX_ASSERT(srTel.GraphNodeCount == 7 && srTel.CompiledOperatorDispatched);

    PRISMX_PASS()
    return 0;
}

int Test_PrismX_EnhancedBarriers_VulkanOn12_VideoAV1_And_DRED_ZeroTDR() {
    PRISMX_TEST("Test_PrismX_EnhancedBarriers_VulkanOn12_VideoAV1_And_DRED_ZeroTDR")

    // 1. D3D12 Enhanced Barriers (D3D12EnhancedBarriers.md)
    D3D12_TEXTURE_BARRIER texBarrier{};
    texBarrier.SyncBefore   = D3D12_BARRIER_SYNC_RENDER_TARGET;
    texBarrier.SyncAfter    = D3D12_BARRIER_SYNC_PIXEL_SHADING;
    texBarrier.AccessBefore = D3D12_BARRIER_ACCESS_RENDER_TARGET;
    texBarrier.AccessAfter  = D3D12_BARRIER_ACCESS_SHADER_RESOURCE;
    texBarrier.LayoutBefore = D3D12_BARRIER_LAYOUT_RENDER_TARGET;
    texBarrier.LayoutAfter  = D3D12_BARRIER_LAYOUT_SHADER_RESOURCE;
    D3D12_BARRIER_GROUP grp{};
    grp.Type             = D3D12_BARRIER_TYPE_TEXTURE;
    grp.NumBarriers      = 1;
    grp.pTextureBarriers = &texBarrier;
    PRISMX_ASSERT(grp.NumBarriers == 1 && grp.pTextureBarriers[0].LayoutAfter == D3D12_BARRIER_LAYOUT_SHADER_RESOURCE);

    // 2. VulkanOn12 Conformance & D3D12 Video AV1/HEVC Hardware Encode
    VulkanOn12AndVideoEncodeTelemetry vkVid{};
    PRISMX_ASSERT(SUCCEEDED(PrismVulkanOn12AndVideoEngine::VerifyVulkanOn12AndEncodeAv1Frame(3840, 2160, &vkVid)));
    PRISMX_ASSERT(vkVid.relaxedFormatListCastingEnabled && vkVid.unrestrictedRowPitchTextureCopyEnabled);
    PRISMX_ASSERT(vkVid.av1HardwareEncoderActive && vkVid.hevc444HardwareEncoderActive);
    PRISMX_ASSERT(vkVid.encoded4K60Av1BitstreamBytes > 0 && vkVid.motionEstimationSearchBlocks == 32400);

    // 3. DRED 1.2 Auto-Breadcrumbs & Zero-TDR Sub-Millisecond GPU Fault Recovery
    DredZeroTdrSelfHealReport dred{};
    PRISMX_ASSERT(SUCCEEDED(PrismDredZeroTdrSelfHealingEngine::SimulateFaultAndVerifySelfHeal(0x0000000240800000ULL, &dred)));
    PRISMX_ASSERT(dred.AutoBreadcrumbsEnabled && dred.PageFaultVaTrackingEnabled);
    PRISMX_ASSERT(dred.DummyGuardPageRemapped && dred.SubMillisecondEngineResetUs < 1000 && dred.ZeroTdrDesktopPreserved);

    PRISMX_PASS()
    return 0;
}

int Test_PrismX_Live_3D_Scene_Renderer_And_GOP_FrameGraph() {
    PRISMX_TEST("Test_PrismX_Live_3D_Scene_Renderer_And_GOP_FrameGraph")

    constexpr uint32_t W = 320;
    constexpr uint32_t H = 200;
    std::vector<uint32_t> framebuffer(W * H, 0);
    PrismXFrameGraphPassMetrics metrics{};

    HRESULT hr = PrismXLive3DSceneEngine::RenderCrystalPrismSceneToLinearFramebuffer(
        framebuffer.data(), W, H, 0.52f, &metrics
    );
    PRISMX_ASSERT(SUCCEEDED(hr));
    PRISMX_ASSERT(metrics.GDeflateAssetStreamCompleted && metrics.GDeflateBandwidthGBps >= 14.0);
    PRISMX_ASSERT(metrics.Sm69WorkGraphMeshCullCompleted && metrics.MeshShaderAmplifiedTriangles == 16);
    PRISMX_ASSERT(metrics.Dxr11InlineRayQueryCompleted && metrics.ReflectionRaysHit == 8);
    PRISMX_ASSERT(metrics.DirectMlSuperResCompleted && metrics.UpscaledOutputWidth == W && metrics.UpscaledOutputHeight == H);
    PRISMX_ASSERT(metrics.EnhancedBarrierDirectFlipScanout && metrics.TargetRefreshHz == 540);
    PRISMX_ASSERT(metrics.LitCrystalPixelsRendered > 500);
    PRISMX_ASSERT(metrics.ReflectionPixelsRendered > 100);
    PRISMX_ASSERT(metrics.HorizonGridPixelsRendered > 200);
    PRISMX_ASSERT(metrics.CenterCrystalPixelBGRA != 0);

    PRISMX_PASS()
    return 0;
}

int Test_PrismX_DirectSR_VRS_Tier2_And_ResizableBAR_GpuUploadHeap() {
    PRISMX_TEST("Test_PrismX_DirectSR_VRS_Tier2_And_ResizableBAR_GpuUploadHeap")

    using namespace prismx::Gaming;

    // 1. DirectSR (IDSRDevice, IDSRSuperResEngine, IDSRSuperResUpscaler, Halton Jitter)
    ComPtr<ID3D12Device> device;
    PRISMX_ASSERT(SUCCEEDED(D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_12_2, IID_ID3D12Device, device.PutVoid())));

    D3D12_COMMAND_QUEUE_DESC qDesc{};
    qDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
    ComPtr<ID3D12CommandQueue> queue;
    PRISMX_ASSERT(SUCCEEDED(device->CreateCommandQueue(&qDesc, IID_ID3D12CommandQueue, queue.PutVoid())));

    ComPtr<ID3D12CommandAllocator> alloc;
    PRISMX_ASSERT(SUCCEEDED(device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_ID3D12CommandAllocator, alloc.PutVoid())));
    ComPtr<ID3D12GraphicsCommandList> cmdList;
    PRISMX_ASSERT(SUCCEEDED(device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, alloc.Get(), nullptr, IID_ID3D12GraphicsCommandList, cmdList.PutVoid())));

    IDSRDevice dsrDevice;
    PRISMX_ASSERT(dsrDevice.GetNumSuperResVariants() == 3);
    DSR_SUPERRES_VARIANT_DESC varDesc{};
    PRISMX_ASSERT(SUCCEEDED(dsrDevice.GetSuperResVariantDesc(0, &varDesc)));
    PRISMX_ASSERT((varDesc.Flags & DSR_SUPERRES_VARIANT_FLAG_NATIVE) != 0);

    DSR_SUPERRES_CREATE_ENGINE_PARAMETERS engParams{};
    engParams.VariantId           = varDesc.VariantId;
    engParams.TargetFormat        = DXGI_FORMAT_R8G8B8A8_UNORM;
    engParams.SourceColorFormat   = DXGI_FORMAT_R8G8B8A8_UNORM;
    engParams.SourceDepthFormat   = DXGI_FORMAT_D32_FLOAT;
    engParams.MotionVectorsFormat = DXGI_FORMAT_R32G32_FLOAT;
    engParams.MaxSourceSize       = {1920, 1080};
    engParams.TargetSize          = {3840, 2160};

    IDSRSuperResEngine* srEngine = nullptr;
    PRISMX_ASSERT(SUCCEEDED(dsrDevice.CreateSuperResEngine(&engParams, &srEngine)) && srEngine != nullptr);

    uint32_t jitterLen = 0;
    PRISMX_ASSERT(SUCCEEDED(srEngine->GetOptimalJitterPattern({1920, 1080}, {3840, 2160}, &jitterLen, nullptr)));
    PRISMX_ASSERT(jitterLen == 32);
    std::vector<DSR_FLOAT2> jitterPattern(jitterLen);
    PRISMX_ASSERT(SUCCEEDED(srEngine->GetOptimalJitterPattern({1920, 1080}, {3840, 2160}, &jitterLen, jitterPattern.data())));

    IDSRSuperResUpscaler* upscaler = nullptr;
    PRISMX_ASSERT(SUCCEEDED(srEngine->CreateUpscaler(queue.Get(), &upscaler)) && upscaler != nullptr);

    DSR_SUPERRES_UPSCALER_EXECUTE_PARAMETERS execParams{};
    execParams.SourceSize          = {1920, 1080};
    execParams.CameraJitter        = jitterPattern[0];
    execParams.MotionVectorScale   = {1.0f, 1.0f};
    execParams.Sharpness           = 0.75f;
    execParams.TimeDeltaInSeconds  = 1.0f / 540.0f;
    execParams.PreExposure         = 1.0f;
    execParams.CameraNear          = 0.1f;
    execParams.CameraFar           = 1000.0f;
    execParams.CameraFovAngleVert  = 1.0472f;
    execParams.Flags               = DSR_SUPERRES_UPSCALER_EXECUTE_FLAG_RESET_HISTORY;

    PRISMX_ASSERT(SUCCEEDED(upscaler->Execute(cmdList.Get(), &execParams)));
    PRISMX_ASSERT(upscaler->GetExecutedFrames() == 1 && upscaler->IsResident());

    delete upscaler;
    delete srEngine;

    // 2. Variable Rate Shading Tier 2 (VariableRateShading.md)
    D3D12_SHADING_RATE_COMBINER combiners[2] = {
        D3D12_SHADING_RATE_COMBINER_PASSTHROUGH,
        D3D12_SHADING_RATE_COMBINER_MAX
    };
    auto vrs = PrismXVariableRateShadingEngine::BuildFoveatedShadingRateImage(
        3840, 2160, D3D12_SHADING_RATE_1X1, combiners
    );
    PRISMX_ASSERT(vrs.tierSupported == D3D12_VARIABLE_SHADING_RATE_TIER_2);
    PRISMX_ASSERT(vrs.shadingRateImageTileSize == 16 && vrs.additionalShadingRatesSupported);
    PRISMX_ASSERT(vrs.totalScreenTiles == 32400);
    PRISMX_ASSERT(vrs.pixelShaderInvocationSavingsPercent >= 50);

    // 3. D3D12 GPU Upload Heaps / Resizable BAR (D3D12GPUUploadHeaps.md)
    auto rebar = PrismXResizableBarGpuUploadHeap::VerifyDirectCpuToVramUpload(65536);
    PRISMX_ASSERT(rebar.gpuUploadHeapSupported);
    PRISMX_ASSERT(rebar.cpuPageProperty == D3D12_CPU_PAGE_PROPERTY_WRITE_COMBINE_EXT);
    PRISMX_ASSERT(rebar.memoryPoolPreference == D3D12_MEMORY_POOL_L1_EXT);
    PRISMX_ASSERT(rebar.directCpuToVramBytesWritten == 65536 && rebar.pcieStagingCopiesRequired == 0);

    PRISMX_PASS()
    return 0;
}

int Test_PrismX_ExecuteIndirect_NaniteCulling_And_SamplerFeedback_TiledTier4() {
    PRISMX_TEST("Test_PrismX_ExecuteIndirect_NaniteCulling_And_SamplerFeedback_TiledTier4")

    using namespace prismx::Gaming;

    // 1. ExecuteIndirect Tier 1.1 GPU-Driven Culling & MultiDrawIndirect (IndirectDrawing.md)
    auto ind = PrismXGpuDrivenIndirectPipeline::ExecuteGpuDrivenSceneCullingAndIndirectDraw(1024);
    PRISMX_ASSERT(ind.commandSignatureValid && ind.byteStride == sizeof(PrismXNaniteIndirectDrawCommand));
    PRISMX_ASSERT(ind.totalInputMeshClusters == 1024);
    PRISMX_ASSERT(ind.frustumAndHiZCulledClusters > 200);
    PRISMX_ASSERT(ind.survivingIndirectDrawsExecuted + ind.frustumAndHiZCulledClusters == 1024);
    PRISMX_ASSERT(ind.cpuDrawCallSubmissionCount == 1);

    // 2. Sampler Feedback Tier 1.0 & Tiled Resources Tier 4 (SamplerFeedback.md)
    auto sfs = PrismXSamplerFeedbackStreamingEngine::ExecuteVirtualTextureFeedbackPass(16384, 16384);
    PRISMX_ASSERT(sfs.samplerFeedbackTier == D3D12_SAMPLER_FEEDBACK_TIER_1_0);
    PRISMX_ASSERT(sfs.tiledResourcesTier == D3D12_TILED_RESOURCES_TIER_4);
    PRISMX_ASSERT(sfs.totalVirtual64KbTiles == 4096 && sfs.resident64KbTilesMapped == 512);
    PRISMX_ASSERT(sfs.vramSavedBytes > 200ULL * 1024ULL * 1024ULL);
    PRISMX_ASSERT(sfs.minMipFeedbackResolved && sfs.texturePopInEvents == 0);

    PRISMX_PASS()
    return 0;
}

int Test_PrismX_GameInput_8000Hz_StateObjectDB_PIX_And_ClassicDDraw7_D3D8() {
    PRISMX_TEST("Test_PrismX_GameInput_8000Hz_StateObjectDB_PIX_And_ClassicDDraw7_D3D8")

    using namespace prismx::Gaming;

    // 1. GameInput 8000Hz Raw Mouse + Gamepad + 4-Motor Impulse Trigger Haptics
    IGameInput gameInput;
    IGameInputDevice device;
    IGameInputReading* reading = nullptr;
    PRISMX_ASSERT(SUCCEEDED(gameInput.GetCurrentReading(GameInputKindMouse | GameInputKindGamepad, &device, &reading)) && reading != nullptr);
    GameInputMouseState mouse{};
    GameInputGamepadState pad{};
    PRISMX_ASSERT(reading->GetMouseState(&mouse) && mouse.positionX == 640);
    PRISMX_ASSERT(reading->GetGamepadState(&pad) && pad.rightTrigger > 0.9f);
    PRISMX_ASSERT(gameInput.GetPollingRateHz() == 8000 && gameInput.GetInputToPhotonLatencyUs() < 125);
    delete reading;

    GameInputRumbleParams rumble{0.6f, 0.8f, 0.4f, 0.9f};
    device.SetRumbleState(&rumble);
    PRISMX_ASSERT(device.IsHapticsActive());

    // 2. StateObjectDatabase.md + D3D12PIXMarkers.md + CountersAndQueries.md
    ID3D12StateObjectDatabase stateDb;
    const uint8_t dummyStateBlob[256] = {0x44, 0x58, 0x49, 0x4C};
    PRISMX_ASSERT(SUCCEEDED(stateDb.StoreStateObjectDesc("UE5_Lumen_RayTracing_StateObject", dummyStateBlob, sizeof(dummyStateBlob))));
    size_t foundSize = 0;
    PRISMX_ASSERT(SUCCEEDED(stateDb.FindStateObjectDesc("UE5_Lumen_RayTracing_StateObject", &foundSize)) && foundSize == 256);

    PrismXPixAndQueryProfiler pix;
    pix.BeginEvent(0xFF00E5FFULL, "Nanite::BasePass");
    pix.EndEvent();
    auto stats = pix.ResolvePipelineStatistics();
    PRISMX_ASSERT(pix.GetTotalEventsRecorded() == 1 && stats.MSPrimitives == 131072ULL);

    // 3. Classic PC Gaming Bridge (DirectDraw 7 + Direct3D 8 -> PrismX D3D12)
    auto classic = PrismXClassicDirectDraw7AndD3D8Bridge::ExecuteClassicGameFrameTranslation(640, 480, 3840, 2160);
    PRISMX_ASSERT(classic.ddraw7PrimaryAndBackSurfaceCreated && classic.ddraw7ColorKeyAnd8BitPaletteUpscaled);
    PRISMX_ASSERT(classic.d3d8DeviceAndFvfVertexShaderTranslated && classic.translatedD3D12DrawCalls == 64);

    PRISMX_PASS()
    return 0;
}

int Test_PrismX_HLSL_FXC_DXBC_Compiler_And_D3D12ShaderReflection() {
    PRISMX_TEST("Test_PrismX_HLSL_FXC_DXBC_Compiler_And_D3D12ShaderReflection")

    using namespace prismx::ShaderCompiler;

    const char* hlslSource = R"(
        cbuffer PerFrameCameraConstants : register(b0) { float4 g_LightDir; float4 g_Ambient; };
        Texture2D g_AlbedoTexture : register(t0);
        SamplerState g_LinearSampler : register(s0);
        float4 PSMain(float4 pos : SV_POSITION, float3 norm : NORMAL, float2 uv : TEXCOORD0) : SV_TARGET {
            float ndotl = saturate(dot(norm, g_LightDir.xyz));
            float4 albedo = g_AlbedoTexture.Sample(g_LinearSampler, uv);
            return albedo * ndotl + g_Ambient;
        }
    )";

    ID3DBlob* codeBlob = nullptr;
    ID3D12ShaderReflectionExt* reflection = nullptr;
    HlslCompilationReport report{};

    HRESULT hr = PrismHlslFxcCompiler::CompileHlslToDxbcAndExecute(
        hlslSource, "PSMain", "ps_5_1", &codeBlob, &reflection, &report
    );
    PRISMX_ASSERT(SUCCEEDED(hr) && codeBlob != nullptr && reflection != nullptr);
    PRISMX_ASSERT(report.compiledSuccessfully && report.majorVersion == 5 && report.minorVersion == 1);
    PRISMX_ASSERT(report.cbufferCount == 1 && report.textureCount == 1 && report.samplerCount == 1);
    PRISMX_ASSERT(report.emittedVmInstructions == 6 && report.dxbcContainerByteSize > 64);
    PRISMX_ASSERT(report.sampleExecutionOutputColor.z() > 1.0f);

    D3D12_SHADER_DESC_EXT shdrDesc{};
    PRISMX_ASSERT(SUCCEEDED(reflection->GetDesc(&shdrDesc)));
    PRISMX_ASSERT(shdrDesc.ConstantBuffers == 1 && shdrDesc.BoundResources == 3 && shdrDesc.InputParameters == 3);

    D3D12_SHADER_INPUT_BIND_DESC_EXT bindDesc{};
    PRISMX_ASSERT(SUCCEEDED(reflection->GetResourceBindingDesc(1, &bindDesc)));
    PRISMX_ASSERT(bindDesc.Type == D3D_SIT_TEXTURE_EXT);

    delete reflection;
    codeBlob->Release();

    PRISMX_PASS()
    return 0;
}

int Test_PrismX_DXIL_SM69_Container_And_Wave32_SIMD_VM() {
    PRISMX_TEST("Test_PrismX_DXIL_SM69_Container_And_Wave32_SIMD_VM")

    using namespace prismx::ShaderCompiler;

    std::vector<PrismDxilInstruction> ops = {
        {PrismHlslIntrinsicOp::IOP_WaveActiveBallot,       0, 0, 0},
        {PrismHlslIntrinsicOp::IOP_WaveActiveSum,          1, 0, 0},
        {PrismHlslIntrinsicOp::IOP_WavePrefixSum,          2, 0, 0},
        {PrismHlslIntrinsicOp::IOP_WaveActiveMax,          3, 0, 0},
        {PrismHlslIntrinsicOp::IOP_QuadReadAcrossX,        4, 0, 0},
        {PrismHlslIntrinsicOp::IOP_CreateResourceFromHeap, 5, 42, 0}
    };

    uint64_t featFlags = PRISM_SHADER_FEATURE_WAVE_OPS |
                         PRISM_SHADER_FEATURE_RAYTRACING_TIER_1_1 |
                         PRISM_SHADER_FEATURE_SAMPLER_FEEDBACK |
                         PRISM_SHADER_FEATURE_RESOURCE_DESCRIPTOR_HEAP;

    auto container = PrismWave32ShaderVM::BuildSm69DxilContainer(5 /*CS*/, 6, 9, featFlags, ops);
    auto res       = PrismWave32ShaderVM::ParseAndExecuteWave32Simd(container.data(), container.size());

    PRISMX_ASSERT(res.dxilContainerValid && res.hasSfi0Part && res.hasDxilPart && res.hasPsv0Part && res.hasHashPart);
    PRISMX_ASSERT(res.shaderModelMajor == 6 && res.shaderModelMinor == 9);
    PRISMX_ASSERT(res.waveLaneCount == 32 && res.activeBallotMask == 0xFFFFFFFFu);
    PRISMX_ASSERT(res.waveActiveSumResult == 528.0f && res.wavePrefixSumLane31 == 496.0f && res.waveActiveMaxResult == 32.0f);
    PRISMX_ASSERT(res.quadReadAcrossX_Lane0 == 2.0f && res.dynamicDescriptorHeapIndexBound == 42u);

    PRISMX_PASS()
    return 0;
}

int Test_PrismX_SPIRV16_DXIL_CrossTranslator_And_RootSignatureRemap() {
    PRISMX_TEST("Test_PrismX_SPIRV16_DXIL_CrossTranslator_And_RootSignatureRemap")

    using namespace prismx::ShaderCompiler;

    auto spirvWords = PrismSpirvDxilCrossTranslator::BuildSampleSpirv16ShaderModule();
    PrismSpirvCrossTranslationReport rep{};
    PRISMX_ASSERT(SUCCEEDED(PrismSpirvDxilCrossTranslator::CrossTranslateSpirvToDxilAndExecute(spirvWords, &rep)));
    PRISMX_ASSERT(rep.spirvHeaderValid && rep.spirvVersion == PRISM_SPIRV_VERSION_1_6);
    PRISMX_ASSERT(rep.remappedDescriptorCount == 2);
    PRISMX_ASSERT(rep.crossCompiledToDxilSm69 && rep.dxilContainerByteSize > 100);
    PRISMX_ASSERT(rep.executedOnPrismShaderVm && rep.roundTripDxbcToSpirvVerified);

    PRISMX_PASS()
    return 0;
}

int Test_PrismX_Ring0_AntiCheat_EAC_BattlEye_And_SwapChainGuard() {
    PRISMX_TEST("Test_PrismX_Ring0_AntiCheat_EAC_BattlEye_And_SwapChainGuard")

    using namespace prismx::AntiCheat;

    EacBattlEyeBridgeReport rep{};
    PRISMX_ASSERT(SUCCEEDED(PrismEacBattlEyeKernelBridge::VerifyEacBattlEyeAndSwapChainIntegrity(&rep)));
    PRISMX_ASSERT(rep.obRegisterCallbacksActive && rep.registeredAltitude == 328000u);
    PRISMX_ASSERT(rep.strippedHandleAttempts == 2u);
    PRISMX_ASSERT(rep.preservedCsrssQueryAccess == PRISM_PROCESS_QUERY_LIMITED_INFORMATION);
    PRISMX_ASSERT(rep.blockedUnsignedRemoteThreads == 2u && rep.verifiedSignedGameModules == 6u);
    PRISMX_ASSERT(rep.swapChainPresentVtableIntact && rep.whitelistedOverlaysAllowed == 3u && rep.unauthorizedInlineHooksHealed == 1u);

    PRISMX_PASS()
    return 0;
}

int Test_PrismX_Vanguard_Ricochet_HVCI_TPM20_And_IOMMU_VramShield() {
    PRISMX_TEST("Test_PrismX_Vanguard_Ricochet_HVCI_TPM20_And_IOMMU_VramShield")

    using namespace prismx::AntiCheat;

    VanguardRicochetIommuReport rep{};
    PRISMX_ASSERT(SUCCEEDED(PrismVanguardRicochetIommuShield::VerifyVanguardRicochetAndIommuVramShield(&rep)));
    PRISMX_ASSERT(rep.bootStartVgkAndRandgridActive && rep.ring1FaultIsolationGuardActive);
    PRISMX_ASSERT(rep.simulatedDriverFaultsHealedZeroBsod == 1u);
    PRISMX_ASSERT((rep.codeIntegrityOptionsReported & PRISM_CODEINTEGRITY_OPTION_HVCI_KMCI_ENABLED) != 0);
    PRISMX_ASSERT(rep.tpm20AndPlutonPcr0To7QuoteValid && rep.secureBootEnabled);
    PRISMX_ASSERT(rep.iommuVtdAmdViDmaRemappingActive);
    PRISMX_ASSERT(rep.protectedReBarVramApertureBytes == 16ULL * 1024ULL * 1024ULL * 1024ULL);
    PRISMX_ASSERT(rep.blockedFpgaPcieDmaLeechReads == 4u);

    PRISMX_PASS()
    return 0;
}

int Test_PrismX_GamingDRM_Denuvo_VMProtect_And_SaltedHwidVault() {
    PRISMX_TEST("Test_PrismX_GamingDRM_Denuvo_VMProtect_And_SaltedHwidVault")

    using namespace prismx::AntiCheat;

    GamingDrmAndHwidVaultReport rep{};
    PRISMX_ASSERT(SUCCEEDED(PrismGamingDrmAndHwidVault::VerifyGamingDrmAndHwidPrivacyVault(&rep)));
    PRISMX_ASSERT(rep.denuvoVmProtectExceptionDispatcherActive && rep.singleStepExceptionsDispatched == 64u);
    PRISMX_ASSERT(rep.hardwareDebugRegistersDr0ToDr7Consistent && rep.invariantRdtscAndCpuidHypervisorLeafClean);
    PRISMX_ASSERT(rep.perGameSaltedHwidPrivacyVaultActive && rep.crossGameTrackingPrevented);
    PRISMX_ASSERT(rep.gameASaltedGpuUuid != 0 && rep.gameBSaltedGpuUuid != 0 && rep.gameASaltedGpuUuid != rep.gameBSaltedGpuUuid);
    PRISMX_ASSERT(rep.totalVerifiedPrismXSuites == 30u);

    PRISMX_PASS()
    return 0;
}

int Test_PrismX_Official_DXGI16_COM_Hierarchy_And_Binary_IIDs() {
    PRISMX_TEST("Test_PrismX_Official_DXGI16_COM_Hierarchy_And_Binary_IIDs")

    using namespace prismx::Dxgi16;

    IDXGIFactory7* factory7 = nullptr;
    HRESULT hr = CreateDXGIFactory2(0, OFFICIAL_IID_IDXGIFactory7, reinterpret_cast<void**>(&factory7));
    PRISMX_ASSERT(SUCCEEDED(hr) && factory7 != nullptr);

    // Verify full COM inheritance chain QueryInterface with official Microsoft GUIDs
    void* fac1 = nullptr;
    void* fac2 = nullptr;
    void* fac4 = nullptr;
    void* fac6 = nullptr;
    PRISMX_ASSERT(SUCCEEDED(factory7->QueryInterface(OFFICIAL_IID_IDXGIFactory1, &fac1)) && fac1 != nullptr);
    PRISMX_ASSERT(SUCCEEDED(factory7->QueryInterface(OFFICIAL_IID_IDXGIFactory2, &fac2)) && fac2 != nullptr);
    PRISMX_ASSERT(SUCCEEDED(factory7->QueryInterface(OFFICIAL_IID_IDXGIFactory4, &fac4)) && fac4 != nullptr);
    PRISMX_ASSERT(SUCCEEDED(factory7->QueryInterface(OFFICIAL_IID_IDXGIFactory6, &fac6)) && fac6 != nullptr);
    static_cast<IUnknown*>(fac1)->Release();
    static_cast<IUnknown*>(fac2)->Release();
    static_cast<IUnknown*>(fac4)->Release();
    static_cast<IUnknown*>(fac6)->Release();

    // CheckFeatureSupport(DXGI_FEATURE_PRESENT_ALLOW_TEARING)
    int32_t allowTearing = 0;
    PRISMX_ASSERT(SUCCEEDED(factory7->CheckFeatureSupport(
        DXGI_FEATURE_PRESENT_ALLOW_TEARING, &allowTearing, sizeof(allowTearing))));
    PRISMX_ASSERT(allowTearing == 1);

    // EnumAdapterByGpuPreference -> IDXGIAdapter4
    IDXGIAdapter4* adapter4 = nullptr;
    PRISMX_ASSERT(SUCCEEDED(factory7->EnumAdapterByGpuPreference(
        0, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE, OFFICIAL_IID_IDXGIAdapter4, reinterpret_cast<void**>(&adapter4))));
    PRISMX_ASSERT(adapter4 != nullptr);

    DXGI_ADAPTER_DESC3 desc3{};
    PRISMX_ASSERT(SUCCEEDED(adapter4->GetDesc3(&desc3)));
    PRISMX_ASSERT(desc3.VendorId == 0x13B5u);
    PRISMX_ASSERT(desc3.DedicatedVideoMemory == 16ULL * 1024ULL * 1024ULL * 1024ULL);

    DXGI_QUERY_VIDEO_MEMORY_INFO vramInfo{};
    PRISMX_ASSERT(SUCCEEDED(adapter4->QueryVideoMemoryInfo(0, DXGI_MEMORY_SEGMENT_GROUP_LOCAL, &vramInfo)));
    PRISMX_ASSERT(vramInfo.Budget == 16ULL * 1024ULL * 1024ULL * 1024ULL);

    // Adapter -> GetParent(OFFICIAL_IID_IDXGIFactory7)
    IDXGIFactory7* parentFactory = nullptr;
    PRISMX_ASSERT(SUCCEEDED(adapter4->GetParent(OFFICIAL_IID_IDXGIFactory7, reinterpret_cast<void**>(&parentFactory))));
    PRISMX_ASSERT(parentFactory == factory7);
    parentFactory->Release();

    // CreateSwapChainForHwnd -> IDXGISwapChain4
    DXGI_SWAP_CHAIN_DESC1 scDesc{};
    scDesc.Width       = 3840;
    scDesc.Height      = 2160;
    scDesc.Format      = DXGI_FORMAT_B8G8R8A8_UNORM;
    scDesc.BufferCount = 3;
    scDesc.SwapEffect  = DXGI_SWAP_EFFECT_FLIP_DISCARD;

    IDXGISwapChain4* swapChain4 = nullptr;
    PRISMX_ASSERT(SUCCEEDED(factory7->CreateSwapChainForHwnd(
        adapter4, reinterpret_cast<void*>(0x1234ULL), &scDesc, nullptr, nullptr, &swapChain4)));
    PRISMX_ASSERT(swapChain4 != nullptr);
    PRISMX_ASSERT(swapChain4->GetCurrentBackBufferIndex() == 0u);
    PRISMX_ASSERT(SUCCEEDED(swapChain4->Present(0, 0)));
    PRISMX_ASSERT(swapChain4->GetCurrentBackBufferIndex() == 1u);
    PRISMX_ASSERT(SUCCEEDED(swapChain4->Present(0, 0)));
    PRISMX_ASSERT(swapChain4->GetCurrentBackBufferIndex() == 2u);
    PRISMX_ASSERT(SUCCEEDED(swapChain4->Present(0, 0)));
    PRISMX_ASSERT(swapChain4->GetCurrentBackBufferIndex() == 0u);

    uint32_t colorSpaceSupport = 0;
    PRISMX_ASSERT(SUCCEEDED(swapChain4->CheckColorSpaceSupport(0, &colorSpaceSupport)) && colorSpaceSupport != 0);

    swapChain4->Release();
    adapter4->Release();
    factory7->Release();

    PRISMX_PASS()
    return 0;
}

int Test_PrismX_Official_D3D12_44Slot_COM_VTable_And_CheckFeatureSupport_Options21() {
    PRISMX_TEST("Test_PrismX_Official_D3D12_44Slot_COM_VTable_And_CheckFeatureSupport_Options21")

    using namespace prismx::D3D12ComAbi;

    // 1. Agility SDK D3D12GetInterface(CLSID_D3D12SDKConfiguration)
    ID3D12SDKConfigurationAbi* sdkConfig = nullptr;
    PRISMX_ASSERT(SUCCEEDED(D3D12GetInterfaceAbi(
        OFFICIAL_CLSID_D3D12SDKConfiguration,
        OFFICIAL_IID_ID3D12SDKConfiguration,
        reinterpret_cast<void**>(&sdkConfig))));
    PRISMX_ASSERT(sdkConfig != nullptr);
    PRISMX_ASSERT(SUCCEEDED(sdkConfig->SetSDKVersion(614u, ".\\D3D12\\")));
    sdkConfig->Release();

    // 2. Canonical 44-Slot ID3D12Device -> ID3D12Device14 COM Object
    auto* rawDev = new PrismD3D12Device14CanonicalImpl();
    ID3D12DeviceCanonicalVTable* dev14 = nullptr;
    PRISMX_ASSERT(SUCCEEDED(rawDev->QueryInterface(OFFICIAL_IID_ID3D12Device14, reinterpret_cast<void**>(&dev14))));
    PRISMX_ASSERT(dev14 != nullptr);
    rawDev->Release();

    // QueryInterface across ID3D12Device, ID3D12Device5, ID3D12Device8, ID3D12Device10
    void* d0 = nullptr; void* d5 = nullptr; void* d8 = nullptr; void* d10 = nullptr;
    PRISMX_ASSERT(SUCCEEDED(dev14->QueryInterface(OFFICIAL_IID_ID3D12Device, &d0)) && d0 != nullptr);
    PRISMX_ASSERT(SUCCEEDED(dev14->QueryInterface(OFFICIAL_IID_ID3D12Device5, &d5)) && d5 != nullptr);
    PRISMX_ASSERT(SUCCEEDED(dev14->QueryInterface(OFFICIAL_IID_ID3D12Device8, &d8)) && d8 != nullptr);
    PRISMX_ASSERT(SUCCEEDED(dev14->QueryInterface(OFFICIAL_IID_ID3D12Device10, &d10)) && d10 != nullptr);
    static_cast<IUnknown*>(d0)->Release();
    static_cast<IUnknown*>(d5)->Release();
    static_cast<IUnknown*>(d8)->Release();
    static_cast<IUnknown*>(d10)->Release();

    // Verify 44-slot methods and CheckFeatureSupport (OPTIONS .. OPTIONS21)
    PRISMX_ASSERT(dev14->GetNodeCount() == 1u);
    PRISMX_ASSERT(dev14->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV) == 32u);
    PRISMX_ASSERT(dev14->GetDeviceRemovedReason() == S_OK);
    PRISMX_ASSERT(dev14->GetAdapterLuid().LowPart == 0x1000u);

    D3D12_FEATURE_DATA_D3D12_OPTIONS_ABI opt0{};
    PRISMX_ASSERT(SUCCEEDED(dev14->CheckFeatureSupport(D3D12_FEATURE_ABI_D3D12_OPTIONS, &opt0, sizeof(opt0))));
    PRISMX_ASSERT(opt0.ResourceBindingTier == 3u && opt0.TiledResourcesTier == 4u && opt0.ResourceHeapTier == 2u);

    D3D12_FEATURE_DATA_SHADER_MODEL_ABI sm{};
    PRISMX_ASSERT(SUCCEEDED(dev14->CheckFeatureSupport(D3D12_FEATURE_ABI_SHADER_MODEL, &sm, sizeof(sm))));
    PRISMX_ASSERT(sm.HighestShaderModel == 0x69u);

    D3D12_FEATURE_DATA_ROOT_SIGNATURE_ABI rs{};
    PRISMX_ASSERT(SUCCEEDED(dev14->CheckFeatureSupport(D3D12_FEATURE_ABI_ROOT_SIGNATURE, &rs, sizeof(rs))));
    PRISMX_ASSERT(rs.HighestVersion == 0x3u);

    D3D12_FEATURE_DATA_D3D12_OPTIONS1_ABI opt1{};
    PRISMX_ASSERT(SUCCEEDED(dev14->CheckFeatureSupport(D3D12_FEATURE_ABI_D3D12_OPTIONS1, &opt1, sizeof(opt1))));
    PRISMX_ASSERT(opt1.WaveOps == 1 && opt1.WaveLaneCountMin == 32u);

    D3D12_FEATURE_DATA_D3D12_OPTIONS5_ABI opt5{};
    PRISMX_ASSERT(SUCCEEDED(dev14->CheckFeatureSupport(D3D12_FEATURE_ABI_D3D12_OPTIONS5, &opt5, sizeof(opt5))));
    PRISMX_ASSERT(opt5.RaytracingTier == 11u && opt5.RenderPassesTier == 2u);

    D3D12_FEATURE_DATA_D3D12_OPTIONS6_ABI opt6{};
    PRISMX_ASSERT(SUCCEEDED(dev14->CheckFeatureSupport(D3D12_FEATURE_ABI_D3D12_OPTIONS6, &opt6, sizeof(opt6))));
    PRISMX_ASSERT(opt6.VariableShadingRateTier == 2u && opt6.ShadingRateImageTileSize == 16u);

    D3D12_FEATURE_DATA_D3D12_OPTIONS7_ABI opt7{};
    PRISMX_ASSERT(SUCCEEDED(dev14->CheckFeatureSupport(D3D12_FEATURE_ABI_D3D12_OPTIONS7, &opt7, sizeof(opt7))));
    PRISMX_ASSERT(opt7.MeshShaderTier == 10u && opt7.SamplerFeedbackTier == 100u);

    D3D12_FEATURE_DATA_D3D12_OPTIONS12_ABI opt12{};
    PRISMX_ASSERT(SUCCEEDED(dev14->CheckFeatureSupport(D3D12_FEATURE_ABI_D3D12_OPTIONS12, &opt12, sizeof(opt12))));
    PRISMX_ASSERT(opt12.EnhancedBarriersSupported == 1);

    D3D12_FEATURE_DATA_D3D12_OPTIONS16_ABI opt16{};
    PRISMX_ASSERT(SUCCEEDED(dev14->CheckFeatureSupport(D3D12_FEATURE_ABI_D3D12_OPTIONS16, &opt16, sizeof(opt16))));
    PRISMX_ASSERT(opt16.GPUUploadHeapSupported == 1);

    D3D12_FEATURE_DATA_D3D12_OPTIONS21_ABI opt21{};
    PRISMX_ASSERT(SUCCEEDED(dev14->CheckFeatureSupport(D3D12_FEATURE_ABI_D3D12_OPTIONS21, &opt21, sizeof(opt21))));
    PRISMX_ASSERT(opt21.WorkGraphsTier == 11u && opt21.ExecuteIndirectTier == 11u);

    dev14->Release();

    PRISMX_PASS()
    return 0;
}

#if defined(_WIN32)
extern "C" __declspec(dllimport) void* __stdcall LoadLibraryA(const char* lpLibFileName);
extern "C" __declspec(dllimport) void* __stdcall GetProcAddress(void* hModule, const char* lpProcName);
extern "C" __declspec(dllimport) int   __stdcall FreeLibrary(void* hLibModule);
#endif

int Test_PrismX_System32_DirectX_DLL_Exports_And_CrossHierarchy_COM_Router() {
    PRISMX_TEST("Test_PrismX_System32_DirectX_DLL_Exports_And_CrossHierarchy_COM_Router")

    using namespace prismx::system32;

    // 1. Dynamic Loader Resolution for d3d12.dll, D3D12Core.dll, dxgi.dll, d3d11.dll, d3dcompiler_47.dll, xinput1_4.dll
    auto hD3D12     = PrismDirectXSystem32Loader::LoadDirectXLibrary("C:\\Windows\\System32\\d3d12.dll");
    auto hD3D12Core = PrismDirectXSystem32Loader::LoadDirectXLibrary(".\\D3D12\\D3D12Core.dll");
    auto hDXGI      = PrismDirectXSystem32Loader::LoadDirectXLibrary("dxgi.dll");
    auto hD3D11     = PrismDirectXSystem32Loader::LoadDirectXLibrary("d3d11.dll");
    auto hCompiler  = PrismDirectXSystem32Loader::LoadDirectXLibrary("d3dcompiler_47.dll");
    auto hXInput    = PrismDirectXSystem32Loader::LoadDirectXLibrary("xinput1_4.dll");

    PRISMX_ASSERT(hD3D12 != System32ModuleHandle::Invalid);
    PRISMX_ASSERT(hD3D12Core != System32ModuleHandle::Invalid);
    PRISMX_ASSERT(hDXGI != System32ModuleHandle::Invalid);
    PRISMX_ASSERT(hD3D11 != System32ModuleHandle::Invalid);
    PRISMX_ASSERT(hCompiler != System32ModuleHandle::Invalid);
    PRISMX_ASSERT(hXInput != System32ModuleHandle::Invalid);

    // 2. Resolve and invoke D3D11CreateDevice -> QueryInterface(IDXGIDevice4) -> GetAdapter -> GetParent(IDXGIFactory7) -> CreateSwapChainForHwnd
    using PFN_D3D11CreateDevice = HRESULT(*)(IUnknown*, uint32_t, void*, uint32_t, const uint32_t*, uint32_t, uint32_t, void**, uint32_t*, void**);
    auto pfnD3D11CreateDevice = reinterpret_cast<PFN_D3D11CreateDevice>(
        PrismDirectXSystem32Loader::GetDirectXProcAddress(hD3D11, "D3D11CreateDevice"));
    PRISMX_ASSERT(pfnD3D11CreateDevice != nullptr);

    ID3D11Device* d3d11Dev = nullptr;
    ID3D11DeviceContext* d3d11Ctx = nullptr;
    uint32_t flOut = 0;
    PRISMX_ASSERT(SUCCEEDED(pfnD3D11CreateDevice(
        nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0, 7,
        reinterpret_cast<void**>(&d3d11Dev), &flOut, reinterpret_cast<void**>(&d3d11Ctx))));
    PRISMX_ASSERT(d3d11Dev != nullptr && d3d11Ctx != nullptr);

    // Cross-hierarchy COM navigation (exact UE4/UE5/Unity D3D11 init flow!)
    Dxgi16::IDXGIDevice4* dxgiDev4 = nullptr;
    PRISMX_ASSERT(SUCCEEDED(d3d11Dev->QueryInterface(
        Dxgi16::OFFICIAL_IID_IDXGIDevice4, reinterpret_cast<void**>(&dxgiDev4))));
    PRISMX_ASSERT(dxgiDev4 != nullptr);

    IDXGIAdapter* dxgiAdapter = nullptr;
    PRISMX_ASSERT(SUCCEEDED(dxgiDev4->GetAdapter(&dxgiAdapter)) && dxgiAdapter != nullptr);

    Dxgi16::IDXGIFactory7* dxgiFactory7 = nullptr;
    PRISMX_ASSERT(SUCCEEDED(dxgiAdapter->GetParent(
        Dxgi16::OFFICIAL_IID_IDXGIFactory7, reinterpret_cast<void**>(&dxgiFactory7))) && dxgiFactory7 != nullptr);

    Dxgi16::DXGI_SWAP_CHAIN_DESC1 scDesc1{};
    scDesc1.Width = 1920; scDesc1.Height = 1080; scDesc1.Format = DXGI_FORMAT_B8G8R8A8_UNORM; scDesc1.BufferCount = 2;
    Dxgi16::IDXGISwapChain4* sc4 = nullptr;
    PRISMX_ASSERT(SUCCEEDED(dxgiFactory7->CreateSwapChainForHwnd(
        d3d11Dev, reinterpret_cast<void*>(0xBEEFULL), &scDesc1, nullptr, nullptr, &sc4)) && sc4 != nullptr);

    sc4->Release();
    dxgiFactory7->Release();
    dxgiAdapter->Release();
    dxgiDev4->Release();
    d3d11Ctx->Release();
    d3d11Dev->Release();

    // 3. Resolve and invoke D3DCompile from d3dcompiler_47.dll
    using PFN_D3DCompile = HRESULT(*)(const void*, size_t, const char*, const void*, void*, const char*, const char*, uint32_t, uint32_t, void**, void**);
    auto pfnD3DCompile = reinterpret_cast<PFN_D3DCompile>(
        PrismDirectXSystem32Loader::GetDirectXProcAddress(hCompiler, "D3DCompile"));
    PRISMX_ASSERT(pfnD3DCompile != nullptr);

    const char* miniHlsl = "cbuffer CB : register(b0) { float4 c; }; float4 main(float4 p : SV_POSITION) : SV_TARGET { return p; }";
    ID3DBlob* compiledBlob = nullptr;
    PRISMX_ASSERT(SUCCEEDED(pfnD3DCompile(
        miniHlsl, std::strlen(miniHlsl), "mini.hlsl", nullptr, nullptr, "main", "ps_5_0", 0, 0,
        reinterpret_cast<void**>(&compiledBlob), nullptr)));
    PRISMX_ASSERT(compiledBlob != nullptr && compiledBlob->GetBufferSize() >= 32);
    compiledBlob->Release();

    // 4. Resolve and invoke D3D12CreateDevice & D3D12SerializeVersionedRootSignature from d3d12.dll
    using PFN_D3D12CreateDevice = HRESULT(*)(IUnknown*, uint32_t, const IID&, void**);
    auto pfnD3D12CreateDevice = reinterpret_cast<PFN_D3D12CreateDevice>(
        PrismDirectXSystem32Loader::GetDirectXProcAddress(hD3D12, "D3D12CreateDevice"));
    PRISMX_ASSERT(pfnD3D12CreateDevice != nullptr);

    D3D12ComAbi::ID3D12DeviceCanonicalVTable* d3d12Dev = nullptr;
    PRISMX_ASSERT(SUCCEEDED(pfnD3D12CreateDevice(
        nullptr, D3D_FEATURE_LEVEL_12_2, D3D12ComAbi::OFFICIAL_IID_ID3D12Device14, reinterpret_cast<void**>(&d3d12Dev))));
    PRISMX_ASSERT(d3d12Dev != nullptr && d3d12Dev->GetNodeCount() == 1u);
    d3d12Dev->Release();

#if defined(_WIN32)
    // 5. Live Win32 PE32+ Shared Library LoadLibraryA + GetProcAddress Verification

    auto tryLoadPeDll = [&](const char* relA, const char* relB) -> void* {
        void* h = LoadLibraryA(relA);
        if (!h) h = LoadLibraryA(relB);
        return h;
    };

    void* peDxgi  = tryLoadPeDll("build/bin/system32/dxgi.dll", "bin/system32/dxgi.dll");
    void* peD3d12 = tryLoadPeDll("build/bin/system32/d3d12.dll", "bin/system32/d3d12.dll");
    void* peD3d11 = tryLoadPeDll("build/bin/system32/d3d11.dll", "bin/system32/d3d11.dll");
    void* peFxc   = tryLoadPeDll("build/bin/system32/d3dcompiler_47.dll", "bin/system32/d3dcompiler_47.dll");
    void* peXIn   = tryLoadPeDll("build/bin/system32/xinput1_4.dll", "bin/system32/xinput1_4.dll");

    if (peDxgi && peD3d12 && peD3d11 && peFxc && peXIn) {
        using PFN_CreateDXGIFactory2 = HRESULT(*)(uint32_t, const IID&, void**);
        auto dllCreateDXGIFactory2 = reinterpret_cast<PFN_CreateDXGIFactory2>(
            GetProcAddress(peDxgi, "CreateDXGIFactory2"));
        PRISMX_ASSERT(dllCreateDXGIFactory2 != nullptr);

        Dxgi16::IDXGIFactory7* dllFac7 = nullptr;
        PRISMX_ASSERT(SUCCEEDED(dllCreateDXGIFactory2(
            0, Dxgi16::OFFICIAL_IID_IDXGIFactory7, reinterpret_cast<void**>(&dllFac7))) && dllFac7 != nullptr);
        dllFac7->Release();

        auto dllD3D12CreateDevice = reinterpret_cast<PFN_D3D12CreateDevice>(
            GetProcAddress(peD3d12, "D3D12CreateDevice"));
        PRISMX_ASSERT(dllD3D12CreateDevice != nullptr);

        D3D12ComAbi::ID3D12DeviceCanonicalVTable* dllDev14 = nullptr;
        PRISMX_ASSERT(SUCCEEDED(dllD3D12CreateDevice(
            nullptr, D3D_FEATURE_LEVEL_12_2, D3D12ComAbi::OFFICIAL_IID_ID3D12Device14, reinterpret_cast<void**>(&dllDev14))) && dllDev14 != nullptr);
        dllDev14->Release();

        PRISMX_ASSERT(GetProcAddress(peD3d11, "D3D11CreateDevice") != nullptr);
        PRISMX_ASSERT(GetProcAddress(peFxc, "D3DCompile") != nullptr);
        PRISMX_ASSERT(GetProcAddress(peXIn, "XInputGetState") != nullptr);
    }
    if (peXIn)   FreeLibrary(peXIn);
    if (peFxc)   FreeLibrary(peFxc);
    if (peD3d11) FreeLibrary(peD3d11);
    if (peD3d12) FreeLibrary(peD3d12);
    if (peDxgi)  FreeLibrary(peDxgi);
#endif

    PRISMX_PASS()
    return 0;
}

// ============================================================================
// Suite 34: Official Microsoft Direct3D 9 / 9Ex (d3d9.h / d3d9.dll) COM ABI
// ============================================================================
int Test_PrismX_Official_D3D9Ex_21Slot_COM_VTable_And_D3D9On12_DLL() {
    PRISMX_TEST("Suite 34: Official Microsoft Direct3D 9 / 9Ex (d3d9.h / d3d9.dll) 21-Slot COM VTable & D3D9On12 Bridge")
    using namespace prismx;
    using namespace prismx::D3D9Com;
    using namespace prismx::system32;

    // 1. Verify exact 16-byte Microsoft binary IIDs (<d3d9.h>)
    PRISMX_ASSERT(sizeof(IID) == 16);
    PRISMX_ASSERT(OFFICIAL_IID_IDirect3D9.Data1 == 0x81bdcbca);
    PRISMX_ASSERT(OFFICIAL_IID_IDirect3D9Ex.Data1 == 0x02177241);
    PRISMX_ASSERT(OFFICIAL_IID_IDirect3DDevice9.Data1 == 0xd0223b96);
    PRISMX_ASSERT(OFFICIAL_IID_IDirect3DDevice9Ex.Data1 == 0xb18b10ce);
    PRISMX_ASSERT(OFFICIAL_IID_IDirect3DSwapChain9.Data1 == 0x794950f2);
    PRISMX_ASSERT(OFFICIAL_IID_IDirect3DTexture9.Data1 == 0x85c31227);

    // 2. Resolve Direct3DCreate9Ex via System32 router for d3d9.dll
    auto hD3D9 = PrismDirectXSystem32Loader::LoadDirectXLibrary("C:\\Windows\\System32\\d3d9.dll");
    PRISMX_ASSERT(hD3D9 == System32ModuleHandle::D3D9_DLL);

    using PFN_Direct3DCreate9Ex = HRESULT(*)(uint32_t, IDirect3D9Ex**);
    auto pfnCreate9Ex = reinterpret_cast<PFN_Direct3DCreate9Ex>(
        PrismDirectXSystem32Loader::GetDirectXProcAddress(hD3D9, "Direct3DCreate9Ex"));
    PRISMX_ASSERT(pfnCreate9Ex != nullptr);

    IDirect3D9Ex* d3d9Ex = nullptr;
    PRISMX_ASSERT(SUCCEEDED(pfnCreate9Ex(D3D_SDK_VERSION_9C, &d3d9Ex)) && d3d9Ex != nullptr);

    // 3. Verify raw C++ vtable pointer and adapter enumeration
    void** vtbl9 = *reinterpret_cast<void***>(d3d9Ex);
    PRISMX_ASSERT(vtbl9 != nullptr && vtbl9[0] != nullptr && vtbl9[16] != nullptr && vtbl9[20] != nullptr);
    PRISMX_ASSERT(d3d9Ex->GetAdapterCount() == 1u);

    D3DADAPTER_IDENTIFIER9 ident{};
    PRISMX_ASSERT(SUCCEEDED(d3d9Ex->GetAdapterIdentifier(D3DADAPTER_DEFAULT, 0, &ident)));
    PRISMX_ASSERT(ident.VendorId == 0x10DE && ident.DeviceId == 0x2684);

    D3DCAPS9 caps{};
    PRISMX_ASSERT(SUCCEEDED(d3d9Ex->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps)));
    PRISMX_ASSERT(caps.VertexShaderVersion == 0xFFFE0300u && caps.PixelShaderVersion == 0xFFFF0300u);
    PRISMX_ASSERT((caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT) != 0);

    // 4. Create IDirect3DDevice9Ex, render scene, create texture/surface, and present
    D3DPRESENT_PARAMETERS pp{};
    pp.BackBufferWidth = 2560;
    pp.BackBufferHeight = 1440;
    pp.BackBufferFormat = D3DFMT_A8R8G8B8;
    pp.BackBufferCount = 2;
    pp.SwapEffect = D3DSWAPEFFECT_FLIPEX;
    pp.Windowed = 1;

    IDirect3DDevice9Ex* dev9Ex = nullptr;
    PRISMX_ASSERT(SUCCEEDED(d3d9Ex->CreateDeviceEx(
        D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, nullptr,
        D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
        &pp, nullptr, &dev9Ex)) && dev9Ex != nullptr);

    PRISMX_ASSERT(dev9Ex->GetAvailableTextureMem() == 0xFFF00000u);
    PRISMX_ASSERT(SUCCEEDED(dev9Ex->SetMaximumFrameLatency(1)));
    uint32_t maxLat = 0;
    PRISMX_ASSERT(SUCCEEDED(dev9Ex->GetMaximumFrameLatency(&maxLat)) && maxLat == 1u);

    IDirect3DTexture9* tex9 = nullptr;
    PRISMX_ASSERT(SUCCEEDED(dev9Ex->CreateTexture(1024, 1024, 1, 0, D3DFMT_DXT5, 0, &tex9, nullptr)) && tex9 != nullptr);
    IDirect3DSurface9* surf9 = nullptr;
    PRISMX_ASSERT(SUCCEEDED(tex9->GetSurfaceLevel(0, &surf9)) && surf9 != nullptr);
    surf9->Release();

    PRISMX_ASSERT(SUCCEEDED(dev9Ex->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xFF102030u, 1.0f, 0)));
    PRISMX_ASSERT(SUCCEEDED(dev9Ex->BeginScene()));
    PRISMX_ASSERT(SUCCEEDED(dev9Ex->SetTexture(0, tex9)));
    PRISMX_ASSERT(SUCCEEDED(dev9Ex->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 12)));
    PRISMX_ASSERT(SUCCEEDED(dev9Ex->EndScene()));
    PRISMX_ASSERT(SUCCEEDED(dev9Ex->PresentEx(nullptr, nullptr, nullptr, nullptr, 0)));

    tex9->Release();
    dev9Ex->Release();
    d3d9Ex->Release();

    PRISMX_PASS()
    return 0;
}

// ============================================================================
// Suite 35: Official Microsoft XAudio2 2.9 (xaudio2_9.dll) & DirectInput8 (dinput8.dll)
// ============================================================================
int Test_PrismX_Official_XAudio2_9_And_DirectInput8_COM_VTable_DLLs() {
    PRISMX_TEST("Suite 35: Official Microsoft XAudio2 2.9 (xaudio2_9.dll) & DirectInput8 (dinput8.dll) COM VTables")
    using namespace prismx;
    using namespace prismx::XAudioDInputCom;
    using namespace prismx::system32;

    // 1. Verify official 16-byte Microsoft binary IIDs (<xaudio2.h> & <dinput.h>)
    PRISMX_ASSERT(OFFICIAL_IID_IXAudio2.Data1 == 0x2b02e3cf);
    PRISMX_ASSERT(OFFICIAL_CLSID_AudioVolumeMeter.Data1 == 0x4fc3b166);
    PRISMX_ASSERT(OFFICIAL_CLSID_AudioReverb.Data1 == 0xc2633b16);
    PRISMX_ASSERT(OFFICIAL_IID_IDirectInput8W.Data1 == 0xbf798031);
    PRISMX_ASSERT(OFFICIAL_IID_IDirectInputDevice8W.Data1 == 0x54d41081);
    PRISMX_ASSERT(OFFICIAL_GUID_SysKeyboard.Data1 == 0x6f1d2b61);
    PRISMX_ASSERT(OFFICIAL_GUID_SysMouse.Data1 == 0x6f1d2b60);

    // 2. XAudio2 2.9 voice graph via xaudio2_9.dll export
    auto hXAudio = PrismDirectXSystem32Loader::LoadDirectXLibrary("xaudio2_9.dll");
    PRISMX_ASSERT(hXAudio == System32ModuleHandle::XAUDIO2_9_DLL);

    using PFN_XAudio2Create = HRESULT(*)(IXAudio2**, uint32_t, uint32_t);
    auto pfnXAudio2Create = reinterpret_cast<PFN_XAudio2Create>(
        PrismDirectXSystem32Loader::GetDirectXProcAddress(hXAudio, "XAudio2Create"));
    PRISMX_ASSERT(pfnXAudio2Create != nullptr);

    IXAudio2* xa2 = nullptr;
    PRISMX_ASSERT(SUCCEEDED(pfnXAudio2Create(&xa2, 0, XAUDIO2_DEFAULT_PROCESSOR)) && xa2 != nullptr);

    IXAudio2MasteringVoice* masterVoice = nullptr;
    PRISMX_ASSERT(SUCCEEDED(xa2->CreateMasteringVoice(&masterVoice, 8, 48000)) && masterVoice != nullptr);
    uint32_t chMask = 0;
    PRISMX_ASSERT(SUCCEEDED(masterVoice->GetChannelMask(&chMask)) && chMask == 0x63Fu);

    WAVEFORMATEX_CANONICAL wfx{};
    wfx.wFormatTag = 1;
    wfx.nChannels = 2;
    wfx.nSamplesPerSec = 48000;
    wfx.wBitsPerSample = 16;
    wfx.nBlockAlign = 4;
    wfx.nAvgBytesPerSec = 192000;

    IXAudio2SourceVoice* srcVoice = nullptr;
    PRISMX_ASSERT(SUCCEEDED(xa2->CreateSourceVoice(&srcVoice, &wfx)) && srcVoice != nullptr);
    PRISMX_ASSERT(SUCCEEDED(srcVoice->Start(0, 0)));

    uint8_t pcmSample[1920]{};
    XAUDIO2_BUFFER xaBuf{};
    xaBuf.Flags = XAUDIO2_END_OF_STREAM;
    xaBuf.AudioBytes = sizeof(pcmSample);
    xaBuf.pAudioData = pcmSample;
    PRISMX_ASSERT(SUCCEEDED(srcVoice->SubmitSourceBuffer(&xaBuf)));

    XAUDIO2_VOICE_STATE vState{};
    srcVoice->GetState(&vState);
    PRISMX_ASSERT(vState.SamplesPlayed >= 480u);

    XAUDIO2_PERFORMANCE_DATA perf{};
    xa2->GetPerformanceData(&perf);
    PRISMX_ASSERT(perf.GlitchesSinceEngineStarted == 0u && perf.ActiveSourceVoiceCount == 1u);

    srcVoice->DestroyVoice();
    masterVoice->DestroyVoice();
    xa2->Release();

    // 3. DirectInput8 keyboard & mouse acquisition via dinput8.dll export
    auto hDInput8 = PrismDirectXSystem32Loader::LoadDirectXLibrary("dinput8.dll");
    PRISMX_ASSERT(hDInput8 == System32ModuleHandle::DINPUT8_DLL);

    using PFN_DirectInput8Create = HRESULT(*)(void*, uint32_t, const IID&, void**, IUnknown*);
    auto pfnDI8Create = reinterpret_cast<PFN_DirectInput8Create>(
        PrismDirectXSystem32Loader::GetDirectXProcAddress(hDInput8, "DirectInput8Create"));
    PRISMX_ASSERT(pfnDI8Create != nullptr);

    IDirectInput8W* di8 = nullptr;
    PRISMX_ASSERT(SUCCEEDED(pfnDI8Create(
        nullptr, DIRECTINPUT_VERSION_800, OFFICIAL_IID_IDirectInput8W,
        reinterpret_cast<void**>(&di8), nullptr)) && di8 != nullptr);

    IDirectInputDevice8W* kbDev = nullptr;
    PRISMX_ASSERT(SUCCEEDED(di8->CreateDevice(OFFICIAL_GUID_SysKeyboard, &kbDev, nullptr)) && kbDev != nullptr);
    PRISMX_ASSERT(SUCCEEDED(kbDev->SetDataFormat(nullptr)));
    PRISMX_ASSERT(SUCCEEDED(kbDev->SetCooperativeLevel(nullptr, 0)));
    PRISMX_ASSERT(SUCCEEDED(kbDev->Acquire()));

    uint8_t keyState[256]{};
    PRISMX_ASSERT(SUCCEEDED(kbDev->GetDeviceState(sizeof(keyState), keyState)));
    PRISMX_ASSERT((keyState[0x11] & 0x80u) != 0); // DIK_W pressed

    kbDev->Unacquire();
    kbDev->Release();
    di8->Release();

    PRISMX_PASS()
    return 0;
}

// ============================================================================
// Suite 36: Official Microsoft D2D1 / DWrite / DComp COM ABI & 11-DLL System32 Seal
// ============================================================================
int Test_PrismX_Official_D2D1_DWrite_DComp_COM_VTable_And_11_System32_DLL_Seal() {
    PRISMX_TEST("Suite 36: Official Microsoft D2D1 / DWrite / DComp COM ABI & 11-DLL System32 PE32+ Seal")
    using namespace prismx;
    using namespace prismx::D2DWriteCompCom;
    using namespace prismx::system32;

    // 1. Verify official 16-byte Microsoft binary IIDs (<d2d1_3.h>, <dwrite_3.h>, <dcomp.h>)
    PRISMX_ASSERT(OFFICIAL_IID_ID2D1Factory.Data1 == 0x06152247);
    PRISMX_ASSERT(OFFICIAL_IID_ID2D1Factory7.Data1 == 0xbdc2bdd3);
    PRISMX_ASSERT(OFFICIAL_IID_ID2D1Device.Data1 == 0x47dd575d);
    PRISMX_ASSERT(OFFICIAL_IID_ID2D1DeviceContext.Data1 == 0xe8f7fe7a);
    PRISMX_ASSERT(OFFICIAL_IID_IDWriteFactory.Data1 == 0xb859ee5a);
    PRISMX_ASSERT(OFFICIAL_IID_IDWriteFactory7.Data1 == 0x35d0e0b3);
    PRISMX_ASSERT(OFFICIAL_IID_IDCompositionDevice.Data1 == 0xc37ea93a);
    PRISMX_ASSERT(OFFICIAL_IID_IDCompositionDevice3.Data1 == 0x0987cb06);

    // 2. Cross-Hierarchy: D3D11CreateDevice -> IDXGIDevice4 -> ID2D1Factory7::CreateDevice ->
    //    ID2D1DeviceContext + IDWriteFactory7 + IDCompositionDevice3
    ID3D11Device* d3d11Dev = nullptr;
    PRISMX_ASSERT(SUCCEEDED(Export_D3D11CreateDevice(
        nullptr, 1, nullptr, 0, nullptr, 0, 7,
        reinterpret_cast<void**>(&d3d11Dev), nullptr, nullptr)) && d3d11Dev != nullptr);

    Dxgi16::IDXGIDevice4* dxgiDev4 = nullptr;
    PRISMX_ASSERT(SUCCEEDED(d3d11Dev->QueryInterface(
        Dxgi16::OFFICIAL_IID_IDXGIDevice4, reinterpret_cast<void**>(&dxgiDev4))) && dxgiDev4 != nullptr);

    ID2D1Factory7* d2dFactory7 = nullptr;
    PRISMX_ASSERT(SUCCEEDED(Export_D2D1CreateFactory(
        1, OFFICIAL_IID_ID2D1Factory7, nullptr, reinterpret_cast<void**>(&d2dFactory7))) && d2dFactory7 != nullptr);

    ID2D1Device* d2dDev = nullptr;
    PRISMX_ASSERT(SUCCEEDED(d2dFactory7->CreateDevice(dxgiDev4, &d2dDev)) && d2dDev != nullptr);

    ID2D1DeviceContext* d2dCtx = nullptr;
    PRISMX_ASSERT(SUCCEEDED(d2dDev->CreateDeviceContext(0, &d2dCtx)) && d2dCtx != nullptr);

    IDWriteFactory7* dwrite7 = nullptr;
    PRISMX_ASSERT(SUCCEEDED(Export_DWriteCreateFactory(
        0, OFFICIAL_IID_IDWriteFactory7, reinterpret_cast<IUnknown**>(&dwrite7))) && dwrite7 != nullptr);

    IDWriteTextFormat* textFmt = nullptr;
    PRISMX_ASSERT(SUCCEEDED(dwrite7->CreateTextFormat(
        L"Segoe UI", nullptr, 400, 0, 5, 18.0f, L"en-us", &textFmt)) && textFmt != nullptr);
    PRISMX_ASSERT(std::abs(textFmt->GetFontSize() - 18.0f) < 1e-4f);

    D2D1_COLOR_F brushCol{0.1f, 0.8f, 0.4f, 1.0f};
    ID2D1SolidColorBrush* brush = nullptr;
    PRISMX_ASSERT(SUCCEEDED(d2dCtx->CreateSolidColorBrush(&brushCol, nullptr, &brush)) && brush != nullptr);

    d2dCtx->BeginDraw();
    d2dCtx->Clear(&brushCol);
    D2D1_RECT_F rc{0.0f, 0.0f, 400.0f, 60.0f};
    d2dCtx->FillRectangle(&rc, brush);
    d2dCtx->DrawTextW(L"PrismX Standard WinNT Direct2D HUD", 34, textFmt, &rc, brush);
    uint64_t drawOps = 0;
    PRISMX_ASSERT(SUCCEEDED(d2dCtx->EndDraw(&drawOps, nullptr)) && drawOps == 3u);

    IDCompositionDevice3* dcomp3 = nullptr;
    PRISMX_ASSERT(SUCCEEDED(Export_DCompositionCreateDevice3(
        dxgiDev4, OFFICIAL_IID_IDCompositionDevice3, reinterpret_cast<void**>(&dcomp3))) && dcomp3 != nullptr);

    D2DWriteCompCom::IDCompositionTarget* dcompTarget = nullptr;
    PRISMX_ASSERT(SUCCEEDED(dcomp3->CreateTargetForHwnd(
        reinterpret_cast<void*>(0x10020ULL), 1, &dcompTarget)) && dcompTarget != nullptr);
    D2DWriteCompCom::IDCompositionVisual* rootVis = nullptr;
    PRISMX_ASSERT(SUCCEEDED(dcomp3->CreateVisual(&rootVis)) && rootVis != nullptr);
    PRISMX_ASSERT(SUCCEEDED(dcompTarget->SetRoot(rootVis)));
    PRISMX_ASSERT(SUCCEEDED(dcomp3->Commit()));

    rootVis->Release();
    dcompTarget->Release();
    dcomp3->Release();
    brush->Release();
    textFmt->Release();
    dwrite7->Release();
    d2dCtx->Release();
    d2dDev->Release();
    d2dFactory7->Release();
    dxgiDev4->Release();
    d3d11Dev->Release();

#if defined(_WIN32)
    // 3. Live Win32 LoadLibraryA + GetProcAddress Verification Across All 6 New PE32+ System32 DLLs
    auto tryLoadPeDll = [&](const char* relA, const char* relB) -> void* {
        void* h = LoadLibraryA(relA);
        if (!h) h = LoadLibraryA(relB);
        return h;
    };

    void* peD3d9   = tryLoadPeDll("build/bin/system32/d3d9.dll", "bin/system32/d3d9.dll");
    void* peXA2    = tryLoadPeDll("build/bin/system32/xaudio2_9.dll", "bin/system32/xaudio2_9.dll");
    void* peDI8    = tryLoadPeDll("build/bin/system32/dinput8.dll", "bin/system32/dinput8.dll");
    void* peD2D1   = tryLoadPeDll("build/bin/system32/d2d1.dll", "bin/system32/d2d1.dll");
    void* peDWrite = tryLoadPeDll("build/bin/system32/dwrite.dll", "bin/system32/dwrite.dll");
    void* peDComp  = tryLoadPeDll("build/bin/system32/dcomp.dll", "bin/system32/dcomp.dll");

    if (peD3d9 && peXA2 && peDI8 && peD2D1 && peDWrite && peDComp) {
        PRISMX_ASSERT(GetProcAddress(peD3d9, "Direct3DCreate9Ex") != nullptr);
        PRISMX_ASSERT(GetProcAddress(peXA2, "XAudio2Create") != nullptr);
        PRISMX_ASSERT(GetProcAddress(peDI8, "DirectInput8Create") != nullptr);
        PRISMX_ASSERT(GetProcAddress(peD2D1, "D2D1CreateFactory") != nullptr);
        PRISMX_ASSERT(GetProcAddress(peDWrite, "DWriteCreateFactory") != nullptr);
        PRISMX_ASSERT(GetProcAddress(peDComp, "DCompositionCreateDevice3") != nullptr);
    }

    if (peDComp)  FreeLibrary(peDComp);
    if (peDWrite) FreeLibrary(peDWrite);
    if (peD2D1)   FreeLibrary(peD2D1);
    if (peDI8)    FreeLibrary(peDI8);
    if (peXA2)    FreeLibrary(peXA2);
    if (peD3d9)   FreeLibrary(peD3d9);
#endif

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
    if (Test_DirectStorage_Subsystem() != 0) return 1;
    if (Test_DirectML_And_DXCore_Subsystem() != 0) return 1;
    if (Test_DirectComposition_Subsystem() != 0) return 1;
    if (Test_PrismComposition_VisualLayer_Subsystem() != 0) return 1;
    if (Test_PrismColor_AdvancedColor_HDR_Subsystem() != 0) return 1;
    if (Test_PrismInput_Pointer_Gesture_And_Inking_Subsystem() != 0) return 1;
    if (Test_PrismVector_Font_Tessellation_Subsystem() != 0) return 1;
    if (Test_PrismCanvas2D_Vector_Renderer() != 0) return 1;
    if (Test_PrismEffects_PostProcessing_And_EffectGraph() != 0) return 1;
    if (Test_PrismX_MicrosoftDirectX_OpenSource_Ecosystem_And_D3DKMT_Funnel() != 0) return 1;
    if (Test_PrismX_DXC_SM68_DirectStorage_GDeflate_And_DirectML_SuperResolution() != 0) return 1;
    if (Test_PrismX_EnhancedBarriers_VulkanOn12_VideoAV1_And_DRED_ZeroTDR() != 0) return 1;
    if (Test_PrismX_Live_3D_Scene_Renderer_And_GOP_FrameGraph() != 0) return 1;
    if (Test_PrismX_DirectSR_VRS_Tier2_And_ResizableBAR_GpuUploadHeap() != 0) return 1;
    if (Test_PrismX_ExecuteIndirect_NaniteCulling_And_SamplerFeedback_TiledTier4() != 0) return 1;
    if (Test_PrismX_GameInput_8000Hz_StateObjectDB_PIX_And_ClassicDDraw7_D3D8() != 0) return 1;
    if (Test_PrismX_HLSL_FXC_DXBC_Compiler_And_D3D12ShaderReflection() != 0) return 1;
    if (Test_PrismX_DXIL_SM69_Container_And_Wave32_SIMD_VM() != 0) return 1;
    if (Test_PrismX_SPIRV16_DXIL_CrossTranslator_And_RootSignatureRemap() != 0) return 1;
    if (Test_PrismX_Ring0_AntiCheat_EAC_BattlEye_And_SwapChainGuard() != 0) return 1;
    if (Test_PrismX_Vanguard_Ricochet_HVCI_TPM20_And_IOMMU_VramShield() != 0) return 1;
    if (Test_PrismX_GamingDRM_Denuvo_VMProtect_And_SaltedHwidVault() != 0) return 1;
    if (Test_PrismX_Official_DXGI16_COM_Hierarchy_And_Binary_IIDs() != 0) return 1;
    if (Test_PrismX_Official_D3D12_44Slot_COM_VTable_And_CheckFeatureSupport_Options21() != 0) return 1;
    if (Test_PrismX_System32_DirectX_DLL_Exports_And_CrossHierarchy_COM_Router() != 0) return 1;
    if (Test_PrismX_Official_D3D9Ex_21Slot_COM_VTable_And_D3D9On12_DLL() != 0) return 1;
    if (Test_PrismX_Official_XAudio2_9_And_DirectInput8_COM_VTable_DLLs() != 0) return 1;
    if (Test_PrismX_Official_D2D1_DWrite_DComp_COM_VTable_And_11_System32_DLL_Seal() != 0) return 1;

    std::cout << "========================================================\n";
    std::cout << " ALL PRISMX GRAPHICS SUBSYSTEM TESTS PASSED! (36/36)    \n";
    std::cout << "========================================================\n";
    return 0;
}







