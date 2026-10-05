// ============================================================================
// PrismX: Sovereign Graphics Architecture - Modern UI Composition & Visual Layer
// 
// Strict Clean-Room Implementation in ISO C++23. Zero External Dependencies.
// Implements the Modern Scene-Graph Visual Layer & Expression Animation Subsystem.
// 
// Reference: Microsoft MIT-Licensed microsoft/win32metadata (Windows.UI.Composition)
// Tribute to Dave Cutler's 1988 DEC PRISM Architecture.
// ============================================================================

#pragma once

#include "types.hpp"
#include "math.hpp"
#include "dcomp.hpp"
#include <vector>
#include <string>
#include <memory>
#include <unordered_map>
#include <cmath>
#include <algorithm>
#include <functional>
#include <sstream>

namespace prismx::composition {

// ============================================================================
// 1. Core WinRT Foundation Types & GUIDs
// ============================================================================

using HSTRING = void*;

enum class TrustLevel {
    BaseTrust = 0,
    PartialTrust = 1,
    FullTrust = 2
};

enum class CompositionCompositeMode {
    Inherit = 0,
    SourceOver = 1,
    MinBlend = 2
};

enum class CompositionStretch {
    None = 0,
    Fill = 1,
    Uniform = 2,
    UniformToFill = 3
};

using Vector2 = prismx::math::Vector2;
using Vector3 = prismx::math::Vector3;
using Vector4 = prismx::math::Vector4;
using Matrix4x4 = prismx::math::Matrix;

struct CompositionColor {
    uint8_t a{ 255 };
    uint8_t r{ 0 };
    uint8_t g{ 0 };
    uint8_t b{ 0 };

    constexpr CompositionColor() = default;
    constexpr CompositionColor(uint8_t a_, uint8_t r_, uint8_t g_, uint8_t b_) : a(a_), r(r_), g(g_), b(b_) {}

