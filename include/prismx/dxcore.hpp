// ============================================================================
// PrismX: DXCore Modern Adapter Enumeration Subsystem
//
// Strict Clean-Room Implementation based on Microsoft's MIT-licensed:
//   - https://github.com/microsoft/DirectX-Headers (dxcore.h / dxcore_interface.h)
//   - Open DirectX Specifications for Modern Adapter Enumeration
//
// Subsystem Overview:
//   dxcore.hpp provides low-overhead, modular GPU/NPU device enumeration
//   independent of DXGI desktop/swapchain dependencies, engineered for compute,
//   machine learning (DirectML), and Direct3D 12 device creation.
//
// Interfaces:
//   - IDXCoreAdapter
//   - IDXCoreAdapterList
//   - IDXCoreAdapterFactory
//
// Clean-Room Implementation in ISO C++23. Zero External Dependencies.
// ============================================================================

#pragma once

#include "types.hpp"

#include <cstdint>
#include <string>
#include <vector>
#include <memory>
#include <atomic>
#include <mutex>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <sstream>

namespace prismx {

// ============================================================================
// 1. GUIDs & Interface Identifiers
// ============================================================================

inline constexpr IID IID_IDXCoreAdapter = {
    0xf0db4c7f, 0xcf5a, 0x42a6, { 0xa1, 0x52, 0xcb, 0x81, 0x12, 0x7b, 0x3f, 0x66 }
};

inline constexpr IID IID_IDXCoreAdapterList = {
    0x526c7776, 0x40e9, 0x459b, { 0xb7, 0x11, 0xf3, 0x2a, 0xd7, 0x6d, 0xfc, 0x28 }
};

inline constexpr IID IID_IDXCoreAdapterFactory = {
    0x78e687d0, 0x2629, 0x495b, { 0xa2, 0x4c, 0x68, 0xe7, 0x74, 0x64, 0x85, 0x94 }
};

// Adapter Attribute GUIDs
inline constexpr GUID DXCORE_ADAPTER_ATTRIBUTE_D3D11_GRAPHICS = {
    0x8c47866b, 0xf31a, 0x45e5, { 0xbd, 0x98, 0x04, 0x84, 0xa7, 0x37, 0x83, 0xfa }
};

inline constexpr GUID DXCORE_ADAPTER_ATTRIBUTE_D3D12_GRAPHICS = {
    0x0c9e7e61, 0xcb94, 0x4645, { 0x89, 0xf9, 0xd7, 0x2d, 0x0d, 0xe3, 0x0e, 0xcb }
};

inline constexpr GUID DXCORE_ADAPTER_ATTRIBUTE_D3D12_CORE_COMPUTE = {
    0x248e2800, 0xa793, 0x4724, { 0xab, 0xaa, 0x23, 0xa6, 0xde, 0x1a, 0x47, 0xd0 }
};

inline constexpr GUID DXCORE_ADAPTER_ATTRIBUTE_WSL = {
    0x9035f5e5, 0x33a7, 0x4fe7, { 0x87, 0xb4, 0x3a, 0x56, 0x24, 0x7c, 0x0a, 0x87 }
};

// ============================================================================
// 2. Constants & Enums
// ============================================================================

enum class DXCoreAdapterProperty : uint32_t {
    InstanceLUID                 = 0,
    DriverVersion                = 1,
    DriverDescription            = 2,
    HardwareID                   = 3,
    KmdModelVersion              = 4,
    ComputePreemptionGranularity = 5,
    GraphicsPreemptionGranularity= 6,
    DedicatedAdapterMemory       = 7,
    DedicatedSystemMemory        = 8,
    SharedSystemMemory           = 9,
    AdapterEngineCount           = 10,
    IsHardware                   = 11,
    IsIntegrated                 = 12,
    IsDetachable                 = 13,
    HardwareIDParts              = 14
};

enum class DXCoreAdapterEngineGranularity : uint32_t {
    DMA         = 0,
    Packet      = 1,
    Instruction = 2,
    PageFault   = 3,
    Partition   = 4
};

enum class DXCoreAdapterState : uint32_t {
    IsDriverUpdateInProgress = 0,
    AdapterMemoryBudget      = 1
};

enum class DXCoreSegmentGroup : uint32_t {
    Local    = 0,
    NonLocal = 1
};

enum class DXCoreNotificationType : uint32_t {
    AdapterListStale                          = 0,
    AdapterNoLongerValid                      = 1,
    AdapterBudgetChange                       = 2,
    AdapterHardwareContentProtectionTeardown  = 3
};

enum class DXCoreAdapterPreference : uint32_t {
    Hardware        = 0,
    MinimumPower    = 1,
    HighPerformance = 2
};

// ============================================================================
// 3. Structures
// ============================================================================

struct DXCoreHardwareID {
    uint32_t vendorID;
    uint32_t deviceID;
    uint32_t subSysID;
    uint32_t revision;
};

struct DXCoreHardwareIDParts {
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

struct DXCoreAdapterMemoryBudgetNodeSegmentGroup {
    uint32_t nodeIndex;
    DXCoreSegmentGroup segmentGroup;
};

using PFN_DXCORE_NOTIFICATION_CALLBACK = void (*)(DXCoreNotificationType notificationType, IUnknown* object, void* context);

// ============================================================================
// 4. Abstract COM Interfaces
// ============================================================================

class IDXCoreAdapter;
class IDXCoreAdapterList;
class IDXCoreAdapterFactory;

class IDXCoreAdapter : public IUnknown {
public:
    virtual bool IsValid() = 0;
    virtual bool IsAttributeSupported(const GUID& attributeGUID) = 0;
    virtual bool IsPropertySupported(DXCoreAdapterProperty property) = 0;
    virtual HRESULT GetProperty(DXCoreAdapterProperty property, size_t bufferSize, void* propertyData) = 0;
    virtual HRESULT GetPropertySize(DXCoreAdapterProperty property, size_t* bufferSize) = 0;
    virtual bool IsQueryStateSupported(DXCoreAdapterState property) = 0;
    virtual HRESULT QueryState(DXCoreAdapterState state, size_t inputStateDetailsSize, const void* inputStateDetails, size_t outputBufferSize, void* outputBuffer) = 0;
    virtual bool IsSetStateSupported(DXCoreAdapterState property) = 0;
    virtual HRESULT SetState(DXCoreAdapterState state, size_t inputStateDetailsSize, const void* inputStateDetails, size_t inputDataSize, const void* inputData) = 0;
    virtual HRESULT GetFactory(const IID& riid, void** ppvFactory) = 0;
};

class IDXCoreAdapterList : public IUnknown {
public:
    virtual HRESULT GetAdapter(uint32_t index, const IID& riid, void** ppvAdapter) = 0;
    virtual uint32_t GetAdapterCount() = 0;
    virtual bool IsStale() = 0;
    virtual HRESULT GetFactory(const IID& riid, void** ppvFactory) = 0;
    virtual HRESULT Sort(uint32_t preferencesCount, const DXCoreAdapterPreference* preferences) = 0;
    virtual bool IsAdapterInList(IDXCoreAdapter* adapter) = 0;
};

class IDXCoreAdapterFactory : public IUnknown {
public:
    virtual HRESULT CreateAdapterList(uint32_t numAttributes, const GUID* filterAttributes, const IID& riid, void** ppvAdapterList) = 0;
    virtual HRESULT GetAdapterByLUID(const LUID& adapterLUID, const IID& riid, void** ppvAdapter) = 0;
    virtual bool IsNotificationTypeSupported(DXCoreNotificationType notificationType) = 0;
    virtual HRESULT RegisterEventNotification(IUnknown* dxCoreObject, DXCoreNotificationType notificationType, PFN_DXCORE_NOTIFICATION_CALLBACK callback, void* callbackContext, uint32_t* eventCookie) = 0;
    virtual HRESULT UnregisterEventNotification(uint32_t eventCookie) = 0;
};

// ============================================================================
// 5. Concrete Subsystem Implementation
// ============================================================================

class PrismXCoreAdapterImpl : public IDXCoreAdapter {
private:
    std::atomic<uint32_t> m_refCount{ 1 };
    IDXCoreAdapterFactory* m_pFactory{ nullptr };
    std::string m_description;
    LUID m_luid{};
    DXCoreHardwareID m_hwId{};
    uint64_t m_driverVersion{ 0x001F000000010000ULL }; // 31.0.100.1
    uint64_t m_dedicatedAdapterMemory{ 16ULL * 1024 * 1024 * 1024 }; // 16 GB
    uint64_t m_dedicatedSystemMemory{ 0 };
    uint64_t m_sharedSystemMemory{ 32ULL * 1024 * 1024 * 1024 };    // 32 GB
    uint32_t m_engineCount{ 8 };
    bool m_isHardware{ true };
    bool m_isIntegrated{ false };
    bool m_isDetachable{ false };
    bool m_isValid{ true };
    std::vector<GUID> m_supportedAttributes;

public:
    PrismXCoreAdapterImpl(IDXCoreAdapterFactory* factory,
                          std::string desc,
                          LUID luid,
                          DXCoreHardwareID hwId,
                          uint64_t dedicatedMem,
                          bool isIntegrated)
        : m_pFactory(factory),
          m_description(std::move(desc)),
          m_luid(luid),
          m_hwId(hwId),
          m_dedicatedAdapterMemory(dedicatedMem),
          m_isIntegrated(isIntegrated) {
        m_supportedAttributes.push_back(DXCORE_ADAPTER_ATTRIBUTE_D3D11_GRAPHICS);
        m_supportedAttributes.push_back(DXCORE_ADAPTER_ATTRIBUTE_D3D12_GRAPHICS);
        m_supportedAttributes.push_back(DXCORE_ADAPTER_ATTRIBUTE_D3D12_CORE_COMPUTE);
        m_supportedAttributes.push_back(DXCORE_ADAPTER_ATTRIBUTE_WSL);
    }

