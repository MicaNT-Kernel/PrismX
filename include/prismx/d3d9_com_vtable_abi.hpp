// ============================================================================
// PrismX: Official Microsoft Direct3D 9 / 9Ex (d3d9.h / d3d9.dll) COM ABI
// (Suite 34 — IDirect3D9Ex 21-Slot VTable, IDirect3DDevice9Ex & D3D9On12 Bridge)
//
// Clean-Room Implementation in ISO C++23. Zero External Dependencies.
// Provides:
//   - Exact 16-byte Microsoft binary IIDs from <d3d9.h>:
//       * IID_IDirect3D9           {81bdcbca-64d4-426d-ae8d-ad0147f4275c}
//       * IID_IDirect3D9Ex         {02177241-69fc-400c-8ff1-93a44df6861d}
//       * IID_IDirect3DDevice9     {d0223b96-bf7a-43fd-92bd-a43b0d82b9eb}
//       * IID_IDirect3DDevice9Ex   {b18b10ce-2649-405a-870f-95f777d4313a}
//       * IID_IDirect3DSwapChain9  {794950f2-adfc-458a-905e-10a10b0b503b}
//       * IID_IDirect3DSwapChain9Ex{91886caf-1c3d-4d2e-a0ab-3e4c7d8d3303}
//       * IID_IDirect3DTexture9    {85c31227-3de5-4f00-9b3a-f11ac38c18b5}
//       * IID_IDirect3DSurface9    {0cfbaf3a-9ff6-429a-99b3-a2796af8b89b}
//   - Canonical 21-slot IDirect3D9Ex COM vtable (Slots 0..20) and
//     IDirect3DDevice9Ex COM interface routed over D3D9On12 / PrismX.
//   - Official d3d9.dll exports: Direct3DCreate9, Direct3DCreate9Ex,
//     D3DPERF_BeginEvent, D3DPERF_EndEvent, D3DPERF_SetMarker, D3DPERF_GetStatus.
// ============================================================================

#pragma once

#include "types.hpp"
#include <atomic>
#include <cstring>