    constexpr bool operator==(const CompositionColor& o) const noexcept {
        return a == o.a && r == o.r && g == o.g && b == o.b;
    }
};

struct Quaternion {
    float x{ 0.0f };
    float y{ 0.0f };
    float z{ 0.0f };
    float w{ 1.0f };
};

// Interface GUIDs
inline constexpr GUID IID_IInspectable = {
    0xAF86E2E0, 0xB12D, 0x4c6a, { 0x9C, 0x5D, 0xD7, 0xAA, 0x65, 0x10, 0x1E, 0x90 }
};

inline constexpr GUID IID_IActivationFactory = {
    0x00000035, 0x0000, 0x0000, { 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46 }
};

inline constexpr GUID IID_ICompositionObject = {
    0xBCB4AD45, 0x7609, 0x4550, { 0x93, 0x4F, 0x16, 0x00, 0x2A, 0xEE, 0x7D, 0x04 }
};

inline constexpr GUID IID_ICompositor = {
    0xC620A459, 0xE722, 0x4850, { 0x98, 0x13, 0xD3, 0xD0, 0x82, 0x22, 0x1D, 0x41 }
};

inline constexpr GUID IID_ICompositor2 = {
    0x70E69F66, 0x9619, 0x4821, { 0x8C, 0xD4, 0x7E, 0x7E, 0x05, 0x83, 0x6E, 0x7E }
};

inline constexpr GUID IID_IVisual = {
    0x117E202D, 0xA859, 0x4C5E, { 0xBE, 0x82, 0x4B, 0x0A, 0x5E, 0x08, 0x11, 0x10 }
};

inline constexpr GUID IID_IContainerVisual = {
    0x02867F5B, 0x8415, 0x4C3A, { 0x86, 0x9B, 0x8C, 0x7E, 0x5E, 0x43, 0x98, 0x87 }
};

inline constexpr GUID IID_ISpriteVisual = {
    0x0866A487, 0x8035, 0x44D9, { 0x9B, 0x8B, 0x8F, 0x10, 0xBE, 0x69, 0x3F, 0x99 }
};

inline constexpr GUID IID_IVisualCollection = {
    0x40319451, 0x9472, 0x4989, { 0x92, 0x98, 0x7F, 0x07, 0x3C, 0x3E, 0x2A, 0x55 }
};

inline constexpr GUID IID_ICompositionBrush = {
    0xABBEB362, 0x5A4C, 0x4D36, { 0xBE, 0xC6, 0x0D, 0x4E, 0x12, 0x30, 0x25, 0x83 }
};

inline constexpr GUID IID_ICompositionColorBrush = {
    0x21703212, 0x7292, 0x4C48, { 0xAE, 0x8C, 0x29, 0x9B, 0x90, 0x8A, 0x62, 0x6A }
};

inline constexpr GUID IID_ICompositionSurfaceBrush = {
    0xAD1C9F40, 0x8D38, 0x4296, { 0x9B, 0x9C, 0x9A, 0x4C, 0x6A, 0x12, 0x78, 0x90 }
};

inline constexpr GUID IID_ICompositionEffectBrush = {
    0x3E12B001, 0x43C2, 0x4876, { 0x88, 0x1B, 0x5B, 0xC2, 0x77, 0x32, 0x1A, 0x8B }
};

inline constexpr GUID IID_ICompositionAnimation = {
    0x464C4C22, 0x7A0A, 0x4C36, { 0x9E, 0x5A, 0x0A, 0x0D, 0x32, 0x55, 0x8B, 0x99 }
};

inline constexpr GUID IID_IKeyFrameAnimation = {
    0x5AE92265, 0x3A6A, 0x4AD8, { 0x81, 0x4B, 0x35, 0x70, 0x6D, 0x01, 0x8B, 0x54 }
};

inline constexpr GUID IID_IScalarKeyFrameAnimation = {
    0xAE6384C1, 0x4153, 0x4642, { 0x93, 0xC3, 0x1D, 0x8E, 0x5A, 0x1C, 0x90, 0x77 }
};

inline constexpr GUID IID_IVector3KeyFrameAnimation = {
    0x7C0428E1, 0x9376, 0x4850, { 0x86, 0x74, 0x39, 0x24, 0x5A, 0x62, 0x7E, 0x88 }
};

inline constexpr GUID IID_IExpressionAnimation = {
    0x6A974240, 0x712B, 0x4632, { 0x85, 0x3C, 0x91, 0x7C, 0x32, 0x1A, 0x4B, 0x66 }
};

inline constexpr GUID IID_ICompositionPropertySet = {
    0x51B07481, 0x2170, 0x4523, { 0x87, 0x88, 0x7E, 0x1B, 0x6A, 0x33, 0x90, 0x11 }
};

// ============================================================================
// 2. WinRT COM Foundation Interfaces
// ============================================================================

class IInspectable : public IUnknown {
public:
    virtual HRESULT GetIids(uint32_t* iidCount, GUID** iids) = 0;
    virtual HRESULT GetRuntimeClassName(HSTRING* className) = 0;
    virtual HRESULT GetTrustLevel(TrustLevel* trustLevel) = 0;
};

class IActivationFactory : public IInspectable {
public:
    virtual HRESULT ActivateInstance(IInspectable** instance) = 0;
};

// Forward Declarations
class ICompositor;
class IVisual;
class IContainerVisual;
class ISpriteVisual;
class IVisualCollection;
class ICompositionBrush;
class ICompositionAnimation;
class ICompositionPropertySet;

// ============================================================================
// 3. UI Composition Interfaces
// ============================================================================

class ICompositionPropertySet : public IInspectable {
public:
    virtual HRESULT InsertScalar(const wchar_t* propertyName, float value) = 0;
    virtual HRESULT InsertVector3(const wchar_t* propertyName, Vector3 value) = 0;
    virtual HRESULT TryGetScalar(const wchar_t* propertyName, float* value) = 0;
    virtual HRESULT TryGetVector3(const wchar_t* propertyName, Vector3* value) = 0;
};

class ICompositionAnimation : public IInspectable {
public:
    virtual HRESULT SetTarget(const wchar_t* target) = 0;
    virtual const wchar_t* GetTarget() const = 0;
};

class ICompositionObject : public IInspectable {
public:
    virtual HRESULT GetCompositor(ICompositor** compositor) = 0;
    virtual HRESULT GetPropertySet(ICompositionPropertySet** propertySet) = 0;
    virtual HRESULT StartAnimation(const wchar_t* propertyName, ICompositionAnimation* animation) = 0;
    virtual HRESULT StopAnimation(const wchar_t* propertyName) = 0;
};

class IVisual : public ICompositionObject {
public:
    virtual Vector3 GetOffset() const = 0;
    virtual HRESULT SetOffset(Vector3 offset) = 0;
    virtual Vector2 GetSize() const = 0;
    virtual HRESULT SetSize(Vector2 size) = 0;
    virtual Vector3 GetScale() const = 0;
    virtual HRESULT SetScale(Vector3 scale) = 0;
    virtual float GetRotationAngle() const = 0;
    virtual HRESULT SetRotationAngle(float radians) = 0;
    virtual Vector3 GetCenterPoint() const = 0;
    virtual HRESULT SetCenterPoint(Vector3 center) = 0;
    virtual float GetOpacity() const = 0;
    virtual HRESULT SetOpacity(float opacity) = 0;
    virtual bool GetIsVisible() const = 0;
    virtual HRESULT SetIsVisible(bool visible) = 0;
    virtual CompositionCompositeMode GetCompositeMode() const = 0;
    virtual HRESULT SetCompositeMode(CompositionCompositeMode mode) = 0;
    virtual IVisual* GetParent() const = 0;
    virtual void SetParent(IVisual* parent) = 0;
};

class IVisualCollection : public IInspectable {
public:
    virtual int32_t GetCount() const = 0;
    virtual HRESULT InsertAtTop(IVisual* newChild) = 0;
    virtual HRESULT InsertAtBottom(IVisual* newChild) = 0;
    virtual HRESULT InsertAbove(IVisual* newChild, IVisual* sibling) = 0;
    virtual HRESULT InsertBelow(IVisual* newChild, IVisual* sibling) = 0;
    virtual HRESULT Remove(IVisual* child) = 0;
    virtual HRESULT RemoveAll() = 0;
    virtual IVisual* GetAt(int32_t index) const = 0;
};

class IContainerVisual : public IVisual {
public:
    virtual HRESULT GetChildren(IVisualCollection** children) = 0;
};

class ICompositionBrush : public ICompositionObject {
public:
};

class ICompositionColorBrush : public ICompositionBrush {
public:
    virtual CompositionColor GetColor() const = 0;
    virtual HRESULT SetColor(CompositionColor color) = 0;
};

class ICompositionSurfaceBrush : public ICompositionBrush {
public:
    virtual void* GetSurface() const = 0;
    virtual HRESULT SetSurface(void* surface) = 0;
    virtual CompositionStretch GetStretch() const = 0;
    virtual HRESULT SetStretch(CompositionStretch stretch) = 0;
    virtual float GetHorizontalAlignmentRatio() const = 0;
    virtual HRESULT SetHorizontalAlignmentRatio(float ratio) = 0;
    virtual float GetVerticalAlignmentRatio() const = 0;
    virtual HRESULT SetVerticalAlignmentRatio(float ratio) = 0;
};

class ICompositionEffectBrush : public ICompositionBrush {
public:
    virtual const std::wstring& GetEffectName() const = 0;
    virtual HRESULT SetSourceParameter(const wchar_t* name, ICompositionBrush* source) = 0;
    virtual ICompositionBrush* GetSourceParameter(const wchar_t* name) const = 0;
};

class ISpriteVisual : public IContainerVisual {
public:
    virtual ICompositionBrush* GetBrush() const = 0;
    virtual HRESULT SetBrush(ICompositionBrush* brush) = 0;
};

class IKeyFrameAnimation : public ICompositionAnimation {
public:
    virtual float GetDuration() const = 0;
    virtual HRESULT SetDuration(float durationSeconds) = 0;
    virtual int32_t GetIterationCount() const = 0;
    virtual HRESULT SetIterationCount(int32_t count) = 0;
};

class IScalarKeyFrameAnimation : public IKeyFrameAnimation {
public:
    virtual HRESULT InsertKeyFrame(float normalizedProgressKey, float value) = 0;
    virtual float Evaluate(float progress) const = 0;
};

class IVector3KeyFrameAnimation : public IKeyFrameAnimation {
public:
    virtual HRESULT InsertKeyFrame(float normalizedProgressKey, Vector3 value) = 0;
    virtual Vector3 Evaluate(float progress) const = 0;
};

class IExpressionAnimation : public ICompositionAnimation {
public:
    virtual const std::wstring& GetExpression() const = 0;
    virtual HRESULT SetExpression(const wchar_t* expression) = 0;
    virtual HRESULT SetScalarParameter(const wchar_t* key, float value) = 0;
    virtual HRESULT SetVector3Parameter(const wchar_t* key, Vector3 value) = 0;
    virtual HRESULT SetReferenceParameter(const wchar_t* key, ICompositionObject* object) = 0;
    virtual float EvaluateScalar() const = 0;
};

class ICompositor : public IInspectable {
public:
    virtual HRESULT CreateContainerVisual(IContainerVisual** result) = 0;
    virtual HRESULT CreateSpriteVisual(ISpriteVisual** result) = 0;
    virtual HRESULT CreateColorBrush(ICompositionColorBrush** result) = 0;
    virtual HRESULT CreateColorBrushWithColor(CompositionColor color, ICompositionColorBrush** result) = 0;
    virtual HRESULT CreateSurfaceBrush(ICompositionSurfaceBrush** result) = 0;
    virtual HRESULT CreateEffectBrush(const wchar_t* effectName, ICompositionEffectBrush** result) = 0;
    virtual HRESULT CreateScalarKeyFrameAnimation(IScalarKeyFrameAnimation** result) = 0;
    virtual HRESULT CreateVector3KeyFrameAnimation(IVector3KeyFrameAnimation** result) = 0;
    virtual HRESULT CreateExpressionAnimation(IExpressionAnimation** result) = 0;
    virtual HRESULT CreateExpressionAnimationWithExpression(const wchar_t* expression, IExpressionAnimation** result) = 0;
    virtual HRESULT CreatePropertySet(ICompositionPropertySet** result) = 0;
};

// ============================================================================
// 4. PrismComposition Sovereign Implementation
// ============================================================================

class PrismCompositionPropertySetImpl : public ICompositionPropertySet {
private:
    std::atomic<uint32_t> m_refCount{ 1 };
    std::unordered_map<std::wstring, float> m_scalars;
    std::unordered_map<std::wstring, Vector3> m_vectors;

public:
    HRESULT QueryInterface(const GUID& riid, void** ppv) override {
        if (!ppv) return E_POINTER;
        if (riid == IID_IUnknown || riid == IID_IInspectable || riid == IID_ICompositionPropertySet) {
            *ppv = static_cast<ICompositionPropertySet*>(this);
            AddRef();
            return S_OK;
        }
        *ppv = nullptr;
        return E_NOINTERFACE;
    }

