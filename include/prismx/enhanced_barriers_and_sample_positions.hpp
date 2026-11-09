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
// ID3D12GraphicsCommandList17 (Work Graphs 3.2 128x128 Cooperative Matrix & Dynamic Cluster Tier)
// ============================================================================

inline constexpr IID OFFICIAL_IID_ID3D12GraphicsCommandList17 =
    { 0x7b320f94, 0x823b, 0x4e23, { 0xbb, 0x44, 0xa9, 0x32, 0x66, 0x55, 0x99, 0x2a } };
inline constexpr IID IID_ID3D12GraphicsCommandList17 = OFFICIAL_IID_ID3D12GraphicsCommandList17;

class ID3D12GraphicsCommandList17 : public ID3D12GraphicsCommandList16 {
public:
    virtual void SetWorkGraphBackingMemory7(
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart,
        uint64_t RangeSizeInBytes,
        uint64_t ScratchBufferSizeInBytes,
        uint32_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t Flags) = 0;

    virtual void DispatchGraphProgramRecord7(
        uint32_t NodeIndex,
        const void* pRecord,
        uint32_t RecordSizeInBytes,
        uint32_t ConcurrencyGroup,
        uint32_t QueueAffinityMask,
        uint32_t DynamicClusterExpansionTier,
        uint32_t DispatchMask,
        uint32_t DispatchFlags) = 0;
};

// ============================================================================
// ID3D12GraphicsCommandList18 (Work Graphs 3.3 256x256 Cooperative Matrix, Sparse Tensor & Concurrency 1024)
// ============================================================================

inline constexpr IID OFFICIAL_IID_ID3D12GraphicsCommandList18 =
    { 0xf44a8612, 0x4217, 0x4ef3, { 0x99, 0xb8, 0xec, 0x16, 0x7c, 0xb4, 0x47, 0xcb } };
inline constexpr IID IID_ID3D12GraphicsCommandList18 = OFFICIAL_IID_ID3D12GraphicsCommandList18;

class ID3D12GraphicsCommandList18 : public ID3D12GraphicsCommandList17 {
public:
    virtual void SetWorkGraphBackingMemory8(
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart,
        uint64_t RangeSizeInBytes,
        uint64_t ScratchBufferSizeInBytes,
        uint32_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t SparsityMask,
        uint32_t Flags) = 0;

    virtual void DispatchGraphProgramRecord8(
        uint32_t NodeIndex,
        const void* pRecord,
        uint32_t RecordSizeInBytes,
        uint32_t ConcurrencyGroup,
        uint32_t QueueAffinityMask,
        uint32_t DynamicClusterExpansionTier,
        uint32_t TensorCoreMask,
        uint32_t DispatchMask,
        uint32_t DispatchFlags) = 0;
};

// ============================================================================
// ID3D12GraphicsCommandList19 (Work Graphs 3.4 512x512 Cooperative Matrix, FP4 Sub-Byte & Concurrency 2048)
// ============================================================================

inline constexpr IID OFFICIAL_IID_ID3D12GraphicsCommandList19 =
    { 0x055b9723, 0x5328, 0x4f04, { 0xaa, 0xc9, 0xfd, 0x27, 0x8d, 0xc5, 0x58, 0x0c } };
inline constexpr IID IID_ID3D12GraphicsCommandList19 = OFFICIAL_IID_ID3D12GraphicsCommandList19;

class ID3D12GraphicsCommandList19 : public ID3D12GraphicsCommandList18 {
public:
    virtual void SetWorkGraphBackingMemory9(
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart,
        uint64_t RangeSizeInBytes,
        uint64_t ScratchBufferSizeInBytes,
        uint32_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t SparsityMask,
        uint32_t SubAllocationMask,
        uint32_t Flags) = 0;

    virtual void DispatchGraphProgramRecord9(
        uint32_t NodeIndex,
        const void* pRecord,
        uint32_t RecordSizeInBytes,
        uint32_t ConcurrencyGroup,
        uint32_t QueueAffinityMask,
        uint32_t DynamicClusterExpansionTier,
        uint32_t TensorCoreMask,
        uint32_t SubAllocationMask,
        uint32_t DispatchMask,
        uint32_t DispatchFlags) = 0;
};

// ============================================================================
// ID3D12GraphicsCommandList20 (Work Graphs 3.5 1024x1024 Cooperative Matrix, MXFP6/MXFP4 & Concurrency 4096)
// ============================================================================

inline constexpr IID OFFICIAL_IID_ID3D12GraphicsCommandList20 =
    { 0x166ca834, 0x6439, 0x4015, { 0xbb, 0xda, 0x0e, 0x28, 0x9e, 0xd6, 0x59, 0x1d } };
inline constexpr IID IID_ID3D12GraphicsCommandList20 = OFFICIAL_IID_ID3D12GraphicsCommandList20;

class ID3D12GraphicsCommandList20 : public ID3D12GraphicsCommandList19 {
public:
    virtual void SetWorkGraphBackingMemory10(
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart,
        uint64_t RangeSizeInBytes,
        uint64_t ScratchBufferSizeInBytes,
        uint32_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t SparsityMask,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t Flags) = 0;

    virtual void DispatchGraphProgramRecord10(
        uint32_t NodeIndex,
        const void* pRecord,
        uint32_t RecordSizeInBytes,
        uint32_t ConcurrencyGroup,
        uint32_t QueueAffinityMask,
        uint32_t DynamicClusterExpansionTier,
        uint32_t TensorCoreMask,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t DispatchMask,
        uint32_t DispatchFlags) = 0;
};

// ============================================================================
// ID3D12GraphicsCommandList21 (Work Graphs 3.6 2048x2048 Cooperative Matrix, MXFP8/MXFP4/MXFP2, Feedback Loops & Concurrency 8192)
// ============================================================================

inline constexpr IID OFFICIAL_IID_ID3D12GraphicsCommandList21 =
    { 0x277db945, 0x754a, 0x4126, { 0xcc, 0xeb, 0x1f, 0x39, 0xaf, 0xe7, 0x6a, 0x2e } };
inline constexpr IID IID_ID3D12GraphicsCommandList21 = OFFICIAL_IID_ID3D12GraphicsCommandList21;

class ID3D12GraphicsCommandList21 : public ID3D12GraphicsCommandList20 {
public:
    virtual void SetWorkGraphBackingMemory11(
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart,
        uint64_t RangeSizeInBytes,
        uint64_t ScratchBufferSizeInBytes,
        uint32_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t SparsityMask,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t Flags) = 0;

    virtual void DispatchGraphProgramRecord11(
        uint32_t NodeIndex,
        const void* pRecord,
        uint32_t RecordSizeInBytes,
        uint32_t ConcurrencyGroup,
        uint32_t QueueAffinityMask,
        uint32_t DynamicClusterExpansionTier,
        uint32_t TensorCoreMask,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t DispatchMask,
        uint32_t DispatchFlags) = 0;
};

// ============================================================================
// ID3D12GraphicsCommandList22 (Work Graphs 3.7 4096x4096 Cooperative Matrix, Recursion & Concurrency 16384)
// ============================================================================

inline constexpr IID OFFICIAL_IID_ID3D12GraphicsCommandList22 =
    { 0x388ec056, 0x865b, 0x4237, { 0x9d, 0xfc, 0x2e, 0x40, 0xba, 0xf8, 0x7b, 0x3f } };
inline constexpr IID IID_ID3D12GraphicsCommandList22 = OFFICIAL_IID_ID3D12GraphicsCommandList22;

class ID3D12GraphicsCommandList22 : public ID3D12GraphicsCommandList21 {
public:
    virtual void SetWorkGraphBackingMemory12(
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart,
        uint64_t RangeSizeInBytes,
        uint64_t ScratchBufferSizeInBytes,
        uint32_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t SparsityMask,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t Flags) = 0;

    virtual void DispatchGraphProgramRecord12(
        uint32_t NodeIndex,
        const void* pRecord,
        uint32_t RecordSizeInBytes,
        uint32_t ConcurrencyGroup,
        uint32_t QueueAffinityMask,
        uint32_t DynamicClusterExpansionTier,
        uint32_t TensorCoreMask,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t DispatchMask,
        uint32_t DispatchFlags) = 0;
};

// ============================================================================
// ID3D12GraphicsCommandList23 (Work Graphs 3.8 8192x8192 Cooperative Matrix, Mesh Pipelining & Concurrency 32768)
// ============================================================================

inline constexpr IID OFFICIAL_IID_ID3D12GraphicsCommandList23 =
    { 0x499fd167, 0x976c, 0x4348, { 0xae, 0x0d, 0x3f, 0x51, 0xcb, 0x09, 0x8c, 0x40 } };
inline constexpr IID IID_ID3D12GraphicsCommandList23 = OFFICIAL_IID_ID3D12GraphicsCommandList23;

class ID3D12GraphicsCommandList23 : public ID3D12GraphicsCommandList22 {
public:
    virtual void SetWorkGraphBackingMemory13(
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart,
        uint64_t RangeSizeInBytes,
        uint64_t ScratchBufferSizeInBytes,
        uint32_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t SparsityMask,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t Flags) = 0;

    virtual void DispatchGraphProgramRecord13(
        uint32_t NodeIndex,
        const void* pRecord,
        uint32_t RecordSizeInBytes,
        uint32_t ConcurrencyGroup,
        uint32_t QueueAffinityMask,
        uint32_t DynamicClusterExpansionTier,
        uint32_t TensorCoreMask,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t DispatchMask,
        uint32_t DispatchFlags) = 0;
};

// ============================================================================
// ID3D12GraphicsCommandList24 (Work Graphs 3.9 16384x16384 Cooperative Matrix, Mesh Pipelining Tier 2 & Concurrency 65536)
// ============================================================================

inline constexpr IID OFFICIAL_IID_ID3D12GraphicsCommandList24 =
    { 0x5a18e278, 0xa87d, 0x4459, { 0xbf, 0x1e, 0x4f, 0x62, 0xdc, 0x1a, 0x9d, 0x51 } };
inline constexpr IID IID_ID3D12GraphicsCommandList24 = OFFICIAL_IID_ID3D12GraphicsCommandList24;

class ID3D12GraphicsCommandList24 : public ID3D12GraphicsCommandList23 {
public:
    virtual void SetWorkGraphBackingMemory14(
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart,
        uint64_t RangeSizeInBytes,
        uint64_t ScratchBufferSizeInBytes,
        uint32_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t SparsityMask,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t Flags) = 0;

    virtual void DispatchGraphProgramRecord14(
        uint32_t NodeIndex,
        const void* pRecord,
        uint32_t RecordSizeInBytes,
        uint32_t ConcurrencyGroup,
        uint32_t QueueAffinityMask,
        uint32_t DynamicClusterExpansionTier,
        uint32_t TensorCoreMask,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t DispatchMask,
        uint32_t DispatchFlags) = 0;
};

// ============================================================================
// ID3D12GraphicsCommandList25 (Work Graphs 4.0 32768x32768 Cooperative Matrix, Mesh Pipelining Tier 3 & Concurrency 131072)
// ============================================================================

inline constexpr IID OFFICIAL_IID_ID3D12GraphicsCommandList25 =
    { 0x6b29f389, 0xb98e, 0x456a, { 0xc0, 0x2f, 0x50, 0x73, 0xed, 0x2b, 0xae, 0x62 } };
inline constexpr IID IID_ID3D12GraphicsCommandList25 = OFFICIAL_IID_ID3D12GraphicsCommandList25;

class ID3D12GraphicsCommandList25 : public ID3D12GraphicsCommandList24 {
public:
    virtual void SetWorkGraphBackingMemory15(
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart,
        uint64_t RangeSizeInBytes,
        uint64_t ScratchBufferSizeInBytes,
        uint32_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t SparsityMask,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t Flags) = 0;

    virtual void DispatchGraphProgramRecord15(
        uint32_t NodeIndex,
        const void* pRecord,
        uint32_t RecordSizeInBytes,
        uint32_t ConcurrencyGroup,
        uint32_t QueueAffinityMask,
        uint32_t DynamicClusterExpansionTier,
        uint32_t TensorCoreMask,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t DispatchMask,
        uint32_t DispatchFlags) = 0;
};

// ============================================================================
// ID3D12GraphicsCommandList26 (Work Graphs 4.1 65536x65536 Cooperative Matrix, Microscopic V7 & Concurrency 262144)
// ============================================================================

inline constexpr IID OFFICIAL_IID_ID3D12GraphicsCommandList26 =
    { 0x9b7e3f81, 0x5a2d, 0x41e8, { 0x93, 0x4f, 0x3d, 0x1a, 0x7c, 0x9e, 0x5b, 0x2f } };
inline constexpr IID IID_ID3D12GraphicsCommandList26 = OFFICIAL_IID_ID3D12GraphicsCommandList26;

class ID3D12GraphicsCommandList26 : public ID3D12GraphicsCommandList25 {
public:
    virtual void SetWorkGraphBackingMemory16(
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart,
        uint64_t RangeSizeInBytes,
        uint64_t ScratchBufferSizeInBytes,
        uint32_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t SparsityMask,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t Flags) = 0;

    virtual void DispatchGraphProgramRecord16(
        uint32_t NodeIndex,
        const void* pRecord,
        uint32_t RecordSizeInBytes,
        uint32_t ConcurrencyGroup,
        uint32_t QueueAffinityMask,
        uint32_t DynamicClusterExpansionTier,
        uint32_t TensorCoreMask,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t DispatchMask,
        uint32_t DispatchFlags) = 0;
};

// ============================================================================
// ID3D12GraphicsCommandList27 (Work Graphs 5.0 131072x131072 Cooperative Matrix, Microscopic V8, Sparse Tensor & Concurrency 524288)
// ============================================================================

inline constexpr IID OFFICIAL_IID_ID3D12GraphicsCommandList27 =
    { 0x2b8c9d1a, 0x3e4f, 0x5a6b, { 0x7c, 0x8d, 0x9e, 0x0f, 0x1a, 0x2b, 0x3c, 0x4d } };
inline constexpr IID IID_ID3D12GraphicsCommandList27 = OFFICIAL_IID_ID3D12GraphicsCommandList27;

class ID3D12GraphicsCommandList27 : public ID3D12GraphicsCommandList26 {
public:
    virtual void SetWorkGraphBackingMemory17(
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart,
        uint64_t RangeSizeInBytes,
        uint64_t ScratchBufferSizeInBytes,
        uint32_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t SparsityMask,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t Flags) = 0;

    virtual void DispatchGraphProgramRecord17(
        uint32_t NodeIndex,
        const void* pRecord,
        uint32_t RecordSizeInBytes,
        uint32_t ConcurrencyGroup,
        uint32_t QueueAffinityMask,
        uint32_t DynamicClusterExpansionTier,
        uint32_t TensorCoreMask,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DispatchMask,
        uint32_t DispatchFlags) = 0;
};

// ============================================================================
// ID3D12GraphicsCommandList28 (Work Graphs 5.1 262144x262144 Cooperative Matrix, Microscopic V9, Sparse Tensor Block Tier 2, Deterministic Reduction & Concurrency 1048576)
// ============================================================================

inline constexpr IID OFFICIAL_IID_ID3D12GraphicsCommandList28 =
    { 0x3c9d0e2b, 0x4f5a, 0x6b7c, { 0x8d, 0x9e, 0x0f, 0x1a, 0x2b, 0x3c, 0x4d, 0x5e } };
inline constexpr IID IID_ID3D12GraphicsCommandList28 = OFFICIAL_IID_ID3D12GraphicsCommandList28;

class ID3D12GraphicsCommandList28 : public ID3D12GraphicsCommandList27 {
public:
    virtual void SetWorkGraphBackingMemory18(
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart,
        uint64_t RangeSizeInBytes,
        uint64_t ScratchBufferSizeInBytes,
        uint32_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t SparsityMask,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t Flags) = 0;

    virtual void DispatchGraphProgramRecord18(
        uint32_t NodeIndex,
        const void* pRecord,
        uint32_t RecordSizeInBytes,
        uint32_t ConcurrencyGroup,
        uint32_t QueueAffinityMask,
        uint32_t DynamicClusterExpansionTier,
        uint32_t TensorCoreMask,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t DispatchMask,
        uint32_t DispatchFlags) = 0;
};

// ============================================================================
// ID3D12GraphicsCommandList29 (Work Graphs 5.2 524288x524288 Cooperative Matrix, Microscopic V10, Sparse Tensor Block Tier 3, Deterministic Reduction Tier 2 & Concurrency 2097152)
// ============================================================================

inline constexpr IID OFFICIAL_IID_ID3D12GraphicsCommandList29 =
    { 0x4d0e1f3c, 0x5a6b, 0x7c8d, { 0x9e, 0x0f, 0x1a, 0x2b, 0x3c, 0x4d, 0x5e, 0x6f } };
inline constexpr IID IID_ID3D12GraphicsCommandList29 = OFFICIAL_IID_ID3D12GraphicsCommandList29;

class ID3D12GraphicsCommandList29 : public ID3D12GraphicsCommandList28 {
public:
    virtual void SetWorkGraphBackingMemory19(
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart,
        uint64_t RangeSizeInBytes,
        uint64_t ScratchBufferSizeInBytes,
        uint32_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t SparsityMask,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t Flags) = 0;

    virtual void DispatchGraphProgramRecord19(
        uint32_t NodeIndex,
        const void* pRecord,
        uint32_t RecordSizeInBytes,
        uint32_t ConcurrencyGroup,
        uint32_t QueueAffinityMask,
        uint32_t DynamicClusterExpansionTier,
        uint32_t TensorCoreMask,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t DispatchMask,
        uint32_t DispatchFlags) = 0;
};

// ============================================================================
// ID3D12GraphicsCommandList30 (Work Graphs 5.3 1048576x1048576 Cooperative Matrix, Microscopic V11, Sparse Cluster Tier, Deterministic Reduction Tier 3 & Concurrency 4194304)
// ============================================================================

inline constexpr IID OFFICIAL_IID_ID3D12GraphicsCommandList30 =
    { 0x5e1f204d, 0x6b7c, 0x8d9e, { 0xaf, 0x10, 0x2b, 0x3c, 0x4d, 0x5e, 0x6f, 0x70 } };
inline constexpr IID IID_ID3D12GraphicsCommandList30 = OFFICIAL_IID_ID3D12GraphicsCommandList30;

class ID3D12GraphicsCommandList30 : public ID3D12GraphicsCommandList29 {
public:
    virtual void SetWorkGraphBackingMemory20(
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart,
        uint64_t RangeSizeInBytes,
        uint64_t ScratchBufferSizeInBytes,
        uint32_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t SparsityMask,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t Flags) = 0;

    virtual void DispatchGraphProgramRecord20(
        uint32_t NodeIndex,
        const void* pRecord,
        uint32_t RecordSizeInBytes,
        uint32_t ConcurrencyGroup,
        uint32_t QueueAffinityMask,
        uint32_t DynamicClusterExpansionTier,
        uint32_t TensorCoreMask,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t DispatchMask,
        uint32_t DispatchFlags) = 0;
};

// ============================================================================
// ID3D12GraphicsCommandList31 (Work Graphs 5.4 2097152x2097152 Cooperative Matrix, Microscopic V12, Sparse Cluster Expansion Tier 2, Multi-Queue Fusion Tier 8 & Concurrency 8388608)
// ============================================================================

inline constexpr IID OFFICIAL_IID_ID3D12GraphicsCommandList31 =
    { 0x6f20315e, 0x7c8d, 0x9e0f, { 0xba, 0x21, 0x3c, 0x4d, 0x5e, 0x6f, 0x70, 0x81 } };
inline constexpr IID IID_ID3D12GraphicsCommandList31 = OFFICIAL_IID_ID3D12GraphicsCommandList31;

class ID3D12GraphicsCommandList31 : public ID3D12GraphicsCommandList30 {
public:
    virtual void SetWorkGraphBackingMemory21(
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart,
        uint64_t RangeSizeInBytes,
        uint64_t ScratchBufferSizeInBytes,
        uint32_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t SparsityMask,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t Flags) = 0;

    virtual void DispatchGraphProgramRecord21(
        uint32_t NodeIndex,
        const void* pRecord,
        uint32_t RecordSizeInBytes,
        uint32_t ConcurrencyGroup,
        uint32_t QueueAffinityMask,
        uint32_t DynamicClusterExpansionTier,
        uint32_t TensorCoreMask,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t DispatchMask,
        uint32_t DispatchFlags) = 0;
};

// ============================================================================
// ID3D12GraphicsCommandList32 (Work Graphs 5.5 4194304x4194304 Cooperative Matrix, Microscopic V13, Sparse Cluster Expansion Tier 3, Multi-Queue Fusion Tier 9, Async Kernel Dispatch Tier 3 & Concurrency 16777216)
// ============================================================================

inline constexpr IID OFFICIAL_IID_ID3D12GraphicsCommandList32 =
    { 0x7031426f, 0x8d9e, 0xaf10, { 0xcb, 0x32, 0x4d, 0x5e, 0x6f, 0x70, 0x81, 0x92 } };
inline constexpr IID IID_ID3D12GraphicsCommandList32 = OFFICIAL_IID_ID3D12GraphicsCommandList32;

class ID3D12GraphicsCommandList32 : public ID3D12GraphicsCommandList31 {
public:
    virtual void SetWorkGraphBackingMemory22(
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart,
        uint64_t RangeSizeInBytes,
        uint64_t ScratchBufferSizeInBytes,
        uint32_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t SparsityMask,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t Flags) = 0;

    virtual void DispatchGraphProgramRecord22(
        uint32_t NodeIndex,
        const void* pRecord,
        uint32_t RecordSizeInBytes,
        uint32_t ConcurrencyGroup,
        uint32_t QueueAffinityMask,
        uint32_t DynamicClusterExpansionTier,
        uint32_t TensorCoreMask,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t DispatchMask,
        uint32_t DispatchFlags) = 0;
};

// ============================================================================
// ID3D12GraphicsCommandList33 (Work Graphs 5.6 8388608x8388608 Cooperative Matrix, Microscopic V14, Sparse Cluster Expansion Tier 4, Multi-Queue Fusion Tier 10, Async Kernel Dispatch Tier 4, Neural Execution Engine Tier 1 & Concurrency 33554432)
// ============================================================================

inline constexpr IID OFFICIAL_IID_ID3D12GraphicsCommandList33 =
    { 0x81425370, 0x9eaf, 0xb021, { 0xdc, 0x43, 0x5e, 0x6f, 0x70, 0x81, 0x92, 0xa3 } };
inline constexpr IID IID_ID3D12GraphicsCommandList33 = OFFICIAL_IID_ID3D12GraphicsCommandList33;

class ID3D12GraphicsCommandList33 : public ID3D12GraphicsCommandList32 {
public:
    virtual void SetWorkGraphBackingMemory23(
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart,
        uint64_t RangeSizeInBytes,
        uint64_t ScratchBufferSizeInBytes,
        uint32_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t SparsityMask,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t NeuralExecutionEngineTier,
        uint32_t Flags) = 0;

    virtual void DispatchGraphProgramRecord23(
        uint32_t NodeIndex,
        const void* pRecord,
        uint32_t RecordSizeInBytes,
        uint32_t ConcurrencyGroup,
        uint32_t QueueAffinityMask,
        uint32_t DynamicClusterExpansionTier,
        uint32_t TensorCoreMask,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t NeuralExecutionEngineTier,
        uint32_t DispatchMask,
        uint32_t DispatchFlags) = 0;
};

// ============================================================================
// ID3D12GraphicsCommandList34 (Work Graphs 5.7 16777216x16777216 Cooperative Matrix, Microscopic V15, Sparse Cluster Expansion Tier 5, Multi-Queue Fusion Tier 11, Async Kernel Dispatch Tier 5, Neural Execution Engine Tier 2, Adaptive Tensor Core Tier 1 & Concurrency 67108864)
// ============================================================================

inline constexpr IID OFFICIAL_IID_ID3D12GraphicsCommandList34 =
    { 0x92536481, 0xafb0, 0xc132, { 0xed, 0x54, 0x6f, 0x70, 0x81, 0x92, 0xa3, 0xb4 } };
inline constexpr IID IID_ID3D12GraphicsCommandList34 = OFFICIAL_IID_ID3D12GraphicsCommandList34;

class ID3D12GraphicsCommandList34 : public ID3D12GraphicsCommandList33 {
public:
    virtual void SetWorkGraphBackingMemory24(
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart,
        uint64_t RangeSizeInBytes,
        uint64_t ScratchBufferSizeInBytes,
        uint32_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t SparsityMask,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t NeuralExecutionEngineTier,
        uint32_t AdaptiveTensorCoreTier,
        uint32_t Flags) = 0;

    virtual void DispatchGraphProgramRecord24(
        uint32_t NodeIndex,
        const void* pRecord,
        uint32_t RecordSizeInBytes,
        uint32_t ConcurrencyGroup,
        uint32_t QueueAffinityMask,
        uint32_t DynamicClusterExpansionTier,
        uint32_t TensorCoreMask,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t NeuralExecutionEngineTier,
        uint32_t AdaptiveTensorCoreTier,
        uint32_t DispatchMask,
        uint32_t DispatchFlags) = 0;
};

// ============================================================================
// ID3D12GraphicsCommandList35 (Work Graphs 5.8 33554432x33554432 Cooperative Matrix, Microscopic V16, Dynamic Cluster Expansion Tier 21, Multi-Queue Fusion Tier 12, Async Kernel Dispatch Tier 6, Neural Execution Engine Tier 3, Adaptive Tensor Core Tier 2, Sovereign Silicon Telemetry Tier 1 & Concurrency 134217728)
// ============================================================================

inline constexpr IID OFFICIAL_IID_ID3D12GraphicsCommandList35 =
    { 0xa3647592, 0xbfc1, 0xd243, { 0xfe, 0x65, 0x7a, 0x81, 0x92, 0xa3, 0xb4, 0xc5 } };
inline constexpr IID IID_ID3D12GraphicsCommandList35 = OFFICIAL_IID_ID3D12GraphicsCommandList35;

class ID3D12GraphicsCommandList35 : public ID3D12GraphicsCommandList34 {
public:
    virtual void SetWorkGraphBackingMemory25(
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart,
        uint64_t RangeSizeInBytes,
        uint64_t ScratchBufferSizeInBytes,
        uint32_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t SparsityMask,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t NeuralExecutionEngineTier,
        uint32_t AdaptiveTensorCoreTier,
        uint32_t SovereignSiliconTelemetryTier,
        uint32_t Flags) = 0;

    virtual void DispatchGraphProgramRecord25(
        uint32_t NodeIndex,
        const void* pRecord,
        uint32_t RecordSizeInBytes,
        uint32_t ConcurrencyGroup,
        uint32_t QueueAffinityMask,
        uint32_t DynamicClusterExpansionTier,
        uint32_t TensorCoreMask,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t NeuralExecutionEngineTier,
        uint32_t AdaptiveTensorCoreTier,
        uint32_t SovereignSiliconTelemetryTier,
        uint32_t DispatchMask,
        uint32_t DispatchFlags) = 0;
};

// ============================================================================
// ID3D12GraphicsCommandList36 (Work Graphs 5.9 67108864x67108864 Cooperative Matrix, Microscopic V17, Dynamic Cluster Expansion Tier 22, Multi-Queue Fusion Tier 13, Async Kernel Dispatch Tier 7, Neural Execution Engine Tier 4, Adaptive Tensor Core Tier 3, Sovereign Silicon Telemetry Tier 2, Quantum Emulation Tier 1 & Concurrency 268435456)
// ============================================================================

inline constexpr IID OFFICIAL_IID_ID3D12GraphicsCommandList36 =
    { 0xb47586a3, 0xcfd2, 0xe354, { 0x0f, 0x76, 0x8b, 0x92, 0xa3, 0xb4, 0xc5, 0xd6 } };
inline constexpr IID IID_ID3D12GraphicsCommandList36 = OFFICIAL_IID_ID3D12GraphicsCommandList36;

class ID3D12GraphicsCommandList36 : public ID3D12GraphicsCommandList35 {
public:
    virtual void SetWorkGraphBackingMemory26(
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart,
        uint64_t RangeSizeInBytes,
        uint64_t ScratchBufferSizeInBytes,
        uint32_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t SparsityMask,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t NeuralExecutionEngineTier,
        uint32_t AdaptiveTensorCoreTier,
        uint32_t SovereignSiliconTelemetryTier,
        uint32_t QuantumEmulationTier,
        uint32_t Flags) = 0;

    virtual void DispatchGraphProgramRecord26(
        uint32_t NodeIndex,
        const void* pRecord,
        uint32_t RecordSizeInBytes,
        uint32_t ConcurrencyGroup,
        uint32_t QueueAffinityMask,
        uint32_t DynamicClusterExpansionTier,
        uint32_t TensorCoreMask,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t NeuralExecutionEngineTier,
        uint32_t AdaptiveTensorCoreTier,
        uint32_t SovereignSiliconTelemetryTier,
        uint32_t QuantumEmulationTier,
        uint32_t DispatchMask,
        uint32_t DispatchFlags) = 0;
};

// ============================================================================
// ID3D12GraphicsCommandList37 (Work Graphs 6.0 134217728x134217728 Cooperative Matrix, Microscopic V18, Dynamic Cluster Expansion Tier 23, Multi-Queue Fusion Tier 14, Async Kernel Dispatch Tier 8, Neural Execution Engine Tier 5, Adaptive Tensor Core Tier 4, Sovereign Silicon Telemetry Tier 3, Quantum Emulation Tier 2 & Concurrency 536870912)
// ============================================================================

inline constexpr IID OFFICIAL_IID_ID3D12GraphicsCommandList37 =
    { 0xc58697b4, 0xd0e3, 0xf465, { 0x10, 0x87, 0x9c, 0xa3, 0xb4, 0xc5, 0xd6, 0xe7 } };
inline constexpr IID IID_ID3D12GraphicsCommandList37 = OFFICIAL_IID_ID3D12GraphicsCommandList37;

class ID3D12GraphicsCommandList37 : public ID3D12GraphicsCommandList36 {
public:
    virtual void SetWorkGraphBackingMemory27(
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart,
        uint64_t RangeSizeInBytes,
        uint64_t ScratchBufferSizeInBytes,
        uint32_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t SparsityMask,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t NeuralExecutionEngineTier,
        uint32_t AdaptiveTensorCoreTier,
        uint32_t SovereignSiliconTelemetryTier,
        uint32_t QuantumEmulationTier,
        uint32_t Flags) = 0;

    virtual void DispatchGraphProgramRecord27(
        uint32_t NodeIndex,
        const void* pRecord,
        uint32_t RecordSizeInBytes,
        uint32_t ConcurrencyGroup,
        uint32_t QueueAffinityMask,
        uint32_t DynamicClusterExpansionTier,
        uint32_t TensorCoreMask,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t NeuralExecutionEngineTier,
        uint32_t AdaptiveTensorCoreTier,
        uint32_t SovereignSiliconTelemetryTier,
        uint32_t QuantumEmulationTier,
        uint32_t DispatchMask,
        uint32_t DispatchFlags) = 0;
};

// ============================================================================
// ID3D12GraphicsCommandList38 (Work Graphs 6.1 268435456x268435456 Cooperative Matrix, Microscopic V19, Dynamic Cluster Expansion Tier 24, Multi-Queue Fusion Tier 15, Async Kernel Dispatch Tier 9, Neural Execution Engine Tier 6, Adaptive Tensor Core Tier 5, Sovereign Silicon Telemetry Tier 4, Quantum Emulation Tier 3 & Concurrency 1073741824)
// ============================================================================

inline constexpr IID OFFICIAL_IID_ID3D12GraphicsCommandList38 =
    { 0xd697a8c5, 0xe1f4, 0x0576, { 0x21, 0x98, 0xad, 0xb4, 0xc5, 0xd6, 0xe7, 0xf8 } };
inline constexpr IID IID_ID3D12GraphicsCommandList38 = OFFICIAL_IID_ID3D12GraphicsCommandList38;

class ID3D12GraphicsCommandList38 : public ID3D12GraphicsCommandList37 {
public:
    virtual void SetWorkGraphBackingMemory28(
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart,
        uint64_t RangeSizeInBytes,
        uint64_t ScratchBufferSizeInBytes,
        uint32_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t SparsityMask,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t NeuralExecutionEngineTier,
        uint32_t AdaptiveTensorCoreTier,
        uint32_t SovereignSiliconTelemetryTier,
        uint32_t QuantumEmulationTier,
        uint32_t Flags) = 0;

    virtual void DispatchGraphProgramRecord28(
        uint32_t NodeIndex,
        const void* pRecord,
        uint32_t RecordSizeInBytes,
        uint32_t ConcurrencyGroup,
        uint32_t QueueAffinityMask,
        uint32_t DynamicClusterExpansionTier,
        uint32_t TensorCoreMask,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t NeuralExecutionEngineTier,
        uint32_t AdaptiveTensorCoreTier,
        uint32_t SovereignSiliconTelemetryTier,
        uint32_t QuantumEmulationTier,
        uint32_t DispatchMask,
        uint32_t DispatchFlags) = 0;
};

// ============================================================================
// ID3D12GraphicsCommandList39 (Work Graphs 6.2 536870912x536870912 Cooperative Matrix, Microscopic V20, Dynamic Cluster Expansion Tier 25, Multi-Queue Fusion Tier 16, Async Kernel Dispatch Tier 10, Neural Execution Engine Tier 7, Adaptive Tensor Core Tier 6, Sovereign Silicon Telemetry Tier 5, Quantum Emulation Tier 4 & Concurrency 2147483648)
// ============================================================================