    HRESULT QueryInterface(const IID& riid, void** ppv) override {
        if (!ppv) return E_POINTER;
        if (riid == IID_IUnknown || riid == IID_IDXCoreAdapter) {
            *ppv = static_cast<IDXCoreAdapter*>(this);
            AddRef();
            return S_OK;
        }
        *ppv = nullptr;
        return E_NOINTERFACE;
    }

    uint32_t AddRef() override {
        return m_refCount.fetch_add(1, std::memory_order_relaxed) + 1;
    }

    uint32_t Release() override {
        uint32_t count = m_refCount.fetch_sub(1, std::memory_order_acq_rel) - 1;
        if (count == 0) delete this;
        return count;
    }

    bool IsValid() override {
        return m_isValid;
    }

    bool IsAttributeSupported(const GUID& attributeGUID) override {
        for (const auto& attr : m_supportedAttributes) {
            if (attr == attributeGUID) return true;
        }
        return false;
    }

    bool IsPropertySupported(DXCoreAdapterProperty property) override {
        switch (property) {
            case DXCoreAdapterProperty::InstanceLUID:
            case DXCoreAdapterProperty::DriverVersion:
            case DXCoreAdapterProperty::DriverDescription:
            case DXCoreAdapterProperty::HardwareID:
            case DXCoreAdapterProperty::KmdModelVersion:
            case DXCoreAdapterProperty::ComputePreemptionGranularity:
            case DXCoreAdapterProperty::GraphicsPreemptionGranularity:
            case DXCoreAdapterProperty::DedicatedAdapterMemory:
            case DXCoreAdapterProperty::DedicatedSystemMemory:
            case DXCoreAdapterProperty::SharedSystemMemory:
            case DXCoreAdapterProperty::AdapterEngineCount:
            case DXCoreAdapterProperty::IsHardware:
            case DXCoreAdapterProperty::IsIntegrated:
            case DXCoreAdapterProperty::IsDetachable:
            case DXCoreAdapterProperty::HardwareIDParts:
                return true;
            default:
                return false;
        }
    }