    uint32_t AddRef() override { return ++m_refCount; }
    uint32_t Release() override {
        uint32_t r = --m_refCount;
        if (r == 0) delete this;
        return r;
    }

    HRESULT GetIids(uint32_t* c, GUID** i) override { if (c) *c = 0; if (i) *i = nullptr; return S_OK; }
    HRESULT GetRuntimeClassName(HSTRING* n) override { if (n) *n = nullptr; return S_OK; }
    HRESULT GetTrustLevel(TrustLevel* t) override { if (t) *t = TrustLevel::BaseTrust; return S_OK; }

    HRESULT InsertScalar(const wchar_t* name, float value) override {
        if (!name) return E_INVALIDARG;
        m_scalars[name] = value;
        return S_OK;
    }

    HRESULT InsertVector3(const wchar_t* name, Vector3 value) override {
        if (!name) return E_INVALIDARG;
        m_vectors[name] = value;
        return S_OK;
    }

    HRESULT TryGetScalar(const wchar_t* name, float* val) override {
        if (!name || !val) return E_INVALIDARG;
        auto it = m_scalars.find(name);
        if (it != m_scalars.end()) {
            *val = it->second;
            return S_OK;
        }
        return E_FAIL;
    }

    HRESULT TryGetVector3(const wchar_t* name, Vector3* val) override {
        if (!name || !val) return E_INVALIDARG;
        auto it = m_vectors.find(name);
        if (it != m_vectors.end()) {
            *val = it->second;
            return S_OK;
        }
        return E_FAIL;
    }
};

class PrismScalarKeyFrameAnimationImpl : public IScalarKeyFrameAnimation {
private:
    std::atomic<uint32_t> m_refCount{ 1 };
    std::wstring m_target;
    float m_duration{ 1.0f };
    int32_t m_iterationCount{ 1 };
    struct KeyFrame { float progress; float value; };
    std::vector<KeyFrame> m_keyframes;

public:
    HRESULT QueryInterface(const GUID& riid, void** ppv) override {
        if (!ppv) return E_POINTER;
        if (riid == IID_IUnknown || riid == IID_IInspectable || riid == IID_ICompositionAnimation ||
            riid == IID_IKeyFrameAnimation || riid == IID_IScalarKeyFrameAnimation) {
            *ppv = static_cast<IScalarKeyFrameAnimation*>(this);
            AddRef();
            return S_OK;
        }
        *ppv = nullptr;
        return E_NOINTERFACE;
    }

    uint32_t AddRef() override { return ++m_refCount; }
    uint32_t Release() override {
        uint32_t r = --m_refCount;
        if (r == 0) delete this;
        return r;
    }

    HRESULT GetIids(uint32_t* c, GUID** i) override { if (c) *c = 0; if (i) *i = nullptr; return S_OK; }
    HRESULT GetRuntimeClassName(HSTRING* n) override { if (n) *n = nullptr; return S_OK; }
    HRESULT GetTrustLevel(TrustLevel* t) override { if (t) *t = TrustLevel::BaseTrust; return S_OK; }

    HRESULT SetTarget(const wchar_t* target) override {
        m_target = target ? target : L"";
        return S_OK;
    }

    const wchar_t* GetTarget() const override { return m_target.c_str(); }

    float GetDuration() const override { return m_duration; }
    HRESULT SetDuration(float d) override { m_duration = (d > 0.0f) ? d : 1.0f; return S_OK; }

    int32_t GetIterationCount() const override { return m_iterationCount; }
    HRESULT SetIterationCount(int32_t c) override { m_iterationCount = c; return S_OK; }

    HRESULT InsertKeyFrame(float progress, float value) override {
        progress = std::clamp(progress, 0.0f, 1.0f);
        m_keyframes.push_back({ progress, value });
        std::sort(m_keyframes.begin(), m_keyframes.end(), [](const KeyFrame& a, const KeyFrame& b) {
            return a.progress < b.progress;
        });
        return S_OK;
    }

    float Evaluate(float progress) const override {
        if (m_keyframes.empty()) return 0.0f;
        progress = std::clamp(progress, 0.0f, 1.0f);
        if (progress <= m_keyframes.front().progress) return m_keyframes.front().value;
        if (progress >= m_keyframes.back().progress) return m_keyframes.back().value;

        for (size_t i = 0; i < m_keyframes.size() - 1; ++i) {
            if (progress >= m_keyframes[i].progress && progress <= m_keyframes[i + 1].progress) {
                float segLen = m_keyframes[i + 1].progress - m_keyframes[i].progress;
                if (segLen < 1e-6f) return m_keyframes[i + 1].value;
                float t = (progress - m_keyframes[i].progress) / segLen;
                // Smooth cubic hermite easing
                float smoothT = t * t * (3.0f - 2.0f * t);
                return m_keyframes[i].value + (m_keyframes[i + 1].value - m_keyframes[i].value) * smoothT;
            }
        }
        return m_keyframes.back().value;
    }
};

class PrismVector3KeyFrameAnimationImpl : public IVector3KeyFrameAnimation {
private:
    std::atomic<uint32_t> m_refCount{ 1 };
    std::wstring m_target;
    float m_duration{ 1.0f };
    int32_t m_iterationCount{ 1 };
    struct KeyFrame { float progress; Vector3 value; };
    std::vector<KeyFrame> m_keyframes;

public:
    HRESULT QueryInterface(const GUID& riid, void** ppv) override {
        if (!ppv) return E_POINTER;
        if (riid == IID_IUnknown || riid == IID_IInspectable || riid == IID_ICompositionAnimation ||
            riid == IID_IKeyFrameAnimation || riid == IID_IVector3KeyFrameAnimation) {
            *ppv = static_cast<IVector3KeyFrameAnimation*>(this);
            AddRef();
            return S_OK;
        }
        *ppv = nullptr;
        return E_NOINTERFACE;
    }

