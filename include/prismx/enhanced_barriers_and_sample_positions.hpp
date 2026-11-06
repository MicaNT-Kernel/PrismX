// ============================================================================
// PrismX: Direct3D 12 Enhanced Barriers (ID3D12GraphicsCommandList7),
//         Sample Positions (ID3D12GraphicsCommandList1), and Options 12/13/14
//
// Clean-Room Implementation in ISO C++23.
// Tribute to Dave Cutler's 1988 DEC PRISM Architecture.
// ============================================================================

#pragma once

#include "types.hpp"
#include "d3d12.hpp"
#include "d3d12_com_vtable_options21.hpp"
#include "d3d12raytracing.hpp"
#include "agility_dred_vulkanon12_video.hpp"
#include <vector>
#include <cstring>
#include <atomic>

namespace prismx {

// ============================================================================
// 1. Official Microsoft Direct3D 12 Command List IIDs (Agility SDK 1.606+ / 1.614+)
// ============================================================================

inline constexpr IID OFFICIAL_IID_ID3D12GraphicsCommandList1 =
    { 0x553103fb, 0x1e74, 0x4511, { 0xb0, 0xad, 0x73, 0x82, 0xc9, 0xf1, 0x57, 0xd6 } };

inline constexpr IID OFFICIAL_IID_ID3D12GraphicsCommandList2 =
    { 0x383ee830, 0x6768, 0x4d56, { 0x96, 0x37, 0x7a, 0xb1, 0x25, 0xf7, 0x70, 0x57 } };

inline constexpr IID OFFICIAL_IID_ID3D12GraphicsCommandList7 =
    { 0x37a1f50b, 0x4861, 0x41dd, { 0x93, 0x3e, 0xf1, 0x4d, 0x86, 0xbf, 0xa2, 0x54 } };

// Canonical Direct3D 12 Agility SDK IID: dd171223-8b61-4769-90e3-160cfb902180
inline constexpr IID OFFICIAL_IID_ID3D12GraphicsCommandList7_Agility =
    { 0xdd171223, 0x8b61, 0x4769, { 0x90, 0xe3, 0x16, 0x0c, 0xfb, 0x90, 0x21, 0x80 } };

inline constexpr IID IID_ID3D12GraphicsCommandList7 =
    { 0xdd171223, 0x8b61, 0x4769, { 0x90, 0xe3, 0x16, 0x0c, 0xfb, 0x90, 0x21, 0x80 } };

// ============================================================================
// 2. D3D12 Sample Position & ID3D12GraphicsCommandList1
// ============================================================================

struct D3D12_SAMPLE_POSITION {
    int8_t X;
    int8_t Y;
};

class ID3D12GraphicsCommandList1 : public ID3D12GraphicsCommandList {
public:
    virtual void SetSamplePositions(uint32_t NumSamplesPerPixel, uint32_t NumPixels, const D3D12_SAMPLE_POSITION* pSamplePositions) = 0;
    virtual void ResolveSubresourceRegion(ID3D12Resource* pDstResource, uint32_t DstSubresource, uint32_t DstX, uint32_t DstY,
                                          ID3D12Resource* pSrcResource, uint32_t SrcSubresource, const D3D12_RECT* pSrcRect,
                                          DXGI_FORMAT Format, uint32_t ResolveMode) = 0;
    virtual void SetViewInstanceMask(uint32_t Mask) = 0;
};

// ============================================================================
// 3. D3D12 WriteBufferImmediate & ID3D12GraphicsCommandList2
// ============================================================================

using D3D12_GPU_VIRTUAL_ADDRESS = uint64_t;

enum D3D12_WRITEBUFFERIMMEDIATE_MODE : uint32_t {
    D3D12_WRITEBUFFERIMMEDIATE_MODE_DEFAULT    = 0,
    D3D12_WRITEBUFFERIMMEDIATE_MODE_MARKER_IN  = 1,
    D3D12_WRITEBUFFERIMMEDIATE_MODE_MARKER_OUT = 2
};

struct D3D12_WRITEBUFFERIMMEDIATE_PARAMETER {
    D3D12_GPU_VIRTUAL_ADDRESS Dest;
    uint32_t                  Value;
};

class ID3D12GraphicsCommandList2 : public ID3D12GraphicsCommandList1 {
public:
    virtual void WriteBufferImmediate(
        uint32_t Count,
        const D3D12_WRITEBUFFERIMMEDIATE_PARAMETER* pParams,
        const D3D12_WRITEBUFFERIMMEDIATE_MODE* pModes) = 0;
};

// ============================================================================
// 4. ID3D12GraphicsCommandList3 (Protected Resource Session)
// ============================================================================

// {6bee3950-4446-44a2-8bc4-03d0aa1f0427}
inline constexpr IID OFFICIAL_IID_ID3D12GraphicsCommandList3 = {
    0x6bee3950, 0x4446, 0x44a2, { 0x8b, 0xc4, 0x03, 0xd0, 0xaa, 0x1f, 0x04, 0x27 }
};

// {70470636-2f0f-48d2-8926-2bb16839352e}
inline constexpr IID OFFICIAL_IID_ID3D12ProtectedResourceSession = {
    0x70470636, 0x2f0f, 0x48d2, { 0x89, 0x26, 0x2b, 0xb1, 0x68, 0x39, 0x35, 0x2e }
};

class ID3D12ProtectedSession : public ID3D12DeviceChild {
public:
    virtual int32_t GetSessionStatus() = 0;
};

class ID3D12ProtectedResourceSession : public ID3D12ProtectedSession {
public:
    virtual void GetDesc(void* pDesc) = 0;
};

class ID3D12GraphicsCommandList3 : public ID3D12GraphicsCommandList2 {
public:
    virtual void SetProtectedResourceSession(ID3D12ProtectedResourceSession* pProtectedSession) = 0;
};

// ============================================================================
// 5. ID3D12GraphicsCommandList7 (Enhanced Barriers)
// ============================================================================

class ID3D12GraphicsCommandList7 : public ID3D12GraphicsCommandList3 {
public:
    virtual void Barrier(uint32_t NumBarrierGroups, const D3D12_BARRIER_GROUP* pBarrierGroups) = 0;
};

// ============================================================================
// 6. ID3D12GraphicsCommandList8 (Front & Back Stencil Reference)
// ============================================================================

inline constexpr IID OFFICIAL_IID_ID3D12GraphicsCommandList8 =
    { 0xee936ef9, 0x599d, 0x4d28, { 0x93, 0x8e, 0x23, 0xc4, 0xad, 0x05, 0xce, 0x51 } };
inline constexpr IID IID_ID3D12GraphicsCommandList8 = OFFICIAL_IID_ID3D12GraphicsCommandList8;

class ID3D12GraphicsCommandList8 : public ID3D12GraphicsCommandList7 {
public:
    virtual void OMSetFrontAndBackStencilRef(uint32_t FrontStencilRef, uint32_t BackStencilRef) = 0;
};

// ============================================================================
// 7. ID3D12GraphicsCommandList9 (Dynamic Depth Bias & Strip Cut)
// ============================================================================

enum D3D12_INDEX_BUFFER_STRIP_CUT_VALUE : uint32_t {
    D3D12_INDEX_BUFFER_STRIP_CUT_VALUE_DISABLED   = 0,
    D3D12_INDEX_BUFFER_STRIP_CUT_VALUE_0xFFFF     = 1,
    D3D12_INDEX_BUFFER_STRIP_CUT_VALUE_0xFFFFFFFF = 2
};

inline constexpr IID OFFICIAL_IID_ID3D12GraphicsCommandList9 =
    { 0x34ed2808, 0xffe6, 0x4c2b, { 0xb1, 0x1a, 0xca, 0xbd, 0x2b, 0x0c, 0x59, 0xe1 } };
inline constexpr IID IID_ID3D12GraphicsCommandList9 = OFFICIAL_IID_ID3D12GraphicsCommandList9;

class ID3D12GraphicsCommandList9 : public ID3D12GraphicsCommandList8 {
public:
    virtual void RSSetDepthBias(float DepthBias, float DepthBiasClamp, float SlopeScaledDepthBias) = 0;
    virtual void IASetIndexBufferStripCutValue(D3D12_INDEX_BUFFER_STRIP_CUT_VALUE IBStripCutValue) = 0;
};

// ============================================================================
// 4. Concrete Implementation: Prism3D12GraphicsCommandList7Impl
// ============================================================================

// ============================================================================
// ID3D12GraphicsCommandList10 (Work Graphs Tier 1.1 & Generic Programs)
// ============================================================================

inline constexpr IID OFFICIAL_IID_ID3D12GraphicsCommandList10 =
    { 0x217d12bc, 0x1f72, 0x4f72, { 0x87, 0x05, 0x76, 0x8a, 0x48, 0x49, 0x89, 0xb8 } };
inline constexpr IID IID_ID3D12GraphicsCommandList10 = OFFICIAL_IID_ID3D12GraphicsCommandList10;

enum D3D12_PROGRAM_TYPE : uint32_t {
    D3D12_PROGRAM_TYPE_GENERIC_PIPELINE    = 1,
    D3D12_PROGRAM_TYPE_RAYTRACING_PIPELINE = 2,
    D3D12_PROGRAM_TYPE_WORK_GRAPH          = 3
};

struct D3D12_SET_WORK_GRAPH_DESC {
    D3D12_GPU_VIRTUAL_ADDRESS_RANGE            ProgramIdentifier{};
    uint32_t                                   Flags{ 0 };
    D3D12_GPU_VIRTUAL_ADDRESS_RANGE_AND_STRIDE BackingMemory{};
    D3D12_GPU_VIRTUAL_ADDRESS_RANGE_AND_STRIDE NodeLocalRootArgumentsTable{};
};

struct D3D12_SET_PROGRAM_DESC {
    D3D12_PROGRAM_TYPE Type{ D3D12_PROGRAM_TYPE_WORK_GRAPH };
    union {
        D3D12_SET_WORK_GRAPH_DESC WorkGraph;
    };
};

enum D3D12_DISPATCH_MODE : uint32_t {
    D3D12_DISPATCH_MODE_NODE_CPU_INPUT = 0,
    D3D12_DISPATCH_MODE_NODE_GPU_INPUT = 1
};

struct D3D12_NODE_CPU_INPUT {
    uint32_t    EntrypointIndex{ 0 };
    uint32_t    NumRecords{ 0 };
    const void* pRecords{ nullptr };
    uint64_t    RecordStrideInBytes{ 0 };
};

struct D3D12_NODE_GPU_INPUT {
    uint32_t                  EntrypointIndex{ 0 };
    uint32_t                  NumRecords{ 0 };
    D3D12_GPU_VIRTUAL_ADDRESS Records{ 0 };
    uint64_t                  RecordStrideInBytes{ 0 };
};

struct D3D12_DISPATCH_GRAPH_DESC {
    D3D12_DISPATCH_MODE Mode{ D3D12_DISPATCH_MODE_NODE_CPU_INPUT };
    union {
        D3D12_NODE_CPU_INPUT NodeCPUInput;
        D3D12_NODE_GPU_INPUT NodeGPUInput;
    };
};

class ID3D12GraphicsCommandList10 : public ID3D12GraphicsCommandList9 {
public:
    virtual void SetProgram(const D3D12_SET_PROGRAM_DESC* pDesc) = 0;
    virtual void DispatchGraph(const D3D12_DISPATCH_GRAPH_DESC* pDesc) = 0;
};

// ============================================================================
// ID3D12GraphicsCommandList11 (Work Graphs Backing Memory & Program Records)
// ============================================================================

inline constexpr IID OFFICIAL_IID_ID3D12GraphicsCommandList11 =
    { 0x845f9da5, 0xe11a, 0x45c1, { 0x9d, 0xc5, 0xd3, 0x6c, 0x50, 0x7c, 0x39, 0x05 } };
inline constexpr IID IID_ID3D12GraphicsCommandList11 = OFFICIAL_IID_ID3D12GraphicsCommandList11;

class ID3D12GraphicsCommandList11 : public ID3D12GraphicsCommandList10 {
public:
    virtual void SetWorkGraphBackingMemory(const D3D12_GPU_VIRTUAL_ADDRESS_RANGE* pBackingMemory) = 0;
    virtual void DispatchGraphProgramRecord(uint32_t NodeIndex, const void* pRecord) = 0;
};

// ============================================================================
// ID3D12GraphicsCommandList12 (Next-Gen Work Graph Output Records & Remap)
// ============================================================================

inline constexpr IID OFFICIAL_IID_ID3D12GraphicsCommandList12 =
    { 0x9c44eb8f, 0x8ef7, 0x4c75, { 0xa0, 0x13, 0x1f, 0xb9, 0xb3, 0x90, 0xd8, 0x85 } };
inline constexpr IID IID_ID3D12GraphicsCommandList12 = OFFICIAL_IID_ID3D12GraphicsCommandList12;

class ID3D12GraphicsCommandList12 : public ID3D12GraphicsCommandList11 {
public:
    virtual void SetWorkGraphBackingMemory2(
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart,
        uint64_t RangeSizeInBytes,
        uint32_t Flags) = 0;

