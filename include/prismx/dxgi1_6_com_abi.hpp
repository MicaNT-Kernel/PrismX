#pragma once
// ============================================================================
// PrismX Suite 31: Official Microsoft DXGI 1.0 - 1.6 COM Hierarchy & Exact
// Binary IID GUIDs (IDXGIFactory -> IDXGIFactory7, IDXGIAdapter -> IDXGIAdapter4,
// IDXGISwapChain -> IDXGISwapChain4, IDXGIDevice -> IDXGIDevice4)
// ============================================================================

#include <cstdint>
#include <cstring>
#include <atomic>
#include <vector>

#include "types.hpp"
#include "dxgi.hpp"

namespace prismx {
namespace Dxgi16 {

// ============================================================================
// 1. Official Microsoft DXGI 1.0 - 1.6 Interface IIDs (Exact 16-Byte Binary GUIDs)
// ============================================================================

inline constexpr IID OFFICIAL_IID_IDXGIObject =
    { 0xaec22fb8, 0x76f3, 0x4639, { 0x9b, 0xe0, 0x28, 0xeb, 0x43, 0xa6, 0x7a, 0x2e } };
inline constexpr IID OFFICIAL_IID_IDXGIDeviceSubObject =
    { 0x3d3e0379, 0xd9de, 0x4d58, { 0xbb, 0x6c, 0x18, 0xd4, 0x19, 0x92, 0x9f, 0x6a } };
inline constexpr IID OFFICIAL_IID_IDXGIResource =
    { 0x035f3ab4, 0x482e, 0x4e50, { 0xb4, 0x1f, 0x8a, 0x7f, 0x8b, 0xd8, 0x96, 0x0b } };
inline constexpr IID OFFICIAL_IID_IDXGIResource1 =
    { 0x30961379, 0x4609, 0x4a41, { 0x99, 0x8e, 0x54, 0xfe, 0x56, 0x7e, 0xe0, 0xc1 } };
inline constexpr IID OFFICIAL_IID_IDXGISurface =
    { 0xcafcb56c, 0x6ac3, 0x4889, { 0xbf, 0x47, 0x9e, 0x23, 0xbb, 0xd2, 0x60, 0xec } };
inline constexpr IID OFFICIAL_IID_IDXGISurface1 =
    { 0x4ae63092, 0x6327, 0x4c1b, { 0x80, 0xae, 0xbf, 0xe1, 0x2e, 0xa3, 0x2b, 0x86 } };
inline constexpr IID OFFICIAL_IID_IDXGISurface2 =
    { 0xaba496dd, 0xb617, 0x4cb8, { 0xa8, 0x66, 0xbc, 0x44, 0xd7, 0xeb, 0x1f, 0xa2 } };

// Adapters (IDXGIAdapter -> IDXGIAdapter4)
inline constexpr IID OFFICIAL_IID_IDXGIAdapter =
    { 0x2411e7e1, 0x12ac, 0x4ccf, { 0xbd, 0x14, 0x97, 0x98, 0xe8, 0x53, 0x4d, 0x00 } };
inline constexpr IID OFFICIAL_IID_IDXGIAdapter1 =
    { 0x29038f61, 0x3839, 0x4626, { 0x91, 0xfd, 0x08, 0x68, 0x79, 0x01, 0x1a, 0x05 } };
inline constexpr IID OFFICIAL_IID_IDXGIAdapter2 =
    { 0x0aa1ae0a, 0xfa0e, 0x4b84, { 0x86, 0x44, 0xe0, 0x5f, 0xf8, 0xe5, 0xac, 0xb5 } };
inline constexpr IID OFFICIAL_IID_IDXGIAdapter3 =
    { 0x645967a4, 0x1392, 0x4310, { 0xa7, 0x98, 0x80, 0x53, 0xce, 0x3e, 0x93, 0xfd } };
inline constexpr IID OFFICIAL_IID_IDXGIAdapter4 =
    { 0x3c8d99d1, 0x4fbf, 0x4181, { 0xa8, 0x2c, 0xaf, 0x66, 0xbf, 0x7b, 0xd2, 0x4e } };

// Factories (IDXGIFactory -> IDXGIFactory7)
inline constexpr IID OFFICIAL_IID_IDXGIFactory =
    { 0x7b7166ec, 0x21c7, 0x44ae, { 0xb2, 0x1a, 0xc9, 0xae, 0x32, 0x1a, 0xe3, 0x69 } };
inline constexpr IID OFFICIAL_IID_IDXGIFactory1 =
    { 0x770aae78, 0xf26f, 0x4dba, { 0xa8, 0x29, 0x25, 0x3c, 0x83, 0xd1, 0xb3, 0x87 } };
inline constexpr IID OFFICIAL_IID_IDXGIFactory2 =
    { 0x50c83a1c, 0xe072, 0x4c48, { 0x87, 0xb0, 0x36, 0x30, 0xfa, 0x36, 0xa6, 0xd0 } };
inline constexpr IID OFFICIAL_IID_IDXGIFactory3 =
    { 0x25483823, 0xcd46, 0x4c7d, { 0x86, 0xca, 0x47, 0xaa, 0x95, 0xb8, 0x37, 0xbd } };
inline constexpr IID OFFICIAL_IID_IDXGIFactory4 =
    { 0x1bc6ea02, 0xef36, 0x464f, { 0xbf, 0x0c, 0x21, 0xca, 0x39, 0xe5, 0x16, 0x8a } };
inline constexpr IID OFFICIAL_IID_IDXGIFactory5 =
    { 0x7632e1f5, 0xee65, 0x4dca, { 0x87, 0xfd, 0x84, 0xcd, 0x75, 0xf8, 0x83, 0x8d } };
inline constexpr IID OFFICIAL_IID_IDXGIFactory6 =
    { 0xc1b6694f, 0xff09, 0x44a9, { 0xb0, 0x3c, 0x77, 0x90, 0x0a, 0x0a, 0x1d, 0x17 } };
inline constexpr IID OFFICIAL_IID_IDXGIFactory7 =
    { 0xa4966eed, 0x76db, 0x44da, { 0x84, 0xc1, 0xee, 0x9a, 0x7a, 0xfb, 0x20, 0xa8 } };

// SwapChains (IDXGISwapChain -> IDXGISwapChain4)
inline constexpr IID OFFICIAL_IID_IDXGISwapChain =
    { 0x310d36a0, 0xd0e7, 0x4c40, { 0x90, 0x97, 0x62, 0xe0, 0x39, 0x04, 0xbe, 0x4e } };
inline constexpr IID OFFICIAL_IID_IDXGISwapChain1 =
    { 0x790a45f7, 0x0d42, 0x4876, { 0x98, 0x3a, 0x0a, 0x55, 0xcf, 0xe6, 0xf4, 0xaa } };
inline constexpr IID OFFICIAL_IID_IDXGISwapChain2 =
    { 0xa8be2ac4, 0x199f, 0x4946, { 0xb3, 0x31, 0x79, 0x59, 0x9f, 0xb9, 0x8d, 0xe7 } };
inline constexpr IID OFFICIAL_IID_IDXGISwapChain3 =
    { 0x94d99bdb, 0xf1f8, 0x4ab0, { 0xb2, 0x36, 0x7d, 0xa0, 0x17, 0x0e, 0xda, 0xb1 } };
inline constexpr IID OFFICIAL_IID_IDXGISwapChain4 =
    { 0x3d585d5a, 0xbd4a, 0x489e, { 0xb1, 0xf4, 0x3d, 0xbc, 0xb6, 0x45, 0x2f, 0xfb } };

// Devices (IDXGIDevice -> IDXGIDevice4)
inline constexpr IID OFFICIAL_IID_IDXGIDevice =
    { 0x54ec77fa, 0x1377, 0x44e6, { 0x8c, 0x32, 0x88, 0xfd, 0x5f, 0x44, 0xc8, 0x4c } };
inline constexpr IID OFFICIAL_IID_IDXGIDevice1 =
    { 0x77db970f, 0x6276, 0x48ba, { 0xba, 0x28, 0x07, 0x01, 0x43, 0xb4, 0x39, 0x2c } };
inline constexpr IID OFFICIAL_IID_IDXGIDevice2 =
    { 0x05008617, 0xfbfd, 0x4051, { 0xa7, 0x90, 0x14, 0x48, 0x84, 0xb4, 0xf6, 0xa9 } };
inline constexpr IID OFFICIAL_IID_IDXGIDevice3 =
    { 0x6007896c, 0x3244, 0x4afd, { 0xbf, 0x18, 0xa6, 0xd3, 0xbe, 0xda, 0x50, 0x23 } };
inline constexpr IID OFFICIAL_IID_IDXGIDevice4 =
    { 0x95b4f95f, 0xd8da, 0x4ca4, { 0x9e, 0xe6, 0x3b, 0x76, 0xd5, 0x96, 0x8a, 0x10 } };

// ============================================================================
// 2. DXGI 1.2 - 1.6 Structures & Enums
// ============================================================================

enum DXGI_GPU_PREFERENCE : uint32_t {
    DXGI_GPU_PREFERENCE_UNSPECIFIED      = 0,
    DXGI_GPU_PREFERENCE_MINIMUM_POWER    = 1,
    DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE = 2
};

enum DXGI_FEATURE : uint32_t {
    DXGI_FEATURE_PRESENT_ALLOW_TEARING = 0
};

enum DXGI_MEMORY_SEGMENT_GROUP : uint32_t {
    DXGI_MEMORY_SEGMENT_GROUP_LOCAL     = 0,
    DXGI_MEMORY_SEGMENT_GROUP_NON_LOCAL = 1
};

struct DXGI_QUERY_VIDEO_MEMORY_INFO {
    uint64_t Budget;
    uint64_t CurrentUsage;
    uint64_t AvailableForReservation;
    uint64_t CurrentReservation;
};

struct DXGI_SWAP_CHAIN_DESC1 {
    uint32_t         Width;
    uint32_t         Height;
    DXGI_FORMAT      Format;
    int32_t          Stereo;
    DXGI_SAMPLE_DESC SampleDesc;
    uint32_t         BufferUsage;
    uint32_t         BufferCount;
    uint32_t         Scaling;
    DXGI_SWAP_EFFECT SwapEffect;
    DXGI_ALPHA_MODE  AlphaMode;
    uint32_t         Flags;
};

struct DXGI_ADAPTER_DESC3 {
    wchar_t  Description[128];
    uint32_t VendorId;
    uint32_t DeviceId;
    uint32_t SubSysId;
    uint32_t Revision;
    size_t   DedicatedVideoMemory;
    size_t   DedicatedSystemMemory;
    size_t   SharedSystemMemory;
    LUID     AdapterLuid;
    uint32_t Flags;
    uint32_t GraphicsPreemptionGranularity;
    uint32_t ComputePreemptionGranularity;
};

// ============================================================================
// 3. DXGI 1.2 - 1.6 COM Interfaces (IDXGIAdapter4, IDXGISwapChain4, IDXGIDevice4, IDXGIFactory7)
// ============================================================================

class IDXGIAdapter4 : public IDXGIAdapter1 {
public:
    virtual HRESULT GetDesc3(DXGI_ADAPTER_DESC3* pDesc) = 0;
    virtual HRESULT QueryVideoMemoryInfo(uint32_t NodeIndex, DXGI_MEMORY_SEGMENT_GROUP MemorySegmentGroup, DXGI_QUERY_VIDEO_MEMORY_INFO* pVideoMemoryInfo) = 0;
    virtual HRESULT SetVideoMemoryReservation(uint32_t NodeIndex, DXGI_MEMORY_SEGMENT_GROUP MemorySegmentGroup, uint64_t Reservation) = 0;
};

class IDXGISwapChain4 : public IDXGISwapChain {
public:
    virtual HRESULT GetDesc1(DXGI_SWAP_CHAIN_DESC1* pDesc) = 0;
    virtual uint32_t GetCurrentBackBufferIndex() = 0;
    virtual HRESULT CheckColorSpaceSupport(uint32_t ColorSpace, uint32_t* pColorSpaceSupport) = 0;
    virtual HRESULT SetColorSpace1(uint32_t ColorSpace) = 0;
    virtual HRESULT SetHDRMetaData(uint32_t Type, uint32_t Size, void* pMetaData) = 0;
};

class IDXGIDevice4 : public IDXGIDevice {
public:
    virtual HRESULT SetMaximumFrameLatency(uint32_t MaxLatency) = 0;
    virtual HRESULT GetMaximumFrameLatency(uint32_t* pMaxLatency) = 0;
    virtual void    Trim() = 0;
};

class IDXGIFactory7 : public IDXGIFactory1 {
public:
    virtual HRESULT CreateSwapChainForHwnd(IUnknown* pDevice, void* hWnd, const DXGI_SWAP_CHAIN_DESC1* pDesc, const void* pFullscreenDesc, IDXGIOutput* pRestrictToOutput, IDXGISwapChain4** ppSwapChain) = 0;
    virtual HRESULT EnumAdapterByLuid(LUID AdapterLuid, const IID& riid, void** ppvAdapter) = 0;
    virtual HRESULT EnumWarpAdapter(const IID& riid, void** ppvAdapter) = 0;
    virtual HRESULT CheckFeatureSupport(DXGI_FEATURE Feature, void* pFeatureSupportData, uint32_t FeatureSupportDataSize) = 0;
    virtual HRESULT EnumAdapterByGpuPreference(uint32_t Adapter, DXGI_GPU_PREFERENCE GpuPreference, const IID& riid, void** ppvAdapter) = 0;
};

// ============================================================================
// 4. Concrete Sovereign DXGI 1.6 Implementations with Full GetParent / QI Graph
// ============================================================================

class PrismDXGIAdapter4Impl : public IDXGIAdapter4 {
private:
    std::atomic<uint32_t> m_refCount{ 1 };
    IUnknown*             m_pParentFactory{ nullptr };
    uint32_t              m_adapterIndex{ 0 };
    uint64_t              m_reservation{ 0 };

public:
    PrismDXGIAdapter4Impl(IUnknown* pFactory, uint32_t idx)
        : m_pParentFactory(pFactory), m_adapterIndex(idx) {}