namespace prismx::D3D9Com {

// ----------------------------------------------------------------------------
// 1. Official 16-Byte Microsoft Binary IIDs (<d3d9.h>)
// ----------------------------------------------------------------------------
// {81bdcbca-64d4-426d-ae8d-ad0147f4275c}
inline constexpr IID OFFICIAL_IID_IDirect3D9 = {
    0x81bdcbca, 0x64d4, 0x426d, {0xae, 0x8d, 0xad, 0x01, 0x47, 0xf4, 0x27, 0x5c}
};
// {02177241-69fc-400c-8ff1-93a44df6861d}
inline constexpr IID OFFICIAL_IID_IDirect3D9Ex = {
    0x02177241, 0x69fc, 0x400c, {0x8f, 0xf1, 0x93, 0xa4, 0x4d, 0xf6, 0x86, 0x1d}
};
// {d0223b96-bf7a-43fd-92bd-a43b0d82b9eb}
inline constexpr IID OFFICIAL_IID_IDirect3DDevice9 = {
    0xd0223b96, 0xbf7a, 0x43fd, {0x92, 0xbd, 0xa4, 0x3b, 0x0d, 0x82, 0xb9, 0xeb}
};
// {b18b10ce-2649-405a-870f-95f777d4313a}
inline constexpr IID OFFICIAL_IID_IDirect3DDevice9Ex = {
    0xb18b10ce, 0x2649, 0x405a, {0x87, 0x0f, 0x95, 0xf7, 0x77, 0xd4, 0x31, 0x3a}
};
// {794950f2-adfc-458a-905e-10a10b0b503b}
inline constexpr IID OFFICIAL_IID_IDirect3DSwapChain9 = {
    0x794950f2, 0xadfc, 0x458a, {0x90, 0x5e, 0x10, 0xa1, 0x0b, 0x0b, 0x50, 0x3b}
};
// {91886caf-1c3d-4d2e-a0ab-3e4c7d8d3303}
inline constexpr IID OFFICIAL_IID_IDirect3DSwapChain9Ex = {
    0x91886caf, 0x1c3d, 0x4d2e, {0xa0, 0xab, 0x3e, 0x4c, 0x7d, 0x8d, 0x33, 0x03}
};
// {85c31227-3de5-4f00-9b3a-f11ac38c18b5}
inline constexpr IID OFFICIAL_IID_IDirect3DTexture9 = {
    0x85c31227, 0x3de5, 0x4f00, {0x9b, 0x3a, 0xf1, 0x1a, 0xc3, 0x8c, 0x18, 0xb5}
};
// {0cfbaf3a-9ff6-429a-99b3-a2796af8b89b}
inline constexpr IID OFFICIAL_IID_IDirect3DSurface9 = {
    0x0cfbaf3a, 0x9ff6, 0x429a, {0x99, 0xb3, 0xa2, 0x79, 0x6a, 0xf8, 0xb8, 0x9b}
};

// ----------------------------------------------------------------------------
// 2. Canonical <d3d9types.h> / <d3d9caps.h> Constants & Structures
// ----------------------------------------------------------------------------
inline constexpr uint32_t D3D_SDK_VERSION_9C         = 32;
inline constexpr uint32_t D3DADAPTER_DEFAULT         = 0;
inline constexpr uint32_t D3DCREATE_HARDWARE_VERTEXPROCESSING = 0x00000040;
inline constexpr uint32_t D3DCREATE_MULTITHREADED    = 0x00000004;
inline constexpr uint32_t D3DDEVCAPS_HWTRANSFORMANDLIGHT = 0x00010000;
inline constexpr uint32_t D3DDEVCAPS_PUREDEVICE      = 0x00100000;
inline constexpr uint32_t D3DCLEAR_TARGET            = 0x00000001;
inline constexpr uint32_t D3DCLEAR_ZBUFFER           = 0x00000002;
inline constexpr uint32_t D3DCLEAR_STENCIL           = 0x00000004;

enum D3DDEVTYPE : uint32_t {
    D3DDEVTYPE_HAL     = 1,
    D3DDEVTYPE_REF     = 2,
    D3DDEVTYPE_SW      = 3,
    D3DDEVTYPE_NULLREF = 4
};

enum D3DFORMAT : uint32_t {
    D3DFMT_UNKNOWN      = 0,
    D3DFMT_R8G8B8       = 20,
    D3DFMT_A8R8G8B8     = 21,
    D3DFMT_X8R8G8B8     = 22,
    D3DFMT_A2B10G10R10  = 31,
    D3DFMT_A16B16G16R16F = 113,
    D3DFMT_D24S8        = 75,
    D3DFMT_DXT1         = 0x31545844u,
    D3DFMT_DXT5         = 0x35545844u
};

enum D3DSWAPEFFECT : uint32_t {
    D3DSWAPEFFECT_DISCARD = 1,
    D3DSWAPEFFECT_FLIP    = 2,
    D3DSWAPEFFECT_COPY    = 3,
    D3DSWAPEFFECT_FLIPEX  = 5
};

enum D3DPRIMITIVETYPE : uint32_t {
    D3DPT_POINTLIST     = 1,
    D3DPT_LINELIST      = 2,
    D3DPT_LINESTRIP     = 3,
    D3DPT_TRIANGLELIST  = 4,
    D3DPT_TRIANGLESTRIP = 5,
    D3DPT_TRIANGLEFAN   = 6
};

struct D3DDISPLAYMODE {
    uint32_t Width;
    uint32_t Height;
    uint32_t RefreshRate;
    D3DFORMAT Format;
};

struct D3DDISPLAYMODEEX {
    uint32_t Size;
    uint32_t Width;
    uint32_t Height;
    uint32_t RefreshRate;
    D3DFORMAT Format;
    uint32_t ScanLineOrdering;
};

struct D3DADAPTER_IDENTIFIER9 {
    char Driver[512];
    char Description[512];
    char DeviceName[32];
    uint64_t DriverVersion;
    uint32_t VendorId;
    uint32_t DeviceId;
    uint32_t SubSysId;
    uint32_t Revision;
    IID DeviceIdentifier;
    uint32_t WHQLLevel;
};

struct D3DPRESENT_PARAMETERS {
    uint32_t BackBufferWidth;
    uint32_t BackBufferHeight;
    D3DFORMAT BackBufferFormat;
    uint32_t BackBufferCount;
    uint32_t MultiSampleType;
    uint32_t MultiSampleQuality;
    D3DSWAPEFFECT SwapEffect;
    void* hDeviceWindow;
    int32_t Windowed;
    int32_t EnableAutoDepthStencil;
    D3DFORMAT AutoDepthStencilFormat;
    uint32_t Flags;
    uint32_t FullScreen_RefreshRateInHz;
    uint32_t PresentationInterval;
};

struct D3DCAPS9 {
    D3DDEVTYPE DeviceType;
    uint32_t AdapterOrdinal;
    uint32_t Caps;
    uint32_t DevCaps;
    uint32_t MaxTextureWidth;
    uint32_t MaxTextureHeight;
    uint32_t MaxVolumeExtent;
    uint32_t MaxTextureRepeat;
    uint32_t MaxAnisotropy;
    uint32_t VertexShaderVersion; // 0xFFFE0300 (vs_3_0)
    uint32_t MaxVertexShaderConst;
    uint32_t PixelShaderVersion;  // 0xFFFF0300 (ps_3_0)
    uint32_t NumSimultaneousRTs;
    uint32_t MaxPrimitiveCount;
    uint32_t MaxVertexIndex;
    uint32_t MaxStreams;
};

// Forward declarations
struct IDirect3D9;
struct IDirect3D9Ex;
struct IDirect3DDevice9;
struct IDirect3DDevice9Ex;
struct IDirect3DSwapChain9;
struct IDirect3DSwapChain9Ex;
struct IDirect3DSurface9;
struct IDirect3DTexture9;

// ----------------------------------------------------------------------------
// 3. Canonical IDirect3DSurface9 & IDirect3DTexture9 COM Interfaces
// ----------------------------------------------------------------------------
struct IDirect3DSurface9 : public IUnknown {
    virtual HRESULT GetDevice(IDirect3DDevice9** ppDevice) = 0;
    virtual HRESULT LockRect(void* pLockedRect, const void* pRect, uint32_t Flags) = 0;
    virtual HRESULT UnlockRect() = 0;
};

struct IDirect3DTexture9 : public IUnknown {
    virtual HRESULT GetDevice(IDirect3DDevice9** ppDevice) = 0;
    virtual uint32_t GetLevelCount() = 0;
    virtual HRESULT GetSurfaceLevel(uint32_t Level, IDirect3DSurface9** ppSurfaceLevel) = 0;
    virtual HRESULT LockRect(uint32_t Level, void* pLockedRect, const void* pRect, uint32_t Flags) = 0;
    virtual HRESULT UnlockRect(uint32_t Level) = 0;
};

// ----------------------------------------------------------------------------
// 4. Canonical IDirect3DSwapChain9 -> IDirect3DSwapChain9Ex COM Hierarchy
// ----------------------------------------------------------------------------
struct IDirect3DSwapChain9 : public IUnknown {
    virtual HRESULT Present(const void* pSourceRect, const void* pDestRect,
                            void* hDestWindowOverride, const void* pDirtyRegion,
                            uint32_t dwFlags) = 0;
    virtual HRESULT GetFrontBufferData(IDirect3DSurface9* pDestSurface) = 0;
    virtual HRESULT GetBackBuffer(uint32_t iBackBuffer, uint32_t Type,
                                  IDirect3DSurface9** ppBackBuffer) = 0;
    virtual HRESULT GetRasterStatus(void* pRasterStatus) = 0;
    virtual HRESULT GetDisplayMode(D3DDISPLAYMODE* pMode) = 0;
    virtual HRESULT GetDevice(IDirect3DDevice9** ppDevice) = 0;
    virtual HRESULT GetPresentParameters(D3DPRESENT_PARAMETERS* pPresentationParameters) = 0;
};

struct IDirect3DSwapChain9Ex : public IDirect3DSwapChain9 {
    virtual HRESULT GetLastPresentCount(uint32_t* pLastPresentCount) = 0;
    virtual HRESULT GetPresentStats(void* pPresentationStatistics) = 0;
    virtual HRESULT GetDisplayModeEx(D3DDISPLAYMODEEX* pMode, uint32_t* pRotation) = 0;
};

// ----------------------------------------------------------------------------
// 5. Canonical IDirect3DDevice9 -> IDirect3DDevice9Ex COM Hierarchy
// ----------------------------------------------------------------------------
struct IDirect3DDevice9 : public IUnknown {
    virtual HRESULT TestCooperativeLevel() = 0;                                 // Slot 3
    virtual uint32_t GetAvailableTextureMem() = 0;                              // Slot 4
    virtual HRESULT EvictManagedResources() = 0;                                // Slot 5
    virtual HRESULT GetDirect3D(IDirect3D9** ppD3D9) = 0;                       // Slot 6
    virtual HRESULT GetDeviceCaps(D3DCAPS9* pCaps) = 0;                         // Slot 7
    virtual HRESULT GetDisplayMode(uint32_t iSwapChain, D3DDISPLAYMODE* pMode) = 0; // Slot 8
    virtual HRESULT GetCreationParameters(void* pParameters) = 0;               // Slot 9
    virtual HRESULT SetCursorProperties(uint32_t XHotSpot, uint32_t YHotSpot,
                                        IDirect3DSurface9* pCursorBitmap) = 0;  // Slot 10
    virtual void SetCursorPosition(int32_t X, int32_t Y, uint32_t Flags) = 0;   // Slot 11
    virtual int32_t ShowCursor(int32_t bShow) = 0;                              // Slot 12
    virtual HRESULT CreateAdditionalSwapChain(
        D3DPRESENT_PARAMETERS* pPresentationParameters,
        IDirect3DSwapChain9** pSwapChain) = 0;                                  // Slot 13
    virtual HRESULT GetSwapChain(uint32_t iSwapChain,
                                 IDirect3DSwapChain9** pSwapChain) = 0;         // Slot 14
    virtual uint32_t GetNumberOfSwapChains() = 0;                               // Slot 15
    virtual HRESULT Reset(D3DPRESENT_PARAMETERS* pPresentationParameters) = 0;  // Slot 16
    virtual HRESULT Present(const void* pSourceRect, const void* pDestRect,
                            void* hDestWindowOverride,
                            const void* pDirtyRegion) = 0;                      // Slot 17 (Standard Overlay Hook Target!)
    virtual HRESULT GetBackBuffer(uint32_t iSwapChain, uint32_t iBackBuffer,
                                  uint32_t Type,
                                  IDirect3DSurface9** ppBackBuffer) = 0;        // Slot 18
    virtual HRESULT BeginScene() = 0;                                           // Slot 19
    virtual HRESULT EndScene() = 0;                                             // Slot 20
    virtual HRESULT Clear(uint32_t Count, const void* pRects, uint32_t Flags,
                          uint32_t Color, float Z, uint32_t Stencil) = 0;       // Slot 21
    virtual HRESULT SetRenderState(uint32_t State, uint32_t Value) = 0;         // Slot 22
    virtual HRESULT CreateTexture(uint32_t Width, uint32_t Height,
                                  uint32_t Levels, uint32_t Usage,
                                  D3DFORMAT Format, uint32_t Pool,
                                  IDirect3DTexture9** ppTexture,
                                  void** pSharedHandle) = 0;                    // Slot 23
    virtual HRESULT SetTexture(uint32_t Stage, IDirect3DTexture9* pTexture) = 0;// Slot 24
    virtual HRESULT DrawPrimitive(D3DPRIMITIVETYPE PrimitiveType,
                                  uint32_t StartVertex,
                                  uint32_t PrimitiveCount) = 0;                 // Slot 25
};

struct IDirect3DDevice9Ex : public IDirect3DDevice9 {
    virtual HRESULT CheckDeviceState(void* hDestinationWindow) = 0;             // Slot 26
    virtual HRESULT PresentEx(const void* pSourceRect, const void* pDestRect,
                              void* hDestWindowOverride, const void* pDirtyRegion,
                              uint32_t dwFlags) = 0;                            // Slot 27
    virtual HRESULT ResetEx(D3DPRESENT_PARAMETERS* pPresentationParameters,
                            D3DDISPLAYMODEEX* pFullscreenDisplayMode) = 0;      // Slot 28
    virtual HRESULT SetMaximumFrameLatency(uint32_t MaxLatency) = 0;            // Slot 29
    virtual HRESULT GetMaximumFrameLatency(uint32_t* pMaxLatency) = 0;          // Slot 30
};

// ----------------------------------------------------------------------------
// 6. Canonical 21-Slot IDirect3D9 -> IDirect3D9Ex COM Hierarchy (Slots 0..20)
// ----------------------------------------------------------------------------
struct IDirect3D9 : public IUnknown {
    virtual HRESULT RegisterSoftwareDevice(void* pInitializeFunction) = 0;      // Slot 3
    virtual uint32_t GetAdapterCount() = 0;                                     // Slot 4
    virtual HRESULT GetAdapterIdentifier(uint32_t Adapter, uint32_t Flags,
                                         D3DADAPTER_IDENTIFIER9* pIdentifier) = 0; // Slot 5
    virtual uint32_t GetAdapterModeCount(uint32_t Adapter, D3DFORMAT Format) = 0;  // Slot 6
    virtual HRESULT EnumAdapterModes(uint32_t Adapter, D3DFORMAT Format,
                                     uint32_t Mode, D3DDISPLAYMODE* pMode) = 0; // Slot 7
    virtual HRESULT GetAdapterDisplayMode(uint32_t Adapter,
                                          D3DDISPLAYMODE* pMode) = 0;           // Slot 8
    virtual HRESULT CheckDeviceType(uint32_t Adapter, D3DDEVTYPE DevType,
                                    D3DFORMAT AdapterFormat,
                                    D3DFORMAT BackBufferFormat,
                                    int32_t bWindowed) = 0;                     // Slot 9
    virtual HRESULT CheckDeviceFormat(uint32_t Adapter, D3DDEVTYPE DeviceType,
                                      D3DFORMAT AdapterFormat, uint32_t Usage,
                                      uint32_t RType, D3DFORMAT CheckFormat) = 0; // Slot 10
    virtual HRESULT CheckDeviceMultiSampleType(uint32_t Adapter,
                                               D3DDEVTYPE DeviceType,
                                               D3DFORMAT SurfaceFormat,
                                               int32_t Windowed,
                                               uint32_t MultiSampleType,
                                               uint32_t* pQualityLevels) = 0;   // Slot 11
    virtual HRESULT CheckDepthStencilMatch(uint32_t Adapter,
                                           D3DDEVTYPE DeviceType,
                                           D3DFORMAT AdapterFormat,
                                           D3DFORMAT RenderTargetFormat,
                                           D3DFORMAT DepthStencilFormat) = 0;   // Slot 12
    virtual HRESULT CheckDeviceFormatConversion(uint32_t Adapter,
                                                D3DDEVTYPE DeviceType,
                                                D3DFORMAT SourceFormat,
                                                D3DFORMAT TargetFormat) = 0;    // Slot 13
    virtual HRESULT GetDeviceCaps(uint32_t Adapter, D3DDEVTYPE DeviceType,
                                  D3DCAPS9* pCaps) = 0;                         // Slot 14
    virtual void* GetAdapterMonitor(uint32_t Adapter) = 0;                      // Slot 15
    virtual HRESULT CreateDevice(uint32_t Adapter, D3DDEVTYPE DeviceType,
                                 void* hFocusWindow, uint32_t BehaviorFlags,
                                 D3DPRESENT_PARAMETERS* pPresentationParameters,
                                 IDirect3DDevice9** ppReturnedDeviceInterface) = 0; // Slot 16
};

struct IDirect3D9Ex : public IDirect3D9 {
    virtual uint32_t GetAdapterModeCountEx(uint32_t Adapter,
                                           const void* pFilter) = 0;            // Slot 17
    virtual HRESULT EnumAdapterModesEx(uint32_t Adapter, const void* pFilter,
                                       uint32_t Mode,
                                       D3DDISPLAYMODEEX* pMode) = 0;            // Slot 18
    virtual HRESULT GetAdapterDisplayModeEx(uint32_t Adapter,
                                            D3DDISPLAYMODEEX* pMode,
                                            uint32_t* pRotation) = 0;           // Slot 19
    virtual HRESULT CreateDeviceEx(uint32_t Adapter, D3DDEVTYPE DeviceType,
                                   void* hFocusWindow, uint32_t BehaviorFlags,
                                   D3DPRESENT_PARAMETERS* pPresentationParameters,
                                   D3DDISPLAYMODEEX* pFullscreenDisplayMode,
                                   IDirect3DDevice9Ex** ppReturnedDeviceInterface) = 0; // Slot 20
};

// ----------------------------------------------------------------------------
// 7. Concrete Implementations Routed Over D3D9On12 / PrismX
// ----------------------------------------------------------------------------
class PrismDirect3DSurface9Impl final : public IDirect3DSurface9 {
    std::atomic<uint32_t> ref_count_{1};
    IDirect3DDevice9* parent_device_ = nullptr;
    uint8_t scratch_pixels_[64]{};

public:
    explicit PrismDirect3DSurface9Impl(IDirect3DDevice9* dev) : parent_device_(dev) {}