    virtual void DispatchGraphProgramRecord2(
        uint32_t NodeIndex,
        const void* pRecord,
        uint32_t RecordSizeInBytes) = 0;
};

// ============================================================================
// ID3D12GraphicsCommandList13 (Work Graphs 2.1 Backing Memory & Program Record Dispatch)
// ============================================================================

inline constexpr IID OFFICIAL_IID_ID3D12GraphicsCommandList13 =
    { 0x8a2c17d4, 0x73b9, 0x4d01, { 0x91, 0x4f, 0x82, 0xd4, 0xe5, 0x36, 0x2c, 0x91 } };
inline constexpr IID IID_ID3D12GraphicsCommandList13 = OFFICIAL_IID_ID3D12GraphicsCommandList13;

class ID3D12GraphicsCommandList13 : public ID3D12GraphicsCommandList12 {
public:
    virtual void SetWorkGraphBackingMemory3(
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart,
        uint64_t RangeSizeInBytes,
        uint64_t ScratchBufferSizeInBytes,
        uint32_t Flags) = 0;

    virtual void DispatchGraphProgramRecord3(
        uint32_t NodeIndex,
        const void* pRecord,
        uint32_t RecordSizeInBytes,
        uint32_t RecordCount) = 0;
};

// ============================================================================
// ID3D12GraphicsCommandList14 (Work Graphs 2.2 Concurrency & Global Root Signature Support)
// ============================================================================

inline constexpr IID OFFICIAL_IID_ID3D12GraphicsCommandList14 =
    { 0x19b4c021, 0x6a98, 0x4b6b, { 0x8f, 0x22, 0x7e, 0x88, 0x94, 0x33, 0x11, 0x40 } };
inline constexpr IID IID_ID3D12GraphicsCommandList14 = OFFICIAL_IID_ID3D12GraphicsCommandList14;

class ID3D12GraphicsCommandList14 : public ID3D12GraphicsCommandList13 {
public:
    virtual void SetWorkGraphBackingMemory4(
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart,
        uint64_t RangeSizeInBytes,
        uint64_t ScratchBufferSizeInBytes,
        uint32_t MaxConcurrency,
        uint32_t Flags) = 0;

