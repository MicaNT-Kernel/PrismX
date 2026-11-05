// ============================================================================
// PrismX: Direct3D 12 Pipeline Library, Shader Cache Sessions,
//         Resource Allocation Info 1 & Agility SDK 1.614+ Extended Heaps
//
// Clean-Room Implementation in ISO C++23.
// Tribute to Dave Cutler's 1988 DEC PRISM Architecture.
// ============================================================================

#pragma once

#include "types.hpp"
#include "d3d12.hpp"
#include "d3d12_com_vtable_options21.hpp"
#include <vector>
#include <string>
#include <string_view>
#include <map>
#include <cstring>
#include <atomic>
#include <algorithm>

namespace prismx {

// ============================================================================
// 1. D3D12 Pipeline Library & Cached Blobs
// ============================================================================

struct D3D12_CACHED_PIPELINE_STATE {
    const void* pCachedBlob{ nullptr };
    size_t      CachedBlobSizeInBytes{ 0 };
};

class ID3D12PipelineLibrary : public ID3D12DeviceChild {
public:
    virtual int32_t StorePipeline(const wchar_t* pName, ID3D12PipelineState* pPipeline) = 0;
    virtual int32_t LoadGraphicsPipeline(const wchar_t* pName, const D3D12_GRAPHICS_PIPELINE_STATE_DESC* pDesc, const IID& riid, void** ppPipelineState) = 0;
    virtual int32_t LoadComputePipeline(const wchar_t* pName, const void* pDesc, const IID& riid, void** ppPipelineState) = 0;
    virtual size_t  GetSerializedSize() = 0;
    virtual int32_t Serialize(void* pData, size_t DataSizeInBytes) = 0;
};

class ID3D12PipelineLibrary1 : public ID3D12PipelineLibrary {
public:
    virtual int32_t LoadPipeline(const wchar_t* pName, const void* pDesc, const IID& riid, void** ppPipelineState) = 0;
};

class Prism3D12PipelineLibraryImpl : public ID3D12PipelineLibrary1 {
private:
    std::atomic<uint32_t> m_refCount{ 1 };
    ID3D12Device* m_pDevice{ nullptr };
    std::map<std::wstring, ID3D12PipelineState*> m_pipelines;

    static constexpr uint32_t PRISMPL_MAGIC = 0x504C5031; // '1PLP' (PRISMPL1)

public:
    Prism3D12PipelineLibraryImpl(ID3D12Device* pDev, const void* pBlob, size_t blobLen)
        : m_pDevice(pDev) {
        if (pBlob && blobLen >= 12) {
            const auto* u32 = reinterpret_cast<const uint32_t*>(pBlob);
            if (u32[0] == PRISMPL_MAGIC) {
                uint32_t count = u32[1];
                const uint8_t* ptr = reinterpret_cast<const uint8_t*>(pBlob) + 8;
                for (uint32_t i = 0; i < count && ptr < reinterpret_cast<const uint8_t*>(pBlob) + blobLen; ++i) {
                    uint32_t nameLen = *reinterpret_cast<const uint32_t*>(ptr);
                    ptr += 4;
                    if (ptr + nameLen * 2 <= reinterpret_cast<const uint8_t*>(pBlob) + blobLen) {
                        std::wstring name(reinterpret_cast<const wchar_t*>(ptr), nameLen);
                        ptr += nameLen * 2;
                        D3D12_GRAPHICS_PIPELINE_STATE_DESC dummy{};
                        ID3D12PipelineState* pso = nullptr;
                        if (m_pDevice && m_pDevice->CreateGraphicsPipelineState(&dummy, IID_ID3D12PipelineState, reinterpret_cast<void**>(&pso)) == 0) {
                            m_pipelines[name] = pso;
                        }
                    }
                }
            }
        }
    }

    ~Prism3D12PipelineLibraryImpl() override {
        for (auto& [name, pso] : m_pipelines) {
            if (pso) pso->Release();
        }
    }