    HRESULT GetPropertySize(DXCoreAdapterProperty property, size_t* bufferSize) override {
        if (!bufferSize) return E_POINTER;
        switch (property) {
            case DXCoreAdapterProperty::InstanceLUID:
                *bufferSize = sizeof(LUID);
                return S_OK;
            case DXCoreAdapterProperty::DriverVersion:
                *bufferSize = sizeof(uint64_t);
                return S_OK;
            case DXCoreAdapterProperty::DriverDescription:
                *bufferSize = m_description.size() + 1;
                return S_OK;
            case DXCoreAdapterProperty::HardwareID:
            case DXCoreAdapterProperty::HardwareIDParts:
                *bufferSize = sizeof(DXCoreHardwareID);
                return S_OK;
            case DXCoreAdapterProperty::KmdModelVersion:
                *bufferSize = sizeof(uint32_t);
                return S_OK;
            case DXCoreAdapterProperty::ComputePreemptionGranularity:
            case DXCoreAdapterProperty::GraphicsPreemptionGranularity:
                *bufferSize = sizeof(DXCoreAdapterEngineGranularity);
                return S_OK;
            case DXCoreAdapterProperty::DedicatedAdapterMemory:
            case DXCoreAdapterProperty::DedicatedSystemMemory:
            case DXCoreAdapterProperty::SharedSystemMemory:
                *bufferSize = sizeof(uint64_t);
                return S_OK;
            case DXCoreAdapterProperty::AdapterEngineCount:
                *bufferSize = sizeof(uint32_t);
                return S_OK;
            case DXCoreAdapterProperty::IsHardware:
            case DXCoreAdapterProperty::IsIntegrated:
            case DXCoreAdapterProperty::IsDetachable:
                *bufferSize = sizeof(bool);
                return S_OK;
            default:
                return E_INVALIDARG;
        }
    }

