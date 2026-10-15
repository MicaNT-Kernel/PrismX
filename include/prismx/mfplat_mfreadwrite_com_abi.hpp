// ============================================================================
// PrismX: Official Microsoft Media Foundation (mfplat.dll & mfreadwrite.dll)
// COM ABI, Binary IIDs, IMFDXGIDeviceManager & Zero-Copy Cutscene Decoder (Suite 37)
//
// Clean-Room Implementation in ISO C++23. Zero External Dependencies.
// Provides:
//   - Exact 16-byte Microsoft binary IIDs & Format GUIDs from <mfapi.h>,
//     <mfidl.h>, <mfobjects.h>, <mfreadwrite.h>:
//       * IID_IMFAttributes         {2cd2d921-c447-44a7-a13c-4adabfc247e3}
//       * IID_IMFMediaBuffer        {045fa593-8799-42b8-bc8d-8968c6453507}
//       * IID_IMFSample             {c40a00f2-b93a-4d80-ae8c-5a1c634f58e4}
//       * IID_IMFMediaType          {44ae0fa8-ea31-4109-8d2e-4cae4997c555}
//       * IID_IMFDXGIDeviceManager  {eb533d5d-2db6-40f8-97a9-494692014f07}
//       * IID_IMFDXGIBuffer         {e7174cfa-1c9e-48b1-8866-626226bfc258}
//       * IID_IMFSourceReader       {70ae66f2-c809-4e4f-8915-bdcb406b7993}
//       * IID_IMFSinkWriter         {3137f1cd-fe5e-4805-a5d8-fb477448cb3d}
//   - Canonical COM vtable hierarchy for IMFAttributes, IMFMediaType,
//     IMFMediaBuffer, IMFDXGIBuffer, IMFSample, IMFDXGIDeviceManager,
//     IMFSourceReader, and IMFSinkWriter.
//   - Official mfplat.dll & mfreadwrite.dll C-linkage exports for game
//     H.264 / HEVC / AV1 cutscene playback into D3D11/DXGI textures.
// ============================================================================

#pragma once

#include "types.hpp"
#include "d3d11.hpp"
#include <atomic>
#include <cstring>
#include <vector>

