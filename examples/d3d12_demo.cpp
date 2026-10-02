// ============================================================================
// PrismX Example: Direct3D 12 Explicit Low-Level GPU Pipeline
// 
// Demonstrates CommandAllocators, GraphicsCommandLists, Resource Barriers,
// CommandQueue execution, and GPU/CPU Fence synchronization.
// ============================================================================

#include "prismx.hpp"
#include <iostream>

using namespace prismx;

int main() {
    std::cout << "[PrismX] Initializing Direct3D 12 Low-Level Pipeline...\n";

    ComPtr<ID3D12Device> device;
    HRESULT hr = D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_12_0, IID_ID3D12Device, device.PutVoid());
    if (FAILED(hr)) {
        std::cerr << "Failed to create Direct3D 12 Device!\n";
        return 1;
    }

    // Create Direct Command Queue
    D3D12_COMMAND_QUEUE_DESC qDesc{};
    qDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
    qDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
    ComPtr<ID3D12CommandQueue> commandQueue;
    device->CreateCommandQueue(&qDesc, IID_ID3D12CommandQueue, commandQueue.PutVoid());

    // Create Command Allocator
    ComPtr<ID3D12CommandAllocator> commandAlloc;
    device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_ID3D12CommandAllocator, commandAlloc.PutVoid());

    // Create Graphics Command List
    ComPtr<ID3D12GraphicsCommandList> commandList;
    device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, commandAlloc.Get(), nullptr, IID_ID3D12GraphicsCommandList, commandList.PutVoid());

    // Create GPU/CPU Synchronization Fence
    ComPtr<ID3D12Fence> fence;
    device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_ID3D12Fence, fence.PutVoid());

    // Create Texture2D Render Target Resource
    D3D12_HEAP_PROPERTIES heapProps{};
    heapProps.Type = D3D12_HEAP_TYPE_DEFAULT;
    D3D12_RESOURCE_DESC resDesc{};
    resDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
    resDesc.Width = 1920;
    resDesc.Height = 1080;
    resDesc.DepthOrArraySize = 1;
    resDesc.MipLevels = 1;
    resDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
    resDesc.SampleDesc = { 1, 0 };
    resDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
    resDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET;

    ComPtr<ID3D12Resource> renderTarget;
    device->CreateCommittedResource(&heapProps, D3D12_HEAP_FLAG_NONE, &resDesc, D3D12_RESOURCE_STATE_PRESENT, nullptr, IID_ID3D12Resource, renderTarget.PutVoid());

    // 1. Record Barrier: PRESENT -> RENDER_TARGET
    D3D12_RESOURCE_BARRIER barrier{};
    barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    barrier.Transition.pResource = renderTarget.Get();
    barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
    barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
    commandList->ResourceBarrier(1, &barrier);

    // 2. Clear Render Target
    float clearColor[4] = { 0.1f, 0.2f, 0.4f, 1.0f };
    D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle{ 0x1000 };
    commandList->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);

    // 3. Record Barrier: RENDER_TARGET -> PRESENT
    barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
    barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
    commandList->ResourceBarrier(1, &barrier);

    // Close command list
    commandList->Close();

    // Execute recorded commands
    ID3D12CommandList* const ppCmdLists[] = { commandList.Get() };
    commandQueue->ExecuteCommandLists(1, ppCmdLists);

    // Signal fence for frame synchronization
    commandQueue->Signal(fence.Get(), 1);

    std::cout << "[PrismX] Direct3D 12 Commands executed. Fence value: " 
              << fence->GetCompletedValue() << "\n";
    return 0;
}