    HRESULT GetProperty(DXCoreAdapterProperty property, size_t bufferSize, void* propertyData) override {
        if (!propertyData) return E_POINTER;
        size_t requiredSize = 0;
        HRESULT hr = GetPropertySize(property, &requiredSize);
        if (FAILED(hr)) return hr;
        if (bufferSize < requiredSize) return E_INVALIDARG;

        switch (property) {
            case DXCoreAdapterProperty::InstanceLUID:
                std::memcpy(propertyData, &m_luid, sizeof(LUID));
                return S_OK;
            case DXCoreAdapterProperty::DriverVersion:
                std::memcpy(propertyData, &m_driverVersion, sizeof(uint64_t));
                return S_OK;
            case DXCoreAdapterProperty::DriverDescription:
                std::memcpy(propertyData, m_description.c_str(), m_description.size() + 1);
                return S_OK;
            case DXCoreAdapterProperty::HardwareID:
            case DXCoreAdapterProperty::HardwareIDParts:
                std::memcpy(propertyData, &m_hwId, sizeof(DXCoreHardwareID));
                return S_OK;
            case DXCoreAdapterProperty::KmdModelVersion: {
                uint32_t kmd = 0x2000; // WDDM 2.0+
                std::memcpy(propertyData, &kmd, sizeof(uint32_t));
                return S_OK;
            }
            case DXCoreAdapterProperty::ComputePreemptionGranularity: {
                auto g = DXCoreAdapterEngineGranularity::Instruction;
                std::memcpy(propertyData, &g, sizeof(g));
                return S_OK;
            }
            case DXCoreAdapterProperty::GraphicsPreemptionGranularity: {
                auto g = DXCoreAdapterEngineGranularity::DMA;
                std::memcpy(propertyData, &g, sizeof(g));
                return S_OK;
            }
            case DXCoreAdapterProperty::DedicatedAdapterMemory:
                std::memcpy(propertyData, &m_dedicatedAdapterMemory, sizeof(uint64_t));
                return S_OK;
            case DXCoreAdapterProperty::DedicatedSystemMemory:
                std::memcpy(propertyData, &m_dedicatedSystemMemory, sizeof(uint64_t));
                return S_OK;
            case DXCoreAdapterProperty::SharedSystemMemory:
                std::memcpy(propertyData, &m_sharedSystemMemory, sizeof(uint64_t));
                return S_OK;
            case DXCoreAdapterProperty::AdapterEngineCount:
                std::memcpy(propertyData, &m_engineCount, sizeof(uint32_t));
                return S_OK;
            case DXCoreAdapterProperty::IsHardware:
                std::memcpy(propertyData, &m_isHardware, sizeof(bool));
                return S_OK;
            case DXCoreAdapterProperty::IsIntegrated:
                std::memcpy(propertyData, &m_isIntegrated, sizeof(bool));
                return S_OK;
            case DXCoreAdapterProperty::IsDetachable:
                std::memcpy(propertyData, &m_isDetachable, sizeof(bool));
                return S_OK;
            default:
                return E_INVALIDARG;
        }
    }

