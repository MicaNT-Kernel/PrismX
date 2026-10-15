#pragma once

#include "types.hpp"
#include "dxgi1_6_com_abi.hpp"
#include "d3d9_com_vtable_abi.hpp"
#include "xaudio2_dinput8_com_abi.hpp"
#include "mfplat_mfreadwrite_com_abi.hpp"
#include <cstdint>
#include <cstring>

namespace prismx::D3D10DSoundDDrawMFCom {

// ============================================================================
// PrismX Suite 41 — Standard D3D10.1 (d3d10_1.dll), DirectSound8 (dsound.dll),
// DirectDraw7 (ddraw.dll) & Media Foundation Session/Topology (mf.dll) COM ABI
// ============================================================================

// --- 1. d3d10_1.dll / d3d10.dll Standard Constants & COM Interfaces ---
inline constexpr uint32_t D3D10_SDK_VERSION          = 29;
inline constexpr uint32_t D3D10_1_SDK_VERSION        = 0x20;
inline constexpr uint32_t D3D10_DRIVER_TYPE_HARDWARE = 1;
inline constexpr uint32_t D3D10_FEATURE_LEVEL_10_0   = 0xa000;
inline constexpr uint32_t D3D10_FEATURE_LEVEL_10_1   = 0xa100;

inline constexpr IID OFFICIAL_IID_ID3D10Device = {
    0x9B7E4C0F, 0x342C, 0x4106, {0xA1, 0x9F, 0x4F, 0x27, 0x04, 0xF6, 0x89, 0xF0}
};
inline constexpr IID OFFICIAL_IID_ID3D10Device1 = {
    0x9B7E4C8F, 0x342C, 0x4106, {0xA1, 0x9F, 0x4F, 0x27, 0x04, 0xF6, 0x89, 0xF0}
};

struct ID3D10Device : public IUnknown {
    virtual void VSSetConstantBuffers(uint32_t StartSlot, uint32_t NumBuffers, void* const* ppConstantBuffers) = 0;
    virtual void PSSetShaderResources(uint32_t StartSlot, uint32_t NumViews, void* const* ppShaderResourceViews) = 0;
    virtual void PSSetShader(void* pPixelShader) = 0;
    virtual void PSSetSamplers(uint32_t StartSlot, uint32_t NumSamplers, void* const* ppSamplers) = 0;
    virtual void VSSetShader(void* pVertexShader) = 0;
    virtual void DrawIndexed(uint32_t IndexCount, uint32_t StartIndexLocation, int32_t BaseVertexLocation) = 0;
    virtual void Draw(uint32_t VertexCount, uint32_t StartVertexLocation) = 0;
    virtual void ClearRenderTargetView(void* pRenderTargetView, const float ColorRGBA[4]) = 0;
    virtual void Flush() = 0;
};

struct ID3D10Device1 : public ID3D10Device {
    virtual uint32_t GetFeatureLevel() = 0;
};

class PrismD3D10Device1 final : public ID3D10Device1 {
    uint32_t m_featureLevel = D3D10_FEATURE_LEVEL_10_1;
    uint32_t m_drawCalls    = 0;
    uint32_t m_flushes      = 0;
    float    m_clearColor[4]{0.0f, 0.0f, 0.0f, 1.0f};
    Dxgi16::PrismDXGIDevice4Impl m_dxgiDevice{};

public:
    explicit PrismD3D10Device1(uint32_t featureLevel = D3D10_FEATURE_LEVEL_10_1)
        : m_featureLevel(featureLevel) {}

    HRESULT QueryInterface(const IID& riid, void** ppvObject) override {
        if (!ppvObject) return E_POINTER;
        if (riid == IID_IUnknown || riid == OFFICIAL_IID_ID3D10Device || riid == OFFICIAL_IID_ID3D10Device1) {
            *ppvObject = static_cast<ID3D10Device1*>(this);
            return S_OK;
        }
        if (riid == IID_IDXGIDevice || riid == Dxgi16::OFFICIAL_IID_IDXGIDevice ||
            riid == Dxgi16::OFFICIAL_IID_IDXGIDevice1 || riid == Dxgi16::OFFICIAL_IID_IDXGIDevice4) {
            *ppvObject = static_cast<Dxgi16::IDXGIDevice4*>(&m_dxgiDevice);
            return S_OK;
        }
        *ppvObject = nullptr;
        return E_NOINTERFACE;
    }
    uint32_t AddRef() override { return 1; }
    uint32_t Release() override { return 1; }