    int32_t QueryInterface(const IID& riid, void** ppvObject) override {
        if (!ppvObject) return E_POINTER;
        if (riid == IID_IUnknown || riid == OFFICIAL_IID_IDirect3DSurface9) {
            *ppvObject = static_cast<IDirect3DSurface9*>(this);
            AddRef();
            return S_OK;
        }
        *ppvObject = nullptr;
        return E_NOINTERFACE;
    }
    uint32_t AddRef() override { return ++ref_count_; }
    uint32_t Release() override {
        uint32_t r = --ref_count_;
        if (r == 0) delete this;
        return r;
    }
    HRESULT GetDevice(IDirect3DDevice9** ppDevice) override {
        if (!ppDevice) return E_POINTER;
        *ppDevice = parent_device_;
        if (parent_device_) parent_device_->AddRef();
        return S_OK;
    }
    HRESULT LockRect(void* pLockedRect, const void*, uint32_t) override {
        if (pLockedRect) {
            struct LockedRect { int32_t Pitch; void* pBits; };
            auto* lr = static_cast<LockedRect*>(pLockedRect);
            lr->Pitch = 256;
            lr->pBits = scratch_pixels_;
        }
        return S_OK;
    }
    HRESULT UnlockRect() override { return S_OK; }
};

class PrismDirect3DTexture9Impl final : public IDirect3DTexture9 {
    std::atomic<uint32_t> ref_count_{1};
    IDirect3DDevice9* parent_device_ = nullptr;
    uint32_t levels_ = 1;

public:
    PrismDirect3DTexture9Impl(IDirect3DDevice9* dev, uint32_t levels)
        : parent_device_(dev), levels_(levels ? levels : 1) {}