    virtual void DispatchGraphProgramRecord4(
        uint32_t NodeIndex,
        const void* pRecord,
        uint32_t RecordSizeInBytes,
        uint32_t ConcurrencyGroup,
        uint32_t DispatchFlags) = 0;
};

// ============================================================================
// ID3D12GraphicsCommandList15 (Work Graphs 3.0 Autonomous Allocation & Dispatch Mask)
// ============================================================================

inline constexpr IID OFFICIAL_IID_ID3D12GraphicsCommandList15 =
    { 0x3f5b7218, 0x82b4, 0x4f19, { 0x93, 0x22, 0x6e, 0x11, 0x4c, 0x77, 0x90, 0x51 } };
inline constexpr IID IID_ID3D12GraphicsCommandList15 = OFFICIAL_IID_ID3D12GraphicsCommandList15;

class ID3D12GraphicsCommandList15 : public ID3D12GraphicsCommandList14 {
public:
    virtual void SetWorkGraphBackingMemory5(
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart,
        uint64_t RangeSizeInBytes,
        uint64_t ScratchBufferSizeInBytes,
        uint32_t MaxConcurrency,
        uint32_t AllocationTier,
        uint32_t Flags) = 0;

    virtual void DispatchGraphProgramRecord5(
        uint32_t NodeIndex,
        const void* pRecord,
        uint32_t RecordSizeInBytes,
        uint32_t ConcurrencyGroup,
        uint32_t DispatchMask,
        uint32_t DispatchFlags) = 0;
};

// ============================================================================
// ID3D12GraphicsCommandList16 (Work Graphs 3.1 Cooperative Matrix & Dynamic Clusters)
// ============================================================================

inline constexpr IID OFFICIAL_IID_ID3D12GraphicsCommandList16 =
    { 0x6a219e83, 0x712a, 0x4d12, { 0xba, 0x33, 0x98, 0x21, 0x55, 0x44, 0x88, 0x19 } };
inline constexpr IID IID_ID3D12GraphicsCommandList16 = OFFICIAL_IID_ID3D12GraphicsCommandList16;

class ID3D12GraphicsCommandList16 : public ID3D12GraphicsCommandList15 {
public:
    virtual void SetWorkGraphBackingMemory6(
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart,
        uint64_t RangeSizeInBytes,
        uint64_t ScratchBufferSizeInBytes,
        uint32_t MaxConcurrency,
        uint32_t AllocationTier,
        uint32_t CooperativeMatrixFlags,
        uint32_t Flags) = 0;