    void VSSetConstantBuffers(uint32_t, uint32_t, void* const*) override {}
    void PSSetShaderResources(uint32_t, uint32_t, void* const*) override {}
    void PSSetShader(void*) override {}
    void PSSetSamplers(uint32_t, uint32_t, void* const*) override {}
    void VSSetShader(void*) override {}
    void DrawIndexed(uint32_t, uint32_t, int32_t) override { ++m_drawCalls; }
    void Draw(uint32_t, uint32_t) override { ++m_drawCalls; }
    void ClearRenderTargetView(void*, const float ColorRGBA[4]) override {
        if (ColorRGBA) {
            for (int i = 0; i < 4; ++i) m_clearColor[i] = ColorRGBA[i];
        }
    }
    void Flush() override { ++m_flushes; }
    uint32_t GetFeatureLevel() override { return m_featureLevel; }
};

inline PrismD3D10Device1& GetGlobalD3D10Device1() {
    static PrismD3D10Device1 s_dev{};
    return s_dev;
}

inline HRESULT D3D10CreateDevice1(IDXGIAdapter* pAdapter, uint32_t DriverType,
                                  void* Software, uint32_t Flags,
                                  uint32_t HardwareLevel, uint32_t SDKVersion,
                                  ID3D10Device1** ppDevice) {
    (void)pAdapter; (void)DriverType; (void)Software; (void)Flags; (void)SDKVersion;
    if (!ppDevice) return E_INVALIDARG;
    *ppDevice = &GetGlobalD3D10Device1();
    (void)HardwareLevel;
    return S_OK;
}

inline HRESULT D3D10CreateDeviceAndSwapChain1(IDXGIAdapter* pAdapter, uint32_t DriverType,
                                              void* Software, uint32_t Flags,
                                              uint32_t HardwareLevel, uint32_t SDKVersion,
                                              const void* pSwapChainDesc,
                                              IDXGISwapChain** ppSwapChain,
                                              ID3D10Device1** ppDevice) {
    HRESULT hr = D3D10CreateDevice1(pAdapter, DriverType, Software, Flags, HardwareLevel, SDKVersion, ppDevice);
    if (hr < 0) return hr;
    if (ppSwapChain) {
        Dxgi16::DXGI_SWAP_CHAIN_DESC1 desc1{};
        desc1.Width = 1920;
        desc1.Height = 1080;
        desc1.BufferCount = 2;
        static Dxgi16::PrismDXGISwapChain4Impl s_swapChain(nullptr, desc1);
        (void)pSwapChainDesc;
        *ppSwapChain = &s_swapChain;
    }
    return S_OK;
}

inline HRESULT D3D10CreateDevice(IDXGIAdapter* pAdapter, uint32_t DriverType,
                                 void* Software, uint32_t Flags,
                                 uint32_t SDKVersion, ID3D10Device** ppDevice) {
    ID3D10Device1* dev1 = nullptr;
    HRESULT hr = D3D10CreateDevice1(pAdapter, DriverType, Software, Flags, D3D10_FEATURE_LEVEL_10_0, SDKVersion, &dev1);
    if (hr >= 0 && ppDevice) *ppDevice = dev1;
    return hr;
}

// --- 2. dsound.dll Standard DirectSound8 COM Interfaces ---
inline constexpr uint32_t DSSCL_NORMAL       = 0x00000001;
inline constexpr uint32_t DSSCL_PRIORITY     = 0x00000002;
inline constexpr uint32_t DSSCL_EXCLUSIVE    = 0x00000003;
inline constexpr uint32_t DSSCL_WRITEPRIMARY = 0x00000004;
inline constexpr uint32_t DSBPLAY_LOOPING    = 0x00000001;
inline constexpr uint32_t DSBSTATUS_PLAYING  = 0x00000001;
inline constexpr uint32_t DSBSTATUS_LOOPING  = 0x00000004;

inline constexpr IID OFFICIAL_IID_IDirectSound8 = {
    0xC50A7E93, 0xF395, 0x4834, {0x9E, 0xF6, 0x7F, 0xA9, 0x9D, 0xE5, 0x09, 0x66}
};
inline constexpr IID OFFICIAL_IID_IDirectSoundBuffer8 = {
    0x6825A449, 0x7524, 0x4D82, {0x92, 0x0F, 0x50, 0xE3, 0x6A, 0xB3, 0xAB, 0x1E}
};

struct DSBUFFERDESC {
    uint32_t dwSize;
    uint32_t dwFlags;
    uint32_t dwBufferBytes;
    uint32_t dwReserved;
    void*    lpwfxFormat;
    IID      guid3DAlgorithm;
};

struct IDirectSoundBuffer8 : public IUnknown {
    virtual HRESULT GetCaps(void* pDSBufferCaps) = 0;
    virtual HRESULT GetCurrentPosition(uint32_t* pdwCurrentPlayCursor, uint32_t* pdwCurrentWriteCursor) = 0;
    virtual HRESULT GetFormat(void* pwfxFormat, uint32_t dwSizeAllocated, uint32_t* pdwSizeWritten) = 0;
    virtual HRESULT GetVolume(int32_t* plVolume) = 0;
    virtual HRESULT GetPan(int32_t* plPan) = 0;
    virtual HRESULT GetFrequency(uint32_t* pdwFrequency) = 0;
    virtual HRESULT GetStatus(uint32_t* pdwStatus) = 0;
    virtual HRESULT Initialize(void* pDirectSound, const DSBUFFERDESC* pcDSBufferDesc) = 0;
    virtual HRESULT Lock(uint32_t dwOffset, uint32_t dwBytes, void** ppvAudioPtr1, uint32_t* pdwAudioBytes1,
                         void** ppvAudioPtr2, uint32_t* pdwAudioBytes2, uint32_t dwFlags) = 0;
    virtual HRESULT Play(uint32_t dwReserved1, uint32_t dwPriority, uint32_t dwFlags) = 0;
    virtual HRESULT SetCurrentPosition(uint32_t dwNewPosition) = 0;
    virtual HRESULT SetFormat(const void* pcfxFormat) = 0;
    virtual HRESULT SetVolume(int32_t lVolume) = 0;
    virtual HRESULT SetPan(int32_t lPan) = 0;
    virtual HRESULT SetFrequency(uint32_t dwFrequency) = 0;
    virtual HRESULT Stop() = 0;
    virtual HRESULT Unlock(void* pvAudioPtr1, uint32_t dwAudioBytes1, void* pvAudioPtr2, uint32_t dwAudioBytes2) = 0;
    virtual HRESULT Restore() = 0;
};

struct IDirectSound8 : public IUnknown {
    virtual HRESULT CreateSoundBuffer(const DSBUFFERDESC* pcDSBufferDesc, IDirectSoundBuffer8** ppDSBuffer, IUnknown* pUnkOuter) = 0;
    virtual HRESULT GetCaps(void* pDSCaps) = 0;
    virtual HRESULT DuplicateSoundBuffer(IDirectSoundBuffer8* pDSBufferOriginal, IDirectSoundBuffer8** ppDSBufferDuplicate) = 0;
    virtual HRESULT SetCooperativeLevel(void* hwnd, uint32_t dwLevel) = 0;
    virtual HRESULT Compact() = 0;
    virtual HRESULT GetSpeakerConfig(uint32_t* pdwSpeakerConfig) = 0;
    virtual HRESULT SetSpeakerConfig(uint32_t dwSpeakerConfig) = 0;
    virtual HRESULT Initialize(const IID* pcGuidDevice) = 0;
    virtual HRESULT VerifyCertification(uint32_t* pdwCertified) = 0;
};

class PrismDirectSoundBuffer8 final : public IDirectSoundBuffer8 {
    alignas(16) uint8_t m_pcmRing[65536]{};
    uint32_t m_bufferBytes = 65536;
    uint32_t m_playCursor  = 0;
    uint32_t m_writeCursor = 1920; // 10ms @ 48kHz stereo 16-bit
    uint32_t m_frequency   = 48000;
    int32_t  m_volume      = 0;    // 0 dB (DSBVOLUME_MAX)
    int32_t  m_pan         = 0;    // DSBPAN_CENTER
    uint32_t m_status      = 0;

public:
    void Configure(uint32_t bytes) {
        m_bufferBytes = (bytes > 0 && bytes <= sizeof(m_pcmRing)) ? bytes : sizeof(m_pcmRing);
    }