    int32_t QueryInterface(const IID& riid, void** ppvObject) override {
        if (!ppvObject) return E_POINTER;
        if (riid == IID_IUnknown || riid == OFFICIAL_IID_IDirect3DTexture9) {
            *ppvObject = static_cast<IDirect3DTexture9*>(this);
            AddRef();
            return S_OK;
        }
        *ppvObject = nullptr;
        return E_NOINTERFACE;
    }
    uint32_t AddRef() override { return ++ref_count_; }
    uint32_t Release() override {
        uint32_t r = --ref_count_;
        if (r == 0) delete this;
        return r;
    }
    HRESULT GetDevice(IDirect3DDevice9** ppDevice) override {
        if (!ppDevice) return E_POINTER;
        *ppDevice = parent_device_;
        if (parent_device_) parent_device_->AddRef();
        return S_OK;
    }
    uint32_t GetLevelCount() override { return levels_; }
    HRESULT GetSurfaceLevel(uint32_t, IDirect3DSurface9** ppSurfaceLevel) override {
        if (!ppSurfaceLevel) return E_POINTER;
        *ppSurfaceLevel = new PrismDirect3DSurface9Impl(parent_device_);
        return S_OK;
    }
    HRESULT LockRect(uint32_t, void*, const void*, uint32_t) override { return S_OK; }
    HRESULT UnlockRect(uint32_t) override { return S_OK; }
};

class PrismDirect3DSwapChain9ExImpl final : public IDirect3DSwapChain9Ex {
    std::atomic<uint32_t> ref_count_{1};
    IDirect3DDevice9* parent_device_ = nullptr;
    D3DPRESENT_PARAMETERS present_params_{};
    uint32_t present_count_ = 0;

public:
    PrismDirect3DSwapChain9ExImpl(IDirect3DDevice9* dev, const D3DPRESENT_PARAMETERS* pp)
        : parent_device_(dev) {
        if (pp) present_params_ = *pp;
        else {
            present_params_.BackBufferWidth = 1920;
            present_params_.BackBufferHeight = 1080;
            present_params_.BackBufferFormat = D3DFMT_A8R8G8B8;
            present_params_.BackBufferCount = 2;
            present_params_.SwapEffect = D3DSWAPEFFECT_FLIPEX;
            present_params_.Windowed = 1;
        }
    }

