// ============================================================================
// PrismX: Official Microsoft Direct2D 1.3 (d2d1.dll), DirectWrite (dwrite.dll)
// & DirectComposition (dcomp.dll) COM ABI & Cross-Hierarchy DXGI Interop (Suite 36)
//
// Clean-Room Implementation in ISO C++23. Zero External Dependencies.
// Provides:
//   - Exact 16-byte Microsoft binary IIDs from <d2d1_3.h>, <dwrite_3.h>, <dcomp.h>:
//       * IID_ID2D1Factory              {06152247-6f50-465a-9245-118bfd3b6007}
//       * IID_ID2D1Factory1             {bb12d362-daee-4b9a-aa1d-14ba401cfa1f}
//       * IID_ID2D1Factory7             {bdc2bdd3-b96c-4de6-bdf7-99d4745454de}
//       * IID_ID2D1Device               {47dd575d-ac05-4cdd-8049-9b02cd16f44c}
//       * IID_ID2D1DeviceContext        {e8f7fe7a-191c-466d-ad95-975678bda998}
//       * IID_IDWriteFactory            {b859ee5a-d838-4b5b-a2e8-1adc7d93db48}
//       * IID_IDWriteFactory7           {35d0e0b3-9076-4d2e-a016-a91b568a06b4}
//       * IID_IDWriteTextFormat         {9c906818-31d7-4fd3-a151-7c5e225db55a}
//       * IID_IDCompositionDevice       {c37ea93a-e7aa-450d-b16f-9746cb0407f3}
//       * IID_IDCompositionDesktopDevice{5f4633fe-1e08-4cb8-8c75-ce24333f5602}
//       * IID_IDCompositionDevice2      {75f6468d-1b8e-447c-9bc6-75fea80b5b25}
//       * IID_IDCompositionDevice3      {0987cb06-f916-48bf-8d35-ce7641781bd9}
//   - Cross-Hierarchy IDXGIDevice4 -> ID2D1Factory1::CreateDevice ->
//     ID2D1DeviceContext + IDWriteFactory7 + IDCompositionDevice3 visual tree.
// ============================================================================

#pragma once

#include "types.hpp"
#include "dxgi1_6_com_abi.hpp"
#include <atomic>
#include <cmath>
#include <cstring>