    HRESULT QueryInterface(const IID& riid, void** ppvObject) override {
        if (!ppvObject) return E_POINTER;
        if (riid == IID_IUnknown || riid == OFFICIAL_IID_IDirectSoundBuffer8) {
            *ppvObject = static_cast<IDirectSoundBuffer8*>(this);
            return S_OK;
        }
        *ppvObject = nullptr;
        return E_NOINTERFACE;
    }
    uint32_t AddRef() override { return 1; }
    uint32_t Release() override { return 1; }

    HRESULT GetCaps(void*) override { return S_OK; }
    HRESULT GetCurrentPosition(uint32_t* pdwCurrentPlayCursor, uint32_t* pdwCurrentWriteCursor) override {
        if (pdwCurrentPlayCursor) *pdwCurrentPlayCursor = m_playCursor;
        if (pdwCurrentWriteCursor) *pdwCurrentWriteCursor = m_writeCursor;
        return S_OK;
    }
    HRESULT GetFormat(void*, uint32_t, uint32_t* pdwSizeWritten) override {
        if (pdwSizeWritten) *pdwSizeWritten = 18;
        return S_OK;
    }
    HRESULT GetVolume(int32_t* plVolume) override {
        if (!plVolume) return E_POINTER;
        *plVolume = m_volume;
        return S_OK;
    }
    HRESULT GetPan(int32_t* plPan) override {
        if (!plPan) return E_POINTER;
        *plPan = m_pan;
        return S_OK;
    }
    HRESULT GetFrequency(uint32_t* pdwFrequency) override {
        if (!pdwFrequency) return E_POINTER;
        *pdwFrequency = m_frequency;
        return S_OK;
    }
    HRESULT GetStatus(uint32_t* pdwStatus) override {
        if (!pdwStatus) return E_POINTER;
        *pdwStatus = m_status;
        return S_OK;
    }
    HRESULT Initialize(void*, const DSBUFFERDESC* pcDSBufferDesc) override {
        if (pcDSBufferDesc) Configure(pcDSBufferDesc->dwBufferBytes);
        return S_OK;
    }
    HRESULT Lock(uint32_t dwOffset, uint32_t dwBytes, void** ppvAudioPtr1, uint32_t* pdwAudioBytes1,
                 void** ppvAudioPtr2, uint32_t* pdwAudioBytes2, uint32_t) override {
        if (!ppvAudioPtr1 || !pdwAudioBytes1) return E_INVALIDARG;
        uint32_t off = dwOffset % m_bufferBytes;
        uint32_t len = (dwBytes > 0 && dwBytes <= m_bufferBytes - off) ? dwBytes : (m_bufferBytes - off);
        *ppvAudioPtr1 = &m_pcmRing[off];
        *pdwAudioBytes1 = len;
        if (ppvAudioPtr2) *ppvAudioPtr2 = nullptr;
        if (pdwAudioBytes2) *pdwAudioBytes2 = 0;
        return S_OK;
    }
    HRESULT Play(uint32_t, uint32_t, uint32_t dwFlags) override {
        m_status = DSBSTATUS_PLAYING | ((dwFlags & DSBPLAY_LOOPING) ? DSBSTATUS_LOOPING : 0u);
        return S_OK;
    }
    HRESULT SetCurrentPosition(uint32_t dwNewPosition) override {
        m_playCursor = dwNewPosition % m_bufferBytes;
        return S_OK;
    }
    HRESULT SetFormat(const void*) override { return S_OK; }
    HRESULT SetVolume(int32_t lVolume) override { m_volume = lVolume; return S_OK; }
    HRESULT SetPan(int32_t lPan) override { m_pan = lPan; return S_OK; }
    HRESULT SetFrequency(uint32_t dwFrequency) override { m_frequency = dwFrequency; return S_OK; }
    HRESULT Stop() override { m_status = 0; return S_OK; }
    HRESULT Unlock(void*, uint32_t dwAudioBytes1, void*, uint32_t) override {
        m_writeCursor = (m_writeCursor + dwAudioBytes1) % m_bufferBytes;
        return S_OK;
    }
    HRESULT Restore() override { return S_OK; }
};

class PrismDirectSound8 final : public IDirectSound8 {
    PrismDirectSoundBuffer8 m_primaryBuffer{};
    void*    m_hwnd      = nullptr;
    uint32_t m_coopLevel = DSSCL_PRIORITY;

public:
    HRESULT QueryInterface(const IID& riid, void** ppvObject) override {
        if (!ppvObject) return E_POINTER;
        if (riid == IID_IUnknown || riid == OFFICIAL_IID_IDirectSound8) {
            *ppvObject = static_cast<IDirectSound8*>(this);
            return S_OK;
        }
        *ppvObject = nullptr;
        return E_NOINTERFACE;
    }
    uint32_t AddRef() override { return 1; }
    uint32_t Release() override { return 1; }