    bool IsQueryStateSupported(DXCoreAdapterState property) override {
        return (property == DXCoreAdapterState::IsDriverUpdateInProgress ||
                property == DXCoreAdapterState::AdapterMemoryBudget);
    }

    HRESULT QueryState(DXCoreAdapterState state, size_t, const void*, size_t outputBufferSize, void* outputBuffer) override {
        if (!outputBuffer) return E_POINTER;
        if (state == DXCoreAdapterState::IsDriverUpdateInProgress) {
            if (outputBufferSize < sizeof(bool)) return E_INVALIDARG;
            bool updating = false;
            std::memcpy(outputBuffer, &updating, sizeof(bool));
            return S_OK;
        } else if (state == DXCoreAdapterState::AdapterMemoryBudget) {
            if (outputBufferSize < sizeof(DXCoreAdapterMemoryBudget)) return E_INVALIDARG;
            DXCoreAdapterMemoryBudget budget{};
            budget.budget = m_dedicatedAdapterMemory;
            budget.currentUsage = 1024ULL * 1024 * 256; // 256 MB in use
            budget.availableForReservation = m_dedicatedAdapterMemory - budget.currentUsage;
            budget.currentReservation = 0;
            std::memcpy(outputBuffer, &budget, sizeof(budget));
            return S_OK;
        }
        return E_NOTIMPL;
    }

    bool IsSetStateSupported(DXCoreAdapterState) override {
        return false;
    }

    HRESULT SetState(DXCoreAdapterState, size_t, const void*, size_t, const void*) override {
        return E_NOTIMPL;
    }

    HRESULT GetFactory(const IID& riid, void** ppvFactory) override {
        if (!ppvFactory) return E_POINTER;
        if (!m_pFactory) return E_FAIL;
        return m_pFactory->QueryInterface(riid, ppvFactory);
    }

    const LUID& GetLUID() const { return m_luid; }
    uint64_t GetDedicatedMemory() const { return m_dedicatedAdapterMemory; }
    bool IsIntegratedAdapter() const { return m_isIntegrated; }
    const std::string& GetDescription() const { return m_description; }
};

class PrismXCoreAdapterListImpl : public IDXCoreAdapterList {
private:
    std::atomic<uint32_t> m_refCount{ 1 };
    IDXCoreAdapterFactory* m_pFactory{ nullptr };
    std::vector<ComPtr<IDXCoreAdapter>> m_adapters;
    bool m_isStale{ false };

public:
    PrismXCoreAdapterListImpl(IDXCoreAdapterFactory* factory, std::vector<ComPtr<IDXCoreAdapter>> adapters)
        : m_pFactory(factory), m_adapters(std::move(adapters)) {}

    HRESULT QueryInterface(const IID& riid, void** ppv) override {
        if (!ppv) return E_POINTER;
        if (riid == IID_IUnknown || riid == IID_IDXCoreAdapterList) {
            *ppv = static_cast<IDXCoreAdapterList*>(this);
            AddRef();
            return S_OK;
        }
        *ppv = nullptr;
        return E_NOINTERFACE;
    }

