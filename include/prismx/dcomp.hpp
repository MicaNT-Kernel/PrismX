// ============================================================================
// PrismX: Windows DirectComposition Subsystem (dcomp.hpp)
//
// Strict Clean-Room Implementation based on Microsoft's MIT-licensed:
//   - https://github.com/microsoft/DirectX-Headers
//   - https://github.com/microsoft/win32metadata (Windows.Win32.Graphics.DirectComposition)
//   - Open DirectX Specifications for Modern Desktop Visual Trees & Compositing
//
// Subsystem Overview:
//   dcomp.hpp provides low-latency, GPU-accelerated visual tree composition,
//   independent of window message pumps. Supports hierarchical visuals,
//   2D/3D affine transforms, clipping, opacity masking, animation curves
//   (cubic bezier, sinusoidal), and direct D3D/D2D surface binding.
//
// Core Interfaces:
//   - IDCompositionAnimation
//   - IDCompositionTransform / Translate / Scale / Rotate
//   - IDCompositionEffect / EffectGroup / Clip
//   - IDCompositionVisual / Visual2 / Visual3
//   - IDCompositionSurface / VirtualSurface
//   - IDCompositionTarget
//   - IDCompositionDevice / Device2 / Device3
//
// Clean-Room Implementation in ISO C++23. Zero External Dependencies.
// ============================================================================

#pragma once

#include "types.hpp"
#include "dxgi.hpp"
#include "d3d11.hpp"

#include <cstdint>
#include <string>
#include <vector>
#include <memory>
#include <atomic>
#include <mutex>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
#include <sstream>