    HRESULT QueryInterface(const IID& riid, void** ppv) override {
        if (!ppv) return E_POINTER;
        if (riid == IID_IUnknown ||
            riid == IID_IDXGIObject || riid == OFFICIAL_IID_IDXGIObject ||
            riid == IID_IDXGIAdapter || riid == OFFICIAL_IID_IDXGIAdapter ||
            riid == IID_IDXGIAdapter1 || riid == OFFICIAL_IID_IDXGIAdapter1 ||
            riid == OFFICIAL_IID_IDXGIAdapter2 ||
            riid == OFFICIAL_IID_IDXGIAdapter3 ||
            riid == OFFICIAL_IID_IDXGIAdapter4) {
            *ppv = static_cast<IDXGIAdapter4*>(this);
            AddRef();
            return S_OK;
        }
        *ppv = nullptr;
        return E_NOINTERFACE;
    }

    uint32_t AddRef() override { return ++m_refCount; }
    uint32_t Release() override {
        uint32_t c = --m_refCount;
        if (c == 0) delete this;
        return c;
    }

    HRESULT SetPrivateData(const IID&, uint32_t, const void*) override { return S_OK; }
    HRESULT SetPrivateDataInterface(const IID&, const IUnknown*) override { return S_OK; }
    HRESULT GetPrivateData(const IID&, uint32_t*, void*) override { return S_OK; }