inline constexpr IID OFFICIAL_IID_ID3D12GraphicsCommandList39 =
    { 0xe7a8b9d6, 0xf205, 0x1687, { 0x32, 0xa9, 0xbe, 0xc5, 0xd6, 0xe7, 0xf8, 0x09 } };
inline constexpr IID IID_ID3D12GraphicsCommandList39 = OFFICIAL_IID_ID3D12GraphicsCommandList39;

class ID3D12GraphicsCommandList39 : public ID3D12GraphicsCommandList38 {
public:
    virtual void SetWorkGraphBackingMemory29(
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart,
        uint64_t RangeSizeInBytes,
        uint64_t ScratchBufferSizeInBytes,
        uint32_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t SparsityMask,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t NeuralExecutionEngineTier,
        uint32_t AdaptiveTensorCoreTier,
        uint32_t SovereignSiliconTelemetryTier,
        uint32_t QuantumEmulationTier,
        uint32_t Flags) = 0;

    virtual void DispatchGraphProgramRecord29(
        uint32_t NodeIndex,
        const void* pRecord,
        uint32_t RecordSizeInBytes,
        uint32_t ConcurrencyGroup,
        uint32_t QueueAffinityMask,
        uint32_t DynamicClusterExpansionTier,
        uint32_t TensorCoreMask,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t NeuralExecutionEngineTier,
        uint32_t AdaptiveTensorCoreTier,
        uint32_t SovereignSiliconTelemetryTier,
        uint32_t QuantumEmulationTier,
        uint32_t DispatchMask,
        uint32_t DispatchFlags) = 0;
};

// ============================================================================
// ID3D12GraphicsCommandList40 (Work Graphs 6.3 1073741824x1073741824 Cooperative Matrix, Microscopic V21, Dynamic Cluster Expansion Tier 26, Multi-Queue Fusion Tier 17, Async Kernel Dispatch Tier 11, Neural Execution Engine Tier 8, Adaptive Tensor Core Tier 7, Sovereign Silicon Telemetry Tier 6, Quantum Emulation Tier 5 & Concurrency 4294967296)
// ============================================================================

inline constexpr IID OFFICIAL_IID_ID3D12GraphicsCommandList40 =
    { 0x3370b79b, 0xfebe, 0x4df6, { 0xcd, 0x9b, 0x06, 0xcc, 0xfa, 0x5c, 0x6d, 0xc7 } };
inline constexpr IID IID_ID3D12GraphicsCommandList40 = OFFICIAL_IID_ID3D12GraphicsCommandList40;

class ID3D12GraphicsCommandList40 : public ID3D12GraphicsCommandList39 {
public:
    virtual void SetWorkGraphBackingMemory30(
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart,
        uint64_t RangeSizeInBytes,
        uint64_t ScratchBufferSizeInBytes,
        uint64_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t SparsityMask,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t NeuralExecutionEngineTier,
        uint32_t AdaptiveTensorCoreTier,
        uint32_t SovereignSiliconTelemetryTier,
        uint32_t QuantumEmulationTier,
        uint32_t Flags) = 0;

    virtual void DispatchGraphProgramRecord30(
        uint32_t NodeIndex,
        const void* pRecord,
        uint32_t RecordSizeInBytes,
        uint32_t ConcurrencyGroup,
        uint32_t QueueAffinityMask,
        uint32_t DynamicClusterExpansionTier,
        uint32_t TensorCoreMask,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t NeuralExecutionEngineTier,
        uint32_t AdaptiveTensorCoreTier,
        uint32_t SovereignSiliconTelemetryTier,
        uint32_t QuantumEmulationTier,
        uint32_t DispatchMask,
        uint32_t DispatchFlags) = 0;
};

// ============================================================================
// ID3D12GraphicsCommandList41 (Work Graphs 6.4 2147483648x2147483648 Cooperative Matrix, Microscopic V22, Dynamic Cluster Expansion Tier 27, Multi-Queue Fusion Tier 18, Async Kernel Dispatch Tier 12, Neural Execution Engine Tier 9, Adaptive Tensor Core Tier 8, Sovereign Silicon Telemetry Tier 7, Quantum Emulation Tier 6 & Concurrency 8589934592)
// ============================================================================

inline constexpr IID OFFICIAL_IID_ID3D12GraphicsCommandList41 =
    { 0x4481c8ac, 0x0fcf, 0x5ef7, { 0xde, 0xac, 0x17, 0xdd, 0x0b, 0x6d, 0x7e, 0xd8 } };
inline constexpr IID IID_ID3D12GraphicsCommandList41 = OFFICIAL_IID_ID3D12GraphicsCommandList41;

class ID3D12GraphicsCommandList41 : public ID3D12GraphicsCommandList40 {
public:
    virtual void SetWorkGraphBackingMemory31(
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart,
        uint64_t RangeSizeInBytes,
        uint64_t ScratchBufferSizeInBytes,
        uint64_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t SparsityMask,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t NeuralExecutionEngineTier,
        uint32_t AdaptiveTensorCoreTier,
        uint32_t SovereignSiliconTelemetryTier,
        uint32_t QuantumEmulationTier,
        uint32_t Flags) = 0;

    virtual void DispatchGraphProgramRecord31(
        uint32_t NodeIndex,
        const void* pRecord,
        uint32_t RecordSizeInBytes,
        uint32_t ConcurrencyGroup,
        uint32_t QueueAffinityMask,
        uint32_t DynamicClusterExpansionTier,
        uint32_t TensorCoreMask,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t NeuralExecutionEngineTier,
        uint32_t AdaptiveTensorCoreTier,
        uint32_t SovereignSiliconTelemetryTier,
        uint32_t QuantumEmulationTier,
        uint32_t DispatchMask,
        uint32_t DispatchFlags) = 0;
};

// ============================================================================
// ID3D12GraphicsCommandList42 (Work Graphs 6.5 4294967296x4294967296 Cooperative Matrix, Microscopic V23, Dynamic Cluster Expansion Tier 28, Multi-Queue Fusion Tier 19, Async Kernel Dispatch Tier 13, Neural Execution Engine Tier 10, Adaptive Tensor Core Tier 9, Sovereign Silicon Telemetry Tier 8, Quantum Emulation Tier 7 & Concurrency 17179869184)
// ============================================================================

inline constexpr IID OFFICIAL_IID_ID3D12GraphicsCommandList42 =
    { 0x5592d9bd, 0x20df, 0x7008, { 0xef, 0xbd, 0x28, 0xee, 0x1c, 0x7e, 0x8f, 0xe9 } };
inline constexpr IID IID_ID3D12GraphicsCommandList42 = OFFICIAL_IID_ID3D12GraphicsCommandList42;

class ID3D12GraphicsCommandList42 : public ID3D12GraphicsCommandList41 {
public:
    virtual void SetWorkGraphBackingMemory32(
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart,
        uint64_t RangeSizeInBytes,
        uint64_t ScratchBufferSizeInBytes,
        uint64_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t SparsityMask,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t NeuralExecutionEngineTier,
        uint32_t AdaptiveTensorCoreTier,
        uint32_t SovereignSiliconTelemetryTier,
        uint32_t QuantumEmulationTier,
        uint32_t Flags) = 0;

    virtual void DispatchGraphProgramRecord32(
        uint32_t NodeIndex,
        const void* pRecord,
        uint32_t RecordSizeInBytes,
        uint32_t ConcurrencyGroup,
        uint32_t QueueAffinityMask,
        uint32_t DynamicClusterExpansionTier,
        uint32_t TensorCoreMask,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t NeuralExecutionEngineTier,
        uint32_t AdaptiveTensorCoreTier,
        uint32_t SovereignSiliconTelemetryTier,
        uint32_t QuantumEmulationTier,
        uint32_t DispatchMask,
        uint32_t DispatchFlags) = 0;
};

// ============================================================================
// ID3D12GraphicsCommandList43 (Work Graphs 6.6 8589934592x8589934592 Cooperative Matrix, Microscopic V24, Dynamic Cluster Expansion Tier 29, Multi-Queue Fusion Tier 20, Async Kernel Dispatch Tier 14, Neural Execution Engine Tier 11, Adaptive Tensor Core Tier 10, Sovereign Silicon Telemetry Tier 9, Quantum Emulation Tier 8 & Concurrency 34359738368)
// ============================================================================

inline constexpr IID OFFICIAL_IID_ID3D12GraphicsCommandList43 =
    { 0x66a3eace, 0x31ef, 0x8119, { 0xfa, 0xce, 0x39, 0xff, 0x2d, 0x8f, 0x90, 0xfa } };
inline constexpr IID IID_ID3D12GraphicsCommandList43 = OFFICIAL_IID_ID3D12GraphicsCommandList43;

class ID3D12GraphicsCommandList43 : public ID3D12GraphicsCommandList42 {
public:
    virtual void SetWorkGraphBackingMemory33(
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart,
        uint64_t RangeSizeInBytes,
        uint64_t ScratchBufferSizeInBytes,
        uint64_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t SparsityMask,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t NeuralExecutionEngineTier,
        uint32_t AdaptiveTensorCoreTier,
        uint32_t SovereignSiliconTelemetryTier,
        uint32_t QuantumEmulationTier,
        uint32_t Flags) = 0;

    virtual void DispatchGraphProgramRecord33(
        uint32_t NodeIndex,
        const void* pRecord,
        uint32_t RecordSizeInBytes,
        uint32_t ConcurrencyGroup,
        uint32_t QueueAffinityMask,
        uint32_t DynamicClusterExpansionTier,
        uint32_t TensorCoreMask,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t NeuralExecutionEngineTier,
        uint32_t AdaptiveTensorCoreTier,
        uint32_t SovereignSiliconTelemetryTier,
        uint32_t QuantumEmulationTier,
        uint32_t DispatchMask,
        uint32_t DispatchFlags) = 0;
};

// ============================================================================
// ID3D12GraphicsCommandList44 (Work Graphs 6.7 17179869184x17179869184 Cooperative Matrix, Microscopic V25, Dynamic Cluster Expansion Tier 30, Multi-Queue Fusion Tier 21, Async Kernel Dispatch Tier 15, Neural Execution Engine Tier 12, Adaptive Tensor Core Tier 11, Sovereign Silicon Telemetry Tier 10, Quantum Emulation Tier 9 & Concurrency 68719476736)
// ============================================================================

inline constexpr IID OFFICIAL_IID_ID3D12GraphicsCommandList44 =
    { 0x77b4fbdf, 0x42f0, 0x922a, { 0x0b, 0xdf, 0x4a, 0x00, 0x3e, 0x90, 0xa1, 0x0b } };
inline constexpr IID IID_ID3D12GraphicsCommandList44 = OFFICIAL_IID_ID3D12GraphicsCommandList44;

class ID3D12GraphicsCommandList44 : public ID3D12GraphicsCommandList43 {
public:
    virtual void SetWorkGraphBackingMemory34(
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart,
        uint64_t RangeSizeInBytes,
        uint64_t ScratchBufferSizeInBytes,
        uint64_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t SparsityMask,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t NeuralExecutionEngineTier,
        uint32_t AdaptiveTensorCoreTier,
        uint32_t SovereignSiliconTelemetryTier,
        uint32_t QuantumEmulationTier,
        uint32_t Flags) = 0;

    virtual void DispatchGraphProgramRecord34(
        uint32_t NodeIndex,
        const void* pRecord,
        uint32_t RecordSizeInBytes,
        uint32_t ConcurrencyGroup,
        uint32_t QueueAffinityMask,
        uint32_t DynamicClusterExpansionTier,
        uint32_t TensorCoreMask,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t NeuralExecutionEngineTier,
        uint32_t AdaptiveTensorCoreTier,
        uint32_t SovereignSiliconTelemetryTier,
        uint32_t QuantumEmulationTier,
        uint32_t DispatchMask,
        uint32_t DispatchFlags) = 0;
};

// ============================================================================
// ID3D12GraphicsCommandList45 (Work Graphs 6.8 34359738368x34359738368 Cooperative Matrix, Microscopic V26, Dynamic Cluster Expansion Tier 31, Multi-Queue Fusion Tier 22, Async Kernel Dispatch Tier 16, Neural Execution Engine Tier 13, Adaptive Tensor Core Tier 12, Sovereign Silicon Telemetry Tier 11, Quantum Emulation Tier 10 & Concurrency 137438953472)
// ============================================================================

inline constexpr IID OFFICIAL_IID_ID3D12GraphicsCommandList45 =
    { 0x88c50ce0, 0x5301, 0x47e2, { 0x98, 0xee, 0x5b, 0x11, 0x4f, 0xa1, 0xb2, 0x1c } };
inline constexpr IID IID_ID3D12GraphicsCommandList45 = OFFICIAL_IID_ID3D12GraphicsCommandList45;

class ID3D12GraphicsCommandList45 : public ID3D12GraphicsCommandList44 {
public:
    virtual void SetWorkGraphBackingMemory35(
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart,
        uint64_t RangeSizeInBytes,
        uint64_t ScratchBufferSizeInBytes,
        uint64_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t SparsityMask,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t NeuralExecutionEngineTier,
        uint32_t AdaptiveTensorCoreTier,
        uint32_t SovereignSiliconTelemetryTier,
        uint32_t QuantumEmulationTier,
        uint32_t Flags) = 0;

    virtual void DispatchGraphProgramRecord35(
        uint32_t NodeIndex,
        const void* pRecord,
        uint32_t RecordSizeInBytes,
        uint32_t ConcurrencyGroup,
        uint32_t QueueAffinityMask,
        uint32_t DynamicClusterExpansionTier,
        uint32_t TensorCoreMask,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t NeuralExecutionEngineTier,
        uint32_t AdaptiveTensorCoreTier,
        uint32_t SovereignSiliconTelemetryTier,
        uint32_t QuantumEmulationTier,
        uint32_t DispatchMask,
        uint32_t DispatchFlags) = 0;
};

inline constexpr IID OFFICIAL_IID_ID3D12GraphicsCommandList46 =
    { 0x99d60df1, 0x6412, 0x58f3, { 0xa9, 0xff, 0x6c, 0x22, 0x60, 0xb2, 0xc3, 0x2d } };
inline constexpr IID IID_ID3D12GraphicsCommandList46 = OFFICIAL_IID_ID3D12GraphicsCommandList46;

class ID3D12GraphicsCommandList46 : public ID3D12GraphicsCommandList45 {
public:
    virtual void SetWorkGraphBackingMemory36(
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart,
        uint64_t RangeSizeInBytes,
        uint64_t ScratchBufferSizeInBytes,
        uint64_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t SparsityMask,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t NeuralExecutionEngineTier,
        uint32_t AdaptiveTensorCoreTier,
        uint32_t SovereignSiliconTelemetryTier,
        uint32_t QuantumEmulationTier,
        uint32_t Flags) = 0;

    virtual void DispatchGraphProgramRecord36(
        uint32_t NodeIndex,
        const void* pRecord,
        uint32_t RecordSizeInBytes,
        uint32_t ConcurrencyGroup,
        uint32_t QueueAffinityMask,
        uint32_t DynamicClusterExpansionTier,
        uint32_t TensorCoreMask,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t NeuralExecutionEngineTier,
        uint32_t AdaptiveTensorCoreTier,
        uint32_t SovereignSiliconTelemetryTier,
        uint32_t QuantumEmulationTier,
        uint32_t DispatchMask,
        uint32_t DispatchFlags) = 0;
};

inline constexpr IID OFFICIAL_IID_ID3D12GraphicsCommandList47 =
    { 0xaae71ef2, 0x7523, 0x6904, { 0xba, 0x00, 0x7d, 0x33, 0x71, 0xc3, 0xd4, 0x3e } };
inline constexpr IID IID_ID3D12GraphicsCommandList47 = OFFICIAL_IID_ID3D12GraphicsCommandList47;

class ID3D12GraphicsCommandList47 : public ID3D12GraphicsCommandList46 {
public:
    virtual void SetWorkGraphBackingMemory37(
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart,
        uint64_t RangeSizeInBytes,
        uint64_t ScratchBufferSizeInBytes,
        uint64_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t SparsityMask,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t NeuralExecutionEngineTier,
        uint32_t AdaptiveTensorCoreTier,
        uint32_t SovereignSiliconTelemetryTier,
        uint32_t QuantumEmulationTier,
        uint32_t Flags) = 0;

    virtual void DispatchGraphProgramRecord37(
        uint32_t NodeIndex,
        const void* pRecord,
        uint32_t RecordSizeInBytes,
        uint32_t ConcurrencyGroup,
        uint32_t QueueAffinityMask,
        uint32_t DynamicClusterExpansionTier,
        uint32_t TensorCoreMask,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t NeuralExecutionEngineTier,
        uint32_t AdaptiveTensorCoreTier,
        uint32_t SovereignSiliconTelemetryTier,
        uint32_t QuantumEmulationTier,
        uint32_t DispatchMask,
        uint32_t DispatchFlags) = 0;
};

inline constexpr IID OFFICIAL_IID_ID3D12GraphicsCommandList48 =
    { 0xbbf82f03, 0x8634, 0x7015, { 0xcb, 0x11, 0x8e, 0x44, 0x82, 0xd4, 0xe5, 0x4f } };
inline constexpr IID IID_ID3D12GraphicsCommandList48 = OFFICIAL_IID_ID3D12GraphicsCommandList48;

class ID3D12GraphicsCommandList48 : public ID3D12GraphicsCommandList47 {
public:
    virtual void SetWorkGraphBackingMemory38(
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart,
        uint64_t RangeSizeInBytes,
        uint64_t ScratchBufferSizeInBytes,
        uint64_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t SparsityMask,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t NeuralExecutionEngineTier,
        uint32_t AdaptiveTensorCoreTier,
        uint32_t SovereignSiliconTelemetryTier,
        uint32_t QuantumEmulationTier,
        uint32_t Flags) = 0;

    virtual void DispatchGraphProgramRecord38(
        uint32_t NodeIndex,
        const void* pRecord,
        uint32_t RecordSizeInBytes,
        uint32_t ConcurrencyGroup,
        uint32_t QueueAffinityMask,
        uint32_t DynamicClusterExpansionTier,
        uint32_t TensorCoreMask,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t NeuralExecutionEngineTier,
        uint32_t AdaptiveTensorCoreTier,
        uint32_t SovereignSiliconTelemetryTier,
        uint32_t QuantumEmulationTier,
        uint32_t DispatchMask,
        uint32_t DispatchFlags) = 0;
};

inline constexpr IID OFFICIAL_IID_ID3D12GraphicsCommandList49 =
    { 0xcc093014, 0x9745, 0x8126, { 0xdc, 0x22, 0x9f, 0x55, 0x93, 0xe5, 0xf6, 0x5a } };
inline constexpr IID IID_ID3D12GraphicsCommandList49 = OFFICIAL_IID_ID3D12GraphicsCommandList49;

class ID3D12GraphicsCommandList49 : public ID3D12GraphicsCommandList48 {
public:
    virtual void SetWorkGraphBackingMemory39(
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart,
        uint64_t RangeSizeInBytes,
        uint64_t ScratchBufferSizeInBytes,
        uint64_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t SparsityMask,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t NeuralExecutionEngineTier,
        uint32_t AdaptiveTensorCoreTier,
        uint32_t SovereignSiliconTelemetryTier,
        uint32_t QuantumEmulationTier,
        uint32_t Flags) = 0;

    virtual void DispatchGraphProgramRecord39(
        uint32_t NodeIndex,
        const void* pRecord,
        uint32_t RecordSizeInBytes,
        uint32_t ConcurrencyGroup,
        uint32_t QueueAffinityMask,
        uint32_t DynamicClusterExpansionTier,
        uint32_t TensorCoreMask,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t NeuralExecutionEngineTier,
        uint32_t AdaptiveTensorCoreTier,
        uint32_t SovereignSiliconTelemetryTier,
        uint32_t QuantumEmulationTier,
        uint32_t DispatchMask,
        uint32_t DispatchFlags) = 0;
};

inline constexpr IID OFFICIAL_IID_ID3D12GraphicsCommandList50 =
    { 0xdd104125, 0x0856, 0x9237, { 0xed, 0x33, 0x00, 0x66, 0x04, 0xf6, 0x07, 0x6b } };
inline constexpr IID IID_ID3D12GraphicsCommandList50 = OFFICIAL_IID_ID3D12GraphicsCommandList50;

class ID3D12GraphicsCommandList50 : public ID3D12GraphicsCommandList49 {
public:
    virtual void SetWorkGraphBackingMemory40(
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart,
        uint64_t RangeSizeInBytes,
        uint64_t ScratchBufferSizeInBytes,
        uint64_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t SparsityMask,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t NeuralExecutionEngineTier,
        uint32_t AdaptiveTensorCoreTier,
        uint32_t SovereignSiliconTelemetryTier,
        uint32_t QuantumEmulationTier,
        uint32_t Flags) = 0;

    virtual void DispatchGraphProgramRecord40(
        uint32_t NodeIndex,
        const void* pRecord,
        uint32_t RecordSizeInBytes,
        uint32_t ConcurrencyGroup,
        uint32_t QueueAffinityMask,
        uint32_t DynamicClusterExpansionTier,
        uint32_t TensorCoreMask,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t NeuralExecutionEngineTier,
        uint32_t AdaptiveTensorCoreTier,
        uint32_t SovereignSiliconTelemetryTier,
        uint32_t QuantumEmulationTier,
        uint32_t DispatchMask,
        uint32_t DispatchFlags) = 0;
};

inline constexpr IID OFFICIAL_IID_ID3D12GraphicsCommandList51 =
    { 0xee215236, 0x1967, 0xa348, { 0xfe, 0x44, 0x11, 0x77, 0x15, 0x07, 0x18, 0x7c } };
inline constexpr IID IID_ID3D12GraphicsCommandList51 = OFFICIAL_IID_ID3D12GraphicsCommandList51;

class ID3D12GraphicsCommandList51 : public ID3D12GraphicsCommandList50 {
public:
    virtual void SetWorkGraphBackingMemory41(
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart,
        uint64_t RangeSizeInBytes,
        uint64_t ScratchBufferSizeInBytes,
        uint64_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t SparsityMask,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t NeuralExecutionEngineTier,
        uint32_t AdaptiveTensorCoreTier,
        uint32_t SovereignSiliconTelemetryTier,
        uint32_t QuantumEmulationTier,
        uint32_t Flags) = 0;

    virtual void DispatchGraphProgramRecord41(
        uint32_t NodeIndex,
        const void* pRecord,
        uint32_t RecordSizeInBytes,
        uint32_t ConcurrencyGroup,
        uint32_t QueueAffinityMask,
        uint32_t DynamicClusterExpansionTier,
        uint32_t TensorCoreMask,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t NeuralExecutionEngineTier,
        uint32_t AdaptiveTensorCoreTier,
        uint32_t SovereignSiliconTelemetryTier,
        uint32_t QuantumEmulationTier,
        uint32_t DispatchMask,
        uint32_t DispatchFlags) = 0;
};

inline constexpr IID OFFICIAL_IID_ID3D12GraphicsCommandList52 =
    { 0xee215237, 0x1968, 0xa349, { 0xfe, 0x45, 0x11, 0x78, 0x15, 0x08, 0x18, 0x7d } };
inline constexpr IID IID_ID3D12GraphicsCommandList52 = OFFICIAL_IID_ID3D12GraphicsCommandList52;

class ID3D12GraphicsCommandList52 : public ID3D12GraphicsCommandList51 {
public:
    virtual void SetWorkGraphBackingMemory42(
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart,
        uint64_t RangeSizeInBytes,
        uint64_t ScratchBufferSizeInBytes,
        uint64_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t SparsityMask,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t NeuralExecutionEngineTier,
        uint32_t AdaptiveTensorCoreTier,
        uint32_t SovereignSiliconTelemetryTier,
        uint32_t QuantumEmulationTier,
        uint32_t Flags) = 0;

    virtual void DispatchGraphProgramRecord42(
        uint32_t NodeIndex,
        const void* pRecord,
        uint32_t RecordSizeInBytes,
        uint32_t ConcurrencyGroup,
        uint32_t QueueAffinityMask,
        uint32_t DynamicClusterExpansionTier,
        uint32_t TensorCoreMask,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t NeuralExecutionEngineTier,
        uint32_t AdaptiveTensorCoreTier,
        uint32_t SovereignSiliconTelemetryTier,
        uint32_t QuantumEmulationTier,
        uint32_t DispatchMask,
        uint32_t DispatchFlags) = 0;
};

inline constexpr IID OFFICIAL_IID_ID3D12GraphicsCommandList53 =
    { 0xee215238, 0x1969, 0xa34a, { 0xfe, 0x46, 0x11, 0x79, 0x15, 0x09, 0x18, 0x7e } };
inline constexpr IID IID_ID3D12GraphicsCommandList53 = OFFICIAL_IID_ID3D12GraphicsCommandList53;

class ID3D12GraphicsCommandList53 : public ID3D12GraphicsCommandList52 {
public:
    virtual void SetWorkGraphBackingMemory43(
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart,
        uint64_t RangeSizeInBytes,
        uint64_t ScratchBufferSizeInBytes,
        uint64_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t SparsityMask,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t NeuralExecutionEngineTier,
        uint32_t AdaptiveTensorCoreTier,
        uint32_t SovereignSiliconTelemetryTier,
        uint32_t QuantumEmulationTier,
        uint32_t Flags) = 0;

    virtual void DispatchGraphProgramRecord43(
        uint32_t NodeIndex,
        const void* pRecord,
        uint32_t RecordSizeInBytes,
        uint32_t ConcurrencyGroup,
        uint32_t QueueAffinityMask,
        uint32_t DynamicClusterExpansionTier,
        uint32_t TensorCoreMask,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t NeuralExecutionEngineTier,
        uint32_t AdaptiveTensorCoreTier,
        uint32_t SovereignSiliconTelemetryTier,
        uint32_t QuantumEmulationTier,
        uint32_t DispatchMask,
        uint32_t DispatchFlags) = 0;
};

inline constexpr IID OFFICIAL_IID_ID3D12GraphicsCommandList54 =
    { 0xee215239, 0x196a, 0xa34b, { 0xfe, 0x47, 0x11, 0x7a, 0x15, 0x0a, 0x18, 0x7f } };
inline constexpr IID IID_ID3D12GraphicsCommandList54 = OFFICIAL_IID_ID3D12GraphicsCommandList54;

class ID3D12GraphicsCommandList54 : public ID3D12GraphicsCommandList53 {
public:
    virtual void SetWorkGraphBackingMemory44(
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart,
        uint64_t RangeSizeInBytes,
        uint64_t ScratchBufferSizeInBytes,
        uint64_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t SparsityMask,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t NeuralExecutionEngineTier,
        uint32_t AdaptiveTensorCoreTier,
        uint32_t SovereignSiliconTelemetryTier,
        uint32_t QuantumEmulationTier,
        uint32_t Flags) = 0;

    virtual void DispatchGraphProgramRecord44(
        uint32_t NodeIndex,
        const void* pRecord,
        uint32_t RecordSizeInBytes,
        uint32_t ConcurrencyGroup,
        uint32_t QueueAffinityMask,
        uint32_t DynamicClusterExpansionTier,
        uint32_t TensorCoreMask,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t NeuralExecutionEngineTier,
        uint32_t AdaptiveTensorCoreTier,
        uint32_t SovereignSiliconTelemetryTier,
        uint32_t QuantumEmulationTier,
        uint32_t DispatchMask,
        uint32_t DispatchFlags) = 0;
};

// ============================================================================
// 4. Concrete Implementation: Prism3D12GraphicsCommandList7Impl
// ============================================================================

class Prism3D12GraphicsCommandList7Impl : public ID3D12GraphicsCommandList54 {
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

    struct BackingMemory7Record {
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart{ 0 };
        uint64_t RangeSizeInBytes{ 0 };
        uint64_t ScratchBufferSizeInBytes{ 0 };
        uint32_t MaxConcurrency{ 0 };
        uint32_t DynamicExpansionFlags{ 0 };
        uint32_t MemoryPoolTier{ 0 };
        uint32_t Flags{ 0 };
    };
    BackingMemory7Record m_backingMemory7{};

    struct ProgramRecord7Entry {
        uint32_t NodeIndex{ 0 };
        const void* pRecord{ nullptr };
        uint32_t RecordSizeInBytes{ 0 };
        uint32_t ConcurrencyGroup{ 0 };
        uint32_t QueueAffinityMask{ 0 };
        uint32_t DynamicClusterExpansionTier{ 0 };
        uint32_t DispatchMask{ 0 };
        uint32_t DispatchFlags{ 0 };
    };
    std::vector<ProgramRecord7Entry> m_recordedProgramRecords7;

    struct BackingMemory8Record {
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart{ 0 };
        uint64_t RangeSizeInBytes{ 0 };
        uint64_t ScratchBufferSizeInBytes{ 0 };
        uint32_t MaxConcurrency{ 0 };
        uint32_t DynamicExpansionFlags{ 0 };
        uint32_t MemoryPoolTier{ 0 };
        uint32_t SparsityMask{ 0 };
        uint32_t Flags{ 0 };
    };
    BackingMemory8Record m_backingMemory8{};

    struct ProgramRecord8Entry {
        uint32_t NodeIndex{ 0 };
        const void* pRecord{ nullptr };
        uint32_t RecordSizeInBytes{ 0 };
        uint32_t ConcurrencyGroup{ 0 };
        uint32_t QueueAffinityMask{ 0 };
        uint32_t DynamicClusterExpansionTier{ 0 };
        uint32_t TensorCoreMask{ 0 };
        uint32_t DispatchMask{ 0 };
        uint32_t DispatchFlags{ 0 };
    };
    std::vector<ProgramRecord8Entry> m_recordedProgramRecords8;

    struct BackingMemory9Record {
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart{ 0 };
        uint64_t RangeSizeInBytes{ 0 };
        uint64_t ScratchBufferSizeInBytes{ 0 };
        uint32_t MaxConcurrency{ 0 };
        uint32_t DynamicExpansionFlags{ 0 };
        uint32_t MemoryPoolTier{ 0 };
        uint32_t SparsityMask{ 0 };
        uint32_t SubAllocationMask{ 0 };
        uint32_t Flags{ 0 };
    };
    BackingMemory9Record m_backingMemory9{};

    struct ProgramRecord9Entry {
        uint32_t NodeIndex{ 0 };
        const void* pRecord{ nullptr };
        uint32_t RecordSizeInBytes{ 0 };
        uint32_t ConcurrencyGroup{ 0 };
        uint32_t QueueAffinityMask{ 0 };
        uint32_t DynamicClusterExpansionTier{ 0 };
        uint32_t TensorCoreMask{ 0 };
        uint32_t SubAllocationMask{ 0 };
        uint32_t DispatchMask{ 0 };
        uint32_t DispatchFlags{ 0 };
    };
    std::vector<ProgramRecord9Entry> m_recordedProgramRecords9;

    struct BackingMemory10Record {
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart{ 0 };
        uint64_t RangeSizeInBytes{ 0 };
        uint64_t ScratchBufferSizeInBytes{ 0 };
        uint32_t MaxConcurrency{ 0 };
        uint32_t DynamicExpansionFlags{ 0 };
        uint32_t MemoryPoolTier{ 0 };
        uint32_t SparsityMask{ 0 };
        uint32_t SubAllocationMask{ 0 };
        uint32_t PipelineCoherencyTier{ 0 };
        uint32_t Flags{ 0 };
    };
    BackingMemory10Record m_backingMemory10{};

    struct ProgramRecord10Entry {
        uint32_t NodeIndex{ 0 };
        const void* pRecord{ nullptr };
        uint32_t RecordSizeInBytes{ 0 };
        uint32_t ConcurrencyGroup{ 0 };
        uint32_t QueueAffinityMask{ 0 };
        uint32_t DynamicClusterExpansionTier{ 0 };
        uint32_t TensorCoreMask{ 0 };
        uint32_t SubAllocationMask{ 0 };
        uint32_t PipelineCoherencyTier{ 0 };
        uint32_t DispatchMask{ 0 };
        uint32_t DispatchFlags{ 0 };
    };
    std::vector<ProgramRecord10Entry> m_recordedProgramRecords10;

    struct BackingMemory11Record {
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart{ 0 };
        uint64_t RangeSizeInBytes{ 0 };
        uint64_t ScratchBufferSizeInBytes{ 0 };
        uint32_t MaxConcurrency{ 0 };
        uint32_t DynamicExpansionFlags{ 0 };
        uint32_t MemoryPoolTier{ 0 };
        uint32_t SparsityMask{ 0 };
        uint32_t SubAllocationMask{ 0 };
        uint32_t PipelineCoherencyTier{ 0 };
        uint32_t FeedbackLoopTier{ 0 };
        uint32_t Flags{ 0 };
    };
    BackingMemory11Record m_backingMemory11{};

    struct ProgramRecord11Entry {
        uint32_t NodeIndex{ 0 };
        const void* pRecord{ nullptr };
        uint32_t RecordSizeInBytes{ 0 };
        uint32_t ConcurrencyGroup{ 0 };
        uint32_t QueueAffinityMask{ 0 };
        uint32_t DynamicClusterExpansionTier{ 0 };
        uint32_t TensorCoreMask{ 0 };
        uint32_t SubAllocationMask{ 0 };
        uint32_t PipelineCoherencyTier{ 0 };
        uint32_t FeedbackLoopTier{ 0 };
        uint32_t DispatchMask{ 0 };
        uint32_t DispatchFlags{ 0 };
    };
    std::vector<ProgramRecord11Entry> m_recordedProgramRecords11;