    virtual void DispatchGraphProgramRecord6(
        uint32_t NodeIndex,
        const void* pRecord,
        uint32_t RecordSizeInBytes,
        uint32_t ConcurrencyGroup,
        uint32_t CooperativeMatrixDim,
        uint32_t DispatchMask,
        uint32_t DispatchFlags) = 0;
};

// ============================================================================
// 4. Concrete Implementation: Prism3D12GraphicsCommandList7Impl
// ============================================================================

class Prism3D12GraphicsCommandList7Impl : public ID3D12GraphicsCommandList16 {
private:
    std::atomic<uint32_t> m_refCount{ 1 };
    ID3D12Device* m_pDevice{ nullptr };
    ID3D12CommandAllocator* m_pAllocator{ nullptr };
    D3D12_COMMAND_LIST_TYPE m_type{ D3D12_COMMAND_LIST_TYPE_DIRECT };
    bool m_isOpen{ true };

    std::vector<D3D12_SAMPLE_POSITION> m_samplePositions;
    uint32_t m_samplesPerPixel{ 0 };
    uint32_t m_viewInstanceMask{ 0 };
    ID3D12ProtectedResourceSession* m_pProtectedSession{ nullptr };

    uint32_t m_frontStencilRef{ 0 };
    uint32_t m_backStencilRef{ 0 };
    float m_depthBias{ 0.0f };
    float m_depthBiasClamp{ 0.0f };
    float m_slopeScaledDepthBias{ 0.0f };
    D3D12_INDEX_BUFFER_STRIP_CUT_VALUE m_ibStripCutValue{ D3D12_INDEX_BUFFER_STRIP_CUT_VALUE_DISABLED };

    D3D12_SET_PROGRAM_DESC m_activeProgramDesc{};
    bool m_hasActiveProgram{ false };
    std::vector<D3D12_DISPATCH_GRAPH_DESC> m_recordedDispatchGraphs;
    D3D12_GPU_VIRTUAL_ADDRESS_RANGE m_backingMemory{};
    std::vector<std::pair<uint32_t, const void*>> m_recordedProgramRecords;

    struct BackingMemory2Record {
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart{ 0 };
        uint64_t RangeSizeInBytes{ 0 };
        uint32_t Flags{ 0 };
    };
    BackingMemory2Record m_backingMemory2{};

    struct ProgramRecord2Entry {
        uint32_t NodeIndex{ 0 };
        const void* pRecord{ nullptr };
        uint32_t RecordSizeInBytes{ 0 };
    };
    std::vector<ProgramRecord2Entry> m_recordedProgramRecords2;

    struct BackingMemory3Record {
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart{ 0 };
        uint64_t RangeSizeInBytes{ 0 };
        uint64_t ScratchBufferSizeInBytes{ 0 };
        uint32_t Flags{ 0 };
    };
    BackingMemory3Record m_backingMemory3{};

    struct ProgramRecord3Entry {
        uint32_t NodeIndex{ 0 };
        const void* pRecord{ nullptr };
        uint32_t RecordSizeInBytes{ 0 };
        uint32_t RecordCount{ 0 };
    };
    std::vector<ProgramRecord3Entry> m_recordedProgramRecords3;

    struct BackingMemory4Record {
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart{ 0 };
        uint64_t RangeSizeInBytes{ 0 };
        uint64_t ScratchBufferSizeInBytes{ 0 };
        uint32_t MaxConcurrency{ 0 };
        uint32_t Flags{ 0 };
    };
    BackingMemory4Record m_backingMemory4{};

    struct ProgramRecord4Entry {
        uint32_t NodeIndex{ 0 };
        const void* pRecord{ nullptr };
        uint32_t RecordSizeInBytes{ 0 };
        uint32_t ConcurrencyGroup{ 0 };
        uint32_t DispatchFlags{ 0 };
    };
    std::vector<ProgramRecord4Entry> m_recordedProgramRecords4;

    struct BackingMemory5Record {
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart{ 0 };
        uint64_t RangeSizeInBytes{ 0 };
        uint64_t ScratchBufferSizeInBytes{ 0 };
        uint32_t MaxConcurrency{ 0 };
        uint32_t AllocationTier{ 0 };
        uint32_t Flags{ 0 };
    };
    BackingMemory5Record m_backingMemory5{};

    struct ProgramRecord5Entry {
        uint32_t NodeIndex{ 0 };
        const void* pRecord{ nullptr };
        uint32_t RecordSizeInBytes{ 0 };
        uint32_t ConcurrencyGroup{ 0 };
        uint32_t DispatchMask{ 0 };
        uint32_t DispatchFlags{ 0 };
    };
    std::vector<ProgramRecord5Entry> m_recordedProgramRecords5;

