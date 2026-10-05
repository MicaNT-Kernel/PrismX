// ============================================================================
// PrismX: DirectX Graphics Infrastructure (DXGI 1.0 / 1.1 Compatible)
// 
// Strict Clean-Room Implementation in ISO C++23
// Open Specs: https://github.com/microsoft/DirectX-Headers (directx/dxgi*.h)
// ============================================================================

#pragma once

#include "types.hpp"
#include <vector>
#include <string>
#include <atomic>
#include <functional>
#include <cstring>
#include <cmath>

namespace prismx {

// ============================================================================
// 1. Standard DXGI Formats & Enums
// ============================================================================

enum DXGI_FORMAT : uint32_t {
    DXGI_FORMAT_UNKNOWN                    = 0,
    DXGI_FORMAT_R32G32B32A32_TYPELESS       = 1,
    DXGI_FORMAT_R32G32B32A32_FLOAT          = 2,
    DXGI_FORMAT_R32G32B32_FLOAT             = 6,
    DXGI_FORMAT_R16G16B16A16_FLOAT          = 10,
    DXGI_FORMAT_R16G16B16A16_UNORM          = 11,
    DXGI_FORMAT_R32G32_FLOAT                = 16,
    DXGI_FORMAT_R8G8B8A8_TYPELESS           = 27,
    DXGI_FORMAT_R8G8B8A8_UNORM              = 28,
    DXGI_FORMAT_R8G8B8A8_UNORM_SRGB         = 29,
    DXGI_FORMAT_R8G8B8A8_UINT               = 30,
    DXGI_FORMAT_R8G8B8A8_SNORM              = 31,
    DXGI_FORMAT_R32_FLOAT                   = 41,
    DXGI_FORMAT_R32_UINT                    = 42,
    DXGI_FORMAT_D32_FLOAT                   = 40,
    DXGI_FORMAT_D24_UNORM_S8_UINT           = 45,
    DXGI_FORMAT_R16_UINT                    = 57,
    DXGI_FORMAT_B8G8R8A8_UNORM              = 87,
    DXGI_FORMAT_B8G8R8X8_UNORM              = 88,
    DXGI_FORMAT_B8G8R8A8_UNORM_SRGB         = 91
};

enum DXGI_MODE_SCANLINE_ORDER : uint32_t {
    DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED        = 0,
    DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE        = 1,
    DXGI_MODE_SCANLINE_ORDER_UPPER_FIELD_FIRST  = 2,
    DXGI_MODE_SCANLINE_ORDER_LOWER_FIELD_FIRST  = 3
};

enum DXGI_MODE_SCALING : uint32_t {
    DXGI_MODE_SCALING_UNSPECIFIED   = 0,
    DXGI_MODE_SCALING_CENTERED      = 1,
    DXGI_MODE_SCALING_STRETCHED     = 2
};

struct DXGI_RATIONAL {
    uint32_t Numerator;
    uint32_t Denominator;
};

struct DXGI_MODE_DESC {
    uint32_t Width;
    uint32_t Height;
    DXGI_RATIONAL RefreshRate;
    DXGI_FORMAT Format;
    DXGI_MODE_SCANLINE_ORDER ScanlineOrdering;
    DXGI_MODE_SCALING Scaling;
};

struct DXGI_SAMPLE_DESC {
    uint32_t Count;
    uint32_t Quality;
};

enum DXGI_SWAP_EFFECT : uint32_t {
    DXGI_SWAP_EFFECT_DISCARD         = 0,
    DXGI_SWAP_EFFECT_SEQUENTIAL      = 1,
    DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL = 3,
    DXGI_SWAP_EFFECT_FLIP_DISCARD    = 4
};

enum class DXGI_ALPHA_MODE : uint32_t {
    UNSPECIFIED   = 0,
    PREMULTIPLIED = 1,
    STRAIGHT      = 2,
    IGNORE        = 3,
    FORCE_DWORD   = 0xFFFFFFFF
};

enum DXGI_SWAP_CHAIN_FLAG : uint32_t {
    DXGI_SWAP_CHAIN_FLAG_NONPREROTATED                          = 1,
    DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH                      = 2,
    DXGI_SWAP_CHAIN_FLAG_GDI_COMPATIBLE                         = 4,
    DXGI_SWAP_CHAIN_FLAG_RESTRICTED_CONTENT                     = 8,
    DXGI_SWAP_CHAIN_FLAG_RESTRICT_SHARED_RESOURCE_DRIVER        = 16,
    DXGI_SWAP_CHAIN_FLAG_DISPLAY_ONLY                           = 32,
    DXGI_SWAP_CHAIN_FLAG_FRAME_LATENCY_WAITABLE_OBJECT          = 64,
    DXGI_SWAP_CHAIN_FLAG_FOREGROUND_LAYER                       = 128,
    DXGI_SWAP_CHAIN_FLAG_FULLSCREEN_VIDEO                       = 256,
    DXGI_SWAP_CHAIN_FLAG_HW_PROTECTED                           = 512,
    DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING                          = 2048
};

enum DXGI_USAGE : uint32_t {
    DXGI_USAGE_SHADER_INPUT         = 1 << (0 + 4),
    DXGI_USAGE_RENDER_TARGET_OUTPUT = 1 << (1 + 4),
    DXGI_USAGE_BACK_BUFFER          = 1 << (2 + 4),
    DXGI_USAGE_SHARED               = 1 << (3 + 4),
    DXGI_USAGE_READ_ONLY            = 1 << (4 + 4),
    DXGI_USAGE_DISCARD_ON_PRESENT   = 1 << (5 + 4),
    DXGI_USAGE_UNORDERED_ACCESS     = 1 << (6 + 4)
};

struct DXGI_SWAP_CHAIN_DESC {
    DXGI_MODE_DESC BufferDesc;
    DXGI_SAMPLE_DESC SampleDesc;
    uint32_t BufferUsage;
    uint32_t BufferCount;
    void* OutputWindow;
    int32_t Windowed;
    DXGI_SWAP_EFFECT SwapEffect;
    uint32_t Flags;
};

struct DXGI_ADAPTER_DESC {
    wchar_t Description[128];
    uint32_t VendorId;
    uint32_t DeviceId;
    uint32_t SubSysId;
    uint32_t Revision;
    size_t DedicatedVideoMemory;
    size_t DedicatedSystemMemory;
    size_t SharedSystemMemory;
    LUID AdapterLuid;
};

struct DXGI_ADAPTER_DESC1 {
    wchar_t Description[128];
    uint32_t VendorId;
    uint32_t DeviceId;
    uint32_t SubSysId;
    uint32_t Revision;
    size_t DedicatedVideoMemory;
    size_t DedicatedSystemMemory;
    size_t SharedSystemMemory;
    LUID AdapterLuid;
    uint32_t Flags;
};

struct DXGI_OUTPUT_DESC {
    wchar_t DeviceName[32];
    RECT DesktopCoordinates;
    int32_t AttachedToDesktop;
    uint32_t Rotation;
    void* Monitor;
};

struct DXGI_FRAME_STATISTICS {
    uint32_t PresentCount;
    uint32_t PresentRefreshCount;
    uint32_t SyncRefreshCount;
    int64_t SyncQPCTime;
    int64_t SyncGPUTime;
};

// DXGI Errors
inline constexpr HRESULT DXGI_ERROR_INVALID_CALL  = static_cast<HRESULT>(0x887A0001L);
inline constexpr HRESULT DXGI_ERROR_NOT_FOUND     = static_cast<HRESULT>(0x887A0002L);
inline constexpr HRESULT DXGI_ERROR_MORE_DATA     = static_cast<HRESULT>(0x887A0003L);
inline constexpr HRESULT DXGI_ERROR_UNSUPPORTED   = static_cast<HRESULT>(0x887A0004L);
inline constexpr HRESULT DXGI_ERROR_DEVICE_REMOVED= static_cast<HRESULT>(0x887A0005L);
inline constexpr HRESULT DXGI_ERROR_DEVICE_RESET  = static_cast<HRESULT>(0x887A0007L);
inline constexpr HRESULT DXGI_STATUS_OCCLUDED     = static_cast<HRESULT>(0x087A0001L);

// ============================================================================
// 2. GUID Declarations
// ============================================================================

inline constexpr IID IID_IDXGIObject = 
    { 0xaec22fb8, 0x76f3, 0x4639, { 0x9b, 0xe0, 0x28, 0xeb, 0x43, 0xa6, 0x7a, 0x2e } };

inline constexpr IID IID_IDXGIDeviceSubObject = 
    { 0x3d3e0379, 0xd9de, 0x4d58, { 0xbb, 0x6c, 0x18, 0xd4, 0x19, 0x92, 0x9f, 0x6a } };

inline constexpr IID IID_IDXGIResource = 
    { 0x035f3ab4, 0x482e, 0x4e50, { 0xb4, 0x1f, 0x8a, 0x7f, 0x8b, 0xd8, 0x96, 0x0b } };

inline constexpr IID IID_IDXGISurface = 
    { 0xcafcb56c, 0x6ac3, 0x4889, { 0xbf, 0x47, 0x9e, 0x23, 0xbb, 0xd2, 0x60, 0xec } };

inline constexpr IID IID_IDXGIAdapter = 
    { 0x2411e7e1, 0x12ac, 0x4ccf, { 0xbd, 0x14, 0x97, 0x98, 0xe8, 0x53, 0x4d, 0x00 } };

inline constexpr IID IID_IDXGIAdapter1 = 
    { 0x29038f61, 0x3839, 0x4626, { 0x91, 0xfd, 0x08, 0x68, 0x79, 0x01, 0x1a, 0x05 } };

inline constexpr IID IID_IDXGIOutput = 
    { 0xae02eedb, 0xc735, 0x4690, { 0x8d, 0x52, 0x5a, 0x8d, 0xc2, 0x02, 0x13, 0xaa } };

inline constexpr IID IID_IDXGISwapChain = 
    { 0x310d36a0, 0xd0e7, 0x4c40, { 0x90, 0x97, 0x62, 0xe0, 0x39, 0x04, 0xbe, 0x4e } };

inline constexpr IID IID_IDXGIFactory = 
    { 0x7b716634, 0x20c7, 0x44ae, { 0xb5, 0x1a, 0x97, 0x43, 0x25, 0x6e, 0x29, 0x78 } };

inline constexpr IID IID_IDXGIFactory1 = 
    { 0x770aae78, 0xf26f, 0x4dba, { 0xa8, 0x29, 0x25, 0x3c, 0x83, 0xd1, 0xb3, 0x87 } };

inline constexpr IID IID_IDXGIDevice = 
    { 0x54ec77fa, 0x1377, 0x44e6, { 0x8c, 0x32, 0x88, 0xfd, 0x5f, 0x44, 0xc8, 0x4c } };

// Forward declarations
class IDXGIObject;
class IDXGIDevice;
class IDXGIDeviceSubObject;
class IDXGIResource;
class IDXGISurface;
class IDXGIAdapter;
class IDXGIAdapter1;
class IDXGIOutput;
class IDXGISwapChain;
class IDXGIFactory;
class IDXGIFactory1;

// ============================================================================
// 3. COM Interface Base Declarations
// ============================================================================

class IDXGIObject : public IUnknown {
public:
    virtual HRESULT SetPrivateData(const IID& Name, uint32_t DataSize, const void* pData) = 0;
    virtual HRESULT SetPrivateDataInterface(const IID& Name, const IUnknown* pUnknown) = 0;
    virtual HRESULT GetPrivateData(const IID& Name, uint32_t* pDataSize, void* pData) = 0;
    virtual HRESULT GetParent(const IID& riid, void** ppParent) = 0;
};

class IDXGISurface : public IDXGIObject {
public:
    virtual HRESULT GetDesc(DXGI_MODE_DESC* pDesc) = 0;
    virtual HRESULT Map(void** ppSurfaceData, uint32_t* pPitch) = 0;
    virtual HRESULT Unmap() = 0;
};

class IDXGIOutput : public IDXGIObject {
public:
    virtual HRESULT GetDesc(DXGI_OUTPUT_DESC* pDesc) = 0;
    virtual HRESULT GetDisplayModeList(DXGI_FORMAT EnumFormat, uint32_t Flags, uint32_t* pNumModes, DXGI_MODE_DESC* pDesc) = 0;
    virtual HRESULT FindClosestMatchingMode(const DXGI_MODE_DESC* pModeToMatch, DXGI_MODE_DESC* pClosestMatch, IUnknown* pConcernedDevice) = 0;
    virtual HRESULT WaitForVBlank() = 0;
    virtual HRESULT TakeOwnership(IUnknown* pDevice, int32_t Exclusive) = 0;
    virtual void ReleaseOwnership() = 0;
};

class IDXGIAdapter : public IDXGIObject {
public:
    virtual HRESULT EnumOutputs(uint32_t Output, IDXGIOutput** ppOutput) = 0;
    virtual HRESULT GetDesc(DXGI_ADAPTER_DESC* pDesc) = 0;
    virtual HRESULT CheckInterfaceSupport(const IID& InterfaceName, int64_t* pUMDVersion) = 0;
};

class IDXGIAdapter1 : public IDXGIAdapter {
public:
    virtual HRESULT GetDesc1(DXGI_ADAPTER_DESC1* pDesc) = 0;
};

class IDXGISwapChain : public IDXGIObject {
public:
    virtual HRESULT Present(uint32_t SyncInterval, uint32_t Flags) = 0;
    virtual HRESULT GetBuffer(uint32_t Buffer, const IID& riid, void** ppSurface) = 0;
    virtual HRESULT SetFullscreenState(int32_t Fullscreen, IDXGIOutput* pTarget) = 0;
    virtual HRESULT GetFullscreenState(int32_t* pFullscreen, IDXGIOutput** ppTarget) = 0;
    virtual HRESULT GetDesc(DXGI_SWAP_CHAIN_DESC* pDesc) = 0;
    virtual HRESULT ResizeBuffers(uint32_t BufferCount, uint32_t Width, uint32_t Height, DXGI_FORMAT NewFormat, uint32_t SwapChainFlags) = 0;
    virtual HRESULT ResizeTarget(const DXGI_MODE_DESC* pNewTargetParameters) = 0;
    virtual HRESULT GetContainingOutput(IDXGIOutput** ppOutput) = 0;
    virtual HRESULT GetFrameStatistics(DXGI_FRAME_STATISTICS* pStats) = 0;
    virtual HRESULT GetLastPresentCount(uint32_t* pLastPresentCount) = 0;
};

class IDXGIDevice : public IDXGIObject {
public:
    virtual HRESULT GetAdapter(IDXGIAdapter** pAdapter) = 0;
    virtual HRESULT CreateSurface(const void* pDesc, uint32_t NumSurfaces, uint32_t Usage, const void* pSharedResource, IDXGISurface** ppSurface) = 0;
    virtual HRESULT QueryResourceResidency(IUnknown* const* ppResources, uint32_t* pResidencyStatus, uint32_t NumResources) = 0;
    virtual HRESULT SetGPUThreadPriority(int32_t Priority) = 0;
    virtual HRESULT GetGPUThreadPriority(int32_t* pPriority) = 0;
};

class IDXGIFactory : public IDXGIObject {
public:
    virtual HRESULT EnumAdapters(uint32_t Adapter, IDXGIAdapter** ppAdapter) = 0;
    virtual HRESULT MakeWindowAssociation(void* WindowHandle, uint32_t Flags) = 0;
    virtual HRESULT GetWindowAssociation(void** pWindowHandle) = 0;
    virtual HRESULT CreateSwapChain(IUnknown* pDevice, DXGI_SWAP_CHAIN_DESC* pDesc, IDXGISwapChain** ppSwapChain) = 0;
    virtual HRESULT CreateSoftwareAdapter(void* Module, IDXGIAdapter** ppAdapter) = 0;
};

class IDXGIFactory1 : public IDXGIFactory {
public:
    virtual HRESULT EnumAdapters1(uint32_t Adapter, IDXGIAdapter1** ppAdapter) = 0;
    virtual HRESULT IsCurrent() = 0;
};

// ============================================================================
// 4. Concrete Implementations
// ============================================================================

class PrismXSurfaceImpl : public IDXGISurface {
private:
    std::atomic<uint32_t> m_refCount{ 1 };
    DXGI_MODE_DESC m_desc{};
    std::vector<uint8_t> m_pixelData;
    uint32_t m_pitch{ 0 };
    bool m_isMapped{ false };

public:
    PrismXSurfaceImpl(uint32_t width, uint32_t height, DXGI_FORMAT format) {
        m_desc.Width = width;
        m_desc.Height = height;
        m_desc.Format = format;
        m_desc.RefreshRate = { 60, 1 };
        m_desc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE;
        m_desc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
        m_pitch = width * 4;
        m_pixelData.resize(static_cast<size_t>(m_pitch) * height, 0);
    }

