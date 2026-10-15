// ============================================================================
// PrismX: Official Microsoft DXCore (<dxcore.h> / <dxcore_interface.h> / dxcore.dll)
// COM Hierarchy, 16-Byte Binary IIDs & Attribute Enumeration (Suite 38)
//
// Clean-Room Implementation in ISO C++23. Zero External Dependencies.
// Provides:
//   - Exact 16-byte Microsoft binary IIDs & Attribute GUIDs from <dxcore_interface.h>:
//       * IID_IDXCoreAdapterFactory  {78ee5945-c36e-4b13-a669-005dd11c0f06}
//       * IID_IDXCoreAdapterFactory1 {d5682e19-6d21-401c-827a-9a51a4ea35d7}
//       * IID_IDXCoreAdapterList     {526c7776-40e9-459b-b711-f32ad76dfc28}
//       * IID_IDXCoreAdapter         {f0db4c7f-fe5a-42a2-bd62-f2a6cf6fc83e}
//       * IID_IDXCoreAdapter1        {a0783366-cfa3-43be-9d79-55b2da97c63c}
//       * DXCORE_ADAPTER_ATTRIBUTE_D3D11_GRAPHICS    {8c47866b-7583-450d-f0f0-6bada895af4b}
//       * DXCORE_ADAPTER_ATTRIBUTE_D3D12_GRAPHICS    {0c9ece4d-2f6e-4f01-8c96-e89e331b47b1}
//       * DXCORE_ADAPTER_ATTRIBUTE_D3D12_CORE_COMPUTE{248e2800-a793-4724-abaa-23a6de1be090}
//       * DXCORE_ADAPTER_ATTRIBUTE_D3D12_GENERIC_ML  {b71b0d41-1088-422f-a27c-0250b7d3a988}
//   - Canonical COM vtable hierarchy for IDXCoreAdapter1, IDXCoreAdapterList,
//     and IDXCoreAdapterFactory1 + DXCoreCreateAdapterFactory C export.
// ============================================================================

#pragma once

#include "types.hpp"
#include <atomic>
#include <cstring>

