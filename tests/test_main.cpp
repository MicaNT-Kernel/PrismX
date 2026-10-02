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

int main() {
    std::cout << "========================================================\n";
    std::cout << "     PrismX Sovereign Graphics Architecture Tests     \n";
    std::cout << "========================================================\n";

    if (Test_DXGI_Infrastructure() != 0) return 1;
    if (Test_Direct3D11_SoftwareRasterizer() != 0) return 1;
    if (Test_Direct3D12_LowLevelPipeline() != 0) return 1;
    if (Test_PrismShaderVM_SIMD() != 0) return 1;
    if (Test_Vulkan13_ICD_Driver() != 0) return 1;

    std::cout << "========================================================\n";
    std::cout << " ALL PRISMX GRAPHICS SUBSYSTEM TESTS PASSED! (5/5 PASS) \n";
    std::cout << "========================================================\n";
    return 0;
}