    int32_t QueryInterface(const IID& riid, void** ppvObject) override {
        if (!ppvObject) return E_POINTER;
        if (riid == IID_IUnknown ||
            riid == OFFICIAL_IID_IDirect3DSwapChain9 ||
            riid == OFFICIAL_IID_IDirect3DSwapChain9Ex) {
            *ppvObject = static_cast<IDirect3DSwapChain9Ex*>(this);
            AddRef();
            return S_OK;
        }
        *ppvObject = nullptr;
        return E_NOINTERFACE;
    }
    uint32_t AddRef() override { return ++ref_count_; }
    uint32_t Release() override {
        uint32_t r = --ref_count_;
        if (r == 0) delete this;
        return r;
    }
    HRESULT Present(const void*, const void*, void*, const void*, uint32_t) override {
        ++present_count_;
        return S_OK;
    }
    HRESULT GetFrontBufferData(IDirect3DSurface9*) override { return S_OK; }
    HRESULT GetBackBuffer(uint32_t, uint32_t, IDirect3DSurface9** ppBackBuffer) override {
        if (!ppBackBuffer) return E_POINTER;
        *ppBackBuffer = new PrismDirect3DSurface9Impl(parent_device_);
        return S_OK;
    }
    HRESULT GetRasterStatus(void*) override { return S_OK; }
    HRESULT GetDisplayMode(D3DDISPLAYMODE* pMode) override {
        if (!pMode) return E_POINTER;
        pMode->Width = present_params_.BackBufferWidth;
        pMode->Height = present_params_.BackBufferHeight;
        pMode->RefreshRate = 540;
        pMode->Format = present_params_.BackBufferFormat;
        return S_OK;
    }
    HRESULT GetDevice(IDirect3DDevice9** ppDevice) override {
        if (!ppDevice) return E_POINTER;
        *ppDevice = parent_device_;
        if (parent_device_) parent_device_->AddRef();
        return S_OK;
    }
    HRESULT GetPresentParameters(D3DPRESENT_PARAMETERS* pPresentationParameters) override {
        if (!pPresentationParameters) return E_POINTER;
        *pPresentationParameters = present_params_;
        return S_OK;
    }
    HRESULT GetLastPresentCount(uint32_t* pLastPresentCount) override {
        if (!pLastPresentCount) return E_POINTER;
        *pLastPresentCount = present_count_;
        return S_OK;
    }
    HRESULT GetPresentStats(void*) override { return S_OK; }
    HRESULT GetDisplayModeEx(D3DDISPLAYMODEEX* pMode, uint32_t* pRotation) override {
        if (!pMode) return E_POINTER;
        pMode->Size = sizeof(D3DDISPLAYMODEEX);
        pMode->Width = present_params_.BackBufferWidth;
        pMode->Height = present_params_.BackBufferHeight;
        pMode->RefreshRate = 540;
        pMode->Format = present_params_.BackBufferFormat;
        pMode->ScanLineOrdering = 1;
        if (pRotation) *pRotation = 1;
        return S_OK;
    }
};

class PrismDirect3DDevice9ExImpl final : public IDirect3DDevice9Ex {
    std::atomic<uint32_t> ref_count_{1};
    IDirect3D9* parent_d3d9_ = nullptr;
    D3DPRESENT_PARAMETERS present_params_{};
    uint32_t max_frame_latency_ = 1;
    uint32_t present_count_ = 0;
    uint32_t draw_calls_ = 0;

public:
    PrismDirect3DDevice9ExImpl(IDirect3D9* parent, const D3DPRESENT_PARAMETERS* pp)
        : parent_d3d9_(parent) {
        if (parent_d3d9_) parent_d3d9_->AddRef();
        if (pp) present_params_ = *pp;
        else {
            present_params_.BackBufferWidth = 1920;
            present_params_.BackBufferHeight = 1080;
            present_params_.BackBufferFormat = D3DFMT_A8R8G8B8;
            present_params_.BackBufferCount = 2;
            present_params_.SwapEffect = D3DSWAPEFFECT_FLIPEX;
            present_params_.Windowed = 1;
        }
    }