    uint8_t* GetRawData() noexcept { return m_pixelData.data(); }
    size_t GetDataSize() const noexcept { return m_pixelData.size(); }
    uint32_t GetWidth() const noexcept { return m_desc.Width; }
    uint32_t GetHeight() const noexcept { return m_desc.Height; }
    uint32_t GetPitch() const noexcept { return m_pitch; }

    HRESULT QueryInterface(const IID& riid, void** ppvObject) override {
        if (!ppvObject) return E_POINTER;
        if (riid == IID_IUnknown || riid == IID_IDXGIObject || riid == IID_IDXGISurface) {
            *ppvObject = static_cast<IDXGISurface*>(this);
            AddRef();
            return S_OK;
        }
        *ppvObject = nullptr;
        return E_NOINTERFACE;
    }

    uint32_t AddRef() override { return ++m_refCount; }
    uint32_t Release() override {
        uint32_t count = --m_refCount;
        if (count == 0) delete this;
        return count;
    }

    HRESULT SetPrivateData(const IID&, uint32_t, const void*) override { return S_OK; }
    HRESULT SetPrivateDataInterface(const IID&, const IUnknown*) override { return S_OK; }
    HRESULT GetPrivateData(const IID&, uint32_t*, void*) override { return S_OK; }
    HRESULT GetParent(const IID&, void**) override { return S_OK; }