    uint32_t AddRef() override {
        return m_refCount.fetch_add(1, std::memory_order_relaxed) + 1;
    }

    uint32_t Release() override {
        uint32_t count = m_refCount.fetch_sub(1, std::memory_order_acq_rel) - 1;
        if (count == 0) delete this;
        return count;
    }

    HRESULT GetAdapter(uint32_t index, const IID& riid, void** ppvAdapter) override {
        if (!ppvAdapter) return E_POINTER;
        if (index >= m_adapters.size()) return E_INVALIDARG;
        return m_adapters[index]->QueryInterface(riid, ppvAdapter);
    }

    uint32_t GetAdapterCount() override {
        return static_cast<uint32_t>(m_adapters.size());
    }

    bool IsStale() override {
        return m_isStale;
    }

    HRESULT GetFactory(const IID& riid, void** ppvFactory) override {
        if (!ppvFactory) return E_POINTER;
        if (!m_pFactory) return E_FAIL;
        return m_pFactory->QueryInterface(riid, ppvFactory);
    }

    HRESULT Sort(uint32_t preferencesCount, const DXCoreAdapterPreference* preferences) override {
        if (!preferences && preferencesCount > 0) return E_POINTER;

        for (uint32_t i = 0; i < preferencesCount; ++i) {
            if (preferences[i] == DXCoreAdapterPreference::HighPerformance) {
                std::stable_sort(m_adapters.begin(), m_adapters.end(), [](const auto& a, const auto& b) {
                    auto* pa = static_cast<PrismXCoreAdapterImpl*>(a.Get());
                    auto* pb = static_cast<PrismXCoreAdapterImpl*>(b.Get());
                    return pa->GetDedicatedMemory() > pb->GetDedicatedMemory();
                });
            } else if (preferences[i] == DXCoreAdapterPreference::MinimumPower) {
                std::stable_sort(m_adapters.begin(), m_adapters.end(), [](const auto& a, const auto& b) {
                    auto* pa = static_cast<PrismXCoreAdapterImpl*>(a.Get());
                    auto* pb = static_cast<PrismXCoreAdapterImpl*>(b.Get());
                    return pa->IsIntegratedAdapter() && !pb->IsIntegratedAdapter();
                });
            }
        }
        return S_OK;
    }

    bool IsAdapterInList(IDXCoreAdapter* adapter) override {
        if (!adapter) return false;
        for (const auto& a : m_adapters) {
            if (a.Get() == adapter) return true;
        }
        return false;
    }
};

class PrismXCoreAdapterFactoryImpl : public IDXCoreAdapterFactory {
private:
    std::atomic<uint32_t> m_refCount{ 1 };
    std::mutex m_mutex;
    std::vector<ComPtr<PrismXCoreAdapterImpl>> m_allAdapters;
    struct NotificationEntry {
        uint32_t cookie;
        DXCoreNotificationType type;
        PFN_DXCORE_NOTIFICATION_CALLBACK callback;
        void* context;
    };
    std::vector<NotificationEntry> m_notifications;
    uint32_t m_nextCookie{ 100 };

public:
    PrismXCoreAdapterFactoryImpl() {
        // 1. Primary Sovereign Dedicated GPU
        LUID luid1{ 0x1000, 0 };
        DXCoreHardwareID hw1{ 0x13B5, 0x2B80, 0x0001, 0x01 }; // PrismX Sovereign
        auto* primary = new PrismXCoreAdapterImpl(this, "PrismX Sovereign Neural & Graphics Accelerator", luid1, hw1, 16ULL * 1024 * 1024 * 1024, false);
        m_allAdapters.emplace_back(primary);
        primary->Release();

        // 2. Secondary Integrated Neural Compute Unit
        LUID luid2{ 0x1001, 0 };
        DXCoreHardwareID hw2{ 0x13B5, 0x10A0, 0x0001, 0x01 };
        auto* secondary = new PrismXCoreAdapterImpl(this, "PrismX Integrated Neural Compute Core", luid2, hw2, 0, true);
        m_allAdapters.emplace_back(secondary);
        secondary->Release();
    }