    struct BackingMemory12Record {
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart{ 0 };
        uint64_t RangeSizeInBytes{ 0 };
        uint64_t ScratchBufferSizeInBytes{ 0 };
        uint32_t MaxConcurrency{ 0 };
        uint32_t DynamicExpansionFlags{ 0 };
        uint32_t MemoryPoolTier{ 0 };
        uint32_t SparsityMask{ 0 };
        uint32_t SubAllocationMask{ 0 };
        uint32_t PipelineCoherencyTier{ 0 };
        uint32_t FeedbackLoopTier{ 0 };
        uint32_t SubGraphRecursionTier{ 0 };
        uint32_t Flags{ 0 };
    };
    BackingMemory12Record m_backingMemory12{};

    struct ProgramRecord12Entry {
        uint32_t NodeIndex{ 0 };
        const void* pRecord{ nullptr };
        uint32_t RecordSizeInBytes{ 0 };
        uint32_t ConcurrencyGroup{ 0 };
        uint32_t QueueAffinityMask{ 0 };
        uint32_t DynamicClusterExpansionTier{ 0 };
        uint32_t TensorCoreMask{ 0 };
        uint32_t SubAllocationMask{ 0 };
        uint32_t PipelineCoherencyTier{ 0 };
        uint32_t FeedbackLoopTier{ 0 };
        uint32_t SubGraphRecursionTier{ 0 };
        uint32_t DispatchMask{ 0 };
        uint32_t DispatchFlags{ 0 };
    };
    std::vector<ProgramRecord12Entry> m_recordedProgramRecords12;

    struct BackingMemory13Record {
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart{ 0 };
        uint64_t RangeSizeInBytes{ 0 };
        uint64_t ScratchBufferSizeInBytes{ 0 };
        uint32_t MaxConcurrency{ 0 };
        uint32_t DynamicExpansionFlags{ 0 };
        uint32_t MemoryPoolTier{ 0 };
        uint32_t SparsityMask{ 0 };
        uint32_t SubAllocationMask{ 0 };
        uint32_t PipelineCoherencyTier{ 0 };
        uint32_t FeedbackLoopTier{ 0 };
        uint32_t SubGraphRecursionTier{ 0 };
        uint32_t MeshPipeliningTier{ 0 };
        uint32_t Flags{ 0 };
    };
    BackingMemory13Record m_backingMemory13{};

    struct ProgramRecord13Entry {
        uint32_t NodeIndex{ 0 };
        const void* pRecord{ nullptr };
        uint32_t RecordSizeInBytes{ 0 };
        uint32_t ConcurrencyGroup{ 0 };
        uint32_t QueueAffinityMask{ 0 };
        uint32_t DynamicClusterExpansionTier{ 0 };
        uint32_t TensorCoreMask{ 0 };
        uint32_t SubAllocationMask{ 0 };
        uint32_t PipelineCoherencyTier{ 0 };
        uint32_t FeedbackLoopTier{ 0 };
        uint32_t SubGraphRecursionTier{ 0 };
        uint32_t MeshPipeliningTier{ 0 };
        uint32_t DispatchMask{ 0 };
        uint32_t DispatchFlags{ 0 };
    };
    std::vector<ProgramRecord13Entry> m_recordedProgramRecords13;

    struct BackingMemory14Record {
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart{ 0 };
        uint64_t RangeSizeInBytes{ 0 };
        uint64_t ScratchBufferSizeInBytes{ 0 };
        uint32_t MaxConcurrency{ 0 };
        uint32_t DynamicExpansionFlags{ 0 };
        uint32_t MemoryPoolTier{ 0 };
        uint32_t SparsityMask{ 0 };
        uint32_t SubAllocationMask{ 0 };
        uint32_t PipelineCoherencyTier{ 0 };
        uint32_t FeedbackLoopTier{ 0 };
        uint32_t SubGraphRecursionTier{ 0 };
        uint32_t MeshPipeliningTier{ 0 };
        uint32_t MultiQueueFusionTier{ 0 };
        uint32_t Flags{ 0 };
    };
    BackingMemory14Record m_backingMemory14{};

    struct ProgramRecord14Entry {
        uint32_t NodeIndex{ 0 };
        const void* pRecord{ nullptr };
        uint32_t RecordSizeInBytes{ 0 };
        uint32_t ConcurrencyGroup{ 0 };
        uint32_t QueueAffinityMask{ 0 };
        uint32_t DynamicClusterExpansionTier{ 0 };
        uint32_t TensorCoreMask{ 0 };
        uint32_t SubAllocationMask{ 0 };
        uint32_t PipelineCoherencyTier{ 0 };
        uint32_t FeedbackLoopTier{ 0 };
        uint32_t SubGraphRecursionTier{ 0 };
        uint32_t MeshPipeliningTier{ 0 };
        uint32_t MultiQueueFusionTier{ 0 };
        uint32_t DispatchMask{ 0 };
        uint32_t DispatchFlags{ 0 };
    };
    std::vector<ProgramRecord14Entry> m_recordedProgramRecords14;
    struct BackingMemory15Record {
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart{ 0 };
        uint64_t RangeSizeInBytes{ 0 };
        uint64_t ScratchBufferSizeInBytes{ 0 };
        uint32_t MaxConcurrency{ 0 };
        uint32_t DynamicExpansionFlags{ 0 };
        uint32_t MemoryPoolTier{ 0 };
        uint32_t SparsityMask{ 0 };
        uint32_t SubAllocationMask{ 0 };
        uint32_t PipelineCoherencyTier{ 0 };
        uint32_t FeedbackLoopTier{ 0 };
        uint32_t SubGraphRecursionTier{ 0 };
        uint32_t MeshPipeliningTier{ 0 };
        uint32_t MultiQueueFusionTier{ 0 };
        uint32_t MicroscalingTier{ 0 };
        uint32_t Flags{ 0 };
    };
    BackingMemory15Record m_backingMemory15{};

    struct ProgramRecord15Entry {
        uint32_t NodeIndex{ 0 };
        const void* pRecord{ nullptr };
        uint32_t RecordSizeInBytes{ 0 };
        uint32_t ConcurrencyGroup{ 0 };
        uint32_t QueueAffinityMask{ 0 };
        uint32_t DynamicClusterExpansionTier{ 0 };
        uint32_t TensorCoreMask{ 0 };
        uint32_t SubAllocationMask{ 0 };
        uint32_t PipelineCoherencyTier{ 0 };
        uint32_t FeedbackLoopTier{ 0 };
        uint32_t SubGraphRecursionTier{ 0 };
        uint32_t MeshPipeliningTier{ 0 };
        uint32_t MultiQueueFusionTier{ 0 };
        uint32_t MicroscalingTier{ 0 };
        uint32_t DispatchMask{ 0 };
        uint32_t DispatchFlags{ 0 };
    };
    std::vector<ProgramRecord15Entry> m_recordedProgramRecords15;

    struct BackingMemory16Record {
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart{ 0 };
        uint64_t RangeSizeInBytes{ 0 };
        uint64_t ScratchBufferSizeInBytes{ 0 };
        uint32_t MaxConcurrency{ 0 };
        uint32_t DynamicExpansionFlags{ 0 };
        uint32_t MemoryPoolTier{ 0 };
        uint32_t SparsityMask{ 0 };
        uint32_t SubAllocationMask{ 0 };
        uint32_t PipelineCoherencyTier{ 0 };
        uint32_t FeedbackLoopTier{ 0 };
        uint32_t SubGraphRecursionTier{ 0 };
        uint32_t MeshPipeliningTier{ 0 };
        uint32_t MultiQueueFusionTier{ 0 };
        uint32_t MicroscalingTier{ 0 };
        uint32_t SubBytePrecisionTier{ 0 };
        uint32_t Flags{ 0 };
    };
    BackingMemory16Record m_backingMemory16{};

    struct ProgramRecord16Entry {
        uint32_t NodeIndex{ 0 };
        const void* pRecord{ nullptr };
        uint32_t RecordSizeInBytes{ 0 };
        uint32_t ConcurrencyGroup{ 0 };
        uint32_t QueueAffinityMask{ 0 };
        uint32_t DynamicClusterExpansionTier{ 0 };
        uint32_t TensorCoreMask{ 0 };
        uint32_t SubAllocationMask{ 0 };
        uint32_t PipelineCoherencyTier{ 0 };
        uint32_t FeedbackLoopTier{ 0 };
        uint32_t SubGraphRecursionTier{ 0 };
        uint32_t MeshPipeliningTier{ 0 };
        uint32_t MultiQueueFusionTier{ 0 };
        uint32_t MicroscalingTier{ 0 };
        uint32_t SubBytePrecisionTier{ 0 };
        uint32_t DispatchMask{ 0 };
        uint32_t DispatchFlags{ 0 };
    };
    std::vector<ProgramRecord16Entry> m_recordedProgramRecords16;

    struct BackingMemory17Record {
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart{ 0 };
        uint64_t RangeSizeInBytes{ 0 };
        uint64_t ScratchBufferSizeInBytes{ 0 };
        uint32_t MaxConcurrency{ 0 };
        uint32_t DynamicExpansionFlags{ 0 };
        uint32_t MemoryPoolTier{ 0 };
        uint32_t SparsityMask{ 0 };
        uint32_t SubAllocationMask{ 0 };
        uint32_t PipelineCoherencyTier{ 0 };
        uint32_t FeedbackLoopTier{ 0 };
        uint32_t SubGraphRecursionTier{ 0 };
        uint32_t MeshPipeliningTier{ 0 };
        uint32_t MultiQueueFusionTier{ 0 };
        uint32_t MicroscalingTier{ 0 };
        uint32_t SubBytePrecisionTier{ 0 };
        uint32_t SparseTensorBlockTier{ 0 };
        uint32_t Flags{ 0 };
    };
    BackingMemory17Record m_backingMemory17{};

    struct ProgramRecord17Entry {
        uint32_t NodeIndex{ 0 };
        const void* pRecord{ nullptr };
        uint32_t RecordSizeInBytes{ 0 };
        uint32_t ConcurrencyGroup{ 0 };
        uint32_t QueueAffinityMask{ 0 };
        uint32_t DynamicClusterExpansionTier{ 0 };
        uint32_t TensorCoreMask{ 0 };
        uint32_t SubAllocationMask{ 0 };
        uint32_t PipelineCoherencyTier{ 0 };
        uint32_t FeedbackLoopTier{ 0 };
        uint32_t SubGraphRecursionTier{ 0 };
        uint32_t MeshPipeliningTier{ 0 };
        uint32_t MultiQueueFusionTier{ 0 };
        uint32_t MicroscalingTier{ 0 };
        uint32_t SubBytePrecisionTier{ 0 };
        uint32_t SparseTensorBlockTier{ 0 };
        uint32_t DispatchMask{ 0 };
        uint32_t DispatchFlags{ 0 };
    };
    std::vector<ProgramRecord17Entry> m_recordedProgramRecords17;

    struct BackingMemory18Record {
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart{ 0 };
        uint64_t RangeSizeInBytes{ 0 };
        uint64_t ScratchBufferSizeInBytes{ 0 };
        uint32_t MaxConcurrency{ 0 };
        uint32_t DynamicExpansionFlags{ 0 };
        uint32_t MemoryPoolTier{ 0 };
        uint32_t SparsityMask{ 0 };
        uint32_t SubAllocationMask{ 0 };
        uint32_t PipelineCoherencyTier{ 0 };
        uint32_t FeedbackLoopTier{ 0 };
        uint32_t SubGraphRecursionTier{ 0 };
        uint32_t MeshPipeliningTier{ 0 };
        uint32_t MultiQueueFusionTier{ 0 };
        uint32_t MicroscalingTier{ 0 };
        uint32_t SubBytePrecisionTier{ 0 };
        uint32_t SparseTensorBlockTier{ 0 };
        uint32_t DeterministicTensorReductionTier{ 0 };
        uint32_t Flags{ 0 };
    };
    BackingMemory18Record m_backingMemory18{};

    struct ProgramRecord18Entry {
        uint32_t NodeIndex{ 0 };
        const void* pRecord{ nullptr };
        uint32_t RecordSizeInBytes{ 0 };
        uint32_t ConcurrencyGroup{ 0 };
        uint32_t QueueAffinityMask{ 0 };
        uint32_t DynamicClusterExpansionTier{ 0 };
        uint32_t TensorCoreMask{ 0 };
        uint32_t SubAllocationMask{ 0 };
        uint32_t PipelineCoherencyTier{ 0 };
        uint32_t FeedbackLoopTier{ 0 };
        uint32_t SubGraphRecursionTier{ 0 };
        uint32_t MeshPipeliningTier{ 0 };
        uint32_t MultiQueueFusionTier{ 0 };
        uint32_t MicroscalingTier{ 0 };
        uint32_t SubBytePrecisionTier{ 0 };
        uint32_t SparseTensorBlockTier{ 0 };
        uint32_t DeterministicTensorReductionTier{ 0 };
        uint32_t DispatchMask{ 0 };
        uint32_t DispatchFlags{ 0 };
    };
    std::vector<ProgramRecord18Entry> m_recordedProgramRecords18;

    struct BackingMemory19Record {
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart{ 0 };
        uint64_t RangeSizeInBytes{ 0 };
        uint64_t ScratchBufferSizeInBytes{ 0 };
        uint32_t MaxConcurrency{ 0 };
        uint32_t DynamicExpansionFlags{ 0 };
        uint32_t MemoryPoolTier{ 0 };
        uint32_t SparsityMask{ 0 };
        uint32_t SubAllocationMask{ 0 };
        uint32_t PipelineCoherencyTier{ 0 };
        uint32_t FeedbackLoopTier{ 0 };
        uint32_t SubGraphRecursionTier{ 0 };
        uint32_t MeshPipeliningTier{ 0 };
        uint32_t MultiQueueFusionTier{ 0 };
        uint32_t MicroscalingTier{ 0 };
        uint32_t SubBytePrecisionTier{ 0 };
        uint32_t SparseTensorBlockTier{ 0 };
        uint32_t DeterministicTensorReductionTier{ 0 };
        uint32_t HyperQuantizationTier{ 0 };
        uint32_t Flags{ 0 };
    };
    BackingMemory19Record m_backingMemory19{};

    struct ProgramRecord19Entry {
        uint32_t NodeIndex{ 0 };
        const void* pRecord{ nullptr };
        uint32_t RecordSizeInBytes{ 0 };
        uint32_t ConcurrencyGroup{ 0 };
        uint32_t QueueAffinityMask{ 0 };
        uint32_t DynamicClusterExpansionTier{ 0 };
        uint32_t TensorCoreMask{ 0 };
        uint32_t SubAllocationMask{ 0 };
        uint32_t PipelineCoherencyTier{ 0 };
        uint32_t FeedbackLoopTier{ 0 };
        uint32_t SubGraphRecursionTier{ 0 };
        uint32_t MeshPipeliningTier{ 0 };
        uint32_t MultiQueueFusionTier{ 0 };
        uint32_t MicroscalingTier{ 0 };
        uint32_t SubBytePrecisionTier{ 0 };
        uint32_t SparseTensorBlockTier{ 0 };
        uint32_t DeterministicTensorReductionTier{ 0 };
        uint32_t HyperQuantizationTier{ 0 };
        uint32_t DispatchMask{ 0 };
        uint32_t DispatchFlags{ 0 };
    };
    std::vector<ProgramRecord19Entry> m_recordedProgramRecords19;

    struct BackingMemory20Record {
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart{ 0 };
        uint64_t RangeSizeInBytes{ 0 };
        uint64_t ScratchBufferSizeInBytes{ 0 };
        uint32_t MaxConcurrency{ 0 };
        uint32_t DynamicExpansionFlags{ 0 };
        uint32_t MemoryPoolTier{ 0 };
        uint32_t SparsityMask{ 0 };
        uint32_t SubAllocationMask{ 0 };
        uint32_t PipelineCoherencyTier{ 0 };
        uint32_t FeedbackLoopTier{ 0 };
        uint32_t SubGraphRecursionTier{ 0 };
        uint32_t MeshPipeliningTier{ 0 };
        uint32_t MultiQueueFusionTier{ 0 };
        uint32_t MicroscalingTier{ 0 };
        uint32_t SubBytePrecisionTier{ 0 };
        uint32_t SparseTensorBlockTier{ 0 };
        uint32_t DeterministicTensorReductionTier{ 0 };
        uint32_t HyperQuantizationTier{ 0 };
        uint32_t SparseClusterTier{ 0 };
        uint32_t Flags{ 0 };
    };
    BackingMemory20Record m_backingMemory20{};

    struct ProgramRecord20Entry {
        uint32_t NodeIndex{ 0 };
        const void* pRecord{ nullptr };
        uint32_t RecordSizeInBytes{ 0 };
        uint32_t ConcurrencyGroup{ 0 };
        uint32_t QueueAffinityMask{ 0 };
        uint32_t DynamicClusterExpansionTier{ 0 };
        uint32_t TensorCoreMask{ 0 };
        uint32_t SubAllocationMask{ 0 };
        uint32_t PipelineCoherencyTier{ 0 };
        uint32_t FeedbackLoopTier{ 0 };
        uint32_t SubGraphRecursionTier{ 0 };
        uint32_t MeshPipeliningTier{ 0 };
        uint32_t MultiQueueFusionTier{ 0 };
        uint32_t MicroscalingTier{ 0 };
        uint32_t SubBytePrecisionTier{ 0 };
        uint32_t SparseTensorBlockTier{ 0 };
        uint32_t DeterministicTensorReductionTier{ 0 };
        uint32_t HyperQuantizationTier{ 0 };
        uint32_t SparseClusterTier{ 0 };
        uint32_t DispatchMask{ 0 };
        uint32_t DispatchFlags{ 0 };
    };
    std::vector<ProgramRecord20Entry> m_recordedProgramRecords20;

    struct BackingMemory21Record {
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart{ 0 };
        uint64_t RangeSizeInBytes{ 0 };
        uint64_t ScratchBufferSizeInBytes{ 0 };
        uint32_t MaxConcurrency{ 0 };
        uint32_t DynamicExpansionFlags{ 0 };
        uint32_t MemoryPoolTier{ 0 };
        uint32_t SparsityMask{ 0 };
        uint32_t SubAllocationMask{ 0 };
        uint32_t PipelineCoherencyTier{ 0 };
        uint32_t FeedbackLoopTier{ 0 };
        uint32_t SubGraphRecursionTier{ 0 };
        uint32_t MeshPipeliningTier{ 0 };
        uint32_t MultiQueueFusionTier{ 0 };
        uint32_t MicroscalingTier{ 0 };
        uint32_t SubBytePrecisionTier{ 0 };
        uint32_t SparseTensorBlockTier{ 0 };
        uint32_t DeterministicTensorReductionTier{ 0 };
        uint32_t HyperQuantizationTier{ 0 };
        uint32_t SparseClusterTier{ 0 };
        uint32_t MultiQueueSyncTier{ 0 };
        uint32_t Flags{ 0 };
    };
    BackingMemory21Record m_backingMemory21{};

    struct ProgramRecord21Entry {
        uint32_t NodeIndex{ 0 };
        const void* pRecord{ nullptr };
        uint32_t RecordSizeInBytes{ 0 };
        uint32_t ConcurrencyGroup{ 0 };
        uint32_t QueueAffinityMask{ 0 };
        uint32_t DynamicClusterExpansionTier{ 0 };
        uint32_t TensorCoreMask{ 0 };
        uint32_t SubAllocationMask{ 0 };
        uint32_t PipelineCoherencyTier{ 0 };
        uint32_t FeedbackLoopTier{ 0 };
        uint32_t SubGraphRecursionTier{ 0 };
        uint32_t MeshPipeliningTier{ 0 };
        uint32_t MultiQueueFusionTier{ 0 };
        uint32_t MicroscalingTier{ 0 };
        uint32_t SubBytePrecisionTier{ 0 };
        uint32_t SparseTensorBlockTier{ 0 };
        uint32_t DeterministicTensorReductionTier{ 0 };
        uint32_t HyperQuantizationTier{ 0 };
        uint32_t SparseClusterTier{ 0 };
        uint32_t MultiQueueSyncTier{ 0 };
        uint32_t DispatchMask{ 0 };
        uint32_t DispatchFlags{ 0 };
    };
    std::vector<ProgramRecord21Entry> m_recordedProgramRecords21;

    struct BackingMemory22Record {
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart{ 0 };
        uint64_t RangeSizeInBytes{ 0 };
        uint64_t ScratchBufferSizeInBytes{ 0 };
        uint32_t MaxConcurrency{ 0 };
        uint32_t DynamicExpansionFlags{ 0 };
        uint32_t MemoryPoolTier{ 0 };
        uint32_t SparsityMask{ 0 };
        uint32_t SubAllocationMask{ 0 };
        uint32_t PipelineCoherencyTier{ 0 };
        uint32_t FeedbackLoopTier{ 0 };
        uint32_t SubGraphRecursionTier{ 0 };
        uint32_t MeshPipeliningTier{ 0 };
        uint32_t MultiQueueFusionTier{ 0 };
        uint32_t MicroscalingTier{ 0 };
        uint32_t SubBytePrecisionTier{ 0 };
        uint32_t SparseTensorBlockTier{ 0 };
        uint32_t DeterministicTensorReductionTier{ 0 };
        uint32_t HyperQuantizationTier{ 0 };
        uint32_t SparseClusterTier{ 0 };
        uint32_t MultiQueueSyncTier{ 0 };
        uint32_t AsyncKernelDispatchTier{ 0 };
        uint32_t Flags{ 0 };
    };
    BackingMemory22Record m_backingMemory22{};

    struct ProgramRecord22Entry {
        uint32_t NodeIndex{ 0 };
        const void* pRecord{ nullptr };
        uint32_t RecordSizeInBytes{ 0 };
        uint32_t ConcurrencyGroup{ 0 };
        uint32_t QueueAffinityMask{ 0 };
        uint32_t DynamicClusterExpansionTier{ 0 };
        uint32_t TensorCoreMask{ 0 };
        uint32_t SubAllocationMask{ 0 };
        uint32_t PipelineCoherencyTier{ 0 };
        uint32_t FeedbackLoopTier{ 0 };
        uint32_t SubGraphRecursionTier{ 0 };
        uint32_t MeshPipeliningTier{ 0 };
        uint32_t MultiQueueFusionTier{ 0 };
        uint32_t MicroscalingTier{ 0 };
        uint32_t SubBytePrecisionTier{ 0 };
        uint32_t SparseTensorBlockTier{ 0 };
        uint32_t DeterministicTensorReductionTier{ 0 };
        uint32_t HyperQuantizationTier{ 0 };
        uint32_t SparseClusterTier{ 0 };
        uint32_t MultiQueueSyncTier{ 0 };
        uint32_t AsyncKernelDispatchTier{ 0 };
        uint32_t DispatchMask{ 0 };
        uint32_t DispatchFlags{ 0 };
    };
    std::vector<ProgramRecord22Entry> m_recordedProgramRecords22;

    struct BackingMemory23Record {
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart{ 0 };
        uint64_t RangeSizeInBytes{ 0 };
        uint64_t ScratchBufferSizeInBytes{ 0 };
        uint32_t MaxConcurrency{ 0 };
        uint32_t DynamicExpansionFlags{ 0 };
        uint32_t MemoryPoolTier{ 0 };
        uint32_t SparsityMask{ 0 };
        uint32_t SubAllocationMask{ 0 };
        uint32_t PipelineCoherencyTier{ 0 };
        uint32_t FeedbackLoopTier{ 0 };
        uint32_t SubGraphRecursionTier{ 0 };
        uint32_t MeshPipeliningTier{ 0 };
        uint32_t MultiQueueFusionTier{ 0 };
        uint32_t MicroscalingTier{ 0 };
        uint32_t SubBytePrecisionTier{ 0 };
        uint32_t SparseTensorBlockTier{ 0 };
        uint32_t DeterministicTensorReductionTier{ 0 };
        uint32_t HyperQuantizationTier{ 0 };
        uint32_t SparseClusterTier{ 0 };
        uint32_t MultiQueueSyncTier{ 0 };
        uint32_t AsyncKernelDispatchTier{ 0 };
        uint32_t NeuralExecutionEngineTier{ 0 };
        uint32_t Flags{ 0 };
    };
    BackingMemory23Record m_backingMemory23{};

    struct ProgramRecord23Entry {
        uint32_t NodeIndex{ 0 };
        const void* pRecord{ nullptr };
        uint32_t RecordSizeInBytes{ 0 };
        uint32_t ConcurrencyGroup{ 0 };
        uint32_t QueueAffinityMask{ 0 };
        uint32_t DynamicClusterExpansionTier{ 0 };
        uint32_t TensorCoreMask{ 0 };
        uint32_t SubAllocationMask{ 0 };
        uint32_t PipelineCoherencyTier{ 0 };
        uint32_t FeedbackLoopTier{ 0 };
        uint32_t SubGraphRecursionTier{ 0 };
        uint32_t MeshPipeliningTier{ 0 };
        uint32_t MultiQueueFusionTier{ 0 };
        uint32_t MicroscalingTier{ 0 };
        uint32_t SubBytePrecisionTier{ 0 };
        uint32_t SparseTensorBlockTier{ 0 };
        uint32_t DeterministicTensorReductionTier{ 0 };
        uint32_t HyperQuantizationTier{ 0 };
        uint32_t SparseClusterTier{ 0 };
        uint32_t MultiQueueSyncTier{ 0 };
        uint32_t AsyncKernelDispatchTier{ 0 };
        uint32_t NeuralExecutionEngineTier{ 0 };
        uint32_t DispatchMask{ 0 };
        uint32_t DispatchFlags{ 0 };
    };
    std::vector<ProgramRecord23Entry> m_recordedProgramRecords23;

    struct BackingMemory24Record {
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart{ 0 };
        uint64_t RangeSizeInBytes{ 0 };
        uint64_t ScratchBufferSizeInBytes{ 0 };
        uint32_t MaxConcurrency{ 0 };
        uint32_t DynamicExpansionFlags{ 0 };
        uint32_t MemoryPoolTier{ 0 };
        uint32_t SparsityMask{ 0 };
        uint32_t SubAllocationMask{ 0 };
        uint32_t PipelineCoherencyTier{ 0 };
        uint32_t FeedbackLoopTier{ 0 };
        uint32_t SubGraphRecursionTier{ 0 };
        uint32_t MeshPipeliningTier{ 0 };
        uint32_t MultiQueueFusionTier{ 0 };
        uint32_t MicroscalingTier{ 0 };
        uint32_t SubBytePrecisionTier{ 0 };
        uint32_t SparseTensorBlockTier{ 0 };
        uint32_t DeterministicTensorReductionTier{ 0 };
        uint32_t HyperQuantizationTier{ 0 };
        uint32_t SparseClusterTier{ 0 };
        uint32_t MultiQueueSyncTier{ 0 };
        uint32_t AsyncKernelDispatchTier{ 0 };
        uint32_t NeuralExecutionEngineTier{ 0 };
        uint32_t AdaptiveTensorCoreTier{ 0 };
        uint32_t Flags{ 0 };
    };
    BackingMemory24Record m_backingMemory24{};

    struct ProgramRecord24Entry {
        uint32_t NodeIndex{ 0 };
        const void* pRecord{ nullptr };
        uint32_t RecordSizeInBytes{ 0 };
        uint32_t ConcurrencyGroup{ 0 };
        uint32_t QueueAffinityMask{ 0 };
        uint32_t DynamicClusterExpansionTier{ 0 };
        uint32_t TensorCoreMask{ 0 };
        uint32_t SubAllocationMask{ 0 };
        uint32_t PipelineCoherencyTier{ 0 };
        uint32_t FeedbackLoopTier{ 0 };
        uint32_t SubGraphRecursionTier{ 0 };
        uint32_t MeshPipeliningTier{ 0 };
        uint32_t MultiQueueFusionTier{ 0 };
        uint32_t MicroscalingTier{ 0 };
        uint32_t SubBytePrecisionTier{ 0 };
        uint32_t SparseTensorBlockTier{ 0 };
        uint32_t DeterministicTensorReductionTier{ 0 };
        uint32_t HyperQuantizationTier{ 0 };
        uint32_t SparseClusterTier{ 0 };
        uint32_t MultiQueueSyncTier{ 0 };
        uint32_t AsyncKernelDispatchTier{ 0 };
        uint32_t NeuralExecutionEngineTier{ 0 };
        uint32_t AdaptiveTensorCoreTier{ 0 };
        uint32_t DispatchMask{ 0 };
        uint32_t DispatchFlags{ 0 };
    };
    std::vector<ProgramRecord24Entry> m_recordedProgramRecords24;

    struct BackingMemory25Record {
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart{ 0 };
        uint64_t RangeSizeInBytes{ 0 };
        uint64_t ScratchBufferSizeInBytes{ 0 };
        uint32_t MaxConcurrency{ 0 };
        uint32_t DynamicExpansionFlags{ 0 };
        uint32_t MemoryPoolTier{ 0 };
        uint32_t SparsityMask{ 0 };
        uint32_t SubAllocationMask{ 0 };
        uint32_t PipelineCoherencyTier{ 0 };
        uint32_t FeedbackLoopTier{ 0 };
        uint32_t SubGraphRecursionTier{ 0 };
        uint32_t MeshPipeliningTier{ 0 };
        uint32_t MultiQueueFusionTier{ 0 };
        uint32_t MicroscalingTier{ 0 };
        uint32_t SubBytePrecisionTier{ 0 };
        uint32_t SparseTensorBlockTier{ 0 };
        uint32_t DeterministicTensorReductionTier{ 0 };
        uint32_t HyperQuantizationTier{ 0 };
        uint32_t SparseClusterTier{ 0 };
        uint32_t MultiQueueSyncTier{ 0 };
        uint32_t AsyncKernelDispatchTier{ 0 };
        uint32_t NeuralExecutionEngineTier{ 0 };
        uint32_t AdaptiveTensorCoreTier{ 0 };
        uint32_t SovereignSiliconTelemetryTier{ 0 };
        uint32_t Flags{ 0 };
    };
    BackingMemory25Record m_backingMemory25{};

    struct ProgramRecord25Entry {
        uint32_t NodeIndex{ 0 };
        const void* pRecord{ nullptr };
        uint32_t RecordSizeInBytes{ 0 };
        uint32_t ConcurrencyGroup{ 0 };
        uint32_t QueueAffinityMask{ 0 };
        uint32_t DynamicClusterExpansionTier{ 0 };
        uint32_t TensorCoreMask{ 0 };
        uint32_t SubAllocationMask{ 0 };
        uint32_t PipelineCoherencyTier{ 0 };
        uint32_t FeedbackLoopTier{ 0 };
        uint32_t SubGraphRecursionTier{ 0 };
        uint32_t MeshPipeliningTier{ 0 };
        uint32_t MultiQueueFusionTier{ 0 };
        uint32_t MicroscalingTier{ 0 };
        uint32_t SubBytePrecisionTier{ 0 };
        uint32_t SparseTensorBlockTier{ 0 };
        uint32_t DeterministicTensorReductionTier{ 0 };
        uint32_t HyperQuantizationTier{ 0 };
        uint32_t SparseClusterTier{ 0 };
        uint32_t MultiQueueSyncTier{ 0 };
        uint32_t AsyncKernelDispatchTier{ 0 };
        uint32_t NeuralExecutionEngineTier{ 0 };
        uint32_t AdaptiveTensorCoreTier{ 0 };
        uint32_t SovereignSiliconTelemetryTier{ 0 };
        uint32_t DispatchMask{ 0 };
        uint32_t DispatchFlags{ 0 };
    };
    std::vector<ProgramRecord25Entry> m_recordedProgramRecords25;

    struct BackingMemory26Record {
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart{ 0 };
        uint64_t RangeSizeInBytes{ 0 };
        uint64_t ScratchBufferSizeInBytes{ 0 };
        uint32_t MaxConcurrency{ 0 };
        uint32_t DynamicExpansionFlags{ 0 };
        uint32_t MemoryPoolTier{ 0 };
        uint32_t SparsityMask{ 0 };
        uint32_t SubAllocationMask{ 0 };
        uint32_t PipelineCoherencyTier{ 0 };
        uint32_t FeedbackLoopTier{ 0 };
        uint32_t SubGraphRecursionTier{ 0 };
        uint32_t MeshPipeliningTier{ 0 };
        uint32_t MultiQueueFusionTier{ 0 };
        uint32_t MicroscalingTier{ 0 };
        uint32_t SubBytePrecisionTier{ 0 };
        uint32_t SparseTensorBlockTier{ 0 };
        uint32_t DeterministicTensorReductionTier{ 0 };
        uint32_t HyperQuantizationTier{ 0 };
        uint32_t SparseClusterTier{ 0 };
        uint32_t MultiQueueSyncTier{ 0 };
        uint32_t AsyncKernelDispatchTier{ 0 };
        uint32_t NeuralExecutionEngineTier{ 0 };
        uint32_t AdaptiveTensorCoreTier{ 0 };
        uint32_t SovereignSiliconTelemetryTier{ 0 };
        uint32_t QuantumEmulationTier{ 0 };
        uint32_t Flags{ 0 };
    } m_backingMemory26;