namespace prismx::DXCoreComAbi {

// ----------------------------------------------------------------------------
// 1. Official 16-Byte Microsoft Binary IIDs & Attribute GUIDs (<dxcore_interface.h>)
// ----------------------------------------------------------------------------
// {78ee5945-c36e-4b13-a669-005dd11c0f06}
inline constexpr IID OFFICIAL_IID_IDXCoreAdapterFactory = {
    0x78ee5945, 0xc36e, 0x4b13, {0xa6, 0x69, 0x00, 0x5d, 0xd1, 0x1c, 0x0f, 0x06}
};
// {d5682e19-6d21-401c-827a-9a51a4ea35d7}
inline constexpr IID OFFICIAL_IID_IDXCoreAdapterFactory1 = {
    0xd5682e19, 0x6d21, 0x401c, {0x82, 0x7a, 0x9a, 0x51, 0xa4, 0xea, 0x35, 0xd7}
};
// {526c7776-40e9-459b-b711-f32ad76dfc28}
inline constexpr IID OFFICIAL_IID_IDXCoreAdapterList = {
    0x526c7776, 0x40e9, 0x459b, {0xb7, 0x11, 0xf3, 0x2a, 0xd7, 0x6d, 0xfc, 0x28}
};
// {f0db4c7f-fe5a-42a2-bd62-f2a6cf6fc83e}
inline constexpr IID OFFICIAL_IID_IDXCoreAdapter = {
    0xf0db4c7f, 0xfe5a, 0x42a2, {0xbd, 0x62, 0xf2, 0xa6, 0xcf, 0x6f, 0xc8, 0x3e}
};
// {a0783366-cfa3-43be-9d79-55b2da97c63c}
inline constexpr IID OFFICIAL_IID_IDXCoreAdapter1 = {
    0xa0783366, 0xcfa3, 0x43be, {0x9d, 0x79, 0x55, 0xb2, 0xda, 0x97, 0xc6, 0x3c}
};

// {8c47866b-7583-450d-f0f0-6bada895af4b}
inline constexpr IID OFFICIAL_DXCORE_ADAPTER_ATTRIBUTE_D3D11_GRAPHICS = {
    0x8c47866b, 0x7583, 0x450d, {0xf0, 0xf0, 0x6b, 0xad, 0xa8, 0x95, 0xaf, 0x4b}
};
// {0c9ece4d-2f6e-4f01-8c96-e89e331b47b1}
inline constexpr IID OFFICIAL_DXCORE_ADAPTER_ATTRIBUTE_D3D12_GRAPHICS = {
    0x0c9ece4d, 0x2f6e, 0x4f01, {0x8c, 0x96, 0xe8, 0x9e, 0x33, 0x1b, 0x47, 0xb1}
};
// {248e2800-a793-4724-abaa-23a6de1be090}
inline constexpr IID OFFICIAL_DXCORE_ADAPTER_ATTRIBUTE_D3D12_CORE_COMPUTE = {
    0x248e2800, 0xa793, 0x4724, {0xab, 0xaa, 0x23, 0xa6, 0xde, 0x1b, 0xe0, 0x90}
};
// {b71b0d41-1088-422f-a27c-0250b7d3a988}
inline constexpr IID OFFICIAL_DXCORE_ADAPTER_ATTRIBUTE_D3D12_GENERIC_ML = {
    0xb71b0d41, 0x1088, 0x422f, {0xa2, 0x7c, 0x02, 0x50, 0xb7, 0xd3, 0xa9, 0x88}
};

// ----------------------------------------------------------------------------
// 2. Canonical DXCore Property Enums & Structures (<dxcore_interface.h>)
// ----------------------------------------------------------------------------
enum class DXCoreAdapterProperty : uint32_t {
    InstanceLuid                  = 0,
    DriverVersion                 = 1,
    DriverDescription             = 2,
    HardwareID                    = 3,
    KmdModelVersion               = 4,
    ComputePreemptionGranularity  = 5,
    GraphicsPreemptionGranularity = 6,
    DedicatedAdapterMemory        = 7,
    DedicatedSystemMemory         = 8,
    SharedSystemMemory            = 9,
    AcgCompatible                 = 10,
    IsHardware                    = 11,
    IsIntegrated                  = 12,
    IsDetachable                  = 13,
    HardwareIDParts               = 14
};

struct DXCoreHardwareID {
    uint32_t vendorID;
    uint32_t deviceID;
    uint32_t subSysID;
    uint32_t revision;
};

struct DXCoreAdapterMemoryBudget {
    uint64_t budget;
    uint64_t currentUsage;
    uint64_t availableForReservation;
    uint64_t currentReservation;
};

// ----------------------------------------------------------------------------
// 3. Canonical DXCore COM VTable Interfaces
// ----------------------------------------------------------------------------
struct IDXCoreAdapter : public IUnknown {
    virtual bool IsValid() = 0;                                                 // Slot 3
    virtual bool IsAttributeSupported(const IID& attributeGUID) = 0;            // Slot 4
    virtual bool IsPropertySupported(DXCoreAdapterProperty property) = 0;       // Slot 5
    virtual HRESULT GetProperty(DXCoreAdapterProperty property,
                                size_t bufferSize,
                                void* propertyData) = 0;                        // Slot 6
    virtual HRESULT GetPropertySize(DXCoreAdapterProperty property,
                                    size_t* bufferSize) = 0;                    // Slot 7
    virtual bool IsQueryStateSupported(uint32_t property) = 0;                  // Slot 8
    virtual HRESULT QueryState(uint32_t state, size_t inputStateDetailsSize,
                               const void* inputStateDetails,
                               size_t outputBufferSize, void* outputBuffer) = 0;// Slot 9
    virtual bool IsSetStateSupported(uint32_t property) = 0;                    // Slot 10
    virtual HRESULT SetState(uint32_t state, size_t inputStateDetailsSize,
                             const void* inputStateDetails,
                             size_t inputDataSize, const void* inputData) = 0;  // Slot 11
    virtual HRESULT GetFactory(const IID& riid, void** ppvFactory) = 0;         // Slot 12
};

struct IDXCoreAdapter1 : public IDXCoreAdapter {
    virtual HRESULT GetPropertyWithInput(DXCoreAdapterProperty property,
                                         size_t inputPropertyDetailsSize,
                                         const void* inputPropertyDetails,
                                         size_t outputBufferSize,
                                         void* outputBuffer) = 0;               // Slot 13
};

struct IDXCoreAdapterList : public IUnknown {
    virtual HRESULT GetAdapter(uint32_t index, const IID& riid, void** ppvAdapter) = 0; // Slot 3
    virtual uint32_t GetAdapterCount() = 0;                                     // Slot 4
    virtual bool IsStale() = 0;                                                 // Slot 5
    virtual HRESULT GetFactory(const IID& riid, void** ppvFactory) = 0;         // Slot 6
    virtual HRESULT Sort(uint32_t numPreferences, const uint32_t* preferences) = 0; // Slot 7
    virtual bool IsAdapterPreferenceSupported(uint32_t preference) = 0;         // Slot 8
};

struct IDXCoreAdapterFactory : public IUnknown {
    virtual HRESULT CreateAdapterList(uint32_t numAttributes,
                                      const IID* filterAttributes,
                                      const IID& riid,
                                      void** ppvAdapterList) = 0;               // Slot 3
    virtual HRESULT GetAdapterByLuid(const LUID& adapterLUID,
                                     const IID& riid,
                                     void** ppvAdapter) = 0;                    // Slot 4
    virtual bool IsNotificationTypeSupported(uint32_t notificationType) = 0;    // Slot 5
    virtual HRESULT RegisterEventNotification(IUnknown* dxCoreObject,
                                              uint32_t notificationType,
                                              void* callbackFunction,
                                              void* callbackContext,
                                              uint32_t* eventCookie) = 0;       // Slot 6
    virtual HRESULT UnregisterEventNotification(uint32_t eventCookie) = 0;      // Slot 7
};

struct IDXCoreAdapterFactory1 : public IDXCoreAdapterFactory {
    virtual HRESULT CreateAdapterListByWorkload(uint32_t workload,
                                                uint32_t runtimeFilter,
                                                uint32_t hardwareTypeFilter,
                                                const IID& riid,
                                                void** ppvAdapterList) = 0;     // Slot 8
};

// ----------------------------------------------------------------------------
// 4. Concrete Implementations
// ----------------------------------------------------------------------------
class PrismDXCoreAdapterFactory1Impl;

class PrismDXCoreAdapter1Impl final : public IDXCoreAdapter1 {
    std::atomic<uint32_t> ref_count_{1};
    IUnknown* parent_factory_ = nullptr;