    int32_t QueryInterface(const IID& riid, void** ppv) override {
        if (!ppv) return -1;
        if (riid == IID_IUnknown || riid == IID_ID3D12Object || riid == IID_ID3D12DeviceChild ||
            riid == D3D12ComAbi::OFFICIAL_IID_ID3D12PipelineLibrary || riid == D3D12ComAbi::OFFICIAL_IID_ID3D12PipelineLibrary1) {
            *ppv = static_cast<ID3D12PipelineLibrary1*>(this);
            AddRef();
            return 0;
        }
        *ppv = nullptr;
        return -2147467262;
    }

    uint32_t AddRef() override { return ++m_refCount; }
    uint32_t Release() override {
        uint32_t c = --m_refCount;
        if (c == 0) delete this;
        return c;
    }

    int32_t GetPrivateData(const IID&, uint32_t*, void*) override { return 0; }
    int32_t SetPrivateData(const IID&, uint32_t, const void*) override { return 0; }
    int32_t SetPrivateDataInterface(const IID&, const IUnknown*) override { return 0; }
    int32_t SetName(const wchar_t*) override { return 0; }
    int32_t GetDevice(const IID&, void** ppDevice) override {
        if (!ppDevice) return -1;
        *ppDevice = m_pDevice;
        if (m_pDevice) m_pDevice->AddRef();
        return 0;
    }

    int32_t StorePipeline(const wchar_t* pName, ID3D12PipelineState* pPipeline) override {
        if (!pName || !pPipeline) return -1;
        if (m_pipelines.find(pName) != m_pipelines.end()) return 1; // E_INVALIDARG / already exists
        pPipeline->AddRef();
        m_pipelines[pName] = pPipeline;
        return 0;
    }

    int32_t LoadGraphicsPipeline(const wchar_t* pName, const D3D12_GRAPHICS_PIPELINE_STATE_DESC*, const IID& riid, void** ppPipelineState) override {
        if (!pName || !ppPipelineState) return -1;
        auto it = m_pipelines.find(pName);
        if (it == m_pipelines.end()) return -2147024894; // E_FILENOTFOUND
        return it->second->QueryInterface(riid, ppPipelineState);
    }

    int32_t LoadComputePipeline(const wchar_t* pName, const void*, const IID& riid, void** ppPipelineState) override {
        if (!pName || !ppPipelineState) return -1;
        auto it = m_pipelines.find(pName);
        if (it == m_pipelines.end()) return -2147024894;
        return it->second->QueryInterface(riid, ppPipelineState);
    }

    int32_t LoadPipeline(const wchar_t* pName, const void*, const IID& riid, void** ppPipelineState) override {
        return LoadComputePipeline(pName, nullptr, riid, ppPipelineState);
    }

    size_t GetSerializedSize() override {
        size_t total = 8; // magic + count
        for (const auto& [name, pso] : m_pipelines) {
            total += 4 + name.size() * sizeof(wchar_t);
        }
        return total;
    }