    struct ProgramRecord26Entry {
        uint32_t NodeIndex{ 0 };
        const void* pRecord{ nullptr };
        uint32_t RecordSizeInBytes{ 0 };
        uint32_t ConcurrencyGroup{ 0 };
        uint32_t QueueAffinityMask{ 0 };
        uint32_t DynamicClusterExpansionTier{ 0 };
        uint32_t TensorCoreMask{ 0 };
        uint32_t SubAllocationMask{ 0 };
        uint32_t PipelineCoherencyTier{ 0 };
        uint32_t FeedbackLoopTier{ 0 };
        uint32_t SubGraphRecursionTier{ 0 };
        uint32_t MeshPipeliningTier{ 0 };
        uint32_t MultiQueueFusionTier{ 0 };
        uint32_t MicroscalingTier{ 0 };
        uint32_t SubBytePrecisionTier{ 0 };
        uint32_t SparseTensorBlockTier{ 0 };
        uint32_t DeterministicTensorReductionTier{ 0 };
        uint32_t HyperQuantizationTier{ 0 };
        uint32_t SparseClusterTier{ 0 };
        uint32_t MultiQueueSyncTier{ 0 };
        uint32_t AsyncKernelDispatchTier{ 0 };
        uint32_t NeuralExecutionEngineTier{ 0 };
        uint32_t AdaptiveTensorCoreTier{ 0 };
        uint32_t SovereignSiliconTelemetryTier{ 0 };
        uint32_t QuantumEmulationTier{ 0 };
        uint32_t DispatchMask{ 0 };
        uint32_t DispatchFlags{ 0 };
    };
    std::vector<ProgramRecord26Entry> m_recordedProgramRecords26;

    struct BackingMemory27Record {
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart{ 0 };
        uint64_t RangeSizeInBytes{ 0 };
        uint64_t ScratchBufferSizeInBytes{ 0 };
        uint32_t MaxConcurrency{ 0 };
        uint32_t DynamicExpansionFlags{ 0 };
        uint32_t MemoryPoolTier{ 0 };
        uint32_t SparsityMask{ 0 };
        uint32_t SubAllocationMask{ 0 };
        uint32_t PipelineCoherencyTier{ 0 };
        uint32_t FeedbackLoopTier{ 0 };
        uint32_t SubGraphRecursionTier{ 0 };
        uint32_t MeshPipeliningTier{ 0 };
        uint32_t MultiQueueFusionTier{ 0 };
        uint32_t MicroscalingTier{ 0 };
        uint32_t SubBytePrecisionTier{ 0 };
        uint32_t SparseTensorBlockTier{ 0 };
        uint32_t DeterministicTensorReductionTier{ 0 };
        uint32_t HyperQuantizationTier{ 0 };
        uint32_t SparseClusterTier{ 0 };
        uint32_t MultiQueueSyncTier{ 0 };
        uint32_t AsyncKernelDispatchTier{ 0 };
        uint32_t NeuralExecutionEngineTier{ 0 };
        uint32_t AdaptiveTensorCoreTier{ 0 };
        uint32_t SovereignSiliconTelemetryTier{ 0 };
        uint32_t QuantumEmulationTier{ 0 };
        uint32_t Flags{ 0 };
    } m_backingMemory27;

    struct ProgramRecord27Entry {
        uint32_t NodeIndex{ 0 };
        const void* pRecord{ nullptr };
        uint32_t RecordSizeInBytes{ 0 };
        uint32_t ConcurrencyGroup{ 0 };
        uint32_t QueueAffinityMask{ 0 };
        uint32_t DynamicClusterExpansionTier{ 0 };
        uint32_t TensorCoreMask{ 0 };
        uint32_t SubAllocationMask{ 0 };
        uint32_t PipelineCoherencyTier{ 0 };
        uint32_t FeedbackLoopTier{ 0 };
        uint32_t SubGraphRecursionTier{ 0 };
        uint32_t MeshPipeliningTier{ 0 };
        uint32_t MultiQueueFusionTier{ 0 };
        uint32_t MicroscalingTier{ 0 };
        uint32_t SubBytePrecisionTier{ 0 };
        uint32_t SparseTensorBlockTier{ 0 };
        uint32_t DeterministicTensorReductionTier{ 0 };
        uint32_t HyperQuantizationTier{ 0 };
        uint32_t SparseClusterTier{ 0 };
        uint32_t MultiQueueSyncTier{ 0 };
        uint32_t AsyncKernelDispatchTier{ 0 };
        uint32_t NeuralExecutionEngineTier{ 0 };
        uint32_t AdaptiveTensorCoreTier{ 0 };
        uint32_t SovereignSiliconTelemetryTier{ 0 };
        uint32_t QuantumEmulationTier{ 0 };
        uint32_t DispatchMask{ 0 };
        uint32_t DispatchFlags{ 0 };
    };
    std::vector<ProgramRecord27Entry> m_recordedProgramRecords27;

    struct BackingMemory28Record {
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart{ 0 };
        uint64_t RangeSizeInBytes{ 0 };
        uint64_t ScratchBufferSizeInBytes{ 0 };
        uint32_t MaxConcurrency{ 0 };
        uint32_t DynamicExpansionFlags{ 0 };
        uint32_t MemoryPoolTier{ 0 };
        uint32_t SparsityMask{ 0 };
        uint32_t SubAllocationMask{ 0 };
        uint32_t PipelineCoherencyTier{ 0 };
        uint32_t FeedbackLoopTier{ 0 };
        uint32_t SubGraphRecursionTier{ 0 };
        uint32_t MeshPipeliningTier{ 0 };
        uint32_t MultiQueueFusionTier{ 0 };
        uint32_t MicroscalingTier{ 0 };
        uint32_t SubBytePrecisionTier{ 0 };
        uint32_t SparseTensorBlockTier{ 0 };
        uint32_t DeterministicTensorReductionTier{ 0 };
        uint32_t HyperQuantizationTier{ 0 };
        uint32_t SparseClusterTier{ 0 };
        uint32_t MultiQueueSyncTier{ 0 };
        uint32_t AsyncKernelDispatchTier{ 0 };
        uint32_t NeuralExecutionEngineTier{ 0 };
        uint32_t AdaptiveTensorCoreTier{ 0 };
        uint32_t SovereignSiliconTelemetryTier{ 0 };
        uint32_t QuantumEmulationTier{ 0 };
        uint32_t Flags{ 0 };
    } m_backingMemory28;

    struct ProgramRecord28Entry {
        uint32_t NodeIndex{ 0 };
        const void* pRecord{ nullptr };
        uint32_t RecordSizeInBytes{ 0 };
        uint32_t ConcurrencyGroup{ 0 };
        uint32_t QueueAffinityMask{ 0 };
        uint32_t DynamicClusterExpansionTier{ 0 };
        uint32_t TensorCoreMask{ 0 };
        uint32_t SubAllocationMask{ 0 };
        uint32_t PipelineCoherencyTier{ 0 };
        uint32_t FeedbackLoopTier{ 0 };
        uint32_t SubGraphRecursionTier{ 0 };
        uint32_t MeshPipeliningTier{ 0 };
        uint32_t MultiQueueFusionTier{ 0 };
        uint32_t MicroscalingTier{ 0 };
        uint32_t SubBytePrecisionTier{ 0 };
        uint32_t SparseTensorBlockTier{ 0 };
        uint32_t DeterministicTensorReductionTier{ 0 };
        uint32_t HyperQuantizationTier{ 0 };
        uint32_t SparseClusterTier{ 0 };
        uint32_t MultiQueueSyncTier{ 0 };
        uint32_t AsyncKernelDispatchTier{ 0 };
        uint32_t NeuralExecutionEngineTier{ 0 };
        uint32_t AdaptiveTensorCoreTier{ 0 };
        uint32_t SovereignSiliconTelemetryTier{ 0 };
        uint32_t QuantumEmulationTier{ 0 };
        uint32_t DispatchMask{ 0 };
        uint32_t DispatchFlags{ 0 };
    };
    std::vector<ProgramRecord28Entry> m_recordedProgramRecords28;

    struct BackingMemory29Record {
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart{ 0 };
        uint64_t RangeSizeInBytes{ 0 };
        uint64_t ScratchBufferSizeInBytes{ 0 };
        uint32_t MaxConcurrency{ 0 };
        uint32_t DynamicExpansionFlags{ 0 };
        uint32_t MemoryPoolTier{ 0 };
        uint32_t SparsityMask{ 0 };
        uint32_t SubAllocationMask{ 0 };
        uint32_t PipelineCoherencyTier{ 0 };
        uint32_t FeedbackLoopTier{ 0 };
        uint32_t SubGraphRecursionTier{ 0 };
        uint32_t MeshPipeliningTier{ 0 };
        uint32_t MultiQueueFusionTier{ 0 };
        uint32_t MicroscalingTier{ 0 };
        uint32_t SubBytePrecisionTier{ 0 };
        uint32_t SparseTensorBlockTier{ 0 };
        uint32_t DeterministicTensorReductionTier{ 0 };
        uint32_t HyperQuantizationTier{ 0 };
        uint32_t SparseClusterTier{ 0 };
        uint32_t MultiQueueSyncTier{ 0 };
        uint32_t AsyncKernelDispatchTier{ 0 };
        uint32_t NeuralExecutionEngineTier{ 0 };
        uint32_t AdaptiveTensorCoreTier{ 0 };
        uint32_t SovereignSiliconTelemetryTier{ 0 };
        uint32_t QuantumEmulationTier{ 0 };
        uint32_t Flags{ 0 };
    } m_backingMemory29;

    struct ProgramRecord29Entry {
        uint32_t NodeIndex{ 0 };
        const void* pRecord{ nullptr };
        uint32_t RecordSizeInBytes{ 0 };
        uint32_t ConcurrencyGroup{ 0 };
        uint32_t QueueAffinityMask{ 0 };
        uint32_t DynamicClusterExpansionTier{ 0 };
        uint32_t TensorCoreMask{ 0 };
        uint32_t SubAllocationMask{ 0 };
        uint32_t PipelineCoherencyTier{ 0 };
        uint32_t FeedbackLoopTier{ 0 };
        uint32_t SubGraphRecursionTier{ 0 };
        uint32_t MeshPipeliningTier{ 0 };
        uint32_t MultiQueueFusionTier{ 0 };
        uint32_t MicroscalingTier{ 0 };
        uint32_t SubBytePrecisionTier{ 0 };
        uint32_t SparseTensorBlockTier{ 0 };
        uint32_t DeterministicTensorReductionTier{ 0 };
        uint32_t HyperQuantizationTier{ 0 };
        uint32_t SparseClusterTier{ 0 };
        uint32_t MultiQueueSyncTier{ 0 };
        uint32_t AsyncKernelDispatchTier{ 0 };
        uint32_t NeuralExecutionEngineTier{ 0 };
        uint32_t AdaptiveTensorCoreTier{ 0 };
        uint32_t SovereignSiliconTelemetryTier{ 0 };
        uint32_t QuantumEmulationTier{ 0 };
        uint32_t DispatchMask{ 0 };
        uint32_t DispatchFlags{ 0 };
    };
    std::vector<ProgramRecord29Entry> m_recordedProgramRecords29;

    struct BackingMemory30Record {
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart{ 0 };
        uint64_t RangeSizeInBytes{ 0 };
        uint64_t ScratchBufferSizeInBytes{ 0 };
        uint64_t MaxConcurrency{ 0 };
        uint32_t DynamicExpansionFlags{ 0 };
        uint32_t MemoryPoolTier{ 0 };
        uint32_t SparsityMask{ 0 };
        uint32_t SubAllocationMask{ 0 };
        uint32_t PipelineCoherencyTier{ 0 };
        uint32_t FeedbackLoopTier{ 0 };
        uint32_t SubGraphRecursionTier{ 0 };
        uint32_t MeshPipeliningTier{ 0 };
        uint32_t MultiQueueFusionTier{ 0 };
        uint32_t MicroscalingTier{ 0 };
        uint32_t SubBytePrecisionTier{ 0 };
        uint32_t SparseTensorBlockTier{ 0 };
        uint32_t DeterministicTensorReductionTier{ 0 };
        uint32_t HyperQuantizationTier{ 0 };
        uint32_t SparseClusterTier{ 0 };
        uint32_t MultiQueueSyncTier{ 0 };
        uint32_t AsyncKernelDispatchTier{ 0 };
        uint32_t NeuralExecutionEngineTier{ 0 };
        uint32_t AdaptiveTensorCoreTier{ 0 };
        uint32_t SovereignSiliconTelemetryTier{ 0 };
        uint32_t QuantumEmulationTier{ 0 };
        uint32_t Flags{ 0 };
    } m_backingMemory30;

    struct ProgramRecord30Entry {
        uint32_t NodeIndex{ 0 };
        const void* pRecord{ nullptr };
        uint32_t RecordSizeInBytes{ 0 };
        uint32_t ConcurrencyGroup{ 0 };
        uint32_t QueueAffinityMask{ 0 };
        uint32_t DynamicClusterExpansionTier{ 0 };
        uint32_t TensorCoreMask{ 0 };
        uint32_t SubAllocationMask{ 0 };
        uint32_t PipelineCoherencyTier{ 0 };
        uint32_t FeedbackLoopTier{ 0 };
        uint32_t SubGraphRecursionTier{ 0 };
        uint32_t MeshPipeliningTier{ 0 };
        uint32_t MultiQueueFusionTier{ 0 };
        uint32_t MicroscalingTier{ 0 };
        uint32_t SubBytePrecisionTier{ 0 };
        uint32_t SparseTensorBlockTier{ 0 };
        uint32_t DeterministicTensorReductionTier{ 0 };
        uint32_t HyperQuantizationTier{ 0 };
        uint32_t SparseClusterTier{ 0 };
        uint32_t MultiQueueSyncTier{ 0 };
        uint32_t AsyncKernelDispatchTier{ 0 };
        uint32_t NeuralExecutionEngineTier{ 0 };
        uint32_t AdaptiveTensorCoreTier{ 0 };
        uint32_t SovereignSiliconTelemetryTier{ 0 };
        uint32_t QuantumEmulationTier{ 0 };
        uint32_t DispatchMask{ 0 };
        uint32_t DispatchFlags{ 0 };
    };
    std::vector<ProgramRecord30Entry> m_recordedProgramRecords30;

    struct BackingMemory31Record {
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart{ 0 };
        uint64_t RangeSizeInBytes{ 0 };
        uint64_t ScratchBufferSizeInBytes{ 0 };
        uint64_t MaxConcurrency{ 0 };
        uint32_t DynamicExpansionFlags{ 0 };
        uint32_t MemoryPoolTier{ 0 };
        uint32_t SparsityMask{ 0 };
        uint32_t SubAllocationMask{ 0 };
        uint32_t PipelineCoherencyTier{ 0 };
        uint32_t FeedbackLoopTier{ 0 };
        uint32_t SubGraphRecursionTier{ 0 };
        uint32_t MeshPipeliningTier{ 0 };
        uint32_t MultiQueueFusionTier{ 0 };
        uint32_t MicroscalingTier{ 0 };
        uint32_t SubBytePrecisionTier{ 0 };
        uint32_t SparseTensorBlockTier{ 0 };
        uint32_t DeterministicTensorReductionTier{ 0 };
        uint32_t HyperQuantizationTier{ 0 };
        uint32_t SparseClusterTier{ 0 };
        uint32_t MultiQueueSyncTier{ 0 };
        uint32_t AsyncKernelDispatchTier{ 0 };
        uint32_t NeuralExecutionEngineTier{ 0 };
        uint32_t AdaptiveTensorCoreTier{ 0 };
        uint32_t SovereignSiliconTelemetryTier{ 0 };
        uint32_t QuantumEmulationTier{ 0 };
        uint32_t Flags{ 0 };
    } m_backingMemory31;

    struct ProgramRecord31Entry {
        uint32_t NodeIndex{ 0 };
        const void* pRecord{ nullptr };
        uint32_t RecordSizeInBytes{ 0 };
        uint32_t ConcurrencyGroup{ 0 };
        uint32_t QueueAffinityMask{ 0 };
        uint32_t DynamicClusterExpansionTier{ 0 };
        uint32_t TensorCoreMask{ 0 };
        uint32_t SubAllocationMask{ 0 };
        uint32_t PipelineCoherencyTier{ 0 };
        uint32_t FeedbackLoopTier{ 0 };
        uint32_t SubGraphRecursionTier{ 0 };
        uint32_t MeshPipeliningTier{ 0 };
        uint32_t MultiQueueFusionTier{ 0 };
        uint32_t MicroscalingTier{ 0 };
        uint32_t SubBytePrecisionTier{ 0 };
        uint32_t SparseTensorBlockTier{ 0 };
        uint32_t DeterministicTensorReductionTier{ 0 };
        uint32_t HyperQuantizationTier{ 0 };
        uint32_t SparseClusterTier{ 0 };
        uint32_t MultiQueueSyncTier{ 0 };
        uint32_t AsyncKernelDispatchTier{ 0 };
        uint32_t NeuralExecutionEngineTier{ 0 };
        uint32_t AdaptiveTensorCoreTier{ 0 };
        uint32_t SovereignSiliconTelemetryTier{ 0 };
        uint32_t QuantumEmulationTier{ 0 };
        uint32_t DispatchMask{ 0 };
        uint32_t DispatchFlags{ 0 };
    };
    std::vector<ProgramRecord31Entry> m_recordedProgramRecords31;

    struct BackingMemory32Record {
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart{ 0 };
        uint64_t RangeSizeInBytes{ 0 };
        uint64_t ScratchBufferSizeInBytes{ 0 };
        uint64_t MaxConcurrency{ 0 };
        uint32_t DynamicExpansionFlags{ 0 };
        uint32_t MemoryPoolTier{ 0 };
        uint32_t SparsityMask{ 0 };
        uint32_t SubAllocationMask{ 0 };
        uint32_t PipelineCoherencyTier{ 0 };
        uint32_t FeedbackLoopTier{ 0 };
        uint32_t SubGraphRecursionTier{ 0 };
        uint32_t MeshPipeliningTier{ 0 };
        uint32_t MultiQueueFusionTier{ 0 };
        uint32_t MicroscalingTier{ 0 };
        uint32_t SubBytePrecisionTier{ 0 };
        uint32_t SparseTensorBlockTier{ 0 };
        uint32_t DeterministicTensorReductionTier{ 0 };
        uint32_t HyperQuantizationTier{ 0 };
        uint32_t SparseClusterTier{ 0 };
        uint32_t MultiQueueSyncTier{ 0 };
        uint32_t AsyncKernelDispatchTier{ 0 };
        uint32_t NeuralExecutionEngineTier{ 0 };
        uint32_t AdaptiveTensorCoreTier{ 0 };
        uint32_t SovereignSiliconTelemetryTier{ 0 };
        uint32_t QuantumEmulationTier{ 0 };
        uint32_t Flags{ 0 };
    } m_backingMemory32;

    struct ProgramRecord32Entry {
        uint32_t NodeIndex{ 0 };
        const void* pRecord{ nullptr };
        uint32_t RecordSizeInBytes{ 0 };
        uint32_t ConcurrencyGroup{ 0 };
        uint32_t QueueAffinityMask{ 0 };
        uint32_t DynamicClusterExpansionTier{ 0 };
        uint32_t TensorCoreMask{ 0 };
        uint32_t SubAllocationMask{ 0 };
        uint32_t PipelineCoherencyTier{ 0 };
        uint32_t FeedbackLoopTier{ 0 };
        uint32_t SubGraphRecursionTier{ 0 };
        uint32_t MeshPipeliningTier{ 0 };
        uint32_t MultiQueueFusionTier{ 0 };
        uint32_t MicroscalingTier{ 0 };
        uint32_t SubBytePrecisionTier{ 0 };
        uint32_t SparseTensorBlockTier{ 0 };
        uint32_t DeterministicTensorReductionTier{ 0 };
        uint32_t HyperQuantizationTier{ 0 };
        uint32_t SparseClusterTier{ 0 };
        uint32_t MultiQueueSyncTier{ 0 };
        uint32_t AsyncKernelDispatchTier{ 0 };
        uint32_t NeuralExecutionEngineTier{ 0 };
        uint32_t AdaptiveTensorCoreTier{ 0 };
        uint32_t SovereignSiliconTelemetryTier{ 0 };
        uint32_t QuantumEmulationTier{ 0 };
        uint32_t DispatchMask{ 0 };
        uint32_t DispatchFlags{ 0 };
    };
    std::vector<ProgramRecord32Entry> m_recordedProgramRecords32;

    struct BackingMemory33Record {
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart{ 0 };
        uint64_t RangeSizeInBytes{ 0 };
        uint64_t ScratchBufferSizeInBytes{ 0 };
        uint64_t MaxConcurrency{ 0 };
        uint32_t DynamicExpansionFlags{ 0 };
        uint32_t MemoryPoolTier{ 0 };
        uint32_t SparsityMask{ 0 };
        uint32_t SubAllocationMask{ 0 };
        uint32_t PipelineCoherencyTier{ 0 };
        uint32_t FeedbackLoopTier{ 0 };
        uint32_t SubGraphRecursionTier{ 0 };
        uint32_t MeshPipeliningTier{ 0 };
        uint32_t MultiQueueFusionTier{ 0 };
        uint32_t MicroscalingTier{ 0 };
        uint32_t SubBytePrecisionTier{ 0 };
        uint32_t SparseTensorBlockTier{ 0 };
        uint32_t DeterministicTensorReductionTier{ 0 };
        uint32_t HyperQuantizationTier{ 0 };
        uint32_t SparseClusterTier{ 0 };
        uint32_t MultiQueueSyncTier{ 0 };
        uint32_t AsyncKernelDispatchTier{ 0 };
        uint32_t NeuralExecutionEngineTier{ 0 };
        uint32_t AdaptiveTensorCoreTier{ 0 };
        uint32_t SovereignSiliconTelemetryTier{ 0 };
        uint32_t QuantumEmulationTier{ 0 };
        uint32_t Flags{ 0 };
    } m_backingMemory33;

    struct ProgramRecord33Entry {
        uint32_t NodeIndex{ 0 };
        const void* pRecord{ nullptr };
        uint32_t RecordSizeInBytes{ 0 };
        uint32_t ConcurrencyGroup{ 0 };
        uint32_t QueueAffinityMask{ 0 };
        uint32_t DynamicClusterExpansionTier{ 0 };
        uint32_t TensorCoreMask{ 0 };
        uint32_t SubAllocationMask{ 0 };
        uint32_t PipelineCoherencyTier{ 0 };
        uint32_t FeedbackLoopTier{ 0 };
        uint32_t SubGraphRecursionTier{ 0 };
        uint32_t MeshPipeliningTier{ 0 };
        uint32_t MultiQueueFusionTier{ 0 };
        uint32_t MicroscalingTier{ 0 };
        uint32_t SubBytePrecisionTier{ 0 };
        uint32_t SparseTensorBlockTier{ 0 };
        uint32_t DeterministicTensorReductionTier{ 0 };
        uint32_t HyperQuantizationTier{ 0 };
        uint32_t SparseClusterTier{ 0 };
        uint32_t MultiQueueSyncTier{ 0 };
        uint32_t AsyncKernelDispatchTier{ 0 };
        uint32_t NeuralExecutionEngineTier{ 0 };
        uint32_t AdaptiveTensorCoreTier{ 0 };
        uint32_t SovereignSiliconTelemetryTier{ 0 };
        uint32_t QuantumEmulationTier{ 0 };
        uint32_t DispatchMask{ 0 };
        uint32_t DispatchFlags{ 0 };
    };
    std::vector<ProgramRecord33Entry> m_recordedProgramRecords33;

    struct BackingMemory34Record {
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart{ 0 };
        uint64_t RangeSizeInBytes{ 0 };
        uint64_t ScratchBufferSizeInBytes{ 0 };
        uint64_t MaxConcurrency{ 0 };
        uint32_t DynamicExpansionFlags{ 0 };
        uint32_t MemoryPoolTier{ 0 };
        uint32_t SparsityMask{ 0 };
        uint32_t SubAllocationMask{ 0 };
        uint32_t PipelineCoherencyTier{ 0 };
        uint32_t FeedbackLoopTier{ 0 };
        uint32_t SubGraphRecursionTier{ 0 };
        uint32_t MeshPipeliningTier{ 0 };
        uint32_t MultiQueueFusionTier{ 0 };
        uint32_t MicroscalingTier{ 0 };
        uint32_t SubBytePrecisionTier{ 0 };
        uint32_t SparseTensorBlockTier{ 0 };
        uint32_t DeterministicTensorReductionTier{ 0 };
        uint32_t HyperQuantizationTier{ 0 };
        uint32_t SparseClusterTier{ 0 };
        uint32_t MultiQueueSyncTier{ 0 };
        uint32_t AsyncKernelDispatchTier{ 0 };
        uint32_t NeuralExecutionEngineTier{ 0 };
        uint32_t AdaptiveTensorCoreTier{ 0 };
        uint32_t SovereignSiliconTelemetryTier{ 0 };
        uint32_t QuantumEmulationTier{ 0 };
        uint32_t Flags{ 0 };
    } m_backingMemory34;

    struct ProgramRecord34Entry {
        uint32_t NodeIndex{ 0 };
        const void* pRecord{ nullptr };
        uint32_t RecordSizeInBytes{ 0 };
        uint32_t ConcurrencyGroup{ 0 };
        uint32_t QueueAffinityMask{ 0 };
        uint32_t DynamicClusterExpansionTier{ 0 };
        uint32_t TensorCoreMask{ 0 };
        uint32_t SubAllocationMask{ 0 };
        uint32_t PipelineCoherencyTier{ 0 };
        uint32_t FeedbackLoopTier{ 0 };
        uint32_t SubGraphRecursionTier{ 0 };
        uint32_t MeshPipeliningTier{ 0 };
        uint32_t MultiQueueFusionTier{ 0 };
        uint32_t MicroscalingTier{ 0 };
        uint32_t SubBytePrecisionTier{ 0 };
        uint32_t SparseTensorBlockTier{ 0 };
        uint32_t DeterministicTensorReductionTier{ 0 };
        uint32_t HyperQuantizationTier{ 0 };
        uint32_t SparseClusterTier{ 0 };
        uint32_t MultiQueueSyncTier{ 0 };
        uint32_t AsyncKernelDispatchTier{ 0 };
        uint32_t NeuralExecutionEngineTier{ 0 };
        uint32_t AdaptiveTensorCoreTier{ 0 };
        uint32_t SovereignSiliconTelemetryTier{ 0 };
        uint32_t QuantumEmulationTier{ 0 };
        uint32_t DispatchMask{ 0 };
        uint32_t DispatchFlags{ 0 };
    };
    std::vector<ProgramRecord34Entry> m_recordedProgramRecords34;

    struct BackingMemory35Record {
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart{ 0 };
        uint64_t RangeSizeInBytes{ 0 };
        uint64_t ScratchBufferSizeInBytes{ 0 };
        uint64_t MaxConcurrency{ 0 };
        uint32_t DynamicExpansionFlags{ 0 };
        uint32_t MemoryPoolTier{ 0 };
        uint32_t SparsityMask{ 0 };
        uint32_t SubAllocationMask{ 0 };
        uint32_t PipelineCoherencyTier{ 0 };
        uint32_t FeedbackLoopTier{ 0 };
        uint32_t SubGraphRecursionTier{ 0 };
        uint32_t MeshPipeliningTier{ 0 };
        uint32_t MultiQueueFusionTier{ 0 };
        uint32_t MicroscalingTier{ 0 };
        uint32_t SubBytePrecisionTier{ 0 };
        uint32_t SparseTensorBlockTier{ 0 };
        uint32_t DeterministicTensorReductionTier{ 0 };
        uint32_t HyperQuantizationTier{ 0 };
        uint32_t SparseClusterTier{ 0 };
        uint32_t MultiQueueSyncTier{ 0 };
        uint32_t AsyncKernelDispatchTier{ 0 };
        uint32_t NeuralExecutionEngineTier{ 0 };
        uint32_t AdaptiveTensorCoreTier{ 0 };
        uint32_t SovereignSiliconTelemetryTier{ 0 };
        uint32_t QuantumEmulationTier{ 0 };
        uint32_t Flags{ 0 };
    } m_backingMemory35;

    struct ProgramRecord35Entry {
        uint32_t NodeIndex{ 0 };
        const void* pRecord{ nullptr };
        uint32_t RecordSizeInBytes{ 0 };
        uint32_t ConcurrencyGroup{ 0 };
        uint32_t QueueAffinityMask{ 0 };
        uint32_t DynamicClusterExpansionTier{ 0 };
        uint32_t TensorCoreMask{ 0 };
        uint32_t SubAllocationMask{ 0 };
        uint32_t PipelineCoherencyTier{ 0 };
        uint32_t FeedbackLoopTier{ 0 };
        uint32_t SubGraphRecursionTier{ 0 };
        uint32_t MeshPipeliningTier{ 0 };
        uint32_t MultiQueueFusionTier{ 0 };
        uint32_t MicroscalingTier{ 0 };
        uint32_t SubBytePrecisionTier{ 0 };
        uint32_t SparseTensorBlockTier{ 0 };
        uint32_t DeterministicTensorReductionTier{ 0 };
        uint32_t HyperQuantizationTier{ 0 };
        uint32_t SparseClusterTier{ 0 };
        uint32_t MultiQueueSyncTier{ 0 };
        uint32_t AsyncKernelDispatchTier{ 0 };
        uint32_t NeuralExecutionEngineTier{ 0 };
        uint32_t AdaptiveTensorCoreTier{ 0 };
        uint32_t SovereignSiliconTelemetryTier{ 0 };
        uint32_t QuantumEmulationTier{ 0 };
        uint32_t DispatchMask{ 0 };
        uint32_t DispatchFlags{ 0 };
    };
    std::vector<ProgramRecord35Entry> m_recordedProgramRecords35;

    struct BackingMemory36Record {
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart{ 0 };
        uint64_t RangeSizeInBytes{ 0 };
        uint64_t ScratchBufferSizeInBytes{ 0 };
        uint64_t MaxConcurrency{ 0 };
        uint32_t DynamicExpansionFlags{ 0 };
        uint32_t MemoryPoolTier{ 0 };
        uint32_t SparsityMask{ 0 };
        uint32_t SubAllocationMask{ 0 };
        uint32_t PipelineCoherencyTier{ 0 };
        uint32_t FeedbackLoopTier{ 0 };
        uint32_t SubGraphRecursionTier{ 0 };
        uint32_t MeshPipeliningTier{ 0 };
        uint32_t MultiQueueFusionTier{ 0 };
        uint32_t MicroscalingTier{ 0 };
        uint32_t SubBytePrecisionTier{ 0 };
        uint32_t SparseTensorBlockTier{ 0 };
        uint32_t DeterministicTensorReductionTier{ 0 };
        uint32_t HyperQuantizationTier{ 0 };
        uint32_t SparseClusterTier{ 0 };
        uint32_t MultiQueueSyncTier{ 0 };
        uint32_t AsyncKernelDispatchTier{ 0 };
        uint32_t NeuralExecutionEngineTier{ 0 };
        uint32_t AdaptiveTensorCoreTier{ 0 };
        uint32_t SovereignSiliconTelemetryTier{ 0 };
        uint32_t QuantumEmulationTier{ 0 };
        uint32_t Flags{ 0 };
    } m_backingMemory36;

    struct ProgramRecord36Entry {
        uint32_t NodeIndex{ 0 };
        const void* pRecord{ nullptr };
        uint32_t RecordSizeInBytes{ 0 };
        uint32_t ConcurrencyGroup{ 0 };
        uint32_t QueueAffinityMask{ 0 };
        uint32_t DynamicClusterExpansionTier{ 0 };
        uint32_t TensorCoreMask{ 0 };
        uint32_t SubAllocationMask{ 0 };
        uint32_t PipelineCoherencyTier{ 0 };
        uint32_t FeedbackLoopTier{ 0 };
        uint32_t SubGraphRecursionTier{ 0 };
        uint32_t MeshPipeliningTier{ 0 };
        uint32_t MultiQueueFusionTier{ 0 };
        uint32_t MicroscalingTier{ 0 };
        uint32_t SubBytePrecisionTier{ 0 };
        uint32_t SparseTensorBlockTier{ 0 };
        uint32_t DeterministicTensorReductionTier{ 0 };
        uint32_t HyperQuantizationTier{ 0 };
        uint32_t SparseClusterTier{ 0 };
        uint32_t MultiQueueSyncTier{ 0 };
        uint32_t AsyncKernelDispatchTier{ 0 };
        uint32_t NeuralExecutionEngineTier{ 0 };
        uint32_t AdaptiveTensorCoreTier{ 0 };
        uint32_t SovereignSiliconTelemetryTier{ 0 };
        uint32_t QuantumEmulationTier{ 0 };
        uint32_t DispatchMask{ 0 };
        uint32_t DispatchFlags{ 0 };
    };
    std::vector<ProgramRecord36Entry> m_recordedProgramRecords36;