    HRESULT GetParent(const IID& riid, void** ppParent) override {
        if (!ppParent || !m_pParentFactory) return E_INVALIDARG;
        return m_pParentFactory->QueryInterface(riid, ppParent);
    }

    HRESULT EnumOutputs(uint32_t Output, IDXGIOutput** ppOutput) override {
        if (Output > 0) return DXGI_ERROR_NOT_FOUND;
        if (!ppOutput) return E_INVALIDARG;
        *ppOutput = new PrismXOutputImpl(L"\\\\.\\DISPLAY1", 3840, 2160);
        return S_OK;
    }

    HRESULT GetDesc(DXGI_ADAPTER_DESC* pDesc) override {
        if (!pDesc) return E_INVALIDARG;
        std::memset(pDesc, 0, sizeof(DXGI_ADAPTER_DESC));
        const wchar_t* name = (m_adapterIndex == 0) ? L"PrismX Sovereign Direct3D 12 Ultimate GPU" : L"PrismX WARP Software Rasterizer";
        std::memcpy(pDesc->Description, name, (wcslen(name) + 1) * sizeof(wchar_t));
        pDesc->VendorId = 0x13B5u;
        pDesc->DeviceId = (m_adapterIndex == 0) ? 0x2026u : 0x008Cu;
        pDesc->DedicatedVideoMemory = (m_adapterIndex == 0) ? (16ULL * 1024 * 1024 * 1024) : 0;
        pDesc->SharedSystemMemory   = 32ULL * 1024 * 1024 * 1024;
        pDesc->AdapterLuid          = { 0x1000u + m_adapterIndex, 0 };
        return S_OK;
    }