    HRESULT GetDesc(DXGI_MODE_DESC* pDesc) override {
        if (!pDesc) return E_POINTER;
        *pDesc = m_desc;
        return S_OK;
    }

    HRESULT Map(void** ppSurfaceData, uint32_t* pPitch) override {
        if (!ppSurfaceData || !pPitch) return E_POINTER;
        *ppSurfaceData = m_pixelData.data();
        *pPitch = m_pitch;
        m_isMapped = true;
        return S_OK;
    }

    HRESULT Unmap() override {
        m_isMapped = false;
        return S_OK;
    }
};

class PrismXOutputImpl : public IDXGIOutput {
private:
    std::atomic<uint32_t> m_refCount{ 1 };
    DXGI_OUTPUT_DESC m_desc{};

public:
    PrismXOutputImpl(const std::wstring& name, int32_t width, int32_t height) {
        std::memset(&m_desc, 0, sizeof(m_desc));
        size_t len = (std::min)(name.length(), size_t(31));
        std::memcpy(m_desc.DeviceName, name.data(), len * sizeof(wchar_t));
        m_desc.DeviceName[len] = L'\0';
        m_desc.DesktopCoordinates = { 0, 0, width, height };
        m_desc.AttachedToDesktop = 1;
        m_desc.Rotation = 0;
        m_desc.Monitor = reinterpret_cast<void*>(0x10001);
    }