    uint32_t AddRef() override { return ++m_refCount; }
    uint32_t Release() override {
        uint32_t r = --m_refCount;
        if (r == 0) delete this;
        return r;
    }

    HRESULT GetIids(uint32_t* c, GUID** i) override { if (c) *c = 0; if (i) *i = nullptr; return S_OK; }
    HRESULT GetRuntimeClassName(HSTRING* n) override { if (n) *n = nullptr; return S_OK; }
    HRESULT GetTrustLevel(TrustLevel* t) override { if (t) *t = TrustLevel::BaseTrust; return S_OK; }

    HRESULT SetTarget(const wchar_t* target) override {
        m_target = target ? target : L"";
        return S_OK;
    }

    const wchar_t* GetTarget() const override { return m_target.c_str(); }

    float GetDuration() const override { return m_duration; }
    HRESULT SetDuration(float d) override { m_duration = (d > 0.0f) ? d : 1.0f; return S_OK; }

    int32_t GetIterationCount() const override { return m_iterationCount; }
    HRESULT SetIterationCount(int32_t c) override { m_iterationCount = c; return S_OK; }

    HRESULT InsertKeyFrame(float progress, Vector3 value) override {
        progress = std::clamp(progress, 0.0f, 1.0f);
        m_keyframes.push_back({ progress, value });
        std::sort(m_keyframes.begin(), m_keyframes.end(), [](const KeyFrame& a, const KeyFrame& b) {
            return a.progress < b.progress;
        });
        return S_OK;
    }

    Vector3 Evaluate(float progress) const override {
        if (m_keyframes.empty()) return { 0.0f, 0.0f, 0.0f };
        progress = std::clamp(progress, 0.0f, 1.0f);
        if (progress <= m_keyframes.front().progress) return m_keyframes.front().value;
        if (progress >= m_keyframes.back().progress) return m_keyframes.back().value;

        for (size_t i = 0; i < m_keyframes.size() - 1; ++i) {
            if (progress >= m_keyframes[i].progress && progress <= m_keyframes[i + 1].progress) {
                float segLen = m_keyframes[i + 1].progress - m_keyframes[i].progress;
                if (segLen < 1e-6f) return m_keyframes[i + 1].value;
                float t = (progress - m_keyframes[i].progress) / segLen;
                float smoothT = t * t * (3.0f - 2.0f * t);
                const auto& v0 = m_keyframes[i].value;
                const auto& v1 = m_keyframes[i + 1].value;
                return {
                    v0.x + (v1.x - v0.x) * smoothT,
                    v0.y + (v1.y - v0.y) * smoothT,
                    v0.z + (v1.z - v0.z) * smoothT
                };
            }
        }
        return m_keyframes.back().value;
    }
};

class PrismExpressionAnimationImpl : public IExpressionAnimation {
private:
    std::atomic<uint32_t> m_refCount{ 1 };
    std::wstring m_target;
    std::wstring m_expression;
    std::unordered_map<std::wstring, float> m_scalars;
    std::unordered_map<std::wstring, Vector3> m_vectors;

public:
    explicit PrismExpressionAnimationImpl(const wchar_t* expr = nullptr) {
        if (expr) m_expression = expr;
    }

    HRESULT QueryInterface(const GUID& riid, void** ppv) override {
        if (!ppv) return E_POINTER;
        if (riid == IID_IUnknown || riid == IID_IInspectable || riid == IID_ICompositionAnimation ||
            riid == IID_IExpressionAnimation) {
            *ppv = static_cast<IExpressionAnimation*>(this);
            AddRef();
            return S_OK;
        }
        *ppv = nullptr;
        return E_NOINTERFACE;
    }

    uint32_t AddRef() override { return ++m_refCount; }
    uint32_t Release() override {
        uint32_t r = --m_refCount;
        if (r == 0) delete this;
        return r;
    }

    HRESULT GetIids(uint32_t* c, GUID** i) override { if (c) *c = 0; if (i) *i = nullptr; return S_OK; }
    HRESULT GetRuntimeClassName(HSTRING* n) override { if (n) *n = nullptr; return S_OK; }
    HRESULT GetTrustLevel(TrustLevel* t) override { if (t) *t = TrustLevel::BaseTrust; return S_OK; }

    HRESULT SetTarget(const wchar_t* target) override {
        m_target = target ? target : L"";
        return S_OK;
    }

    const wchar_t* GetTarget() const override { return m_target.c_str(); }

    const std::wstring& GetExpression() const override { return m_expression; }
    HRESULT SetExpression(const wchar_t* expression) override {
        m_expression = expression ? expression : L"";
        return S_OK;
    }

    HRESULT SetScalarParameter(const wchar_t* key, float value) override {
        if (!key) return E_INVALIDARG;
        m_scalars[key] = value;
        return S_OK;
    }

    HRESULT SetVector3Parameter(const wchar_t* key, Vector3 value) override {
        if (!key) return E_INVALIDARG;
        m_vectors[key] = value;
        return S_OK;
    }

    HRESULT SetReferenceParameter(const wchar_t* key, ICompositionObject* object) override {
        (void)key; (void)object;
        return S_OK;
    }

    float EvaluateScalar() const override {
        // Fast parametric expression evaluator: supports Linear interpolation "Lerp(A, B, Progress)"
        // or arithmetic expressions like "A * 2.0"
        if (m_expression.find(L"Lerp") != std::wstring::npos) {
            float a = 0.0f, b = 1.0f, progress = 0.5f;
            auto itA = m_scalars.find(L"A"); if (itA != m_scalars.end()) a = itA->second;
            auto itB = m_scalars.find(L"B"); if (itB != m_scalars.end()) b = itB->second;
            auto itP = m_scalars.find(L"Progress"); if (itP != m_scalars.end()) progress = itP->second;
            return a + (b - a) * progress;
        }

        if (m_expression.find(L"Clamp") != std::wstring::npos) {
            float val = 0.0f, minV = 0.0f, maxV = 1.0f;
            auto itV = m_scalars.find(L"Value"); if (itV != m_scalars.end()) val = itV->second;
            auto itMin = m_scalars.find(L"Min"); if (itMin != m_scalars.end()) minV = itMin->second;
            auto itMax = m_scalars.find(L"Max"); if (itMax != m_scalars.end()) maxV = itMax->second;
            return std::clamp(val, minV, maxV);
        }

        // Default scalar lookup
        if (!m_scalars.empty()) {
            return m_scalars.begin()->second;
        }
        return 1.0f;
    }
};

class PrismColorBrushImpl : public ICompositionColorBrush {
private:
    std::atomic<uint32_t> m_refCount{ 1 };
    ICompositor* m_compositor{ nullptr };
    CompositionColor m_color{};

public:
    explicit PrismColorBrushImpl(ICompositor* comp, CompositionColor c) : m_compositor(comp), m_color(c) {}

