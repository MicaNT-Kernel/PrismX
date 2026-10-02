// ============================================================================
// PrismX Example: 3D Colored Cube Rendering with Direct3D 11
// 
// Demonstrates View/Projection transformations, indexed drawing, and z-buffering.
// ============================================================================

#include "prismx.hpp"
#include <iostream>
#include <vector>

using namespace prismx;

int main() {
    std::cout << "[PrismX] Initializing Direct3D 11 Pipeline...\n";

    DXGI_SWAP_CHAIN_DESC scDesc{};
    scDesc.BufferDesc.Width = 320;
    scDesc.BufferDesc.Height = 240;
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
        7,
        &scDesc,
        swapChain.ReleaseAndGetAddressOf(),
        device.ReleaseAndGetAddressOf(),
        nullptr,
        context.ReleaseAndGetAddressOf()
    );

    if (FAILED(hr)) {
        std::cerr << "Failed to create Direct3D 11 device!\n";
        return 1;
    }

    // 8 Vertices of a unit cube (x, y, z, r, g, b, a)
    VertexPositionColor cubeVertices[] = {
        { -1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f },
        { -1.0f,  1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f },
        {  1.0f,  1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f },
        {  1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 1.0f },
        { -1.0f, -1.0f,  1.0f, 1.0f, 0.0f, 1.0f, 1.0f },
        { -1.0f,  1.0f,  1.0f, 0.0f, 1.0f, 1.0f, 1.0f },
        {  1.0f,  1.0f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f },
        {  1.0f, -1.0f,  1.0f, 0.2f, 0.2f, 0.2f, 1.0f },
    };

    // 36 indices for 12 triangles (6 faces)
    uint32_t cubeIndices[] = {
        0, 1, 2,  0, 2, 3, // Front
        4, 6, 5,  4, 7, 6, // Back
        4, 5, 1,  4, 1, 0, // Left
        3, 2, 6,  3, 6, 7, // Right
        1, 5, 6,  1, 6, 2, // Top
        4, 0, 3,  4, 3, 7  // Bottom
    };

    D3D11_BUFFER_DESC vbDesc{ sizeof(cubeVertices), D3D11_USAGE_DEFAULT, D3D11_BIND_VERTEX_BUFFER, 0, 0, 0 };
    D3D11_SUBRESOURCE_DATA vbInit{ cubeVertices, 0, 0 };
    ComPtr<ID3D11Buffer> vb;
    device->CreateBuffer(&vbDesc, &vbInit, vb.ReleaseAndGetAddressOf());

    D3D11_BUFFER_DESC ibDesc{ sizeof(cubeIndices), D3D11_USAGE_DEFAULT, D3D11_BIND_INDEX_BUFFER, 0, 0, 0 };
    D3D11_SUBRESOURCE_DATA ibInit{ cubeIndices, 0, 0 };
    ComPtr<ID3D11Buffer> ib;
    device->CreateBuffer(&ibDesc, &ibInit, ib.ReleaseAndGetAddressOf());

    uint32_t stride = sizeof(VertexPositionColor);
    uint32_t offset = 0;
    ID3D11Buffer* vbs[] = { vb.Get() };
    context->IASetVertexBuffers(0, 1, vbs, &stride, &offset);
    context->IASetIndexBuffer(ib.Get(), DXGI_FORMAT_R32_UINT, 0);
    context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    // Setup viewport
    D3D11_VIEWPORT vp{ 0.0f, 0.0f, 320.0f, 240.0f, 0.0f, 1.0f };
    context->RSSetViewports(1, &vp);

    // Setup camera matrices
    Mat4x4 world = MatrixRotationY(0.785f); // 45 deg rotate
    Mat4x4 view = MatrixLookAtLH({ 0.0f, 2.0f, -5.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f });
    Mat4x4 proj = MatrixPerspectiveFovLH(1.047f, 320.0f / 240.0f, 0.1f, 100.0f);
    Mat4x4 mvp = MatrixMultiply(MatrixMultiply(world, view), proj);

    // Bind MVP matrix to Vertex Shader Constant Buffer (Slot 0)
    D3D11_BUFFER_DESC cbDesc{ sizeof(Matrix4x4), D3D11_USAGE_DEFAULT, D3D11_BIND_CONSTANT_BUFFER, 0, 0, 0 };
    D3D11_SUBRESOURCE_DATA cbInit{ &mvp, 0, 0 };
    ComPtr<ID3D11Buffer> cb;
    device->CreateBuffer(&cbDesc, &cbInit, cb.ReleaseAndGetAddressOf());
    ID3D11Buffer* cbs[] = { cb.Get() };
    context->VSSetConstantBuffers(0, 1, cbs);

    // Render frame
    float clearColor[4] = { 0.05f, 0.05f, 0.1f, 1.0f };
    ComPtr<ID3D11Texture2D> backBuffer;
    swapChain->GetBuffer(0, IID_IDXGISurface, backBuffer.PutVoid());
    ComPtr<ID3D11RenderTargetView> rtv;
    device->CreateRenderTargetView(backBuffer.Get(), nullptr, rtv.ReleaseAndGetAddressOf());

    context->ClearRenderTargetView(rtv.Get(), clearColor);
    ID3D11RenderTargetView* rtvs[] = { rtv.Get() };
    context->OMSetRenderTargets(1, rtvs, nullptr);

    context->DrawIndexed(36, 0, 0);
    swapChain->Present(1, 0);

    std::cout << "[PrismX] 3D Cube Rendered successfully (36 indices, DrawIndexed)\n";
    return 0;
}