    HRESULT QueryInterface(const IID& riid, void** ppvObject) override {
        if (!ppvObject) return E_POINTER;
        if (riid == IID_IUnknown || riid == IID_IDXGIObject || riid == IID_IDXGIOutput) {
            *ppvObject = static_cast<IDXGIOutput*>(this);
            AddRef();
            return S_OK;
        }
        *ppvObject = nullptr;
        return E_NOINTERFACE;
    }

    uint32_t AddRef() override { return ++m_refCount; }
    uint32_t Release() override {
        uint32_t count = --m_refCount;
        if (count == 0) delete this;
        return count;
    }

    HRESULT SetPrivateData(const IID&, uint32_t, const void*) override { return S_OK; }
    HRESULT SetPrivateDataInterface(const IID&, const IUnknown*) override { return S_OK; }
    HRESULT GetPrivateData(const IID&, uint32_t*, void*) override { return S_OK; }
    HRESULT GetParent(const IID&, void**) override { return S_OK; }

    HRESULT GetDesc(DXGI_OUTPUT_DESC* pDesc) override {
        if (!pDesc) return E_POINTER;
        *pDesc = m_desc;
        return S_OK;
    }

    HRESULT GetDisplayModeList(DXGI_FORMAT, uint32_t, uint32_t* pNumModes, DXGI_MODE_DESC* pDesc) override {
        if (!pNumModes) return E_POINTER;
        if (!pDesc) {
            *pNumModes = 3;
            return S_OK;
        }
        pDesc[0] = { 1920, 1080, { 60, 1 }, DXGI_FORMAT_B8G8R8A8_UNORM, DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE, DXGI_MODE_SCALING_UNSPECIFIED };
        pDesc[1] = { 1280, 720, { 60, 1 }, DXGI_FORMAT_B8G8R8A8_UNORM, DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE, DXGI_MODE_SCALING_UNSPECIFIED };
        pDesc[2] = { 1024, 768, { 60, 1 }, DXGI_FORMAT_B8G8R8A8_UNORM, DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE, DXGI_MODE_SCALING_UNSPECIFIED };
        *pNumModes = 3;
        return S_OK;
    }