    HRESULT CreateSoundBuffer(const DSBUFFERDESC* pcDSBufferDesc, IDirectSoundBuffer8** ppDSBuffer, IUnknown*) override {
        if (!pcDSBufferDesc || !ppDSBuffer) return E_INVALIDARG;
        m_primaryBuffer.Configure(pcDSBufferDesc->dwBufferBytes);
        *ppDSBuffer = &m_primaryBuffer;
        return S_OK;
    }
    HRESULT GetCaps(void*) override { return S_OK; }
    HRESULT DuplicateSoundBuffer(IDirectSoundBuffer8* pOriginal, IDirectSoundBuffer8** ppDuplicate) override {
        if (!pOriginal || !ppDuplicate) return E_INVALIDARG;
        *ppDuplicate = pOriginal;
        return S_OK;
    }
    HRESULT SetCooperativeLevel(void* hwnd, uint32_t dwLevel) override {
        m_hwnd = hwnd;
        m_coopLevel = dwLevel;
        return S_OK;
    }
    HRESULT Compact() override { return S_OK; }
    HRESULT GetSpeakerConfig(uint32_t* pdwSpeakerConfig) override {
        if (!pdwSpeakerConfig) return E_POINTER;
        *pdwSpeakerConfig = 0x00000002; // DSSPEAKER_STEREO
        return S_OK;
    }
    HRESULT SetSpeakerConfig(uint32_t) override { return S_OK; }
    HRESULT Initialize(const IID*) override { return S_OK; }
    HRESULT VerifyCertification(uint32_t* pdwCertified) override {
        if (pdwCertified) *pdwCertified = 0; // DSCERTIFIED
        return S_OK;
    }
};

inline PrismDirectSound8& GetGlobalDirectSound8() {
    static PrismDirectSound8 s_ds8{};
    return s_ds8;
}

inline HRESULT DirectSoundCreate8(const IID* lpcGuidDevice, IDirectSound8** ppDS8, IUnknown* pUnkOuter) {
    (void)lpcGuidDevice;
    if (pUnkOuter != nullptr) return static_cast<HRESULT>(0x80040110L); // CLASS_E_NOAGGREGATION
    if (!ppDS8) return E_INVALIDARG;
    *ppDS8 = &GetGlobalDirectSound8();
    return S_OK;
}

inline HRESULT DirectSoundCreate(const IID* lpcGuidDevice, IDirectSound8** ppDS, IUnknown* pUnkOuter) {
    return DirectSoundCreate8(lpcGuidDevice, ppDS, pUnkOuter);
}

// --- 3. ddraw.dll Standard DirectDraw7 COM Interfaces ---
inline constexpr uint32_t DDSCL_FULLSCREEN = 0x00000001;
inline constexpr uint32_t DDSCL_EXCLUSIVE  = 0x00000010;
inline constexpr uint32_t DDSCL_NORMAL     = 0x00000008;

inline constexpr IID OFFICIAL_IID_IDirectDraw7 = {
    0x15E65EC0, 0x3B9C, 0x11D2, {0xB9, 0x2F, 0x00, 0x60, 0x97, 0x97, 0xEA, 0x5B}
};

struct IDirectDrawSurface7 : public IUnknown {
    virtual HRESULT Flip(IDirectDrawSurface7* lpDDSurfaceTargetOverride, uint32_t dwFlags) = 0;
    virtual HRESULT Lock(const void* lpDestRect, void* lpDDSurfaceDesc, uint32_t dwFlags, void* hEvent) = 0;
    virtual HRESULT Unlock(const void* lpRect) = 0;
    virtual HRESULT Restore() = 0;
};

struct IDirectDraw7 : public IUnknown {
    virtual HRESULT Compact() = 0;
    virtual HRESULT CreateSurface(void* lpDDSurfaceDesc2, IDirectDrawSurface7** lplpDDSurface, IUnknown* pUnkOuter) = 0;
    virtual HRESULT RestoreDisplayMode() = 0;
    virtual HRESULT SetCooperativeLevel(void* hWnd, uint32_t dwFlags) = 0;
    virtual HRESULT SetDisplayMode(uint32_t dwWidth, uint32_t dwHeight, uint32_t dwBPP, uint32_t dwRefreshRate, uint32_t dwFlags) = 0;
    virtual HRESULT WaitForVerticalBlank(uint32_t dwFlags, void* hEvent) = 0;
};

class PrismDirectDrawSurface7 final : public IDirectDrawSurface7 {
    uint32_t m_flips = 0;
public:
    HRESULT QueryInterface(const IID& riid, void** ppvObject) override {
        if (!ppvObject) return E_POINTER;
        if (riid == IID_IUnknown) {
            *ppvObject = static_cast<IDirectDrawSurface7*>(this);
            return S_OK;
        }
        *ppvObject = nullptr;
        return E_NOINTERFACE;
    }
    uint32_t AddRef() override { return 1; }
    uint32_t Release() override { return 1; }