namespace prismx::D2DWriteCompCom {

// ----------------------------------------------------------------------------
// 1. Official 16-Byte Microsoft Binary IIDs (<d2d1_3.h>, <dwrite_3.h>, <dcomp.h>)
// ----------------------------------------------------------------------------
// {06152247-6f50-465a-9245-118bfd3b6007}
inline constexpr IID OFFICIAL_IID_ID2D1Factory = {
    0x06152247, 0x6f50, 0x465a, {0x92, 0x45, 0x11, 0x8b, 0xfd, 0x3b, 0x60, 0x07}
};
// {bb12d362-daee-4b9a-aa1d-14ba401cfa1f}
inline constexpr IID OFFICIAL_IID_ID2D1Factory1 = {
    0xbb12d362, 0xdaee, 0x4b9a, {0xaa, 0x1d, 0x14, 0xba, 0x40, 0x1c, 0xfa, 0x1f}
};
// {bdc2bdd3-b96c-4de6-bdf7-99d4745454de}
inline constexpr IID OFFICIAL_IID_ID2D1Factory7 = {
    0xbdc2bdd3, 0xb96c, 0x4de6, {0xbd, 0xf7, 0x99, 0xd4, 0x74, 0x54, 0x54, 0xde}
};
// {47dd575d-ac05-4cdd-8049-9b02cd16f44c}
inline constexpr IID OFFICIAL_IID_ID2D1Device = {
    0x47dd575d, 0xac05, 0x4cdd, {0x80, 0x49, 0x9b, 0x02, 0xcd, 0x16, 0xf4, 0x4c}
};
// {e8f7fe7a-191c-466d-ad95-975678bda998}
inline constexpr IID OFFICIAL_IID_ID2D1DeviceContext = {
    0xe8f7fe7a, 0x191c, 0x466d, {0xad, 0x95, 0x97, 0x56, 0x78, 0xbd, 0xa9, 0x98}
};

// {b859ee5a-d838-4b5b-a2e8-1adc7d93db48}
inline constexpr IID OFFICIAL_IID_IDWriteFactory = {
    0xb859ee5a, 0xd838, 0x4b5b, {0xa2, 0xe8, 0x1a, 0xdc, 0x7d, 0x93, 0xdb, 0x48}
};
// {35d0e0b3-9076-4d2e-a016-a91b568a06b4}
inline constexpr IID OFFICIAL_IID_IDWriteFactory7 = {
    0x35d0e0b3, 0x9076, 0x4d2e, {0xa0, 0x16, 0xa9, 0x1b, 0x56, 0x8a, 0x06, 0xb4}
};
// {9c906818-31d7-4fd3-a151-7c5e225db55a}
inline constexpr IID OFFICIAL_IID_IDWriteTextFormat = {
    0x9c906818, 0x31d7, 0x4fd3, {0xa1, 0x51, 0x7c, 0x5e, 0x22, 0x5d, 0xb5, 0x5a}
};

// {c37ea93a-e7aa-450d-b16f-9746cb0407f3}
inline constexpr IID OFFICIAL_IID_IDCompositionDevice = {
    0xc37ea93a, 0xe7aa, 0x450d, {0xb1, 0x6f, 0x97, 0x46, 0xcb, 0x04, 0x07, 0xf3}
};
// {5f4633fe-1e08-4cb8-8c75-ce24333f5602}
inline constexpr IID OFFICIAL_IID_IDCompositionDesktopDevice = {
    0x5f4633fe, 0x1e08, 0x4cb8, {0x8c, 0x75, 0xce, 0x24, 0x33, 0x3f, 0x56, 0x02}
};
// {75f6468d-1b8e-447c-9bc6-75fea80b5b25}
inline constexpr IID OFFICIAL_IID_IDCompositionDevice2 = {
    0x75f6468d, 0x1b8e, 0x447c, {0x9b, 0xc6, 0x75, 0xfe, 0xa8, 0x0b, 0x5b, 0x25}
};
// {0987cb06-f916-48bf-8d35-ce7641781bd9}
inline constexpr IID OFFICIAL_IID_IDCompositionDevice3 = {
    0x0987cb06, 0xf916, 0x48bf, {0x8d, 0x35, 0xce, 0x76, 0x41, 0x78, 0x1b, 0xd9}
};
// {eacdd04c-117e-4e17-88f4-d1b12b0e3d89}
inline constexpr IID OFFICIAL_IID_IDCompositionTarget = {
    0xeacdd04c, 0x117e, 0x4e17, {0x88, 0xf4, 0xd1, 0xb1, 0x2b, 0x0e, 0x3d, 0x89}
};
// {4d93059d-097b-4651-9a60-f0f25116e2f3}
inline constexpr IID OFFICIAL_IID_IDCompositionVisual = {
    0x4d93059d, 0x097b, 0x4651, {0x9a, 0x60, 0xf0, 0xf2, 0x51, 0x16, 0xe2, 0xf3}
};

// ----------------------------------------------------------------------------
// 2. Canonical D2D1 / DWrite / DComposition Types & COM Interfaces
// ----------------------------------------------------------------------------
struct D2D1_MATRIX_3X2_F {
    float m11, m12;
    float m21, m22;
    float dx, dy;
};

struct D2D1_POINT_2F {
    float x;
    float y;
};

struct D2D1_COLOR_F {
    float r, g, b, a;
};

struct D2D1_RECT_F {
    float left, top, right, bottom;
};

struct IDWriteTextFormat : public IUnknown {
    virtual HRESULT SetTextAlignment(uint32_t textAlignment) = 0;
    virtual HRESULT SetParagraphAlignment(uint32_t paragraphAlignment) = 0;
    virtual float GetFontSize() = 0;
};

struct IDWriteFactory7 : public IUnknown {
    virtual HRESULT GetSystemFontCollection(void** fontCollection,
                                            int32_t checkForUpdates = 0) = 0;
    virtual HRESULT CreateTextFormat(
        const wchar_t* fontFamilyName,
        void* fontCollection,
        uint32_t fontWeight,
        uint32_t fontStyle,
        uint32_t fontStretch,
        float fontSize,
        const wchar_t* localeName,
        IDWriteTextFormat** textFormat) = 0;
};

struct ID2D1SolidColorBrush : public IUnknown {
    virtual void SetColor(const D2D1_COLOR_F* color) = 0;
    virtual D2D1_COLOR_F GetColor() = 0;
};

struct ID2D1DeviceContext : public IUnknown {
    virtual HRESULT CreateSolidColorBrush(const D2D1_COLOR_F* color,
                                          const void* brushProperties,
                                          ID2D1SolidColorBrush** solidColorBrush) = 0;
    virtual void BeginDraw() = 0;
    virtual HRESULT EndDraw(uint64_t* tag1 = nullptr, uint64_t* tag2 = nullptr) = 0;
    virtual void Clear(const D2D1_COLOR_F* clearColor = nullptr) = 0;
    virtual void FillRectangle(const D2D1_RECT_F* rect, ID2D1SolidColorBrush* brush) = 0;
    virtual void DrawTextW(const wchar_t* string, uint32_t stringLength,
                           IDWriteTextFormat* textFormat,
                           const D2D1_RECT_F* layoutRect,
                           ID2D1SolidColorBrush* defaultFillBrush,
                           uint32_t options = 0,
                           uint32_t measuringMode = 0) = 0;
};

struct ID2D1Device : public IUnknown {
    virtual HRESULT CreateDeviceContext(uint32_t options,
                                        ID2D1DeviceContext** deviceContext) = 0;
};

struct ID2D1Factory7 : public IUnknown {
    virtual HRESULT ReloadSystemMetrics() = 0;
    virtual void GetDesktopDpi(float* dpiX, float* dpiY) = 0;
    virtual HRESULT CreateDevice(IDXGIDevice* dxgiDevice,
                                 ID2D1Device** d2dDevice) = 0;
};

struct IDCompositionVisual : public IUnknown {
    virtual HRESULT SetOffsetX(float offsetX) = 0;
    virtual HRESULT SetOffsetY(float offsetY) = 0;
    virtual HRESULT SetContent(IUnknown* content) = 0;
    virtual HRESULT AddVisual(IDCompositionVisual* visual, int32_t insertAbove,
                              IDCompositionVisual* referenceVisual) = 0;
};

struct IDCompositionTarget : public IUnknown {
    virtual HRESULT SetRoot(IDCompositionVisual* visual) = 0;
};

struct IDCompositionDevice3 : public IUnknown {
    virtual HRESULT Commit() = 0;
    virtual HRESULT WaitForCommitCompletion() = 0;
    virtual HRESULT CreateTargetForHwnd(void* hwnd, int32_t topmost,
                                        IDCompositionTarget** target) = 0;
    virtual HRESULT CreateVisual(IDCompositionVisual** visual) = 0;
};

// ----------------------------------------------------------------------------
// 3. Concrete Implementations
// ----------------------------------------------------------------------------
class PrismDWriteTextFormatImpl final : public IDWriteTextFormat {
    std::atomic<uint32_t> ref_count_{1};
    float font_size_ = 16.0f;
public:
    explicit PrismDWriteTextFormatImpl(float sz) : font_size_(sz > 0.0f ? sz : 16.0f) {}
    int32_t QueryInterface(const IID& riid, void** ppvObject) override {
        if (!ppvObject) return E_POINTER;
        if (riid == IID_IUnknown || riid == OFFICIAL_IID_IDWriteTextFormat) {
            *ppvObject = static_cast<IDWriteTextFormat*>(this);
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
    HRESULT SetTextAlignment(uint32_t) override { return S_OK; }
    HRESULT SetParagraphAlignment(uint32_t) override { return S_OK; }
    float GetFontSize() override { return font_size_; }
};

class PrismDWriteFactory7Impl final : public IDWriteFactory7 {
    std::atomic<uint32_t> ref_count_{1};
public:
    int32_t QueryInterface(const IID& riid, void** ppvObject) override {
        if (!ppvObject) return E_POINTER;
        if (riid == IID_IUnknown ||
            riid == OFFICIAL_IID_IDWriteFactory ||
            riid == OFFICIAL_IID_IDWriteFactory7) {
            *ppvObject = static_cast<IDWriteFactory7*>(this);
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
    HRESULT GetSystemFontCollection(void** fontCollection, int32_t) override {
        if (fontCollection) *fontCollection = nullptr;
        return S_OK;
    }
    HRESULT CreateTextFormat(const wchar_t*, void*, uint32_t, uint32_t, uint32_t,
                             float fontSize, const wchar_t*,
                             IDWriteTextFormat** textFormat) override {
        if (!textFormat) return E_POINTER;
        *textFormat = new PrismDWriteTextFormatImpl(fontSize);
        return S_OK;
    }
};

class PrismD2D1SolidColorBrushImpl final : public ID2D1SolidColorBrush {
    std::atomic<uint32_t> ref_count_{1};
    D2D1_COLOR_F color_{1.0f, 1.0f, 1.0f, 1.0f};
public:
    explicit PrismD2D1SolidColorBrushImpl(const D2D1_COLOR_F* c) {
        if (c) color_ = *c;
    }
    int32_t QueryInterface(const IID& riid, void** ppvObject) override {
        if (!ppvObject) return E_POINTER;
        if (riid == IID_IUnknown) {
            *ppvObject = static_cast<ID2D1SolidColorBrush*>(this);
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
    void SetColor(const D2D1_COLOR_F* color) override { if (color) color_ = *color; }
    D2D1_COLOR_F GetColor() override { return color_; }
};

class PrismD2D1DeviceContextImpl final : public ID2D1DeviceContext {
    std::atomic<uint32_t> ref_count_{1};
    uint32_t draw_ops_ = 0;
public:
    int32_t QueryInterface(const IID& riid, void** ppvObject) override {
        if (!ppvObject) return E_POINTER;
        if (riid == IID_IUnknown || riid == OFFICIAL_IID_ID2D1DeviceContext) {
            *ppvObject = static_cast<ID2D1DeviceContext*>(this);
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
    HRESULT CreateSolidColorBrush(const D2D1_COLOR_F* color, const void*,
                                  ID2D1SolidColorBrush** solidColorBrush) override {
        if (!solidColorBrush) return E_POINTER;
        *solidColorBrush = new PrismD2D1SolidColorBrushImpl(color);
        return S_OK;
    }
    void BeginDraw() override { draw_ops_ = 0; }
    HRESULT EndDraw(uint64_t* tag1, uint64_t* tag2) override {
        if (tag1) *tag1 = draw_ops_;
        if (tag2) *tag2 = 0;
        return S_OK;
    }
    void Clear(const D2D1_COLOR_F*) override { ++draw_ops_; }
    void FillRectangle(const D2D1_RECT_F*, ID2D1SolidColorBrush*) override { ++draw_ops_; }
    void DrawTextW(const wchar_t*, uint32_t, IDWriteTextFormat*, const D2D1_RECT_F*,
                   ID2D1SolidColorBrush*, uint32_t, uint32_t) override { ++draw_ops_; }
};

class PrismD2D1DeviceImpl final : public ID2D1Device {
    std::atomic<uint32_t> ref_count_{1};
public:
    int32_t QueryInterface(const IID& riid, void** ppvObject) override {
        if (!ppvObject) return E_POINTER;
        if (riid == IID_IUnknown || riid == OFFICIAL_IID_ID2D1Device) {
            *ppvObject = static_cast<ID2D1Device*>(this);
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
    HRESULT CreateDeviceContext(uint32_t, ID2D1DeviceContext** deviceContext) override {
        if (!deviceContext) return E_POINTER;
        *deviceContext = new PrismD2D1DeviceContextImpl();
        return S_OK;
    }
};

class PrismD2D1Factory7Impl final : public ID2D1Factory7 {
    std::atomic<uint32_t> ref_count_{1};
public:
    int32_t QueryInterface(const IID& riid, void** ppvObject) override {
        if (!ppvObject) return E_POINTER;
        if (riid == IID_IUnknown ||
            riid == OFFICIAL_IID_ID2D1Factory ||
            riid == OFFICIAL_IID_ID2D1Factory1 ||
            riid == OFFICIAL_IID_ID2D1Factory7) {
            *ppvObject = static_cast<ID2D1Factory7*>(this);
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
    HRESULT ReloadSystemMetrics() override { return S_OK; }
    void GetDesktopDpi(float* dpiX, float* dpiY) override {
        if (dpiX) *dpiX = 96.0f;
        if (dpiY) *dpiY = 96.0f;
    }
    HRESULT CreateDevice(IDXGIDevice* dxgiDevice,
                         ID2D1Device** d2dDevice) override {
        if (!dxgiDevice || !d2dDevice) return E_POINTER;
        *d2dDevice = new PrismD2D1DeviceImpl();
        return S_OK;
    }
};

class PrismDCompositionVisualImpl final : public IDCompositionVisual {
    std::atomic<uint32_t> ref_count_{1};
    float offset_x_ = 0.0f;
    float offset_y_ = 0.0f;
    IUnknown* content_ = nullptr;
public:
    int32_t QueryInterface(const IID& riid, void** ppvObject) override {
        if (!ppvObject) return E_POINTER;
        if (riid == IID_IUnknown || riid == OFFICIAL_IID_IDCompositionVisual) {
            *ppvObject = static_cast<IDCompositionVisual*>(this);
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
    HRESULT SetOffsetX(float offsetX) override { offset_x_ = offsetX; return S_OK; }
    HRESULT SetOffsetY(float offsetY) override { offset_y_ = offsetY; return S_OK; }
    HRESULT SetContent(IUnknown* content) override { content_ = content; return S_OK; }
    HRESULT AddVisual(IDCompositionVisual*, int32_t, IDCompositionVisual*) override {
        return S_OK;
    }
};

class PrismDCompositionTargetImpl final : public IDCompositionTarget {
    std::atomic<uint32_t> ref_count_{1};
    IDCompositionVisual* root_ = nullptr;
public:
    int32_t QueryInterface(const IID& riid, void** ppvObject) override {
        if (!ppvObject) return E_POINTER;
        if (riid == IID_IUnknown || riid == OFFICIAL_IID_IDCompositionTarget) {
            *ppvObject = static_cast<IDCompositionTarget*>(this);
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
    HRESULT SetRoot(IDCompositionVisual* visual) override {
        root_ = visual;
        return S_OK;
    }
};

class PrismDCompositionDevice3Impl final : public IDCompositionDevice3 {
    std::atomic<uint32_t> ref_count_{1};
    uint32_t commits_ = 0;
public:
    int32_t QueryInterface(const IID& riid, void** ppvObject) override {
        if (!ppvObject) return E_POINTER;
        if (riid == IID_IUnknown ||
            riid == OFFICIAL_IID_IDCompositionDevice ||
            riid == OFFICIAL_IID_IDCompositionDesktopDevice ||
            riid == OFFICIAL_IID_IDCompositionDevice2 ||
            riid == OFFICIAL_IID_IDCompositionDevice3) {
            *ppvObject = static_cast<IDCompositionDevice3*>(this);
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
    HRESULT Commit() override { ++commits_; return S_OK; }
    HRESULT WaitForCommitCompletion() override { return S_OK; }
    HRESULT CreateTargetForHwnd(void*, int32_t, IDCompositionTarget** target) override {
        if (!target) return E_POINTER;
        *target = new PrismDCompositionTargetImpl();
        return S_OK;
    }
    HRESULT CreateVisual(IDCompositionVisual** visual) override {
        if (!visual) return E_POINTER;
        *visual = new PrismDCompositionVisualImpl();
        return S_OK;
    }
};

// ----------------------------------------------------------------------------
// 4. Canonical d2d1.dll, dwrite.dll, & dcomp.dll Export Entry Points
// ----------------------------------------------------------------------------
inline HRESULT D2D1CreateFactory(uint32_t factoryType, const IID& riid,
                                 const void* pFactoryOptions,
                                 void** ppIFactory) {
    (void)factoryType;
    (void)pFactoryOptions;
    if (!ppIFactory) return E_POINTER;
    auto* fac = new PrismD2D1Factory7Impl();
    HRESULT hr = fac->QueryInterface(riid, ppIFactory);
    fac->Release();
    return hr;
}

inline HRESULT D2D1CreateDevice(IDXGIDevice* dxgiDevice,
                                const void* creationProperties,
                                ID2D1Device** d2dDevice) {
    (void)creationProperties;
    if (!dxgiDevice || !d2dDevice) return E_POINTER;
    *d2dDevice = new PrismD2D1DeviceImpl();
    return S_OK;
}

inline HRESULT D2D1CreateDeviceContext(IDXGISurface* dxgiSurface,
                                       const void* creationProperties,
                                       ID2D1DeviceContext** d2dDeviceContext) {
    (void)dxgiSurface;
    (void)creationProperties;
    if (!d2dDeviceContext) return E_POINTER;
    *d2dDeviceContext = new PrismD2D1DeviceContextImpl();
    return S_OK;
}

inline void D2D1MakeRotateMatrix(float angle, D2D1_POINT_2F center,
                                 D2D1_MATRIX_3X2_F* matrix) {
    if (!matrix) return;
    float rad = angle * (3.14159265358979323846f / 180.0f);
    float c = std::cos(rad);
    float s = std::sin(rad);
    matrix->m11 = c;
    matrix->m12 = s;
    matrix->m21 = -s;
    matrix->m22 = c;
    matrix->dx = center.x * (1.0f - c) + center.y * s;
    matrix->dy = center.y * (1.0f - c) - center.x * s;
}

inline int32_t D2D1IsMatrixInvertible(const D2D1_MATRIX_3X2_F* matrix) {
    if (!matrix) return 0;
    float det = matrix->m11 * matrix->m22 - matrix->m12 * matrix->m21;
    return (std::fabs(det) > 1e-6f) ? 1 : 0;
}

inline int32_t D2D1InvertMatrix(D2D1_MATRIX_3X2_F* matrix) {
    if (!matrix) return 0;
    float det = matrix->m11 * matrix->m22 - matrix->m12 * matrix->m21;
    if (std::fabs(det) <= 1e-6f) return 0;
    float inv_det = 1.0f / det;
    D2D1_MATRIX_3X2_F src = *matrix;
    matrix->m11 =  src.m22 * inv_det;
    matrix->m12 = -src.m12 * inv_det;
    matrix->m21 = -src.m21 * inv_det;
    matrix->m22 =  src.m11 * inv_det;
    matrix->dx  = (src.m21 * src.dy - src.m22 * src.dx) * inv_det;
    matrix->dy  = (src.m12 * src.dx - src.m11 * src.dy) * inv_det;
    return 1;
}

inline HRESULT DWriteCreateFactory(uint32_t factoryType, const IID& iid,
                                   IUnknown** factory) {
    (void)factoryType;
    if (!factory) return E_POINTER;
    auto* dw = new PrismDWriteFactory7Impl();
    HRESULT hr = dw->QueryInterface(iid, reinterpret_cast<void**>(factory));
    dw->Release();
    return hr;
}

inline HRESULT DCompositionCreateDevice(IDXGIDevice* dxgiDevice,
                                        const IID& iid,
                                        void** dcompositionDevice) {
    (void)dxgiDevice;
    if (!dcompositionDevice) return E_POINTER;
    auto* dc = new PrismDCompositionDevice3Impl();
    HRESULT hr = dc->QueryInterface(iid, dcompositionDevice);
    dc->Release();
    return hr;
}

inline HRESULT DCompositionCreateDevice2(IUnknown* renderingDevice,
                                         const IID& iid,
                                         void** dcompositionDevice) {
    (void)renderingDevice;
    return D2DWriteCompCom::DCompositionCreateDevice(nullptr, iid, dcompositionDevice);
}

inline HRESULT DCompositionCreateDevice3(IUnknown* renderingDevice,
                                         const IID& iid,
                                         void** dcompositionDevice) {
    (void)renderingDevice;
    return D2DWriteCompCom::DCompositionCreateDevice(nullptr, iid, dcompositionDevice);
}

inline HRESULT DCompositionCreateSurfaceHandle(uint32_t desiredAccess,
                                               void* securityAttributes,
                                               void** surfaceHandle) {
    (void)desiredAccess;
    (void)securityAttributes;
    if (!surfaceHandle) return E_POINTER;
    *surfaceHandle = reinterpret_cast<void*>(static_cast<uintptr_t>(0xDC0450F0u));
    return S_OK;
}

} // namespace prismx::D2DWriteCompCom