    struct BackingMemory37Record {
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart{ 0 };
        uint64_t RangeSizeInBytes{ 0 };
        uint64_t ScratchBufferSizeInBytes{ 0 };
        uint64_t MaxConcurrency{ 0 };
        uint32_t DynamicExpansionFlags{ 0 };
        uint32_t MemoryPoolTier{ 0 };
        uint32_t SparsityMask{ 0 };
        uint32_t SubAllocationMask{ 0 };
        uint32_t PipelineCoherencyTier{ 0 };
        uint32_t FeedbackLoopTier{ 0 };
        uint32_t SubGraphRecursionTier{ 0 };
        uint32_t MeshPipeliningTier{ 0 };
        uint32_t MultiQueueFusionTier{ 0 };
        uint32_t MicroscalingTier{ 0 };
        uint32_t SubBytePrecisionTier{ 0 };
        uint32_t SparseTensorBlockTier{ 0 };
        uint32_t DeterministicTensorReductionTier{ 0 };
        uint32_t HyperQuantizationTier{ 0 };
        uint32_t SparseClusterTier{ 0 };
        uint32_t MultiQueueSyncTier{ 0 };
        uint32_t AsyncKernelDispatchTier{ 0 };
        uint32_t NeuralExecutionEngineTier{ 0 };
        uint32_t AdaptiveTensorCoreTier{ 0 };
        uint32_t SovereignSiliconTelemetryTier{ 0 };
        uint32_t QuantumEmulationTier{ 0 };
        uint32_t Flags{ 0 };
    } m_backingMemory37;

    struct ProgramRecord37Entry {
        uint32_t NodeIndex{ 0 };
        const void* pRecord{ nullptr };
        uint32_t RecordSizeInBytes{ 0 };
        uint32_t ConcurrencyGroup{ 0 };
        uint32_t QueueAffinityMask{ 0 };
        uint32_t DynamicClusterExpansionTier{ 0 };
        uint32_t TensorCoreMask{ 0 };
        uint32_t SubAllocationMask{ 0 };
        uint32_t PipelineCoherencyTier{ 0 };
        uint32_t FeedbackLoopTier{ 0 };
        uint32_t SubGraphRecursionTier{ 0 };
        uint32_t MeshPipeliningTier{ 0 };
        uint32_t MultiQueueFusionTier{ 0 };
        uint32_t MicroscalingTier{ 0 };
        uint32_t SubBytePrecisionTier{ 0 };
        uint32_t SparseTensorBlockTier{ 0 };
        uint32_t DeterministicTensorReductionTier{ 0 };
        uint32_t HyperQuantizationTier{ 0 };
        uint32_t SparseClusterTier{ 0 };
        uint32_t MultiQueueSyncTier{ 0 };
        uint32_t AsyncKernelDispatchTier{ 0 };
        uint32_t NeuralExecutionEngineTier{ 0 };
        uint32_t AdaptiveTensorCoreTier{ 0 };
        uint32_t SovereignSiliconTelemetryTier{ 0 };
        uint32_t QuantumEmulationTier{ 0 };
        uint32_t DispatchMask{ 0 };
        uint32_t DispatchFlags{ 0 };
    };
    std::vector<ProgramRecord37Entry> m_recordedProgramRecords37;

    struct BackingMemory38Record {
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart{ 0 };
        uint64_t RangeSizeInBytes{ 0 };
        uint64_t ScratchBufferSizeInBytes{ 0 };
        uint64_t MaxConcurrency{ 0 };
        uint32_t DynamicExpansionFlags{ 0 };
        uint32_t MemoryPoolTier{ 0 };
        uint32_t SparsityMask{ 0 };
        uint32_t SubAllocationMask{ 0 };
        uint32_t PipelineCoherencyTier{ 0 };
        uint32_t FeedbackLoopTier{ 0 };
        uint32_t SubGraphRecursionTier{ 0 };
        uint32_t MeshPipeliningTier{ 0 };
        uint32_t MultiQueueFusionTier{ 0 };
        uint32_t MicroscalingTier{ 0 };
        uint32_t SubBytePrecisionTier{ 0 };
        uint32_t SparseTensorBlockTier{ 0 };
        uint32_t DeterministicTensorReductionTier{ 0 };
        uint32_t HyperQuantizationTier{ 0 };
        uint32_t SparseClusterTier{ 0 };
        uint32_t MultiQueueSyncTier{ 0 };
        uint32_t AsyncKernelDispatchTier{ 0 };
        uint32_t NeuralExecutionEngineTier{ 0 };
        uint32_t AdaptiveTensorCoreTier{ 0 };
        uint32_t SovereignSiliconTelemetryTier{ 0 };
        uint32_t QuantumEmulationTier{ 0 };
        uint32_t Flags{ 0 };
    } m_backingMemory38;

    struct ProgramRecord38Entry {
        uint32_t NodeIndex{ 0 };
        const void* pRecord{ nullptr };
        uint32_t RecordSizeInBytes{ 0 };
        uint32_t ConcurrencyGroup{ 0 };
        uint32_t QueueAffinityMask{ 0 };
        uint32_t DynamicClusterExpansionTier{ 0 };
        uint32_t TensorCoreMask{ 0 };
        uint32_t SubAllocationMask{ 0 };
        uint32_t PipelineCoherencyTier{ 0 };
        uint32_t FeedbackLoopTier{ 0 };
        uint32_t SubGraphRecursionTier{ 0 };
        uint32_t MeshPipeliningTier{ 0 };
        uint32_t MultiQueueFusionTier{ 0 };
        uint32_t MicroscalingTier{ 0 };
        uint32_t SubBytePrecisionTier{ 0 };
        uint32_t SparseTensorBlockTier{ 0 };
        uint32_t DeterministicTensorReductionTier{ 0 };
        uint32_t HyperQuantizationTier{ 0 };
        uint32_t SparseClusterTier{ 0 };
        uint32_t MultiQueueSyncTier{ 0 };
        uint32_t AsyncKernelDispatchTier{ 0 };
        uint32_t NeuralExecutionEngineTier{ 0 };
        uint32_t AdaptiveTensorCoreTier{ 0 };
        uint32_t SovereignSiliconTelemetryTier{ 0 };
        uint32_t QuantumEmulationTier{ 0 };
        uint32_t DispatchMask{ 0 };
        uint32_t DispatchFlags{ 0 };
    };
    std::vector<ProgramRecord38Entry> m_recordedProgramRecords38;

    struct BackingMemory39Record {
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart{ 0 };
        uint64_t RangeSizeInBytes{ 0 };
        uint64_t ScratchBufferSizeInBytes{ 0 };
        uint64_t MaxConcurrency{ 0 };
        uint32_t DynamicExpansionFlags{ 0 };
        uint32_t MemoryPoolTier{ 0 };
        uint32_t SparsityMask{ 0 };
        uint32_t SubAllocationMask{ 0 };
        uint32_t PipelineCoherencyTier{ 0 };
        uint32_t FeedbackLoopTier{ 0 };
        uint32_t SubGraphRecursionTier{ 0 };
        uint32_t MeshPipeliningTier{ 0 };
        uint32_t MultiQueueFusionTier{ 0 };
        uint32_t MicroscalingTier{ 0 };
        uint32_t SubBytePrecisionTier{ 0 };
        uint32_t SparseTensorBlockTier{ 0 };
        uint32_t DeterministicTensorReductionTier{ 0 };
        uint32_t HyperQuantizationTier{ 0 };
        uint32_t SparseClusterTier{ 0 };
        uint32_t MultiQueueSyncTier{ 0 };
        uint32_t AsyncKernelDispatchTier{ 0 };
        uint32_t NeuralExecutionEngineTier{ 0 };
        uint32_t AdaptiveTensorCoreTier{ 0 };
        uint32_t SovereignSiliconTelemetryTier{ 0 };
        uint32_t QuantumEmulationTier{ 0 };
        uint32_t Flags{ 0 };
    } m_backingMemory39;

    struct ProgramRecord39Entry {
        uint32_t NodeIndex{ 0 };
        const void* pRecord{ nullptr };
        uint32_t RecordSizeInBytes{ 0 };
        uint32_t ConcurrencyGroup{ 0 };
        uint32_t QueueAffinityMask{ 0 };
        uint32_t DynamicClusterExpansionTier{ 0 };
        uint32_t TensorCoreMask{ 0 };
        uint32_t SubAllocationMask{ 0 };
        uint32_t PipelineCoherencyTier{ 0 };
        uint32_t FeedbackLoopTier{ 0 };
        uint32_t SubGraphRecursionTier{ 0 };
        uint32_t MeshPipeliningTier{ 0 };
        uint32_t MultiQueueFusionTier{ 0 };
        uint32_t MicroscalingTier{ 0 };
        uint32_t SubBytePrecisionTier{ 0 };
        uint32_t SparseTensorBlockTier{ 0 };
        uint32_t DeterministicTensorReductionTier{ 0 };
        uint32_t HyperQuantizationTier{ 0 };
        uint32_t SparseClusterTier{ 0 };
        uint32_t MultiQueueSyncTier{ 0 };
        uint32_t AsyncKernelDispatchTier{ 0 };
        uint32_t NeuralExecutionEngineTier{ 0 };
        uint32_t AdaptiveTensorCoreTier{ 0 };
        uint32_t SovereignSiliconTelemetryTier{ 0 };
        uint32_t QuantumEmulationTier{ 0 };
        uint32_t DispatchMask{ 0 };
        uint32_t DispatchFlags{ 0 };
    };
    std::vector<ProgramRecord39Entry> m_recordedProgramRecords39;

    struct BackingMemory40Record {
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart{ 0 };
        uint64_t RangeSizeInBytes{ 0 };
        uint64_t ScratchBufferSizeInBytes{ 0 };
        uint64_t MaxConcurrency{ 0 };
        uint32_t DynamicExpansionFlags{ 0 };
        uint32_t MemoryPoolTier{ 0 };
        uint32_t SparsityMask{ 0 };
        uint32_t SubAllocationMask{ 0 };
        uint32_t PipelineCoherencyTier{ 0 };
        uint32_t FeedbackLoopTier{ 0 };
        uint32_t SubGraphRecursionTier{ 0 };
        uint32_t MeshPipeliningTier{ 0 };
        uint32_t MultiQueueFusionTier{ 0 };
        uint32_t MicroscalingTier{ 0 };
        uint32_t SubBytePrecisionTier{ 0 };
        uint32_t SparseTensorBlockTier{ 0 };
        uint32_t DeterministicTensorReductionTier{ 0 };
        uint32_t HyperQuantizationTier{ 0 };
        uint32_t SparseClusterTier{ 0 };
        uint32_t MultiQueueSyncTier{ 0 };
        uint32_t AsyncKernelDispatchTier{ 0 };
        uint32_t NeuralExecutionEngineTier{ 0 };
        uint32_t AdaptiveTensorCoreTier{ 0 };
        uint32_t SovereignSiliconTelemetryTier{ 0 };
        uint32_t QuantumEmulationTier{ 0 };
        uint32_t Flags{ 0 };
    } m_backingMemory40;

    struct ProgramRecord40Entry {
        uint32_t NodeIndex{ 0 };
        const void* pRecord{ nullptr };
        uint32_t RecordSizeInBytes{ 0 };
        uint32_t ConcurrencyGroup{ 0 };
        uint32_t QueueAffinityMask{ 0 };
        uint32_t DynamicClusterExpansionTier{ 0 };
        uint32_t TensorCoreMask{ 0 };
        uint32_t SubAllocationMask{ 0 };
        uint32_t PipelineCoherencyTier{ 0 };
        uint32_t FeedbackLoopTier{ 0 };
        uint32_t SubGraphRecursionTier{ 0 };
        uint32_t MeshPipeliningTier{ 0 };
        uint32_t MultiQueueFusionTier{ 0 };
        uint32_t MicroscalingTier{ 0 };
        uint32_t SubBytePrecisionTier{ 0 };
        uint32_t SparseTensorBlockTier{ 0 };
        uint32_t DeterministicTensorReductionTier{ 0 };
        uint32_t HyperQuantizationTier{ 0 };
        uint32_t SparseClusterTier{ 0 };
        uint32_t MultiQueueSyncTier{ 0 };
        uint32_t AsyncKernelDispatchTier{ 0 };
        uint32_t NeuralExecutionEngineTier{ 0 };
        uint32_t AdaptiveTensorCoreTier{ 0 };
        uint32_t SovereignSiliconTelemetryTier{ 0 };
        uint32_t QuantumEmulationTier{ 0 };
        uint32_t DispatchMask{ 0 };
        uint32_t DispatchFlags{ 0 };
    };
    std::vector<ProgramRecord40Entry> m_recordedProgramRecords40;

    struct BackingMemory41Record {
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart{ 0 };
        uint64_t RangeSizeInBytes{ 0 };
        uint64_t ScratchBufferSizeInBytes{ 0 };
        uint64_t MaxConcurrency{ 0 };
        uint32_t DynamicExpansionFlags{ 0 };
        uint32_t MemoryPoolTier{ 0 };
        uint32_t SparsityMask{ 0 };
        uint32_t SubAllocationMask{ 0 };
        uint32_t PipelineCoherencyTier{ 0 };
        uint32_t FeedbackLoopTier{ 0 };
        uint32_t SubGraphRecursionTier{ 0 };
        uint32_t MeshPipeliningTier{ 0 };
        uint32_t MultiQueueFusionTier{ 0 };
        uint32_t MicroscalingTier{ 0 };
        uint32_t SubBytePrecisionTier{ 0 };
        uint32_t SparseTensorBlockTier{ 0 };
        uint32_t DeterministicTensorReductionTier{ 0 };
        uint32_t HyperQuantizationTier{ 0 };
        uint32_t SparseClusterTier{ 0 };
        uint32_t MultiQueueSyncTier{ 0 };
        uint32_t AsyncKernelDispatchTier{ 0 };
        uint32_t NeuralExecutionEngineTier{ 0 };
        uint32_t AdaptiveTensorCoreTier{ 0 };
        uint32_t SovereignSiliconTelemetryTier{ 0 };
        uint32_t QuantumEmulationTier{ 0 };
        uint32_t Flags{ 0 };
    } m_backingMemory41;

    struct ProgramRecord41Entry {
        uint32_t NodeIndex{ 0 };
        const void* pRecord{ nullptr };
        uint32_t RecordSizeInBytes{ 0 };
        uint32_t ConcurrencyGroup{ 0 };
        uint32_t QueueAffinityMask{ 0 };
        uint32_t DynamicClusterExpansionTier{ 0 };
        uint32_t TensorCoreMask{ 0 };
        uint32_t SubAllocationMask{ 0 };
        uint32_t PipelineCoherencyTier{ 0 };
        uint32_t FeedbackLoopTier{ 0 };
        uint32_t SubGraphRecursionTier{ 0 };
        uint32_t MeshPipeliningTier{ 0 };
        uint32_t MultiQueueFusionTier{ 0 };
        uint32_t MicroscalingTier{ 0 };
        uint32_t SubBytePrecisionTier{ 0 };
        uint32_t SparseTensorBlockTier{ 0 };
        uint32_t DeterministicTensorReductionTier{ 0 };
        uint32_t HyperQuantizationTier{ 0 };
        uint32_t SparseClusterTier{ 0 };
        uint32_t MultiQueueSyncTier{ 0 };
        uint32_t AsyncKernelDispatchTier{ 0 };
        uint32_t NeuralExecutionEngineTier{ 0 };
        uint32_t AdaptiveTensorCoreTier{ 0 };
        uint32_t SovereignSiliconTelemetryTier{ 0 };
        uint32_t QuantumEmulationTier{ 0 };
        uint32_t DispatchMask{ 0 };
        uint32_t DispatchFlags{ 0 };
    };
    std::vector<ProgramRecord41Entry> m_recordedProgramRecords41;

    struct BackingMemory42Record {
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart{ 0 };
        uint64_t RangeSizeInBytes{ 0 };
        uint64_t ScratchBufferSizeInBytes{ 0 };
        uint64_t MaxConcurrency{ 0 };
        uint32_t DynamicExpansionFlags{ 0 };
        uint32_t MemoryPoolTier{ 0 };
        uint32_t SparsityMask{ 0 };
        uint32_t SubAllocationMask{ 0 };
        uint32_t PipelineCoherencyTier{ 0 };
        uint32_t FeedbackLoopTier{ 0 };
        uint32_t SubGraphRecursionTier{ 0 };
        uint32_t MeshPipeliningTier{ 0 };
        uint32_t MultiQueueFusionTier{ 0 };
        uint32_t MicroscalingTier{ 0 };
        uint32_t SubBytePrecisionTier{ 0 };
        uint32_t SparseTensorBlockTier{ 0 };
        uint32_t DeterministicTensorReductionTier{ 0 };
        uint32_t HyperQuantizationTier{ 0 };
        uint32_t SparseClusterTier{ 0 };
        uint32_t MultiQueueSyncTier{ 0 };
        uint32_t AsyncKernelDispatchTier{ 0 };
        uint32_t NeuralExecutionEngineTier{ 0 };
        uint32_t AdaptiveTensorCoreTier{ 0 };
        uint32_t SovereignSiliconTelemetryTier{ 0 };
        uint32_t QuantumEmulationTier{ 0 };
        uint32_t Flags{ 0 };
    } m_backingMemory42;

    struct ProgramRecord42Entry {
        uint32_t NodeIndex{ 0 };
        const void* pRecord{ nullptr };
        uint32_t RecordSizeInBytes{ 0 };
        uint32_t ConcurrencyGroup{ 0 };
        uint32_t QueueAffinityMask{ 0 };
        uint32_t DynamicClusterExpansionTier{ 0 };
        uint32_t TensorCoreMask{ 0 };
        uint32_t SubAllocationMask{ 0 };
        uint32_t PipelineCoherencyTier{ 0 };
        uint32_t FeedbackLoopTier{ 0 };
        uint32_t SubGraphRecursionTier{ 0 };
        uint32_t MeshPipeliningTier{ 0 };
        uint32_t MultiQueueFusionTier{ 0 };
        uint32_t MicroscalingTier{ 0 };
        uint32_t SubBytePrecisionTier{ 0 };
        uint32_t SparseTensorBlockTier{ 0 };
        uint32_t DeterministicTensorReductionTier{ 0 };
        uint32_t HyperQuantizationTier{ 0 };
        uint32_t SparseClusterTier{ 0 };
        uint32_t MultiQueueSyncTier{ 0 };
        uint32_t AsyncKernelDispatchTier{ 0 };
        uint32_t NeuralExecutionEngineTier{ 0 };
        uint32_t AdaptiveTensorCoreTier{ 0 };
        uint32_t SovereignSiliconTelemetryTier{ 0 };
        uint32_t QuantumEmulationTier{ 0 };
        uint32_t DispatchMask{ 0 };
        uint32_t DispatchFlags{ 0 };
    };
    std::vector<ProgramRecord42Entry> m_recordedProgramRecords42;

    struct BackingMemory43Record {
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart{ 0 };
        uint64_t RangeSizeInBytes{ 0 };
        uint64_t ScratchBufferSizeInBytes{ 0 };
        uint64_t MaxConcurrency{ 0 };
        uint32_t DynamicExpansionFlags{ 0 };
        uint32_t MemoryPoolTier{ 0 };
        uint32_t SparsityMask{ 0 };
        uint32_t SubAllocationMask{ 0 };
        uint32_t PipelineCoherencyTier{ 0 };
        uint32_t FeedbackLoopTier{ 0 };
        uint32_t SubGraphRecursionTier{ 0 };
        uint32_t MeshPipeliningTier{ 0 };
        uint32_t MultiQueueFusionTier{ 0 };
        uint32_t MicroscalingTier{ 0 };
        uint32_t SubBytePrecisionTier{ 0 };
        uint32_t SparseTensorBlockTier{ 0 };
        uint32_t DeterministicTensorReductionTier{ 0 };
        uint32_t HyperQuantizationTier{ 0 };
        uint32_t SparseClusterTier{ 0 };
        uint32_t MultiQueueSyncTier{ 0 };
        uint32_t AsyncKernelDispatchTier{ 0 };
        uint32_t NeuralExecutionEngineTier{ 0 };
        uint32_t AdaptiveTensorCoreTier{ 0 };
        uint32_t SovereignSiliconTelemetryTier{ 0 };
        uint32_t QuantumEmulationTier{ 0 };
        uint32_t Flags{ 0 };
    } m_backingMemory43;

    struct ProgramRecord43Entry {
        uint32_t NodeIndex{ 0 };
        const void* pRecord{ nullptr };
        uint32_t RecordSizeInBytes{ 0 };
        uint32_t ConcurrencyGroup{ 0 };
        uint32_t QueueAffinityMask{ 0 };
        uint32_t DynamicClusterExpansionTier{ 0 };
        uint32_t TensorCoreMask{ 0 };
        uint32_t SubAllocationMask{ 0 };
        uint32_t PipelineCoherencyTier{ 0 };
        uint32_t FeedbackLoopTier{ 0 };
        uint32_t SubGraphRecursionTier{ 0 };
        uint32_t MeshPipeliningTier{ 0 };
        uint32_t MultiQueueFusionTier{ 0 };
        uint32_t MicroscalingTier{ 0 };
        uint32_t SubBytePrecisionTier{ 0 };
        uint32_t SparseTensorBlockTier{ 0 };
        uint32_t DeterministicTensorReductionTier{ 0 };
        uint32_t HyperQuantizationTier{ 0 };
        uint32_t SparseClusterTier{ 0 };
        uint32_t MultiQueueSyncTier{ 0 };
        uint32_t AsyncKernelDispatchTier{ 0 };
        uint32_t NeuralExecutionEngineTier{ 0 };
        uint32_t AdaptiveTensorCoreTier{ 0 };
        uint32_t SovereignSiliconTelemetryTier{ 0 };
        uint32_t QuantumEmulationTier{ 0 };
        uint32_t DispatchMask{ 0 };
        uint32_t DispatchFlags{ 0 };
    };
    std::vector<ProgramRecord43Entry> m_recordedProgramRecords43;

    struct BackingMemory44Record {
        D3D12_GPU_VIRTUAL_ADDRESS RangeStart{ 0 };
        uint64_t RangeSizeInBytes{ 0 };
        uint64_t ScratchBufferSizeInBytes{ 0 };
        uint64_t MaxConcurrency{ 0 };
        uint32_t DynamicExpansionFlags{ 0 };
        uint32_t MemoryPoolTier{ 0 };
        uint32_t SparsityMask{ 0 };
        uint32_t SubAllocationMask{ 0 };
        uint32_t PipelineCoherencyTier{ 0 };
        uint32_t FeedbackLoopTier{ 0 };
        uint32_t SubGraphRecursionTier{ 0 };
        uint32_t MeshPipeliningTier{ 0 };
        uint32_t MultiQueueFusionTier{ 0 };
        uint32_t MicroscalingTier{ 0 };
        uint32_t SubBytePrecisionTier{ 0 };
        uint32_t SparseTensorBlockTier{ 0 };
        uint32_t DeterministicTensorReductionTier{ 0 };
        uint32_t HyperQuantizationTier{ 0 };
        uint32_t SparseClusterTier{ 0 };
        uint32_t MultiQueueSyncTier{ 0 };
        uint32_t AsyncKernelDispatchTier{ 0 };
        uint32_t NeuralExecutionEngineTier{ 0 };
        uint32_t AdaptiveTensorCoreTier{ 0 };
        uint32_t SovereignSiliconTelemetryTier{ 0 };
        uint32_t QuantumEmulationTier{ 0 };
        uint32_t Flags{ 0 };
    } m_backingMemory44;