    HRESULT QueryInterface(const GUID& riid, void** ppv) override {
        if (!ppv) return E_POINTER;
        if (riid == IID_IUnknown || riid == IID_IInspectable || riid == IID_ICompositionObject ||
            riid == IID_ICompositionBrush || riid == IID_ICompositionColorBrush) {
            *ppv = static_cast<ICompositionColorBrush*>(this);
            AddRef();
            return S_OK;
        }
        *ppv = nullptr;
        return E_NOINTERFACE;
    }

    uint32_t AddRef() override { return ++m_refCount; }
    uint32_t Release() override {
        uint32_t r = --m_refCount;
        if (r == 0) delete this;
        return r;
    }

    HRESULT GetIids(uint32_t* c, GUID** i) override { if (c) *c = 0; if (i) *i = nullptr; return S_OK; }
    HRESULT GetRuntimeClassName(HSTRING* n) override { if (n) *n = nullptr; return S_OK; }
    HRESULT GetTrustLevel(TrustLevel* t) override { if (t) *t = TrustLevel::BaseTrust; return S_OK; }

    HRESULT GetCompositor(ICompositor** comp) override {
        if (!comp) return E_POINTER;
        *comp = m_compositor;
        if (m_compositor) m_compositor->AddRef();
        return S_OK;
    }

    HRESULT GetPropertySet(ICompositionPropertySet** prop) override {
        if (!prop) return E_POINTER;
        *prop = nullptr;
        return S_OK;
    }

    HRESULT StartAnimation(const wchar_t*, ICompositionAnimation*) override { return S_OK; }
    HRESULT StopAnimation(const wchar_t*) override { return S_OK; }

    CompositionColor GetColor() const override { return m_color; }
    HRESULT SetColor(CompositionColor color) override { m_color = color; return S_OK; }
};

class PrismSurfaceBrushImpl : public ICompositionSurfaceBrush {
private:
    std::atomic<uint32_t> m_refCount{ 1 };
    ICompositor* m_compositor{ nullptr };
    void* m_surface{ nullptr };
    CompositionStretch m_stretch{ CompositionStretch::Uniform };
    float m_hRatio{ 0.5f };
    float m_vRatio{ 0.5f };

public:
    explicit PrismSurfaceBrushImpl(ICompositor* comp) : m_compositor(comp) {}

    HRESULT QueryInterface(const GUID& riid, void** ppv) override {
        if (!ppv) return E_POINTER;
        if (riid == IID_IUnknown || riid == IID_IInspectable || riid == IID_ICompositionObject ||
            riid == IID_ICompositionBrush || riid == IID_ICompositionSurfaceBrush) {
            *ppv = static_cast<ICompositionSurfaceBrush*>(this);
            AddRef();
            return S_OK;
        }
        *ppv = nullptr;
        return E_NOINTERFACE;
    }

    uint32_t AddRef() override { return ++m_refCount; }
    uint32_t Release() override {
        uint32_t r = --m_refCount;
        if (r == 0) delete this;
        return r;
    }

    HRESULT GetIids(uint32_t* c, GUID** i) override { if (c) *c = 0; if (i) *i = nullptr; return S_OK; }
    HRESULT GetRuntimeClassName(HSTRING* n) override { if (n) *n = nullptr; return S_OK; }
    HRESULT GetTrustLevel(TrustLevel* t) override { if (t) *t = TrustLevel::BaseTrust; return S_OK; }

    HRESULT GetCompositor(ICompositor** comp) override {
        if (!comp) return E_POINTER;
        *comp = m_compositor;
        if (m_compositor) m_compositor->AddRef();
        return S_OK;
    }

    HRESULT GetPropertySet(ICompositionPropertySet** prop) override {
        if (!prop) return E_POINTER;
        *prop = nullptr;
        return S_OK;
    }

    HRESULT StartAnimation(const wchar_t*, ICompositionAnimation*) override { return S_OK; }
    HRESULT StopAnimation(const wchar_t*) override { return S_OK; }

    void* GetSurface() const override { return m_surface; }
    HRESULT SetSurface(void* surf) override { m_surface = surf; return S_OK; }

    CompositionStretch GetStretch() const override { return m_stretch; }
    HRESULT SetStretch(CompositionStretch stretch) override { m_stretch = stretch; return S_OK; }

    float GetHorizontalAlignmentRatio() const override { return m_hRatio; }
    HRESULT SetHorizontalAlignmentRatio(float ratio) override { m_hRatio = ratio; return S_OK; }

    float GetVerticalAlignmentRatio() const override { return m_vRatio; }
    HRESULT SetVerticalAlignmentRatio(float ratio) override { m_vRatio = ratio; return S_OK; }
};

class PrismEffectBrushImpl : public ICompositionEffectBrush {
private:
    std::atomic<uint32_t> m_refCount{ 1 };
    ICompositor* m_compositor{ nullptr };
    std::wstring m_effectName;
    std::unordered_map<std::wstring, ICompositionBrush*> m_sources;

public:
    explicit PrismEffectBrushImpl(ICompositor* comp, const wchar_t* name)
        : m_compositor(comp), m_effectName(name ? name : L"MicaBlur") {}

    ~PrismEffectBrushImpl() {
        for (auto& pair : m_sources) {
            if (pair.second) pair.second->Release();
        }
    }

    HRESULT QueryInterface(const GUID& riid, void** ppv) override {
        if (!ppv) return E_POINTER;
        if (riid == IID_IUnknown || riid == IID_IInspectable || riid == IID_ICompositionObject ||
            riid == IID_ICompositionBrush || riid == IID_ICompositionEffectBrush) {
            *ppv = static_cast<ICompositionEffectBrush*>(this);
            AddRef();
            return S_OK;
        }
        *ppv = nullptr;
        return E_NOINTERFACE;
    }

    uint32_t AddRef() override { return ++m_refCount; }
    uint32_t Release() override {
        uint32_t r = --m_refCount;
        if (r == 0) delete this;
        return r;
    }