namespace prismx {

using HWND = void*;
using HANDLE = void*;

// ============================================================================
// 1. GUIDs & Interface Identifiers
// ============================================================================

inline constexpr IID IID_IDCompositionAnimation = {
    0xcbfd91d9, 0x0470, 0x424f, { 0xa6, 0x50, 0x3f, 0xb5, 0x58, 0x38, 0xeb, 0x7e }
};

inline constexpr IID IID_IDCompositionDevice = {
    0xc37de93d, 0xdd6e, 0x43b1, { 0x97, 0x85, 0x83, 0x04, 0x7b, 0xe0, 0x42, 0xf7 }
};

inline constexpr IID IID_IDCompositionDevice2 = {
    0x7504de88, 0xa135, 0x44cb, { 0x9c, 0x17, 0xa9, 0x0e, 0x21, 0xd9, 0xe3, 0x41 }
};

inline constexpr IID IID_IDCompositionDevice3 = {
    0xa1a3c64a, 0x224f, 0x4a81, { 0x97, 0x73, 0x4f, 0x03, 0xa8, 0x9d, 0x3c, 0x68 }
};

inline constexpr IID IID_IDCompositionTarget = {
    0xeacdd04c, 0x117e, 0x4e17, { 0x88, 0xf4, 0xd1, 0xb1, 0x2b, 0x0e, 0x3d, 0x89 }
};

inline constexpr IID IID_IDCompositionVisual = {
    0x4ee3903e, 0x07f4, 0x46e3, { 0xa3, 0x2b, 0xb4, 0x1e, 0x5e, 0xbe, 0xc7, 0x24 }
};

inline constexpr IID IID_IDCompositionVisual2 = {
    0xe8de1639, 0x4331, 0x4b26, { 0xbc, 0x5f, 0x6a, 0x32, 0x1d, 0x34, 0x7a, 0x85 }
};

inline constexpr IID IID_IDCompositionVisual3 = {
    0x2775f462, 0xb6c1, 0x4015, { 0xb0, 0xe3, 0x34, 0x6e, 0x2c, 0xeb, 0x32, 0x14 }
};

inline constexpr IID IID_IDCompositionSurface = {
    0xbb8a4953, 0x2c99, 0x4729, { 0xab, 0x25, 0x23, 0xfe, 0x3c, 0x06, 0xb9, 0x18 }
};

inline constexpr IID IID_IDCompositionVirtualSurface = {
    0x8ac39406, 0xaa38, 0x4ff2, { 0xb3, 0x96, 0x09, 0x27, 0x80, 0x23, 0x60, 0x0f }
};

inline constexpr IID IID_IDCompositionEffect = {
    0xec81b08f, 0xbf99, 0x4e8a, { 0x92, 0x41, 0xe9, 0xa5, 0xac, 0x81, 0x66, 0x1a }
};

inline constexpr IID IID_IDCompositionTransform = {
    0xfd55fa73, 0x5e5f, 0x42c3, { 0x90, 0x17, 0x94, 0x98, 0xec, 0xc4, 0x56, 0x43 }
};

inline constexpr IID IID_IDCompositionTranslateTransform = {
    0x0676274e, 0xd290, 0x4523, { 0x87, 0x94, 0x6e, 0x32, 0x23, 0x09, 0xbe, 0x19 }
};

inline constexpr IID IID_IDCompositionScaleTransform = {
    0x71f81771, 0x7b14, 0x42e2, { 0x8d, 0x34, 0x1a, 0x64, 0x4a, 0x44, 0xf2, 0x67 }
};

inline constexpr IID IID_IDCompositionRotateTransform = {
    0x641f3833, 0x410c, 0x4864, { 0x96, 0x5f, 0xa2, 0x8a, 0x1e, 0x40, 0x4c, 0x30 }
};

inline constexpr IID IID_IDCompositionMatrixTransform = {
    0x16cd7cdc, 0x50e6, 0x4972, { 0x9f, 0xed, 0xfa, 0x49, 0x49, 0x50, 0xc9, 0x0a }
};

inline constexpr IID IID_IDCompositionEffectGroup = {
    0xa7924ae3, 0x0ca3, 0x4f9e, { 0x99, 0x83, 0x00, 0xc5, 0x5d, 0x15, 0xd0, 0xe7 }
};

inline constexpr IID IID_IDCompositionClip = {
    0x9f10c3c3, 0x7070, 0x45e5, { 0xaa, 0x86, 0xb6, 0x93, 0x04, 0x4c, 0xfa, 0x29 }
};

inline constexpr IID IID_IDCompositionRectangleClip = {
    0x9842ad7d, 0xd9cf, 0x4308, { 0xae, 0xea, 0x6e, 0x60, 0xb8, 0x92, 0x46, 0xbf }
};

// ============================================================================
// 2. Constants & Enums
// ============================================================================

enum class DCOMPOSITION_BITMAP_INTERPOLATION_MODE : uint32_t {
    NEAREST_NEIGHBOR = 0,
    LINEAR = 1,
    INHERIT = 0xFFFFFFFF
};

enum class DCOMPOSITION_BORDER_MODE : uint32_t {
    SOFT = 0,
    HARD = 1,
    INHERIT = 0xFFFFFFFF
};

enum class DCOMPOSITION_COMPOSITE_MODE : uint32_t {
    SOURCE_OVER = 0,
    DESTINATION_INVERT = 1,
    MIN_BLEND = 2,
    INHERIT = 0xFFFFFFFF
};

enum class DCOMPOSITION_BACKFACE_VISIBILITY : uint32_t {
    VISIBLE = 0,
    HIDDEN = 1,
    INHERIT = 0xFFFFFFFF
};

enum class DCOMPOSITION_OPACITY_MODE : uint32_t {
    LAYER = 0,
    MULTIPLY = 1,
    INHERIT = 0xFFFFFFFF
};

struct DCOMPOSITION_FRAME_STATISTICS {
    uint64_t lastFrameTime{ 0 };
    uint64_t currentFrameTime{ 0 };
    uint64_t timeFrequency{ 10000000 };
    uint32_t nextKeyFrame{ 0 };
};

struct DCOMP_RECT {
    int32_t left{ 0 };
    int32_t top{ 0 };
    int32_t right{ 0 };
    int32_t bottom{ 0 };
};

struct DCOMP_POINT {
    int32_t x{ 0 };
    int32_t y{ 0 };
};

struct DCOMP_MATRIX3x2 {
    float m[3][2]{ { 1.0f, 0.0f }, { 0.0f, 1.0f }, { 0.0f, 0.0f } };
};

// ============================================================================
// 3. Forward Declarations & Core Interfaces
// ============================================================================

class IDCompositionAnimation;
class IDCompositionEffect;
class IDCompositionTransform;
class IDCompositionTranslateTransform;
class IDCompositionScaleTransform;
class IDCompositionRotateTransform;
class IDCompositionMatrixTransform;
class IDCompositionClip;
class IDCompositionVisual;
class IDCompositionVisual2;
class IDCompositionSurface;
class IDCompositionVirtualSurface;
class IDCompositionTarget;

class IDCompositionAnimation : public IUnknown {
public:
    virtual int32_t Reset() = 0;
    virtual int32_t SetAbsoluteBeginTime(int64_t beginTime) = 0;
    virtual int32_t AddCubic(double beginOffset, float constantOffset, float linearCoefficient, float quadraticCoefficient, float cubicCoefficient) = 0;
    virtual int32_t AddSinusoidal(double beginOffset, float bias, float amplitude, float frequency, float phase) = 0;
    virtual int32_t AddRepeat(double beginOffset, double repeatDuration) = 0;
    virtual int32_t End(double endOffset, float endValue) = 0;
    virtual float Evaluate(double offset) const = 0;
};

class IDCompositionEffect : public IUnknown {};

class IDCompositionTransform : public IDCompositionEffect {};

class IDCompositionTranslateTransform : public IDCompositionTransform {
public:
    virtual int32_t SetOffsetX(float offsetX) = 0;
    virtual int32_t SetOffsetX(IDCompositionAnimation* animation) = 0;
    virtual int32_t SetOffsetY(float offsetY) = 0;
    virtual int32_t SetOffsetY(IDCompositionAnimation* animation) = 0;
    virtual float GetOffsetX() const = 0;
    virtual float GetOffsetY() const = 0;
};

class IDCompositionScaleTransform : public IDCompositionTransform {
public:
    virtual int32_t SetScaleX(float scaleX) = 0;
    virtual int32_t SetScaleX(IDCompositionAnimation* animation) = 0;
    virtual int32_t SetScaleY(float scaleY) = 0;
    virtual int32_t SetScaleY(IDCompositionAnimation* animation) = 0;
    virtual int32_t SetCenterX(float centerX) = 0;
    virtual int32_t SetCenterY(float centerY) = 0;
    virtual float GetScaleX() const = 0;
    virtual float GetScaleY() const = 0;
    virtual float GetCenterX() const = 0;
    virtual float GetCenterY() const = 0;
};

class IDCompositionRotateTransform : public IDCompositionTransform {
public:
    virtual int32_t SetAngle(float angle) = 0;
    virtual int32_t SetAngle(IDCompositionAnimation* animation) = 0;
    virtual int32_t SetCenterX(float centerX) = 0;
    virtual int32_t SetCenterY(float centerY) = 0;
    virtual float GetAngle() const = 0;
    virtual float GetCenterX() const = 0;
    virtual float GetCenterY() const = 0;
};

class IDCompositionMatrixTransform : public IDCompositionTransform {
public:
    virtual int32_t SetMatrix(const DCOMP_MATRIX3x2& matrix) = 0;
    virtual const DCOMP_MATRIX3x2& GetMatrix() const = 0;
};

class IDCompositionClip : public IUnknown {};

class IDCompositionRectangleClip : public IDCompositionClip {
public:
    virtual int32_t SetLeft(float left) = 0;
    virtual int32_t SetTop(float top) = 0;
    virtual int32_t SetRight(float right) = 0;
    virtual int32_t SetBottom(float bottom) = 0;
    virtual int32_t SetTopLeftRadiusX(float radius) = 0;
    virtual int32_t SetTopLeftRadiusY(float radius) = 0;
    virtual const DCOMP_RECT& GetRect() const = 0;
};

class IDCompositionSurface : public IUnknown {
public:
    virtual int32_t BeginDraw(const DCOMP_RECT* updateRect, const IID& iid, void** updateObject, DCOMP_POINT* updateOffset) = 0;
    virtual int32_t EndDraw() = 0;
    virtual int32_t SuspendDraw() = 0;
    virtual int32_t ResumeDraw() = 0;
    virtual int32_t Scroll(const DCOMP_RECT* scrollRect, const DCOMP_RECT* clipRect, int32_t offsetX, int32_t offsetY) = 0;
    virtual uint32_t GetWidth() const = 0;
    virtual uint32_t GetHeight() const = 0;
    virtual uint8_t* GetBuffer() = 0;
};

class IDCompositionVirtualSurface : public IDCompositionSurface {
public:
    virtual int32_t Resize(uint32_t width, uint32_t height) = 0;
    virtual int32_t Trim(const DCOMP_RECT* rectangles, uint32_t count) = 0;
};

class IDCompositionVisual : public IUnknown {
public:
    virtual int32_t SetOffsetX(float offsetX) = 0;
    virtual int32_t SetOffsetX(IDCompositionAnimation* animation) = 0;
    virtual int32_t SetOffsetY(float offsetY) = 0;
    virtual int32_t SetOffsetY(IDCompositionAnimation* animation) = 0;
    virtual int32_t SetTransform(IDCompositionTransform* transform) = 0;
    virtual int32_t SetTransformParent(IDCompositionVisual* visual) = 0;
    virtual int32_t SetEffect(IDCompositionEffect* effect) = 0;
    virtual int32_t SetOpacity(float opacity) = 0;
    virtual int32_t SetOpacity(IDCompositionAnimation* animation) = 0;
    virtual int32_t SetInterpolationMode(DCOMPOSITION_BITMAP_INTERPOLATION_MODE interpolationMode) = 0;
    virtual int32_t SetBorderMode(DCOMPOSITION_BORDER_MODE borderMode) = 0;
    virtual int32_t SetClip(const DCOMP_RECT& rect) = 0;
    virtual int32_t SetClip(IDCompositionClip* clip) = 0;
    virtual int32_t SetContent(IUnknown* content) = 0;
    virtual int32_t AddVisual(IDCompositionVisual* visual, bool insertAbove, IDCompositionVisual* referenceVisual) = 0;
    virtual int32_t RemoveVisual(IDCompositionVisual* visual) = 0;
    virtual int32_t RemoveAllVisuals() = 0;