    struct BackingMemory6Record {
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart{ 0 };
        uint64_t RangeSizeInBytes{ 0 };
        uint64_t ScratchBufferSizeInBytes{ 0 };
        uint32_t MaxConcurrency{ 0 };
        uint32_t AllocationTier{ 0 };
        uint32_t CooperativeMatrixFlags{ 0 };
        uint32_t Flags{ 0 };
    };
    BackingMemory6Record m_backingMemory6{};

    struct ProgramRecord6Entry {
        uint32_t NodeIndex{ 0 };
        const void* pRecord{ nullptr };
        uint32_t RecordSizeInBytes{ 0 };
        uint32_t ConcurrencyGroup{ 0 };
        uint32_t CooperativeMatrixDim{ 0 };
        uint32_t DispatchMask{ 0 };
        uint32_t DispatchFlags{ 0 };
    };
    std::vector<ProgramRecord6Entry> m_recordedProgramRecords6;

    struct RecordedBarrierGroup {
        D3D12_BARRIER_TYPE type;
        uint32_t count;
        std::vector<D3D12_GLOBAL_BARRIER>  globals;
        std::vector<D3D12_BUFFER_BARRIER>  buffers;
        std::vector<D3D12_TEXTURE_BARRIER> textures;
    };
    std::vector<RecordedBarrierGroup> m_recordedBarriers;

public:
    struct WriteBufferImmediateRecord {
        D3D12_GPU_VIRTUAL_ADDRESS dest;
        uint32_t value;
        D3D12_WRITEBUFFERIMMEDIATE_MODE mode;
    };
private:
    std::vector<WriteBufferImmediateRecord> m_recordedWriteBufferImmediates;

public:
    Prism3D12GraphicsCommandList7Impl(ID3D12Device* pDev, D3D12_COMMAND_LIST_TYPE type, ID3D12CommandAllocator* pAlloc)
        : m_pDevice(pDev), m_pAllocator(pAlloc), m_type(type) {}