    HRESULT Flip(IDirectDrawSurface7*, uint32_t) override { ++m_flips; return S_OK; }
    HRESULT Lock(const void*, void*, uint32_t, void*) override { return S_OK; }
    HRESULT Unlock(const void*) override { return S_OK; }
    HRESULT Restore() override { return S_OK; }
};

class PrismDirectDraw7 final : public IDirectDraw7 {
    PrismDirectDrawSurface7 m_primarySurface{};
    uint32_t m_width  = 1920;
    uint32_t m_height = 1080;
    uint32_t m_bpp    = 32;
    uint32_t m_hz     = 540;
public:
    HRESULT QueryInterface(const IID& riid, void** ppvObject) override {
        if (!ppvObject) return E_POINTER;
        if (riid == IID_IUnknown || riid == OFFICIAL_IID_IDirectDraw7) {
            *ppvObject = static_cast<IDirectDraw7*>(this);
            return S_OK;
        }
        *ppvObject = nullptr;
        return E_NOINTERFACE;
    }
    uint32_t AddRef() override { return 1; }
    uint32_t Release() override { return 1; }

    HRESULT Compact() override { return S_OK; }
    HRESULT CreateSurface(void*, IDirectDrawSurface7** lplpDDSurface, IUnknown*) override {
        if (!lplpDDSurface) return E_INVALIDARG;
        *lplpDDSurface = &m_primarySurface;
        return S_OK;
    }
    HRESULT RestoreDisplayMode() override { return S_OK; }
    HRESULT SetCooperativeLevel(void*, uint32_t) override { return S_OK; }
    HRESULT SetDisplayMode(uint32_t dwWidth, uint32_t dwHeight, uint32_t dwBPP, uint32_t dwRefreshRate, uint32_t) override {
        m_width  = dwWidth;
        m_height = dwHeight;
        m_bpp    = dwBPP;
        m_hz     = (dwRefreshRate > 0) ? dwRefreshRate : 540;
        return S_OK;
    }
    HRESULT WaitForVerticalBlank(uint32_t, void*) override { return S_OK; }
};

inline PrismDirectDraw7& GetGlobalDirectDraw7() {
    static PrismDirectDraw7 s_dd7{};
    return s_dd7;
}

inline HRESULT DirectDrawCreateEx(const IID* lpGuid, void** lplpDD, const IID& iid, IUnknown* pUnkOuter) {
    (void)lpGuid;
    if (pUnkOuter != nullptr) return static_cast<HRESULT>(0x80040110L);
    if (!lplpDD) return E_INVALIDARG;
    if (iid == OFFICIAL_IID_IDirectDraw7 || iid == IID_IUnknown) {
        *lplpDD = static_cast<IDirectDraw7*>(&GetGlobalDirectDraw7());
        return S_OK;
    }
    *lplpDD = nullptr;
    return E_NOINTERFACE;
}

inline HRESULT DirectDrawCreate(const IID* lpGUID, IDirectDraw7** lplpDD, IUnknown* pUnkOuter) {
    return DirectDrawCreateEx(lpGUID, reinterpret_cast<void**>(lplpDD), OFFICIAL_IID_IDirectDraw7, pUnkOuter);
}

// --- 4. mf.dll Standard Media Foundation Session & Topology COM Interfaces ---
struct IMFTopology : public IUnknown {
    virtual HRESULT GetTopologyID(uint64_t* pID) = 0;
    virtual HRESULT AddNode(IUnknown* pNode) = 0;
    virtual HRESULT Clear() = 0;
    virtual HRESULT GetNodeCount(uint16_t* pwNodes) = 0;
};

struct IMFMediaSession : public IUnknown {
    virtual HRESULT SetTopology(uint32_t dwSetTopologyFlags, IMFTopology* pTopology) = 0;
    virtual HRESULT ClearTopologies() = 0;
    virtual HRESULT Start(const IID* pguidTimeFormat, const void* pvarStartPosition) = 0;
    virtual HRESULT Pause() = 0;
    virtual HRESULT Stop() = 0;
    virtual HRESULT Close() = 0;
    virtual HRESULT Shutdown() = 0;
};

class PrismMFTopology final : public IMFTopology {
    uint64_t m_topologyId = 0x4D46544F504F0001ULL;
    uint16_t m_nodeCount  = 0;
public:
    HRESULT QueryInterface(const IID& riid, void** ppvObject) override {
        if (!ppvObject) return E_POINTER;
        if (riid == IID_IUnknown) {
            *ppvObject = static_cast<IMFTopology*>(this);
            return S_OK;
        }
        *ppvObject = nullptr;
        return E_NOINTERFACE;
    }
    uint32_t AddRef() override { return 1; }
    uint32_t Release() override { return 1; }