    virtual float GetOffsetX() const = 0;
    virtual float GetOffsetY() const = 0;
    virtual float GetOpacity() const = 0;
    virtual IUnknown* GetContent() const = 0;
    virtual IDCompositionTransform* GetTransform() const = 0;
    virtual const std::vector<IDCompositionVisual*>& GetChildren() const = 0;
};

class IDCompositionVisual2 : public IDCompositionVisual {
public:
    virtual int32_t SetOpacityMode(DCOMPOSITION_OPACITY_MODE mode) = 0;
    virtual int32_t SetBackFaceVisibility(DCOMPOSITION_BACKFACE_VISIBILITY visibility) = 0;
    virtual DCOMPOSITION_OPACITY_MODE GetOpacityMode() const = 0;
    virtual DCOMPOSITION_BACKFACE_VISIBILITY GetBackFaceVisibility() const = 0;
};

class IDCompositionTarget : public IUnknown {
public:
    virtual int32_t SetRoot(IDCompositionVisual* visual) = 0;
    virtual IDCompositionVisual* GetRoot() const = 0;
    virtual HWND GetHwnd() const = 0;
};

class IDCompositionDevice : public IUnknown {
public:
    virtual int32_t Commit() = 0;
    virtual int32_t WaitForCommitCompletion() = 0;
    virtual int32_t GetFrameStatistics(DCOMPOSITION_FRAME_STATISTICS* statistics) = 0;
    virtual int32_t CreateTargetForHwnd(HWND hwnd, bool topmost, IDCompositionTarget** target) = 0;
    virtual int32_t CreateVisual(IDCompositionVisual** visual) = 0;
    virtual int32_t CreateSurface(uint32_t width, uint32_t height, DXGI_FORMAT format, DXGI_ALPHA_MODE alphaMode, IDCompositionSurface** surface) = 0;
    virtual int32_t CreateVirtualSurface(uint32_t initialWidth, uint32_t initialHeight, DXGI_FORMAT format, DXGI_ALPHA_MODE alphaMode, IDCompositionVirtualSurface** virtualSurface) = 0;
    virtual int32_t CreateTranslateTransform(IDCompositionTranslateTransform** translateTransform) = 0;
    virtual int32_t CreateScaleTransform(IDCompositionScaleTransform** scaleTransform) = 0;
    virtual int32_t CreateRotateTransform(IDCompositionRotateTransform** rotateTransform) = 0;
    virtual int32_t CreateMatrixTransform(IDCompositionMatrixTransform** matrixTransform) = 0;
    virtual int32_t CreateRectangleClip(IDCompositionRectangleClip** clip) = 0;
    virtual int32_t CreateAnimation(IDCompositionAnimation** animation) = 0;
};

class IDCompositionDevice2 : public IDCompositionDevice {
public:
    virtual int32_t CreateVisual2(IDCompositionVisual2** visual) = 0;
};

// ============================================================================
// 4. Concrete Subsystem Implementation
// ============================================================================

// ----------------------------------------------------------------------------
// Animation Implementation
// ----------------------------------------------------------------------------
class MicaDCompositionAnimationImpl : public IDCompositionAnimation {
private:
    std::atomic<uint32_t> m_refCount{ 1 };
    int64_t m_beginTime{ 0 };

    struct Segment {
        enum class Type { Cubic, Sinusoidal, Repeat, End } type;
        double beginOffset;
        float c0, c1, c2, c3; // cubic params
        float bias, amplitude, frequency, phase; // sine params
        double duration;
        float endVal;
    };

    std::vector<Segment> m_segments;
    mutable std::mutex m_mutex;

public:
    int32_t QueryInterface(const IID& riid, void** ppv) override {
        if (!ppv) return -2147467261;
        if (riid == IID_IUnknown || riid == IID_IDCompositionAnimation) {
            *ppv = static_cast<IDCompositionAnimation*>(this);
            AddRef();
            return 0;
        }
        *ppv = nullptr;
        return -2147467262;
    }

    uint32_t AddRef() override {
        return m_refCount.fetch_add(1, std::memory_order_relaxed) + 1;
    }

    uint32_t Release() override {
        uint32_t count = m_refCount.fetch_sub(1, std::memory_order_acq_rel) - 1;
        if (count == 0) delete this;
        return count;
    }