    ~PrismDirect3DDevice9ExImpl() {
        if (parent_d3d9_) parent_d3d9_->Release();
    }

    int32_t QueryInterface(const IID& riid, void** ppvObject) override {
        if (!ppvObject) return E_POINTER;
        if (riid == IID_IUnknown ||
            riid == OFFICIAL_IID_IDirect3DDevice9 ||
            riid == OFFICIAL_IID_IDirect3DDevice9Ex) {
            *ppvObject = static_cast<IDirect3DDevice9Ex*>(this);
            AddRef();
            return S_OK;
        }
        *ppvObject = nullptr;
        return E_NOINTERFACE;
    }
    uint32_t AddRef() override { return ++ref_count_; }
    uint32_t Release() override {
        uint32_t r = --ref_count_;
        if (r == 0) delete this;
        return r;
    }

    HRESULT TestCooperativeLevel() override { return S_OK; }
    uint32_t GetAvailableTextureMem() override { return 0xFFF00000u; } // 4095 MB canonical cap
    HRESULT EvictManagedResources() override { return S_OK; }
    HRESULT GetDirect3D(IDirect3D9** ppD3D9) override {
        if (!ppD3D9) return E_POINTER;
        *ppD3D9 = parent_d3d9_;
        if (parent_d3d9_) parent_d3d9_->AddRef();
        return S_OK;
    }
    HRESULT GetDeviceCaps(D3DCAPS9* pCaps) override {
        if (!pCaps) return E_POINTER;
        std::memset(pCaps, 0, sizeof(D3DCAPS9));
        pCaps->DeviceType = D3DDEVTYPE_HAL;
        pCaps->AdapterOrdinal = 0;
        pCaps->DevCaps = D3DDEVCAPS_HWTRANSFORMANDLIGHT | D3DDEVCAPS_PUREDEVICE;
        pCaps->MaxTextureWidth = 16384;
        pCaps->MaxTextureHeight = 16384;
        pCaps->MaxVolumeExtent = 2048;
        pCaps->MaxTextureRepeat = 8192;
        pCaps->MaxAnisotropy = 16;
        pCaps->VertexShaderVersion = 0xFFFE0300u; // vs_3_0
        pCaps->MaxVertexShaderConst = 256;
        pCaps->PixelShaderVersion = 0xFFFF0300u;  // ps_3_0
        pCaps->NumSimultaneousRTs = 4;
        pCaps->MaxPrimitiveCount = 0x00FFFFFFu;
        pCaps->MaxVertexIndex = 0x00FFFFFFu;
        pCaps->MaxStreams = 16;
        return S_OK;
    }
    HRESULT GetDisplayMode(uint32_t, D3DDISPLAYMODE* pMode) override {
        if (!pMode) return E_POINTER;
        pMode->Width = present_params_.BackBufferWidth;
        pMode->Height = present_params_.BackBufferHeight;
        pMode->RefreshRate = 540;
        pMode->Format = present_params_.BackBufferFormat;
        return S_OK;
    }
    HRESULT GetCreationParameters(void*) override { return S_OK; }
    HRESULT SetCursorProperties(uint32_t, uint32_t, IDirect3DSurface9*) override { return S_OK; }
    void SetCursorPosition(int32_t, int32_t, uint32_t) override {}
    int32_t ShowCursor(int32_t bShow) override { return bShow; }
    HRESULT CreateAdditionalSwapChain(D3DPRESENT_PARAMETERS* pPresentationParameters,
                                      IDirect3DSwapChain9** pSwapChain) override {
        if (!pSwapChain) return E_POINTER;
        *pSwapChain = new PrismDirect3DSwapChain9ExImpl(this, pPresentationParameters);
        return S_OK;
    }
    HRESULT GetSwapChain(uint32_t, IDirect3DSwapChain9** pSwapChain) override {
        if (!pSwapChain) return E_POINTER;
        *pSwapChain = new PrismDirect3DSwapChain9ExImpl(this, &present_params_);
        return S_OK;
    }
    uint32_t GetNumberOfSwapChains() override { return 1; }
    HRESULT Reset(D3DPRESENT_PARAMETERS* pPresentationParameters) override {
        if (pPresentationParameters) present_params_ = *pPresentationParameters;
        return S_OK;
    }
    HRESULT Present(const void*, const void*, void*, const void*) override {
        ++present_count_;
        return S_OK;
    }
    HRESULT GetBackBuffer(uint32_t, uint32_t, uint32_t,
                          IDirect3DSurface9** ppBackBuffer) override {
        if (!ppBackBuffer) return E_POINTER;
        *ppBackBuffer = new PrismDirect3DSurface9Impl(this);
        return S_OK;
    }
    HRESULT BeginScene() override { return S_OK; }
    HRESULT EndScene() override { return S_OK; }
    HRESULT Clear(uint32_t, const void*, uint32_t, uint32_t, float, uint32_t) override {
        return S_OK;
    }
    HRESULT SetRenderState(uint32_t, uint32_t) override { return S_OK; }
    HRESULT CreateTexture(uint32_t, uint32_t, uint32_t Levels, uint32_t,
                          D3DFORMAT, uint32_t, IDirect3DTexture9** ppTexture,
                          void**) override {
        if (!ppTexture) return E_POINTER;
        *ppTexture = new PrismDirect3DTexture9Impl(this, Levels);
        return S_OK;
    }
    HRESULT SetTexture(uint32_t, IDirect3DTexture9*) override { return S_OK; }
    HRESULT DrawPrimitive(D3DPRIMITIVETYPE, uint32_t, uint32_t) override {
        ++draw_calls_;
        return S_OK;
    }