    HRESULT GetTopologyID(uint64_t* pID) override {
        if (!pID) return E_POINTER;
        *pID = m_topologyId;
        return S_OK;
    }
    HRESULT AddNode(IUnknown*) override {
        ++m_nodeCount;
        return S_OK;
    }
    HRESULT Clear() override {
        m_nodeCount = 0;
        return S_OK;
    }
    HRESULT GetNodeCount(uint16_t* pwNodes) override {
        if (!pwNodes) return E_POINTER;
        *pwNodes = m_nodeCount;
        return S_OK;
    }
};

class PrismMFMediaSession final : public IMFMediaSession {
    IMFTopology* m_activeTopology = nullptr;
    bool         m_started        = false;
public:
    HRESULT QueryInterface(const IID& riid, void** ppvObject) override {
        if (!ppvObject) return E_POINTER;
        if (riid == IID_IUnknown) {
            *ppvObject = static_cast<IMFMediaSession*>(this);
            return S_OK;
        }
        *ppvObject = nullptr;
        return E_NOINTERFACE;
    }
    uint32_t AddRef() override { return 1; }
    uint32_t Release() override { return 1; }

    HRESULT SetTopology(uint32_t, IMFTopology* pTopology) override {
        if (!pTopology) return E_INVALIDARG;
        m_activeTopology = pTopology;
        return S_OK;
    }
    HRESULT ClearTopologies() override {
        m_activeTopology = nullptr;
        return S_OK;
    }
    HRESULT Start(const IID*, const void*) override {
        m_started = true;
        return S_OK;
    }
    HRESULT Pause() override {
        m_started = false;
        return S_OK;
    }
    HRESULT Stop() override {
        m_started = false;
        return S_OK;
    }
    HRESULT Close() override {
        m_started = false;
        return S_OK;
    }
    HRESULT Shutdown() override {
        m_started = false;
        m_activeTopology = nullptr;
        return S_OK;
    }
};

inline HRESULT MFCreateMediaSession(MediaFoundationCom::IMFAttributes* pConfiguration, IMFMediaSession** ppMediaSession) {
    (void)pConfiguration;
    if (!ppMediaSession) return E_INVALIDARG;
    static PrismMFMediaSession s_session{};
    *ppMediaSession = &s_session;
    return S_OK;
}

inline HRESULT MFCreateTopology(IMFTopology** ppTopo) {
    if (!ppTopo) return E_INVALIDARG;
    static PrismMFTopology s_topo{};
    *ppTopo = &s_topo;
    return S_OK;
}

} // namespace prismx::D3D10DSoundDDrawMFCom