    HRESULT FindClosestMatchingMode(const DXGI_MODE_DESC* pModeToMatch, DXGI_MODE_DESC* pClosestMatch, IUnknown*) override {
        if (!pModeToMatch || !pClosestMatch) return E_POINTER;
        *pClosestMatch = *pModeToMatch;
        return S_OK;
    }

    HRESULT WaitForVBlank() override { return S_OK; }
    HRESULT TakeOwnership(IUnknown*, int32_t) override { return S_OK; }
    void ReleaseOwnership() override {}
};

class PrismXAdapterImpl : public IDXGIAdapter1 {
private:
    std::atomic<uint32_t> m_refCount{ 1 };
    DXGI_ADAPTER_DESC1 m_desc{};
    std::vector<IDXGIOutput*> m_outputs;

public:
    PrismXAdapterImpl(const std::wstring& name, uint32_t vendorId, uint32_t deviceId, size_t vramBytes, bool isSoftware = false) {
        std::memset(&m_desc, 0, sizeof(m_desc));
        size_t len = (std::min)(name.length(), size_t(127));
        std::memcpy(m_desc.Description, name.data(), len * sizeof(wchar_t));
        m_desc.Description[len] = L'\0';
        m_desc.VendorId = vendorId;
        m_desc.DeviceId = deviceId;
        m_desc.SubSysId = 0x0001;
        m_desc.Revision = 0x01;
        m_desc.DedicatedVideoMemory = vramBytes;
        m_desc.DedicatedSystemMemory = 256 * 1024 * 1024;
        m_desc.SharedSystemMemory = 1024 * 1024 * 1024;
        m_desc.AdapterLuid = { 0x00000001, 0x00000000 };
        m_desc.Flags = isSoftware ? 2 : 0;
        m_outputs.push_back(new PrismXOutputImpl(L"\\\\.\\DISPLAY1", 1920, 1080));
    }