    int32_t Serialize(void* pData, size_t DataSizeInBytes) override {
        size_t needed = GetSerializedSize();
        if (!pData || DataSizeInBytes < needed) return -1;
        auto* u32 = reinterpret_cast<uint32_t*>(pData);
        u32[0] = PRISMPL_MAGIC;
        u32[1] = static_cast<uint32_t>(m_pipelines.size());
        auto* ptr = reinterpret_cast<uint8_t*>(pData) + 8;
        for (const auto& [name, pso] : m_pipelines) {
            uint32_t nameLen = static_cast<uint32_t>(name.size());
            std::memcpy(ptr, &nameLen, 4);
            ptr += 4;
            std::memcpy(ptr, name.data(), nameLen * sizeof(wchar_t));
            ptr += nameLen * sizeof(wchar_t);
        }
        return 0;
    }
};

// ============================================================================
// 2. Resource Allocation Info 1 & Sub-Allocation Alignment
// ============================================================================

struct D3D12_RESOURCE_ALLOCATION_INFO1 {
    uint64_t Offset{ 0 };
    uint64_t Alignment{ 0 };
    uint64_t SizeInBytes{ 0 };
};

using D3D12_RESOURCE_ALLOCATION_INFO_ABI = D3D12ComAbi::D3D12_RESOURCE_ALLOCATION_INFO_ABI;

inline D3D12_RESOURCE_ALLOCATION_INFO_ABI CalculateResourceAllocationInfo1(
    uint32_t visibleMask,
    uint32_t numResourceDescs,
    const D3D12_RESOURCE_DESC* pResourceDescs,
    D3D12_RESOURCE_ALLOCATION_INFO1* pResourceAllocationInfo1) {
    (void)visibleMask;
    D3D12_RESOURCE_ALLOCATION_INFO_ABI info{};
    if (!pResourceDescs || numResourceDescs == 0) return info;

    uint64_t currentOffset = 0;
    uint64_t maxAlign = 64 * 1024;

    for (uint32_t i = 0; i < numResourceDescs; ++i) {
        uint64_t itemSize = 0;
        uint64_t align = 64 * 1024;
        if (pResourceDescs[i].Dimension == D3D12_RESOURCE_DIMENSION_BUFFER) {
            itemSize = pResourceDescs[i].Width;
        } else if (pResourceDescs[i].Dimension == D3D12_RESOURCE_DIMENSION_TEXTURE2D) {
            itemSize = pResourceDescs[i].Width * pResourceDescs[i].Height * 4;
            if (pResourceDescs[i].SampleDesc.Count > 1 || pResourceDescs[i].Alignment == 4 * 1024 * 1024) {
                align = 4 * 1024 * 1024;
            }
        }
        uint64_t alignedItem = (itemSize + align - 1) & ~(align - 1);
        currentOffset = (currentOffset + align - 1) & ~(align - 1);

        if (pResourceAllocationInfo1) {
            pResourceAllocationInfo1[i].Offset = currentOffset;
            pResourceAllocationInfo1[i].Alignment = align;
            pResourceAllocationInfo1[i].SizeInBytes = alignedItem;
        }

        currentOffset += alignedItem;
        if (align > maxAlign) maxAlign = align;
    }

    info.Alignment = maxAlign;
    info.SizeInBytes = currentOffset;
    return info;
}

// ============================================================================
// 3. Shader Cache Sessions (D3D12 Agility SDK 1.614+)
// ============================================================================

enum D3D12_SHADER_CACHE_MODE {
    D3D12_SHADER_CACHE_MODE_MEMORY = 0,
    D3D12_SHADER_CACHE_MODE_DISK   = 1
};

enum D3D12_SHADER_CACHE_FLAGS : uint32_t {
    D3D12_SHADER_CACHE_FLAG_NONE           = 0,
    D3D12_SHADER_CACHE_FLAG_DRIVER_MANAGED = 1
};

struct D3D12_SHADER_CACHE_SESSION_DESC {
    GUID Identifier;
    D3D12_SHADER_CACHE_MODE Mode;
    D3D12_SHADER_CACHE_FLAGS Flags;
    uint32_t MaximumInMemoryCacheSizeBytes;
    uint32_t MaximumInMemoryCacheEntries;
    uint32_t MaximumValueFileSizeBytes;
};

class ID3D12ShaderCacheSession : public ID3D12DeviceChild {
public:
    virtual int32_t FindValue(const void* pKey, uint32_t KeySize, void* pValue, uint32_t* pValueSize) = 0;
    virtual int32_t StoreValue(const void* pKey, uint32_t KeySize, const void* pValue, uint32_t ValueSize) = 0;
    virtual void SetDeleteOnDestroy() = 0;
    virtual D3D12_SHADER_CACHE_SESSION_DESC GetDesc() = 0;
};

class Prism3D12ShaderCacheSessionImpl : public ID3D12ShaderCacheSession {
private:
    std::atomic<uint32_t> m_refCount{ 1 };
    ID3D12Device* m_pDevice{ nullptr };
    D3D12_SHADER_CACHE_SESSION_DESC m_desc{};
    std::map<std::vector<uint8_t>, std::vector<uint8_t>> m_cache;

public:
    Prism3D12ShaderCacheSessionImpl(ID3D12Device* pDev, const D3D12_SHADER_CACHE_SESSION_DESC& desc)
        : m_pDevice(pDev), m_desc(desc) {}