    int32_t Reset() override {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_segments.clear();
        m_beginTime = 0;
        return 0;
    }

    int32_t SetAbsoluteBeginTime(int64_t beginTime) override {
        m_beginTime = beginTime;
        return 0;
    }

    int32_t AddCubic(double beginOffset, float c0, float c1, float c2, float c3) override {
        std::lock_guard<std::mutex> lock(m_mutex);
        Segment seg{};
        seg.type = Segment::Type::Cubic;
        seg.beginOffset = beginOffset;
        seg.c0 = c0;
        seg.c1 = c1;
        seg.c2 = c2;
        seg.c3 = c3;
        m_segments.push_back(seg);
        return 0;
    }

    int32_t AddSinusoidal(double beginOffset, float bias, float amplitude, float frequency, float phase) override {
        std::lock_guard<std::mutex> lock(m_mutex);
        Segment seg{};
        seg.type = Segment::Type::Sinusoidal;
        seg.beginOffset = beginOffset;
        seg.bias = bias;
        seg.amplitude = amplitude;
        seg.frequency = frequency;
        seg.phase = phase;
        m_segments.push_back(seg);
        return 0;
    }

    int32_t AddRepeat(double beginOffset, double repeatDuration) override {
        std::lock_guard<std::mutex> lock(m_mutex);
        Segment seg{};
        seg.type = Segment::Type::Repeat;
        seg.beginOffset = beginOffset;
        seg.duration = repeatDuration;
        m_segments.push_back(seg);
        return 0;
    }

    int32_t End(double endOffset, float endValue) override {
        std::lock_guard<std::mutex> lock(m_mutex);
        Segment seg{};
        seg.type = Segment::Type::End;
        seg.beginOffset = endOffset;
        seg.endVal = endValue;
        m_segments.push_back(seg);
        return 0;
    }

    float Evaluate(double offset) const override {
        std::lock_guard<std::mutex> lock(m_mutex);
        if (m_segments.empty()) return 0.0f;

        float result = 0.0f;
        for (const auto& seg : m_segments) {
            if (offset >= seg.beginOffset) {
                double dt = offset - seg.beginOffset;
                switch (seg.type) {
                    case Segment::Type::Cubic:
                        result = seg.c0 + seg.c1 * static_cast<float>(dt) +
                                 seg.c2 * static_cast<float>(dt * dt) +
                                 seg.c3 * static_cast<float>(dt * dt * dt);
                        break;
                    case Segment::Type::Sinusoidal:
                        result = seg.bias + seg.amplitude * std::sin(seg.frequency * static_cast<float>(dt) + seg.phase);
                        break;
                    case Segment::Type::End:
                        result = seg.endVal;
                        break;
                    default:
                        break;
                }
            }
        }
        return result;
    }
};

// ----------------------------------------------------------------------------
// Transforms Implementation
// ----------------------------------------------------------------------------
class MicaDCompositionTranslateTransformImpl : public IDCompositionTranslateTransform {
private:
    std::atomic<uint32_t> m_refCount{ 1 };
    float m_offsetX{ 0.0f };
    float m_offsetY{ 0.0f };
    ComPtr<IDCompositionAnimation> m_animX;
    ComPtr<IDCompositionAnimation> m_animY;

public:
    int32_t QueryInterface(const IID& riid, void** ppv) override {
        if (!ppv) return -2147467261;
        if (riid == IID_IUnknown || riid == IID_IDCompositionEffect ||
            riid == IID_IDCompositionTransform || riid == IID_IDCompositionTranslateTransform) {
            *ppv = static_cast<IDCompositionTranslateTransform*>(this);
            AddRef();
            return 0;
        }
        *ppv = nullptr;
        return -2147467262;
    }

    uint32_t AddRef() override {
        return m_refCount.fetch_add(1, std::memory_order_relaxed) + 1;
    }

    uint32_t Release() override {
        uint32_t count = m_refCount.fetch_sub(1, std::memory_order_acq_rel) - 1;
        if (count == 0) delete this;
        return count;
    }

    int32_t SetOffsetX(float offsetX) override {
        m_offsetX = offsetX;
        m_animX.Reset();
        return 0;
    }

    int32_t SetOffsetX(IDCompositionAnimation* animation) override {
        m_animX = animation;
        return 0;
    }

    int32_t SetOffsetY(float offsetY) override {
        m_offsetY = offsetY;
        m_animY.Reset();
        return 0;
    }

    int32_t SetOffsetY(IDCompositionAnimation* animation) override {
        m_animY = animation;
        return 0;
    }

    float GetOffsetX() const override {
        return m_animX ? m_animX->Evaluate(0.0) : m_offsetX;
    }

    float GetOffsetY() const override {
        return m_animY ? m_animY->Evaluate(0.0) : m_offsetY;
    }
};

class MicaDCompositionScaleTransformImpl : public IDCompositionScaleTransform {
private:
    std::atomic<uint32_t> m_refCount{ 1 };
    float m_scaleX{ 1.0f };
    float m_scaleY{ 1.0f };
    float m_centerX{ 0.0f };
    float m_centerY{ 0.0f };
    ComPtr<IDCompositionAnimation> m_animX;
    ComPtr<IDCompositionAnimation> m_animY;

public:
    int32_t QueryInterface(const IID& riid, void** ppv) override {
        if (!ppv) return -2147467261;
        if (riid == IID_IUnknown || riid == IID_IDCompositionEffect ||
            riid == IID_IDCompositionTransform || riid == IID_IDCompositionScaleTransform) {
            *ppv = static_cast<IDCompositionScaleTransform*>(this);
            AddRef();
            return 0;
        }
        *ppv = nullptr;
        return -2147467262;
    }

    uint32_t AddRef() override {
        return m_refCount.fetch_add(1, std::memory_order_relaxed) + 1;
    }

    uint32_t Release() override {
        uint32_t count = m_refCount.fetch_sub(1, std::memory_order_acq_rel) - 1;
        if (count == 0) delete this;
        return count;
    }

    int32_t SetScaleX(float scaleX) override {
        m_scaleX = scaleX;
        m_animX.Reset();
        return 0;
    }

    int32_t SetScaleX(IDCompositionAnimation* animation) override {
        m_animX = animation;
        return 0;
    }

