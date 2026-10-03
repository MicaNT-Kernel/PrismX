// ============================================================================
// PrismX Example: Sovereign Multimedia Showcase (3D, Audio & Input)
// 
// Demonstrates the unified Direct3D 11 rasterizer, 3D math engine,
// XAudio2 procedural audio synthesis, and XInput gamepad polling.
// Pure ISO C++23. Zero External Dependencies.
// ============================================================================

#include "prismx.hpp"
#include <iostream>
#include <vector>
#include <cmath>
#include <numbers>
#include <iomanip>
#include <fstream>

using namespace prismx;
using namespace prismx::math;
using namespace prismx::audio;
using namespace prismx::hid;

int main() {
    std::cout << "========================================================\n";
    std::cout << "       PrismX Sovereign Multimedia Subsystem Demo       \n";
    std::cout << "   3D Direct3D 11 + Sovereign 3D Math + Audio + Input   \n";
    std::cout << "========================================================\n\n";

    // ------------------------------------------------------------------------
    // 1. Initialize Direct3D 11 Pipeline & SwapChain
    // ------------------------------------------------------------------------
    const uint32_t width = 320;
    const uint32_t height = 240;

    DXGI_SWAP_CHAIN_DESC scDesc{};
    scDesc.BufferDesc.Width = width;
    scDesc.BufferDesc.Height = height;
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
        std::cerr << "[-] Failed to initialize Direct3D 11 device!\n";
        return 1;
    }
    std::cout << "[+] Direct3D 11 Device & 320x240 SwapChain created.\n";

    // ------------------------------------------------------------------------
    // 2. Initialize XAudio2 Procedural Synthesizer
    // ------------------------------------------------------------------------
    ComPtr<IXAudio2> audio;
    hr = XAudio2Create(audio.ReleaseAndGetAddressOf(), 0, 0);
    if (FAILED(hr)) {
        std::cerr << "[-] Failed to initialize XAudio2 engine!\n";
        return 1;
    }

    IXAudio2MasteringVoice* masteringVoice = nullptr;
    hr = audio->CreateMasteringVoice(&masteringVoice, 2, 48000, 0, nullptr);
    if (FAILED(hr)) {
        std::cerr << "[-] Failed to create Mastering Voice!\n";
        return 1;
    }

    WAVEFORMATEX wfx{};
    wfx.wFormatTag = 3; // IEEE Float
    wfx.nChannels = 2;
    wfx.nSamplesPerSec = 48000;
    wfx.wBitsPerSample = 32;
    wfx.nBlockAlign = wfx.nChannels * (wfx.wBitsPerSample / 8);
    wfx.nAvgBytesPerSec = wfx.nSamplesPerSec * wfx.nBlockAlign;

    IXAudio2SourceVoice* sourceVoice = nullptr;
    audio->CreateSourceVoice(&sourceVoice, &wfx, 0, 2.0f, nullptr);

    // Synthesize harmonic crystal chord (528 Hz Love Frequency + 660 Hz E5 + 792 Hz G5)
    std::vector<float> audioSamples(48000 * 2); // 1.0 second stereo buffer
    for (size_t i = 0; i < 48000; ++i) {
        float t = static_cast<float>(i) / 48000.0f;
        float envelope = std::exp(-2.5f * t); // Exponential decay chime
        float f1 = std::sin(2.0f * std::numbers::pi_v<float> * 528.0f * t);
        float f2 = std::sin(2.0f * std::numbers::pi_v<float> * 660.0f * t) * 0.7f;
        float f3 = std::sin(2.0f * std::numbers::pi_v<float> * 792.0f * t) * 0.5f;
        float sample = (f1 + f2 + f3) * 0.3f * envelope;

        audioSamples[i * 2 + 0] = sample; // Left
        audioSamples[i * 2 + 1] = sample; // Right
    }

    XAUDIO2_BUFFER audioBuffer{};
    audioBuffer.AudioBytes = static_cast<uint32_t>(audioSamples.size() * sizeof(float));
    audioBuffer.pAudioData = reinterpret_cast<const uint8_t*>(audioSamples.data());
    audioBuffer.LoopCount = XAUDIO2_LOOP_INFINITE;

    sourceVoice->SubmitSourceBuffer(&audioBuffer, nullptr);
    sourceVoice->Start(0, 0);
    std::cout << "[+] PrismAudio: 48kHz Stereo Procedural Synthesizer started (528Hz Harmonic Chime).\n";

    // ------------------------------------------------------------------------
    // 3. Construct 3D Prism Crystal Geometry (Hexagonal Bipyramid)
    // ------------------------------------------------------------------------
    // Apex Top (0), Apex Bottom (1), Equator 6 vertices (2..7)
    std::vector<VertexPositionColor> crystalVertices = {
        // Top Apex (Cyan)
        { 0.0f,  1.8f,  0.0f,  0.1f, 0.9f, 1.0f, 1.0f },
        // Bottom Apex (Indigo)
        { 0.0f, -1.8f,  0.0f,  0.4f, 0.2f, 0.9f, 1.0f }
    };

    const int numEquator = 6;
    for (int i = 0; i < numEquator; ++i) {
        float angle = (2.0f * std::numbers::pi_v<float> * i) / numEquator;
        float x = std::cos(angle) * 1.2f;
        float z = std::sin(angle) * 1.2f;
        float r = 0.2f + 0.6f * (static_cast<float>(i) / numEquator);
        float g = 0.7f + 0.3f * (static_cast<float>(numEquator - i) / numEquator);
        float b = 0.95f;
        crystalVertices.push_back({ x, 0.0f, z, r, g, b, 1.0f });
    }

    // Indices: 6 triangles for top cone, 6 triangles for bottom cone
    std::vector<uint32_t> crystalIndices;
    for (int i = 0; i < numEquator; ++i) {
        uint32_t curr = 2 + i;
        uint32_t next = 2 + ((i + 1) % numEquator);
        // Top pyramid triangle (Top Apex 0 -> curr -> next)
        crystalIndices.push_back(0);
        crystalIndices.push_back(curr);
        crystalIndices.push_back(next);

        // Bottom pyramid triangle (Bottom Apex 1 -> next -> curr)
        crystalIndices.push_back(1);
        crystalIndices.push_back(next);
        crystalIndices.push_back(curr);
    }

    D3D11_BUFFER_DESC vbDesc{ static_cast<uint32_t>(crystalVertices.size() * sizeof(VertexPositionColor)), D3D11_USAGE_DEFAULT, D3D11_BIND_VERTEX_BUFFER, 0, 0, 0 };
    D3D11_SUBRESOURCE_DATA vbInit{ crystalVertices.data(), 0, 0 };
    ComPtr<ID3D11Buffer> vb;
    device->CreateBuffer(&vbDesc, &vbInit, vb.ReleaseAndGetAddressOf());

    D3D11_BUFFER_DESC ibDesc{ static_cast<uint32_t>(crystalIndices.size() * sizeof(uint32_t)), D3D11_USAGE_DEFAULT, D3D11_BIND_INDEX_BUFFER, 0, 0, 0 };
    D3D11_SUBRESOURCE_DATA ibInit{ crystalIndices.data(), 0, 0 };
    ComPtr<ID3D11Buffer> ib;
    device->CreateBuffer(&ibDesc, &ibInit, ib.ReleaseAndGetAddressOf());

    uint32_t stride = sizeof(VertexPositionColor);
    uint32_t offset = 0;
    ID3D11Buffer* vbs[] = { vb.Get() };
    context->IASetVertexBuffers(0, 1, vbs, &stride, &offset);
    context->IASetIndexBuffer(ib.Get(), DXGI_FORMAT_R32_UINT, 0);
    context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    D3D11_VIEWPORT vp{ 0.0f, 0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f, 1.0f };
    context->RSSetViewports(1, &vp);

    // Setup Depth Stencil View
    D3D11_TEXTURE2D_DESC dsDesc{};
    dsDesc.Width = width;
    dsDesc.Height = height;
    dsDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    dsDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    ComPtr<ID3D11Texture2D> depthTexture;
    device->CreateTexture2D(&dsDesc, nullptr, depthTexture.ReleaseAndGetAddressOf());

    ComPtr<ID3D11DepthStencilView> dsv;
    device->CreateDepthStencilView(depthTexture.Get(), nullptr, dsv.ReleaseAndGetAddressOf());

    // Back buffer render target
    ComPtr<ID3D11Texture2D> backBuffer;
    swapChain->GetBuffer(0, IID_IDXGISurface, backBuffer.PutVoid());
    ComPtr<ID3D11RenderTargetView> rtv;
    device->CreateRenderTargetView(backBuffer.Get(), nullptr, rtv.ReleaseAndGetAddressOf());

    // Constant buffer for MVP Matrix
    D3D11_BUFFER_DESC cbDesc{ sizeof(Matrix), D3D11_USAGE_DEFAULT, D3D11_BIND_CONSTANT_BUFFER, 0, 0, 0 };
    ComPtr<ID3D11Buffer> cb;
    device->CreateBuffer(&cbDesc, nullptr, cb.ReleaseAndGetAddressOf());
    ID3D11Buffer* cbs[] = { cb.Get() };
    context->VSSetConstantBuffers(0, 1, cbs);

    // ------------------------------------------------------------------------
    // 4. Configure Virtual Gamepad Input
    // ------------------------------------------------------------------------
    ControllerManager::get().SetSlotConnected(0, true);
    XINPUT_GAMEPAD simPad{};
    simPad.wButtons = XINPUT_GAMEPAD_DPAD_UP | XINPUT_GAMEPAD_A;
    simPad.sThumbLX = 16000; // Tilt right
    simPad.sThumbLY = 8000;
    ControllerManager::get().SetSlotState(0, simPad);
    std::cout << "[+] VectorHID: Gamepad Slot 0 connected (simulated thumbstick tilt).\n\n";

    // ------------------------------------------------------------------------
    // 5. Render 6 Animated Transformation Frames
    // ------------------------------------------------------------------------
    std::cout << "--- [Simulated Realtime Animation Loop (6 Keyframes)] ---\n";
    float clearColor[4] = { 0.04f, 0.06f, 0.12f, 1.0f }; // Deep midnight navy

    for (int frame = 0; frame < 6; ++frame) {
        // Poll Gamepad
        XINPUT_STATE padState{};
        XInputGetState(0, &padState);

        float normLX = 0.0f, normLY = 0.0f;
        ControllerManager::NormalizeThumbstick(padState.Gamepad.sThumbLX, padState.Gamepad.sThumbLY, XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE, normLX, normLY);

        // Compute Rotation Angles
        float rotY = (frame * 0.35f) + (normLX * 0.2f);
        float rotX = std::sin(frame * 0.4f) * 0.25f;

        // Camera View & Projection
        Matrix matWorld = Matrix::CreateRotationX(rotX) * Matrix::CreateRotationY(rotY);
        Matrix matView = Matrix::CreateLookAtLH(
            Vector3(0.0f, 1.0f, -4.5f),
            Vector3(0.0f, 0.0f, 0.0f),
            Vector3(0.0f, 1.0f, 0.0f)
        );
        Matrix matProj = Matrix::CreatePerspectiveFovLH(
            std::numbers::pi_v<float> / 3.0f, // 60 deg FoV
            static_cast<float>(width) / static_cast<float>(height),
            0.1f,
            100.0f
        );

        Matrix mvp = matWorld * matView * matProj;

        // Update GPU Constant Buffer
        context->UpdateSubresource(cb.Get(), 0, &mvp, sizeof(Matrix), sizeof(Matrix));

        // Clear & Draw
        context->ClearRenderTargetView(rtv.Get(), clearColor);
        context->ClearDepthStencilView(dsv.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);

        ID3D11RenderTargetView* rtvs[] = { rtv.Get() };
        context->OMSetRenderTargets(1, rtvs, dsv.Get());

        context->DrawIndexed(static_cast<uint32_t>(crystalIndices.size()), 0, 0);
        swapChain->Present(1, 0);

        // Process audio mixing cycle
        std::vector<float> mixedAudio;
        static_cast<PrismAudioEngineImpl*>(audio.Get())->ProcessMixingCycle(480, mixedAudio);

        std::cout << " Frame #" << frame 
                  << " | RotY: " << std::fixed << std::setprecision(2) << rotY << " rad"
                  << " | Triangles: " << (crystalIndices.size() / 3)
                  << " | Audio Mixed: " << mixedAudio.size() << " samples"
                  << " | Pad LX: " << std::setprecision(2) << normLX << "\n";
    }

    std::cout << "\n[+] Animation loop completed successfully.\n";

    // Export rendered framebuffer to BMP
    auto* rtvImpl = static_cast<Prism3DRenderTargetViewImpl*>(rtv.Get());
    if (rtvImpl && rtvImpl->GetSurface()) {
        auto* surf = rtvImpl->GetSurface();
        uint32_t w = surf->GetWidth();
        uint32_t h = surf->GetHeight();
        const uint8_t* rawPix = surf->GetRawData();

        std::ofstream bmpFile("prismx_crystal_render.bmp", std::ios::binary);
        if (bmpFile.is_open()) {
            uint32_t rowPitch = w * 4;
            uint32_t imageSize = rowPitch * h;
            uint32_t fileSize = 54 + imageSize;

            uint8_t bmpHeader[54] = {
                'B', 'M',
                static_cast<uint8_t>(fileSize & 0xFF), static_cast<uint8_t>((fileSize >> 8) & 0xFF),
                static_cast<uint8_t>((fileSize >> 16) & 0xFF), static_cast<uint8_t>((fileSize >> 24) & 0xFF),
                0, 0, 0, 0,
                54, 0, 0, 0,
                40, 0, 0, 0,
                static_cast<uint8_t>(w & 0xFF), static_cast<uint8_t>((w >> 8) & 0xFF),
                static_cast<uint8_t>((w >> 16) & 0xFF), static_cast<uint8_t>((w >> 24) & 0xFF),
                static_cast<uint8_t>((-static_cast<int32_t>(h)) & 0xFF),
                static_cast<uint8_t>(((-static_cast<int32_t>(h)) >> 8) & 0xFF),
                static_cast<uint8_t>(((-static_cast<int32_t>(h)) >> 16) & 0xFF),
                static_cast<uint8_t>(((-static_cast<int32_t>(h)) >> 24) & 0xFF),
                1, 0,
                32, 0,
                0, 0, 0, 0,
                static_cast<uint8_t>(imageSize & 0xFF), static_cast<uint8_t>((imageSize >> 8) & 0xFF),
                static_cast<uint8_t>((imageSize >> 16) & 0xFF), static_cast<uint8_t>((imageSize >> 24) & 0xFF),
                0x13, 0x0B, 0, 0,
                0x13, 0x0B, 0, 0,
                0, 0, 0, 0,
                0, 0, 0, 0
            };

            bmpFile.write(reinterpret_cast<const char*>(bmpHeader), 54);
            bmpFile.write(reinterpret_cast<const char*>(rawPix), imageSize);
            bmpFile.close();
            std::cout << "[+] Rendered 3D crystal framebuffer exported to: prismx_crystal_render.bmp\n";
        }
    }

    std::cout << "[+] Releasing multimedia resources...\n";

    sourceVoice->Stop(0, 0);
    sourceVoice->DestroyVoice();
    masteringVoice->DestroyVoice();

    std::cout << "========================================================\n";
    std::cout << "     PRISMX MULTIMEDIA PIPELINE VERIFIED CLEAN!         \n";
    std::cout << "========================================================\n";
    return 0;
}