    int32_t QueryInterface(const IID& riid, void** ppv) override {
        if (!ppv) return -1;
        if (riid == IID_IUnknown || riid == IID_ID3D12Object || riid == IID_ID3D12DeviceChild ||
            riid == D3D12ComAbi::OFFICIAL_IID_ID3D12ShaderCacheSession) {
            *ppv = static_cast<ID3D12ShaderCacheSession*>(this);
            AddRef();
            return 0;
        }
        *ppv = nullptr;
        return -2147467262;
    }

    uint32_t AddRef() override { return ++m_refCount; }
    uint32_t Release() override {
        uint32_t c = --m_refCount;
        if (c == 0) delete this;
        return c;
    }

    int32_t GetPrivateData(const IID&, uint32_t*, void*) override { return 0; }
    int32_t SetPrivateData(const IID&, uint32_t, const void*) override { return 0; }
    int32_t SetPrivateDataInterface(const IID&, const IUnknown*) override { return 0; }
    int32_t SetName(const wchar_t*) override { return 0; }
    int32_t GetDevice(const IID&, void** ppDevice) override {
        if (!ppDevice) return -1;
        *ppDevice = m_pDevice;
        if (m_pDevice) m_pDevice->AddRef();
        return 0;
    }

    int32_t FindValue(const void* pKey, uint32_t KeySize, void* pValue, uint32_t* pValueSize) override {
        if (!pKey || KeySize == 0 || !pValueSize) return -1;
        const auto* kptr = reinterpret_cast<const uint8_t*>(pKey);
        std::vector<uint8_t> key(kptr, kptr + KeySize);
        auto it = m_cache.find(key);
        if (it == m_cache.end()) return -2147024894; // E_FILENOTFOUND
        if (!pValue || *pValueSize < it->second.size()) {
            *pValueSize = static_cast<uint32_t>(it->second.size());
            return 1; // S_FALSE / buffer too small
        }
        std::memcpy(pValue, it->second.data(), it->second.size());
        *pValueSize = static_cast<uint32_t>(it->second.size());
        return 0;
    }

    int32_t StoreValue(const void* pKey, uint32_t KeySize, const void* pValue, uint32_t ValueSize) override {
        if (!pKey || KeySize == 0 || !pValue || ValueSize == 0) return -1;
        const auto* kptr = reinterpret_cast<const uint8_t*>(pKey);
        const auto* vptr = reinterpret_cast<const uint8_t*>(pValue);
        m_cache[std::vector<uint8_t>(kptr, kptr + KeySize)] = std::vector<uint8_t>(vptr, vptr + ValueSize);
        return 0;
    }