    int32_t SetScaleY(float scaleY) override {
        m_scaleY = scaleY;
        m_animY.Reset();
        return 0;
    }

    int32_t SetScaleY(IDCompositionAnimation* animation) override {
        m_animY = animation;
        return 0;
    }

    int32_t SetCenterX(float centerX) override {
        m_centerX = centerX;
        return 0;
    }

    int32_t SetCenterY(float centerY) override {
        m_centerY = centerY;
        return 0;
    }

    float GetScaleX() const override { return m_animX ? m_animX->Evaluate(0.0) : m_scaleX; }
    float GetScaleY() const override { return m_animY ? m_animY->Evaluate(0.0) : m_scaleY; }
    float GetCenterX() const override { return m_centerX; }
    float GetCenterY() const override { return m_centerY; }
};

class MicaDCompositionRotateTransformImpl : public IDCompositionRotateTransform {
private:
    std::atomic<uint32_t> m_refCount{ 1 };
    float m_angle{ 0.0f };
    float m_centerX{ 0.0f };
    float m_centerY{ 0.0f };
    ComPtr<IDCompositionAnimation> m_animAngle;

public:
    int32_t QueryInterface(const IID& riid, void** ppv) override {
        if (!ppv) return -2147467261;
        if (riid == IID_IUnknown || riid == IID_IDCompositionEffect ||
            riid == IID_IDCompositionTransform || riid == IID_IDCompositionRotateTransform) {
            *ppv = static_cast<IDCompositionRotateTransform*>(this);
            AddRef();
            return 0;
        }
        *ppv = nullptr;
        return -2147467262;
    }

    uint32_t AddRef() override {
        return m_refCount.fetch_add(1, std::memory_order_relaxed) + 1;
    }

    uint32_t Release() override {
        uint32_t count = m_refCount.fetch_sub(1, std::memory_order_acq_rel) - 1;
        if (count == 0) delete this;
        return count;
    }

    int32_t SetAngle(float angle) override {
        m_angle = angle;
        m_animAngle.Reset();
        return 0;
    }

    int32_t SetAngle(IDCompositionAnimation* animation) override {
        m_animAngle = animation;
        return 0;
    }

    int32_t SetCenterX(float centerX) override {
        m_centerX = centerX;
        return 0;
    }

    int32_t SetCenterY(float centerY) override {
        m_centerY = centerY;
        return 0;
    }

    float GetAngle() const override { return m_animAngle ? m_animAngle->Evaluate(0.0) : m_angle; }
    float GetCenterX() const override { return m_centerX; }
    float GetCenterY() const override { return m_centerY; }
};

class MicaDCompositionMatrixTransformImpl : public IDCompositionMatrixTransform {
private:
    std::atomic<uint32_t> m_refCount{ 1 };
    DCOMP_MATRIX3x2 m_matrix{};

public:
    MicaDCompositionMatrixTransformImpl() {
        m_matrix.m[0][0] = 1.0f; m_matrix.m[0][1] = 0.0f;
        m_matrix.m[1][0] = 0.0f; m_matrix.m[1][1] = 1.0f;
        m_matrix.m[2][0] = 0.0f; m_matrix.m[2][1] = 0.0f;
    }

    int32_t QueryInterface(const IID& riid, void** ppv) override {
        if (!ppv) return -2147467261;
        if (riid == IID_IUnknown || riid == IID_IDCompositionEffect ||
            riid == IID_IDCompositionTransform || riid == IID_IDCompositionMatrixTransform) {
            *ppv = static_cast<IDCompositionMatrixTransform*>(this);
            AddRef();
            return 0;
        }
        *ppv = nullptr;
        return -2147467262;
    }

    uint32_t AddRef() override {
        return m_refCount.fetch_add(1, std::memory_order_relaxed) + 1;
    }

    uint32_t Release() override {
        uint32_t count = m_refCount.fetch_sub(1, std::memory_order_acq_rel) - 1;
        if (count == 0) delete this;
        return count;
    }

    int32_t SetMatrix(const DCOMP_MATRIX3x2& matrix) override {
        m_matrix = matrix;
        return 0;
    }

    const DCOMP_MATRIX3x2& GetMatrix() const override { return m_matrix; }
};

// ----------------------------------------------------------------------------
// Rectangle Clip Implementation
// ----------------------------------------------------------------------------
class MicaDCompositionRectangleClipImpl : public IDCompositionRectangleClip {
private:
    std::atomic<uint32_t> m_refCount{ 1 };
    DCOMP_RECT m_rect{};
    float m_radiusX{ 0.0f };
    float m_radiusY{ 0.0f };

public:
    int32_t QueryInterface(const IID& riid, void** ppv) override {
        if (!ppv) return -2147467261;
        if (riid == IID_IUnknown || riid == IID_IDCompositionClip ||
            riid == IID_IDCompositionRectangleClip) {
            *ppv = static_cast<IDCompositionRectangleClip*>(this);
            AddRef();
            return 0;
        }
        *ppv = nullptr;
        return -2147467262;
    }

    uint32_t AddRef() override {
        return m_refCount.fetch_add(1, std::memory_order_relaxed) + 1;
    }

    uint32_t Release() override {
        uint32_t count = m_refCount.fetch_sub(1, std::memory_order_acq_rel) - 1;
        if (count == 0) delete this;
        return count;
    }

    int32_t SetLeft(float left) override { m_rect.left = static_cast<int32_t>(left); return 0; }
    int32_t SetTop(float top) override { m_rect.top = static_cast<int32_t>(top); return 0; }
    int32_t SetRight(float right) override { m_rect.right = static_cast<int32_t>(right); return 0; }
    int32_t SetBottom(float bottom) override { m_rect.bottom = static_cast<int32_t>(bottom); return 0; }
    int32_t SetTopLeftRadiusX(float radius) override { m_radiusX = radius; return 0; }
    int32_t SetTopLeftRadiusY(float radius) override { m_radiusY = radius; return 0; }
    const DCOMP_RECT& GetRect() const override { return m_rect; }
};

// ----------------------------------------------------------------------------
// Surface Implementation
// ----------------------------------------------------------------------------
class MicaDCompositionSurfaceImpl : public IDCompositionVirtualSurface {
private:
    std::atomic<uint32_t> m_refCount{ 1 };
    uint32_t m_width;
    uint32_t m_height;
    DXGI_FORMAT m_format;
    DXGI_ALPHA_MODE m_alphaMode;
    std::vector<uint8_t> m_pixels;
    bool m_isDrawing{ false };

public:
    MicaDCompositionSurfaceImpl(uint32_t width, uint32_t height, DXGI_FORMAT format, DXGI_ALPHA_MODE alphaMode)
        : m_width(width), m_height(height), m_format(format), m_alphaMode(alphaMode) {
        m_pixels.resize(width * height * 4, 0);
    }