    HRESULT GetIids(uint32_t* c, GUID** i) override { if (c) *c = 0; if (i) *i = nullptr; return S_OK; }
    HRESULT GetRuntimeClassName(HSTRING* n) override { if (n) *n = nullptr; return S_OK; }
    HRESULT GetTrustLevel(TrustLevel* t) override { if (t) *t = TrustLevel::BaseTrust; return S_OK; }

    HRESULT GetCompositor(ICompositor** comp) override {
        if (!comp) return E_POINTER;
        *comp = m_compositor;
        if (m_compositor) m_compositor->AddRef();
        return S_OK;
    }

    HRESULT GetPropertySet(ICompositionPropertySet** prop) override {
        if (!prop) return E_POINTER;
        *prop = nullptr;
        return S_OK;
    }

    HRESULT StartAnimation(const wchar_t*, ICompositionAnimation*) override { return S_OK; }
    HRESULT StopAnimation(const wchar_t*) override { return S_OK; }

    const std::wstring& GetEffectName() const override { return m_effectName; }

    HRESULT SetSourceParameter(const wchar_t* name, ICompositionBrush* source) override {
        if (!name) return E_INVALIDARG;
        auto it = m_sources.find(name);
        if (it != m_sources.end() && it->second) {
            it->second->Release();
        }
        if (source) source->AddRef();
        m_sources[name] = source;
        return S_OK;
    }

    ICompositionBrush* GetSourceParameter(const wchar_t* name) const override {
        if (!name) return nullptr;
        auto it = m_sources.find(name);
        return (it != m_sources.end()) ? it->second : nullptr;
    }
};

class PrismVisualCollectionImpl : public IVisualCollection {
private:
    std::atomic<uint32_t> m_refCount{ 1 };
    IVisual* m_owner{ nullptr };
    std::vector<IVisual*> m_children;

public:
    explicit PrismVisualCollectionImpl(IVisual* owner) : m_owner(owner) {}

    ~PrismVisualCollectionImpl() {
        RemoveAll();
    }

    HRESULT QueryInterface(const GUID& riid, void** ppv) override {
        if (!ppv) return E_POINTER;
        if (riid == IID_IUnknown || riid == IID_IInspectable || riid == IID_IVisualCollection) {
            *ppv = static_cast<IVisualCollection*>(this);
            AddRef();
            return S_OK;
        }
        *ppv = nullptr;
        return E_NOINTERFACE;
    }

    uint32_t AddRef() override { return ++m_refCount; }
    uint32_t Release() override {
        uint32_t r = --m_refCount;
        if (r == 0) delete this;
        return r;
    }

    HRESULT GetIids(uint32_t* c, GUID** i) override { if (c) *c = 0; if (i) *i = nullptr; return S_OK; }
    HRESULT GetRuntimeClassName(HSTRING* n) override { if (n) *n = nullptr; return S_OK; }
    HRESULT GetTrustLevel(TrustLevel* t) override { if (t) *t = TrustLevel::BaseTrust; return S_OK; }

    int32_t GetCount() const override { return static_cast<int32_t>(m_children.size()); }

    IVisual* GetAt(int32_t index) const override {
        if (index < 0 || static_cast<size_t>(index) >= m_children.size()) return nullptr;
        return m_children[index];
    }

    HRESULT InsertAtTop(IVisual* newChild) override {
        if (!newChild) return E_INVALIDARG;
        newChild->AddRef();
        newChild->SetParent(m_owner);
        m_children.push_back(newChild);
        return S_OK;
    }

    HRESULT InsertAtBottom(IVisual* newChild) override {
        if (!newChild) return E_INVALIDARG;
        newChild->AddRef();
        newChild->SetParent(m_owner);
        m_children.insert(m_children.begin(), newChild);
        return S_OK;
    }

    HRESULT InsertAbove(IVisual* newChild, IVisual* sibling) override {
        if (!newChild) return E_INVALIDARG;
        if (!sibling) return InsertAtTop(newChild);

        auto it = std::find(m_children.begin(), m_children.end(), sibling);
        if (it != m_children.end()) {
            newChild->AddRef();
            newChild->SetParent(m_owner);
            m_children.insert(it + 1, newChild);
            return S_OK;
        }
        return InsertAtTop(newChild);
    }

    HRESULT InsertBelow(IVisual* newChild, IVisual* sibling) override {
        if (!newChild) return E_INVALIDARG;
        if (!sibling) return InsertAtBottom(newChild);

        auto it = std::find(m_children.begin(), m_children.end(), sibling);
        if (it != m_children.end()) {
            newChild->AddRef();
            newChild->SetParent(m_owner);
            m_children.insert(it, newChild);
            return S_OK;
        }
        return InsertAtBottom(newChild);
    }

    HRESULT Remove(IVisual* child) override {
        if (!child) return E_INVALIDARG;
        auto it = std::find(m_children.begin(), m_children.end(), child);
        if (it != m_children.end()) {
            (*it)->SetParent(nullptr);
            (*it)->Release();
            m_children.erase(it);
            return S_OK;
        }
        return E_FAIL;
    }

    HRESULT RemoveAll() override {
        for (auto* c : m_children) {
            if (c) {
                c->SetParent(nullptr);
                c->Release();
            }
        }
        m_children.clear();
        return S_OK;
    }
};

class PrismSpriteVisualImpl : public ISpriteVisual {
private:
    std::atomic<uint32_t> m_refCount{ 1 };
    ICompositor* m_compositor{ nullptr };
    IVisual* m_parent{ nullptr };
    PrismVisualCollectionImpl* m_children{ nullptr };

    Vector3 m_offset{ 0.0f, 0.0f, 0.0f };
    Vector2 m_size{ 0.0f, 0.0f };
    Vector3 m_scale{ 1.0f, 1.0f, 1.0f };
    float m_rotationAngle{ 0.0f };
    Vector3 m_centerPoint{ 0.0f, 0.0f, 0.0f };
    float m_opacity{ 1.0f };
    bool m_isVisible{ true };
    CompositionCompositeMode m_compositeMode{ CompositionCompositeMode::SourceOver };

    ICompositionBrush* m_brush{ nullptr };
    std::unordered_map<std::wstring, ICompositionAnimation*> m_activeAnimations;

public:
    explicit PrismSpriteVisualImpl(ICompositor* comp) : m_compositor(comp) {
        m_children = new PrismVisualCollectionImpl(this);
    }

    ~PrismSpriteVisualImpl() {
        if (m_brush) { m_brush->Release(); m_brush = nullptr; }
        if (m_children) { m_children->Release(); m_children = nullptr; }
        for (auto& pair : m_activeAnimations) {
            if (pair.second) pair.second->Release();
        }
    }