    ~PrismXAdapterImpl() override {
        for (auto* out : m_outputs) out->Release();
    }

    HRESULT QueryInterface(const IID& riid, void** ppvObject) override {
        if (!ppvObject) return E_POINTER;
        if (riid == IID_IUnknown || riid == IID_IDXGIObject || riid == IID_IDXGIAdapter || riid == IID_IDXGIAdapter1) {
            *ppvObject = static_cast<IDXGIAdapter1*>(this);
            AddRef();
            return S_OK;
        }
        *ppvObject = nullptr;
        return E_NOINTERFACE;
    }

    uint32_t AddRef() override { return ++m_refCount; }
    uint32_t Release() override {
        uint32_t count = --m_refCount;
        if (count == 0) delete this;
        return count;
    }

    HRESULT SetPrivateData(const IID&, uint32_t, const void*) override { return S_OK; }
    HRESULT SetPrivateDataInterface(const IID&, const IUnknown*) override { return S_OK; }
    HRESULT GetPrivateData(const IID&, uint32_t*, void*) override { return S_OK; }
    HRESULT GetParent(const IID&, void**) override { return S_OK; }

    HRESULT EnumOutputs(uint32_t Output, IDXGIOutput** ppOutput) override {
        if (!ppOutput) return E_POINTER;
        if (Output >= m_outputs.size()) return DXGI_ERROR_NOT_FOUND;
        *ppOutput = m_outputs[Output];
        (*ppOutput)->AddRef();
        return S_OK;
    }

    HRESULT GetDesc(DXGI_ADAPTER_DESC* pDesc) override {
        if (!pDesc) return E_POINTER;
        std::memcpy(pDesc->Description, m_desc.Description, sizeof(pDesc->Description));
        pDesc->VendorId = m_desc.VendorId;
        pDesc->DeviceId = m_desc.DeviceId;
        pDesc->SubSysId = m_desc.SubSysId;
        pDesc->Revision = m_desc.Revision;
        pDesc->DedicatedVideoMemory = m_desc.DedicatedVideoMemory;
        pDesc->DedicatedSystemMemory = m_desc.DedicatedSystemMemory;
        pDesc->SharedSystemMemory = m_desc.SharedSystemMemory;
        pDesc->AdapterLuid = m_desc.AdapterLuid;
        return S_OK;
    }

    HRESULT GetDesc1(DXGI_ADAPTER_DESC1* pDesc) override {
        if (!pDesc) return E_POINTER;
        *pDesc = m_desc;
        return S_OK;
    }

    HRESULT CheckInterfaceSupport(const IID&, int64_t* pUMDVersion) override {
        if (pUMDVersion) *pUMDVersion = 0x00010000;
        return S_OK;
    }
};

class PrismXSwapChainImpl : public IDXGISwapChain {
private:
    std::atomic<uint32_t> m_refCount{ 1 };
    DXGI_SWAP_CHAIN_DESC m_desc{};
    std::vector<PrismXSurfaceImpl*> m_backBuffers;
    uint32_t m_currentBackBuffer{ 0 };
    uint32_t m_presentCount{ 0 };
    int32_t m_isFullscreen{ 0 };
    std::function<void(const uint8_t*, uint32_t, uint32_t, uint32_t)> m_presentCallback;

public:
    PrismXSwapChainImpl(const DXGI_SWAP_CHAIN_DESC& desc, std::function<void(const uint8_t*, uint32_t, uint32_t, uint32_t)> callback = nullptr)
        : m_desc(desc), m_presentCallback(callback) {
        uint32_t bufferCount = (desc.BufferCount == 0) ? 1 : desc.BufferCount;
        for (uint32_t i = 0; i < bufferCount; ++i) {
            m_backBuffers.push_back(new PrismXSurfaceImpl(desc.BufferDesc.Width, desc.BufferDesc.Height, desc.BufferDesc.Format));
        }
    }

    ~PrismXSwapChainImpl() override {
        for (auto* buf : m_backBuffers) buf->Release();
    }