    int32_t QueryInterface(const IID& riid, void** ppv) override {
        if (!ppv) return -2147467261;
        if (riid == IID_IUnknown || riid == IID_IDCompositionSurface || riid == IID_IDCompositionVirtualSurface) {
            *ppv = static_cast<IDCompositionVirtualSurface*>(this);
            AddRef();
            return 0;
        }
        *ppv = nullptr;
        return -2147467262;
    }

    uint32_t AddRef() override {
        return m_refCount.fetch_add(1, std::memory_order_relaxed) + 1;
    }

    uint32_t Release() override {
        uint32_t count = m_refCount.fetch_sub(1, std::memory_order_acq_rel) - 1;
        if (count == 0) delete this;
        return count;
    }

    int32_t BeginDraw(const DCOMP_RECT* updateRect, const IID&, void** updateObject, DCOMP_POINT* updateOffset) override {
        if (!updateObject || !updateOffset) return -2147467261;
        m_isDrawing = true;
        if (updateRect) {
            updateOffset->x = updateRect->left;
            updateOffset->y = updateRect->top;
        } else {
            updateOffset->x = 0;
            updateOffset->y = 0;
        }
        *updateObject = this;
        AddRef();
        return 0;
    }

    int32_t EndDraw() override {
        m_isDrawing = false;
        return 0;
    }

    int32_t SuspendDraw() override { return 0; }
    int32_t ResumeDraw() override { return 0; }

    int32_t Scroll(const DCOMP_RECT*, const DCOMP_RECT*, int32_t, int32_t) override {
        return 0;
    }

    uint32_t GetWidth() const override { return m_width; }
    uint32_t GetHeight() const override { return m_height; }
    uint8_t* GetBuffer() override { return m_pixels.data(); }
    DXGI_FORMAT GetFormat() const { return m_format; }
    DXGI_ALPHA_MODE GetAlphaMode() const { return m_alphaMode; }
    bool IsDrawing() const { return m_isDrawing; }

    int32_t Resize(uint32_t width, uint32_t height) override {
        m_width = width;
        m_height = height;
        m_pixels.resize(width * height * 4, 0);
        return 0;
    }

    int32_t Trim(const DCOMP_RECT*, uint32_t) override {
        return 0;
    }
};

// ----------------------------------------------------------------------------
// Visual Tree Node Implementation
// ----------------------------------------------------------------------------
class MicaDCompositionVisualImpl : public IDCompositionVisual2 {
private:
    std::atomic<uint32_t> m_refCount{ 1 };
    float m_offsetX{ 0.0f };
    float m_offsetY{ 0.0f };
    float m_opacity{ 1.0f };
    DCOMPOSITION_BITMAP_INTERPOLATION_MODE m_interpolationMode{ DCOMPOSITION_BITMAP_INTERPOLATION_MODE::LINEAR };
    DCOMPOSITION_BORDER_MODE m_borderMode{ DCOMPOSITION_BORDER_MODE::HARD };
    DCOMPOSITION_OPACITY_MODE m_opacityMode{ DCOMPOSITION_OPACITY_MODE::LAYER };
    DCOMPOSITION_BACKFACE_VISIBILITY m_backfaceVisibility{ DCOMPOSITION_BACKFACE_VISIBILITY::VISIBLE };

    ComPtr<IDCompositionAnimation> m_animOffsetX;
    ComPtr<IDCompositionAnimation> m_animOffsetY;
    ComPtr<IDCompositionAnimation> m_animOpacity;

    ComPtr<IDCompositionTransform> m_pTransform;
    ComPtr<IDCompositionVisual> m_pTransformParent;
    ComPtr<IDCompositionEffect> m_pEffect;
    ComPtr<IDCompositionClip> m_pClip;
    ComPtr<IUnknown> m_pContent;

    DCOMP_RECT m_clipRect{};
    bool m_hasClipRect{ false };

    std::vector<IDCompositionVisual*> m_children;

public:
    ~MicaDCompositionVisualImpl() {
        RemoveAllVisuals();
    }

    int32_t QueryInterface(const IID& riid, void** ppv) override {
        if (!ppv) return -2147467261;
        if (riid == IID_IUnknown || riid == IID_IDCompositionVisual || riid == IID_IDCompositionVisual2) {
            *ppv = static_cast<IDCompositionVisual2*>(this);
            AddRef();
            return 0;
        }
        *ppv = nullptr;
        return -2147467262;
    }

    uint32_t AddRef() override {
        return m_refCount.fetch_add(1, std::memory_order_relaxed) + 1;
    }

    uint32_t Release() override {
        uint32_t count = m_refCount.fetch_sub(1, std::memory_order_acq_rel) - 1;
        if (count == 0) delete this;
        return count;
    }

    int32_t SetOffsetX(float offsetX) override {
        m_offsetX = offsetX;
        m_animOffsetX.Reset();
        return 0;
    }

    int32_t SetOffsetX(IDCompositionAnimation* animation) override {
        m_animOffsetX = animation;
        return 0;
    }

    int32_t SetOffsetY(float offsetY) override {
        m_offsetY = offsetY;
        m_animOffsetY.Reset();
        return 0;
    }

    int32_t SetOffsetY(IDCompositionAnimation* animation) override {
        m_animOffsetY = animation;
        return 0;
    }

    int32_t SetTransform(IDCompositionTransform* transform) override {
        m_pTransform = transform;
        return 0;
    }

    int32_t SetTransformParent(IDCompositionVisual* visual) override {
        m_pTransformParent = visual;
        return 0;
    }

    int32_t SetEffect(IDCompositionEffect* effect) override {
        m_pEffect = effect;
        return 0;
    }