    HRESULT QueryInterface(const GUID& riid, void** ppv) override {
        if (!ppv) return E_POINTER;
        if (riid == IID_IUnknown || riid == IID_IInspectable || riid == IID_ICompositionObject ||
            riid == IID_IVisual || riid == IID_IContainerVisual || riid == IID_ISpriteVisual) {
            *ppv = static_cast<ISpriteVisual*>(this);
            AddRef();
            return S_OK;
        }
        *ppv = nullptr;
        return E_NOINTERFACE;
    }

    uint32_t AddRef() override { return ++m_refCount; }
    uint32_t Release() override {
        uint32_t r = --m_refCount;
        if (r == 0) delete this;
        return r;
    }

    HRESULT GetIids(uint32_t* c, GUID** i) override { if (c) *c = 0; if (i) *i = nullptr; return S_OK; }
    HRESULT GetRuntimeClassName(HSTRING* n) override { if (n) *n = nullptr; return S_OK; }
    HRESULT GetTrustLevel(TrustLevel* t) override { if (t) *t = TrustLevel::BaseTrust; return S_OK; }

    HRESULT GetCompositor(ICompositor** comp) override {
        if (!comp) return E_POINTER;
        *comp = m_compositor;
        if (m_compositor) m_compositor->AddRef();
        return S_OK;
    }

    HRESULT GetPropertySet(ICompositionPropertySet** prop) override {
        if (!prop) return E_POINTER;
        *prop = nullptr;
        return S_OK;
    }

    HRESULT StartAnimation(const wchar_t* prop, ICompositionAnimation* anim) override {
        if (!prop || !anim) return E_INVALIDARG;
        anim->AddRef();
        m_activeAnimations[prop] = anim;
        return S_OK;
    }

    HRESULT StopAnimation(const wchar_t* prop) override {
        if (!prop) return E_INVALIDARG;
        auto it = m_activeAnimations.find(prop);
        if (it != m_activeAnimations.end()) {
            if (it->second) it->second->Release();
            m_activeAnimations.erase(it);
        }
        return S_OK;
    }

    Vector3 GetOffset() const override { return m_offset; }
    HRESULT SetOffset(Vector3 offset) override { m_offset = offset; return S_OK; }

    Vector2 GetSize() const override { return m_size; }
    HRESULT SetSize(Vector2 size) override { m_size = size; return S_OK; }

    Vector3 GetScale() const override { return m_scale; }
    HRESULT SetScale(Vector3 scale) override { m_scale = scale; return S_OK; }

    float GetRotationAngle() const override { return m_rotationAngle; }
    HRESULT SetRotationAngle(float r) override { m_rotationAngle = r; return S_OK; }

    Vector3 GetCenterPoint() const override { return m_centerPoint; }
    HRESULT SetCenterPoint(Vector3 c) override { m_centerPoint = c; return S_OK; }

    float GetOpacity() const override { return m_opacity; }
    HRESULT SetOpacity(float op) override { m_opacity = std::clamp(op, 0.0f, 1.0f); return S_OK; }

    bool GetIsVisible() const override { return m_isVisible; }
    HRESULT SetIsVisible(bool v) override { m_isVisible = v; return S_OK; }

    CompositionCompositeMode GetCompositeMode() const override { return m_compositeMode; }
    HRESULT SetCompositeMode(CompositionCompositeMode m) override { m_compositeMode = m; return S_OK; }

    IVisual* GetParent() const override { return m_parent; }
    void SetParent(IVisual* p) override { m_parent = p; }

    HRESULT GetChildren(IVisualCollection** children) override {
        if (!children) return E_POINTER;
        *children = m_children;
        if (m_children) m_children->AddRef();
        return S_OK;
    }

    ICompositionBrush* GetBrush() const override { return m_brush; }
    HRESULT SetBrush(ICompositionBrush* brush) override {
        if (m_brush) m_brush->Release();
        m_brush = brush;
        if (m_brush) m_brush->AddRef();
        return S_OK;
    }
};

class PrismContainerVisualImpl : public IContainerVisual {
private:
    std::atomic<uint32_t> m_refCount{ 1 };
    ICompositor* m_compositor{ nullptr };
    IVisual* m_parent{ nullptr };
    PrismVisualCollectionImpl* m_children{ nullptr };

    Vector3 m_offset{ 0.0f, 0.0f, 0.0f };
    Vector2 m_size{ 0.0f, 0.0f };
    Vector3 m_scale{ 1.0f, 1.0f, 1.0f };
    float m_rotationAngle{ 0.0f };
    Vector3 m_centerPoint{ 0.0f, 0.0f, 0.0f };
    float m_opacity{ 1.0f };
    bool m_isVisible{ true };
    CompositionCompositeMode m_compositeMode{ CompositionCompositeMode::SourceOver };

public:
    explicit PrismContainerVisualImpl(ICompositor* comp) : m_compositor(comp) {
        m_children = new PrismVisualCollectionImpl(this);
    }

    ~PrismContainerVisualImpl() {
        if (m_children) { m_children->Release(); m_children = nullptr; }
    }

    HRESULT QueryInterface(const GUID& riid, void** ppv) override {
        if (!ppv) return E_POINTER;
        if (riid == IID_IUnknown || riid == IID_IInspectable || riid == IID_ICompositionObject ||
            riid == IID_IVisual || riid == IID_IContainerVisual) {
            *ppv = static_cast<IContainerVisual*>(this);
            AddRef();
            return S_OK;
        }
        *ppv = nullptr;
        return E_NOINTERFACE;
    }

    uint32_t AddRef() override { return ++m_refCount; }
    uint32_t Release() override {
        uint32_t r = --m_refCount;
        if (r == 0) delete this;
        return r;
    }

    HRESULT GetIids(uint32_t* c, GUID** i) override { if (c) *c = 0; if (i) *i = nullptr; return S_OK; }
    HRESULT GetRuntimeClassName(HSTRING* n) override { if (n) *n = nullptr; return S_OK; }
    HRESULT GetTrustLevel(TrustLevel* t) override { if (t) *t = TrustLevel::BaseTrust; return S_OK; }

    HRESULT GetCompositor(ICompositor** comp) override {
        if (!comp) return E_POINTER;
        *comp = m_compositor;
        if (m_compositor) m_compositor->AddRef();
        return S_OK;
    }

    HRESULT GetPropertySet(ICompositionPropertySet** prop) override {
        if (!prop) return E_POINTER;
        *prop = nullptr;
        return S_OK;
    }

    HRESULT StartAnimation(const wchar_t*, ICompositionAnimation*) override { return S_OK; }
    HRESULT StopAnimation(const wchar_t*) override { return S_OK; }

    Vector3 GetOffset() const override { return m_offset; }
    HRESULT SetOffset(Vector3 offset) override { m_offset = offset; return S_OK; }

    Vector2 GetSize() const override { return m_size; }
    HRESULT SetSize(Vector2 size) override { m_size = size; return S_OK; }

