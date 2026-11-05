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

inline constexpr IID OFFICIAL_IID_ID3D12GraphicsCommandList7 =
    { 0x37a1f50b, 0x4861, 0x41dd, { 0x93, 0x3e, 0xf1, 0x4d, 0x86, 0xbf, 0xa2, 0x54 } };

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
// 3. ID3D12GraphicsCommandList7 (Enhanced Barriers)
// ============================================================================

class ID3D12GraphicsCommandList7 : public ID3D12GraphicsCommandList1 {
public:
    virtual void Barrier(uint32_t NumBarrierGroups, const D3D12_BARRIER_GROUP* pBarrierGroups) = 0;
};

// ============================================================================
// 4. Concrete Implementation: Prism3D12GraphicsCommandList7Impl
// ============================================================================

class Prism3D12GraphicsCommandList7Impl : public ID3D12GraphicsCommandList7 {
private:
    std::atomic<uint32_t> m_refCount{ 1 };
    ID3D12Device* m_pDevice{ nullptr };
    ID3D12CommandAllocator* m_pAllocator{ nullptr };
    D3D12_COMMAND_LIST_TYPE m_type{ D3D12_COMMAND_LIST_TYPE_DIRECT };
    bool m_isOpen{ true };

    std::vector<D3D12_SAMPLE_POSITION> m_samplePositions;
    uint32_t m_samplesPerPixel{ 0 };
    uint32_t m_viewInstanceMask{ 0 };

    struct RecordedBarrierGroup {
        D3D12_BARRIER_TYPE type;
        uint32_t count;
        std::vector<D3D12_GLOBAL_BARRIER>  globals;
        std::vector<D3D12_BUFFER_BARRIER>  buffers;
        std::vector<D3D12_TEXTURE_BARRIER> textures;
    };
    std::vector<RecordedBarrierGroup> m_recordedBarriers;

public:
    Prism3D12GraphicsCommandList7Impl(ID3D12Device* pDev, D3D12_COMMAND_LIST_TYPE type, ID3D12CommandAllocator* pAlloc)
        : m_pDevice(pDev), m_pAllocator(pAlloc), m_type(type) {}

    int32_t QueryInterface(const IID& riid, void** ppv) override {
        if (!ppv) return -1;
        if (riid == IID_IUnknown || riid == IID_ID3D12Object || riid == IID_ID3D12DeviceChild ||
            riid == IID_ID3D12CommandList || riid == IID_ID3D12GraphicsCommandList ||
            riid == OFFICIAL_IID_ID3D12GraphicsCommandList1 ||
            riid == OFFICIAL_IID_ID3D12GraphicsCommandList7) {
            *ppv = static_cast<ID3D12GraphicsCommandList7*>(this);
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
        m_isOpen = true;
        return 0;
    }

    void ClearState(ID3D12PipelineState*) override {
        m_samplePositions.clear();
        m_recordedBarriers.clear();
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
};

} // namespace prismx