    int32_t QueryInterface(const IID& riid, void** ppv) override {
        if (!ppv) return -1;
        if (riid == IID_IUnknown || riid == IID_ID3D12Object || riid == IID_ID3D12DeviceChild ||
            riid == IID_ID3D12CommandList || riid == IID_ID3D12GraphicsCommandList ||
            riid == OFFICIAL_IID_ID3D12GraphicsCommandList1 ||
            riid == OFFICIAL_IID_ID3D12GraphicsCommandList2 ||
            riid == OFFICIAL_IID_ID3D12GraphicsCommandList3 ||
            riid == OFFICIAL_IID_ID3D12GraphicsCommandList7 ||
            riid == OFFICIAL_IID_ID3D12GraphicsCommandList7_Agility ||
            riid == IID_ID3D12GraphicsCommandList7) {
            *ppv = static_cast<ID3D12GraphicsCommandList7*>(this);
            AddRef();
            return 0;
        }
        if (riid == OFFICIAL_IID_ID3D12GraphicsCommandList8 || riid == IID_ID3D12GraphicsCommandList8) {
            *ppv = static_cast<ID3D12GraphicsCommandList8*>(this);
            AddRef();
            return 0;
        }
        if (riid == OFFICIAL_IID_ID3D12GraphicsCommandList9 || riid == IID_ID3D12GraphicsCommandList9) {
            *ppv = static_cast<ID3D12GraphicsCommandList9*>(this);
            AddRef();
            return 0;
        }
        if (riid == OFFICIAL_IID_ID3D12GraphicsCommandList10 || riid == IID_ID3D12GraphicsCommandList10) {
            *ppv = static_cast<ID3D12GraphicsCommandList10*>(this);
            AddRef();
            return 0;
        }
        if (riid == OFFICIAL_IID_ID3D12GraphicsCommandList11 || riid == IID_ID3D12GraphicsCommandList11) {
            *ppv = static_cast<ID3D12GraphicsCommandList11*>(this);
            AddRef();
            return 0;
        }
        if (riid == OFFICIAL_IID_ID3D12GraphicsCommandList12 || riid == IID_ID3D12GraphicsCommandList12) {
            *ppv = static_cast<ID3D12GraphicsCommandList12*>(this);
            AddRef();
            return 0;
        }
        if (riid == OFFICIAL_IID_ID3D12GraphicsCommandList13 || riid == IID_ID3D12GraphicsCommandList13) {
            *ppv = static_cast<ID3D12GraphicsCommandList13*>(this);
            AddRef();
            return 0;
        }
        if (riid == OFFICIAL_IID_ID3D12GraphicsCommandList14 || riid == IID_ID3D12GraphicsCommandList14) {
            *ppv = static_cast<ID3D12GraphicsCommandList14*>(this);
            AddRef();
            return 0;
        }
        if (riid == OFFICIAL_IID_ID3D12GraphicsCommandList15 || riid == IID_ID3D12GraphicsCommandList15) {
            *ppv = static_cast<ID3D12GraphicsCommandList15*>(this);
            AddRef();
            return 0;
        }
        if (riid == OFFICIAL_IID_ID3D12GraphicsCommandList16 || riid == IID_ID3D12GraphicsCommandList16) {
            *ppv = static_cast<ID3D12GraphicsCommandList16*>(this);
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

    D3D12_COMMAND_LIST_TYPE GetType() override { return m_type; }

    int32_t Close() override {
        m_isOpen = false;
        return 0;
    }

    int32_t Reset(ID3D12CommandAllocator* pAllocator, ID3D12PipelineState*) override {
        m_pAllocator = pAllocator;
        m_samplePositions.clear();
        m_samplesPerPixel = 0;
        m_viewInstanceMask = 0;
        m_recordedBarriers.clear();
        m_recordedWriteBufferImmediates.clear();
        m_pProtectedSession = nullptr;
        m_frontStencilRef = 0;
        m_backStencilRef = 0;
        m_depthBias = 0.0f;
        m_depthBiasClamp = 0.0f;
        m_slopeScaledDepthBias = 0.0f;
        m_ibStripCutValue = D3D12_INDEX_BUFFER_STRIP_CUT_VALUE_DISABLED;
        m_backingMemory = {};
        m_recordedProgramRecords.clear();
        m_backingMemory2 = {};
        m_recordedProgramRecords2.clear();
        m_backingMemory3 = {};
        m_recordedProgramRecords3.clear();
        m_backingMemory4 = {};
        m_recordedProgramRecords4.clear();
        m_backingMemory5 = {};
        m_recordedProgramRecords5.clear();
        m_backingMemory6 = {};
        m_recordedProgramRecords6.clear();
        m_isOpen = true;
        return 0;
    }

    void ClearState(ID3D12PipelineState*) override {
        m_samplePositions.clear();
        m_recordedBarriers.clear();
        m_recordedWriteBufferImmediates.clear();
        m_pProtectedSession = nullptr;
        m_backingMemory = {};
        m_recordedProgramRecords.clear();
        m_backingMemory2 = {};
        m_recordedProgramRecords2.clear();
        m_backingMemory3 = {};
        m_recordedProgramRecords3.clear();
        m_backingMemory4 = {};
        m_recordedProgramRecords4.clear();
        m_backingMemory5 = {};
        m_recordedProgramRecords5.clear();
        m_backingMemory6 = {};
        m_recordedProgramRecords6.clear();
    }

    void ResourceBarrier(uint32_t, const D3D12_RESOURCE_BARRIER*) override {}
    void RSSetViewports(uint32_t, const D3D12_VIEWPORT*) override {}
    void RSSetScissorRects(uint32_t, const D3D12_RECT*) override {}
    void OMSetRenderTargets(uint32_t, const D3D12_CPU_DESCRIPTOR_HANDLE*, int32_t, const D3D12_CPU_DESCRIPTOR_HANDLE*) override {}
    void ClearRenderTargetView(D3D12_CPU_DESCRIPTOR_HANDLE, const float[4], uint32_t, const D3D12_RECT*) override {}
    void ClearDepthStencilView(D3D12_CPU_DESCRIPTOR_HANDLE, uint32_t, float, uint8_t, uint32_t, const D3D12_RECT*) override {}
    void IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY) override {}
    void IASetVertexBuffers(uint32_t, uint32_t, const D3D12_VERTEX_BUFFER_VIEW*) override {}
    void IASetIndexBuffer(const D3D12_INDEX_BUFFER_VIEW*) override {}
    void SetGraphicsRootSignature(ID3D12RootSignature*) override {}
    void SetPipelineState(ID3D12PipelineState*) override {}
    void DrawInstanced(uint32_t, uint32_t, uint32_t, uint32_t) override {}
    void DrawIndexedInstanced(uint32_t, uint32_t, uint32_t, int32_t, uint32_t) override {}

    // ID3D12GraphicsCommandList1
    void SetSamplePositions(uint32_t NumSamplesPerPixel, uint32_t NumPixels, const D3D12_SAMPLE_POSITION* pSamplePositions) override {
        m_samplesPerPixel = NumSamplesPerPixel;
        uint32_t total = NumSamplesPerPixel * NumPixels;
        m_samplePositions.clear();
        if (pSamplePositions && total > 0) {
            m_samplePositions.assign(pSamplePositions, pSamplePositions + total);
        }
    }

    void ResolveSubresourceRegion(ID3D12Resource*, uint32_t, uint32_t, uint32_t, ID3D12Resource*, uint32_t, const D3D12_RECT*, DXGI_FORMAT, uint32_t) override {}

    void SetViewInstanceMask(uint32_t Mask) override {
        m_viewInstanceMask = Mask;
    }

    // ID3D12GraphicsCommandList2
    void WriteBufferImmediate(
        uint32_t Count,
        const D3D12_WRITEBUFFERIMMEDIATE_PARAMETER* pParams,
        const D3D12_WRITEBUFFERIMMEDIATE_MODE* pModes) override {
        if (!pParams || Count == 0) return;
        for (uint32_t i = 0; i < Count; ++i) {
            D3D12_WRITEBUFFERIMMEDIATE_MODE mode = pModes ? pModes[i] : D3D12_WRITEBUFFERIMMEDIATE_MODE_DEFAULT;
            m_recordedWriteBufferImmediates.push_back({ pParams[i].Dest, pParams[i].Value, mode });
        }
    }

    // ID3D12GraphicsCommandList3
    void SetProtectedResourceSession(ID3D12ProtectedResourceSession* pProtectedSession) override {
        m_pProtectedSession = pProtectedSession;
    }

    // ID3D12GraphicsCommandList7
    void Barrier(uint32_t NumBarrierGroups, const D3D12_BARRIER_GROUP* pBarrierGroups) override {
        if (!pBarrierGroups) return;
        for (uint32_t i = 0; i < NumBarrierGroups; ++i) {
            const auto& g = pBarrierGroups[i];
            RecordedBarrierGroup rbg;
            rbg.type = g.Type;
            rbg.count = g.NumBarriers;
            if (g.Type == D3D12_BARRIER_TYPE_GLOBAL && g.pGlobalBarriers) {
                rbg.globals.assign(g.pGlobalBarriers, g.pGlobalBarriers + g.NumBarriers);
            } else if (g.Type == D3D12_BARRIER_TYPE_BUFFER && g.pBufferBarriers) {
                rbg.buffers.assign(g.pBufferBarriers, g.pBufferBarriers + g.NumBarriers);
            } else if (g.Type == D3D12_BARRIER_TYPE_TEXTURE && g.pTextureBarriers) {
                rbg.textures.assign(g.pTextureBarriers, g.pTextureBarriers + g.NumBarriers);
            }
            m_recordedBarriers.push_back(std::move(rbg));
        }
    }

    // Inspection accessors
    const std::vector<D3D12_SAMPLE_POSITION>& GetSamplePositions() const noexcept { return m_samplePositions; }
    uint32_t GetSamplesPerPixel() const noexcept { return m_samplesPerPixel; }
    uint32_t GetViewInstanceMask() const noexcept { return m_viewInstanceMask; }
    size_t GetRecordedBarrierGroupCount() const noexcept { return m_recordedBarriers.size(); }
    const RecordedBarrierGroup& GetRecordedBarrierGroup(size_t idx) const { return m_recordedBarriers[idx]; }
    size_t GetWriteBufferImmediateCount() const noexcept { return m_recordedWriteBufferImmediates.size(); }
    const std::vector<WriteBufferImmediateRecord>& GetRecordedWriteBufferImmediates() const noexcept { return m_recordedWriteBufferImmediates; }
    ID3D12ProtectedResourceSession* GetProtectedResourceSession() const noexcept { return m_pProtectedSession; }

    // ID3D12GraphicsCommandList8
    void OMSetFrontAndBackStencilRef(uint32_t FrontStencilRef, uint32_t BackStencilRef) override {
        m_frontStencilRef = FrontStencilRef;
        m_backStencilRef = BackStencilRef;
    }

    // ID3D12GraphicsCommandList9
    void RSSetDepthBias(float DepthBias, float DepthBiasClamp, float SlopeScaledDepthBias) override {
        m_depthBias = DepthBias;
        m_depthBiasClamp = DepthBiasClamp;
        m_slopeScaledDepthBias = SlopeScaledDepthBias;
    }

    void IASetIndexBufferStripCutValue(D3D12_INDEX_BUFFER_STRIP_CUT_VALUE IBStripCutValue) override {
        m_ibStripCutValue = IBStripCutValue;
    }

    uint32_t GetFrontStencilRef() const noexcept { return m_frontStencilRef; }
    uint32_t GetBackStencilRef() const noexcept { return m_backStencilRef; }
    float GetDepthBias() const noexcept { return m_depthBias; }
    float GetDepthBiasClamp() const noexcept { return m_depthBiasClamp; }
    float GetSlopeScaledDepthBias() const noexcept { return m_slopeScaledDepthBias; }
    D3D12_INDEX_BUFFER_STRIP_CUT_VALUE GetIndexBufferStripCutValue() const noexcept { return m_ibStripCutValue; }

    // ID3D12GraphicsCommandList10
    void SetProgram(const D3D12_SET_PROGRAM_DESC* pDesc) override {
        if (pDesc) {
            m_activeProgramDesc = *pDesc;
            m_hasActiveProgram = true;
        } else {
            m_hasActiveProgram = false;
        }
    }

    void DispatchGraph(const D3D12_DISPATCH_GRAPH_DESC* pDesc) override {
        if (pDesc) {
            m_recordedDispatchGraphs.push_back(*pDesc);
        }
    }

    bool HasActiveProgram() const noexcept { return m_hasActiveProgram; }
    D3D12_PROGRAM_TYPE GetActiveProgramType() const noexcept { return m_activeProgramDesc.Type; }
    size_t GetRecordedDispatchGraphCount() const noexcept { return m_recordedDispatchGraphs.size(); }
    const std::vector<D3D12_DISPATCH_GRAPH_DESC>& GetRecordedDispatchGraphs() const noexcept { return m_recordedDispatchGraphs; }

    // ID3D12GraphicsCommandList11
    void SetWorkGraphBackingMemory(const D3D12_GPU_VIRTUAL_ADDRESS_RANGE* pBackingMemory) override {
        if (pBackingMemory) {
            m_backingMemory = *pBackingMemory;
        } else {
            m_backingMemory = {};
        }
    }

    void DispatchGraphProgramRecord(uint32_t NodeIndex, const void* pRecord) override {
        m_recordedProgramRecords.push_back({ NodeIndex, pRecord });
    }

    const D3D12_GPU_VIRTUAL_ADDRESS_RANGE& GetWorkGraphBackingMemory() const noexcept { return m_backingMemory; }
    size_t GetRecordedProgramRecordCount() const noexcept { return m_recordedProgramRecords.size(); }
    const std::vector<std::pair<uint32_t, const void*>>& GetRecordedProgramRecords() const noexcept { return m_recordedProgramRecords; }

    // ID3D12GraphicsCommandList12
    void SetWorkGraphBackingMemory2(D3D12_GPU_VIRTUAL_ADDRESS RangeStart, uint64_t RangeSizeInBytes, uint32_t Flags) override {
        m_backingMemory2 = { RangeStart, RangeSizeInBytes, Flags };
    }

    void DispatchGraphProgramRecord2(uint32_t NodeIndex, const void* pRecord, uint32_t RecordSizeInBytes) override {
        m_recordedProgramRecords2.push_back({ NodeIndex, pRecord, RecordSizeInBytes });
    }

    const BackingMemory2Record& GetWorkGraphBackingMemory2() const noexcept { return m_backingMemory2; }
    size_t GetRecordedProgramRecord2Count() const noexcept { return m_recordedProgramRecords2.size(); }
    const std::vector<ProgramRecord2Entry>& GetRecordedProgramRecords2() const noexcept { return m_recordedProgramRecords2; }

    // ID3D12GraphicsCommandList13
    void SetWorkGraphBackingMemory3(D3D12_GPU_VIRTUAL_ADDRESS RangeStart, uint64_t RangeSizeInBytes, uint64_t ScratchBufferSizeInBytes, uint32_t Flags) override {
        m_backingMemory3 = { RangeStart, RangeSizeInBytes, ScratchBufferSizeInBytes, Flags };
    }

    void DispatchGraphProgramRecord3(uint32_t NodeIndex, const void* pRecord, uint32_t RecordSizeInBytes, uint32_t RecordCount) override {
        m_recordedProgramRecords3.push_back({ NodeIndex, pRecord, RecordSizeInBytes, RecordCount });
    }

    const BackingMemory3Record& GetWorkGraphBackingMemory3() const noexcept { return m_backingMemory3; }
    size_t GetRecordedProgramRecord3Count() const noexcept { return m_recordedProgramRecords3.size(); }
    const std::vector<ProgramRecord3Entry>& GetRecordedProgramRecords3() const noexcept { return m_recordedProgramRecords3; }

    // ID3D12GraphicsCommandList14
    void SetWorkGraphBackingMemory4(D3D12_GPU_VIRTUAL_ADDRESS RangeStart, uint64_t RangeSizeInBytes, uint64_t ScratchBufferSizeInBytes, uint32_t MaxConcurrency, uint32_t Flags) override {
        m_backingMemory4 = { RangeStart, RangeSizeInBytes, ScratchBufferSizeInBytes, MaxConcurrency, Flags };
    }

    void DispatchGraphProgramRecord4(uint32_t NodeIndex, const void* pRecord, uint32_t RecordSizeInBytes, uint32_t ConcurrencyGroup, uint32_t DispatchFlags) override {
        m_recordedProgramRecords4.push_back({ NodeIndex, pRecord, RecordSizeInBytes, ConcurrencyGroup, DispatchFlags });
    }

    const BackingMemory4Record& GetWorkGraphBackingMemory4() const noexcept { return m_backingMemory4; }
    size_t GetRecordedProgramRecord4Count() const noexcept { return m_recordedProgramRecords4.size(); }
    const std::vector<ProgramRecord4Entry>& GetRecordedProgramRecords4() const noexcept { return m_recordedProgramRecords4; }

    // ID3D12GraphicsCommandList15
    void SetWorkGraphBackingMemory5(D3D12_GPU_VIRTUAL_ADDRESS RangeStart, uint64_t RangeSizeInBytes, uint64_t ScratchBufferSizeInBytes, uint32_t MaxConcurrency, uint32_t AllocationTier, uint32_t Flags) override {
        m_backingMemory5 = { RangeStart, RangeSizeInBytes, ScratchBufferSizeInBytes, MaxConcurrency, AllocationTier, Flags };
    }

    void DispatchGraphProgramRecord5(uint32_t NodeIndex, const void* pRecord, uint32_t RecordSizeInBytes, uint32_t ConcurrencyGroup, uint32_t DispatchMask, uint32_t DispatchFlags) override {
        m_recordedProgramRecords5.push_back({ NodeIndex, pRecord, RecordSizeInBytes, ConcurrencyGroup, DispatchMask, DispatchFlags });
    }

    const BackingMemory5Record& GetWorkGraphBackingMemory5() const noexcept { return m_backingMemory5; }
    size_t GetRecordedProgramRecord5Count() const noexcept { return m_recordedProgramRecords5.size(); }
    const std::vector<ProgramRecord5Entry>& GetRecordedProgramRecords5() const noexcept { return m_recordedProgramRecords5; }

    // ID3D12GraphicsCommandList16
    void SetWorkGraphBackingMemory6(D3D12_GPU_VIRTUAL_ADDRESS RangeStart, uint64_t RangeSizeInBytes, uint64_t ScratchBufferSizeInBytes, uint32_t MaxConcurrency, uint32_t AllocationTier, uint32_t CooperativeMatrixFlags, uint32_t Flags) override {
        m_backingMemory6 = { RangeStart, RangeSizeInBytes, ScratchBufferSizeInBytes, MaxConcurrency, AllocationTier, CooperativeMatrixFlags, Flags };
    }

    void DispatchGraphProgramRecord6(uint32_t NodeIndex, const void* pRecord, uint32_t RecordSizeInBytes, uint32_t ConcurrencyGroup, uint32_t CooperativeMatrixDim, uint32_t DispatchMask, uint32_t DispatchFlags) override {
        m_recordedProgramRecords6.push_back({ NodeIndex, pRecord, RecordSizeInBytes, ConcurrencyGroup, CooperativeMatrixDim, DispatchMask, DispatchFlags });
    }

    const BackingMemory6Record& GetWorkGraphBackingMemory6() const noexcept { return m_backingMemory6; }
    size_t GetRecordedProgramRecord6Count() const noexcept { return m_recordedProgramRecords6.size(); }
    const std::vector<ProgramRecord6Entry>& GetRecordedProgramRecords6() const noexcept { return m_recordedProgramRecords6; }
};

using Prism3D12GraphicsCommandList8Impl = Prism3D12GraphicsCommandList7Impl;
using Prism3D12GraphicsCommandList9Impl = Prism3D12GraphicsCommandList7Impl;
using Prism3D12GraphicsCommandList10Impl = Prism3D12GraphicsCommandList7Impl;
using Prism3D12GraphicsCommandList11Impl = Prism3D12GraphicsCommandList7Impl;
using Prism3D12GraphicsCommandList12Impl = Prism3D12GraphicsCommandList7Impl;
using Prism3D12GraphicsCommandList13Impl = Prism3D12GraphicsCommandList7Impl;
using Prism3D12GraphicsCommandList14Impl = Prism3D12GraphicsCommandList7Impl;
using Prism3D12GraphicsCommandList15Impl = Prism3D12GraphicsCommandList7Impl;
using Prism3D12GraphicsCommandList16Impl = Prism3D12GraphicsCommandList7Impl;

} // namespace prismx