    static constexpr const char kDesc[] = "Sovereign PrismX RTX-Class WDDM 3.2 / MCDM Compute Adapter";

public:
    explicit PrismDXCoreAdapter1Impl(IUnknown* fac = nullptr) : parent_factory_(fac) {
        if (parent_factory_) parent_factory_->AddRef();
    }
    ~PrismDXCoreAdapter1Impl() {
        if (parent_factory_) parent_factory_->Release();
    }

    int32_t QueryInterface(const IID& riid, void** ppvObject) override {
        if (!ppvObject) return E_POINTER;
        if (riid == IID_IUnknown ||
            riid == OFFICIAL_IID_IDXCoreAdapter ||
            riid == OFFICIAL_IID_IDXCoreAdapter1) {
            *ppvObject = static_cast<IDXCoreAdapter1*>(this);
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

    bool IsValid() override { return true; }
    bool IsAttributeSupported(const IID& attributeGUID) override {
        return (attributeGUID == OFFICIAL_DXCORE_ADAPTER_ATTRIBUTE_D3D11_GRAPHICS ||
                attributeGUID == OFFICIAL_DXCORE_ADAPTER_ATTRIBUTE_D3D12_GRAPHICS ||
                attributeGUID == OFFICIAL_DXCORE_ADAPTER_ATTRIBUTE_D3D12_CORE_COMPUTE ||
                attributeGUID == OFFICIAL_DXCORE_ADAPTER_ATTRIBUTE_D3D12_GENERIC_ML);
    }
    bool IsPropertySupported(DXCoreAdapterProperty) override { return true; }

    HRESULT GetPropertySize(DXCoreAdapterProperty property, size_t* bufferSize) override {
        if (!bufferSize) return E_POINTER;
        switch (property) {
            case DXCoreAdapterProperty::InstanceLuid:          *bufferSize = sizeof(LUID); break;
            case DXCoreAdapterProperty::DriverVersion:         *bufferSize = sizeof(uint64_t); break;
            case DXCoreAdapterProperty::DriverDescription:     *bufferSize = sizeof(kDesc); break;
            case DXCoreAdapterProperty::HardwareID:            *bufferSize = sizeof(DXCoreHardwareID); break;
            case DXCoreAdapterProperty::DedicatedAdapterMemory:*bufferSize = sizeof(uint64_t); break;
            case DXCoreAdapterProperty::DedicatedSystemMemory: *bufferSize = sizeof(uint64_t); break;
            case DXCoreAdapterProperty::SharedSystemMemory:    *bufferSize = sizeof(uint64_t); break;
            case DXCoreAdapterProperty::IsHardware:            *bufferSize = sizeof(bool); break;
            case DXCoreAdapterProperty::IsIntegrated:          *bufferSize = sizeof(bool); break;
            case DXCoreAdapterProperty::IsDetachable:          *bufferSize = sizeof(bool); break;
            default:                                           *bufferSize = sizeof(uint32_t); break;
        }
        return S_OK;
    }

    HRESULT GetProperty(DXCoreAdapterProperty property, size_t bufferSize, void* propertyData) override {
        if (!propertyData) return E_POINTER;
        size_t req = 0;
        GetPropertySize(property, &req);
        if (bufferSize < req) return E_INVALIDARG;

        switch (property) {
            case DXCoreAdapterProperty::InstanceLuid: {
                auto* luid = static_cast<LUID*>(propertyData);
                luid->LowPart = 0x10DE2684u;
                luid->HighPart = 0;
                break;
            }
            case DXCoreAdapterProperty::DriverVersion:
                *static_cast<uint64_t*>(propertyData) = 0x001F000000010266ULL;
                break;
            case DXCoreAdapterProperty::DriverDescription:
                std::memcpy(propertyData, kDesc, sizeof(kDesc));
                break;
            case DXCoreAdapterProperty::HardwareID: {
                auto* hw = static_cast<DXCoreHardwareID*>(propertyData);
                hw->vendorID = 0x10DE;
                hw->deviceID = 0x2684;
                hw->subSysID = 0x168010DE;
                hw->revision = 0xA1;
                break;
            }
            case DXCoreAdapterProperty::DedicatedAdapterMemory:
                *static_cast<uint64_t*>(propertyData) = 24ULL * 1024 * 1024 * 1024;
                break;
            case DXCoreAdapterProperty::DedicatedSystemMemory:
                *static_cast<uint64_t*>(propertyData) = 0ULL;
                break;
            case DXCoreAdapterProperty::SharedSystemMemory:
                *static_cast<uint64_t*>(propertyData) = 32ULL * 1024 * 1024 * 1024;
                break;
            case DXCoreAdapterProperty::IsHardware:
                *static_cast<bool*>(propertyData) = true;
                break;
            case DXCoreAdapterProperty::IsIntegrated:
            case DXCoreAdapterProperty::IsDetachable:
                *static_cast<bool*>(propertyData) = false;
                break;
            default:
                std::memset(propertyData, 0, bufferSize);
                break;
        }
        return S_OK;
    }

    bool IsQueryStateSupported(uint32_t) override { return true; }
    HRESULT QueryState(uint32_t, size_t, const void*, size_t outputBufferSize, void* outputBuffer) override {
        if (!outputBuffer) return E_POINTER;
        if (outputBufferSize >= sizeof(DXCoreAdapterMemoryBudget)) {
            auto* b = static_cast<DXCoreAdapterMemoryBudget*>(outputBuffer);
            b->budget = (22ULL * 1024 + 512) * 1024 * 1024;
            b->currentUsage = 512ULL * 1024 * 1024;
            b->availableForReservation = 4ULL * 1024 * 1024 * 1024;
            b->currentReservation = 0;
        }
        return S_OK;
    }
    bool IsSetStateSupported(uint32_t) override { return true; }
    HRESULT SetState(uint32_t, size_t, const void*, size_t, const void*) override { return S_OK; }
    HRESULT GetFactory(const IID& riid, void** ppvFactory) override {
        if (!ppvFactory || !parent_factory_) return E_POINTER;
        return parent_factory_->QueryInterface(riid, ppvFactory);
    }
    HRESULT GetPropertyWithInput(DXCoreAdapterProperty property, size_t, const void*,
                                 size_t outputBufferSize, void* outputBuffer) override {
        return GetProperty(property, outputBufferSize, outputBuffer);
    }
};

class PrismDXCoreAdapterListImpl final : public IDXCoreAdapterList {
    std::atomic<uint32_t> ref_count_{1};
    IUnknown* parent_factory_ = nullptr;

public:
    explicit PrismDXCoreAdapterListImpl(IUnknown* fac = nullptr) : parent_factory_(fac) {
        if (parent_factory_) parent_factory_->AddRef();
    }
    ~PrismDXCoreAdapterListImpl() {
        if (parent_factory_) parent_factory_->Release();
    }

    int32_t QueryInterface(const IID& riid, void** ppvObject) override {
        if (!ppvObject) return E_POINTER;
        if (riid == IID_IUnknown || riid == OFFICIAL_IID_IDXCoreAdapterList) {
            *ppvObject = static_cast<IDXCoreAdapterList*>(this);
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

    HRESULT GetAdapter(uint32_t index, const IID& riid, void** ppvAdapter) override {
        if (!ppvAdapter || index > 0) return E_INVALIDARG;
        auto* adp = new PrismDXCoreAdapter1Impl(parent_factory_);
        HRESULT hr = adp->QueryInterface(riid, ppvAdapter);
        adp->Release();
        return hr;
    }
    uint32_t GetAdapterCount() override { return 1u; }
    bool IsStale() override { return false; }
    HRESULT GetFactory(const IID& riid, void** ppvFactory) override {
        if (!ppvFactory || !parent_factory_) return E_POINTER;
        return parent_factory_->QueryInterface(riid, ppvFactory);
    }
    HRESULT Sort(uint32_t, const uint32_t*) override { return S_OK; }
    bool IsAdapterPreferenceSupported(uint32_t) override { return true; }
};

class PrismDXCoreAdapterFactory1Impl final : public IDXCoreAdapterFactory1 {
    std::atomic<uint32_t> ref_count_{1};

public:
    int32_t QueryInterface(const IID& riid, void** ppvObject) override {
        if (!ppvObject) return E_POINTER;
        if (riid == IID_IUnknown ||
            riid == OFFICIAL_IID_IDXCoreAdapterFactory ||
            riid == OFFICIAL_IID_IDXCoreAdapterFactory1) {
            *ppvObject = static_cast<IDXCoreAdapterFactory1*>(this);
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

    HRESULT CreateAdapterList(uint32_t numAttributes,
                              const IID* filterAttributes,
                              const IID& riid,
                              void** ppvAdapterList) override {
        if (numAttributes == 0 || !filterAttributes || !ppvAdapterList) return E_INVALIDARG;
        auto* list = new PrismDXCoreAdapterListImpl(this);
        HRESULT hr = list->QueryInterface(riid, ppvAdapterList);
        list->Release();
        return hr;
    }
    HRESULT GetAdapterByLuid(const LUID&, const IID& riid, void** ppvAdapter) override {
        if (!ppvAdapter) return E_POINTER;
        auto* adp = new PrismDXCoreAdapter1Impl(this);
        HRESULT hr = adp->QueryInterface(riid, ppvAdapter);
        adp->Release();
        return hr;
    }
    bool IsNotificationTypeSupported(uint32_t) override { return true; }
    HRESULT RegisterEventNotification(IUnknown*, uint32_t, void*, void*, uint32_t* eventCookie) override {
        if (eventCookie) *eventCookie = 1;
        return S_OK;
    }
    HRESULT UnregisterEventNotification(uint32_t) override { return S_OK; }
    HRESULT CreateAdapterListByWorkload(uint32_t, uint32_t, uint32_t,
                                        const IID& riid,
                                        void** ppvAdapterList) override {
        if (!ppvAdapterList) return E_POINTER;
        auto* list = new PrismDXCoreAdapterListImpl(this);
        HRESULT hr = list->QueryInterface(riid, ppvAdapterList);
        list->Release();
        return hr;
    }
};

// ----------------------------------------------------------------------------
// 5. Canonical dxcore.dll Export Entry Point
// ----------------------------------------------------------------------------
inline HRESULT DXCoreCreateAdapterFactory(const IID& riid, void** ppvFactory) {
    if (!ppvFactory) return E_POINTER;
    auto* fac = new PrismDXCoreAdapterFactory1Impl();
    HRESULT hr = fac->QueryInterface(riid, ppvFactory);
    fac->Release();
    return hr;
}

} // namespace prismx::DXCoreComAbi