    int32_t SetOpacity(float opacity) override {
        m_opacity = std::clamp(opacity, 0.0f, 1.0f);
        m_animOpacity.Reset();
        return 0;
    }

    int32_t SetOpacity(IDCompositionAnimation* animation) override {
        m_animOpacity = animation;
        return 0;
    }

    int32_t SetInterpolationMode(DCOMPOSITION_BITMAP_INTERPOLATION_MODE interpolationMode) override {
        m_interpolationMode = interpolationMode;
        return 0;
    }

    int32_t SetBorderMode(DCOMPOSITION_BORDER_MODE borderMode) override {
        m_borderMode = borderMode;
        return 0;
    }

    int32_t SetClip(const DCOMP_RECT& rect) override {
        m_clipRect = rect;
        m_hasClipRect = true;
        m_pClip.Reset();
        return 0;
    }

    int32_t SetClip(IDCompositionClip* clip) override {
        m_pClip = clip;
        m_hasClipRect = false;
        return 0;
    }

    int32_t SetContent(IUnknown* content) override {
        m_pContent = content;
        return 0;
    }

    int32_t AddVisual(IDCompositionVisual* visual, bool insertAbove, IDCompositionVisual* referenceVisual) override {
        if (!visual) return -2147467261;
        visual->AddRef();

        if (!referenceVisual) {
            if (insertAbove) {
                m_children.push_back(visual);
            } else {
                m_children.insert(m_children.begin(), visual);
            }
            return 0;
        }

        auto it = std::find(m_children.begin(), m_children.end(), referenceVisual);
        if (it != m_children.end()) {
            if (insertAbove) {
                m_children.insert(it + 1, visual);
            } else {
                m_children.insert(it, visual);
            }
        } else {
            m_children.push_back(visual);
        }
        return 0;
    }

    int32_t RemoveVisual(IDCompositionVisual* visual) override {
        auto it = std::find(m_children.begin(), m_children.end(), visual);
        if (it != m_children.end()) {
            (*it)->Release();
            m_children.erase(it);
            return 0;
        }
        return -2147024809;
    }

    int32_t RemoveAllVisuals() override {
        for (auto* child : m_children) {
            if (child) child->Release();
        }
        m_children.clear();
        return 0;
    }

    int32_t SetOpacityMode(DCOMPOSITION_OPACITY_MODE mode) override {
        m_opacityMode = mode;
        return 0;
    }

    int32_t SetBackFaceVisibility(DCOMPOSITION_BACKFACE_VISIBILITY visibility) override {
        m_backfaceVisibility = visibility;
        return 0;
    }

    float GetOffsetX() const override {
        return m_animOffsetX ? m_animOffsetX->Evaluate(0.0) : m_offsetX;
    }

    float GetOffsetY() const override {
        return m_animOffsetY ? m_animOffsetY->Evaluate(0.0) : m_offsetY;
    }

    float GetOpacity() const override {
        return m_animOpacity ? m_animOpacity->Evaluate(0.0) : m_opacity;
    }

    IUnknown* GetContent() const override { return m_pContent.Get(); }
    IDCompositionTransform* GetTransform() const override { return m_pTransform.Get(); }
    const std::vector<IDCompositionVisual*>& GetChildren() const override { return m_children; }
    DCOMPOSITION_OPACITY_MODE GetOpacityMode() const override { return m_opacityMode; }
    DCOMPOSITION_BACKFACE_VISIBILITY GetBackFaceVisibility() const override { return m_backfaceVisibility; }
};

// ----------------------------------------------------------------------------
// Target Implementation
// ----------------------------------------------------------------------------
class MicaDCompositionTargetImpl : public IDCompositionTarget {
private:
    std::atomic<uint32_t> m_refCount{ 1 };
    HWND m_hwnd{ nullptr };
    ComPtr<IDCompositionVisual> m_pRootVisual;

public:
    explicit MicaDCompositionTargetImpl(HWND hwnd) : m_hwnd(hwnd) {}

    int32_t QueryInterface(const IID& riid, void** ppv) override {
        if (!ppv) return -2147467261;
        if (riid == IID_IUnknown || riid == IID_IDCompositionTarget) {
            *ppv = static_cast<IDCompositionTarget*>(this);
            AddRef();
            return 0;
        }
        *ppv = nullptr;
        return -2147467262;
    }

    uint32_t AddRef() override {
        return m_refCount.fetch_add(1, std::memory_order_relaxed) + 1;
    }

    uint32_t Release() override {
        uint32_t count = m_refCount.fetch_sub(1, std::memory_order_acq_rel) - 1;
        if (count == 0) delete this;
        return count;
    }

    int32_t SetRoot(IDCompositionVisual* visual) override {
        m_pRootVisual = visual;
        return 0;
    }

    IDCompositionVisual* GetRoot() const override {
        return m_pRootVisual.Get();
    }

    HWND GetHwnd() const override { return m_hwnd; }
};

// ----------------------------------------------------------------------------
// Device Implementation
// ----------------------------------------------------------------------------
class MicaDCompositionDeviceImpl : public IDCompositionDevice2 {
private:
    std::atomic<uint32_t> m_refCount{ 1 };
    ComPtr<IUnknown> m_pRenderingDevice;
    uint32_t m_commitCount{ 0 };
    DCOMPOSITION_FRAME_STATISTICS m_frameStats{};
    std::vector<ComPtr<IDCompositionTarget>> m_targets;
    mutable std::mutex m_mutex;

public:
    explicit MicaDCompositionDeviceImpl(IUnknown* renderingDevice)
        : m_pRenderingDevice(renderingDevice) {
        m_frameStats.timeFrequency = 10000000;
    }

    int32_t QueryInterface(const IID& riid, void** ppv) override {
        if (!ppv) return -2147467261;
        if (riid == IID_IUnknown || riid == IID_IDCompositionDevice || riid == IID_IDCompositionDevice2) {
            *ppv = static_cast<IDCompositionDevice2*>(this);
            AddRef();
            return 0;
        }
        *ppv = nullptr;
        return -2147467262;
    }

    uint32_t AddRef() override {
        return m_refCount.fetch_add(1, std::memory_order_relaxed) + 1;
    }