    HRESULT CheckInterfaceSupport(const IID&, int64_t* pUMDVersion) override {
        if (pUMDVersion) *pUMDVersion = 0x0020000000010000LL; // WDDM 3.2 UMD Version
        return S_OK;
    }

    HRESULT GetDesc1(DXGI_ADAPTER_DESC1* pDesc) override {
        if (!pDesc) return E_INVALIDARG;
        DXGI_ADAPTER_DESC base{};
        GetDesc(&base);
        std::memcpy(pDesc, &base, sizeof(base));
        pDesc->Flags = (m_adapterIndex == 0) ? 0u : 2u /*DXGI_ADAPTER_FLAG_SOFTWARE*/;
        return S_OK;
    }

    HRESULT GetDesc3(DXGI_ADAPTER_DESC3* pDesc) override {
        if (!pDesc) return E_INVALIDARG;
        DXGI_ADAPTER_DESC1 d1{};
        GetDesc1(&d1);
        std::memset(pDesc, 0, sizeof(DXGI_ADAPTER_DESC3));
        std::memcpy(pDesc, &d1, sizeof(d1));
        pDesc->GraphicsPreemptionGranularity = 3u; // Triangle/Pixel boundary
        pDesc->ComputePreemptionGranularity  = 3u; // Thread boundary
        return S_OK;
    }