    HRESULT QueryInterface(const IID& riid, void** ppv) override {
        if (!ppv) return E_POINTER;
        if (riid == IID_IUnknown || riid == IID_IDXCoreAdapterFactory) {
            *ppv = static_cast<IDXCoreAdapterFactory*>(this);
            AddRef();
            return S_OK;
        }
        *ppv = nullptr;
        return E_NOINTERFACE;
    }

    uint32_t AddRef() override {
        return m_refCount.fetch_add(1, std::memory_order_relaxed) + 1;
    }

    uint32_t Release() override {
        uint32_t count = m_refCount.fetch_sub(1, std::memory_order_acq_rel) - 1;
        if (count == 0) delete this;
        return count;
    }

    HRESULT CreateAdapterList(uint32_t numAttributes, const GUID* filterAttributes, const IID& riid, void** ppvAdapterList) override {
        if (!ppvAdapterList) return E_POINTER;
        std::vector<ComPtr<IDXCoreAdapter>> matched;

        for (auto& adapter : m_allAdapters) {
            bool matches = true;
            for (uint32_t i = 0; i < numAttributes; ++i) {
                if (!adapter->IsAttributeSupported(filterAttributes[i])) {
                    matches = false;
                    break;
                }
            }
            if (matches) {
                matched.push_back(ComPtr<IDXCoreAdapter>(adapter.Get()));
            }
        }

        auto* list = new PrismXCoreAdapterListImpl(this, std::move(matched));
        HRESULT hr = list->QueryInterface(riid, ppvAdapterList);
        list->Release();
        return hr;
    }

    HRESULT GetAdapterByLUID(const LUID& adapterLUID, const IID& riid, void** ppvAdapter) override {
        if (!ppvAdapter) return E_POINTER;
        for (auto& adapter : m_allAdapters) {
            const auto& l = adapter->GetLUID();
            if (l.LowPart == adapterLUID.LowPart && l.HighPart == adapterLUID.HighPart) {
                return adapter->QueryInterface(riid, ppvAdapter);
            }
        }
        return E_FAIL;
    }

    bool IsNotificationTypeSupported(DXCoreNotificationType notificationType) override {
        return notificationType == DXCoreNotificationType::AdapterBudgetChange ||
               notificationType == DXCoreNotificationType::AdapterListStale;
    }

    HRESULT RegisterEventNotification(IUnknown*, DXCoreNotificationType notificationType, PFN_DXCORE_NOTIFICATION_CALLBACK callback, void* callbackContext, uint32_t* eventCookie) override {
        if (!callback || !eventCookie) return E_POINTER;
        std::lock_guard<std::mutex> lock(m_mutex);
        uint32_t cookie = m_nextCookie++;
        m_notifications.push_back({ cookie, notificationType, callback, callbackContext });
        *eventCookie = cookie;
        return S_OK;
    }

    HRESULT UnregisterEventNotification(uint32_t eventCookie) override {
        std::lock_guard<std::mutex> lock(m_mutex);
        auto it = std::remove_if(m_notifications.begin(), m_notifications.end(), [eventCookie](const auto& entry) {
            return entry.cookie == eventCookie;
        });
        if (it != m_notifications.end()) {
            m_notifications.erase(it, m_notifications.end());
            return S_OK;
        }
        return E_INVALIDARG;
    }
};

// ============================================================================
// 6. Global API Factory Function
// ============================================================================

inline HRESULT DXCoreCreateAdapterFactory(const IID& riid, void** ppvFactory) {
    if (!ppvFactory) return E_POINTER;
    static PrismXCoreAdapterFactoryImpl s_factory;
    return s_factory.QueryInterface(riid, ppvFactory);
}

} // namespace prismx