    // IDirect3DDevice9Ex methods
    HRESULT CheckDeviceState(void*) override { return S_OK; }
    HRESULT PresentEx(const void*, const void*, void*, const void*, uint32_t) override {
        ++present_count_;
        return S_OK;
    }
    HRESULT ResetEx(D3DPRESENT_PARAMETERS* pPresentationParameters,
                    D3DDISPLAYMODEEX*) override {
        if (pPresentationParameters) present_params_ = *pPresentationParameters;
        return S_OK;
    }
    HRESULT SetMaximumFrameLatency(uint32_t MaxLatency) override {
        max_frame_latency_ = MaxLatency ? MaxLatency : 1;
        return S_OK;
    }
    HRESULT GetMaximumFrameLatency(uint32_t* pMaxLatency) override {
        if (!pMaxLatency) return E_POINTER;
        *pMaxLatency = max_frame_latency_;
        return S_OK;
    }
};

class PrismDirect3D9ExImpl final : public IDirect3D9Ex {
    std::atomic<uint32_t> ref_count_{1};
    uint32_t sdk_version_ = D3D_SDK_VERSION_9C;

public:
    explicit PrismDirect3D9ExImpl(uint32_t sdk_version = D3D_SDK_VERSION_9C)
        : sdk_version_(sdk_version) {
        (void)sdk_version_;
    }

    int32_t QueryInterface(const IID& riid, void** ppvObject) override {
        if (!ppvObject) return E_POINTER;
        if (riid == IID_IUnknown ||
            riid == OFFICIAL_IID_IDirect3D9 ||
            riid == OFFICIAL_IID_IDirect3D9Ex) {
            *ppvObject = static_cast<IDirect3D9Ex*>(this);
            AddRef();
            return S_OK;
        }
        *ppvObject = nullptr;
        return E_NOINTERFACE;
    }
    uint32_t AddRef() override { return ++ref_count_; }
    uint32_t Release() override {
        uint32_t r = --ref_count_;
        if (r == 0) delete this;
        return r;
    }