    HRESULT QueryVideoMemoryInfo(uint32_t, DXGI_MEMORY_SEGMENT_GROUP seg, DXGI_QUERY_VIDEO_MEMORY_INFO* pInfo) override {
        if (!pInfo) return E_INVALIDARG;
        pInfo->Budget                  = (seg == DXGI_MEMORY_SEGMENT_GROUP_LOCAL) ? (16ULL * 1024 * 1024 * 1024) : (32ULL * 1024 * 1024 * 1024);
        pInfo->CurrentUsage            = 512ULL * 1024 * 1024;
        pInfo->AvailableForReservation = pInfo->Budget / 2;
        pInfo->CurrentReservation      = m_reservation;
        return S_OK;
    }

    HRESULT SetVideoMemoryReservation(uint32_t, DXGI_MEMORY_SEGMENT_GROUP, uint64_t Reservation) override {
        m_reservation = Reservation;
        return S_OK;
    }
};

class PrismDXGISwapChain4Impl : public IDXGISwapChain4 {
private:
    std::atomic<uint32_t> m_refCount{ 1 };
    IUnknown*             m_pParentFactory{ nullptr };
    DXGI_SWAP_CHAIN_DESC1 m_desc1{};
    uint32_t              m_currentBackBuffer{ 0 };
    uint32_t              m_presentCount{ 0 };
    uint32_t              m_colorSpace{ 0 };
    std::vector<PrismXSurfaceImpl*> m_buffers;

public:
    PrismDXGISwapChain4Impl(IUnknown* pFactory, const DXGI_SWAP_CHAIN_DESC1& d)
        : m_pParentFactory(pFactory), m_desc1(d) {
        if (m_desc1.BufferCount == 0) m_desc1.BufferCount = 2;
        if (m_desc1.Width == 0) m_desc1.Width = 1920;
        if (m_desc1.Height == 0) m_desc1.Height = 1080;
        for (uint32_t i = 0; i < m_desc1.BufferCount; ++i) {
            m_buffers.push_back(new PrismXSurfaceImpl(m_desc1.Width, m_desc1.Height, m_desc1.Format));
        }
    }

    ~PrismDXGISwapChain4Impl() override {
        for (auto* b : m_buffers) b->Release();
    }

    HRESULT QueryInterface(const IID& riid, void** ppv) override {
        if (!ppv) return E_POINTER;
        if (riid == IID_IUnknown ||
            riid == IID_IDXGIObject || riid == OFFICIAL_IID_IDXGIObject ||
            riid == IID_IDXGIDeviceSubObject || riid == OFFICIAL_IID_IDXGIDeviceSubObject ||
            riid == IID_IDXGISwapChain || riid == OFFICIAL_IID_IDXGISwapChain ||
            riid == OFFICIAL_IID_IDXGISwapChain1 ||
            riid == OFFICIAL_IID_IDXGISwapChain2 ||
            riid == OFFICIAL_IID_IDXGISwapChain3 ||
            riid == OFFICIAL_IID_IDXGISwapChain4) {
            *ppv = static_cast<IDXGISwapChain4*>(this);
            AddRef();
            return S_OK;
        }
        *ppv = nullptr;
        return E_NOINTERFACE;
    }

    uint32_t AddRef() override { return ++m_refCount; }
    uint32_t Release() override {
        uint32_t c = --m_refCount;
        if (c == 0) delete this;
        return c;
    }

    HRESULT SetPrivateData(const IID&, uint32_t, const void*) override { return S_OK; }
    HRESULT SetPrivateDataInterface(const IID&, const IUnknown*) override { return S_OK; }
    HRESULT GetPrivateData(const IID&, uint32_t*, void*) override { return S_OK; }
    HRESULT GetParent(const IID& riid, void** ppParent) override {
        if (!ppParent || !m_pParentFactory) return E_INVALIDARG;
        return m_pParentFactory->QueryInterface(riid, ppParent);
    }

    HRESULT Present(uint32_t, uint32_t) override {
        m_presentCount++;
        m_currentBackBuffer = (m_currentBackBuffer + 1) % m_desc1.BufferCount;
        return S_OK;
    }

    HRESULT GetBuffer(uint32_t Buffer, const IID& riid, void** ppSurface) override {
        if (!ppSurface || Buffer >= m_buffers.size()) return E_INVALIDARG;
        return m_buffers[Buffer]->QueryInterface(riid, ppSurface);
    }

    HRESULT SetFullscreenState(int32_t, IDXGIOutput*) override { return S_OK; }
    HRESULT GetFullscreenState(int32_t* pFs, IDXGIOutput** ppTarget) override {
        if (pFs) *pFs = 0;
        if (ppTarget) *ppTarget = nullptr;
        return S_OK;
    }