    struct ProgramRecord44Entry {
        uint32_t NodeIndex{ 0 };
        const void* pRecord{ nullptr };
        uint32_t RecordSizeInBytes{ 0 };
        uint32_t ConcurrencyGroup{ 0 };
        uint32_t QueueAffinityMask{ 0 };
        uint32_t DynamicClusterExpansionTier{ 0 };
        uint32_t TensorCoreMask{ 0 };
        uint32_t SubAllocationMask{ 0 };
        uint32_t PipelineCoherencyTier{ 0 };
        uint32_t FeedbackLoopTier{ 0 };
        uint32_t SubGraphRecursionTier{ 0 };
        uint32_t MeshPipeliningTier{ 0 };
        uint32_t MultiQueueFusionTier{ 0 };
        uint32_t MicroscalingTier{ 0 };
        uint32_t SubBytePrecisionTier{ 0 };
        uint32_t SparseTensorBlockTier{ 0 };
        uint32_t DeterministicTensorReductionTier{ 0 };
        uint32_t HyperQuantizationTier{ 0 };
        uint32_t SparseClusterTier{ 0 };
        uint32_t MultiQueueSyncTier{ 0 };
        uint32_t AsyncKernelDispatchTier{ 0 };
        uint32_t NeuralExecutionEngineTier{ 0 };
        uint32_t AdaptiveTensorCoreTier{ 0 };
        uint32_t SovereignSiliconTelemetryTier{ 0 };
        uint32_t QuantumEmulationTier{ 0 };
        uint32_t DispatchMask{ 0 };
        uint32_t DispatchFlags{ 0 };
    };
    std::vector<ProgramRecord44Entry> m_recordedProgramRecords44;

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
        if (riid == OFFICIAL_IID_ID3D12GraphicsCommandList17 || riid == IID_ID3D12GraphicsCommandList17) {
            *ppv = static_cast<ID3D12GraphicsCommandList17*>(this);
            AddRef();
            return 0;
        }
        if (riid == OFFICIAL_IID_ID3D12GraphicsCommandList18 || riid == IID_ID3D12GraphicsCommandList18) {
            *ppv = static_cast<ID3D12GraphicsCommandList18*>(this);
            AddRef();
            return 0;
        }
        if (riid == OFFICIAL_IID_ID3D12GraphicsCommandList19 || riid == IID_ID3D12GraphicsCommandList19) {
            *ppv = static_cast<ID3D12GraphicsCommandList19*>(this);
            AddRef();
            return 0;
        }
        if (riid == OFFICIAL_IID_ID3D12GraphicsCommandList20 || riid == IID_ID3D12GraphicsCommandList20) {
            *ppv = static_cast<ID3D12GraphicsCommandList20*>(this);
            AddRef();
            return 0;
        }
        if (riid == OFFICIAL_IID_ID3D12GraphicsCommandList21 || riid == IID_ID3D12GraphicsCommandList21) {
            *ppv = static_cast<ID3D12GraphicsCommandList21*>(this);
            AddRef();
            return 0;
        }
        if (riid == OFFICIAL_IID_ID3D12GraphicsCommandList22 || riid == IID_ID3D12GraphicsCommandList22) {
            *ppv = static_cast<ID3D12GraphicsCommandList22*>(this);
            AddRef();
            return 0;
        }
        if (riid == OFFICIAL_IID_ID3D12GraphicsCommandList23 || riid == IID_ID3D12GraphicsCommandList23) {
            *ppv = static_cast<ID3D12GraphicsCommandList23*>(this);
            AddRef();
            return 0;
        }
        if (riid == OFFICIAL_IID_ID3D12GraphicsCommandList24 || riid == IID_ID3D12GraphicsCommandList24) {
            *ppv = static_cast<ID3D12GraphicsCommandList24*>(this);
            AddRef();
            return 0;
        }
        if (riid == OFFICIAL_IID_ID3D12GraphicsCommandList25 || riid == IID_ID3D12GraphicsCommandList25) {
            *ppv = static_cast<ID3D12GraphicsCommandList25*>(this);
            AddRef();
            return 0;
        }
        if (riid == OFFICIAL_IID_ID3D12GraphicsCommandList26 || riid == IID_ID3D12GraphicsCommandList26) {
            *ppv = static_cast<ID3D12GraphicsCommandList26*>(this);
            AddRef();
            return 0;
        }
        if (riid == OFFICIAL_IID_ID3D12GraphicsCommandList27 || riid == IID_ID3D12GraphicsCommandList27) {
            *ppv = static_cast<ID3D12GraphicsCommandList27*>(this);
            AddRef();
            return 0;
        }
        if (riid == OFFICIAL_IID_ID3D12GraphicsCommandList28 || riid == IID_ID3D12GraphicsCommandList28) {
            *ppv = static_cast<ID3D12GraphicsCommandList28*>(this);
            AddRef();
            return 0;
        }
        if (riid == OFFICIAL_IID_ID3D12GraphicsCommandList29 || riid == IID_ID3D12GraphicsCommandList29) {
            *ppv = static_cast<ID3D12GraphicsCommandList29*>(this);
            AddRef();
            return 0;
        }
        if (riid == OFFICIAL_IID_ID3D12GraphicsCommandList30 || riid == IID_ID3D12GraphicsCommandList30) {
            *ppv = static_cast<ID3D12GraphicsCommandList30*>(this);
            AddRef();
            return 0;
        }
        if (riid == OFFICIAL_IID_ID3D12GraphicsCommandList31 || riid == IID_ID3D12GraphicsCommandList31) {
            *ppv = static_cast<ID3D12GraphicsCommandList31*>(this);
            AddRef();
            return 0;
        }
        if (riid == OFFICIAL_IID_ID3D12GraphicsCommandList32 || riid == IID_ID3D12GraphicsCommandList32) {
            *ppv = static_cast<ID3D12GraphicsCommandList32*>(this);
            AddRef();
            return 0;
        }
        if (riid == OFFICIAL_IID_ID3D12GraphicsCommandList33 || riid == IID_ID3D12GraphicsCommandList33) {
            *ppv = static_cast<ID3D12GraphicsCommandList33*>(this);
            AddRef();
            return 0;
        }
        if (riid == OFFICIAL_IID_ID3D12GraphicsCommandList34 || riid == IID_ID3D12GraphicsCommandList34) {
            *ppv = static_cast<ID3D12GraphicsCommandList34*>(this);
            AddRef();
            return 0;
        }
        if (riid == OFFICIAL_IID_ID3D12GraphicsCommandList35 || riid == IID_ID3D12GraphicsCommandList35) {
            *ppv = static_cast<ID3D12GraphicsCommandList35*>(this);
            AddRef();
            return 0;
        }
        if (riid == OFFICIAL_IID_ID3D12GraphicsCommandList36 || riid == IID_ID3D12GraphicsCommandList36 ||
            riid == OFFICIAL_IID_ID3D12GraphicsCommandList37 || riid == IID_ID3D12GraphicsCommandList37 ||
            riid == OFFICIAL_IID_ID3D12GraphicsCommandList38 || riid == IID_ID3D12GraphicsCommandList38 ||
            riid == OFFICIAL_IID_ID3D12GraphicsCommandList39 || riid == IID_ID3D12GraphicsCommandList39 ||
            riid == OFFICIAL_IID_ID3D12GraphicsCommandList40 || riid == IID_ID3D12GraphicsCommandList40 ||
            riid == OFFICIAL_IID_ID3D12GraphicsCommandList41 || riid == IID_ID3D12GraphicsCommandList41 ||
            riid == OFFICIAL_IID_ID3D12GraphicsCommandList42 || riid == IID_ID3D12GraphicsCommandList42 ||
            riid == OFFICIAL_IID_ID3D12GraphicsCommandList43 || riid == IID_ID3D12GraphicsCommandList43 ||
            riid == OFFICIAL_IID_ID3D12GraphicsCommandList44 || riid == IID_ID3D12GraphicsCommandList44 ||
            riid == OFFICIAL_IID_ID3D12GraphicsCommandList45 || riid == IID_ID3D12GraphicsCommandList45 ||
            riid == OFFICIAL_IID_ID3D12GraphicsCommandList46 || riid == IID_ID3D12GraphicsCommandList46 ||
            riid == OFFICIAL_IID_ID3D12GraphicsCommandList47 || riid == IID_ID3D12GraphicsCommandList47 ||
            riid == OFFICIAL_IID_ID3D12GraphicsCommandList48 || riid == IID_ID3D12GraphicsCommandList48 ||
            riid == OFFICIAL_IID_ID3D12GraphicsCommandList49 || riid == IID_ID3D12GraphicsCommandList49 ||
            riid == OFFICIAL_IID_ID3D12GraphicsCommandList50 || riid == IID_ID3D12GraphicsCommandList50 ||
            riid == OFFICIAL_IID_ID3D12GraphicsCommandList51 || riid == IID_ID3D12GraphicsCommandList51 ||
            riid == OFFICIAL_IID_ID3D12GraphicsCommandList52 || riid == IID_ID3D12GraphicsCommandList52 ||
            riid == OFFICIAL_IID_ID3D12GraphicsCommandList53 || riid == IID_ID3D12GraphicsCommandList53 ||
            riid == OFFICIAL_IID_ID3D12GraphicsCommandList54 || riid == IID_ID3D12GraphicsCommandList54) {
            *ppv = static_cast<ID3D12GraphicsCommandList54*>(this);
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
        m_backingMemory7 = {};
        m_recordedProgramRecords7.clear();
        m_backingMemory8 = {};
        m_recordedProgramRecords8.clear();
        m_backingMemory9 = {};
        m_recordedProgramRecords9.clear();
        m_backingMemory10 = {};
        m_recordedProgramRecords10.clear();
        m_backingMemory11 = {};
        m_recordedProgramRecords11.clear();
        m_backingMemory12 = {};
        m_recordedProgramRecords12.clear();
        m_backingMemory13 = {};
        m_recordedProgramRecords13.clear();
        m_backingMemory14 = {};
        m_recordedProgramRecords14.clear();
        m_backingMemory15 = {};
        m_recordedProgramRecords15.clear();
        m_backingMemory16 = {};
        m_recordedProgramRecords16.clear();
        m_backingMemory17 = {};
        m_recordedProgramRecords17.clear();
        m_backingMemory18 = {};
        m_recordedProgramRecords18.clear();
        m_backingMemory19 = {};
        m_recordedProgramRecords19.clear();
        m_backingMemory20 = {};
        m_recordedProgramRecords20.clear();
        m_backingMemory21 = {};
        m_recordedProgramRecords21.clear();
        m_backingMemory22 = {};
        m_recordedProgramRecords22.clear();
        m_backingMemory23 = {};
        m_recordedProgramRecords23.clear();
        m_backingMemory24 = {};
        m_recordedProgramRecords24.clear();
        m_backingMemory25 = {};
        m_recordedProgramRecords25.clear();
        m_backingMemory26 = {};
        m_recordedProgramRecords26.clear();
        m_backingMemory27 = {};
        m_recordedProgramRecords27.clear();
        m_backingMemory28 = {};
        m_recordedProgramRecords28.clear();
        m_backingMemory29 = {};
        m_recordedProgramRecords29.clear();
        m_backingMemory30 = {};
        m_recordedProgramRecords30.clear();
        m_backingMemory31 = {};
        m_recordedProgramRecords31.clear();
        m_backingMemory32 = {};
        m_recordedProgramRecords32.clear();
        m_backingMemory33 = {};
        m_recordedProgramRecords33.clear();
        m_backingMemory34 = {};
        m_recordedProgramRecords34.clear();
        m_backingMemory35 = {};
        m_recordedProgramRecords35.clear();
        m_backingMemory36 = {};
        m_recordedProgramRecords36.clear();
        m_backingMemory37 = {};
        m_recordedProgramRecords37.clear();
        m_backingMemory38 = {};
        m_recordedProgramRecords38.clear();
        m_backingMemory39 = {};
        m_recordedProgramRecords39.clear();
        m_backingMemory40 = {};
        m_recordedProgramRecords40.clear();
        m_backingMemory41 = {};
        m_recordedProgramRecords41.clear();
        m_backingMemory42 = {};
        m_recordedProgramRecords42.clear();
        m_backingMemory43 = {};
        m_recordedProgramRecords43.clear();
        m_backingMemory44 = {};
        m_recordedProgramRecords44.clear();
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
        m_backingMemory7 = {};
        m_recordedProgramRecords7.clear();
        m_backingMemory8 = {};
        m_recordedProgramRecords8.clear();
        m_backingMemory9 = {};
        m_recordedProgramRecords9.clear();
        m_backingMemory10 = {};
        m_recordedProgramRecords10.clear();
        m_backingMemory11 = {};
        m_recordedProgramRecords11.clear();
        m_backingMemory12 = {};
        m_recordedProgramRecords12.clear();
        m_backingMemory13 = {};
        m_recordedProgramRecords13.clear();
        m_backingMemory14 = {};
        m_recordedProgramRecords14.clear();
        m_backingMemory15 = {};
        m_recordedProgramRecords15.clear();
        m_backingMemory16 = {};
        m_recordedProgramRecords16.clear();
        m_backingMemory17 = {};
        m_recordedProgramRecords17.clear();
        m_backingMemory18 = {};
        m_recordedProgramRecords18.clear();
        m_backingMemory19 = {};
        m_recordedProgramRecords19.clear();
        m_backingMemory20 = {};
        m_recordedProgramRecords20.clear();
        m_backingMemory21 = {};
        m_recordedProgramRecords21.clear();
        m_backingMemory22 = {};
        m_recordedProgramRecords22.clear();
        m_backingMemory23 = {};
        m_recordedProgramRecords23.clear();
        m_backingMemory24 = {};
        m_recordedProgramRecords24.clear();
        m_backingMemory25 = {};
        m_recordedProgramRecords25.clear();
        m_backingMemory26 = {};
        m_recordedProgramRecords26.clear();
        m_backingMemory27 = {};
        m_recordedProgramRecords27.clear();
        m_backingMemory28 = {};
        m_recordedProgramRecords28.clear();
        m_backingMemory29 = {};
        m_recordedProgramRecords29.clear();
        m_backingMemory30 = {};
        m_recordedProgramRecords30.clear();
        m_backingMemory31 = {};
        m_recordedProgramRecords31.clear();
        m_backingMemory32 = {};
        m_recordedProgramRecords32.clear();
        m_backingMemory33 = {};
        m_recordedProgramRecords33.clear();
        m_backingMemory34 = {};
        m_recordedProgramRecords34.clear();
        m_backingMemory35 = {};
        m_recordedProgramRecords35.clear();
        m_backingMemory36 = {};
        m_recordedProgramRecords36.clear();
        m_backingMemory37 = {};
        m_recordedProgramRecords37.clear();
        m_backingMemory38 = {};
        m_recordedProgramRecords38.clear();
        m_backingMemory39 = {};
        m_recordedProgramRecords39.clear();
        m_backingMemory40 = {};
        m_recordedProgramRecords40.clear();
        m_backingMemory41 = {};
        m_recordedProgramRecords41.clear();
        m_backingMemory42 = {};
        m_recordedProgramRecords42.clear();
        m_backingMemory43 = {};
        m_recordedProgramRecords43.clear();
        m_backingMemory44 = {};
        m_recordedProgramRecords44.clear();
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

    // ID3D12GraphicsCommandList17
    void SetWorkGraphBackingMemory7(D3D12_GPU_VIRTUAL_ADDRESS RangeStart, uint64_t RangeSizeInBytes, uint64_t ScratchBufferSizeInBytes, uint32_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t Flags) override {
        m_backingMemory7 = { RangeStart, RangeSizeInBytes, ScratchBufferSizeInBytes, MaxConcurrency, DynamicExpansionFlags, MemoryPoolTier, Flags };
    }

    void DispatchGraphProgramRecord7(uint32_t NodeIndex, const void* pRecord, uint32_t RecordSizeInBytes, uint32_t ConcurrencyGroup, uint32_t QueueAffinityMask, uint32_t DynamicClusterExpansionTier, uint32_t DispatchMask, uint32_t DispatchFlags) override {
        m_recordedProgramRecords7.push_back({ NodeIndex, pRecord, RecordSizeInBytes, ConcurrencyGroup, QueueAffinityMask, DynamicClusterExpansionTier, DispatchMask, DispatchFlags });
    }

    const BackingMemory7Record& GetWorkGraphBackingMemory7() const noexcept { return m_backingMemory7; }
    size_t GetRecordedProgramRecord7Count() const noexcept { return m_recordedProgramRecords7.size(); }
    const std::vector<ProgramRecord7Entry>& GetRecordedProgramRecords7() const noexcept { return m_recordedProgramRecords7; }

    // ID3D12GraphicsCommandList18
    void SetWorkGraphBackingMemory8(D3D12_GPU_VIRTUAL_ADDRESS RangeStart, uint64_t RangeSizeInBytes, uint64_t ScratchBufferSizeInBytes, uint32_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t SparsityMask, uint32_t Flags) override {
        m_backingMemory8 = { RangeStart, RangeSizeInBytes, ScratchBufferSizeInBytes, MaxConcurrency, DynamicExpansionFlags, MemoryPoolTier, SparsityMask, Flags };
    }

    void DispatchGraphProgramRecord8(uint32_t NodeIndex, const void* pRecord, uint32_t RecordSizeInBytes, uint32_t ConcurrencyGroup, uint32_t QueueAffinityMask, uint32_t DynamicClusterExpansionTier, uint32_t TensorCoreMask, uint32_t DispatchMask, uint32_t DispatchFlags) override {
        m_recordedProgramRecords8.push_back({ NodeIndex, pRecord, RecordSizeInBytes, ConcurrencyGroup, QueueAffinityMask, DynamicClusterExpansionTier, TensorCoreMask, DispatchMask, DispatchFlags });
    }

    const BackingMemory8Record& GetWorkGraphBackingMemory8() const noexcept { return m_backingMemory8; }
    size_t GetRecordedProgramRecord8Count() const noexcept { return m_recordedProgramRecords8.size(); }
    const std::vector<ProgramRecord8Entry>& GetRecordedProgramRecords8() const noexcept { return m_recordedProgramRecords8; }

    // ID3D12GraphicsCommandList19
    void SetWorkGraphBackingMemory9(D3D12_GPU_VIRTUAL_ADDRESS RangeStart, uint64_t RangeSizeInBytes, uint64_t ScratchBufferSizeInBytes, uint32_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t SparsityMask, uint32_t SubAllocationMask, uint32_t Flags) override {
        m_backingMemory9 = { RangeStart, RangeSizeInBytes, ScratchBufferSizeInBytes, MaxConcurrency, DynamicExpansionFlags, MemoryPoolTier, SparsityMask, SubAllocationMask, Flags };
    }

    void DispatchGraphProgramRecord9(uint32_t NodeIndex, const void* pRecord, uint32_t RecordSizeInBytes, uint32_t ConcurrencyGroup, uint32_t QueueAffinityMask, uint32_t DynamicClusterExpansionTier, uint32_t TensorCoreMask, uint32_t SubAllocationMask, uint32_t DispatchMask, uint32_t DispatchFlags) override {
        m_recordedProgramRecords9.push_back({ NodeIndex, pRecord, RecordSizeInBytes, ConcurrencyGroup, QueueAffinityMask, DynamicClusterExpansionTier, TensorCoreMask, SubAllocationMask, DispatchMask, DispatchFlags });
    }

    const BackingMemory9Record& GetWorkGraphBackingMemory9() const noexcept { return m_backingMemory9; }
    size_t GetRecordedProgramRecord9Count() const noexcept { return m_recordedProgramRecords9.size(); }
    const std::vector<ProgramRecord9Entry>& GetRecordedProgramRecords9() const noexcept { return m_recordedProgramRecords9; }

    // ID3D12GraphicsCommandList20
    void SetWorkGraphBackingMemory10(D3D12_GPU_VIRTUAL_ADDRESS RangeStart, uint64_t RangeSizeInBytes, uint64_t ScratchBufferSizeInBytes, uint32_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t SparsityMask, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t Flags) override {
        m_backingMemory10 = { RangeStart, RangeSizeInBytes, ScratchBufferSizeInBytes, MaxConcurrency, DynamicExpansionFlags, MemoryPoolTier, SparsityMask, SubAllocationMask, PipelineCoherencyTier, Flags };
    }

    void DispatchGraphProgramRecord10(uint32_t NodeIndex, const void* pRecord, uint32_t RecordSizeInBytes, uint32_t ConcurrencyGroup, uint32_t QueueAffinityMask, uint32_t DynamicClusterExpansionTier, uint32_t TensorCoreMask, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t DispatchMask, uint32_t DispatchFlags) override {
        m_recordedProgramRecords10.push_back({ NodeIndex, pRecord, RecordSizeInBytes, ConcurrencyGroup, QueueAffinityMask, DynamicClusterExpansionTier, TensorCoreMask, SubAllocationMask, PipelineCoherencyTier, DispatchMask, DispatchFlags });
    }

    const BackingMemory10Record& GetWorkGraphBackingMemory10() const noexcept { return m_backingMemory10; }
    size_t GetRecordedProgramRecord10Count() const noexcept { return m_recordedProgramRecords10.size(); }
    const std::vector<ProgramRecord10Entry>& GetRecordedProgramRecords10() const noexcept { return m_recordedProgramRecords10; }

    // ID3D12GraphicsCommandList21
    void SetWorkGraphBackingMemory11(D3D12_GPU_VIRTUAL_ADDRESS RangeStart, uint64_t RangeSizeInBytes, uint64_t ScratchBufferSizeInBytes, uint32_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t SparsityMask, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t Flags) override {
        m_backingMemory11 = { RangeStart, RangeSizeInBytes, ScratchBufferSizeInBytes, MaxConcurrency, DynamicExpansionFlags, MemoryPoolTier, SparsityMask, SubAllocationMask, PipelineCoherencyTier, FeedbackLoopTier, Flags };
    }

    void DispatchGraphProgramRecord11(uint32_t NodeIndex, const void* pRecord, uint32_t RecordSizeInBytes, uint32_t ConcurrencyGroup, uint32_t QueueAffinityMask, uint32_t DynamicClusterExpansionTier, uint32_t TensorCoreMask, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t DispatchMask, uint32_t DispatchFlags) override {
        m_recordedProgramRecords11.push_back({ NodeIndex, pRecord, RecordSizeInBytes, ConcurrencyGroup, QueueAffinityMask, DynamicClusterExpansionTier, TensorCoreMask, SubAllocationMask, PipelineCoherencyTier, FeedbackLoopTier, DispatchMask, DispatchFlags });
    }

    const BackingMemory11Record& GetWorkGraphBackingMemory11() const noexcept { return m_backingMemory11; }
    size_t GetRecordedProgramRecord11Count() const noexcept { return m_recordedProgramRecords11.size(); }
    const std::vector<ProgramRecord11Entry>& GetRecordedProgramRecords11() const noexcept { return m_recordedProgramRecords11; }

    // ID3D12GraphicsCommandList22
    void SetWorkGraphBackingMemory12(D3D12_GPU_VIRTUAL_ADDRESS RangeStart, uint64_t RangeSizeInBytes, uint64_t ScratchBufferSizeInBytes, uint32_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t SparsityMask, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t Flags) override {
        m_backingMemory12 = { RangeStart, RangeSizeInBytes, ScratchBufferSizeInBytes, MaxConcurrency, DynamicExpansionFlags, MemoryPoolTier, SparsityMask, SubAllocationMask, PipelineCoherencyTier, FeedbackLoopTier, SubGraphRecursionTier, Flags };
    }

    void DispatchGraphProgramRecord12(uint32_t NodeIndex, const void* pRecord, uint32_t RecordSizeInBytes, uint32_t ConcurrencyGroup, uint32_t QueueAffinityMask, uint32_t DynamicClusterExpansionTier, uint32_t TensorCoreMask, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t DispatchMask, uint32_t DispatchFlags) override {
        m_recordedProgramRecords12.push_back({ NodeIndex, pRecord, RecordSizeInBytes, ConcurrencyGroup, QueueAffinityMask, DynamicClusterExpansionTier, TensorCoreMask, SubAllocationMask, PipelineCoherencyTier, FeedbackLoopTier, SubGraphRecursionTier, DispatchMask, DispatchFlags });
    }

    const BackingMemory12Record& GetWorkGraphBackingMemory12() const noexcept { return m_backingMemory12; }
    size_t GetRecordedProgramRecord12Count() const noexcept { return m_recordedProgramRecords12.size(); }
    const std::vector<ProgramRecord12Entry>& GetRecordedProgramRecords12() const noexcept { return m_recordedProgramRecords12; }

    // ID3D12GraphicsCommandList23
    void SetWorkGraphBackingMemory13(D3D12_GPU_VIRTUAL_ADDRESS RangeStart, uint64_t RangeSizeInBytes, uint64_t ScratchBufferSizeInBytes, uint32_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t SparsityMask, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t Flags) override {
        m_backingMemory13 = { RangeStart, RangeSizeInBytes, ScratchBufferSizeInBytes, MaxConcurrency, DynamicExpansionFlags, MemoryPoolTier, SparsityMask, SubAllocationMask, PipelineCoherencyTier, FeedbackLoopTier, SubGraphRecursionTier, MeshPipeliningTier, Flags };
    }

    void DispatchGraphProgramRecord13(uint32_t NodeIndex, const void* pRecord, uint32_t RecordSizeInBytes, uint32_t ConcurrencyGroup, uint32_t QueueAffinityMask, uint32_t DynamicClusterExpansionTier, uint32_t TensorCoreMask, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t DispatchMask, uint32_t DispatchFlags) override {
        m_recordedProgramRecords13.push_back({ NodeIndex, pRecord, RecordSizeInBytes, ConcurrencyGroup, QueueAffinityMask, DynamicClusterExpansionTier, TensorCoreMask, SubAllocationMask, PipelineCoherencyTier, FeedbackLoopTier, SubGraphRecursionTier, MeshPipeliningTier, DispatchMask, DispatchFlags });
    }

    const BackingMemory13Record& GetWorkGraphBackingMemory13() const noexcept { return m_backingMemory13; }
    size_t GetRecordedProgramRecord13Count() const noexcept { return m_recordedProgramRecords13.size(); }
    const std::vector<ProgramRecord13Entry>& GetRecordedProgramRecords13() const noexcept { return m_recordedProgramRecords13; }

    // ID3D12GraphicsCommandList24
    void SetWorkGraphBackingMemory14(D3D12_GPU_VIRTUAL_ADDRESS RangeStart, uint64_t RangeSizeInBytes, uint64_t ScratchBufferSizeInBytes, uint32_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t SparsityMask, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t Flags) override {
        m_backingMemory14 = { RangeStart, RangeSizeInBytes, ScratchBufferSizeInBytes, MaxConcurrency, DynamicExpansionFlags, MemoryPoolTier, SparsityMask, SubAllocationMask, PipelineCoherencyTier, FeedbackLoopTier, SubGraphRecursionTier, MeshPipeliningTier, MultiQueueFusionTier, Flags };
    }

    void DispatchGraphProgramRecord14(uint32_t NodeIndex, const void* pRecord, uint32_t RecordSizeInBytes, uint32_t ConcurrencyGroup, uint32_t QueueAffinityMask, uint32_t DynamicClusterExpansionTier, uint32_t TensorCoreMask, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t DispatchMask, uint32_t DispatchFlags) override {
        m_recordedProgramRecords14.push_back({ NodeIndex, pRecord, RecordSizeInBytes, ConcurrencyGroup, QueueAffinityMask, DynamicClusterExpansionTier, TensorCoreMask, SubAllocationMask, PipelineCoherencyTier, FeedbackLoopTier, SubGraphRecursionTier, MeshPipeliningTier, MultiQueueFusionTier, DispatchMask, DispatchFlags });
    }

    const BackingMemory14Record& GetWorkGraphBackingMemory14() const noexcept { return m_backingMemory14; }
    size_t GetRecordedProgramRecord14Count() const noexcept { return m_recordedProgramRecords14.size(); }
    const std::vector<ProgramRecord14Entry>& GetRecordedProgramRecords14() const noexcept { return m_recordedProgramRecords14; }
    // ID3D12GraphicsCommandList25
    void SetWorkGraphBackingMemory15(D3D12_GPU_VIRTUAL_ADDRESS RangeStart, uint64_t RangeSizeInBytes, uint64_t ScratchBufferSizeInBytes, uint32_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t SparsityMask, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t Flags) override {
        m_backingMemory15 = { RangeStart, RangeSizeInBytes, ScratchBufferSizeInBytes, MaxConcurrency, DynamicExpansionFlags, MemoryPoolTier, SparsityMask, SubAllocationMask, PipelineCoherencyTier, FeedbackLoopTier, SubGraphRecursionTier, MeshPipeliningTier, MultiQueueFusionTier, MicroscalingTier, Flags };
    }

    void DispatchGraphProgramRecord15(uint32_t NodeIndex, const void* pRecord, uint32_t RecordSizeInBytes, uint32_t ConcurrencyGroup, uint32_t QueueAffinityMask, uint32_t DynamicClusterExpansionTier, uint32_t TensorCoreMask, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t DispatchMask, uint32_t DispatchFlags) override {
        m_recordedProgramRecords15.push_back({ NodeIndex, pRecord, RecordSizeInBytes, ConcurrencyGroup, QueueAffinityMask, DynamicClusterExpansionTier, TensorCoreMask, SubAllocationMask, PipelineCoherencyTier, FeedbackLoopTier, SubGraphRecursionTier, MeshPipeliningTier, MultiQueueFusionTier, MicroscalingTier, DispatchMask, DispatchFlags });
    }

    const BackingMemory15Record& GetWorkGraphBackingMemory15() const noexcept { return m_backingMemory15; }
    size_t GetRecordedProgramRecord15Count() const noexcept { return m_recordedProgramRecords15.size(); }
    const std::vector<ProgramRecord15Entry>& GetRecordedProgramRecords15() const noexcept { return m_recordedProgramRecords15; }

    // ID3D12GraphicsCommandList26
    void SetWorkGraphBackingMemory16(D3D12_GPU_VIRTUAL_ADDRESS RangeStart, uint64_t RangeSizeInBytes, uint64_t ScratchBufferSizeInBytes, uint32_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t SparsityMask, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t Flags) override {
        m_backingMemory16 = { RangeStart, RangeSizeInBytes, ScratchBufferSizeInBytes, MaxConcurrency, DynamicExpansionFlags, MemoryPoolTier, SparsityMask, SubAllocationMask, PipelineCoherencyTier, FeedbackLoopTier, SubGraphRecursionTier, MeshPipeliningTier, MultiQueueFusionTier, MicroscalingTier, SubBytePrecisionTier, Flags };
    }

    void DispatchGraphProgramRecord16(uint32_t NodeIndex, const void* pRecord, uint32_t RecordSizeInBytes, uint32_t ConcurrencyGroup, uint32_t QueueAffinityMask, uint32_t DynamicClusterExpansionTier, uint32_t TensorCoreMask, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t DispatchMask, uint32_t DispatchFlags) override {
        m_recordedProgramRecords16.push_back({ NodeIndex, pRecord, RecordSizeInBytes, ConcurrencyGroup, QueueAffinityMask, DynamicClusterExpansionTier, TensorCoreMask, SubAllocationMask, PipelineCoherencyTier, FeedbackLoopTier, SubGraphRecursionTier, MeshPipeliningTier, MultiQueueFusionTier, MicroscalingTier, SubBytePrecisionTier, DispatchMask, DispatchFlags });
    }

    const BackingMemory16Record& GetWorkGraphBackingMemory16() const noexcept { return m_backingMemory16; }
    size_t GetRecordedProgramRecord16Count() const noexcept { return m_recordedProgramRecords16.size(); }
    const std::vector<ProgramRecord16Entry>& GetRecordedProgramRecords16() const noexcept { return m_recordedProgramRecords16; }

    // ID3D12GraphicsCommandList27
    void SetWorkGraphBackingMemory17(D3D12_GPU_VIRTUAL_ADDRESS RangeStart, uint64_t RangeSizeInBytes, uint64_t ScratchBufferSizeInBytes, uint32_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t SparsityMask, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t Flags) override {
        m_backingMemory17 = { RangeStart, RangeSizeInBytes, ScratchBufferSizeInBytes, MaxConcurrency, DynamicExpansionFlags, MemoryPoolTier, SparsityMask, SubAllocationMask, PipelineCoherencyTier, FeedbackLoopTier, SubGraphRecursionTier, MeshPipeliningTier, MultiQueueFusionTier, MicroscalingTier, SubBytePrecisionTier, SparseTensorBlockTier, Flags };
    }

    void DispatchGraphProgramRecord17(uint32_t NodeIndex, const void* pRecord, uint32_t RecordSizeInBytes, uint32_t ConcurrencyGroup, uint32_t QueueAffinityMask, uint32_t DynamicClusterExpansionTier, uint32_t TensorCoreMask, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DispatchMask, uint32_t DispatchFlags) override {
        m_recordedProgramRecords17.push_back({ NodeIndex, pRecord, RecordSizeInBytes, ConcurrencyGroup, QueueAffinityMask, DynamicClusterExpansionTier, TensorCoreMask, SubAllocationMask, PipelineCoherencyTier, FeedbackLoopTier, SubGraphRecursionTier, MeshPipeliningTier, MultiQueueFusionTier, MicroscalingTier, SubBytePrecisionTier, SparseTensorBlockTier, DispatchMask, DispatchFlags });
    }

    const BackingMemory17Record& GetWorkGraphBackingMemory17() const noexcept { return m_backingMemory17; }
    size_t GetRecordedProgramRecord17Count() const noexcept { return m_recordedProgramRecords17.size(); }
    const std::vector<ProgramRecord17Entry>& GetRecordedProgramRecords17() const noexcept { return m_recordedProgramRecords17; }

    // ID3D12GraphicsCommandList28
    void SetWorkGraphBackingMemory18(D3D12_GPU_VIRTUAL_ADDRESS RangeStart, uint64_t RangeSizeInBytes, uint64_t ScratchBufferSizeInBytes, uint32_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t SparsityMask, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t Flags) override {
        m_backingMemory18 = { RangeStart, RangeSizeInBytes, ScratchBufferSizeInBytes, MaxConcurrency, DynamicExpansionFlags, MemoryPoolTier, SparsityMask, SubAllocationMask, PipelineCoherencyTier, FeedbackLoopTier, SubGraphRecursionTier, MeshPipeliningTier, MultiQueueFusionTier, MicroscalingTier, SubBytePrecisionTier, SparseTensorBlockTier, DeterministicTensorReductionTier, Flags };
    }

    void DispatchGraphProgramRecord18(uint32_t NodeIndex, const void* pRecord, uint32_t RecordSizeInBytes, uint32_t ConcurrencyGroup, uint32_t QueueAffinityMask, uint32_t DynamicClusterExpansionTier, uint32_t TensorCoreMask, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t DispatchMask, uint32_t DispatchFlags) override {
        m_recordedProgramRecords18.push_back({ NodeIndex, pRecord, RecordSizeInBytes, ConcurrencyGroup, QueueAffinityMask, DynamicClusterExpansionTier, TensorCoreMask, SubAllocationMask, PipelineCoherencyTier, FeedbackLoopTier, SubGraphRecursionTier, MeshPipeliningTier, MultiQueueFusionTier, MicroscalingTier, SubBytePrecisionTier, SparseTensorBlockTier, DeterministicTensorReductionTier, DispatchMask, DispatchFlags });
    }

    const BackingMemory18Record& GetWorkGraphBackingMemory18() const noexcept { return m_backingMemory18; }
    size_t GetRecordedProgramRecord18Count() const noexcept { return m_recordedProgramRecords18.size(); }
    const std::vector<ProgramRecord18Entry>& GetRecordedProgramRecords18() const noexcept { return m_recordedProgramRecords18; }

    // ID3D12GraphicsCommandList29
    void SetWorkGraphBackingMemory19(D3D12_GPU_VIRTUAL_ADDRESS RangeStart, uint64_t RangeSizeInBytes, uint64_t ScratchBufferSizeInBytes, uint32_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t SparsityMask, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t Flags) override {
        m_backingMemory19 = { RangeStart, RangeSizeInBytes, ScratchBufferSizeInBytes, MaxConcurrency, DynamicExpansionFlags, MemoryPoolTier, SparsityMask, SubAllocationMask, PipelineCoherencyTier, FeedbackLoopTier, SubGraphRecursionTier, MeshPipeliningTier, MultiQueueFusionTier, MicroscalingTier, SubBytePrecisionTier, SparseTensorBlockTier, DeterministicTensorReductionTier, HyperQuantizationTier, Flags };
    }

    void DispatchGraphProgramRecord19(uint32_t NodeIndex, const void* pRecord, uint32_t RecordSizeInBytes, uint32_t ConcurrencyGroup, uint32_t QueueAffinityMask, uint32_t DynamicClusterExpansionTier, uint32_t TensorCoreMask, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t DispatchMask, uint32_t DispatchFlags) override {
        m_recordedProgramRecords19.push_back({ NodeIndex, pRecord, RecordSizeInBytes, ConcurrencyGroup, QueueAffinityMask, DynamicClusterExpansionTier, TensorCoreMask, SubAllocationMask, PipelineCoherencyTier, FeedbackLoopTier, SubGraphRecursionTier, MeshPipeliningTier, MultiQueueFusionTier, MicroscalingTier, SubBytePrecisionTier, SparseTensorBlockTier, DeterministicTensorReductionTier, HyperQuantizationTier, DispatchMask, DispatchFlags });
    }

    const BackingMemory19Record& GetWorkGraphBackingMemory19() const noexcept { return m_backingMemory19; }
    size_t GetRecordedProgramRecord19Count() const noexcept { return m_recordedProgramRecords19.size(); }
    const std::vector<ProgramRecord19Entry>& GetRecordedProgramRecords19() const noexcept { return m_recordedProgramRecords19; }

    // ID3D12GraphicsCommandList30
    void SetWorkGraphBackingMemory20(D3D12_GPU_VIRTUAL_ADDRESS RangeStart, uint64_t RangeSizeInBytes, uint64_t ScratchBufferSizeInBytes, uint32_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t SparsityMask, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t Flags) override {
        m_backingMemory20 = { RangeStart, RangeSizeInBytes, ScratchBufferSizeInBytes, MaxConcurrency, DynamicExpansionFlags, MemoryPoolTier, SparsityMask, SubAllocationMask, PipelineCoherencyTier, FeedbackLoopTier, SubGraphRecursionTier, MeshPipeliningTier, MultiQueueFusionTier, MicroscalingTier, SubBytePrecisionTier, SparseTensorBlockTier, DeterministicTensorReductionTier, HyperQuantizationTier, SparseClusterTier, Flags };
    }

    void DispatchGraphProgramRecord20(uint32_t NodeIndex, const void* pRecord, uint32_t RecordSizeInBytes, uint32_t ConcurrencyGroup, uint32_t QueueAffinityMask, uint32_t DynamicClusterExpansionTier, uint32_t TensorCoreMask, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t DispatchMask, uint32_t DispatchFlags) override {
        m_recordedProgramRecords20.push_back({ NodeIndex, pRecord, RecordSizeInBytes, ConcurrencyGroup, QueueAffinityMask, DynamicClusterExpansionTier, TensorCoreMask, SubAllocationMask, PipelineCoherencyTier, FeedbackLoopTier, SubGraphRecursionTier, MeshPipeliningTier, MultiQueueFusionTier, MicroscalingTier, SubBytePrecisionTier, SparseTensorBlockTier, DeterministicTensorReductionTier, HyperQuantizationTier, SparseClusterTier, DispatchMask, DispatchFlags });
    }

    const BackingMemory20Record& GetWorkGraphBackingMemory20() const noexcept { return m_backingMemory20; }
    size_t GetRecordedProgramRecord20Count() const noexcept { return m_recordedProgramRecords20.size(); }
    const std::vector<ProgramRecord20Entry>& GetRecordedProgramRecords20() const noexcept { return m_recordedProgramRecords20; }

    // ID3D12GraphicsCommandList31
    void SetWorkGraphBackingMemory21(D3D12_GPU_VIRTUAL_ADDRESS RangeStart, uint64_t RangeSizeInBytes, uint64_t ScratchBufferSizeInBytes, uint32_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t SparsityMask, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t Flags) override {
        m_backingMemory21 = { RangeStart, RangeSizeInBytes, ScratchBufferSizeInBytes, MaxConcurrency, DynamicExpansionFlags, MemoryPoolTier, SparsityMask, SubAllocationMask, PipelineCoherencyTier, FeedbackLoopTier, SubGraphRecursionTier, MeshPipeliningTier, MultiQueueFusionTier, MicroscalingTier, SubBytePrecisionTier, SparseTensorBlockTier, DeterministicTensorReductionTier, HyperQuantizationTier, SparseClusterTier, MultiQueueSyncTier, Flags };
    }

    void DispatchGraphProgramRecord21(uint32_t NodeIndex, const void* pRecord, uint32_t RecordSizeInBytes, uint32_t ConcurrencyGroup, uint32_t QueueAffinityMask, uint32_t DynamicClusterExpansionTier, uint32_t TensorCoreMask, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t DispatchMask, uint32_t DispatchFlags) override {
        m_recordedProgramRecords21.push_back({ NodeIndex, pRecord, RecordSizeInBytes, ConcurrencyGroup, QueueAffinityMask, DynamicClusterExpansionTier, TensorCoreMask, SubAllocationMask, PipelineCoherencyTier, FeedbackLoopTier, SubGraphRecursionTier, MeshPipeliningTier, MultiQueueFusionTier, MicroscalingTier, SubBytePrecisionTier, SparseTensorBlockTier, DeterministicTensorReductionTier, HyperQuantizationTier, SparseClusterTier, MultiQueueSyncTier, DispatchMask, DispatchFlags });
    }

    const BackingMemory21Record& GetWorkGraphBackingMemory21() const noexcept { return m_backingMemory21; }
    size_t GetRecordedProgramRecord21Count() const noexcept { return m_recordedProgramRecords21.size(); }
    const std::vector<ProgramRecord21Entry>& GetRecordedProgramRecords21() const noexcept { return m_recordedProgramRecords21; }

    // ID3D12GraphicsCommandList32
    void SetWorkGraphBackingMemory22(D3D12_GPU_VIRTUAL_ADDRESS RangeStart, uint64_t RangeSizeInBytes, uint64_t ScratchBufferSizeInBytes, uint32_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t SparsityMask, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t Flags) override {
        m_backingMemory22 = { RangeStart, RangeSizeInBytes, ScratchBufferSizeInBytes, MaxConcurrency, DynamicExpansionFlags, MemoryPoolTier, SparsityMask, SubAllocationMask, PipelineCoherencyTier, FeedbackLoopTier, SubGraphRecursionTier, MeshPipeliningTier, MultiQueueFusionTier, MicroscalingTier, SubBytePrecisionTier, SparseTensorBlockTier, DeterministicTensorReductionTier, HyperQuantizationTier, SparseClusterTier, MultiQueueSyncTier, AsyncKernelDispatchTier, Flags };
    }

    void DispatchGraphProgramRecord22(uint32_t NodeIndex, const void* pRecord, uint32_t RecordSizeInBytes, uint32_t ConcurrencyGroup, uint32_t QueueAffinityMask, uint32_t DynamicClusterExpansionTier, uint32_t TensorCoreMask, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t DispatchMask, uint32_t DispatchFlags) override {
        m_recordedProgramRecords22.push_back({ NodeIndex, pRecord, RecordSizeInBytes, ConcurrencyGroup, QueueAffinityMask, DynamicClusterExpansionTier, TensorCoreMask, SubAllocationMask, PipelineCoherencyTier, FeedbackLoopTier, SubGraphRecursionTier, MeshPipeliningTier, MultiQueueFusionTier, MicroscalingTier, SubBytePrecisionTier, SparseTensorBlockTier, DeterministicTensorReductionTier, HyperQuantizationTier, SparseClusterTier, MultiQueueSyncTier, AsyncKernelDispatchTier, DispatchMask, DispatchFlags });
    }

    const BackingMemory22Record& GetWorkGraphBackingMemory22() const noexcept { return m_backingMemory22; }
    size_t GetRecordedProgramRecord22Count() const noexcept { return m_recordedProgramRecords22.size(); }
    const std::vector<ProgramRecord22Entry>& GetRecordedProgramRecords22() const noexcept { return m_recordedProgramRecords22; }

    // ID3D12GraphicsCommandList33
    void SetWorkGraphBackingMemory23(D3D12_GPU_VIRTUAL_ADDRESS RangeStart, uint64_t RangeSizeInBytes, uint64_t ScratchBufferSizeInBytes, uint32_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t SparsityMask, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t NeuralExecutionEngineTier, uint32_t Flags) override {
        m_backingMemory23 = { RangeStart, RangeSizeInBytes, ScratchBufferSizeInBytes, MaxConcurrency, DynamicExpansionFlags, MemoryPoolTier, SparsityMask, SubAllocationMask, PipelineCoherencyTier, FeedbackLoopTier, SubGraphRecursionTier, MeshPipeliningTier, MultiQueueFusionTier, MicroscalingTier, SubBytePrecisionTier, SparseTensorBlockTier, DeterministicTensorReductionTier, HyperQuantizationTier, SparseClusterTier, MultiQueueSyncTier, AsyncKernelDispatchTier, NeuralExecutionEngineTier, Flags };
    }

    void DispatchGraphProgramRecord23(uint32_t NodeIndex, const void* pRecord, uint32_t RecordSizeInBytes, uint32_t ConcurrencyGroup, uint32_t QueueAffinityMask, uint32_t DynamicClusterExpansionTier, uint32_t TensorCoreMask, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t NeuralExecutionEngineTier, uint32_t DispatchMask, uint32_t DispatchFlags) override {
        m_recordedProgramRecords23.push_back({ NodeIndex, pRecord, RecordSizeInBytes, ConcurrencyGroup, QueueAffinityMask, DynamicClusterExpansionTier, TensorCoreMask, SubAllocationMask, PipelineCoherencyTier, FeedbackLoopTier, SubGraphRecursionTier, MeshPipeliningTier, MultiQueueFusionTier, MicroscalingTier, SubBytePrecisionTier, SparseTensorBlockTier, DeterministicTensorReductionTier, HyperQuantizationTier, SparseClusterTier, MultiQueueSyncTier, AsyncKernelDispatchTier, NeuralExecutionEngineTier, DispatchMask, DispatchFlags });
    }

    const BackingMemory23Record& GetWorkGraphBackingMemory23() const noexcept { return m_backingMemory23; }
    size_t GetRecordedProgramRecord23Count() const noexcept { return m_recordedProgramRecords23.size(); }
    const std::vector<ProgramRecord23Entry>& GetRecordedProgramRecords23() const noexcept { return m_recordedProgramRecords23; }

    // ID3D12GraphicsCommandList34
    void SetWorkGraphBackingMemory24(D3D12_GPU_VIRTUAL_ADDRESS RangeStart, uint64_t RangeSizeInBytes, uint64_t ScratchBufferSizeInBytes, uint32_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t SparsityMask, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t NeuralExecutionEngineTier, uint32_t AdaptiveTensorCoreTier, uint32_t Flags) override {
        m_backingMemory24 = { RangeStart, RangeSizeInBytes, ScratchBufferSizeInBytes, MaxConcurrency, DynamicExpansionFlags, MemoryPoolTier, SparsityMask, SubAllocationMask, PipelineCoherencyTier, FeedbackLoopTier, SubGraphRecursionTier, MeshPipeliningTier, MultiQueueFusionTier, MicroscalingTier, SubBytePrecisionTier, SparseTensorBlockTier, DeterministicTensorReductionTier, HyperQuantizationTier, SparseClusterTier, MultiQueueSyncTier, AsyncKernelDispatchTier, NeuralExecutionEngineTier, AdaptiveTensorCoreTier, Flags };
    }

    void DispatchGraphProgramRecord24(uint32_t NodeIndex, const void* pRecord, uint32_t RecordSizeInBytes, uint32_t ConcurrencyGroup, uint32_t QueueAffinityMask, uint32_t DynamicClusterExpansionTier, uint32_t TensorCoreMask, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t NeuralExecutionEngineTier, uint32_t AdaptiveTensorCoreTier, uint32_t DispatchMask, uint32_t DispatchFlags) override {
        m_recordedProgramRecords24.push_back({ NodeIndex, pRecord, RecordSizeInBytes, ConcurrencyGroup, QueueAffinityMask, DynamicClusterExpansionTier, TensorCoreMask, SubAllocationMask, PipelineCoherencyTier, FeedbackLoopTier, SubGraphRecursionTier, MeshPipeliningTier, MultiQueueFusionTier, MicroscalingTier, SubBytePrecisionTier, SparseTensorBlockTier, DeterministicTensorReductionTier, HyperQuantizationTier, SparseClusterTier, MultiQueueSyncTier, AsyncKernelDispatchTier, NeuralExecutionEngineTier, AdaptiveTensorCoreTier, DispatchMask, DispatchFlags });
    }

    const BackingMemory24Record& GetWorkGraphBackingMemory24() const noexcept { return m_backingMemory24; }
    size_t GetRecordedProgramRecord24Count() const noexcept { return m_recordedProgramRecords24.size(); }
    const std::vector<ProgramRecord24Entry>& GetRecordedProgramRecords24() const noexcept { return m_recordedProgramRecords24; }

    // ID3D12GraphicsCommandList35
    void SetWorkGraphBackingMemory25(D3D12_GPU_VIRTUAL_ADDRESS RangeStart, uint64_t RangeSizeInBytes, uint64_t ScratchBufferSizeInBytes, uint32_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t SparsityMask, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t NeuralExecutionEngineTier, uint32_t AdaptiveTensorCoreTier, uint32_t SovereignSiliconTelemetryTier, uint32_t Flags) override {
        m_backingMemory25 = { RangeStart, RangeSizeInBytes, ScratchBufferSizeInBytes, MaxConcurrency, DynamicExpansionFlags, MemoryPoolTier, SparsityMask, SubAllocationMask, PipelineCoherencyTier, FeedbackLoopTier, SubGraphRecursionTier, MeshPipeliningTier, MultiQueueFusionTier, MicroscalingTier, SubBytePrecisionTier, SparseTensorBlockTier, DeterministicTensorReductionTier, HyperQuantizationTier, SparseClusterTier, MultiQueueSyncTier, AsyncKernelDispatchTier, NeuralExecutionEngineTier, AdaptiveTensorCoreTier, SovereignSiliconTelemetryTier, Flags };
    }

    void DispatchGraphProgramRecord25(uint32_t NodeIndex, const void* pRecord, uint32_t RecordSizeInBytes, uint32_t ConcurrencyGroup, uint32_t QueueAffinityMask, uint32_t DynamicClusterExpansionTier, uint32_t TensorCoreMask, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t NeuralExecutionEngineTier, uint32_t AdaptiveTensorCoreTier, uint32_t SovereignSiliconTelemetryTier, uint32_t DispatchMask, uint32_t DispatchFlags) override {
        m_recordedProgramRecords25.push_back({ NodeIndex, pRecord, RecordSizeInBytes, ConcurrencyGroup, QueueAffinityMask, DynamicClusterExpansionTier, TensorCoreMask, SubAllocationMask, PipelineCoherencyTier, FeedbackLoopTier, SubGraphRecursionTier, MeshPipeliningTier, MultiQueueFusionTier, MicroscalingTier, SubBytePrecisionTier, SparseTensorBlockTier, DeterministicTensorReductionTier, HyperQuantizationTier, SparseClusterTier, MultiQueueSyncTier, AsyncKernelDispatchTier, NeuralExecutionEngineTier, AdaptiveTensorCoreTier, SovereignSiliconTelemetryTier, DispatchMask, DispatchFlags });
    }

    const BackingMemory25Record& GetWorkGraphBackingMemory25() const noexcept { return m_backingMemory25; }
    size_t GetRecordedProgramRecord25Count() const noexcept { return m_recordedProgramRecords25.size(); }
    const std::vector<ProgramRecord25Entry>& GetRecordedProgramRecords25() const noexcept { return m_recordedProgramRecords25; }

    // ID3D12GraphicsCommandList36
    void SetWorkGraphBackingMemory26(D3D12_GPU_VIRTUAL_ADDRESS RangeStart, uint64_t RangeSizeInBytes, uint64_t ScratchBufferSizeInBytes, uint32_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t SparsityMask, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t NeuralExecutionEngineTier, uint32_t AdaptiveTensorCoreTier, uint32_t SovereignSiliconTelemetryTier, uint32_t QuantumEmulationTier, uint32_t Flags) override {
        m_backingMemory26 = { RangeStart, RangeSizeInBytes, ScratchBufferSizeInBytes, MaxConcurrency, DynamicExpansionFlags, MemoryPoolTier, SparsityMask, SubAllocationMask, PipelineCoherencyTier, FeedbackLoopTier, SubGraphRecursionTier, MeshPipeliningTier, MultiQueueFusionTier, MicroscalingTier, SubBytePrecisionTier, SparseTensorBlockTier, DeterministicTensorReductionTier, HyperQuantizationTier, SparseClusterTier, MultiQueueSyncTier, AsyncKernelDispatchTier, NeuralExecutionEngineTier, AdaptiveTensorCoreTier, SovereignSiliconTelemetryTier, QuantumEmulationTier, Flags };
    }

    void DispatchGraphProgramRecord26(uint32_t NodeIndex, const void* pRecord, uint32_t RecordSizeInBytes, uint32_t ConcurrencyGroup, uint32_t QueueAffinityMask, uint32_t DynamicClusterExpansionTier, uint32_t TensorCoreMask, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t NeuralExecutionEngineTier, uint32_t AdaptiveTensorCoreTier, uint32_t SovereignSiliconTelemetryTier, uint32_t QuantumEmulationTier, uint32_t DispatchMask, uint32_t DispatchFlags) override {
        m_recordedProgramRecords26.push_back({ NodeIndex, pRecord, RecordSizeInBytes, ConcurrencyGroup, QueueAffinityMask, DynamicClusterExpansionTier, TensorCoreMask, SubAllocationMask, PipelineCoherencyTier, FeedbackLoopTier, SubGraphRecursionTier, MeshPipeliningTier, MultiQueueFusionTier, MicroscalingTier, SubBytePrecisionTier, SparseTensorBlockTier, DeterministicTensorReductionTier, HyperQuantizationTier, SparseClusterTier, MultiQueueSyncTier, AsyncKernelDispatchTier, NeuralExecutionEngineTier, AdaptiveTensorCoreTier, SovereignSiliconTelemetryTier, QuantumEmulationTier, DispatchMask, DispatchFlags });
    }

    const BackingMemory26Record& GetWorkGraphBackingMemory26() const noexcept { return m_backingMemory26; }
    size_t GetRecordedProgramRecord26Count() const noexcept { return m_recordedProgramRecords26.size(); }
    const std::vector<ProgramRecord26Entry>& GetRecordedProgramRecords26() const noexcept { return m_recordedProgramRecords26; }

    // ID3D12GraphicsCommandList37
    void SetWorkGraphBackingMemory27(D3D12_GPU_VIRTUAL_ADDRESS RangeStart, uint64_t RangeSizeInBytes, uint64_t ScratchBufferSizeInBytes, uint32_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t SparsityMask, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t NeuralExecutionEngineTier, uint32_t AdaptiveTensorCoreTier, uint32_t SovereignSiliconTelemetryTier, uint32_t QuantumEmulationTier, uint32_t Flags) override {
        m_backingMemory27 = { RangeStart, RangeSizeInBytes, ScratchBufferSizeInBytes, MaxConcurrency, DynamicExpansionFlags, MemoryPoolTier, SparsityMask, SubAllocationMask, PipelineCoherencyTier, FeedbackLoopTier, SubGraphRecursionTier, MeshPipeliningTier, MultiQueueFusionTier, MicroscalingTier, SubBytePrecisionTier, SparseTensorBlockTier, DeterministicTensorReductionTier, HyperQuantizationTier, SparseClusterTier, MultiQueueSyncTier, AsyncKernelDispatchTier, NeuralExecutionEngineTier, AdaptiveTensorCoreTier, SovereignSiliconTelemetryTier, QuantumEmulationTier, Flags };
    }

    void DispatchGraphProgramRecord27(uint32_t NodeIndex, const void* pRecord, uint32_t RecordSizeInBytes, uint32_t ConcurrencyGroup, uint32_t QueueAffinityMask, uint32_t DynamicClusterExpansionTier, uint32_t TensorCoreMask, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t NeuralExecutionEngineTier, uint32_t AdaptiveTensorCoreTier, uint32_t SovereignSiliconTelemetryTier, uint32_t QuantumEmulationTier, uint32_t DispatchMask, uint32_t DispatchFlags) override {
        m_recordedProgramRecords27.push_back({ NodeIndex, pRecord, RecordSizeInBytes, ConcurrencyGroup, QueueAffinityMask, DynamicClusterExpansionTier, TensorCoreMask, SubAllocationMask, PipelineCoherencyTier, FeedbackLoopTier, SubGraphRecursionTier, MeshPipeliningTier, MultiQueueFusionTier, MicroscalingTier, SubBytePrecisionTier, SparseTensorBlockTier, DeterministicTensorReductionTier, HyperQuantizationTier, SparseClusterTier, MultiQueueSyncTier, AsyncKernelDispatchTier, NeuralExecutionEngineTier, AdaptiveTensorCoreTier, SovereignSiliconTelemetryTier, QuantumEmulationTier, DispatchMask, DispatchFlags });
    }

    const BackingMemory27Record& GetWorkGraphBackingMemory27() const noexcept { return m_backingMemory27; }
    size_t GetRecordedProgramRecord27Count() const noexcept { return m_recordedProgramRecords27.size(); }
    const std::vector<ProgramRecord27Entry>& GetRecordedProgramRecords27() const noexcept { return m_recordedProgramRecords27; }

    // ID3D12GraphicsCommandList38
    void SetWorkGraphBackingMemory28(D3D12_GPU_VIRTUAL_ADDRESS RangeStart, uint64_t RangeSizeInBytes, uint64_t ScratchBufferSizeInBytes, uint32_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t SparsityMask, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t NeuralExecutionEngineTier, uint32_t AdaptiveTensorCoreTier, uint32_t SovereignSiliconTelemetryTier, uint32_t QuantumEmulationTier, uint32_t Flags) override {
        m_backingMemory28 = { RangeStart, RangeSizeInBytes, ScratchBufferSizeInBytes, MaxConcurrency, DynamicExpansionFlags, MemoryPoolTier, SparsityMask, SubAllocationMask, PipelineCoherencyTier, FeedbackLoopTier, SubGraphRecursionTier, MeshPipeliningTier, MultiQueueFusionTier, MicroscalingTier, SubBytePrecisionTier, SparseTensorBlockTier, DeterministicTensorReductionTier, HyperQuantizationTier, SparseClusterTier, MultiQueueSyncTier, AsyncKernelDispatchTier, NeuralExecutionEngineTier, AdaptiveTensorCoreTier, SovereignSiliconTelemetryTier, QuantumEmulationTier, Flags };
    }

    void DispatchGraphProgramRecord28(uint32_t NodeIndex, const void* pRecord, uint32_t RecordSizeInBytes, uint32_t ConcurrencyGroup, uint32_t QueueAffinityMask, uint32_t DynamicClusterExpansionTier, uint32_t TensorCoreMask, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t NeuralExecutionEngineTier, uint32_t AdaptiveTensorCoreTier, uint32_t SovereignSiliconTelemetryTier, uint32_t QuantumEmulationTier, uint32_t DispatchMask, uint32_t DispatchFlags) override {
        m_recordedProgramRecords28.push_back({ NodeIndex, pRecord, RecordSizeInBytes, ConcurrencyGroup, QueueAffinityMask, DynamicClusterExpansionTier, TensorCoreMask, SubAllocationMask, PipelineCoherencyTier, FeedbackLoopTier, SubGraphRecursionTier, MeshPipeliningTier, MultiQueueFusionTier, MicroscalingTier, SubBytePrecisionTier, SparseTensorBlockTier, DeterministicTensorReductionTier, HyperQuantizationTier, SparseClusterTier, MultiQueueSyncTier, AsyncKernelDispatchTier, NeuralExecutionEngineTier, AdaptiveTensorCoreTier, SovereignSiliconTelemetryTier, QuantumEmulationTier, DispatchMask, DispatchFlags });
    }

    const BackingMemory28Record& GetWorkGraphBackingMemory28() const noexcept { return m_backingMemory28; }
    size_t GetRecordedProgramRecord28Count() const noexcept { return m_recordedProgramRecords28.size(); }
    const std::vector<ProgramRecord28Entry>& GetRecordedProgramRecords28() const noexcept { return m_recordedProgramRecords28; }

    // ID3D12GraphicsCommandList39
    void SetWorkGraphBackingMemory29(D3D12_GPU_VIRTUAL_ADDRESS RangeStart, uint64_t RangeSizeInBytes, uint64_t ScratchBufferSizeInBytes, uint32_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t SparsityMask, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t NeuralExecutionEngineTier, uint32_t AdaptiveTensorCoreTier, uint32_t SovereignSiliconTelemetryTier, uint32_t QuantumEmulationTier, uint32_t Flags) override {
        m_backingMemory29 = { RangeStart, RangeSizeInBytes, ScratchBufferSizeInBytes, MaxConcurrency, DynamicExpansionFlags, MemoryPoolTier, SparsityMask, SubAllocationMask, PipelineCoherencyTier, FeedbackLoopTier, SubGraphRecursionTier, MeshPipeliningTier, MultiQueueFusionTier, MicroscalingTier, SubBytePrecisionTier, SparseTensorBlockTier, DeterministicTensorReductionTier, HyperQuantizationTier, SparseClusterTier, MultiQueueSyncTier, AsyncKernelDispatchTier, NeuralExecutionEngineTier, AdaptiveTensorCoreTier, SovereignSiliconTelemetryTier, QuantumEmulationTier, Flags };
    }

    void DispatchGraphProgramRecord29(uint32_t NodeIndex, const void* pRecord, uint32_t RecordSizeInBytes, uint32_t ConcurrencyGroup, uint32_t QueueAffinityMask, uint32_t DynamicClusterExpansionTier, uint32_t TensorCoreMask, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t NeuralExecutionEngineTier, uint32_t AdaptiveTensorCoreTier, uint32_t SovereignSiliconTelemetryTier, uint32_t QuantumEmulationTier, uint32_t DispatchMask, uint32_t DispatchFlags) override {
        m_recordedProgramRecords29.push_back({ NodeIndex, pRecord, RecordSizeInBytes, ConcurrencyGroup, QueueAffinityMask, DynamicClusterExpansionTier, TensorCoreMask, SubAllocationMask, PipelineCoherencyTier, FeedbackLoopTier, SubGraphRecursionTier, MeshPipeliningTier, MultiQueueFusionTier, MicroscalingTier, SubBytePrecisionTier, SparseTensorBlockTier, DeterministicTensorReductionTier, HyperQuantizationTier, SparseClusterTier, MultiQueueSyncTier, AsyncKernelDispatchTier, NeuralExecutionEngineTier, AdaptiveTensorCoreTier, SovereignSiliconTelemetryTier, QuantumEmulationTier, DispatchMask, DispatchFlags });
    }

    const BackingMemory29Record& GetWorkGraphBackingMemory29() const noexcept { return m_backingMemory29; }
    size_t GetRecordedProgramRecord29Count() const noexcept { return m_recordedProgramRecords29.size(); }
    const std::vector<ProgramRecord29Entry>& GetRecordedProgramRecords29() const noexcept { return m_recordedProgramRecords29; }

    // ID3D12GraphicsCommandList40
    void SetWorkGraphBackingMemory30(D3D12_GPU_VIRTUAL_ADDRESS RangeStart, uint64_t RangeSizeInBytes, uint64_t ScratchBufferSizeInBytes, uint64_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t SparsityMask, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t NeuralExecutionEngineTier, uint32_t AdaptiveTensorCoreTier, uint32_t SovereignSiliconTelemetryTier, uint32_t QuantumEmulationTier, uint32_t Flags) override {
        m_backingMemory30 = { RangeStart, RangeSizeInBytes, ScratchBufferSizeInBytes, MaxConcurrency, DynamicExpansionFlags, MemoryPoolTier, SparsityMask, SubAllocationMask, PipelineCoherencyTier, FeedbackLoopTier, SubGraphRecursionTier, MeshPipeliningTier, MultiQueueFusionTier, MicroscalingTier, SubBytePrecisionTier, SparseTensorBlockTier, DeterministicTensorReductionTier, HyperQuantizationTier, SparseClusterTier, MultiQueueSyncTier, AsyncKernelDispatchTier, NeuralExecutionEngineTier, AdaptiveTensorCoreTier, SovereignSiliconTelemetryTier, QuantumEmulationTier, Flags };
    }

    void DispatchGraphProgramRecord30(uint32_t NodeIndex, const void* pRecord, uint32_t RecordSizeInBytes, uint32_t ConcurrencyGroup, uint32_t QueueAffinityMask, uint32_t DynamicClusterExpansionTier, uint32_t TensorCoreMask, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t NeuralExecutionEngineTier, uint32_t AdaptiveTensorCoreTier, uint32_t SovereignSiliconTelemetryTier, uint32_t QuantumEmulationTier, uint32_t DispatchMask, uint32_t DispatchFlags) override {
        m_recordedProgramRecords30.push_back({ NodeIndex, pRecord, RecordSizeInBytes, ConcurrencyGroup, QueueAffinityMask, DynamicClusterExpansionTier, TensorCoreMask, SubAllocationMask, PipelineCoherencyTier, FeedbackLoopTier, SubGraphRecursionTier, MeshPipeliningTier, MultiQueueFusionTier, MicroscalingTier, SubBytePrecisionTier, SparseTensorBlockTier, DeterministicTensorReductionTier, HyperQuantizationTier, SparseClusterTier, MultiQueueSyncTier, AsyncKernelDispatchTier, NeuralExecutionEngineTier, AdaptiveTensorCoreTier, SovereignSiliconTelemetryTier, QuantumEmulationTier, DispatchMask, DispatchFlags });
    }

    const BackingMemory30Record& GetWorkGraphBackingMemory30() const noexcept { return m_backingMemory30; }
    size_t GetRecordedProgramRecord30Count() const noexcept { return m_recordedProgramRecords30.size(); }
    const std::vector<ProgramRecord30Entry>& GetRecordedProgramRecords30() const noexcept { return m_recordedProgramRecords30; }

    // ID3D12GraphicsCommandList41
    void SetWorkGraphBackingMemory31(D3D12_GPU_VIRTUAL_ADDRESS RangeStart, uint64_t RangeSizeInBytes, uint64_t ScratchBufferSizeInBytes, uint64_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t SparsityMask, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t NeuralExecutionEngineTier, uint32_t AdaptiveTensorCoreTier, uint32_t SovereignSiliconTelemetryTier, uint32_t QuantumEmulationTier, uint32_t Flags) override {
        m_backingMemory31 = { RangeStart, RangeSizeInBytes, ScratchBufferSizeInBytes, MaxConcurrency, DynamicExpansionFlags, MemoryPoolTier, SparsityMask, SubAllocationMask, PipelineCoherencyTier, FeedbackLoopTier, SubGraphRecursionTier, MeshPipeliningTier, MultiQueueFusionTier, MicroscalingTier, SubBytePrecisionTier, SparseTensorBlockTier, DeterministicTensorReductionTier, HyperQuantizationTier, SparseClusterTier, MultiQueueSyncTier, AsyncKernelDispatchTier, NeuralExecutionEngineTier, AdaptiveTensorCoreTier, SovereignSiliconTelemetryTier, QuantumEmulationTier, Flags };
    }

    void DispatchGraphProgramRecord31(uint32_t NodeIndex, const void* pRecord, uint32_t RecordSizeInBytes, uint32_t ConcurrencyGroup, uint32_t QueueAffinityMask, uint32_t DynamicClusterExpansionTier, uint32_t TensorCoreMask, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t NeuralExecutionEngineTier, uint32_t AdaptiveTensorCoreTier, uint32_t SovereignSiliconTelemetryTier, uint32_t QuantumEmulationTier, uint32_t DispatchMask, uint32_t DispatchFlags) override {
        m_recordedProgramRecords31.push_back({ NodeIndex, pRecord, RecordSizeInBytes, ConcurrencyGroup, QueueAffinityMask, DynamicClusterExpansionTier, TensorCoreMask, SubAllocationMask, PipelineCoherencyTier, FeedbackLoopTier, SubGraphRecursionTier, MeshPipeliningTier, MultiQueueFusionTier, MicroscalingTier, SubBytePrecisionTier, SparseTensorBlockTier, DeterministicTensorReductionTier, HyperQuantizationTier, SparseClusterTier, MultiQueueSyncTier, AsyncKernelDispatchTier, NeuralExecutionEngineTier, AdaptiveTensorCoreTier, SovereignSiliconTelemetryTier, QuantumEmulationTier, DispatchMask, DispatchFlags });
    }

    const BackingMemory31Record& GetWorkGraphBackingMemory31() const noexcept { return m_backingMemory31; }
    size_t GetRecordedProgramRecord31Count() const noexcept { return m_recordedProgramRecords31.size(); }
    const std::vector<ProgramRecord31Entry>& GetRecordedProgramRecords31() const noexcept { return m_recordedProgramRecords31; }

    // ID3D12GraphicsCommandList42
    void SetWorkGraphBackingMemory32(D3D12_GPU_VIRTUAL_ADDRESS RangeStart, uint64_t RangeSizeInBytes, uint64_t ScratchBufferSizeInBytes, uint64_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t SparsityMask, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t NeuralExecutionEngineTier, uint32_t AdaptiveTensorCoreTier, uint32_t SovereignSiliconTelemetryTier, uint32_t QuantumEmulationTier, uint32_t Flags) override {
        m_backingMemory32 = { RangeStart, RangeSizeInBytes, ScratchBufferSizeInBytes, MaxConcurrency, DynamicExpansionFlags, MemoryPoolTier, SparsityMask, SubAllocationMask, PipelineCoherencyTier, FeedbackLoopTier, SubGraphRecursionTier, MeshPipeliningTier, MultiQueueFusionTier, MicroscalingTier, SubBytePrecisionTier, SparseTensorBlockTier, DeterministicTensorReductionTier, HyperQuantizationTier, SparseClusterTier, MultiQueueSyncTier, AsyncKernelDispatchTier, NeuralExecutionEngineTier, AdaptiveTensorCoreTier, SovereignSiliconTelemetryTier, QuantumEmulationTier, Flags };
    }

    void DispatchGraphProgramRecord32(uint32_t NodeIndex, const void* pRecord, uint32_t RecordSizeInBytes, uint32_t ConcurrencyGroup, uint32_t QueueAffinityMask, uint32_t DynamicClusterExpansionTier, uint32_t TensorCoreMask, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t NeuralExecutionEngineTier, uint32_t AdaptiveTensorCoreTier, uint32_t SovereignSiliconTelemetryTier, uint32_t QuantumEmulationTier, uint32_t DispatchMask, uint32_t DispatchFlags) override {
        m_recordedProgramRecords32.push_back({ NodeIndex, pRecord, RecordSizeInBytes, ConcurrencyGroup, QueueAffinityMask, DynamicClusterExpansionTier, TensorCoreMask, SubAllocationMask, PipelineCoherencyTier, FeedbackLoopTier, SubGraphRecursionTier, MeshPipeliningTier, MultiQueueFusionTier, MicroscalingTier, SubBytePrecisionTier, SparseTensorBlockTier, DeterministicTensorReductionTier, HyperQuantizationTier, SparseClusterTier, MultiQueueSyncTier, AsyncKernelDispatchTier, NeuralExecutionEngineTier, AdaptiveTensorCoreTier, SovereignSiliconTelemetryTier, QuantumEmulationTier, DispatchMask, DispatchFlags });
    }

    const BackingMemory32Record& GetWorkGraphBackingMemory32() const noexcept { return m_backingMemory32; }
    size_t GetRecordedProgramRecord32Count() const noexcept { return m_recordedProgramRecords32.size(); }
    const std::vector<ProgramRecord32Entry>& GetRecordedProgramRecords32() const noexcept { return m_recordedProgramRecords32; }

    // ID3D12GraphicsCommandList43
    void SetWorkGraphBackingMemory33(D3D12_GPU_VIRTUAL_ADDRESS RangeStart, uint64_t RangeSizeInBytes, uint64_t ScratchBufferSizeInBytes, uint64_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t SparsityMask, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t NeuralExecutionEngineTier, uint32_t AdaptiveTensorCoreTier, uint32_t SovereignSiliconTelemetryTier, uint32_t QuantumEmulationTier, uint32_t Flags) override {
        m_backingMemory33 = { RangeStart, RangeSizeInBytes, ScratchBufferSizeInBytes, MaxConcurrency, DynamicExpansionFlags, MemoryPoolTier, SparsityMask, SubAllocationMask, PipelineCoherencyTier, FeedbackLoopTier, SubGraphRecursionTier, MeshPipeliningTier, MultiQueueFusionTier, MicroscalingTier, SubBytePrecisionTier, SparseTensorBlockTier, DeterministicTensorReductionTier, HyperQuantizationTier, SparseClusterTier, MultiQueueSyncTier, AsyncKernelDispatchTier, NeuralExecutionEngineTier, AdaptiveTensorCoreTier, SovereignSiliconTelemetryTier, QuantumEmulationTier, Flags };
    }

    void DispatchGraphProgramRecord33(uint32_t NodeIndex, const void* pRecord, uint32_t RecordSizeInBytes, uint32_t ConcurrencyGroup, uint32_t QueueAffinityMask, uint32_t DynamicClusterExpansionTier, uint32_t TensorCoreMask, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t NeuralExecutionEngineTier, uint32_t AdaptiveTensorCoreTier, uint32_t SovereignSiliconTelemetryTier, uint32_t QuantumEmulationTier, uint32_t DispatchMask, uint32_t DispatchFlags) override {
        m_recordedProgramRecords33.push_back({ NodeIndex, pRecord, RecordSizeInBytes, ConcurrencyGroup, QueueAffinityMask, DynamicClusterExpansionTier, TensorCoreMask, SubAllocationMask, PipelineCoherencyTier, FeedbackLoopTier, SubGraphRecursionTier, MeshPipeliningTier, MultiQueueFusionTier, MicroscalingTier, SubBytePrecisionTier, SparseTensorBlockTier, DeterministicTensorReductionTier, HyperQuantizationTier, SparseClusterTier, MultiQueueSyncTier, AsyncKernelDispatchTier, NeuralExecutionEngineTier, AdaptiveTensorCoreTier, SovereignSiliconTelemetryTier, QuantumEmulationTier, DispatchMask, DispatchFlags });
    }

    const BackingMemory33Record& GetWorkGraphBackingMemory33() const noexcept { return m_backingMemory33; }
    size_t GetRecordedProgramRecord33Count() const noexcept { return m_recordedProgramRecords33.size(); }
    const std::vector<ProgramRecord33Entry>& GetRecordedProgramRecords33() const noexcept { return m_recordedProgramRecords33; }

    // ID3D12GraphicsCommandList44
    void SetWorkGraphBackingMemory34(D3D12_GPU_VIRTUAL_ADDRESS RangeStart, uint64_t RangeSizeInBytes, uint64_t ScratchBufferSizeInBytes, uint64_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t SparsityMask, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t NeuralExecutionEngineTier, uint32_t AdaptiveTensorCoreTier, uint32_t SovereignSiliconTelemetryTier, uint32_t QuantumEmulationTier, uint32_t Flags) override {
        m_backingMemory34 = { RangeStart, RangeSizeInBytes, ScratchBufferSizeInBytes, MaxConcurrency, DynamicExpansionFlags, MemoryPoolTier, SparsityMask, SubAllocationMask, PipelineCoherencyTier, FeedbackLoopTier, SubGraphRecursionTier, MeshPipeliningTier, MultiQueueFusionTier, MicroscalingTier, SubBytePrecisionTier, SparseTensorBlockTier, DeterministicTensorReductionTier, HyperQuantizationTier, SparseClusterTier, MultiQueueSyncTier, AsyncKernelDispatchTier, NeuralExecutionEngineTier, AdaptiveTensorCoreTier, SovereignSiliconTelemetryTier, QuantumEmulationTier, Flags };
    }

    void DispatchGraphProgramRecord34(uint32_t NodeIndex, const void* pRecord, uint32_t RecordSizeInBytes, uint32_t ConcurrencyGroup, uint32_t QueueAffinityMask, uint32_t DynamicClusterExpansionTier, uint32_t TensorCoreMask, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t NeuralExecutionEngineTier, uint32_t AdaptiveTensorCoreTier, uint32_t SovereignSiliconTelemetryTier, uint32_t QuantumEmulationTier, uint32_t DispatchMask, uint32_t DispatchFlags) override {
        m_recordedProgramRecords34.push_back({ NodeIndex, pRecord, RecordSizeInBytes, ConcurrencyGroup, QueueAffinityMask, DynamicClusterExpansionTier, TensorCoreMask, SubAllocationMask, PipelineCoherencyTier, FeedbackLoopTier, SubGraphRecursionTier, MeshPipeliningTier, MultiQueueFusionTier, MicroscalingTier, SubBytePrecisionTier, SparseTensorBlockTier, DeterministicTensorReductionTier, HyperQuantizationTier, SparseClusterTier, MultiQueueSyncTier, AsyncKernelDispatchTier, NeuralExecutionEngineTier, AdaptiveTensorCoreTier, SovereignSiliconTelemetryTier, QuantumEmulationTier, DispatchMask, DispatchFlags });
    }

    const BackingMemory34Record& GetWorkGraphBackingMemory34() const noexcept { return m_backingMemory34; }
    size_t GetRecordedProgramRecord34Count() const noexcept { return m_recordedProgramRecords34.size(); }
    const std::vector<ProgramRecord34Entry>& GetRecordedProgramRecords34() const noexcept { return m_recordedProgramRecords34; }

    // ID3D12GraphicsCommandList45
    void SetWorkGraphBackingMemory35(D3D12_GPU_VIRTUAL_ADDRESS RangeStart, uint64_t RangeSizeInBytes, uint64_t ScratchBufferSizeInBytes, uint64_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t SparsityMask, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t NeuralExecutionEngineTier, uint32_t AdaptiveTensorCoreTier, uint32_t SovereignSiliconTelemetryTier, uint32_t QuantumEmulationTier, uint32_t Flags) override {
        m_backingMemory35 = { RangeStart, RangeSizeInBytes, ScratchBufferSizeInBytes, MaxConcurrency, DynamicExpansionFlags, MemoryPoolTier, SparsityMask, SubAllocationMask, PipelineCoherencyTier, FeedbackLoopTier, SubGraphRecursionTier, MeshPipeliningTier, MultiQueueFusionTier, MicroscalingTier, SubBytePrecisionTier, SparseTensorBlockTier, DeterministicTensorReductionTier, HyperQuantizationTier, SparseClusterTier, MultiQueueSyncTier, AsyncKernelDispatchTier, NeuralExecutionEngineTier, AdaptiveTensorCoreTier, SovereignSiliconTelemetryTier, QuantumEmulationTier, Flags };
    }

    void DispatchGraphProgramRecord35(uint32_t NodeIndex, const void* pRecord, uint32_t RecordSizeInBytes, uint32_t ConcurrencyGroup, uint32_t QueueAffinityMask, uint32_t DynamicClusterExpansionTier, uint32_t TensorCoreMask, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t NeuralExecutionEngineTier, uint32_t AdaptiveTensorCoreTier, uint32_t SovereignSiliconTelemetryTier, uint32_t QuantumEmulationTier, uint32_t DispatchMask, uint32_t DispatchFlags) override {
        m_recordedProgramRecords35.push_back({ NodeIndex, pRecord, RecordSizeInBytes, ConcurrencyGroup, QueueAffinityMask, DynamicClusterExpansionTier, TensorCoreMask, SubAllocationMask, PipelineCoherencyTier, FeedbackLoopTier, SubGraphRecursionTier, MeshPipeliningTier, MultiQueueFusionTier, MicroscalingTier, SubBytePrecisionTier, SparseTensorBlockTier, DeterministicTensorReductionTier, HyperQuantizationTier, SparseClusterTier, MultiQueueSyncTier, AsyncKernelDispatchTier, NeuralExecutionEngineTier, AdaptiveTensorCoreTier, SovereignSiliconTelemetryTier, QuantumEmulationTier, DispatchMask, DispatchFlags });
    }

    const BackingMemory35Record& GetWorkGraphBackingMemory35() const noexcept { return m_backingMemory35; }
    size_t GetRecordedProgramRecord35Count() const noexcept { return m_recordedProgramRecords35.size(); }
    const std::vector<ProgramRecord35Entry>& GetRecordedProgramRecords35() const noexcept { return m_recordedProgramRecords35; }

    // ID3D12GraphicsCommandList46
    void SetWorkGraphBackingMemory36(D3D12_GPU_VIRTUAL_ADDRESS RangeStart, uint64_t RangeSizeInBytes, uint64_t ScratchBufferSizeInBytes, uint64_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t SparsityMask, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t NeuralExecutionEngineTier, uint32_t AdaptiveTensorCoreTier, uint32_t SovereignSiliconTelemetryTier, uint32_t QuantumEmulationTier, uint32_t Flags) override {
        m_backingMemory36 = { RangeStart, RangeSizeInBytes, ScratchBufferSizeInBytes, MaxConcurrency, DynamicExpansionFlags, MemoryPoolTier, SparsityMask, SubAllocationMask, PipelineCoherencyTier, FeedbackLoopTier, SubGraphRecursionTier, MeshPipeliningTier, MultiQueueFusionTier, MicroscalingTier, SubBytePrecisionTier, SparseTensorBlockTier, DeterministicTensorReductionTier, HyperQuantizationTier, SparseClusterTier, MultiQueueSyncTier, AsyncKernelDispatchTier, NeuralExecutionEngineTier, AdaptiveTensorCoreTier, SovereignSiliconTelemetryTier, QuantumEmulationTier, Flags };
    }

    void DispatchGraphProgramRecord36(uint32_t NodeIndex, const void* pRecord, uint32_t RecordSizeInBytes, uint32_t ConcurrencyGroup, uint32_t QueueAffinityMask, uint32_t DynamicClusterExpansionTier, uint32_t TensorCoreMask, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t NeuralExecutionEngineTier, uint32_t AdaptiveTensorCoreTier, uint32_t SovereignSiliconTelemetryTier, uint32_t QuantumEmulationTier, uint32_t DispatchMask, uint32_t DispatchFlags) override {
        m_recordedProgramRecords36.push_back({ NodeIndex, pRecord, RecordSizeInBytes, ConcurrencyGroup, QueueAffinityMask, DynamicClusterExpansionTier, TensorCoreMask, SubAllocationMask, PipelineCoherencyTier, FeedbackLoopTier, SubGraphRecursionTier, MeshPipeliningTier, MultiQueueFusionTier, MicroscalingTier, SubBytePrecisionTier, SparseTensorBlockTier, DeterministicTensorReductionTier, HyperQuantizationTier, SparseClusterTier, MultiQueueSyncTier, AsyncKernelDispatchTier, NeuralExecutionEngineTier, AdaptiveTensorCoreTier, SovereignSiliconTelemetryTier, QuantumEmulationTier, DispatchMask, DispatchFlags });
    }

    const BackingMemory36Record& GetWorkGraphBackingMemory36() const noexcept { return m_backingMemory36; }
    size_t GetRecordedProgramRecord36Count() const noexcept { return m_recordedProgramRecords36.size(); }
    const std::vector<ProgramRecord36Entry>& GetRecordedProgramRecords36() const noexcept { return m_recordedProgramRecords36; }

    // ID3D12GraphicsCommandList47
    void SetWorkGraphBackingMemory37(D3D12_GPU_VIRTUAL_ADDRESS RangeStart, uint64_t RangeSizeInBytes, uint64_t ScratchBufferSizeInBytes, uint64_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t SparsityMask, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t NeuralExecutionEngineTier, uint32_t AdaptiveTensorCoreTier, uint32_t SovereignSiliconTelemetryTier, uint32_t QuantumEmulationTier, uint32_t Flags) override {
        m_backingMemory37 = { RangeStart, RangeSizeInBytes, ScratchBufferSizeInBytes, MaxConcurrency, DynamicExpansionFlags, MemoryPoolTier, SparsityMask, SubAllocationMask, PipelineCoherencyTier, FeedbackLoopTier, SubGraphRecursionTier, MeshPipeliningTier, MultiQueueFusionTier, MicroscalingTier, SubBytePrecisionTier, SparseTensorBlockTier, DeterministicTensorReductionTier, HyperQuantizationTier, SparseClusterTier, MultiQueueSyncTier, AsyncKernelDispatchTier, NeuralExecutionEngineTier, AdaptiveTensorCoreTier, SovereignSiliconTelemetryTier, QuantumEmulationTier, Flags };
    }

    void DispatchGraphProgramRecord37(uint32_t NodeIndex, const void* pRecord, uint32_t RecordSizeInBytes, uint32_t ConcurrencyGroup, uint32_t QueueAffinityMask, uint32_t DynamicClusterExpansionTier, uint32_t TensorCoreMask, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t NeuralExecutionEngineTier, uint32_t AdaptiveTensorCoreTier, uint32_t SovereignSiliconTelemetryTier, uint32_t QuantumEmulationTier, uint32_t DispatchMask, uint32_t DispatchFlags) override {
        m_recordedProgramRecords37.push_back({ NodeIndex, pRecord, RecordSizeInBytes, ConcurrencyGroup, QueueAffinityMask, DynamicClusterExpansionTier, TensorCoreMask, SubAllocationMask, PipelineCoherencyTier, FeedbackLoopTier, SubGraphRecursionTier, MeshPipeliningTier, MultiQueueFusionTier, MicroscalingTier, SubBytePrecisionTier, SparseTensorBlockTier, DeterministicTensorReductionTier, HyperQuantizationTier, SparseClusterTier, MultiQueueSyncTier, AsyncKernelDispatchTier, NeuralExecutionEngineTier, AdaptiveTensorCoreTier, SovereignSiliconTelemetryTier, QuantumEmulationTier, DispatchMask, DispatchFlags });
    }

    const BackingMemory37Record& GetWorkGraphBackingMemory37() const noexcept { return m_backingMemory37; }
    size_t GetRecordedProgramRecord37Count() const noexcept { return m_recordedProgramRecords37.size(); }
    const std::vector<ProgramRecord37Entry>& GetRecordedProgramRecords37() const noexcept { return m_recordedProgramRecords37; }

    // ID3D12GraphicsCommandList48
    void SetWorkGraphBackingMemory38(D3D12_GPU_VIRTUAL_ADDRESS RangeStart, uint64_t RangeSizeInBytes, uint64_t ScratchBufferSizeInBytes, uint64_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t SparsityMask, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t NeuralExecutionEngineTier, uint32_t AdaptiveTensorCoreTier, uint32_t SovereignSiliconTelemetryTier, uint32_t QuantumEmulationTier, uint32_t Flags) override {
        m_backingMemory38 = { RangeStart, RangeSizeInBytes, ScratchBufferSizeInBytes, MaxConcurrency, DynamicExpansionFlags, MemoryPoolTier, SparsityMask, SubAllocationMask, PipelineCoherencyTier, FeedbackLoopTier, SubGraphRecursionTier, MeshPipeliningTier, MultiQueueFusionTier, MicroscalingTier, SubBytePrecisionTier, SparseTensorBlockTier, DeterministicTensorReductionTier, HyperQuantizationTier, SparseClusterTier, MultiQueueSyncTier, AsyncKernelDispatchTier, NeuralExecutionEngineTier, AdaptiveTensorCoreTier, SovereignSiliconTelemetryTier, QuantumEmulationTier, Flags };
    }

    void DispatchGraphProgramRecord38(uint32_t NodeIndex, const void* pRecord, uint32_t RecordSizeInBytes, uint32_t ConcurrencyGroup, uint32_t QueueAffinityMask, uint32_t DynamicClusterExpansionTier, uint32_t TensorCoreMask, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t NeuralExecutionEngineTier, uint32_t AdaptiveTensorCoreTier, uint32_t SovereignSiliconTelemetryTier, uint32_t QuantumEmulationTier, uint32_t DispatchMask, uint32_t DispatchFlags) override {
        m_recordedProgramRecords38.push_back({ NodeIndex, pRecord, RecordSizeInBytes, ConcurrencyGroup, QueueAffinityMask, DynamicClusterExpansionTier, TensorCoreMask, SubAllocationMask, PipelineCoherencyTier, FeedbackLoopTier, SubGraphRecursionTier, MeshPipeliningTier, MultiQueueFusionTier, MicroscalingTier, SubBytePrecisionTier, SparseTensorBlockTier, DeterministicTensorReductionTier, HyperQuantizationTier, SparseClusterTier, MultiQueueSyncTier, AsyncKernelDispatchTier, NeuralExecutionEngineTier, AdaptiveTensorCoreTier, SovereignSiliconTelemetryTier, QuantumEmulationTier, DispatchMask, DispatchFlags });
    }

    const BackingMemory38Record& GetWorkGraphBackingMemory38() const noexcept { return m_backingMemory38; }
    size_t GetRecordedProgramRecord38Count() const noexcept { return m_recordedProgramRecords38.size(); }
    const std::vector<ProgramRecord38Entry>& GetRecordedProgramRecords38() const noexcept { return m_recordedProgramRecords38; }

    // ID3D12GraphicsCommandList49
    void SetWorkGraphBackingMemory39(D3D12_GPU_VIRTUAL_ADDRESS RangeStart, uint64_t RangeSizeInBytes, uint64_t ScratchBufferSizeInBytes, uint64_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t SparsityMask, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t NeuralExecutionEngineTier, uint32_t AdaptiveTensorCoreTier, uint32_t SovereignSiliconTelemetryTier, uint32_t QuantumEmulationTier, uint32_t Flags) override {
        m_backingMemory39 = { RangeStart, RangeSizeInBytes, ScratchBufferSizeInBytes, MaxConcurrency, DynamicExpansionFlags, MemoryPoolTier, SparsityMask, SubAllocationMask, PipelineCoherencyTier, FeedbackLoopTier, SubGraphRecursionTier, MeshPipeliningTier, MultiQueueFusionTier, MicroscalingTier, SubBytePrecisionTier, SparseTensorBlockTier, DeterministicTensorReductionTier, HyperQuantizationTier, SparseClusterTier, MultiQueueSyncTier, AsyncKernelDispatchTier, NeuralExecutionEngineTier, AdaptiveTensorCoreTier, SovereignSiliconTelemetryTier, QuantumEmulationTier, Flags };
    }

    void DispatchGraphProgramRecord39(uint32_t NodeIndex, const void* pRecord, uint32_t RecordSizeInBytes, uint32_t ConcurrencyGroup, uint32_t QueueAffinityMask, uint32_t DynamicClusterExpansionTier, uint32_t TensorCoreMask, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t NeuralExecutionEngineTier, uint32_t AdaptiveTensorCoreTier, uint32_t SovereignSiliconTelemetryTier, uint32_t QuantumEmulationTier, uint32_t DispatchMask, uint32_t DispatchFlags) override {
        m_recordedProgramRecords39.push_back({ NodeIndex, pRecord, RecordSizeInBytes, ConcurrencyGroup, QueueAffinityMask, DynamicClusterExpansionTier, TensorCoreMask, SubAllocationMask, PipelineCoherencyTier, FeedbackLoopTier, SubGraphRecursionTier, MeshPipeliningTier, MultiQueueFusionTier, MicroscalingTier, SubBytePrecisionTier, SparseTensorBlockTier, DeterministicTensorReductionTier, HyperQuantizationTier, SparseClusterTier, MultiQueueSyncTier, AsyncKernelDispatchTier, NeuralExecutionEngineTier, AdaptiveTensorCoreTier, SovereignSiliconTelemetryTier, QuantumEmulationTier, DispatchMask, DispatchFlags });
    }

    const BackingMemory39Record& GetWorkGraphBackingMemory39() const noexcept { return m_backingMemory39; }
    size_t GetRecordedProgramRecord39Count() const noexcept { return m_recordedProgramRecords39.size(); }
    const std::vector<ProgramRecord39Entry>& GetRecordedProgramRecords39() const noexcept { return m_recordedProgramRecords39; }

    // ID3D12GraphicsCommandList50
    void SetWorkGraphBackingMemory40(D3D12_GPU_VIRTUAL_ADDRESS RangeStart, uint64_t RangeSizeInBytes, uint64_t ScratchBufferSizeInBytes, uint64_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t SparsityMask, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t NeuralExecutionEngineTier, uint32_t AdaptiveTensorCoreTier, uint32_t SovereignSiliconTelemetryTier, uint32_t QuantumEmulationTier, uint32_t Flags) override {
        m_backingMemory40 = { RangeStart, RangeSizeInBytes, ScratchBufferSizeInBytes, MaxConcurrency, DynamicExpansionFlags, MemoryPoolTier, SparsityMask, SubAllocationMask, PipelineCoherencyTier, FeedbackLoopTier, SubGraphRecursionTier, MeshPipeliningTier, MultiQueueFusionTier, MicroscalingTier, SubBytePrecisionTier, SparseTensorBlockTier, DeterministicTensorReductionTier, HyperQuantizationTier, SparseClusterTier, MultiQueueSyncTier, AsyncKernelDispatchTier, NeuralExecutionEngineTier, AdaptiveTensorCoreTier, SovereignSiliconTelemetryTier, QuantumEmulationTier, Flags };
    }

    void DispatchGraphProgramRecord40(uint32_t NodeIndex, const void* pRecord, uint32_t RecordSizeInBytes, uint32_t ConcurrencyGroup, uint32_t QueueAffinityMask, uint32_t DynamicClusterExpansionTier, uint32_t TensorCoreMask, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t NeuralExecutionEngineTier, uint32_t AdaptiveTensorCoreTier, uint32_t SovereignSiliconTelemetryTier, uint32_t QuantumEmulationTier, uint32_t DispatchMask, uint32_t DispatchFlags) override {
        m_recordedProgramRecords40.push_back({ NodeIndex, pRecord, RecordSizeInBytes, ConcurrencyGroup, QueueAffinityMask, DynamicClusterExpansionTier, TensorCoreMask, SubAllocationMask, PipelineCoherencyTier, FeedbackLoopTier, SubGraphRecursionTier, MeshPipeliningTier, MultiQueueFusionTier, MicroscalingTier, SubBytePrecisionTier, SparseTensorBlockTier, DeterministicTensorReductionTier, HyperQuantizationTier, SparseClusterTier, MultiQueueSyncTier, AsyncKernelDispatchTier, NeuralExecutionEngineTier, AdaptiveTensorCoreTier, SovereignSiliconTelemetryTier, QuantumEmulationTier, DispatchMask, DispatchFlags });
    }

    const BackingMemory40Record& GetWorkGraphBackingMemory40() const noexcept { return m_backingMemory40; }
    size_t GetRecordedProgramRecord40Count() const noexcept { return m_recordedProgramRecords40.size(); }
    const std::vector<ProgramRecord40Entry>& GetRecordedProgramRecords40() const noexcept { return m_recordedProgramRecords40; }

    // ID3D12GraphicsCommandList51
    void SetWorkGraphBackingMemory41(D3D12_GPU_VIRTUAL_ADDRESS RangeStart, uint64_t RangeSizeInBytes, uint64_t ScratchBufferSizeInBytes, uint64_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t SparsityMask, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t NeuralExecutionEngineTier, uint32_t AdaptiveTensorCoreTier, uint32_t SovereignSiliconTelemetryTier, uint32_t QuantumEmulationTier, uint32_t Flags) override {
        m_backingMemory41 = { RangeStart, RangeSizeInBytes, ScratchBufferSizeInBytes, MaxConcurrency, DynamicExpansionFlags, MemoryPoolTier, SparsityMask, SubAllocationMask, PipelineCoherencyTier, FeedbackLoopTier, SubGraphRecursionTier, MeshPipeliningTier, MultiQueueFusionTier, MicroscalingTier, SubBytePrecisionTier, SparseTensorBlockTier, DeterministicTensorReductionTier, HyperQuantizationTier, SparseClusterTier, MultiQueueSyncTier, AsyncKernelDispatchTier, NeuralExecutionEngineTier, AdaptiveTensorCoreTier, SovereignSiliconTelemetryTier, QuantumEmulationTier, Flags };
    }

    void DispatchGraphProgramRecord41(uint32_t NodeIndex, const void* pRecord, uint32_t RecordSizeInBytes, uint32_t ConcurrencyGroup, uint32_t QueueAffinityMask, uint32_t DynamicClusterExpansionTier, uint32_t TensorCoreMask, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t NeuralExecutionEngineTier, uint32_t AdaptiveTensorCoreTier, uint32_t SovereignSiliconTelemetryTier, uint32_t QuantumEmulationTier, uint32_t DispatchMask, uint32_t DispatchFlags) override {
        m_recordedProgramRecords41.push_back({ NodeIndex, pRecord, RecordSizeInBytes, ConcurrencyGroup, QueueAffinityMask, DynamicClusterExpansionTier, TensorCoreMask, SubAllocationMask, PipelineCoherencyTier, FeedbackLoopTier, SubGraphRecursionTier, MeshPipeliningTier, MultiQueueFusionTier, MicroscalingTier, SubBytePrecisionTier, SparseTensorBlockTier, DeterministicTensorReductionTier, HyperQuantizationTier, SparseClusterTier, MultiQueueSyncTier, AsyncKernelDispatchTier, NeuralExecutionEngineTier, AdaptiveTensorCoreTier, SovereignSiliconTelemetryTier, QuantumEmulationTier, DispatchMask, DispatchFlags });
    }

    const BackingMemory41Record& GetWorkGraphBackingMemory41() const noexcept { return m_backingMemory41; }
    size_t GetRecordedProgramRecord41Count() const noexcept { return m_recordedProgramRecords41.size(); }
    const std::vector<ProgramRecord41Entry>& GetRecordedProgramRecords41() const noexcept { return m_recordedProgramRecords41; }

    // ID3D12GraphicsCommandList52
    void SetWorkGraphBackingMemory42(D3D12_GPU_VIRTUAL_ADDRESS RangeStart, uint64_t RangeSizeInBytes, uint64_t ScratchBufferSizeInBytes, uint64_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t SparsityMask, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t NeuralExecutionEngineTier, uint32_t AdaptiveTensorCoreTier, uint32_t SovereignSiliconTelemetryTier, uint32_t QuantumEmulationTier, uint32_t Flags) override {
        m_backingMemory42 = { RangeStart, RangeSizeInBytes, ScratchBufferSizeInBytes, MaxConcurrency, DynamicExpansionFlags, MemoryPoolTier, SparsityMask, SubAllocationMask, PipelineCoherencyTier, FeedbackLoopTier, SubGraphRecursionTier, MeshPipeliningTier, MultiQueueFusionTier, MicroscalingTier, SubBytePrecisionTier, SparseTensorBlockTier, DeterministicTensorReductionTier, HyperQuantizationTier, SparseClusterTier, MultiQueueSyncTier, AsyncKernelDispatchTier, NeuralExecutionEngineTier, AdaptiveTensorCoreTier, SovereignSiliconTelemetryTier, QuantumEmulationTier, Flags };
    }

    void DispatchGraphProgramRecord42(uint32_t NodeIndex, const void* pRecord, uint32_t RecordSizeInBytes, uint32_t ConcurrencyGroup, uint32_t QueueAffinityMask, uint32_t DynamicClusterExpansionTier, uint32_t TensorCoreMask, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t NeuralExecutionEngineTier, uint32_t AdaptiveTensorCoreTier, uint32_t SovereignSiliconTelemetryTier, uint32_t QuantumEmulationTier, uint32_t DispatchMask, uint32_t DispatchFlags) override {
        m_recordedProgramRecords42.push_back({ NodeIndex, pRecord, RecordSizeInBytes, ConcurrencyGroup, QueueAffinityMask, DynamicClusterExpansionTier, TensorCoreMask, SubAllocationMask, PipelineCoherencyTier, FeedbackLoopTier, SubGraphRecursionTier, MeshPipeliningTier, MultiQueueFusionTier, MicroscalingTier, SubBytePrecisionTier, SparseTensorBlockTier, DeterministicTensorReductionTier, HyperQuantizationTier, SparseClusterTier, MultiQueueSyncTier, AsyncKernelDispatchTier, NeuralExecutionEngineTier, AdaptiveTensorCoreTier, SovereignSiliconTelemetryTier, QuantumEmulationTier, DispatchMask, DispatchFlags });
    }

    const BackingMemory42Record& GetWorkGraphBackingMemory42() const noexcept { return m_backingMemory42; }
    size_t GetRecordedProgramRecord42Count() const noexcept { return m_recordedProgramRecords42.size(); }
    const std::vector<ProgramRecord42Entry>& GetRecordedProgramRecords42() const noexcept { return m_recordedProgramRecords42; }

    // ID3D12GraphicsCommandList53
    void SetWorkGraphBackingMemory43(D3D12_GPU_VIRTUAL_ADDRESS RangeStart, uint64_t RangeSizeInBytes, uint64_t ScratchBufferSizeInBytes, uint64_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t SparsityMask, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t NeuralExecutionEngineTier, uint32_t AdaptiveTensorCoreTier, uint32_t SovereignSiliconTelemetryTier, uint32_t QuantumEmulationTier, uint32_t Flags) override {
        m_backingMemory43 = { RangeStart, RangeSizeInBytes, ScratchBufferSizeInBytes, MaxConcurrency, DynamicExpansionFlags, MemoryPoolTier, SparsityMask, SubAllocationMask, PipelineCoherencyTier, FeedbackLoopTier, SubGraphRecursionTier, MeshPipeliningTier, MultiQueueFusionTier, MicroscalingTier, SubBytePrecisionTier, SparseTensorBlockTier, DeterministicTensorReductionTier, HyperQuantizationTier, SparseClusterTier, MultiQueueSyncTier, AsyncKernelDispatchTier, NeuralExecutionEngineTier, AdaptiveTensorCoreTier, SovereignSiliconTelemetryTier, QuantumEmulationTier, Flags };
    }

    void DispatchGraphProgramRecord43(uint32_t NodeIndex, const void* pRecord, uint32_t RecordSizeInBytes, uint32_t ConcurrencyGroup, uint32_t QueueAffinityMask, uint32_t DynamicClusterExpansionTier, uint32_t TensorCoreMask, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t NeuralExecutionEngineTier, uint32_t AdaptiveTensorCoreTier, uint32_t SovereignSiliconTelemetryTier, uint32_t QuantumEmulationTier, uint32_t DispatchMask, uint32_t DispatchFlags) override {
        m_recordedProgramRecords43.push_back({ NodeIndex, pRecord, RecordSizeInBytes, ConcurrencyGroup, QueueAffinityMask, DynamicClusterExpansionTier, TensorCoreMask, SubAllocationMask, PipelineCoherencyTier, FeedbackLoopTier, SubGraphRecursionTier, MeshPipeliningTier, MultiQueueFusionTier, MicroscalingTier, SubBytePrecisionTier, SparseTensorBlockTier, DeterministicTensorReductionTier, HyperQuantizationTier, SparseClusterTier, MultiQueueSyncTier, AsyncKernelDispatchTier, NeuralExecutionEngineTier, AdaptiveTensorCoreTier, SovereignSiliconTelemetryTier, QuantumEmulationTier, DispatchMask, DispatchFlags });
    }

    const BackingMemory43Record& GetWorkGraphBackingMemory43() const noexcept { return m_backingMemory43; }
    size_t GetRecordedProgramRecord43Count() const noexcept { return m_recordedProgramRecords43.size(); }
    const std::vector<ProgramRecord43Entry>& GetRecordedProgramRecords43() const noexcept { return m_recordedProgramRecords43; }

    // ID3D12GraphicsCommandList54
    void SetWorkGraphBackingMemory44(D3D12_GPU_VIRTUAL_ADDRESS RangeStart, uint64_t RangeSizeInBytes, uint64_t ScratchBufferSizeInBytes, uint64_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t SparsityMask, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t NeuralExecutionEngineTier, uint32_t AdaptiveTensorCoreTier, uint32_t SovereignSiliconTelemetryTier, uint32_t QuantumEmulationTier, uint32_t Flags) override {
        m_backingMemory44 = { RangeStart, RangeSizeInBytes, ScratchBufferSizeInBytes, MaxConcurrency, DynamicExpansionFlags, MemoryPoolTier, SparsityMask, SubAllocationMask, PipelineCoherencyTier, FeedbackLoopTier, SubGraphRecursionTier, MeshPipeliningTier, MultiQueueFusionTier, MicroscalingTier, SubBytePrecisionTier, SparseTensorBlockTier, DeterministicTensorReductionTier, HyperQuantizationTier, SparseClusterTier, MultiQueueSyncTier, AsyncKernelDispatchTier, NeuralExecutionEngineTier, AdaptiveTensorCoreTier, SovereignSiliconTelemetryTier, QuantumEmulationTier, Flags };
    }

    void DispatchGraphProgramRecord44(uint32_t NodeIndex, const void* pRecord, uint32_t RecordSizeInBytes, uint32_t ConcurrencyGroup, uint32_t QueueAffinityMask, uint32_t DynamicClusterExpansionTier, uint32_t TensorCoreMask, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t NeuralExecutionEngineTier, uint32_t AdaptiveTensorCoreTier, uint32_t SovereignSiliconTelemetryTier, uint32_t QuantumEmulationTier, uint32_t DispatchMask, uint32_t DispatchFlags) override {
        m_recordedProgramRecords44.push_back({ NodeIndex, pRecord, RecordSizeInBytes, ConcurrencyGroup, QueueAffinityMask, DynamicClusterExpansionTier, TensorCoreMask, SubAllocationMask, PipelineCoherencyTier, FeedbackLoopTier, SubGraphRecursionTier, MeshPipeliningTier, MultiQueueFusionTier, MicroscalingTier, SubBytePrecisionTier, SparseTensorBlockTier, DeterministicTensorReductionTier, HyperQuantizationTier, SparseClusterTier, MultiQueueSyncTier, AsyncKernelDispatchTier, NeuralExecutionEngineTier, AdaptiveTensorCoreTier, SovereignSiliconTelemetryTier, QuantumEmulationTier, DispatchMask, DispatchFlags });
    }

    const BackingMemory44Record& GetWorkGraphBackingMemory44() const noexcept { return m_backingMemory44; }
    size_t GetRecordedProgramRecord44Count() const noexcept { return m_recordedProgramRecords44.size(); }
    const std::vector<ProgramRecord44Entry>& GetRecordedProgramRecords44() const noexcept { return m_recordedProgramRecords44; }

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
using Prism3D12GraphicsCommandList17Impl = Prism3D12GraphicsCommandList7Impl;
using Prism3D12GraphicsCommandList18Impl = Prism3D12GraphicsCommandList7Impl;
using Prism3D12GraphicsCommandList19Impl = Prism3D12GraphicsCommandList7Impl;
using Prism3D12GraphicsCommandList20Impl = Prism3D12GraphicsCommandList7Impl;
using Prism3D12GraphicsCommandList21Impl = Prism3D12GraphicsCommandList7Impl;
using Prism3D12GraphicsCommandList22Impl = Prism3D12GraphicsCommandList7Impl;
using Prism3D12GraphicsCommandList23Impl = Prism3D12GraphicsCommandList7Impl;
using Prism3D12GraphicsCommandList24Impl = Prism3D12GraphicsCommandList7Impl;
using Prism3D12GraphicsCommandList25Impl = Prism3D12GraphicsCommandList7Impl;
using Prism3D12GraphicsCommandList26Impl = Prism3D12GraphicsCommandList7Impl;
using Prism3D12GraphicsCommandList27Impl = Prism3D12GraphicsCommandList7Impl;
using Prism3D12GraphicsCommandList28Impl = Prism3D12GraphicsCommandList7Impl;
using Prism3D12GraphicsCommandList29Impl = Prism3D12GraphicsCommandList7Impl;
using Prism3D12GraphicsCommandList30Impl = Prism3D12GraphicsCommandList7Impl;
using Prism3D12GraphicsCommandList31Impl = Prism3D12GraphicsCommandList7Impl;
using Prism3D12GraphicsCommandList32Impl = Prism3D12GraphicsCommandList7Impl;
using Prism3D12GraphicsCommandList33Impl = Prism3D12GraphicsCommandList7Impl;
using Prism3D12GraphicsCommandList34Impl = Prism3D12GraphicsCommandList7Impl;
using Prism3D12GraphicsCommandList35Impl = Prism3D12GraphicsCommandList7Impl;
using Prism3D12GraphicsCommandList36Impl = Prism3D12GraphicsCommandList7Impl;
using Prism3D12GraphicsCommandList37Impl = Prism3D12GraphicsCommandList7Impl;
using Prism3D12GraphicsCommandList38Impl = Prism3D12GraphicsCommandList7Impl;
using Prism3D12GraphicsCommandList39Impl = Prism3D12GraphicsCommandList7Impl;
using Prism3D12GraphicsCommandList40Impl = Prism3D12GraphicsCommandList7Impl;
using Prism3D12GraphicsCommandList41Impl = Prism3D12GraphicsCommandList7Impl;
using Prism3D12GraphicsCommandList42Impl = Prism3D12GraphicsCommandList7Impl;
using Prism3D12GraphicsCommandList43Impl = Prism3D12GraphicsCommandList7Impl;
using Prism3D12GraphicsCommandList44Impl = Prism3D12GraphicsCommandList7Impl;
using Prism3D12GraphicsCommandList45Impl = Prism3D12GraphicsCommandList7Impl;
using Prism3D12GraphicsCommandList46Impl = Prism3D12GraphicsCommandList7Impl;
using Prism3D12GraphicsCommandList47Impl = Prism3D12GraphicsCommandList7Impl;
using Prism3D12GraphicsCommandList48Impl = Prism3D12GraphicsCommandList7Impl;
using Prism3D12GraphicsCommandList49Impl = Prism3D12GraphicsCommandList7Impl;
using Prism3D12GraphicsCommandList50Impl = Prism3D12GraphicsCommandList7Impl;
using Prism3D12GraphicsCommandList51Impl = Prism3D12GraphicsCommandList7Impl;
using Prism3D12GraphicsCommandList52Impl = Prism3D12GraphicsCommandList7Impl;
using Prism3D12GraphicsCommandList53Impl = Prism3D12GraphicsCommandList7Impl;
using Prism3D12GraphicsCommandList54Impl = Prism3D12GraphicsCommandList7Impl;

} // namespace prismx