    void SetDeleteOnDestroy() override {}
    D3D12_SHADER_CACHE_SESSION_DESC GetDesc() override { return m_desc; }
};

// ============================================================================
// 4. Agility SDK 1.614+ Resource Creation & Extended Mip Regions
// ============================================================================

struct D3D12_MIP_REGION {
    uint32_t Width{ 0 };
    uint32_t Height{ 0 };
    uint32_t Depth{ 0 };
};

struct D3D12_RESOURCE_DESC1 {
    D3D12_RESOURCE_DIMENSION Dimension{ D3D12_RESOURCE_DIMENSION_UNKNOWN };
    uint64_t Alignment{ 0 };
    uint64_t Width{ 0 };
    uint32_t Height{ 0 };
    uint16_t DepthOrArraySize{ 0 };
    uint16_t MipLevels{ 0 };
    DXGI_FORMAT Format{ DXGI_FORMAT_UNKNOWN };
    DXGI_SAMPLE_DESC SampleDesc{};
    D3D12_TEXTURE_LAYOUT Layout{ D3D12_TEXTURE_LAYOUT_UNKNOWN };
    D3D12_RESOURCE_FLAGS Flags{ D3D12_RESOURCE_FLAG_NONE };
    D3D12_MIP_REGION SamplerFeedbackMipRegion{};
};

// ============================================================================
// 5. Direct3D 12 Render Passes (D3D12GraphicsCommandList4)
// ============================================================================

enum D3D12_RENDER_PASS_BEGINNING_ACCESS_TYPE {
    D3D12_RENDER_PASS_BEGINNING_ACCESS_TYPE_DISCARD   = 0,
    D3D12_RENDER_PASS_BEGINNING_ACCESS_TYPE_PRESERVE  = 1,
    D3D12_RENDER_PASS_BEGINNING_ACCESS_TYPE_CLEAR     = 2,
    D3D12_RENDER_PASS_BEGINNING_ACCESS_TYPE_NO_ACCESS = 3
};

struct D3D12_RENDER_PASS_BEGINNING_ACCESS_CLEAR_PARAMETERS {
    float Color[4]{ 0.0f, 0.0f, 0.0f, 0.0f };
};

struct D3D12_RENDER_PASS_BEGINNING_ACCESS {
    D3D12_RENDER_PASS_BEGINNING_ACCESS_TYPE Type{ D3D12_RENDER_PASS_BEGINNING_ACCESS_TYPE_DISCARD };
    D3D12_RENDER_PASS_BEGINNING_ACCESS_CLEAR_PARAMETERS Clear{};
};

enum D3D12_RENDER_PASS_ENDING_ACCESS_TYPE {
    D3D12_RENDER_PASS_ENDING_ACCESS_TYPE_DISCARD   = 0,
    D3D12_RENDER_PASS_ENDING_ACCESS_TYPE_PRESERVE  = 1,
    D3D12_RENDER_PASS_ENDING_ACCESS_TYPE_RESOLVE   = 2,
    D3D12_RENDER_PASS_ENDING_ACCESS_TYPE_NO_ACCESS = 3
};

struct D3D12_RENDER_PASS_ENDING_ACCESS {
    D3D12_RENDER_PASS_ENDING_ACCESS_TYPE Type{ D3D12_RENDER_PASS_ENDING_ACCESS_TYPE_PRESERVE };
};

struct D3D12_RENDER_PASS_RENDER_TARGET_DESC {
    D3D12_CPU_DESCRIPTOR_HANDLE cpuDescriptor{};
    D3D12_RENDER_PASS_BEGINNING_ACCESS BeginningAccess{};
    D3D12_RENDER_PASS_ENDING_ACCESS EndingAccess{};
};

struct D3D12_RENDER_PASS_DEPTH_STENCIL_DESC {
    D3D12_CPU_DESCRIPTOR_HANDLE cpuDescriptor{};
    D3D12_RENDER_PASS_BEGINNING_ACCESS DepthBeginningAccess{};
    D3D12_RENDER_PASS_BEGINNING_ACCESS StencilBeginningAccess{};
    D3D12_RENDER_PASS_ENDING_ACCESS DepthEndingAccess{};
    D3D12_RENDER_PASS_ENDING_ACCESS StencilEndingAccess{};
};

enum D3D12_RENDER_PASS_FLAGS : uint32_t {
    D3D12_RENDER_PASS_FLAG_NONE             = 0,
    D3D12_RENDER_PASS_FLAG_ALLOW_UAV_WRITES = 1,
    D3D12_RENDER_PASS_FLAG_SUSPENDING_PASS  = 2,
    D3D12_RENDER_PASS_FLAG_RESUMING_PASS    = 4
};

} // namespace prismx