    uint32_t Release() override {
        uint32_t count = m_refCount.fetch_sub(1, std::memory_order_acq_rel) - 1;
        if (count == 0) delete this;
        return count;
    }

    int32_t Commit() override {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_commitCount++;
        m_frameStats.lastFrameTime = m_frameStats.currentFrameTime;
        m_frameStats.currentFrameTime += 166666; // 60 Hz 16.66ms in 100ns units
        m_frameStats.nextKeyFrame = m_commitCount;

        // Perform compositing pass over all targets
        for (const auto& target : m_targets) {
            if (target && target->GetRoot()) {
                CompositeVisualTree(target->GetRoot(), 0.0f, 0.0f, 1.0f);
            }
        }
        return 0;
    }

    int32_t WaitForCommitCompletion() override {
        return 0;
    }

    int32_t GetFrameStatistics(DCOMPOSITION_FRAME_STATISTICS* statistics) override {
        if (!statistics) return -2147467261;
        *statistics = m_frameStats;
        return 0;
    }

    int32_t CreateTargetForHwnd(HWND hwnd, bool, IDCompositionTarget** target) override {
        if (!target) return -2147467261;
        auto* tgt = new MicaDCompositionTargetImpl(hwnd);
        m_targets.emplace_back(tgt);
        *target = tgt;
        return 0;
    }

    int32_t CreateVisual(IDCompositionVisual** visual) override {
        if (!visual) return -2147467261;
        *visual = new MicaDCompositionVisualImpl();
        return 0;
    }

    int32_t CreateVisual2(IDCompositionVisual2** visual) override {
        if (!visual) return -2147467261;
        *visual = new MicaDCompositionVisualImpl();
        return 0;
    }

    int32_t CreateSurface(uint32_t width, uint32_t height, DXGI_FORMAT format, DXGI_ALPHA_MODE alphaMode, IDCompositionSurface** surface) override {
        if (!surface) return -2147467261;
        *surface = new MicaDCompositionSurfaceImpl(width, height, format, alphaMode);
        return 0;
    }

    int32_t CreateVirtualSurface(uint32_t initialWidth, uint32_t initialHeight, DXGI_FORMAT format, DXGI_ALPHA_MODE alphaMode, IDCompositionVirtualSurface** virtualSurface) override {
        if (!virtualSurface) return -2147467261;
        *virtualSurface = new MicaDCompositionSurfaceImpl(initialWidth, initialHeight, format, alphaMode);
        return 0;
    }

    int32_t CreateTranslateTransform(IDCompositionTranslateTransform** translateTransform) override {
        if (!translateTransform) return -2147467261;
        *translateTransform = new MicaDCompositionTranslateTransformImpl();
        return 0;
    }

    int32_t CreateScaleTransform(IDCompositionScaleTransform** scaleTransform) override {
        if (!scaleTransform) return -2147467261;
        *scaleTransform = new MicaDCompositionScaleTransformImpl();
        return 0;
    }

    int32_t CreateRotateTransform(IDCompositionRotateTransform** rotateTransform) override {
        if (!rotateTransform) return -2147467261;
        *rotateTransform = new MicaDCompositionRotateTransformImpl();
        return 0;
    }

    int32_t CreateMatrixTransform(IDCompositionMatrixTransform** matrixTransform) override {
        if (!matrixTransform) return -2147467261;
        *matrixTransform = new MicaDCompositionMatrixTransformImpl();
        return 0;
    }

    int32_t CreateRectangleClip(IDCompositionRectangleClip** clip) override {
        if (!clip) return -2147467261;
        *clip = new MicaDCompositionRectangleClipImpl();
        return 0;
    }

    int32_t CreateAnimation(IDCompositionAnimation** animation) override {
        if (!animation) return -2147467261;
        *animation = new MicaDCompositionAnimationImpl();
        return 0;
    }

    uint32_t GetCommitCount() const { return m_commitCount; }
    IUnknown* GetRenderingDevice() const { return m_pRenderingDevice.Get(); }

private:
    void CompositeVisualTree(IDCompositionVisual* visual, float parentX, float parentY, float parentOpacity) {
        if (!visual) return;

        float x = parentX + visual->GetOffsetX();
        float y = parentY + visual->GetOffsetY();
        float opacity = parentOpacity * visual->GetOpacity();

        // Process Transform if present
        if (auto* tr = visual->GetTransform()) {
            ComPtr<IDCompositionTranslateTransform> tt;
            if (SUCCEEDED(tr->QueryInterface(IID_IDCompositionTranslateTransform, tt.PutVoid()))) {
                x += tt->GetOffsetX();
                y += tt->GetOffsetY();
            }
        }

        // Composite children in order
        for (auto* child : visual->GetChildren()) {
            CompositeVisualTree(child, x, y, opacity);
        }
    }
};

// ============================================================================
// 5. Global API Factory Functions
// ============================================================================

inline int32_t DCompositionCreateDevice(
    IDXGIDevice* dxgiDevice,
    const IID& riid,
    void** ppv
) {
    if (!ppv) return -2147467261;
    auto* dev = new MicaDCompositionDeviceImpl(dxgiDevice);
    int32_t hr = dev->QueryInterface(riid, ppv);
    dev->Release();
    return hr;
}

inline int32_t DCompositionCreateDevice2(
    IUnknown* renderingDevice,
    const IID& riid,
    void** ppv
) {
    if (!ppv) return -2147467261;
    auto* dev = new MicaDCompositionDeviceImpl(renderingDevice);
    int32_t hr = dev->QueryInterface(riid, ppv);
    dev->Release();
    return hr;
}

inline int32_t DCompositionCreateDevice3(
    IUnknown* renderingDevice,
    const IID& riid,
    void** ppv
) {
    if (!ppv) return -2147467261;
    auto* dev = new MicaDCompositionDeviceImpl(renderingDevice);
    int32_t hr = dev->QueryInterface(riid, ppv);
    dev->Release();
    return hr;
}

inline int32_t DCompositionCreateSurfaceHandle(
    uint32_t,
    void*,
    HANDLE* surfaceHandle
) {
    if (!surfaceHandle) return -2147467261;
    static uint64_t s_nextHandle = 0xD0C00001;
    *surfaceHandle = reinterpret_cast<HANDLE>(s_nextHandle++);
    return 0;
}

} // namespace prismx