    HRESULT GetDesc(DXGI_SWAP_CHAIN_DESC* pDesc) override {
        if (!pDesc) return E_INVALIDARG;
        std::memset(pDesc, 0, sizeof(DXGI_SWAP_CHAIN_DESC));
        pDesc->BufferDesc.Width  = m_desc1.Width;
        pDesc->BufferDesc.Height = m_desc1.Height;
        pDesc->BufferDesc.Format = m_desc1.Format;
        pDesc->BufferCount       = m_desc1.BufferCount;
        pDesc->SampleDesc        = m_desc1.SampleDesc;
        pDesc->BufferUsage       = m_desc1.BufferUsage;
        pDesc->SwapEffect        = m_desc1.SwapEffect;
        pDesc->Flags             = m_desc1.Flags;
        pDesc->Windowed          = 1;
        return S_OK;
    }

    HRESULT ResizeBuffers(uint32_t BufferCount, uint32_t Width, uint32_t Height, DXGI_FORMAT NewFormat, uint32_t Flags) override {
        if (BufferCount > 0) m_desc1.BufferCount = BufferCount;
        if (Width > 0) m_desc1.Width = Width;
        if (Height > 0) m_desc1.Height = Height;
        if (NewFormat != DXGI_FORMAT_UNKNOWN) m_desc1.Format = NewFormat;
        m_desc1.Flags = Flags;
        m_currentBackBuffer = 0;
        return S_OK;
    }

    HRESULT ResizeTarget(const DXGI_MODE_DESC*) override { return S_OK; }
    HRESULT GetContainingOutput(IDXGIOutput** ppOut) override {
        if (!ppOut) return E_INVALIDARG;
        *ppOut = new PrismXOutputImpl(L"\\\\.\\DISPLAY1", 3840, 2160);
        return S_OK;
    }
    HRESULT GetFrameStatistics(DXGI_FRAME_STATISTICS* pStats) override {
        if (!pStats) return E_INVALIDARG;
        pStats->PresentCount        = m_presentCount;
        pStats->PresentRefreshCount = m_presentCount;
        pStats->SyncRefreshCount    = m_presentCount;
        pStats->SyncQPCTime         = static_cast<int64_t>(m_presentCount) * 1851LL;
        pStats->SyncGPUTime         = pStats->SyncQPCTime;
        return S_OK;
    }
    HRESULT GetLastPresentCount(uint32_t* pCnt) override {
        if (!pCnt) return E_INVALIDARG;
        *pCnt = m_presentCount;
        return S_OK;
    }

    // IDXGISwapChain1 / 3 / 4 methods
    HRESULT GetDesc1(DXGI_SWAP_CHAIN_DESC1* pDesc) override {
        if (!pDesc) return E_INVALIDARG;
        *pDesc = m_desc1;
        return S_OK;
    }
    uint32_t GetCurrentBackBufferIndex() override {
        return m_currentBackBuffer;
    }
    HRESULT CheckColorSpaceSupport(uint32_t, uint32_t* pSupport) override {
        if (!pSupport) return E_INVALIDARG;
        *pSupport = 0x3u; // DXGI_SWAP_CHAIN_COLOR_SPACE_SUPPORT_FLAG_PRESENT | OVERLAY_PRESENT
        return S_OK;
    }
    HRESULT SetColorSpace1(uint32_t cs) override {
        m_colorSpace = cs;
        return S_OK;
    }
    HRESULT SetHDRMetaData(uint32_t, uint32_t, void*) override {
        return S_OK;
    }
};

class PrismDXGIFactory7Impl : public IDXGIFactory7 {
private:
    std::atomic<uint32_t> m_refCount{ 1 };
    void*                 m_associatedWindow{ nullptr };
    uint32_t              m_creationFlags{ 0 };

public:
    explicit PrismDXGIFactory7Impl(uint32_t flags = 0) : m_creationFlags(flags) {
        (void)m_creationFlags;
    }

    HRESULT QueryInterface(const IID& riid, void** ppv) override {
        if (!ppv) return E_POINTER;
        if (riid == IID_IUnknown ||
            riid == IID_IDXGIObject || riid == OFFICIAL_IID_IDXGIObject ||
            riid == IID_IDXGIFactory || riid == OFFICIAL_IID_IDXGIFactory ||
            riid == IID_IDXGIFactory1 || riid == OFFICIAL_IID_IDXGIFactory1 ||
            riid == OFFICIAL_IID_IDXGIFactory2 ||
            riid == OFFICIAL_IID_IDXGIFactory3 ||
            riid == OFFICIAL_IID_IDXGIFactory4 ||
            riid == OFFICIAL_IID_IDXGIFactory5 ||
            riid == OFFICIAL_IID_IDXGIFactory6 ||
            riid == OFFICIAL_IID_IDXGIFactory7) {
            *ppv = static_cast<IDXGIFactory7*>(this);
            AddRef();
            return S_OK;
        }
        *ppv = nullptr;
        return E_NOINTERFACE;
    }