    PrismXSurfaceImpl* GetActiveBackBuffer() noexcept {
        if (m_backBuffers.empty()) return nullptr;
        return m_backBuffers[m_currentBackBuffer];
    }

    HRESULT QueryInterface(const IID& riid, void** ppvObject) override {
        if (!ppvObject) return E_POINTER;
        if (riid == IID_IUnknown || riid == IID_IDXGIObject || riid == IID_IDXGISwapChain) {
            *ppvObject = static_cast<IDXGISwapChain*>(this);
            AddRef();
            return S_OK;
        }
        *ppvObject = nullptr;
        return E_NOINTERFACE;
    }

    uint32_t AddRef() override { return ++m_refCount; }
    uint32_t Release() override {
        uint32_t count = --m_refCount;
        if (count == 0) delete this;
        return count;
    }

    HRESULT SetPrivateData(const IID&, uint32_t, const void*) override { return S_OK; }
    HRESULT SetPrivateDataInterface(const IID&, const IUnknown*) override { return S_OK; }
    HRESULT GetPrivateData(const IID&, uint32_t*, void*) override { return S_OK; }
    HRESULT GetParent(const IID&, void**) override { return S_OK; }

    HRESULT Present(uint32_t /*SyncInterval*/, uint32_t /*Flags*/) override {
        if (m_backBuffers.empty()) return E_FAIL;
        auto* currentBuffer = m_backBuffers[m_currentBackBuffer];
        m_presentCount++;

        if (m_presentCallback && currentBuffer) {
            m_presentCallback(currentBuffer->GetRawData(),
                              currentBuffer->GetWidth(),
                              currentBuffer->GetHeight(),
                              currentBuffer->GetPitch());
        }

        if (m_desc.SwapEffect == DXGI_SWAP_EFFECT_FLIP_DISCARD ||
            m_desc.SwapEffect == DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL) {
            m_currentBackBuffer = (m_currentBackBuffer + 1) % static_cast<uint32_t>(m_backBuffers.size());
        }
        return S_OK;
    }

    HRESULT GetBuffer(uint32_t Buffer, const IID& riid, void** ppSurface) override {
        if (!ppSurface) return E_POINTER;
        if (Buffer >= m_backBuffers.size()) return DXGI_ERROR_INVALID_CALL;
        return m_backBuffers[Buffer]->QueryInterface(riid, ppSurface);
    }

    HRESULT SetFullscreenState(int32_t Fullscreen, IDXGIOutput*) override {
        m_isFullscreen = Fullscreen;
        return S_OK;
    }

    HRESULT GetFullscreenState(int32_t* pFullscreen, IDXGIOutput** ppTarget) override {
        if (pFullscreen) *pFullscreen = m_isFullscreen;
        if (ppTarget) *ppTarget = nullptr;
        return S_OK;
    }

    HRESULT GetDesc(DXGI_SWAP_CHAIN_DESC* pDesc) override {
        if (!pDesc) return E_POINTER;
        *pDesc = m_desc;
        return S_OK;
    }

    HRESULT ResizeBuffers(uint32_t BufferCount, uint32_t Width, uint32_t Height, DXGI_FORMAT NewFormat, uint32_t /*SwapChainFlags*/) override {
        for (auto* buf : m_backBuffers) buf->Release();
        m_backBuffers.clear();

        m_desc.BufferCount = (BufferCount == 0) ? m_desc.BufferCount : BufferCount;
        m_desc.BufferDesc.Width = (Width == 0) ? m_desc.BufferDesc.Width : Width;
        m_desc.BufferDesc.Height = (Height == 0) ? m_desc.BufferDesc.Height : Height;
        if (NewFormat != DXGI_FORMAT_UNKNOWN) m_desc.BufferDesc.Format = NewFormat;

        for (uint32_t i = 0; i < m_desc.BufferCount; ++i) {
            m_backBuffers.push_back(new PrismXSurfaceImpl(m_desc.BufferDesc.Width, m_desc.BufferDesc.Height, m_desc.BufferDesc.Format));
        }
        m_currentBackBuffer = 0;
        return S_OK;
    }

    HRESULT ResizeTarget(const DXGI_MODE_DESC* pNewTargetParameters) override {
        if (!pNewTargetParameters) return E_POINTER;
        m_desc.BufferDesc = *pNewTargetParameters;
        return S_OK;
    }

    HRESULT GetContainingOutput(IDXGIOutput** ppOutput) override {
        if (!ppOutput) return E_POINTER;
        *ppOutput = new PrismXOutputImpl(L"\\\\.\\DISPLAY1", m_desc.BufferDesc.Width, m_desc.BufferDesc.Height);
        return S_OK;
    }

