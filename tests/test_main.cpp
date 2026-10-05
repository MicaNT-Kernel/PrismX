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

    std::cout << "========================================================\n";
    std::cout << " ALL PRISMX GRAPHICS SUBSYSTEM TESTS PASSED! (12/12)    \n";
    std::cout << "========================================================\n";
    return 0;
}