    uint32_t AddRef() override { return ++m_refCount; }
    uint32_t Release() override {
        uint32_t c = --m_refCount;
        if (c == 0) delete this;
        return c;
    }

    HRESULT SetPrivateData(const IID&, uint32_t, const void*) override { return S_OK; }
    HRESULT SetPrivateDataInterface(const IID&, const IUnknown*) override { return S_OK; }
    HRESULT GetPrivateData(const IID&, uint32_t*, void*) override { return S_OK; }
    HRESULT GetParent(const IID&, void** ppParent) override {
        if (ppParent) *ppParent = nullptr;
        return E_NOINTERFACE;
    }

    HRESULT EnumAdapters(uint32_t Adapter, IDXGIAdapter** ppAdapter) override {
        if (Adapter >= 2) return DXGI_ERROR_NOT_FOUND;
        if (!ppAdapter) return E_INVALIDARG;
        *ppAdapter = new PrismDXGIAdapter4Impl(this, Adapter);
        return S_OK;
    }

    HRESULT MakeWindowAssociation(void* WindowHandle, uint32_t) override {
        m_associatedWindow = WindowHandle;
        return S_OK;
    }

    HRESULT GetWindowAssociation(void** pWindowHandle) override {
        if (!pWindowHandle) return E_INVALIDARG;
        *pWindowHandle = m_associatedWindow;
        return S_OK;
    }

    HRESULT CreateSwapChain(IUnknown*, DXGI_SWAP_CHAIN_DESC* pDesc, IDXGISwapChain** ppSwapChain) override {
        if (!pDesc || !ppSwapChain) return E_INVALIDARG;
        DXGI_SWAP_CHAIN_DESC1 d1{};
        d1.Width       = pDesc->BufferDesc.Width;
        d1.Height      = pDesc->BufferDesc.Height;
        d1.Format      = pDesc->BufferDesc.Format;
        d1.SampleDesc  = pDesc->SampleDesc;
        d1.BufferUsage = pDesc->BufferUsage;
        d1.BufferCount = pDesc->BufferCount;
        d1.SwapEffect  = pDesc->SwapEffect;
        d1.Flags       = pDesc->Flags;
        *ppSwapChain   = new PrismDXGISwapChain4Impl(this, d1);
        return S_OK;
    }

    HRESULT CreateSoftwareAdapter(void*, IDXGIAdapter** ppAdapter) override {
        if (!ppAdapter) return E_INVALIDARG;
        *ppAdapter = new PrismDXGIAdapter4Impl(this, 1);
        return S_OK;
    }

    HRESULT EnumAdapters1(uint32_t Adapter, IDXGIAdapter1** ppAdapter) override {
        if (Adapter >= 2) return DXGI_ERROR_NOT_FOUND;
        if (!ppAdapter) return E_INVALIDARG;
        *ppAdapter = new PrismDXGIAdapter4Impl(this, Adapter);
        return S_OK;
    }

    int32_t IsCurrent() override { return 1; }

    // IDXGIFactory2 / 4 / 5 / 6 / 7 methods
    HRESULT CreateSwapChainForHwnd(IUnknown*, void*, const DXGI_SWAP_CHAIN_DESC1* pDesc, const void*, IDXGIOutput*, IDXGISwapChain4** ppSwapChain) override {
        if (!pDesc || !ppSwapChain) return E_INVALIDARG;
        *ppSwapChain = new PrismDXGISwapChain4Impl(this, *pDesc);
        return S_OK;
    }

    HRESULT EnumAdapterByLuid(LUID, const IID& riid, void** ppvAdapter) override {
        if (!ppvAdapter) return E_INVALIDARG;
        auto* pAd = new PrismDXGIAdapter4Impl(this, 0);
        HRESULT hr = pAd->QueryInterface(riid, ppvAdapter);
        pAd->Release();
        return hr;
    }

    HRESULT EnumWarpAdapter(const IID& riid, void** ppvAdapter) override {
        if (!ppvAdapter) return E_INVALIDARG;
        auto* pAd = new PrismDXGIAdapter4Impl(this, 1);
        HRESULT hr = pAd->QueryInterface(riid, ppvAdapter);
        pAd->Release();
        return hr;
    }

    HRESULT CheckFeatureSupport(DXGI_FEATURE Feature, void* pData, uint32_t DataSize) override {
        if (Feature == DXGI_FEATURE_PRESENT_ALLOW_TEARING && pData && DataSize >= sizeof(int32_t)) {
            *static_cast<int32_t*>(pData) = 1; // TRUE (540Hz VRR / FreeSync / G-Sync tearing supported)
            return S_OK;
        }
        return E_INVALIDARG;
    }