    HRESULT GetFrameStatistics(DXGI_FRAME_STATISTICS* pStats) override {
        if (!pStats) return E_POINTER;
        pStats->PresentCount = m_presentCount;
        pStats->PresentRefreshCount = m_presentCount;
        pStats->SyncRefreshCount = m_presentCount;
        pStats->SyncQPCTime = 0;
        pStats->SyncGPUTime = 0;
        return S_OK;
    }

    HRESULT GetLastPresentCount(uint32_t* pLastPresentCount) override {
        if (!pLastPresentCount) return E_POINTER;
        *pLastPresentCount = m_presentCount;
        return S_OK;
    }
};

class PrismXFactoryImpl : public IDXGIFactory1 {
private:
    std::atomic<uint32_t> m_refCount{ 1 };
    std::vector<IDXGIAdapter1*> m_adapters;

public:
    PrismXFactoryImpl() {
        m_adapters.push_back(new PrismXAdapterImpl(L"PrismX Hardware Rasterizer", 0x1414, 0x0080, 2048ULL * 1024 * 1024, false));
        m_adapters.push_back(new PrismXAdapterImpl(L"PrismX WARP Software Driver", 0x1414, 0x008c, 512ULL * 1024 * 1024, true));
    }

    ~PrismXFactoryImpl() override {
        for (auto* a : m_adapters) a->Release();
    }

    HRESULT QueryInterface(const IID& riid, void** ppvObject) override {
        if (!ppvObject) return E_POINTER;
        if (riid == IID_IUnknown || riid == IID_IDXGIObject || riid == IID_IDXGIFactory || riid == IID_IDXGIFactory1) {
            *ppvObject = static_cast<IDXGIFactory1*>(this);
            AddRef();
            return S_OK;
        }
        *ppvObject = nullptr;
        return E_NOINTERFACE;
    }

    uint32_t AddRef() override { return ++m_refCount; }
    uint32_t Release() override {
        uint32_t count = --m_refCount;
        if (count == 0) delete this;
        return count;
    }

    HRESULT SetPrivateData(const IID&, uint32_t, const void*) override { return S_OK; }
    HRESULT SetPrivateDataInterface(const IID&, const IUnknown*) override { return S_OK; }
    HRESULT GetPrivateData(const IID&, uint32_t*, void*) override { return S_OK; }
    HRESULT GetParent(const IID&, void**) override { return S_OK; }

    HRESULT EnumAdapters(uint32_t Adapter, IDXGIAdapter** ppAdapter) override {
        if (!ppAdapter) return E_POINTER;
        if (Adapter >= m_adapters.size()) return DXGI_ERROR_NOT_FOUND;
        *ppAdapter = m_adapters[Adapter];
        (*ppAdapter)->AddRef();
        return S_OK;
    }

    HRESULT EnumAdapters1(uint32_t Adapter, IDXGIAdapter1** ppAdapter) override {
        if (!ppAdapter) return E_POINTER;
        if (Adapter >= m_adapters.size()) return DXGI_ERROR_NOT_FOUND;
        *ppAdapter = m_adapters[Adapter];
        (*ppAdapter)->AddRef();
        return S_OK;
    }

    HRESULT MakeWindowAssociation(void*, uint32_t) override { return S_OK; }
    HRESULT GetWindowAssociation(void** pWindowHandle) override {
        if (pWindowHandle) *pWindowHandle = nullptr;
        return S_OK;
    }

    HRESULT CreateSwapChain(IUnknown*, DXGI_SWAP_CHAIN_DESC* pDesc, IDXGISwapChain** ppSwapChain) override {
        if (!pDesc || !ppSwapChain) return E_POINTER;
        *ppSwapChain = new PrismXSwapChainImpl(*pDesc);
        return S_OK;
    }

    HRESULT CreateSoftwareAdapter(void*, IDXGIAdapter** ppAdapter) override {
        if (!ppAdapter) return E_POINTER;
        *ppAdapter = new PrismXAdapterImpl(L"PrismX Dynamic Software Adapter", 0x1414, 0x0090, 256ULL * 1024 * 1024, true);
        return S_OK;
    }

    HRESULT IsCurrent() override { return S_OK; }
};

// ============================================================================
// 5. Global Export Functions
// ============================================================================

inline HRESULT CreateDXGIFactory(const IID& riid, void** ppFactory) {
    if (!ppFactory) return E_POINTER;
    auto* factory = new PrismXFactoryImpl();
    HRESULT hr = factory->QueryInterface(riid, ppFactory);
    factory->Release();
    return hr;
}

inline HRESULT CreateDXGIFactory1(const IID& riid, void** ppFactory) {
    return CreateDXGIFactory(riid, ppFactory);
}

} // namespace prismx