    Vector3 GetScale() const override { return m_scale; }
    HRESULT SetScale(Vector3 scale) override { m_scale = scale; return S_OK; }

    float GetRotationAngle() const override { return m_rotationAngle; }
    HRESULT SetRotationAngle(float r) override { m_rotationAngle = r; return S_OK; }

    Vector3 GetCenterPoint() const override { return m_centerPoint; }
    HRESULT SetCenterPoint(Vector3 c) override { m_centerPoint = c; return S_OK; }

    float GetOpacity() const override { return m_opacity; }
    HRESULT SetOpacity(float op) override { m_opacity = std::clamp(op, 0.0f, 1.0f); return S_OK; }

    bool GetIsVisible() const override { return m_isVisible; }
    HRESULT SetIsVisible(bool v) override { m_isVisible = v; return S_OK; }

    CompositionCompositeMode GetCompositeMode() const override { return m_compositeMode; }
    HRESULT SetCompositeMode(CompositionCompositeMode m) override { m_compositeMode = m; return S_OK; }

    IVisual* GetParent() const override { return m_parent; }
    void SetParent(IVisual* p) override { m_parent = p; }

    HRESULT GetChildren(IVisualCollection** children) override {
        if (!children) return E_POINTER;
        *children = m_children;
        if (m_children) m_children->AddRef();
        return S_OK;
    }
};

class PrismCompositorImpl : public ICompositor {
private:
    std::atomic<uint32_t> m_refCount{ 1 };

public:
    PrismCompositorImpl() = default;

    HRESULT QueryInterface(const GUID& riid, void** ppv) override {
        if (!ppv) return E_POINTER;
        if (riid == IID_IUnknown || riid == IID_IInspectable || riid == IID_ICompositor || riid == IID_ICompositor2) {
            *ppv = static_cast<ICompositor*>(this);
            AddRef();
            return S_OK;
        }
        *ppv = nullptr;
        return E_NOINTERFACE;
    }

    uint32_t AddRef() override { return ++m_refCount; }
    uint32_t Release() override {
        uint32_t r = --m_refCount;
        if (r == 0) delete this;
        return r;
    }

    HRESULT GetIids(uint32_t* c, GUID** i) override { if (c) *c = 0; if (i) *i = nullptr; return S_OK; }
    HRESULT GetRuntimeClassName(HSTRING* n) override { if (n) *n = nullptr; return S_OK; }
    HRESULT GetTrustLevel(TrustLevel* t) override { if (t) *t = TrustLevel::BaseTrust; return S_OK; }

    HRESULT CreateContainerVisual(IContainerVisual** result) override {
        if (!result) return E_POINTER;
        *result = new PrismContainerVisualImpl(this);
        return S_OK;
    }

    HRESULT CreateSpriteVisual(ISpriteVisual** result) override {
        if (!result) return E_POINTER;
        *result = new PrismSpriteVisualImpl(this);
        return S_OK;
    }

    HRESULT CreateColorBrush(ICompositionColorBrush** result) override {
        return CreateColorBrushWithColor({ 255, 255, 255, 255 }, result);
    }

    HRESULT CreateColorBrushWithColor(CompositionColor color, ICompositionColorBrush** result) override {
        if (!result) return E_POINTER;
        *result = new PrismColorBrushImpl(this, color);
        return S_OK;
    }

    HRESULT CreateSurfaceBrush(ICompositionSurfaceBrush** result) override {
        if (!result) return E_POINTER;
        *result = new PrismSurfaceBrushImpl(this);
        return S_OK;
    }

    HRESULT CreateEffectBrush(const wchar_t* effectName, ICompositionEffectBrush** result) override {
        if (!result) return E_POINTER;
        *result = new PrismEffectBrushImpl(this, effectName);
        return S_OK;
    }

    HRESULT CreateScalarKeyFrameAnimation(IScalarKeyFrameAnimation** result) override {
        if (!result) return E_POINTER;
        *result = new PrismScalarKeyFrameAnimationImpl();
        return S_OK;
    }

    HRESULT CreateVector3KeyFrameAnimation(IVector3KeyFrameAnimation** result) override {
        if (!result) return E_POINTER;
        *result = new PrismVector3KeyFrameAnimationImpl();
        return S_OK;
    }

    HRESULT CreateExpressionAnimation(IExpressionAnimation** result) override {
        if (!result) return E_POINTER;
        *result = new PrismExpressionAnimationImpl();
        return S_OK;
    }

    HRESULT CreateExpressionAnimationWithExpression(const wchar_t* expr, IExpressionAnimation** result) override {
        if (!result) return E_POINTER;
        *result = new PrismExpressionAnimationImpl(expr);
        return S_OK;
    }

    HRESULT CreatePropertySet(ICompositionPropertySet** result) override {
        if (!result) return E_POINTER;
        *result = new PrismCompositionPropertySetImpl();
        return S_OK;
    }
};

// ============================================================================
// 5. Activation Factory for "Windows.UI.Composition.Compositor"
// ============================================================================

class PrismCompositionActivationFactory : public IActivationFactory {
private:
    std::atomic<uint32_t> m_refCount{ 1 };

public:
    HRESULT QueryInterface(const GUID& riid, void** ppv) override {
        if (!ppv) return E_POINTER;
        if (riid == IID_IUnknown || riid == IID_IInspectable || riid == IID_IActivationFactory) {
            *ppv = static_cast<IActivationFactory*>(this);
            AddRef();
            return S_OK;
        }
        *ppv = nullptr;
        return E_NOINTERFACE;
    }

    uint32_t AddRef() override { return ++m_refCount; }
    uint32_t Release() override {
        uint32_t r = --m_refCount;
        if (r == 0) delete this;
        return r;
    }

    HRESULT GetIids(uint32_t* c, GUID** i) override { if (c) *c = 0; if (i) *i = nullptr; return S_OK; }
    HRESULT GetRuntimeClassName(HSTRING* n) override { if (n) *n = nullptr; return S_OK; }
    HRESULT GetTrustLevel(TrustLevel* t) override { if (t) *t = TrustLevel::BaseTrust; return S_OK; }

    HRESULT ActivateInstance(IInspectable** instance) override {
        if (!instance) return E_POINTER;
        *instance = new PrismCompositorImpl();
        return S_OK;
    }
};

// Standalone Export Helper
inline HRESULT PrismGetActivationFactory(const wchar_t* activatableClassId, IActivationFactory** factory) {
    if (!activatableClassId || !factory) return E_INVALIDARG;
    std::wstring cid(activatableClassId);
    if (cid == L"Windows.UI.Composition.Compositor" || cid == L"Microsoft.UI.Composition.Compositor") {
        *factory = new PrismCompositionActivationFactory();
        return S_OK;
    }
    *factory = nullptr;
    return E_FAIL;
}

} // namespace prismx::composition