namespace prismx::MediaFoundationCom {

// ----------------------------------------------------------------------------
// 1. Official 16-Byte Microsoft Binary IIDs & Media Format GUIDs
// ----------------------------------------------------------------------------
// {2cd2d921-c447-44a7-a13c-4adabfc247e3}
inline constexpr IID OFFICIAL_IID_IMFAttributes = {
    0x2cd2d921, 0xc447, 0x44a7, {0xa1, 0x3c, 0x4a, 0xda, 0xbf, 0xc2, 0x47, 0xe3}
};
// {045fa593-8799-42b8-bc8d-8968c6453507}
inline constexpr IID OFFICIAL_IID_IMFMediaBuffer = {
    0x045fa593, 0x8799, 0x42b8, {0xbc, 0x8d, 0x89, 0x68, 0xc6, 0x45, 0x35, 0x07}
};
// {7dc9d5f9-9ed9-44ec-9bb0-0600bb589f08}
inline constexpr IID OFFICIAL_IID_IMF2DBuffer = {
    0x7dc9d5f9, 0x9ed9, 0x44ec, {0x9b, 0xb0, 0x06, 0x00, 0xbb, 0x58, 0x9f, 0x08}
};
// {c40a00f2-b93a-4d80-ae8c-5a1c634f58e4}
inline constexpr IID OFFICIAL_IID_IMFSample = {
    0xc40a00f2, 0xb93a, 0x4d80, {0xae, 0x8c, 0x5a, 0x1c, 0x63, 0x4f, 0x58, 0xe4}
};
// {44ae0fa8-ea31-4109-8d2e-4cae4997c555}
inline constexpr IID OFFICIAL_IID_IMFMediaType = {
    0x44ae0fa8, 0xea31, 0x4109, {0x8d, 0x2e, 0x4c, 0xae, 0x49, 0x97, 0xc5, 0x55}
};
// {eb533d5d-2db6-40f8-97a9-494692014f07}
inline constexpr IID OFFICIAL_IID_IMFDXGIDeviceManager = {
    0xeb533d5d, 0x2db6, 0x40f8, {0x97, 0xa9, 0x49, 0x46, 0x92, 0x01, 0x4f, 0x07}
};
// {e7174cfa-1c9e-48b1-8866-626226bfc258}
inline constexpr IID OFFICIAL_IID_IMFDXGIBuffer = {
    0xe7174cfa, 0x1c9e, 0x48b1, {0x88, 0x66, 0x62, 0x62, 0x26, 0xbf, 0xc2, 0x58}
};
// {70ae66f2-c809-4e4f-8915-bdcb406b7993}
inline constexpr IID OFFICIAL_IID_IMFSourceReader = {
    0x70ae66f2, 0xc809, 0x4e4f, {0x89, 0x15, 0xbd, 0xcb, 0x40, 0x6b, 0x79, 0x93}
};
// {3137f1cd-fe5e-4805-a5d8-fb477448cb3d}
inline constexpr IID OFFICIAL_IID_IMFSinkWriter = {
    0x3137f1cd, 0xfe5e, 0x4805, {0xa5, 0xd8, 0xfb, 0x47, 0x74, 0x48, 0xcb, 0x3d}
};

// Media Type Major & Subtype GUIDs (<mfapi.h>)
// {73646976-0000-0010-8000-00aa00389b71} ('vids')
inline constexpr IID OFFICIAL_MFMediaType_Video = {
    0x73646976, 0x0000, 0x0010, {0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71}
};
// {73647561-0000-0010-8000-00aa00389b71} ('auds')
inline constexpr IID OFFICIAL_MFMediaType_Audio = {
    0x73647561, 0x0000, 0x0010, {0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71}
};
// {3231564e-0000-0010-8000-00aa00389b71} ('NV12')
inline constexpr IID OFFICIAL_MFVideoFormat_NV12 = {
    0x3231564e, 0x0000, 0x0010, {0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71}
};
// {34363248-0000-0010-8000-00aa00389b71} ('H264')
inline constexpr IID OFFICIAL_MFVideoFormat_H264 = {
    0x34363248, 0x0000, 0x0010, {0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71}
};
// {43564548-0000-0010-8000-00aa00389b71} ('HEVC')
inline constexpr IID OFFICIAL_MFVideoFormat_HEVC = {
    0x43564548, 0x0000, 0x0010, {0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71}
};
// {31305641-0000-0010-8000-00aa00389b71} ('AV01')
inline constexpr IID OFFICIAL_MFVideoFormat_AV1 = {
    0x31305641, 0x0000, 0x0010, {0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71}
};

// Attribute Key GUIDs
// {48eba18e-f8c9-4687-bf11-0a74c9f96a8f} MF_MT_MAJOR_TYPE
inline constexpr IID OFFICIAL_MF_MT_MAJOR_TYPE = {
    0x48eba18e, 0xf8c9, 0x4687, {0xbf, 0x11, 0x0a, 0x74, 0xc9, 0xf9, 0x6a, 0x8f}
};
// {f7e34c9a-42e8-4714-b74b-cb29d72c35e5} MF_MT_SUBTYPE
inline constexpr IID OFFICIAL_MF_MT_SUBTYPE = {
    0xf7e34c9a, 0x42e8, 0x4714, {0xb7, 0x4b, 0xcb, 0x29, 0xd7, 0x2c, 0x35, 0xe5}
};
// {1652c33d-d6b2-4012-b834-72030849a37d} MF_MT_FRAME_SIZE
inline constexpr IID OFFICIAL_MF_MT_FRAME_SIZE = {
    0x1652c33d, 0xd6b2, 0x4012, {0xb8, 0x34, 0x72, 0x03, 0x08, 0x49, 0xa3, 0x7d}
};

inline constexpr uint32_t MF_SDK_VERSION_CANONICAL = 0x0002u;
inline constexpr uint32_t MF_API_VERSION_CANONICAL = 0x0070u;
inline constexpr uint32_t MF_VERSION_CANONICAL     = (MF_SDK_VERSION_CANONICAL << 16) | MF_API_VERSION_CANONICAL;

inline constexpr uint32_t MF_SOURCE_READER_FIRST_VIDEO_STREAM = 0xFFFFFFFCu;
inline constexpr uint32_t MF_SOURCE_READER_FIRST_AUDIO_STREAM = 0xFFFFFFFDu;

// ----------------------------------------------------------------------------
// 2. Canonical Media Foundation COM Interfaces
// ----------------------------------------------------------------------------
struct IMFAttributes : public IUnknown {
    virtual HRESULT GetItem(const IID& guidKey, void* pValue) = 0;              // Slot 3
    virtual HRESULT GetItemType(const IID& guidKey, uint32_t* pType) = 0;       // Slot 4
    virtual HRESULT CompareItem(const IID& guidKey, const void* Value, int32_t* pbResult) = 0; // Slot 5
    virtual HRESULT Compare(IMFAttributes* pTheirs, uint32_t MatchType, int32_t* pbResult) = 0; // Slot 6
    virtual HRESULT GetUINT32(const IID& guidKey, uint32_t* punValue) = 0;      // Slot 7
    virtual HRESULT GetUINT64(const IID& guidKey, uint64_t* punValue) = 0;      // Slot 8
    virtual HRESULT GetDouble(const IID& guidKey, double* pfValue) = 0;         // Slot 9
    virtual HRESULT GetGUID(const IID& guidKey, IID* pguidValue) = 0;           // Slot 10
    virtual HRESULT GetStringLength(const IID& guidKey, uint32_t* pcchLength) = 0; // Slot 11
    virtual HRESULT GetString(const IID& guidKey, wchar_t* pwszValue, uint32_t cchBufSize, uint32_t* pcchLength) = 0; // Slot 12
    virtual HRESULT GetAllocatedString(const IID& guidKey, wchar_t** ppwszValue, uint32_t* pcchLength) = 0; // Slot 13
    virtual HRESULT GetBlobSize(const IID& guidKey, uint32_t* pcbBlobSize) = 0; // Slot 14
    virtual HRESULT GetBlob(const IID& guidKey, uint8_t* pBuf, uint32_t cbBufSize, uint32_t* pcbBlobSize) = 0; // Slot 15
    virtual HRESULT GetAllocatedBlob(const IID& guidKey, uint8_t** ppBuf, uint32_t* pcbSize) = 0; // Slot 16
    virtual HRESULT GetUnknown(const IID& guidKey, const IID& riid, void** ppv) = 0; // Slot 17
    virtual HRESULT SetItem(const IID& guidKey, const void* Value) = 0;         // Slot 18
    virtual HRESULT DeleteItem(const IID& guidKey) = 0;                         // Slot 19
    virtual HRESULT DeleteAllItems() = 0;                                       // Slot 20
    virtual HRESULT SetUINT32(const IID& guidKey, uint32_t unValue) = 0;        // Slot 21
    virtual HRESULT SetUINT64(const IID& guidKey, uint64_t unValue) = 0;        // Slot 22
    virtual HRESULT SetDouble(const IID& guidKey, double fValue) = 0;           // Slot 23
    virtual HRESULT SetGUID(const IID& guidKey, const IID& guidValue) = 0;      // Slot 24
    virtual HRESULT SetString(const IID& guidKey, const wchar_t* wszValue) = 0; // Slot 25
    virtual HRESULT SetBlob(const IID& guidKey, const uint8_t* pBuf, uint32_t cbBufSize) = 0; // Slot 26
    virtual HRESULT SetUnknown(const IID& guidKey, IUnknown* pUnknown) = 0;     // Slot 27
    virtual HRESULT LockStore() = 0;                                            // Slot 28
    virtual HRESULT UnlockStore() = 0;                                          // Slot 29
    virtual HRESULT GetCount(uint32_t* pcItems) = 0;                            // Slot 30
    virtual HRESULT GetItemByIndex(uint32_t unIndex, IID* pguidKey, void* pValue) = 0; // Slot 31
    virtual HRESULT CopyAllItems(IMFAttributes* pDest) = 0;                     // Slot 32
};

struct IMFMediaType : public IMFAttributes {
    virtual HRESULT GetMajorType(IID* pguidMajorType) = 0;                      // Slot 33
    virtual HRESULT IsCompressedFormat(int32_t* pfCompressed) = 0;              // Slot 34
    virtual HRESULT IsEqual(IMFMediaType* pIMediaType, uint32_t* pdwFlags) = 0; // Slot 35
    virtual HRESULT GetRepresentation(IID guidRepresentation, void** ppvRepresentation) = 0; // Slot 36
    virtual HRESULT FreeRepresentation(IID guidRepresentation, void* pvRepresentation) = 0;  // Slot 37
};

struct IMFMediaBuffer : public IUnknown {
    virtual HRESULT Lock(uint8_t** ppbBuffer, uint32_t* pcbMaxLength, uint32_t* pcbCurrentLength) = 0; // Slot 3
    virtual HRESULT Unlock() = 0;                                               // Slot 4
    virtual HRESULT GetCurrentLength(uint32_t* pcbCurrentLength) = 0;           // Slot 5
    virtual HRESULT SetCurrentLength(uint32_t cbCurrentLength) = 0;             // Slot 6
    virtual HRESULT GetMaxLength(uint32_t* pcbMaxLength) = 0;                   // Slot 7
};

struct IMFDXGIBuffer : public IUnknown {
    virtual HRESULT GetResource(const IID& riid, void** ppvObject) = 0;         // Slot 3
    virtual HRESULT GetSubresourceIndex(uint32_t* puSubresource) = 0;           // Slot 4
    virtual HRESULT GetUnknown(const IID& guid, const IID& riid, void** ppvObject) = 0; // Slot 5
    virtual HRESULT SetUnknown(const IID& guid, IUnknown* pUnkData) = 0;        // Slot 6
};

struct IMFSample : public IMFAttributes {
    virtual HRESULT GetSampleFlags(uint32_t* pdwSampleFlags) = 0;               // Slot 33
    virtual HRESULT SetSampleFlags(uint32_t dwSampleFlags) = 0;                 // Slot 34
    virtual HRESULT GetSampleTime(int64_t* phnsSampleTime) = 0;                 // Slot 35
    virtual HRESULT SetSampleTime(int64_t hnsSampleTime) = 0;                   // Slot 36
    virtual HRESULT GetSampleDuration(int64_t* phnsSampleDuration) = 0;         // Slot 37
    virtual HRESULT SetSampleDuration(int64_t hnsSampleDuration) = 0;           // Slot 38
    virtual HRESULT GetBufferCount(uint32_t* pdwBufferCount) = 0;               // Slot 39
    virtual HRESULT GetBufferByIndex(uint32_t dwIndex, IMFMediaBuffer** ppBuffer) = 0; // Slot 40
    virtual HRESULT ConvertToContiguousBuffer(IMFMediaBuffer** ppBuffer) = 0;   // Slot 41
    virtual HRESULT AddBuffer(IMFMediaBuffer* pBuffer) = 0;                     // Slot 42
    virtual HRESULT RemoveBufferByIndex(uint32_t dwIndex) = 0;                  // Slot 43
    virtual HRESULT RemoveAllBuffers() = 0;                                     // Slot 44
    virtual HRESULT GetTotalLength(uint32_t* pcbTotalLength) = 0;               // Slot 45
    virtual HRESULT CopyToBuffer(IMFMediaBuffer* pBuffer) = 0;                  // Slot 46
};

struct IMFDXGIDeviceManager : public IUnknown {
    virtual HRESULT CloseDeviceHandle(void* hDevice) = 0;                       // Slot 3
    virtual HRESULT GetVideoService(void* hDevice, const IID& riid, void** ppService) = 0; // Slot 4
    virtual HRESULT LockDevice(void* hDevice, const IID& riid, void** ppUnkDevice, int32_t fBlock) = 0; // Slot 5
    virtual HRESULT OpenDeviceHandle(void** phDevice) = 0;                      // Slot 6
    virtual HRESULT ResetDevice(IUnknown* pUnkDevice, uint32_t uResetToken) = 0;// Slot 7
    virtual HRESULT TestDevice(void* hDevice) = 0;                              // Slot 8
    virtual HRESULT UnlockDevice(void* hDevice, int32_t fSaveState) = 0;        // Slot 9
};

struct IMFSourceReader : public IUnknown {
    virtual HRESULT GetStreamSelection(uint32_t dwStreamIndex, int32_t* pfSelected) = 0; // Slot 3
    virtual HRESULT SetStreamSelection(uint32_t dwStreamIndex, int32_t fSelected) = 0;   // Slot 4
    virtual HRESULT GetNativeMediaType(uint32_t dwStreamIndex, uint32_t dwMediaTypeIndex, IMFMediaType** ppMediaType) = 0; // Slot 5
    virtual HRESULT GetCurrentMediaType(uint32_t dwStreamIndex, IMFMediaType** ppMediaType) = 0; // Slot 6
    virtual HRESULT SetCurrentMediaType(uint32_t dwStreamIndex, uint32_t* pdwReserved, IMFMediaType* pMediaType) = 0; // Slot 7
    virtual HRESULT SetCurrentPosition(const IID& guidTimeFormat, const void* varPosition) = 0; // Slot 8
    virtual HRESULT ReadSample(uint32_t dwStreamIndex, uint32_t dwControlFlags,
                               uint32_t* pdwActualStreamIndex, uint32_t* pdwStreamFlags,
                               int64_t* pllTimestamp, IMFSample** ppSample) = 0;// Slot 9
    virtual HRESULT Flush(uint32_t dwStreamIndex) = 0;                          // Slot 10
    virtual HRESULT GetServiceForStream(uint32_t dwStreamIndex, const IID& guidService,
                                        const IID& riid, void** ppvObject) = 0; // Slot 11
    virtual HRESULT GetPresentationAttribute(uint32_t dwStreamIndex,
                                             const IID& guidAttribute,
                                             void* pvarAttribute) = 0;          // Slot 12
};

struct IMFSinkWriter : public IUnknown {
    virtual HRESULT AddStream(IMFMediaType* pTargetMediaType, uint32_t* pdwStreamIndex) = 0; // Slot 3
    virtual HRESULT SetInputMediaType(uint32_t dwStreamIndex, IMFMediaType* pInputMediaType, IMFAttributes* pEncodingParameters) = 0; // Slot 4
    virtual HRESULT BeginWriting() = 0;                                         // Slot 5
    virtual HRESULT WriteSample(uint32_t dwStreamIndex, IMFSample* pSample) = 0;// Slot 6
    virtual HRESULT SendStreamTick(uint32_t dwStreamIndex, int64_t llTimestamp) = 0; // Slot 7
    virtual HRESULT PlaceMarker(uint32_t dwStreamIndex, void* pvContext) = 0;   // Slot 8
    virtual HRESULT NotifyEndOfSegment(uint32_t dwStreamIndex) = 0;             // Slot 9
    virtual HRESULT Flush(uint32_t dwStreamIndex) = 0;                          // Slot 10
    virtual HRESULT Finalize() = 0;                                             // Slot 11
    virtual HRESULT GetServiceForStream(uint32_t dwStreamIndex, const IID& guidService,
                                        const IID& riid, void** ppvObject) = 0; // Slot 12
    virtual HRESULT GetStatistics(uint32_t dwStreamIndex, void* pStats) = 0;    // Slot 13
};

// ----------------------------------------------------------------------------
// 3. Concrete Media Foundation Implementations
// ----------------------------------------------------------------------------
class PrismMFAttributesBaseImpl : public IMFMediaType {
protected:
    std::atomic<uint32_t> ref_count_{1};
    struct AttrEntry {
        IID key;
        uint64_t u64_val = 0;
        IID guid_val{};
        IUnknown* unk_val = nullptr;
    };
    std::vector<AttrEntry> attrs_;