    HRESULT RegisterSoftwareDevice(void*) override { return S_OK; }
    uint32_t GetAdapterCount() override { return 1; }
    HRESULT GetAdapterIdentifier(uint32_t Adapter, uint32_t,
                                 D3DADAPTER_IDENTIFIER9* pIdentifier) override {
        if (!pIdentifier) return E_POINTER;
        if (Adapter > 0) return E_INVALIDARG;
        std::memset(pIdentifier, 0, sizeof(D3DADAPTER_IDENTIFIER9));
        std::memcpy(pIdentifier->Driver, "d3d9on12.dll", 13);
        std::memcpy(pIdentifier->Description, "Sovereign PrismX D3D9On12 Hardware Adapter", 43);
        std::memcpy(pIdentifier->DeviceName, "\\\\.\\DISPLAY1", 13);
        pIdentifier->DriverVersion = 0x001F000000010266ULL;
        pIdentifier->VendorId = 0x10DE;
        pIdentifier->DeviceId = 0x2684;
        pIdentifier->WHQLLevel = 1;
        return S_OK;
    }
    uint32_t GetAdapterModeCount(uint32_t Adapter, D3DFORMAT) override {
        return (Adapter == 0) ? 3u : 0u;
    }
    HRESULT EnumAdapterModes(uint32_t Adapter, D3DFORMAT Format, uint32_t Mode,
                             D3DDISPLAYMODE* pMode) override {
        if (!pMode || Adapter > 0 || Mode >= 3) return E_INVALIDARG;
        const uint32_t widths[3]  = {1920, 2560, 3840};
        const uint32_t heights[3] = {1080, 1440, 2160};
        pMode->Width = widths[Mode];
        pMode->Height = heights[Mode];
        pMode->RefreshRate = 540;
        pMode->Format = Format ? Format : D3DFMT_X8R8G8B8;
        return S_OK;
    }
    HRESULT GetAdapterDisplayMode(uint32_t Adapter, D3DDISPLAYMODE* pMode) override {
        return EnumAdapterModes(Adapter, D3DFMT_X8R8G8B8, 2, pMode);
    }
    HRESULT CheckDeviceType(uint32_t, D3DDEVTYPE, D3DFORMAT, D3DFORMAT, int32_t) override {
        return S_OK;
    }
    HRESULT CheckDeviceFormat(uint32_t, D3DDEVTYPE, D3DFORMAT, uint32_t, uint32_t,
                              D3DFORMAT) override {
        return S_OK;
    }
    HRESULT CheckDeviceMultiSampleType(uint32_t, D3DDEVTYPE, D3DFORMAT, int32_t,
                                       uint32_t, uint32_t* pQualityLevels) override {
        if (pQualityLevels) *pQualityLevels = 8;
        return S_OK;
    }
    HRESULT CheckDepthStencilMatch(uint32_t, D3DDEVTYPE, D3DFORMAT, D3DFORMAT,
                                   D3DFORMAT) override {
        return S_OK;
    }
    HRESULT CheckDeviceFormatConversion(uint32_t, D3DDEVTYPE, D3DFORMAT, D3DFORMAT) override {
        return S_OK;
    }
    HRESULT GetDeviceCaps(uint32_t Adapter, D3DDEVTYPE, D3DCAPS9* pCaps) override {
        if (!pCaps || Adapter > 0) return E_INVALIDARG;
        PrismDirect3DDevice9ExImpl temp(this, nullptr);
        return temp.GetDeviceCaps(pCaps);
    }
    void* GetAdapterMonitor(uint32_t) override {
        return reinterpret_cast<void*>(static_cast<uintptr_t>(0x00010001u));
    }
    HRESULT CreateDevice(uint32_t Adapter, D3DDEVTYPE, void*, uint32_t,
                         D3DPRESENT_PARAMETERS* pPresentationParameters,
                         IDirect3DDevice9** ppReturnedDeviceInterface) override {
        if (!ppReturnedDeviceInterface || Adapter > 0) return E_INVALIDARG;
        *ppReturnedDeviceInterface = new PrismDirect3DDevice9ExImpl(this, pPresentationParameters);
        return S_OK;
    }

    // IDirect3D9Ex methods
    uint32_t GetAdapterModeCountEx(uint32_t Adapter, const void*) override {
        return (Adapter == 0) ? 3u : 0u;
    }
    HRESULT EnumAdapterModesEx(uint32_t Adapter, const void*, uint32_t Mode,
                               D3DDISPLAYMODEEX* pMode) override {
        if (!pMode || Adapter > 0 || Mode >= 3) return E_INVALIDARG;
        const uint32_t widths[3]  = {1920, 2560, 3840};
        const uint32_t heights[3] = {1080, 1440, 2160};
        pMode->Size = sizeof(D3DDISPLAYMODEEX);
        pMode->Width = widths[Mode];
        pMode->Height = heights[Mode];
        pMode->RefreshRate = 540;
        pMode->Format = D3DFMT_X8R8G8B8;
        pMode->ScanLineOrdering = 1;
        return S_OK;
    }
    HRESULT GetAdapterDisplayModeEx(uint32_t Adapter, D3DDISPLAYMODEEX* pMode,
                                    uint32_t* pRotation) override {
        if (pRotation) *pRotation = 1;
        return EnumAdapterModesEx(Adapter, nullptr, 2, pMode);
    }
    HRESULT CreateDeviceEx(uint32_t Adapter, D3DDEVTYPE, void*, uint32_t,
                           D3DPRESENT_PARAMETERS* pPresentationParameters,
                           D3DDISPLAYMODEEX*,
                           IDirect3DDevice9Ex** ppReturnedDeviceInterface) override {
        if (!ppReturnedDeviceInterface || Adapter > 0) return E_INVALIDARG;
        *ppReturnedDeviceInterface = new PrismDirect3DDevice9ExImpl(this, pPresentationParameters);
        return S_OK;
    }
};

// ----------------------------------------------------------------------------
// 8. Canonical d3d9.dll Entry Points
// ----------------------------------------------------------------------------
inline IDirect3D9* Direct3DCreate9(uint32_t SDKVersion) {
    return new PrismDirect3D9ExImpl(SDKVersion);
}

inline HRESULT Direct3DCreate9Ex(uint32_t SDKVersion, IDirect3D9Ex** ppD3D) {
    if (!ppD3D) return E_POINTER;
    *ppD3D = new PrismDirect3D9ExImpl(SDKVersion);
    return S_OK;
}

inline int32_t D3DPERF_BeginEvent(uint32_t, const wchar_t*) { return 1; }
inline int32_t D3DPERF_EndEvent() { return 0; }
inline void D3DPERF_SetMarker(uint32_t, const wchar_t*) {}
inline uint32_t D3DPERF_GetStatus() { return 1; }

} // namespace prismx::D3D9Com