    HRESULT EnumAdapterByGpuPreference(uint32_t Adapter, DXGI_GPU_PREFERENCE pref, const IID& riid, void** ppvAdapter) override {
        if (Adapter >= 2) return DXGI_ERROR_NOT_FOUND;
        if (!ppvAdapter) return E_INVALIDARG;
        uint32_t mappedIdx = (pref == DXGI_GPU_PREFERENCE_MINIMUM_POWER) ? (1u - Adapter) : Adapter;
        auto* pAd = new PrismDXGIAdapter4Impl(this, mappedIdx);
        HRESULT hr = pAd->QueryInterface(riid, ppvAdapter);
        pAd->Release();
        return hr;
    }
};

class PrismDXGIDevice4Impl : public IDXGIDevice4 {
private:
    std::atomic<uint32_t> m_refCount{ 1 };
    IUnknown*             m_pParentFactory{ nullptr };
    uint32_t              m_maxLatency{ 1 };
    int32_t               m_gpuPriority{ 0 };

public:
    explicit PrismDXGIDevice4Impl(IUnknown* pFactory = nullptr)
        : m_pParentFactory(pFactory ? pFactory : new PrismDXGIFactory7Impl(0)) {}

    HRESULT QueryInterface(const IID& riid, void** ppv) override {
        if (!ppv) return E_POINTER;
        if (riid == IID_IUnknown ||
            riid == IID_IDXGIObject || riid == OFFICIAL_IID_IDXGIObject ||
            riid == IID_IDXGIDevice || riid == OFFICIAL_IID_IDXGIDevice ||
            riid == OFFICIAL_IID_IDXGIDevice1 ||
            riid == OFFICIAL_IID_IDXGIDevice2 ||
            riid == OFFICIAL_IID_IDXGIDevice3 ||
            riid == OFFICIAL_IID_IDXGIDevice4) {
            *ppv = static_cast<IDXGIDevice4*>(this);
            AddRef();
            return S_OK;
        }
        *ppv = nullptr;
        return E_NOINTERFACE;
    }

    uint32_t AddRef() override { return ++m_refCount; }
    uint32_t Release() override {
        uint32_t c = --m_refCount;
        if (c == 0) delete this;
        return c;
    }

    HRESULT SetPrivateData(const IID&, uint32_t, const void*) override { return S_OK; }
    HRESULT SetPrivateDataInterface(const IID&, const IUnknown*) override { return S_OK; }
    HRESULT GetPrivateData(const IID&, uint32_t*, void*) override { return S_OK; }
    HRESULT GetParent(const IID& riid, void** ppParent) override {
        if (!ppParent) return E_INVALIDARG;
        auto* pAdapter = new PrismDXGIAdapter4Impl(m_pParentFactory, 0);
        HRESULT hr = pAdapter->QueryInterface(riid, ppParent);
        pAdapter->Release();
        return hr;
    }

    HRESULT GetAdapter(IDXGIAdapter** pAdapter) override {
        if (!pAdapter) return E_INVALIDARG;
        *pAdapter = new PrismDXGIAdapter4Impl(m_pParentFactory, 0);
        return S_OK;
    }

    HRESULT CreateSurface(const void*, uint32_t, uint32_t, const void*, IDXGISurface** ppSurface) override {
        if (!ppSurface) return E_INVALIDARG;
        *ppSurface = new PrismXSurfaceImpl(1920, 1080, DXGI_FORMAT_B8G8R8A8_UNORM);
        return S_OK;
    }

    HRESULT QueryResourceResidency(IUnknown* const*, uint32_t* pStatus, uint32_t NumResources) override {
        if (pStatus) {
            for (uint32_t i = 0; i < NumResources; ++i) pStatus[i] = 1u; // DXGI_RESIDENCY_FULLY_RESIDENT
        }
        return S_OK;
    }

    HRESULT SetGPUThreadPriority(int32_t p) override { m_gpuPriority = p; return S_OK; }
    HRESULT GetGPUThreadPriority(int32_t* p) override { if (p) *p = m_gpuPriority; return S_OK; }
    HRESULT SetMaximumFrameLatency(uint32_t m) override { m_maxLatency = m; return S_OK; }
    HRESULT GetMaximumFrameLatency(uint32_t* m) override { if (m) *m = m_maxLatency; return S_OK; }
    void    Trim() override {}
};

inline HRESULT CreateDXGIFactory2(uint32_t Flags, const IID& riid, void** ppFactory) noexcept {
    if (!ppFactory) return E_INVALIDARG;
    auto* pFac = new PrismDXGIFactory7Impl(Flags);
    HRESULT hr = pFac->QueryInterface(riid, ppFactory);
    pFac->Release();
    return hr;
}

} // namespace Dxgi16
} // namespace prismx