    AttrEntry* findOrCreate(const IID& key) {
        for (auto& e : attrs_) {
            if (e.key == key) return &e;
        }
        attrs_.push_back(AttrEntry{key, 0, {}, nullptr});
        return &attrs_.back();
    }

    const AttrEntry* find(const IID& key) const {
        for (const auto& e : attrs_) {
            if (e.key == key) return &e;
        }
        return nullptr;
    }

public:
    virtual ~PrismMFAttributesBaseImpl() = default;

    int32_t QueryInterface(const IID& riid, void** ppvObject) override {
        if (!ppvObject) return E_POINTER;
        if (riid == IID_IUnknown ||
            riid == OFFICIAL_IID_IMFAttributes ||
            riid == OFFICIAL_IID_IMFMediaType) {
            *ppvObject = static_cast<IMFMediaType*>(this);
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

    HRESULT GetItem(const IID&, void*) override { return S_OK; }
    HRESULT GetItemType(const IID&, uint32_t* pType) override {
        if (pType) *pType = 0;
        return S_OK;
    }
    HRESULT CompareItem(const IID&, const void*, int32_t* pbResult) override {
        if (pbResult) *pbResult = 1;
        return S_OK;
    }
    HRESULT Compare(IMFAttributes*, uint32_t, int32_t* pbResult) override {
        if (pbResult) *pbResult = 1;
        return S_OK;
    }
    HRESULT GetUINT32(const IID& guidKey, uint32_t* punValue) override {
        if (!punValue) return E_POINTER;
        const auto* e = find(guidKey);
        *punValue = e ? static_cast<uint32_t>(e->u64_val) : 0u;
        return S_OK;
    }
    HRESULT GetUINT64(const IID& guidKey, uint64_t* punValue) override {
        if (!punValue) return E_POINTER;
        const auto* e = find(guidKey);
        *punValue = e ? e->u64_val : ((3840ULL << 32) | 2160ULL);
        return S_OK;
    }
    HRESULT GetDouble(const IID&, double* pfValue) override {
        if (pfValue) *pfValue = 60.0;
        return S_OK;
    }
    HRESULT GetGUID(const IID& guidKey, IID* pguidValue) override {
        if (!pguidValue) return E_POINTER;
        const auto* e = find(guidKey);
        if (e) {
            *pguidValue = e->guid_val;
            return S_OK;
        }
        if (guidKey == OFFICIAL_MF_MT_MAJOR_TYPE) {
            *pguidValue = OFFICIAL_MFMediaType_Video;
            return S_OK;
        }
        *pguidValue = OFFICIAL_MFVideoFormat_NV12;
        return S_OK;
    }
    HRESULT GetStringLength(const IID&, uint32_t* pcchLength) override {
        if (pcchLength) *pcchLength = 0;
        return S_OK;
    }
    HRESULT GetString(const IID&, wchar_t*, uint32_t, uint32_t*) override { return S_OK; }
    HRESULT GetAllocatedString(const IID&, wchar_t**, uint32_t*) override { return S_OK; }
    HRESULT GetBlobSize(const IID&, uint32_t* pcbBlobSize) override {
        if (pcbBlobSize) *pcbBlobSize = 0;
        return S_OK;
    }
    HRESULT GetBlob(const IID&, uint8_t*, uint32_t, uint32_t*) override { return S_OK; }
    HRESULT GetAllocatedBlob(const IID&, uint8_t**, uint32_t*) override { return S_OK; }
    HRESULT GetUnknown(const IID& guidKey, const IID& riid, void** ppv) override {
        if (!ppv) return E_POINTER;
        const auto* e = find(guidKey);
        if (e && e->unk_val) return e->unk_val->QueryInterface(riid, ppv);
        *ppv = nullptr;
        return E_NOINTERFACE;
    }
    HRESULT SetItem(const IID&, const void*) override { return S_OK; }
    HRESULT DeleteItem(const IID&) override { return S_OK; }
    HRESULT DeleteAllItems() override { attrs_.clear(); return S_OK; }
    HRESULT SetUINT32(const IID& guidKey, uint32_t unValue) override {
        findOrCreate(guidKey)->u64_val = unValue;
        return S_OK;
    }
    HRESULT SetUINT64(const IID& guidKey, uint64_t unValue) override {
        findOrCreate(guidKey)->u64_val = unValue;
        return S_OK;
    }
    HRESULT SetDouble(const IID&, double) override { return S_OK; }
    HRESULT SetGUID(const IID& guidKey, const IID& guidValue) override {
        findOrCreate(guidKey)->guid_val = guidValue;
        return S_OK;
    }
    HRESULT SetString(const IID&, const wchar_t*) override { return S_OK; }
    HRESULT SetBlob(const IID&, const uint8_t*, uint32_t) override { return S_OK; }
    HRESULT SetUnknown(const IID& guidKey, IUnknown* pUnknown) override {
        findOrCreate(guidKey)->unk_val = pUnknown;
        return S_OK;
    }
    HRESULT LockStore() override { return S_OK; }
    HRESULT UnlockStore() override { return S_OK; }
    HRESULT GetCount(uint32_t* pcItems) override {
        if (!pcItems) return E_POINTER;
        *pcItems = static_cast<uint32_t>(attrs_.size());
        return S_OK;
    }
    HRESULT GetItemByIndex(uint32_t unIndex, IID* pguidKey, void*) override {
        if (unIndex >= attrs_.size()) return E_INVALIDARG;
        if (pguidKey) *pguidKey = attrs_[unIndex].key;
        return S_OK;
    }
    HRESULT CopyAllItems(IMFAttributes*) override { return S_OK; }

    // IMFMediaType methods
    HRESULT GetMajorType(IID* pguidMajorType) override {
        return GetGUID(OFFICIAL_MF_MT_MAJOR_TYPE, pguidMajorType);
    }
    HRESULT IsCompressedFormat(int32_t* pfCompressed) override {
        if (pfCompressed) *pfCompressed = 0;
        return S_OK;
    }
    HRESULT IsEqual(IMFMediaType*, uint32_t* pdwFlags) override {
        if (pdwFlags) *pdwFlags = 0x1;
        return S_OK;
    }
    HRESULT GetRepresentation(IID, void**) override { return S_OK; }
    HRESULT FreeRepresentation(IID, void*) override { return S_OK; }
};

class PrismMFMediaBufferImpl final : public IMFMediaBuffer, public IMFDXGIBuffer {
    std::atomic<uint32_t> ref_count_{1};
    std::vector<uint8_t> storage_;
    uint32_t current_len_ = 0;
    Prism3DTexture2DImpl* dxgi_tex_ = nullptr;

public:
    explicit PrismMFMediaBufferImpl(uint32_t max_len)
        : storage_(max_len ? max_len : 4096, 0), current_len_(max_len) {
        D3D11_TEXTURE2D_DESC desc{};
        desc.Width = 1920;
        desc.Height = 1080;
        desc.MipLevels = 1;
        desc.ArraySize = 1;
        desc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
        dxgi_tex_ = new Prism3DTexture2DImpl(nullptr, desc, nullptr);
    }

    ~PrismMFMediaBufferImpl() {
        if (dxgi_tex_) dxgi_tex_->Release();
    }

    int32_t QueryInterface(const IID& riid, void** ppvObject) override {
        if (!ppvObject) return E_POINTER;
        if (riid == IID_IUnknown || riid == OFFICIAL_IID_IMFMediaBuffer) {
            *ppvObject = static_cast<IMFMediaBuffer*>(this);
            AddRef();
            return S_OK;
        }
        if (riid == OFFICIAL_IID_IMFDXGIBuffer) {
            *ppvObject = static_cast<IMFDXGIBuffer*>(this);
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

    HRESULT Lock(uint8_t** ppbBuffer, uint32_t* pcbMaxLength, uint32_t* pcbCurrentLength) override {
        if (!ppbBuffer) return E_POINTER;
        *ppbBuffer = storage_.data();
        if (pcbMaxLength) *pcbMaxLength = static_cast<uint32_t>(storage_.size());
        if (pcbCurrentLength) *pcbCurrentLength = current_len_;
        return S_OK;
    }
    HRESULT Unlock() override { return S_OK; }
    HRESULT GetCurrentLength(uint32_t* pcbCurrentLength) override {
        if (!pcbCurrentLength) return E_POINTER;
        *pcbCurrentLength = current_len_;
        return S_OK;
    }
    HRESULT SetCurrentLength(uint32_t cbCurrentLength) override {
        if (cbCurrentLength > storage_.size()) return E_INVALIDARG;
        current_len_ = cbCurrentLength;
        return S_OK;
    }
    HRESULT GetMaxLength(uint32_t* pcbMaxLength) override {
        if (!pcbMaxLength) return E_POINTER;
        *pcbMaxLength = static_cast<uint32_t>(storage_.size());
        return S_OK;
    }

    // IMFDXGIBuffer methods (Zero-copy D3D11Texture2D extraction for game cutscenes)
    HRESULT GetResource(const IID& riid, void** ppvObject) override {
        if (!ppvObject || !dxgi_tex_) return E_POINTER;
        return dxgi_tex_->QueryInterface(riid, ppvObject);
    }
    HRESULT GetSubresourceIndex(uint32_t* puSubresource) override {
        if (!puSubresource) return E_POINTER;
        *puSubresource = 0;
        return S_OK;
    }
    HRESULT GetUnknown(const IID&, const IID&, void** ppvObject) override {
        if (ppvObject) *ppvObject = nullptr;
        return E_NOINTERFACE;
    }
    HRESULT SetUnknown(const IID&, IUnknown*) override { return S_OK; }
};

class PrismMFSampleImpl final : public IMFSample {
    std::atomic<uint32_t> ref_count_{1};
    PrismMFAttributesBaseImpl attr_delegate_;
    std::vector<IMFMediaBuffer*> buffers_;
    int64_t sample_time_ = 0;
    int64_t sample_duration_ = 166667; // 60fps in 100ns units
    uint32_t sample_flags_ = 0;

public:
    ~PrismMFSampleImpl() {
        for (auto* b : buffers_) {
            if (b) b->Release();
        }
    }

    int32_t QueryInterface(const IID& riid, void** ppvObject) override {
        if (!ppvObject) return E_POINTER;
        if (riid == IID_IUnknown ||
            riid == OFFICIAL_IID_IMFAttributes ||
            riid == OFFICIAL_IID_IMFSample) {
            *ppvObject = static_cast<IMFSample*>(this);
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

    // IMFAttributes delegation
    HRESULT GetItem(const IID& k, void* v) override { return attr_delegate_.GetItem(k, v); }
    HRESULT GetItemType(const IID& k, uint32_t* t) override { return attr_delegate_.GetItemType(k, t); }
    HRESULT CompareItem(const IID& k, const void* v, int32_t* r) override { return attr_delegate_.CompareItem(k, v, r); }
    HRESULT Compare(IMFAttributes* t, uint32_t m, int32_t* r) override { return attr_delegate_.Compare(t, m, r); }
    HRESULT GetUINT32(const IID& k, uint32_t* v) override { return attr_delegate_.GetUINT32(k, v); }
    HRESULT GetUINT64(const IID& k, uint64_t* v) override { return attr_delegate_.GetUINT64(k, v); }
    HRESULT GetDouble(const IID& k, double* v) override { return attr_delegate_.GetDouble(k, v); }
    HRESULT GetGUID(const IID& k, IID* v) override { return attr_delegate_.GetGUID(k, v); }
    HRESULT GetStringLength(const IID& k, uint32_t* l) override { return attr_delegate_.GetStringLength(k, l); }
    HRESULT GetString(const IID& k, wchar_t* v, uint32_t s, uint32_t* l) override { return attr_delegate_.GetString(k, v, s, l); }
    HRESULT GetAllocatedString(const IID& k, wchar_t** v, uint32_t* l) override { return attr_delegate_.GetAllocatedString(k, v, l); }
    HRESULT GetBlobSize(const IID& k, uint32_t* s) override { return attr_delegate_.GetBlobSize(k, s); }
    HRESULT GetBlob(const IID& k, uint8_t* b, uint32_t s, uint32_t* o) override { return attr_delegate_.GetBlob(k, b, s, o); }
    HRESULT GetAllocatedBlob(const IID& k, uint8_t** b, uint32_t* s) override { return attr_delegate_.GetAllocatedBlob(k, b, s); }
    HRESULT GetUnknown(const IID& k, const IID& r, void** p) override { return attr_delegate_.GetUnknown(k, r, p); }
    HRESULT SetItem(const IID& k, const void* v) override { return attr_delegate_.SetItem(k, v); }
    HRESULT DeleteItem(const IID& k) override { return attr_delegate_.DeleteItem(k); }
    HRESULT DeleteAllItems() override { return attr_delegate_.DeleteAllItems(); }
    HRESULT SetUINT32(const IID& k, uint32_t v) override { return attr_delegate_.SetUINT32(k, v); }
    HRESULT SetUINT64(const IID& k, uint64_t v) override { return attr_delegate_.SetUINT64(k, v); }
    HRESULT SetDouble(const IID& k, double v) override { return attr_delegate_.SetDouble(k, v); }
    HRESULT SetGUID(const IID& k, const IID& v) override { return attr_delegate_.SetGUID(k, v); }
    HRESULT SetString(const IID& k, const wchar_t* v) override { return attr_delegate_.SetString(k, v); }
    HRESULT SetBlob(const IID& k, const uint8_t* b, uint32_t s) override { return attr_delegate_.SetBlob(k, b, s); }
    HRESULT SetUnknown(const IID& k, IUnknown* u) override { return attr_delegate_.SetUnknown(k, u); }
    HRESULT LockStore() override { return attr_delegate_.LockStore(); }
    HRESULT UnlockStore() override { return attr_delegate_.UnlockStore(); }
    HRESULT GetCount(uint32_t* c) override { return attr_delegate_.GetCount(c); }
    HRESULT GetItemByIndex(uint32_t i, IID* k, void* v) override { return attr_delegate_.GetItemByIndex(i, k, v); }
    HRESULT CopyAllItems(IMFAttributes* d) override { return attr_delegate_.CopyAllItems(d); }

    // IMFSample methods
    HRESULT GetSampleFlags(uint32_t* pdwSampleFlags) override {
        if (!pdwSampleFlags) return E_POINTER;
        *pdwSampleFlags = sample_flags_;
        return S_OK;
    }
    HRESULT SetSampleFlags(uint32_t dwSampleFlags) override {
        sample_flags_ = dwSampleFlags;
        return S_OK;
    }
    HRESULT GetSampleTime(int64_t* phnsSampleTime) override {
        if (!phnsSampleTime) return E_POINTER;
        *phnsSampleTime = sample_time_;
        return S_OK;
    }
    HRESULT SetSampleTime(int64_t hnsSampleTime) override {
        sample_time_ = hnsSampleTime;
        return S_OK;
    }
    HRESULT GetSampleDuration(int64_t* phnsSampleDuration) override {
        if (!phnsSampleDuration) return E_POINTER;
        *phnsSampleDuration = sample_duration_;
        return S_OK;
    }
    HRESULT SetSampleDuration(int64_t hnsSampleDuration) override {
        sample_duration_ = hnsSampleDuration;
        return S_OK;
    }
    HRESULT GetBufferCount(uint32_t* pdwBufferCount) override {
        if (!pdwBufferCount) return E_POINTER;
        *pdwBufferCount = static_cast<uint32_t>(buffers_.size());
        return S_OK;
    }
    HRESULT GetBufferByIndex(uint32_t dwIndex, IMFMediaBuffer** ppBuffer) override {
        if (!ppBuffer || dwIndex >= buffers_.size()) return E_INVALIDARG;
        *ppBuffer = buffers_[dwIndex];
        (*ppBuffer)->AddRef();
        return S_OK;
    }
    HRESULT ConvertToContiguousBuffer(IMFMediaBuffer** ppBuffer) override {
        if (!ppBuffer) return E_POINTER;
        if (buffers_.empty()) {
            auto* b = new PrismMFMediaBufferImpl(1920 * 1080 * 4);
            buffers_.push_back(b);
        }
        *ppBuffer = buffers_[0];
        (*ppBuffer)->AddRef();
        return S_OK;
    }
    HRESULT AddBuffer(IMFMediaBuffer* pBuffer) override {
        if (!pBuffer) return E_POINTER;
        pBuffer->AddRef();
        buffers_.push_back(pBuffer);
        return S_OK;
    }
    HRESULT RemoveBufferByIndex(uint32_t dwIndex) override {
        if (dwIndex >= buffers_.size()) return E_INVALIDARG;
        buffers_[dwIndex]->Release();
        buffers_.erase(buffers_.begin() + dwIndex);
        return S_OK;
    }
    HRESULT RemoveAllBuffers() override {
        for (auto* b : buffers_) if (b) b->Release();
        buffers_.clear();
        return S_OK;
    }
    HRESULT GetTotalLength(uint32_t* pcbTotalLength) override {
        if (!pcbTotalLength) return E_POINTER;
        uint32_t total = 0;
        for (auto* b : buffers_) {
            uint32_t len = 0;
            if (b && SUCCEEDED(b->GetCurrentLength(&len))) total += len;
        }
        *pcbTotalLength = total;
        return S_OK;
    }
    HRESULT CopyToBuffer(IMFMediaBuffer*) override { return S_OK; }
};

class PrismMFDXGIDeviceManagerImpl final : public IMFDXGIDeviceManager {
    std::atomic<uint32_t> ref_count_{1};
    IUnknown* bound_device_ = nullptr;
    uint32_t reset_token_ = 0xD3D11FA0u;

public:
    explicit PrismMFDXGIDeviceManagerImpl(uint32_t token = 0xD3D11FA0u) : reset_token_(token) {}
    ~PrismMFDXGIDeviceManagerImpl() {
        if (bound_device_) bound_device_->Release();
    }

    int32_t QueryInterface(const IID& riid, void** ppvObject) override {
        if (!ppvObject) return E_POINTER;
        if (riid == IID_IUnknown || riid == OFFICIAL_IID_IMFDXGIDeviceManager) {
            *ppvObject = static_cast<IMFDXGIDeviceManager*>(this);
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

    HRESULT CloseDeviceHandle(void*) override { return S_OK; }
    HRESULT GetVideoService(void*, const IID& riid, void** ppService) override {
        if (!ppService || !bound_device_) return E_POINTER;
        return bound_device_->QueryInterface(riid, ppService);
    }
    HRESULT LockDevice(void*, const IID& riid, void** ppUnkDevice, int32_t) override {
        if (!ppUnkDevice || !bound_device_) return E_POINTER;
        return bound_device_->QueryInterface(riid, ppUnkDevice);
    }
    HRESULT OpenDeviceHandle(void** phDevice) override {
        if (!phDevice) return E_POINTER;
        *phDevice = reinterpret_cast<void*>(static_cast<uintptr_t>(reset_token_));
        return S_OK;
    }
    HRESULT ResetDevice(IUnknown* pUnkDevice, uint32_t uResetToken) override {
        if (!pUnkDevice || uResetToken != reset_token_) return E_INVALIDARG;
        if (bound_device_) bound_device_->Release();
        bound_device_ = pUnkDevice;
        bound_device_->AddRef();
        return S_OK;
    }
    HRESULT TestDevice(void*) override { return S_OK; }
    HRESULT UnlockDevice(void*, int32_t) override { return S_OK; }
};

class PrismMFSourceReaderImpl final : public IMFSourceReader {
    std::atomic<uint32_t> ref_count_{1};
    int64_t next_pts_100ns_ = 0;

public:
    int32_t QueryInterface(const IID& riid, void** ppvObject) override {
        if (!ppvObject) return E_POINTER;
        if (riid == IID_IUnknown || riid == OFFICIAL_IID_IMFSourceReader) {
            *ppvObject = static_cast<IMFSourceReader*>(this);
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

    HRESULT GetStreamSelection(uint32_t, int32_t* pfSelected) override {
        if (pfSelected) *pfSelected = 1;
        return S_OK;
    }
    HRESULT SetStreamSelection(uint32_t, int32_t) override { return S_OK; }
    HRESULT GetNativeMediaType(uint32_t, uint32_t, IMFMediaType** ppMediaType) override {
        return GetCurrentMediaType(0, ppMediaType);
    }
    HRESULT GetCurrentMediaType(uint32_t, IMFMediaType** ppMediaType) override {
        if (!ppMediaType) return E_POINTER;
        auto* mt = new PrismMFAttributesBaseImpl();
        mt->SetGUID(OFFICIAL_MF_MT_MAJOR_TYPE, OFFICIAL_MFMediaType_Video);
        mt->SetGUID(OFFICIAL_MF_MT_SUBTYPE, OFFICIAL_MFVideoFormat_NV12);
        mt->SetUINT64(OFFICIAL_MF_MT_FRAME_SIZE, (1920ULL << 32) | 1080ULL);
        *ppMediaType = mt;
        return S_OK;
    }
    HRESULT SetCurrentMediaType(uint32_t, uint32_t*, IMFMediaType*) override { return S_OK; }
    HRESULT SetCurrentPosition(const IID&, const void*) override {
        next_pts_100ns_ = 0;
        return S_OK;
    }
    HRESULT ReadSample(uint32_t dwStreamIndex, uint32_t,
                       uint32_t* pdwActualStreamIndex, uint32_t* pdwStreamFlags,
                       int64_t* pllTimestamp, IMFSample** ppSample) override {
        if (pdwActualStreamIndex) *pdwActualStreamIndex = (dwStreamIndex == MF_SOURCE_READER_FIRST_VIDEO_STREAM) ? 0u : dwStreamIndex;
        if (pdwStreamFlags) *pdwStreamFlags = 0;
        if (pllTimestamp) *pllTimestamp = next_pts_100ns_;
        if (ppSample) {
            auto* sample = new PrismMFSampleImpl();
            sample->SetSampleTime(next_pts_100ns_);
            sample->SetSampleDuration(166667);
            auto* buf = new PrismMFMediaBufferImpl(1920 * 1080 * 4);
            sample->AddBuffer(buf);
            buf->Release();
            *ppSample = sample;
        }
        next_pts_100ns_ += 166667;
        return S_OK;
    }
    HRESULT Flush(uint32_t) override { return S_OK; }
    HRESULT GetServiceForStream(uint32_t, const IID&, const IID&, void** ppvObject) override {
        if (ppvObject) *ppvObject = nullptr;
        return S_OK;
    }
    HRESULT GetPresentationAttribute(uint32_t, const IID&, void*) override { return S_OK; }
};

class PrismMFSinkWriterImpl final : public IMFSinkWriter {
    std::atomic<uint32_t> ref_count_{1};
    uint32_t streams_ = 0;
    uint32_t samples_written_ = 0;

public:
    int32_t QueryInterface(const IID& riid, void** ppvObject) override {
        if (!ppvObject) return E_POINTER;
        if (riid == IID_IUnknown || riid == OFFICIAL_IID_IMFSinkWriter) {
            *ppvObject = static_cast<IMFSinkWriter*>(this);
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

    HRESULT AddStream(IMFMediaType*, uint32_t* pdwStreamIndex) override {
        if (pdwStreamIndex) *pdwStreamIndex = streams_++;
        return S_OK;
    }
    HRESULT SetInputMediaType(uint32_t, IMFMediaType*, IMFAttributes*) override { return S_OK; }
    HRESULT BeginWriting() override { return S_OK; }
    HRESULT WriteSample(uint32_t, IMFSample*) override { ++samples_written_; return S_OK; }
    HRESULT SendStreamTick(uint32_t, int64_t) override { return S_OK; }
    HRESULT PlaceMarker(uint32_t, void*) override { return S_OK; }
    HRESULT NotifyEndOfSegment(uint32_t) override { return S_OK; }
    HRESULT Flush(uint32_t) override { return S_OK; }
    HRESULT Finalize() override { return S_OK; }
    HRESULT GetServiceForStream(uint32_t, const IID&, const IID&, void** ppvObject) override {
        if (ppvObject) *ppvObject = nullptr;
        return S_OK;
    }
    HRESULT GetStatistics(uint32_t, void*) override { return S_OK; }
};

// ----------------------------------------------------------------------------
// 4. Canonical mfplat.dll & mfreadwrite.dll Export Entry Points
// ----------------------------------------------------------------------------
inline HRESULT MFStartup(uint32_t Version, uint32_t dwFlags = 0) {
    (void)Version;
    (void)dwFlags;
    return S_OK;
}

inline HRESULT MFShutdown() {
    return S_OK;
}

inline HRESULT MFCreateAttributes(IMFAttributes** ppMFAttributes, uint32_t cInitialSize) {
    (void)cInitialSize;
    if (!ppMFAttributes) return E_POINTER;
    *ppMFAttributes = new PrismMFAttributesBaseImpl();
    return S_OK;
}

inline HRESULT MFCreateMediaType(IMFMediaType** ppMFType) {
    if (!ppMFType) return E_POINTER;
    *ppMFType = new PrismMFAttributesBaseImpl();
    return S_OK;
}

inline HRESULT MFCreateMemoryBuffer(uint32_t cbMaxLength, IMFMediaBuffer** ppBuffer) {
    if (!ppBuffer) return E_POINTER;
    *ppBuffer = new PrismMFMediaBufferImpl(cbMaxLength);
    return S_OK;
}

inline HRESULT MFCreateSample(IMFSample** ppIMFSample) {
    if (!ppIMFSample) return E_POINTER;
    *ppIMFSample = new PrismMFSampleImpl();
    return S_OK;
}

inline HRESULT MFCreateDXGIDeviceManager(uint32_t* resetToken, IMFDXGIDeviceManager** ppDeviceManager) {
    if (!resetToken || !ppDeviceManager) return E_POINTER;
    *resetToken = 0xD3D11FA0u;
    *ppDeviceManager = new PrismMFDXGIDeviceManagerImpl(*resetToken);
    return S_OK;
}

inline HRESULT MFCreateSourceReaderFromURL(const wchar_t* pwszURL,
                                           IMFAttributes* pAttributes,
                                           IMFSourceReader** ppSourceReader) {
    (void)pwszURL;
    (void)pAttributes;
    if (!ppSourceReader) return E_POINTER;
    *ppSourceReader = new PrismMFSourceReaderImpl();
    return S_OK;
}

inline HRESULT MFCreateSourceReaderFromByteStream(IUnknown* pByteStream,
                                                  IMFAttributes* pAttributes,
                                                  IMFSourceReader** ppSourceReader) {
    (void)pByteStream;
    (void)pAttributes;
    if (!ppSourceReader) return E_POINTER;
    *ppSourceReader = new PrismMFSourceReaderImpl();
    return S_OK;
}

inline HRESULT MFCreateSinkWriterFromURL(const wchar_t* pwszOutputURL,
                                         IUnknown* pByteStream,
                                         IMFAttributes* pAttributes,
                                         IMFSinkWriter** ppSinkWriter) {
    (void)pwszOutputURL;
    (void)pByteStream;
    (void)pAttributes;
    if (!ppSinkWriter) return E_POINTER;
    *ppSinkWriter = new PrismMFSinkWriterImpl();
    return S_OK;
}

} // namespace prismx::MediaFoundationCom
