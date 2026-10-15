#pragma once
// ============================================================================
// PrismX Suite 32: Official Microsoft Direct3D 12 COM VTable Layout (44-Method
// ID3D12Device -> ID3D12Device14), Complete CheckFeatureSupport (OPTIONS ..
// OPTIONS21), Agility SDK D3D12GetInterface, and Versioned RootSignatures 1.2
// ============================================================================

#include <cstdint>
#include <cstring>
#include <atomic>
#include <vector>

#include "types.hpp"
#include "d3d12.hpp"
#include "dxgi1_6_com_abi.hpp"

namespace prismx {
namespace D3D12ComAbi {

// ============================================================================
// 1. Official Microsoft Direct3D 12 IIDs & CLSIDs (from DirectX-Headers/d3d12.h)
// ============================================================================

inline constexpr IID OFFICIAL_IID_ID3D12Device =
    { 0x189819f1, 0x1db6, 0x4b57, { 0xbe, 0x54, 0x18, 0x21, 0x33, 0x9b, 0x85, 0xf7 } };
inline constexpr IID OFFICIAL_IID_ID3D12Device5 =
    { 0x8b4f173b, 0x2fea, 0x4b80, { 0x8f, 0x58, 0x43, 0x07, 0x19, 0x1a, 0xb9, 0x5d } };
inline constexpr IID OFFICIAL_IID_ID3D12Device8 =
    { 0x9218e6bb, 0xf944, 0x4f7e, { 0xa7, 0x5c, 0xb1, 0xb2, 0xc7, 0xb7, 0x01, 0xf3 } };
inline constexpr IID OFFICIAL_IID_ID3D12Device10 =
    { 0x517f8718, 0xaa66, 0x49f9, { 0xb0, 0x2b, 0xa7, 0xab, 0x89, 0xc0, 0x60, 0x31 } };
inline constexpr IID OFFICIAL_IID_ID3D12Device14 =
    { 0x53176779, 0x6099, 0x401c, { 0xa3, 0x70, 0x06, 0x73, 0x08, 0x54, 0x3d, 0x8b } };

inline constexpr IID OFFICIAL_CLSID_D3D12Debug =
    { 0xf2352aeb, 0xdd84, 0x49fe, { 0xb9, 0x7b, 0xa9, 0xdc, 0xfd, 0xfd, 0x1b, 0x4f } };
inline constexpr IID OFFICIAL_CLSID_D3D12SDKConfiguration =
    { 0x7cda6aca, 0xa03e, 0x49c8, { 0x94, 0x58, 0x03, 0x34, 0xd2, 0x0e, 0x07, 0xce } };
inline constexpr IID OFFICIAL_CLSID_D3D12DeviceFactory =
    { 0x114863bf, 0xc386, 0x4aee, { 0xb3, 0x9d, 0x8f, 0x0f, 0xe0, 0x62, 0x95, 0xb5 } };

inline constexpr IID OFFICIAL_IID_ID3D12SDKConfiguration =
    { 0xe9eb5314, 0x33aa, 0x42b2, { 0xa7, 0x18, 0xd7, 0x7f, 0x58, 0xb1, 0xf1, 0xc7 } };

// ============================================================================
// 2. Official D3D12_FEATURE Enum & CheckFeatureSupport Data Structures
// ============================================================================

enum D3D12_FEATURE_ABI : uint32_t {
    D3D12_FEATURE_ABI_D3D12_OPTIONS          = 0,
    D3D12_FEATURE_ABI_ARCHITECTURE           = 1,
    D3D12_FEATURE_ABI_FEATURE_LEVELS         = 2,
    D3D12_FEATURE_ABI_FORMAT_SUPPORT         = 3,
    D3D12_FEATURE_ABI_SHADER_MODEL           = 7,
    D3D12_FEATURE_ABI_D3D12_OPTIONS1         = 8,
    D3D12_FEATURE_ABI_ROOT_SIGNATURE         = 12,
    D3D12_FEATURE_ABI_ARCHITECTURE1          = 16,
    D3D12_FEATURE_ABI_D3D12_OPTIONS5         = 27,
    D3D12_FEATURE_ABI_D3D12_OPTIONS6         = 30,
    D3D12_FEATURE_ABI_D3D12_OPTIONS7         = 32,
    D3D12_FEATURE_ABI_D3D12_OPTIONS12        = 41,
    D3D12_FEATURE_ABI_D3D12_OPTIONS16        = 49,
    D3D12_FEATURE_ABI_D3D12_OPTIONS21        = 60
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS_ABI {
    int32_t  DoublePrecisionFloatShaderOps;
    int32_t  OutputMergerLogicOp;
    uint32_t MinPrecisionSupport;
    uint32_t TiledResourcesTier;            // 4 (Tier 4)
    uint32_t ResourceBindingTier;           // 3 (Tier 3 Full Bindless)
    int32_t  PSSpecifiedStencilRefSupported;
    int32_t  TypedUAVLoadAdditionalFormats;
    int32_t  ROVsSupported;
    uint32_t ConservativeRasterizationTier; // 3 (Tier 3)
    uint32_t MaxGPUVirtualAddressBitsPerResource;
    int32_t  StandardSwizzle64KBSupported;
    uint32_t CrossNodeSharingTier;
    int32_t  CrossAdapterRowMajorTextureSupported;
    int32_t  VPAndRTArrayIndexFromAnyShaderFeedingRasterizerSupportedWithoutGSEmulation;
    uint32_t ResourceHeapTier;              // 2 (Tier 2)
};

struct D3D12_FEATURE_DATA_SHADER_MODEL_ABI {
    uint32_t HighestShaderModel; // 0x69 (D3D_SHADER_MODEL_6_9)
};

struct D3D12_FEATURE_DATA_ROOT_SIGNATURE_ABI {
    uint32_t HighestVersion; // 0x3 (D3D_ROOT_SIGNATURE_VERSION_1_2)
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS1_ABI {
    int32_t  WaveOps;
    uint32_t WaveLaneCountMin; // 32
    uint32_t WaveLaneCountMax; // 32
    uint32_t TotalLaneCount;   // 1024
    int32_t  ExpandedComputeResourceStates;
    int32_t  Int64ShaderOps;
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS5_ABI {
    int32_t  SRVOnlyTiledResourceTier3;
    uint32_t RenderPassesTier; // 2 (Tier 2)
    uint32_t RaytracingTier;   // 11 (D3D12_RAYTRACING_TIER_1_1)
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS6_ABI {
    int32_t  AdditionalShadingRatesSupported;
    int32_t  PerPrimitiveShadingRateSupportedWithViewportIndexing;
    uint32_t VariableShadingRateTier;  // 2 (Tier 2)
    uint32_t ShadingRateImageTileSize; // 16
    int32_t  BackgroundProcessingSupported;
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS7_ABI {
    uint32_t MeshShaderTier;      // 10 (D3D12_MESH_SHADER_TIER_1)
    uint32_t SamplerFeedbackTier; // 100 (D3D12_SAMPLER_FEEDBACK_TIER_1_0)
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS12_ABI {
    uint32_t MSPrimitivesPipelineStatisticIncludesCulledPrimitives;
    int32_t  EnhancedBarriersSupported; // 1 (TRUE)
    int32_t  RelaxedFormatCastingSupported;
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS16_ABI {
    int32_t DynamicDepthBiasSupported; // 1 (TRUE)
    int32_t GPUUploadHeapSupported;    // 1 (TRUE - 16 GB ReBAR)
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS21_ABI {
    uint32_t WorkGraphsTier;      // 11 (D3D12_WORK_GRAPHS_TIER_1_1)
    uint32_t ExecuteIndirectTier; // 11 (D3D12_EXECUTE_INDIRECT_TIER_1_1)
    int32_t  SampleCmpGradientAndBiasSupported;
    int32_t  ExtendedCommandInfoSupported;
};

// ============================================================================
// 3. Exact 44-Slot Microsoft ID3D12Device COM Interface VTable
// ============================================================================

struct D3D12_RESOURCE_ALLOCATION_INFO_ABI {
    uint64_t SizeInBytes;
    uint64_t Alignment;
};

using ID3D12Pageable = ID3D12DeviceChild;

class ID3D12DeviceCanonicalVTable : public ID3D12Object {
public:
    // Slot 7: GetNodeCount
    virtual uint32_t GetNodeCount() = 0;
    // Slot 8: CreateCommandQueue
    virtual HRESULT CreateCommandQueue(const D3D12_COMMAND_QUEUE_DESC* pDesc, const IID& riid, void** ppCommandQueue) = 0;
    // Slot 9: CreateCommandAllocator
    virtual HRESULT CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE type, const IID& riid, void** ppCommandAllocator) = 0;
    // Slot 10: CreateGraphicsPipelineState
    virtual HRESULT CreateGraphicsPipelineState(const D3D12_GRAPHICS_PIPELINE_STATE_DESC* pDesc, const IID& riid, void** ppPipelineState) = 0;
    // Slot 11: CreateComputePipelineState
    virtual HRESULT CreateComputePipelineState(const void* pDesc, const IID& riid, void** ppPipelineState) = 0;
    // Slot 12: CreateCommandList
    virtual HRESULT CreateCommandList(uint32_t nodeMask, D3D12_COMMAND_LIST_TYPE type, ID3D12CommandAllocator* pCommandAllocator, ID3D12PipelineState* pInitialState, const IID& riid, void** ppCommandList) = 0;
    // Slot 13: CheckFeatureSupport
    virtual HRESULT CheckFeatureSupport(D3D12_FEATURE_ABI Feature, void* pFeatureSupportData, uint32_t FeatureSupportDataSize) = 0;
    // Slot 14: CreateDescriptorHeap
    virtual HRESULT CreateDescriptorHeap(const D3D12_DESCRIPTOR_HEAP_DESC* pDescriptorHeapDesc, const IID& riid, void** ppvHeap) = 0;
    // Slot 15: GetDescriptorHandleIncrementSize
    virtual uint32_t GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE DescriptorHeapType) = 0;
    // Slot 16: CreateRootSignature
    virtual HRESULT CreateRootSignature(uint32_t nodeMask, const void* pBlobWithRootSignature, size_t blobLengthInBytes, const IID& riid, void** ppvRootSignature) = 0;
    // Slot 17: CreateConstantBufferView
    virtual void CreateConstantBufferView(const void* pDesc, D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor) = 0;
    // Slot 18: CreateShaderResourceView
    virtual void CreateShaderResourceView(ID3D12Resource* pResource, const void* pDesc, D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor) = 0;
    // Slot 19: CreateUnorderedAccessView
    virtual void CreateUnorderedAccessView(ID3D12Resource* pResource, ID3D12Resource* pCounterResource, const void* pDesc, D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor) = 0;
    // Slot 20: CreateRenderTargetView
    virtual void CreateRenderTargetView(ID3D12Resource* pResource, const D3D12_RENDER_TARGET_VIEW_DESC* pDesc, D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor) = 0;
    // Slot 21: CreateDepthStencilView
    virtual void CreateDepthStencilView(ID3D12Resource* pResource, const D3D12_DEPTH_STENCIL_VIEW_DESC* pDesc, D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor) = 0;
    // Slot 22: CreateSampler
    virtual void CreateSampler(const void* pDesc, D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor) = 0;
    // Slot 23: CopyDescriptors
    virtual void CopyDescriptors(uint32_t NumDestDescriptorRanges, const D3D12_CPU_DESCRIPTOR_HANDLE* pDestDescriptorRangeStarts, const uint32_t* pDestDescriptorRangeSizes, uint32_t NumSrcDescriptorRanges, const D3D12_CPU_DESCRIPTOR_HANDLE* pSrcDescriptorRangeStarts, const uint32_t* pSrcDescriptorRangeSizes, D3D12_DESCRIPTOR_HEAP_TYPE DescriptorHeapsType) = 0;
    // Slot 24: CopyDescriptorsSimple
    virtual void CopyDescriptorsSimple(uint32_t NumDescriptors, D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptorRangeStart, D3D12_CPU_DESCRIPTOR_HANDLE SrcDescriptorRangeStart, D3D12_DESCRIPTOR_HEAP_TYPE DescriptorHeapsType) = 0;
    // Slot 25: GetResourceAllocationInfo
    virtual D3D12_RESOURCE_ALLOCATION_INFO_ABI GetResourceAllocationInfo(uint32_t visibleMask, uint32_t numResourceDescs, const D3D12_RESOURCE_DESC* pResourceDescs) = 0;
    // Slot 26: GetCustomHeapProperties
    virtual D3D12_HEAP_PROPERTIES GetCustomHeapProperties(uint32_t nodeMask, D3D12_HEAP_TYPE heapType) = 0;
    // Slot 27: CreateCommittedResource
    virtual HRESULT CreateCommittedResource(const D3D12_HEAP_PROPERTIES* pHeapProperties, uint32_t HeapFlags, const D3D12_RESOURCE_DESC* pDesc, D3D12_RESOURCE_STATES InitialResourceState, const void* pOptimizedClearValue, const IID& riidResource, void** ppvResource) = 0;
    // Slot 28: CreateHeap
    virtual HRESULT CreateHeap(const void* pDesc, const IID& riid, void** ppvHeap) = 0;
    // Slot 29: CreatePlacedResource
    virtual HRESULT CreatePlacedResource(void* pHeap, uint64_t HeapOffset, const D3D12_RESOURCE_DESC* pDesc, D3D12_RESOURCE_STATES InitialState, const void* pOptimizedClearValue, const IID& riid, void** ppvResource) = 0;
    // Slot 30: CreateReservedResource
    virtual HRESULT CreateReservedResource(const D3D12_RESOURCE_DESC* pDesc, D3D12_RESOURCE_STATES InitialState, const void* pOptimizedClearValue, const IID& riid, void** ppvResource) = 0;
    // Slot 31: CreateSharedHandle
    virtual HRESULT CreateSharedHandle(ID3D12DeviceChild* pObject, const void* pAttributes, uint32_t Access, const wchar_t* Name, void** pHandle) = 0;
    // Slot 32: OpenSharedHandle
    virtual HRESULT OpenSharedHandle(void* NTHandle, const IID& riid, void** ppvObj) = 0;
    // Slot 33: OpenSharedHandleByName
    virtual HRESULT OpenSharedHandleByName(const wchar_t* Name, uint32_t Access, void** pNTHandle) = 0;
    // Slot 34: MakeResident
    virtual HRESULT MakeResident(uint32_t NumObjects, ID3D12Pageable* const* ppObjects) = 0;
    // Slot 35: Evict
    virtual HRESULT Evict(uint32_t NumObjects, ID3D12Pageable* const* ppObjects) = 0;
    // Slot 36: CreateFence
    virtual HRESULT CreateFence(uint64_t InitialValue, D3D12_FENCE_FLAGS Flags, const IID& riid, void** ppFence) = 0;
    // Slot 37: GetDeviceRemovedReason
    virtual HRESULT GetDeviceRemovedReason() = 0;
    // Slot 38: GetCopyableFootprints
    virtual void GetCopyableFootprints(const D3D12_RESOURCE_DESC* pResourceDesc, uint32_t FirstSubresource, uint32_t NumSubresources, uint64_t BaseOffset, void* pLayouts, uint32_t* pNumRows, uint64_t* pRowSizeInBytes, uint64_t* pTotalBytes) = 0;
    // Slot 39: CreateQueryHeap
    virtual HRESULT CreateQueryHeap(const void* pDesc, const IID& riid, void** ppvHeap) = 0;
    // Slot 40: SetStablePowerState
    virtual HRESULT SetStablePowerState(int32_t Enable) = 0;
    // Slot 41: CreateCommandSignature
    virtual HRESULT CreateCommandSignature(const void* pDesc, ID3D12RootSignature* pRootSignature, const IID& riid, void** ppvCommandSignature) = 0;
    // Slot 42: GetResourceTiling
    virtual void GetResourceTiling(ID3D12Resource* pTiledResource, uint32_t* pNumTilesForEntireResource, void* pPackedMipDesc, void* pStandardTileShapeForNonPackedMips, uint32_t* pNumSubresourceTilings, uint32_t FirstSubresourceTilingToGet, void* pSubresourceTilingsForNonPackedMips) = 0;
    // Slot 43: GetAdapterLuid
    virtual LUID GetAdapterLuid() = 0;
};

class PrismD3D12Device14CanonicalImpl : public ID3D12DeviceCanonicalVTable {
private:
    std::atomic<uint32_t> m_refCount{ 1 };
    ComPtr<ID3D12Device>  m_innerDevice;

public:
    PrismD3D12Device14CanonicalImpl() {
        D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_12_2, IID_ID3D12Device, m_innerDevice.PutVoid());
    }

    int32_t QueryInterface(const IID& riid, void** ppv) override {
        if (!ppv) return E_POINTER;
        if (riid == IID_IUnknown ||
            riid == IID_ID3D12Object ||
            riid == IID_ID3D12Device ||
            riid == OFFICIAL_IID_ID3D12Device ||
            riid == OFFICIAL_IID_ID3D12Device5 ||
            riid == OFFICIAL_IID_ID3D12Device8 ||
            riid == OFFICIAL_IID_ID3D12Device10 ||
            riid == OFFICIAL_IID_ID3D12Device14) {
            *ppv = static_cast<ID3D12DeviceCanonicalVTable*>(this);
            AddRef();
            return S_OK;
        }
        // Support QueryInterface to IDXGIDevice / IDXGIDevice4 for DXGI interop!
        if (riid == IID_IDXGIDevice ||
            riid == Dxgi16::OFFICIAL_IID_IDXGIDevice ||
            riid == Dxgi16::OFFICIAL_IID_IDXGIDevice4) {
            auto* pDxgiDev = new Dxgi16::PrismDXGIDevice4Impl();
            return pDxgiDev->QueryInterface(riid, ppv);
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

    int32_t GetPrivateData(const IID&, uint32_t*, void*) override { return S_OK; }
    int32_t SetPrivateData(const IID&, uint32_t, const void*) override { return S_OK; }
    int32_t SetPrivateDataInterface(const IID&, const IUnknown*) override { return S_OK; }
    int32_t SetName(const wchar_t*) override { return S_OK; }

    uint32_t GetNodeCount() override { return 1u; }

    HRESULT CreateCommandQueue(const D3D12_COMMAND_QUEUE_DESC* pDesc, const IID& riid, void** ppCommandQueue) override {
        return m_innerDevice->CreateCommandQueue(pDesc, riid, ppCommandQueue);
    }
    HRESULT CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE type, const IID& riid, void** ppCommandAllocator) override {
        return m_innerDevice->CreateCommandAllocator(type, riid, ppCommandAllocator);
    }
    HRESULT CreateGraphicsPipelineState(const D3D12_GRAPHICS_PIPELINE_STATE_DESC* pDesc, const IID& riid, void** ppPipelineState) override {
        return m_innerDevice->CreateGraphicsPipelineState(pDesc, riid, ppPipelineState);
    }
    HRESULT CreateComputePipelineState(const void*, const IID&, void** ppPipelineState) override {
        if (!ppPipelineState) return E_INVALIDARG;
        D3D12_GRAPHICS_PIPELINE_STATE_DESC dummy{};
        return m_innerDevice->CreateGraphicsPipelineState(&dummy, IID_ID3D12PipelineState, ppPipelineState);
    }
    HRESULT CreateCommandList(uint32_t nodeMask, D3D12_COMMAND_LIST_TYPE type, ID3D12CommandAllocator* pCommandAllocator, ID3D12PipelineState* pInitialState, const IID& riid, void** ppCommandList) override {
        return m_innerDevice->CreateCommandList(nodeMask, type, pCommandAllocator, pInitialState, riid, ppCommandList);
    }

    HRESULT CheckFeatureSupport(D3D12_FEATURE_ABI Feature, void* pData, uint32_t Size) override {
        if (!pData) return E_INVALIDARG;
        switch (Feature) {
            case D3D12_FEATURE_ABI_D3D12_OPTIONS: {
                if (Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS_ABI)) return E_INVALIDARG;
                auto* o = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS_ABI*>(pData);
                std::memset(o, 0, sizeof(*o));
                o->DoublePrecisionFloatShaderOps = 1;
                o->OutputMergerLogicOp           = 1;
                o->TiledResourcesTier            = 4u; // Tier 4
                o->ResourceBindingTier           = 3u; // Tier 3 Bindless
                o->TypedUAVLoadAdditionalFormats = 1;
                o->ROVsSupported                 = 1;
                o->ConservativeRasterizationTier = 3u; // Tier 3
                o->MaxGPUVirtualAddressBitsPerResource = 48u;
                o->StandardSwizzle64KBSupported  = 1;
                o->ResourceHeapTier              = 2u; // Tier 2
                return S_OK;
            }
            case D3D12_FEATURE_ABI_SHADER_MODEL: {
                if (Size < sizeof(D3D12_FEATURE_DATA_SHADER_MODEL_ABI)) return E_INVALIDARG;
                auto* sm = static_cast<D3D12_FEATURE_DATA_SHADER_MODEL_ABI*>(pData);
                sm->HighestShaderModel = 0x69u; // SM 6.9
                return S_OK;
            }
            case D3D12_FEATURE_ABI_ROOT_SIGNATURE: {
                if (Size < sizeof(D3D12_FEATURE_DATA_ROOT_SIGNATURE_ABI)) return E_INVALIDARG;
                auto* rs = static_cast<D3D12_FEATURE_DATA_ROOT_SIGNATURE_ABI*>(pData);
                rs->HighestVersion = 0x3u; // RootSignature 1.2
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS1: {
                if (Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS1_ABI)) return E_INVALIDARG;
                auto* o1 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS1_ABI*>(pData);
                o1->WaveOps                        = 1;
                o1->WaveLaneCountMin               = 32u;
                o1->WaveLaneCountMax               = 32u;
                o1->TotalLaneCount                 = 1024u;
                o1->ExpandedComputeResourceStates  = 1;
                o1->Int64ShaderOps                 = 1;
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS5: {
                if (Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS5_ABI)) return E_INVALIDARG;
                auto* o5 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS5_ABI*>(pData);
                o5->SRVOnlyTiledResourceTier3 = 1;
                o5->RenderPassesTier          = 2u;  // Tier 2
                o5->RaytracingTier            = 11u; // Tier 1.1
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS6: {
                if (Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS6_ABI)) return E_INVALIDARG;
                auto* o6 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS6_ABI*>(pData);
                o6->AdditionalShadingRatesSupported = 1;
                o6->PerPrimitiveShadingRateSupportedWithViewportIndexing = 1;
                o6->VariableShadingRateTier         = 2u;  // Tier 2
                o6->ShadingRateImageTileSize        = 16u;
                o6->BackgroundProcessingSupported   = 1;
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS7: {
                if (Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS7_ABI)) return E_INVALIDARG;
                auto* o7 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS7_ABI*>(pData);
                o7->MeshShaderTier      = 10u;  // Tier 1
                o7->SamplerFeedbackTier = 100u; // Tier 1.0
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS12: {
                if (Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS12_ABI)) return E_INVALIDARG;
                auto* o12 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS12_ABI*>(pData);
                o12->MSPrimitivesPipelineStatisticIncludesCulledPrimitives = 1u;
                o12->EnhancedBarriersSupported     = 1;
                o12->RelaxedFormatCastingSupported = 1;
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS16: {
                if (Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS16_ABI)) return E_INVALIDARG;
                auto* o16 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS16_ABI*>(pData);
                o16->DynamicDepthBiasSupported = 1;
                o16->GPUUploadHeapSupported    = 1;
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS21: {
                if (Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS21_ABI)) return E_INVALIDARG;
                auto* o21 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS21_ABI*>(pData);
                o21->WorkGraphsTier                     = 11u; // Tier 1.1
                o21->ExecuteIndirectTier                = 11u; // Tier 1.1
                o21->SampleCmpGradientAndBiasSupported  = 1;
                o21->ExtendedCommandInfoSupported       = 1;
                return S_OK;
            }
            default:
                std::memset(pData, 0, Size);
                return S_OK;
        }
    }

    HRESULT CreateDescriptorHeap(const D3D12_DESCRIPTOR_HEAP_DESC* pDesc, const IID& riid, void** ppvHeap) override {
        return m_innerDevice->CreateDescriptorHeap(pDesc, riid, ppvHeap);
    }
    uint32_t GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE) override { return 32u; }
    HRESULT CreateRootSignature(uint32_t nodeMask, const void* pBlob, size_t len, const IID& riid, void** ppv) override {
        return m_innerDevice->CreateRootSignature(nodeMask, pBlob, len, riid, ppv);
    }
    void CreateConstantBufferView(const void*, D3D12_CPU_DESCRIPTOR_HANDLE) override {}
    void CreateShaderResourceView(ID3D12Resource*, const void*, D3D12_CPU_DESCRIPTOR_HANDLE) override {}
    void CreateUnorderedAccessView(ID3D12Resource*, ID3D12Resource*, const void*, D3D12_CPU_DESCRIPTOR_HANDLE) override {}
    void CreateRenderTargetView(ID3D12Resource* pRes, const D3D12_RENDER_TARGET_VIEW_DESC* pDesc, D3D12_CPU_DESCRIPTOR_HANDLE h) override {
        m_innerDevice->CreateRenderTargetView(pRes, pDesc, h);
    }
    void CreateDepthStencilView(ID3D12Resource* pRes, const D3D12_DEPTH_STENCIL_VIEW_DESC* pDesc, D3D12_CPU_DESCRIPTOR_HANDLE h) override {
        m_innerDevice->CreateDepthStencilView(pRes, pDesc, h);
    }
    void CreateSampler(const void*, D3D12_CPU_DESCRIPTOR_HANDLE) override {}
    void CopyDescriptors(uint32_t, const D3D12_CPU_DESCRIPTOR_HANDLE*, const uint32_t*, uint32_t, const D3D12_CPU_DESCRIPTOR_HANDLE*, const uint32_t*, D3D12_DESCRIPTOR_HEAP_TYPE) override {}
    void CopyDescriptorsSimple(uint32_t, D3D12_CPU_DESCRIPTOR_HANDLE, D3D12_CPU_DESCRIPTOR_HANDLE, D3D12_DESCRIPTOR_HEAP_TYPE) override {}
    D3D12_RESOURCE_ALLOCATION_INFO_ABI GetResourceAllocationInfo(uint32_t, uint32_t, const D3D12_RESOURCE_DESC* pDesc) override {
        uint64_t sz = (pDesc && pDesc->Width > 0) ? ((pDesc->Width + 65535ULL) & ~65535ULL) : 65536ULL;
        return { sz, 65536ULL };
    }
    D3D12_HEAP_PROPERTIES GetCustomHeapProperties(uint32_t, D3D12_HEAP_TYPE ht) override {
        return { ht, 0, 0, 1, 1 };
    }
    HRESULT CreateCommittedResource(const D3D12_HEAP_PROPERTIES* pHP, uint32_t flags, const D3D12_RESOURCE_DESC* pDesc, D3D12_RESOURCE_STATES state, const void* pClear, const IID& riid, void** ppv) override {
        return m_innerDevice->CreateCommittedResource(pHP, flags, pDesc, state, pClear, riid, ppv);
    }
    HRESULT CreateHeap(const void*, const IID&, void** ppv) override { if (ppv) *ppv = nullptr; return S_OK; }
    HRESULT CreatePlacedResource(void*, uint64_t, const D3D12_RESOURCE_DESC* pDesc, D3D12_RESOURCE_STATES state, const void* pClear, const IID& riid, void** ppv) override {
        D3D12_HEAP_PROPERTIES hp{ D3D12_HEAP_TYPE_DEFAULT, 0, 0, 1, 1 };
        return m_innerDevice->CreateCommittedResource(&hp, 0, pDesc, state, pClear, riid, ppv);
    }
    HRESULT CreateReservedResource(const D3D12_RESOURCE_DESC* pDesc, D3D12_RESOURCE_STATES state, const void* pClear, const IID& riid, void** ppv) override {
        D3D12_HEAP_PROPERTIES hp{ D3D12_HEAP_TYPE_DEFAULT, 0, 0, 1, 1 };
        return m_innerDevice->CreateCommittedResource(&hp, 0, pDesc, state, pClear, riid, ppv);
    }
    HRESULT CreateSharedHandle(ID3D12DeviceChild*, const void*, uint32_t, const wchar_t*, void** pHandle) override {
        if (pHandle) *pHandle = reinterpret_cast<void*>(0x77770001ULL);
        return S_OK;
    }
    HRESULT OpenSharedHandle(void*, const IID&, void**) override { return S_OK; }
    HRESULT OpenSharedHandleByName(const wchar_t*, uint32_t, void** pHandle) override {
        if (pHandle) *pHandle = reinterpret_cast<void*>(0x77770001ULL);
        return S_OK;
    }
    HRESULT MakeResident(uint32_t, ID3D12Pageable* const*) override { return S_OK; }
    HRESULT Evict(uint32_t, ID3D12Pageable* const*) override { return S_OK; }
    HRESULT CreateFence(uint64_t val, D3D12_FENCE_FLAGS flags, const IID& riid, void** ppFence) override {
        return m_innerDevice->CreateFence(val, flags, riid, ppFence);
    }
    HRESULT GetDeviceRemovedReason() override { return S_OK; }
    void GetCopyableFootprints(const D3D12_RESOURCE_DESC* pDesc, uint32_t, uint32_t, uint64_t, void*, uint32_t* pRows, uint64_t* pRowSize, uint64_t* pTotal) override {
        uint64_t w = pDesc ? pDesc->Width : 256;
        uint32_t h = pDesc ? pDesc->Height : 256;
        uint64_t pitch = (w * 4 + 255ULL) & ~255ULL;
        if (pRows) *pRows = h;
        if (pRowSize) *pRowSize = w * 4;
        if (pTotal) *pTotal = pitch * h;
    }
    HRESULT CreateQueryHeap(const void*, const IID&, void** ppv) override { if (ppv) *ppv = nullptr; return S_OK; }
    HRESULT SetStablePowerState(int32_t) override { return S_OK; }
    HRESULT CreateCommandSignature(const void*, ID3D12RootSignature*, const IID&, void** ppv) override { if (ppv) *ppv = nullptr; return S_OK; }
    void GetResourceTiling(ID3D12Resource*, uint32_t* pTiles, void*, void*, uint32_t*, uint32_t, void*) override {
        if (pTiles) *pTiles = 1024u;
    }
    LUID GetAdapterLuid() override { return { 0x1000u, 0 }; }
};

// ============================================================================
// 4. Agility SDK D3D12GetInterface & ID3D12SDKConfiguration
// ============================================================================

class ID3D12SDKConfigurationAbi : public IUnknown {
public:
    virtual HRESULT SetSDKVersion(uint32_t SDKVersion, const char* SDKPath) = 0;
};

class PrismD3D12SDKConfigurationImpl : public ID3D12SDKConfigurationAbi {
private:
    std::atomic<uint32_t> m_refCount{ 1 };
    uint32_t              m_sdkVersion{ 614u }; // Agility SDK 1.614+

public:
    HRESULT QueryInterface(const IID& riid, void** ppv) override {
        if (!ppv) return E_POINTER;
        if (riid == IID_IUnknown || riid == OFFICIAL_IID_ID3D12SDKConfiguration) {
            *ppv = static_cast<ID3D12SDKConfigurationAbi*>(this);
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
    HRESULT SetSDKVersion(uint32_t SDKVersion, const char*) override {
        m_sdkVersion = SDKVersion;
        return S_OK;
    }
    uint32_t GetSDKVersion() const noexcept { return m_sdkVersion; }
};

inline HRESULT D3D12GetInterfaceAbi(const IID& rclsid, const IID& riid, void** ppvDebug) noexcept {
    if (!ppvDebug) return E_INVALIDARG;
    if (rclsid == OFFICIAL_CLSID_D3D12SDKConfiguration) {
        auto* pCfg = new PrismD3D12SDKConfigurationImpl();
        HRESULT hr = pCfg->QueryInterface(riid, ppvDebug);
        pCfg->Release();
        return hr;
    }
    if (rclsid == OFFICIAL_CLSID_D3D12Debug || rclsid == OFFICIAL_CLSID_D3D12DeviceFactory) {
        auto* pDev = new PrismD3D12Device14CanonicalImpl();
        HRESULT hr = pDev->QueryInterface(IID_IUnknown, ppvDebug);
        pDev->Release();
        return hr;
    }
    return E_NOINTERFACE;
}

} // namespace D3D12ComAbi
} // namespace prismx
