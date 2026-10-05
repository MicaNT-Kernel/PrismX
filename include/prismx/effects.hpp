// ============================================================================
// PrismX: Sovereign Image Processing, Post-Processing Pipeline & Effect Graph
// File: include/prismx/effects.hpp
// 
// Clean-Room Implementation in ISO C++23. Zero External Dependencies.
// Tribute to Dave Cutler's 1988 DEC PRISM Architecture.
// ============================================================================

#pragma once

#include "prismx/types.hpp"
#include "prismx/math.hpp"
#include "prismx/color_system.hpp"

#include <cstdint>
#include <vector>
#include <memory>
#include <string>
#include <cmath>
#include <numbers>
#include <algorithm>
#include <array>
#include <unordered_map>
#include <fstream>
#include <cstring>
#include <functional>

namespace prismx::effects {

using REFIID = const IID&;

// ============================================================================
// 1. COM GUIDs
// ============================================================================

inline constexpr GUID IID_IPrismImage = {
    0x3F91A801, 0x51E2, 0x489B, { 0x82, 0x14, 0x7E, 0x42, 0x90, 0x11, 0xAA, 0x01 }
};
inline constexpr GUID IID_IPrismEffect = {
    0x3F91A802, 0x51E2, 0x489B, { 0x82, 0x14, 0x7E, 0x42, 0x90, 0x11, 0xAA, 0x02 }
};
inline constexpr GUID IID_IPrismEffectGraph = {
    0x3F91A803, 0x51E2, 0x489B, { 0x82, 0x14, 0x7E, 0x42, 0x90, 0x11, 0xAA, 0x03 }
};
inline constexpr GUID IID_IPrismEffectContext = {
    0x3F91A804, 0x51E2, 0x489B, { 0x82, 0x14, 0x7E, 0x42, 0x90, 0x11, 0xAA, 0x04 }
};

inline constexpr GUID CLSID_PrismGaussianBlurEffect = {
    0x3F91B001, 0x51E2, 0x489B, { 0x82, 0x14, 0x7E, 0x42, 0x90, 0x11, 0xBB, 0x01 }
};
inline constexpr GUID CLSID_PrismDirectionalBlurEffect = {
    0x3F91B002, 0x51E2, 0x489B, { 0x82, 0x14, 0x7E, 0x42, 0x90, 0x11, 0xBB, 0x02 }
};
inline constexpr GUID CLSID_PrismColorMatrixEffect = {
    0x3F91B003, 0x51E2, 0x489B, { 0x82, 0x14, 0x7E, 0x42, 0x90, 0x11, 0xBB, 0x03 }
};
inline constexpr GUID CLSID_PrismBloomEffect = {
    0x3F91B004, 0x51E2, 0x489B, { 0x82, 0x14, 0x7E, 0x42, 0x90, 0x11, 0xBB, 0x04 }
};
inline constexpr GUID CLSID_PrismDropShadowEffect = {
    0x3F91B005, 0x51E2, 0x489B, { 0x82, 0x14, 0x7E, 0x42, 0x90, 0x11, 0xBB, 0x05 }
};
inline constexpr GUID CLSID_PrismConvolutionEffect = {
    0x3F91B006, 0x51E2, 0x489B, { 0x82, 0x14, 0x7E, 0x42, 0x90, 0x11, 0xBB, 0x06 }
};
inline constexpr GUID CLSID_PrismVignetteEffect = {
    0x3F91B007, 0x51E2, 0x489B, { 0x82, 0x14, 0x7E, 0x42, 0x90, 0x11, 0xBB, 0x07 }
};
inline constexpr GUID CLSID_PrismToneMappingEffect = {
    0x3F91B008, 0x51E2, 0x489B, { 0x82, 0x14, 0x7E, 0x42, 0x90, 0x11, 0xBB, 0x08 }
};
inline constexpr GUID CLSID_PrismBlendEffect = {
    0x3F91B009, 0x51E2, 0x489B, { 0x82, 0x14, 0x7E, 0x42, 0x90, 0x11, 0xBB, 0x09 }
};
inline constexpr GUID CLSID_PrismChromaticAberrationEffect = {
    0x3F91B00A, 0x51E2, 0x489B, { 0x82, 0x14, 0x7E, 0x42, 0x90, 0x11, 0xBB, 0x0A }
};

// ============================================================================
// 2. Enums & Common Structures
// ============================================================================

enum class BorderMode : uint32_t {
    Soft = 0,
    Hard = 1,
    Mirror = 2,
    Repeat = 3
};

enum class ToneMapOperator : uint32_t {
    Reinhard = 0,
    ACES = 1,
    Filmic = 2,
    Exposure = 3
};

enum class ConvolutionPreset : uint32_t {
    Sharpen = 0,
    EdgeDetect = 1,
    Emboss = 2,
    BoxBlur = 3,
    Custom = 4
};

enum class EffectBlendMode : uint32_t {
    Normal = 0,
    Multiply = 1,
    Screen = 2,
    Overlay = 3,
    Darken = 4,
    Lighten = 5,
    ColorDodge = 6,
    ColorBurn = 7,
    HardLight = 8,
    SoftLight = 9,
    Difference = 10,
    Exclusion = 11,
    Additive = 12
};

// Property IDs
enum EffectPropId : uint32_t {
    PROP_GENERIC_INPUT_0 = 0,
    PROP_GENERIC_INPUT_1 = 1,

    // Gaussian Blur
    PROP_GAUSSIAN_STANDARD_DEVIATION = 100,
    PROP_GAUSSIAN_BORDER_MODE = 101,

    // Directional Blur
    PROP_DIRBLUR_STANDARD_DEVIATION = 200,
    PROP_DIRBLUR_ANGLE = 201,

    // Color Matrix
    PROP_COLORMATRIX_MATRIX = 300,

    // Bloom
    PROP_BLOOM_THRESHOLD = 400,
    PROP_BLOOM_INTENSITY = 401,
    PROP_BLOOM_BLUR_RADIUS = 402,
    PROP_BLOOM_TINT = 403,

    // Drop Shadow
    PROP_SHADOW_OFFSET_X = 500,
    PROP_SHADOW_OFFSET_Y = 501,
    PROP_SHADOW_BLUR_RADIUS = 502,
    PROP_SHADOW_COLOR = 503,
    PROP_SHADOW_OPACITY = 504,

    // Convolution
    PROP_CONV_PRESET = 600,
    PROP_CONV_MATRIX_3X3 = 601,
    PROP_CONV_DIVISOR = 602,
    PROP_CONV_BIAS = 603,

    // Vignette
    PROP_VIGNETTE_CENTER_X = 700,
    PROP_VIGNETTE_CENTER_Y = 701,
    PROP_VIGNETTE_RADIUS = 702,
    PROP_VIGNETTE_SOFTNESS = 703,

    // Tone Mapping
    PROP_TONEMAP_OPERATOR = 800,
    PROP_TONEMAP_EXPOSURE = 801,

    // Blend
    PROP_BLEND_MODE = 900,

    // Chromatic Aberration
    PROP_CHROMA_OFFSET_R_X = 1000,
    PROP_CHROMA_OFFSET_R_Y = 1001,
    PROP_CHROMA_OFFSET_B_X = 1002,
    PROP_CHROMA_OFFSET_B_Y = 1003
};

// 5x4 Affine Color Transform Matrix
struct ColorMatrix5x4 {
    float m[5][4]{
        { 1.0f, 0.0f, 0.0f, 0.0f },
        { 0.0f, 1.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 1.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f, 1.0f },
        { 0.0f, 0.0f, 0.0f, 0.0f }
    };

    static ColorMatrix5x4 Identity() {
        return ColorMatrix5x4{};
    }

    static ColorMatrix5x4 Grayscale() {
        ColorMatrix5x4 cm{};
        for (int r = 0; r < 3; ++r) {
            cm.m[0][r] = 0.2126f;
            cm.m[1][r] = 0.7152f;
            cm.m[2][r] = 0.0722f;
        }
        return cm;
    }

    static ColorMatrix5x4 Sepia() {
        ColorMatrix5x4 cm{};
        cm.m[0][0] = 0.393f; cm.m[1][0] = 0.769f; cm.m[2][0] = 0.189f;
        cm.m[0][1] = 0.349f; cm.m[1][1] = 0.686f; cm.m[2][1] = 0.168f;
        cm.m[0][2] = 0.272f; cm.m[1][2] = 0.534f; cm.m[2][2] = 0.131f;
        return cm;
    }

    static ColorMatrix5x4 Invert() {
        ColorMatrix5x4 cm{};
        cm.m[0][0] = -1.0f;
        cm.m[1][1] = -1.0f;
        cm.m[2][2] = -1.0f;
        cm.m[4][0] = 1.0f;
        cm.m[4][1] = 1.0f;
        cm.m[4][2] = 1.0f;
        return cm;
    }

    static ColorMatrix5x4 BrightnessContrast(float brightness, float contrast) {
        ColorMatrix5x4 cm{};
        cm.m[0][0] = contrast;
        cm.m[1][1] = contrast;
        cm.m[2][2] = contrast;
        cm.m[4][0] = brightness + (1.0f - contrast) * 0.5f;
        cm.m[4][1] = brightness + (1.0f - contrast) * 0.5f;
        cm.m[4][2] = brightness + (1.0f - contrast) * 0.5f;
        return cm;
    }

    static ColorMatrix5x4 Saturation(float sat) {
        ColorMatrix5x4 cm{};
        float r = 0.2126f * (1.0f - sat);
        float g = 0.7152f * (1.0f - sat);
        float b = 0.0722f * (1.0f - sat);

        cm.m[0][0] = r + sat; cm.m[1][0] = g;       cm.m[2][0] = b;
        cm.m[0][1] = r;       cm.m[1][1] = g + sat; cm.m[2][1] = b;
        cm.m[0][2] = r;       cm.m[1][2] = g;       cm.m[2][2] = b + sat;
        return cm;
    }
};

// ============================================================================
// 3. Pixel Math & Color Helpers
// ============================================================================

struct PixelRGBA {
    float r{ 0.0f };
    float g{ 0.0f };
    float b{ 0.0f };
    float a{ 1.0f };

    static PixelRGBA FromU32(uint32_t val) {
        PixelRGBA c;
        c.r = static_cast<float>((val >> 16) & 0xFF) / 255.0f;
        c.g = static_cast<float>((val >> 8) & 0xFF) / 255.0f;
        c.b = static_cast<float>(val & 0xFF) / 255.0f;
        c.a = static_cast<float>((val >> 24) & 0xFF) / 255.0f;
        return c;
    }

    uint32_t ToU32() const {
        uint32_t ur = static_cast<uint32_t>(std::clamp(r * 255.0f + 0.5f, 0.0f, 255.0f));
        uint32_t ug = static_cast<uint32_t>(std::clamp(g * 255.0f + 0.5f, 0.0f, 255.0f));
        uint32_t ub = static_cast<uint32_t>(std::clamp(b * 255.0f + 0.5f, 0.0f, 255.0f));
        uint32_t ua = static_cast<uint32_t>(std::clamp(a * 255.0f + 0.5f, 0.0f, 255.0f));
        return (ua << 24) | (ur << 16) | (ug << 8) | ub;
    }

    float Luminance() const {
        return 0.2126f * r + 0.7152f * g + 0.0722f * b;
    }
};

// ============================================================================
// 4. Core COM Interfaces
// ============================================================================

class IPrismImage : public prismx::IUnknown {
public:
    virtual uint32_t GetWidth() const = 0;
    virtual uint32_t GetHeight() const = 0;
    virtual const uint32_t* GetPixels() const = 0;
    virtual uint32_t* GetPixels() = 0;
    virtual uint32_t GetPixel(uint32_t x, uint32_t y) const = 0;
    virtual void SetPixel(uint32_t x, uint32_t y, uint32_t color) = 0;
    virtual HRESULT Clone(IPrismImage** ppClone) = 0;
    virtual bool SaveToBmp(const char* filename) const = 0;
};

class IPrismEffect : public prismx::IUnknown {
public:
    virtual GUID GetEffectId() const = 0;
    virtual const char* GetEffectName() const = 0;
    virtual uint32_t GetInputCount() const = 0;
    virtual HRESULT SetInput(uint32_t index, IPrismImage* pInput) = 0;
    virtual HRESULT GetInput(uint32_t index, IPrismImage** ppInput) = 0;
    virtual HRESULT SetInputEffect(uint32_t index, IPrismEffect* pInputEffect) = 0;
    virtual HRESULT SetFloat(uint32_t propId, float value) = 0;
    virtual HRESULT GetFloat(uint32_t propId, float* pValue) const = 0;
    virtual HRESULT SetInt(uint32_t propId, int32_t value) = 0;
    virtual HRESULT GetInt(uint32_t propId, int32_t* pValue) const = 0;
    virtual HRESULT SetValue(uint32_t propId, const void* data, uint32_t cbData) = 0;
    virtual HRESULT GetValue(uint32_t propId, void* data, uint32_t cbData) const = 0;
    virtual HRESULT GetOutput(IPrismImage** ppOutput) = 0;
    virtual HRESULT Invalidate() = 0;
};

class IPrismEffectGraph : public prismx::IUnknown {
public:
    virtual HRESULT AddEffect(IPrismEffect* pEffect) = 0;
    virtual HRESULT SetRootEffect(IPrismEffect* pEffect) = 0;
    virtual HRESULT Render(IPrismImage** ppOutput) = 0;
    virtual size_t GetNodeCount() const = 0;
};

class IPrismEffectContext : public prismx::IUnknown {
public:
    virtual HRESULT CreateImage(uint32_t width, uint32_t height, IPrismImage** ppImage) = 0;
    virtual HRESULT CreateImageFromPixels(uint32_t width, uint32_t height, const uint32_t* pPixels, IPrismImage** ppImage) = 0;
    virtual HRESULT CreateEffect(const GUID& effectId, IPrismEffect** ppEffect) = 0;
    virtual HRESULT CreateEffectGraph(IPrismEffectGraph** ppGraph) = 0;
};

// ============================================================================
// 5. Image Buffer Implementation
// ============================================================================

class PrismImageImpl : public IPrismImage {
private:
    std::atomic<uint32_t> m_refCount{ 1 };
    uint32_t m_width{ 0 };
    uint32_t m_height{ 0 };
    std::vector<uint32_t> m_pixels;

public:
    PrismImageImpl(uint32_t w, uint32_t h)
        : m_width(w), m_height(h), m_pixels(static_cast<size_t>(w) * h, 0xFF000000) {}

    PrismImageImpl(uint32_t w, uint32_t h, const uint32_t* pInit)
        : m_width(w), m_height(h) {
        m_pixels.resize(static_cast<size_t>(w) * h);
        if (pInit) {
            std::memcpy(m_pixels.data(), pInit, m_pixels.size() * sizeof(uint32_t));
        } else {
            std::fill(m_pixels.begin(), m_pixels.end(), 0xFF000000);
        }
    }

    HRESULT QueryInterface(REFIID riid, void** ppv) override {
        if (!ppv) return E_POINTER;
        if (riid == IID_IUnknown || riid == IID_IPrismImage) {
            *ppv = static_cast<IPrismImage*>(this);
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

    uint32_t GetWidth() const override { return m_width; }
    uint32_t GetHeight() const override { return m_height; }
    const uint32_t* GetPixels() const override { return m_pixels.data(); }
    uint32_t* GetPixels() override { return m_pixels.data(); }

    uint32_t GetPixel(uint32_t x, uint32_t y) const override {
        if (x >= m_width || y >= m_height) return 0;
        return m_pixels[static_cast<size_t>(y) * m_width + x];
    }

    void SetPixel(uint32_t x, uint32_t y, uint32_t color) override {
        if (x < m_width && y < m_height) {
            m_pixels[static_cast<size_t>(y) * m_width + x] = color;
        }
    }

    HRESULT Clone(IPrismImage** ppClone) override {
        if (!ppClone) return E_POINTER;
        *ppClone = new PrismImageImpl(m_width, m_height, m_pixels.data());
        return S_OK;
    }

    bool SaveToBmp(const char* filename) const override {
        if (!filename || m_pixels.empty()) return false;
        std::ofstream file(filename, std::ios::binary);
        if (!file.is_open()) return false;

        uint32_t rowSize = ((m_width * 3 + 3) / 4) * 4;
        uint32_t imageSize = rowSize * m_height;
        uint32_t fileSize = 54 + imageSize;

        uint8_t fileHeader[14] = {
            'B', 'M',
            static_cast<uint8_t>(fileSize), static_cast<uint8_t>(fileSize >> 8),
            static_cast<uint8_t>(fileSize >> 16), static_cast<uint8_t>(fileSize >> 24),
            0, 0, 0, 0, 54, 0, 0, 0
        };

        uint8_t infoHeader[40] = {
            40, 0, 0, 0,
            static_cast<uint8_t>(m_width), static_cast<uint8_t>(m_width >> 8),
            static_cast<uint8_t>(m_width >> 16), static_cast<uint8_t>(m_width >> 24),
            static_cast<uint8_t>(m_height), static_cast<uint8_t>(m_height >> 8),
            static_cast<uint8_t>(m_height >> 16), static_cast<uint8_t>(m_height >> 24),
            1, 0, 24, 0, 0, 0, 0, 0,
            static_cast<uint8_t>(imageSize), static_cast<uint8_t>(imageSize >> 8),
            static_cast<uint8_t>(imageSize >> 16), static_cast<uint8_t>(imageSize >> 24),
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        };

        file.write(reinterpret_cast<const char*>(fileHeader), sizeof(fileHeader));
        file.write(reinterpret_cast<const char*>(infoHeader), sizeof(infoHeader));

        std::vector<uint8_t> row(rowSize, 0);
        for (int y = static_cast<int>(m_height) - 1; y >= 0; --y) {
            for (uint32_t x = 0; x < m_width; ++x) {
                uint32_t p = m_pixels[static_cast<size_t>(y) * m_width + x];
                row[x * 3 + 0] = static_cast<uint8_t>(p & 0xFF);         // B
                row[x * 3 + 1] = static_cast<uint8_t>((p >> 8) & 0xFF);  // G
                row[x * 3 + 2] = static_cast<uint8_t>((p >> 16) & 0xFF); // R
            }
            file.write(reinterpret_cast<const char*>(row.data()), rowSize);
        }
        return true;
    }
};

// ============================================================================
// 6. Base Effect Implementation Class
// ============================================================================

class PrismEffectBase : public IPrismEffect {
protected:
    std::atomic<uint32_t> m_refCount{ 1 };
    std::vector<ComPtr<IPrismImage>> m_inputs;
    std::vector<ComPtr<IPrismEffect>> m_inputEffects;
    ComPtr<IPrismImage> m_cachedOutput;
    bool m_dirty{ true };

    virtual HRESULT Execute(IPrismImage** ppOutput) = 0;

    HRESULT ResolveInput(uint32_t index, IPrismImage** ppImage) {
        if (!ppImage) return E_POINTER;
        if (index < m_inputEffects.size() && m_inputEffects[index].Get()) {
            return m_inputEffects[index]->GetOutput(ppImage);
        }
        if (index < m_inputs.size() && m_inputs[index].Get()) {
            *ppImage = m_inputs[index].Get();
            (*ppImage)->AddRef();
            return S_OK;
        }
        *ppImage = nullptr;
        return E_FAIL;
    }

public:
    PrismEffectBase(uint32_t numInputs = 1) {
        m_inputs.resize(numInputs);
        m_inputEffects.resize(numInputs);
    }

    HRESULT QueryInterface(REFIID riid, void** ppv) override {
        if (!ppv) return E_POINTER;
        if (riid == IID_IUnknown || riid == IID_IPrismEffect) {
            *ppv = static_cast<IPrismEffect*>(this);
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

    uint32_t GetInputCount() const override {
        return static_cast<uint32_t>(m_inputs.size());
    }

    HRESULT SetInput(uint32_t index, IPrismImage* pInput) override {
        if (index >= m_inputs.size()) return E_INVALIDARG;
        m_inputs[index] = pInput;
        m_inputEffects[index] = nullptr;
        m_dirty = true;
        return S_OK;
    }

    HRESULT GetInput(uint32_t index, IPrismImage** ppInput) override {
        if (!ppInput) return E_POINTER;
        if (index >= m_inputs.size()) return E_INVALIDARG;
        *ppInput = m_inputs[index].Get();
        if (*ppInput) (*ppInput)->AddRef();
        return S_OK;
    }

    HRESULT SetInputEffect(uint32_t index, IPrismEffect* pInputEffect) override {
        if (index >= m_inputs.size()) return E_INVALIDARG;
        m_inputEffects[index] = pInputEffect;
        m_inputs[index] = nullptr;
        m_dirty = true;
        return S_OK;
    }

    HRESULT Invalidate() override {
        m_dirty = true;
        m_cachedOutput = nullptr;
        return S_OK;
    }

    HRESULT GetOutput(IPrismImage** ppOutput) override {
        if (!ppOutput) return E_POINTER;
        if (m_dirty || !m_cachedOutput.Get()) {
            ComPtr<IPrismImage> result;
            HRESULT hr = Execute(result.Put());
            if (FAILED(hr)) return hr;
            m_cachedOutput = result;
            m_dirty = false;
        }
        *ppOutput = m_cachedOutput.Get();
        if (*ppOutput) (*ppOutput)->AddRef();
        return S_OK;
    }
};

// ============================================================================
// 7. Gaussian Blur Effect
// ============================================================================

class PrismGaussianBlurEffect : public PrismEffectBase {
private:
    float m_sigma{ 3.0f };
    BorderMode m_borderMode{ BorderMode::Soft };

public:
    PrismGaussianBlurEffect() : PrismEffectBase(1) {}

    GUID GetEffectId() const override { return CLSID_PrismGaussianBlurEffect; }
    const char* GetEffectName() const override { return "PrismGaussianBlurEffect"; }

    HRESULT SetFloat(uint32_t propId, float value) override {
        if (propId == PROP_GAUSSIAN_STANDARD_DEVIATION) {
            m_sigma = std::max(0.1f, value);
            m_dirty = true;
            return S_OK;
        }
        return E_INVALIDARG;
    }

    HRESULT GetFloat(uint32_t propId, float* pValue) const override {
        if (!pValue) return E_POINTER;
        if (propId == PROP_GAUSSIAN_STANDARD_DEVIATION) {
            *pValue = m_sigma;
            return S_OK;
        }
        return E_INVALIDARG;
    }

    HRESULT SetInt(uint32_t propId, int32_t value) override {
        if (propId == PROP_GAUSSIAN_BORDER_MODE) {
            m_borderMode = static_cast<BorderMode>(value);
            m_dirty = true;
            return S_OK;
        }
        return E_INVALIDARG;
    }

    HRESULT GetInt(uint32_t propId, int32_t* pValue) const override {
        if (!pValue) return E_POINTER;
        if (propId == PROP_GAUSSIAN_BORDER_MODE) {
            *pValue = static_cast<int32_t>(m_borderMode);
            return S_OK;
        }
        return E_INVALIDARG;
    }

    HRESULT SetValue(uint32_t, const void*, uint32_t) override { return E_NOTIMPL; }
    HRESULT GetValue(uint32_t, void*, uint32_t) const override { return E_NOTIMPL; }

protected:
    HRESULT Execute(IPrismImage** ppOutput) override {
        ComPtr<IPrismImage> spInput;
        HRESULT hr = ResolveInput(0, spInput.Put());
        if (FAILED(hr) || !spInput.Get()) return E_FAIL;

        uint32_t w = spInput->GetWidth();
        uint32_t h = spInput->GetHeight();
        if (w == 0 || h == 0) return E_FAIL;

        int radius = std::min(15, std::max(1, static_cast<int>(std::ceil(3.0f * m_sigma))));
        std::vector<float> kernel(2 * radius + 1);
        float sum = 0.0f;
        float twoSigmaSq = 2.0f * m_sigma * m_sigma;

        for (int i = -radius; i <= radius; ++i) {
            float val = std::exp(-static_cast<float>(i * i) / twoSigmaSq);
            kernel[i + radius] = val;
            sum += val;
        }
        for (auto& k : kernel) k /= sum;

        // Pass 1: Horizontal Blur -> Intermediate Buffer
        std::vector<PixelRGBA> intermediate(static_cast<size_t>(w) * h);
        for (uint32_t y = 0; y < h; ++y) {
            for (uint32_t x = 0; x < w; ++x) {
                float r = 0, g = 0, b = 0, a = 0;
                for (int k = -radius; k <= radius; ++k) {
                    int sampleX = static_cast<int>(x) + k;
                    if (m_borderMode == BorderMode::Mirror) {
                        if (sampleX < 0) sampleX = -sampleX;
                        if (sampleX >= static_cast<int>(w)) sampleX = 2 * (static_cast<int>(w) - 1) - sampleX;
                    }
                    sampleX = std::clamp(sampleX, 0, static_cast<int>(w) - 1);

                    PixelRGBA c = PixelRGBA::FromU32(spInput->GetPixel(sampleX, y));
                    float wgt = kernel[k + radius];
                    r += c.r * wgt;
                    g += c.g * wgt;
                    b += c.b * wgt;
                    a += c.a * wgt;
                }
                intermediate[static_cast<size_t>(y) * w + x] = { r, g, b, a };
            }
        }

        // Pass 2: Vertical Blur -> Output Image
        auto* pOutImg = new PrismImageImpl(w, h);
        for (uint32_t y = 0; y < h; ++y) {
            for (uint32_t x = 0; x < w; ++x) {
                float r = 0, g = 0, b = 0, a = 0;
                for (int k = -radius; k <= radius; ++k) {
                    int sampleY = static_cast<int>(y) + k;
                    if (m_borderMode == BorderMode::Mirror) {
                        if (sampleY < 0) sampleY = -sampleY;
                        if (sampleY >= static_cast<int>(h)) sampleY = 2 * (static_cast<int>(h) - 1) - sampleY;
                    }
                    sampleY = std::clamp(sampleY, 0, static_cast<int>(h) - 1);

                    const auto& c = intermediate[static_cast<size_t>(sampleY) * w + x];
                    float wgt = kernel[k + radius];
                    r += c.r * wgt;
                    g += c.g * wgt;
                    b += c.b * wgt;
                    a += c.a * wgt;
                }
                pOutImg->SetPixel(x, y, PixelRGBA{ r, g, b, a }.ToU32());
            }
        }

        *ppOutput = pOutImg;
        return S_OK;
    }
};

// ============================================================================
// 8. Color Matrix Effect
// ============================================================================

class PrismColorMatrixEffect : public PrismEffectBase {
private:
    ColorMatrix5x4 m_matrix{ ColorMatrix5x4::Identity() };

public:
    PrismColorMatrixEffect() : PrismEffectBase(1) {}

    GUID GetEffectId() const override { return CLSID_PrismColorMatrixEffect; }
    const char* GetEffectName() const override { return "PrismColorMatrixEffect"; }

    HRESULT SetFloat(uint32_t, float) override { return E_NOTIMPL; }
    HRESULT GetFloat(uint32_t, float*) const override { return E_NOTIMPL; }
    HRESULT SetInt(uint32_t, int32_t) override { return E_NOTIMPL; }
    HRESULT GetInt(uint32_t, int32_t*) const override { return E_NOTIMPL; }

    HRESULT SetValue(uint32_t propId, const void* data, uint32_t cbData) override {
        if (!data) return E_POINTER;
        if (propId == PROP_COLORMATRIX_MATRIX && cbData == sizeof(ColorMatrix5x4)) {
            std::memcpy(&m_matrix, data, sizeof(ColorMatrix5x4));
            m_dirty = true;
            return S_OK;
        }
        return E_INVALIDARG;
    }

    HRESULT GetValue(uint32_t propId, void* data, uint32_t cbData) const override {
        if (!data) return E_POINTER;
        if (propId == PROP_COLORMATRIX_MATRIX && cbData == sizeof(ColorMatrix5x4)) {
            std::memcpy(data, &m_matrix, sizeof(ColorMatrix5x4));
            return S_OK;
        }
        return E_INVALIDARG;
    }

protected:
    HRESULT Execute(IPrismImage** ppOutput) override {
        ComPtr<IPrismImage> spInput;
        HRESULT hr = ResolveInput(0, spInput.Put());
        if (FAILED(hr) || !spInput.Get()) return E_FAIL;

        uint32_t w = spInput->GetWidth();
        uint32_t h = spInput->GetHeight();
        auto* pOutImg = new PrismImageImpl(w, h);

        for (uint32_t y = 0; y < h; ++y) {
            for (uint32_t x = 0; x < w; ++x) {
                PixelRGBA c = PixelRGBA::FromU32(spInput->GetPixel(x, y));
                float r = c.r * m_matrix.m[0][0] + c.g * m_matrix.m[1][0] + c.b * m_matrix.m[2][0] + c.a * m_matrix.m[3][0] + m_matrix.m[4][0];
                float g = c.r * m_matrix.m[0][1] + c.g * m_matrix.m[1][1] + c.b * m_matrix.m[2][1] + c.a * m_matrix.m[3][1] + m_matrix.m[4][1];
                float b = c.r * m_matrix.m[0][2] + c.g * m_matrix.m[1][2] + c.b * m_matrix.m[2][2] + c.a * m_matrix.m[3][2] + m_matrix.m[4][2];
                float a = c.r * m_matrix.m[0][3] + c.g * m_matrix.m[1][3] + c.b * m_matrix.m[2][3] + c.a * m_matrix.m[3][3] + m_matrix.m[4][3];

                pOutImg->SetPixel(x, y, PixelRGBA{ r, g, b, a }.ToU32());
            }
        }

        *ppOutput = pOutImg;
        return S_OK;
    }
};

// ============================================================================
// 9. Bloom & HDR Glow Effect
// ============================================================================

class PrismBloomEffect : public PrismEffectBase {
private:
    float m_threshold{ 0.7f };
    float m_intensity{ 1.5f };
    float m_blurRadius{ 4.0f };
    uint32_t m_tint{ 0xFFFFFFFF };

public:
    PrismBloomEffect() : PrismEffectBase(1) {}

    GUID GetEffectId() const override { return CLSID_PrismBloomEffect; }
    const char* GetEffectName() const override { return "PrismBloomEffect"; }

    HRESULT SetFloat(uint32_t propId, float value) override {
        if (propId == PROP_BLOOM_THRESHOLD) { m_threshold = std::clamp(value, 0.0f, 1.0f); m_dirty = true; return S_OK; }
        if (propId == PROP_BLOOM_INTENSITY) { m_intensity = std::max(0.0f, value); m_dirty = true; return S_OK; }
        if (propId == PROP_BLOOM_BLUR_RADIUS) { m_blurRadius = std::max(0.1f, value); m_dirty = true; return S_OK; }
        return E_INVALIDARG;
    }

    HRESULT GetFloat(uint32_t propId, float* pValue) const override {
        if (!pValue) return E_POINTER;
        if (propId == PROP_BLOOM_THRESHOLD) { *pValue = m_threshold; return S_OK; }
        if (propId == PROP_BLOOM_INTENSITY) { *pValue = m_intensity; return S_OK; }
        if (propId == PROP_BLOOM_BLUR_RADIUS) { *pValue = m_blurRadius; return S_OK; }
        return E_INVALIDARG;
    }

    HRESULT SetInt(uint32_t propId, int32_t value) override {
        if (propId == PROP_BLOOM_TINT) { m_tint = static_cast<uint32_t>(value); m_dirty = true; return S_OK; }
        return E_INVALIDARG;
    }

    HRESULT GetInt(uint32_t propId, int32_t* pValue) const override {
        if (!pValue) return E_POINTER;
        if (propId == PROP_BLOOM_TINT) { *pValue = static_cast<int32_t>(m_tint); return S_OK; }
        return E_INVALIDARG;
    }

    HRESULT SetValue(uint32_t, const void*, uint32_t) override { return E_NOTIMPL; }
    HRESULT GetValue(uint32_t, void*, uint32_t) const override { return E_NOTIMPL; }

protected:
    HRESULT Execute(IPrismImage** ppOutput) override {
        ComPtr<IPrismImage> spInput;
        HRESULT hr = ResolveInput(0, spInput.Put());
        if (FAILED(hr) || !spInput.Get()) return E_FAIL;

        uint32_t w = spInput->GetWidth();
        uint32_t h = spInput->GetHeight();

        // Step 1: Bright pass extraction
        ComPtr<IPrismImage> spBright(new PrismImageImpl(w, h));
        for (uint32_t y = 0; y < h; ++y) {
            for (uint32_t x = 0; x < w; ++x) {
                PixelRGBA c = PixelRGBA::FromU32(spInput->GetPixel(x, y));
                float lum = c.Luminance();
                if (lum > m_threshold) {
                    float factor = (lum - m_threshold) / (1.0f - m_threshold + 1e-5f);
                    spBright->SetPixel(x, y, PixelRGBA{ c.r * factor, c.g * factor, c.b * factor, c.a }.ToU32());
                } else {
                    spBright->SetPixel(x, y, 0x00000000);
                }
            }
        }

        // Step 2: Gaussian blur on bright pass
        ComPtr<IPrismEffect> spBlur(new PrismGaussianBlurEffect());
        spBlur->SetInput(0, spBright.Get());
        spBlur->SetFloat(PROP_GAUSSIAN_STANDARD_DEVIATION, m_blurRadius);

        ComPtr<IPrismImage> spBlurred;
        hr = spBlur->GetOutput(spBlurred.Put());
        if (FAILED(hr) || !spBlurred.Get()) return hr;

        // Step 3: Recombination (Additive blend with intensity and tint)
        PixelRGBA tint = PixelRGBA::FromU32(m_tint);
        auto* pOutImg = new PrismImageImpl(w, h);

        for (uint32_t y = 0; y < h; ++y) {
            for (uint32_t x = 0; x < w; ++x) {
                PixelRGBA orig = PixelRGBA::FromU32(spInput->GetPixel(x, y));
                PixelRGBA glow = PixelRGBA::FromU32(spBlurred->GetPixel(x, y));

                float r = orig.r + glow.r * m_intensity * tint.r;
                float g = orig.g + glow.g * m_intensity * tint.g;
                float b = orig.b + glow.b * m_intensity * tint.b;
                float a = std::max(orig.a, glow.a);

                pOutImg->SetPixel(x, y, PixelRGBA{ r, g, b, a }.ToU32());
            }
        }

        *ppOutput = pOutImg;
        return S_OK;
    }
};

// ============================================================================
// 10. Drop Shadow Effect
// ============================================================================

class PrismDropShadowEffect : public PrismEffectBase {
private:
    float m_dx{ 4.0f };
    float m_dy{ 4.0f };
    float m_blurRadius{ 3.0f };
    uint32_t m_shadowColor{ 0xFF000000 };
    float m_opacity{ 0.7f };

public:
    PrismDropShadowEffect() : PrismEffectBase(1) {}

    GUID GetEffectId() const override { return CLSID_PrismDropShadowEffect; }
    const char* GetEffectName() const override { return "PrismDropShadowEffect"; }

    HRESULT SetFloat(uint32_t propId, float value) override {
        if (propId == PROP_SHADOW_OFFSET_X) { m_dx = value; m_dirty = true; return S_OK; }
        if (propId == PROP_SHADOW_OFFSET_Y) { m_dy = value; m_dirty = true; return S_OK; }
        if (propId == PROP_SHADOW_BLUR_RADIUS) { m_blurRadius = std::max(0.1f, value); m_dirty = true; return S_OK; }
        if (propId == PROP_SHADOW_OPACITY) { m_opacity = std::clamp(value, 0.0f, 1.0f); m_dirty = true; return S_OK; }
        return E_INVALIDARG;
    }

    HRESULT GetFloat(uint32_t propId, float* pValue) const override {
        if (!pValue) return E_POINTER;
        if (propId == PROP_SHADOW_OFFSET_X) { *pValue = m_dx; return S_OK; }
        if (propId == PROP_SHADOW_OFFSET_Y) { *pValue = m_dy; return S_OK; }
        if (propId == PROP_SHADOW_BLUR_RADIUS) { *pValue = m_blurRadius; return S_OK; }
        if (propId == PROP_SHADOW_OPACITY) { *pValue = m_opacity; return S_OK; }
        return E_INVALIDARG;
    }

    HRESULT SetInt(uint32_t propId, int32_t value) override {
        if (propId == PROP_SHADOW_COLOR) { m_shadowColor = static_cast<uint32_t>(value); m_dirty = true; return S_OK; }
        return E_INVALIDARG;
    }

    HRESULT GetInt(uint32_t propId, int32_t* pValue) const override {
        if (!pValue) return E_POINTER;
        if (propId == PROP_SHADOW_COLOR) { *pValue = static_cast<int32_t>(m_shadowColor); return S_OK; }
        return E_INVALIDARG;
    }

    HRESULT SetValue(uint32_t, const void*, uint32_t) override { return E_NOTIMPL; }
    HRESULT GetValue(uint32_t, void*, uint32_t) const override { return E_NOTIMPL; }

protected:
    HRESULT Execute(IPrismImage** ppOutput) override {
        ComPtr<IPrismImage> spInput;
        HRESULT hr = ResolveInput(0, spInput.Put());
        if (FAILED(hr) || !spInput.Get()) return E_FAIL;

        uint32_t w = spInput->GetWidth();
        uint32_t h = spInput->GetHeight();

        // 1. Create alpha silhouette image
        ComPtr<IPrismImage> spAlpha(new PrismImageImpl(w, h));
        PixelRGBA sColor = PixelRGBA::FromU32(m_shadowColor);

        for (uint32_t y = 0; y < h; ++y) {
            for (uint32_t x = 0; x < w; ++x) {
                PixelRGBA c = PixelRGBA::FromU32(spInput->GetPixel(x, y));
                float alpha = c.a * m_opacity;
                spAlpha->SetPixel(x, y, PixelRGBA{ sColor.r, sColor.g, sColor.b, alpha }.ToU32());
            }
        }

        // 2. Blur the shadow silhouette
        ComPtr<IPrismEffect> spBlur(new PrismGaussianBlurEffect());
        spBlur->SetInput(0, spAlpha.Get());
        spBlur->SetFloat(PROP_GAUSSIAN_STANDARD_DEVIATION, m_blurRadius);

        ComPtr<IPrismImage> spBlurred;
        hr = spBlur->GetOutput(spBlurred.Put());
        if (FAILED(hr) || !spBlurred.Get()) return hr;

        // 3. Composite blurred shadow behind original image with offset
        auto* pOutImg = new PrismImageImpl(w, h);
        int ox = static_cast<int>(m_dx);
        int oy = static_cast<int>(m_dy);

        for (uint32_t y = 0; y < h; ++y) {
            for (uint32_t x = 0; x < w; ++x) {
                // Sample shadow at (x - ox, y - oy)
                int sx = static_cast<int>(x) - ox;
                int sy = static_cast<int>(y) - oy;
                PixelRGBA shadow{ 0, 0, 0, 0 };
                if (sx >= 0 && sx < static_cast<int>(w) && sy >= 0 && sy < static_cast<int>(h)) {
                    shadow = PixelRGBA::FromU32(spBlurred->GetPixel(sx, sy));
                }

                // Sample foreground
                PixelRGBA fg = PixelRGBA::FromU32(spInput->GetPixel(x, y));

                // Alpha composite: fg Over shadow
                float outA = fg.a + shadow.a * (1.0f - fg.a);
                float outR = (outA > 0.0f) ? (fg.r * fg.a + shadow.r * shadow.a * (1.0f - fg.a)) / outA : 0.0f;
                float outG = (outA > 0.0f) ? (fg.g * fg.a + shadow.g * shadow.a * (1.0f - fg.a)) / outA : 0.0f;
                float outB = (outA > 0.0f) ? (fg.b * fg.a + shadow.b * shadow.a * (1.0f - fg.a)) / outA : 0.0f;

                pOutImg->SetPixel(x, y, PixelRGBA{ outR, outG, outB, outA }.ToU32());
            }
        }

        *ppOutput = pOutImg;
        return S_OK;
    }
};

// ============================================================================
// 11. 3x3 Convolution Matrix Effect (Sharpen, Edge, Emboss)
// ============================================================================

class PrismConvolutionEffect : public PrismEffectBase {
private:
    std::array<float, 9> m_kernel{ 0, 0, 0, 0, 1, 0, 0, 0, 0 };
    float m_divisor{ 1.0f };
    float m_bias{ 0.0f };

public:
    PrismConvolutionEffect() : PrismEffectBase(1) {
        SetPreset(ConvolutionPreset::Sharpen);
    }

    void SetPreset(ConvolutionPreset preset) {
        switch (preset) {
        case ConvolutionPreset::Sharpen:
            m_kernel = { 0.0f, -1.0f, 0.0f, -1.0f, 5.0f, -1.0f, 0.0f, -1.0f, 0.0f };
            m_divisor = 1.0f;
            m_bias = 0.0f;
            break;
        case ConvolutionPreset::EdgeDetect:
            m_kernel = { -1.0f, -1.0f, -1.0f, -1.0f, 8.0f, -1.0f, -1.0f, -1.0f, -1.0f };
            m_divisor = 1.0f;
            m_bias = 0.0f;
            break;
        case ConvolutionPreset::Emboss:
            m_kernel = { -2.0f, -1.0f, 0.0f, -1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 2.0f };
            m_divisor = 1.0f;
            m_bias = 0.5f;
            break;
        case ConvolutionPreset::BoxBlur:
            m_kernel = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };
            m_divisor = 9.0f;
            m_bias = 0.0f;
            break;
        default:
            break;
        }
        m_dirty = true;
    }

    GUID GetEffectId() const override { return CLSID_PrismConvolutionEffect; }
    const char* GetEffectName() const override { return "PrismConvolutionEffect"; }

    HRESULT SetFloat(uint32_t propId, float value) override {
        if (propId == PROP_CONV_DIVISOR) { m_divisor = (value != 0.0f) ? value : 1.0f; m_dirty = true; return S_OK; }
        if (propId == PROP_CONV_BIAS) { m_bias = value; m_dirty = true; return S_OK; }
        return E_INVALIDARG;
    }

    HRESULT GetFloat(uint32_t propId, float* pValue) const override {
        if (!pValue) return E_POINTER;
        if (propId == PROP_CONV_DIVISOR) { *pValue = m_divisor; return S_OK; }
        if (propId == PROP_CONV_BIAS) { *pValue = m_bias; return S_OK; }
        return E_INVALIDARG;
    }

    HRESULT SetInt(uint32_t propId, int32_t value) override {
        if (propId == PROP_CONV_PRESET) {
            SetPreset(static_cast<ConvolutionPreset>(value));
            return S_OK;
        }
        return E_INVALIDARG;
    }

    HRESULT GetInt(uint32_t, int32_t*) const override { return E_NOTIMPL; }

    HRESULT SetValue(uint32_t propId, const void* data, uint32_t cbData) override {
        if (!data) return E_POINTER;
        if (propId == PROP_CONV_MATRIX_3X3 && cbData == 9 * sizeof(float)) {
            std::memcpy(m_kernel.data(), data, 9 * sizeof(float));
            m_dirty = true;
            return S_OK;
        }
        return E_INVALIDARG;
    }

    HRESULT GetValue(uint32_t propId, void* data, uint32_t cbData) const override {
        if (!data) return E_POINTER;
        if (propId == PROP_CONV_MATRIX_3X3 && cbData == 9 * sizeof(float)) {
            std::memcpy(data, m_kernel.data(), 9 * sizeof(float));
            return S_OK;
        }
        return E_INVALIDARG;
    }

protected:
    HRESULT Execute(IPrismImage** ppOutput) override {
        ComPtr<IPrismImage> spInput;
        HRESULT hr = ResolveInput(0, spInput.Put());
        if (FAILED(hr) || !spInput.Get()) return E_FAIL;

        uint32_t w = spInput->GetWidth();
        uint32_t h = spInput->GetHeight();
        auto* pOutImg = new PrismImageImpl(w, h);

        for (uint32_t y = 0; y < h; ++y) {
            for (uint32_t x = 0; x < w; ++x) {
                float r = 0, g = 0, b = 0;
                float a = PixelRGBA::FromU32(spInput->GetPixel(x, y)).a;

                for (int ky = -1; ky <= 1; ++ky) {
                    for (int kx = -1; kx <= 1; ++kx) {
                        int sx = std::clamp(static_cast<int>(x) + kx, 0, static_cast<int>(w) - 1);
                        int sy = std::clamp(static_cast<int>(y) + ky, 0, static_cast<int>(h) - 1);

                        PixelRGBA c = PixelRGBA::FromU32(spInput->GetPixel(sx, sy));
                        float wgt = m_kernel[(ky + 1) * 3 + (kx + 1)];
                        r += c.r * wgt;
                        g += c.g * wgt;
                        b += c.b * wgt;
                    }
                }

                r = (r / m_divisor) + m_bias;
                g = (g / m_divisor) + m_bias;
                b = (b / m_divisor) + m_bias;

                pOutImg->SetPixel(x, y, PixelRGBA{ r, g, b, a }.ToU32());
            }
        }

        *ppOutput = pOutImg;
        return S_OK;
    }
};

// ============================================================================
// 12. Vignette & Chromatic Aberration Effect
// ============================================================================

class PrismVignetteEffect : public PrismEffectBase {
private:
    float m_cx{ 0.5f };
    float m_cy{ 0.5f };
    float m_radius{ 0.85f };
    float m_softness{ 0.45f };

public:
    PrismVignetteEffect() : PrismEffectBase(1) {}

    GUID GetEffectId() const override { return CLSID_PrismVignetteEffect; }
    const char* GetEffectName() const override { return "PrismVignetteEffect"; }

    HRESULT SetFloat(uint32_t propId, float value) override {
        if (propId == PROP_VIGNETTE_CENTER_X) { m_cx = value; m_dirty = true; return S_OK; }
        if (propId == PROP_VIGNETTE_CENTER_Y) { m_cy = value; m_dirty = true; return S_OK; }
        if (propId == PROP_VIGNETTE_RADIUS) { m_radius = std::max(0.01f, value); m_dirty = true; return S_OK; }
        if (propId == PROP_VIGNETTE_SOFTNESS) { m_softness = std::max(0.01f, value); m_dirty = true; return S_OK; }
        return E_INVALIDARG;
    }

    HRESULT GetFloat(uint32_t propId, float* pValue) const override {
        if (!pValue) return E_POINTER;
        if (propId == PROP_VIGNETTE_CENTER_X) { *pValue = m_cx; return S_OK; }
        if (propId == PROP_VIGNETTE_CENTER_Y) { *pValue = m_cy; return S_OK; }
        if (propId == PROP_VIGNETTE_RADIUS) { *pValue = m_radius; return S_OK; }
        if (propId == PROP_VIGNETTE_SOFTNESS) { *pValue = m_softness; return S_OK; }
        return E_INVALIDARG;
    }

    HRESULT SetInt(uint32_t, int32_t) override { return E_NOTIMPL; }
    HRESULT GetInt(uint32_t, int32_t*) const override { return E_NOTIMPL; }
    HRESULT SetValue(uint32_t, const void*, uint32_t) override { return E_NOTIMPL; }
    HRESULT GetValue(uint32_t, void*, uint32_t) const override { return E_NOTIMPL; }

protected:
    HRESULT Execute(IPrismImage** ppOutput) override {
        ComPtr<IPrismImage> spInput;
        HRESULT hr = ResolveInput(0, spInput.Put());
        if (FAILED(hr) || !spInput.Get()) return E_FAIL;

        uint32_t w = spInput->GetWidth();
        uint32_t h = spInput->GetHeight();
        auto* pOutImg = new PrismImageImpl(w, h);

        float rInner = std::max(0.0f, m_radius - m_softness);
        float rOuter = m_radius;

        for (uint32_t y = 0; y < h; ++y) {
            float ny = (static_cast<float>(y) / h) - m_cy;
            for (uint32_t x = 0; x < w; ++x) {
                float nx = (static_cast<float>(x) / w) - m_cx;
                float dist = std::sqrt(nx * nx + ny * ny) * 2.0f;

                float factor = 1.0f;
                if (dist > rInner) {
                    float t = std::clamp((dist - rInner) / (rOuter - rInner + 1e-5f), 0.0f, 1.0f);
                    // Smoothstep falloff
                    factor = 1.0f - (t * t * (3.0f - 2.0f * t));
                }

                PixelRGBA c = PixelRGBA::FromU32(spInput->GetPixel(x, y));
                pOutImg->SetPixel(x, y, PixelRGBA{ c.r * factor, c.g * factor, c.b * factor, c.a }.ToU32());
            }
        }

        *ppOutput = pOutImg;
        return S_OK;
    }
};

// ============================================================================
// 13. Tone Mapping & Exposure Effect
// ============================================================================

class PrismToneMappingEffect : public PrismEffectBase {
private:
    ToneMapOperator m_op{ ToneMapOperator::ACES };
    float m_exposure{ 1.0f };

    static float ACESFilm(float x) {
        float a = 2.51f;
        float b = 0.03f;
        float c = 2.43f;
        float d = 0.59f;
        float e = 0.14f;
        return std::clamp((x * (a * x + b)) / (x * (c * x + d) + e), 0.0f, 1.0f);
    }

public:
    PrismToneMappingEffect() : PrismEffectBase(1) {}

    GUID GetEffectId() const override { return CLSID_PrismToneMappingEffect; }
    const char* GetEffectName() const override { return "PrismToneMappingEffect"; }

    HRESULT SetFloat(uint32_t propId, float value) override {
        if (propId == PROP_TONEMAP_EXPOSURE) { m_exposure = std::max(0.0f, value); m_dirty = true; return S_OK; }
        return E_INVALIDARG;
    }

    HRESULT GetFloat(uint32_t propId, float* pValue) const override {
        if (!pValue) return E_POINTER;
        if (propId == PROP_TONEMAP_EXPOSURE) { *pValue = m_exposure; return S_OK; }
        return E_INVALIDARG;
    }

    HRESULT SetInt(uint32_t propId, int32_t value) override {
        if (propId == PROP_TONEMAP_OPERATOR) { m_op = static_cast<ToneMapOperator>(value); m_dirty = true; return S_OK; }
        return E_INVALIDARG;
    }

    HRESULT GetInt(uint32_t propId, int32_t* pValue) const override {
        if (!pValue) return E_POINTER;
        if (propId == PROP_TONEMAP_OPERATOR) { *pValue = static_cast<int32_t>(m_op); return S_OK; }
        return E_INVALIDARG;
    }

    HRESULT SetValue(uint32_t, const void*, uint32_t) override { return E_NOTIMPL; }
    HRESULT GetValue(uint32_t, void*, uint32_t) const override { return E_NOTIMPL; }

protected:
    HRESULT Execute(IPrismImage** ppOutput) override {
        ComPtr<IPrismImage> spInput;
        HRESULT hr = ResolveInput(0, spInput.Put());
        if (FAILED(hr) || !spInput.Get()) return E_FAIL;

        uint32_t w = spInput->GetWidth();
        uint32_t h = spInput->GetHeight();
        auto* pOutImg = new PrismImageImpl(w, h);

        for (uint32_t y = 0; y < h; ++y) {
            for (uint32_t x = 0; x < w; ++x) {
                PixelRGBA c = PixelRGBA::FromU32(spInput->GetPixel(x, y));
                float r = c.r * m_exposure;
                float g = c.g * m_exposure;
                float b = c.b * m_exposure;

                if (m_op == ToneMapOperator::ACES) {
                    r = ACESFilm(r);
                    g = ACESFilm(g);
                    b = ACESFilm(b);
                } else if (m_op == ToneMapOperator::Reinhard) {
                    r = r / (1.0f + r);
                    g = g / (1.0f + g);
                    b = b / (1.0f + b);
                } else if (m_op == ToneMapOperator::Filmic) {
                    r = std::max(0.0f, r - 0.004f);
                    r = (r * (6.2f * r + 0.5f)) / (r * (6.2f * r + 1.7f) + 0.06f);
                    g = std::max(0.0f, g - 0.004f);
                    g = (g * (6.2f * g + 0.5f)) / (g * (6.2f * g + 1.7f) + 0.06f);
                    b = std::max(0.0f, b - 0.004f);
                    b = (b * (6.2f * b + 0.5f)) / (b * (6.2f * b + 1.7f) + 0.06f);
                }

                pOutImg->SetPixel(x, y, PixelRGBA{ r, g, b, c.a }.ToU32());
            }
        }

        *ppOutput = pOutImg;
        return S_OK;
    }
};

// ============================================================================
// 14. Compositing & Blend Effect (2 Inputs: Foreground & Background)
// ============================================================================

class PrismBlendEffect : public PrismEffectBase {
private:
    EffectBlendMode m_mode{ EffectBlendMode::Normal };

public:
    PrismBlendEffect() : PrismEffectBase(2) {}

    GUID GetEffectId() const override { return CLSID_PrismBlendEffect; }
    const char* GetEffectName() const override { return "PrismBlendEffect"; }

    HRESULT SetFloat(uint32_t, float) override { return E_NOTIMPL; }
    HRESULT GetFloat(uint32_t, float*) const override { return E_NOTIMPL; }

    HRESULT SetInt(uint32_t propId, int32_t value) override {
        if (propId == PROP_BLEND_MODE) { m_mode = static_cast<EffectBlendMode>(value); m_dirty = true; return S_OK; }
        return E_INVALIDARG;
    }

    HRESULT GetInt(uint32_t propId, int32_t* pValue) const override {
        if (!pValue) return E_POINTER;
        if (propId == PROP_BLEND_MODE) { *pValue = static_cast<int32_t>(m_mode); return S_OK; }
        return E_INVALIDARG;
    }

    HRESULT SetValue(uint32_t, const void*, uint32_t) override { return E_NOTIMPL; }
    HRESULT GetValue(uint32_t, void*, uint32_t) const override { return E_NOTIMPL; }

protected:
    HRESULT Execute(IPrismImage** ppOutput) override {
        ComPtr<IPrismImage> spFg;
        ComPtr<IPrismImage> spBg;
        HRESULT hr0 = ResolveInput(0, spFg.Put());
        HRESULT hr1 = ResolveInput(1, spBg.Put());

        if (FAILED(hr0) || !spFg.Get()) return E_FAIL;
        if (FAILED(hr1) || !spBg.Get()) return E_FAIL;

        uint32_t w = std::min(spFg->GetWidth(), spBg->GetWidth());
        uint32_t h = std::min(spFg->GetHeight(), spBg->GetHeight());
        auto* pOutImg = new PrismImageImpl(w, h);

        for (uint32_t y = 0; y < h; ++y) {
            for (uint32_t x = 0; x < w; ++x) {
                PixelRGBA fg = PixelRGBA::FromU32(spFg->GetPixel(x, y));
                PixelRGBA bg = PixelRGBA::FromU32(spBg->GetPixel(x, y));

                float r = 0, g = 0, b = 0;
                switch (m_mode) {
                case EffectBlendMode::Normal:
                    r = fg.r; g = fg.g; b = fg.b;
                    break;
                case EffectBlendMode::Multiply:
                    r = fg.r * bg.r; g = fg.g * bg.g; b = fg.b * bg.b;
                    break;
                case EffectBlendMode::Screen:
                    r = 1.0f - (1.0f - fg.r) * (1.0f - bg.r);
                    g = 1.0f - (1.0f - fg.g) * (1.0f - bg.g);
                    b = 1.0f - (1.0f - fg.b) * (1.0f - bg.b);
                    break;
                case EffectBlendMode::Additive:
                    r = fg.r + bg.r; g = fg.g + bg.g; b = fg.b + bg.b;
                    break;
                case EffectBlendMode::Overlay:
                    r = (bg.r < 0.5f) ? (2.0f * bg.r * fg.r) : (1.0f - 2.0f * (1.0f - bg.r) * (1.0f - fg.r));
                    g = (bg.g < 0.5f) ? (2.0f * bg.g * fg.g) : (1.0f - 2.0f * (1.0f - bg.g) * (1.0f - fg.g));
                    b = (bg.b < 0.5f) ? (2.0f * bg.b * fg.b) : (1.0f - 2.0f * (1.0f - bg.b) * (1.0f - fg.b));
                    break;
                case EffectBlendMode::Difference:
                    r = std::abs(fg.r - bg.r); g = std::abs(fg.g - bg.g); b = std::abs(fg.b - bg.b);
                    break;
                default:
                    r = fg.r; g = fg.g; b = fg.b;
                    break;
                }

                // Alpha compositing
                float outA = fg.a + bg.a * (1.0f - fg.a);
                float outR = (outA > 0.0f) ? (r * fg.a + bg.r * bg.a * (1.0f - fg.a)) / outA : 0.0f;
                float outG = (outA > 0.0f) ? (g * fg.a + bg.g * bg.a * (1.0f - fg.a)) / outA : 0.0f;
                float outB = (outA > 0.0f) ? (b * fg.a + bg.b * bg.a * (1.0f - fg.a)) / outA : 0.0f;

                pOutImg->SetPixel(x, y, PixelRGBA{ outR, outG, outB, outA }.ToU32());
            }
        }

        *ppOutput = pOutImg;
        return S_OK;
    }
};

// ============================================================================
// 15. Chromatic Aberration Effect
// ============================================================================

class PrismChromaticAberrationEffect : public PrismEffectBase {
private:
    float m_rOffsetX{ 3.0f };
    float m_rOffsetY{ 0.0f };
    float m_bOffsetX{ -3.0f };
    float m_bOffsetY{ 0.0f };

public:
    PrismChromaticAberrationEffect() : PrismEffectBase(1) {}

    GUID GetEffectId() const override { return CLSID_PrismChromaticAberrationEffect; }
    const char* GetEffectName() const override { return "PrismChromaticAberrationEffect"; }

    HRESULT SetFloat(uint32_t propId, float value) override {
        if (propId == PROP_CHROMA_OFFSET_R_X) { m_rOffsetX = value; m_dirty = true; return S_OK; }
        if (propId == PROP_CHROMA_OFFSET_R_Y) { m_rOffsetY = value; m_dirty = true; return S_OK; }
        if (propId == PROP_CHROMA_OFFSET_B_X) { m_bOffsetX = value; m_dirty = true; return S_OK; }
        if (propId == PROP_CHROMA_OFFSET_B_Y) { m_bOffsetY = value; m_dirty = true; return S_OK; }
        return E_INVALIDARG;
    }

    HRESULT GetFloat(uint32_t propId, float* pValue) const override {
        if (!pValue) return E_POINTER;
        if (propId == PROP_CHROMA_OFFSET_R_X) { *pValue = m_rOffsetX; return S_OK; }
        if (propId == PROP_CHROMA_OFFSET_R_Y) { *pValue = m_rOffsetY; return S_OK; }
        if (propId == PROP_CHROMA_OFFSET_B_X) { *pValue = m_bOffsetX; return S_OK; }
        if (propId == PROP_CHROMA_OFFSET_B_Y) { *pValue = m_bOffsetY; return S_OK; }
        return E_INVALIDARG;
    }

    HRESULT SetInt(uint32_t, int32_t) override { return E_NOTIMPL; }
    HRESULT GetInt(uint32_t, int32_t*) const override { return E_NOTIMPL; }
    HRESULT SetValue(uint32_t, const void*, uint32_t) override { return E_NOTIMPL; }
    HRESULT GetValue(uint32_t, void*, uint32_t) const override { return E_NOTIMPL; }

protected:
    HRESULT Execute(IPrismImage** ppOutput) override {
        ComPtr<IPrismImage> spInput;
        HRESULT hr = ResolveInput(0, spInput.Put());
        if (FAILED(hr) || !spInput.Get()) return E_FAIL;

        uint32_t w = spInput->GetWidth();
        uint32_t h = spInput->GetHeight();
        auto* pOutImg = new PrismImageImpl(w, h);

        int rx = static_cast<int>(m_rOffsetX);
        int ry = static_cast<int>(m_rOffsetY);
        int bx = static_cast<int>(m_bOffsetX);
        int by = static_cast<int>(m_bOffsetY);

        for (uint32_t y = 0; y < h; ++y) {
            for (uint32_t x = 0; x < w; ++x) {
                // Red sampled with offset R
                int srx = std::clamp(static_cast<int>(x) + rx, 0, static_cast<int>(w) - 1);
                int sry = std::clamp(static_cast<int>(y) + ry, 0, static_cast<int>(h) - 1);
                float r = PixelRGBA::FromU32(spInput->GetPixel(srx, sry)).r;

                // Green sampled at center
                PixelRGBA cg = PixelRGBA::FromU32(spInput->GetPixel(x, y));
                float g = cg.g;
                float a = cg.a;

                // Blue sampled with offset B
                int sbx = std::clamp(static_cast<int>(x) + bx, 0, static_cast<int>(w) - 1);
                int sby = std::clamp(static_cast<int>(y) + by, 0, static_cast<int>(h) - 1);
                float b = PixelRGBA::FromU32(spInput->GetPixel(sbx, sby)).b;

                pOutImg->SetPixel(x, y, PixelRGBA{ r, g, b, a }.ToU32());
            }
        }

        *ppOutput = pOutImg;
        return S_OK;
    }
};

// ============================================================================
// 16. Effect Graph Implementation (Node-Based Directed Acyclic Graph)
// ============================================================================

class PrismEffectGraphImpl : public IPrismEffectGraph {
private:
    std::atomic<uint32_t> m_refCount{ 1 };
    std::vector<ComPtr<IPrismEffect>> m_nodes;
    ComPtr<IPrismEffect> m_root;

public:
    PrismEffectGraphImpl() = default;

    HRESULT QueryInterface(REFIID riid, void** ppv) override {
        if (!ppv) return E_POINTER;
        if (riid == IID_IUnknown || riid == IID_IPrismEffectGraph) {
            *ppv = static_cast<IPrismEffectGraph*>(this);
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

    HRESULT AddEffect(IPrismEffect* pEffect) override {
        if (!pEffect) return E_POINTER;
        m_nodes.push_back(ComPtr<IPrismEffect>(pEffect));
        return S_OK;
    }

    HRESULT SetRootEffect(IPrismEffect* pEffect) override {
        if (!pEffect) return E_POINTER;
        m_root = pEffect;
        return S_OK;
    }

    HRESULT Render(IPrismImage** ppOutput) override {
        if (!ppOutput) return E_POINTER;
        if (!m_root.Get()) return E_FAIL;
        return m_root->GetOutput(ppOutput);
    }

    size_t GetNodeCount() const override {
        return m_nodes.size();
    }
};

// ============================================================================
// 17. Effect Context & Factory
// ============================================================================

class PrismEffectContextImpl : public IPrismEffectContext {
private:
    std::atomic<uint32_t> m_refCount{ 1 };

public:
    PrismEffectContextImpl() = default;

    HRESULT QueryInterface(REFIID riid, void** ppv) override {
        if (!ppv) return E_POINTER;
        if (riid == IID_IUnknown || riid == IID_IPrismEffectContext) {
            *ppv = static_cast<IPrismEffectContext*>(this);
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

    HRESULT CreateImage(uint32_t width, uint32_t height, IPrismImage** ppImage) override {
        if (!ppImage) return E_POINTER;
        *ppImage = new PrismImageImpl(width, height);
        return S_OK;
    }

    HRESULT CreateImageFromPixels(uint32_t width, uint32_t height, const uint32_t* pPixels, IPrismImage** ppImage) override {
        if (!ppImage || !pPixels) return E_POINTER;
        *ppImage = new PrismImageImpl(width, height, pPixels);
        return S_OK;
    }

    HRESULT CreateEffect(const GUID& effectId, IPrismEffect** ppEffect) override {
        if (!ppEffect) return E_POINTER;

        if (effectId == CLSID_PrismGaussianBlurEffect) {
            *ppEffect = new PrismGaussianBlurEffect();
            return S_OK;
        }
        if (effectId == CLSID_PrismColorMatrixEffect) {
            *ppEffect = new PrismColorMatrixEffect();
            return S_OK;
        }
        if (effectId == CLSID_PrismBloomEffect) {
            *ppEffect = new PrismBloomEffect();
            return S_OK;
        }
        if (effectId == CLSID_PrismDropShadowEffect) {
            *ppEffect = new PrismDropShadowEffect();
            return S_OK;
        }
        if (effectId == CLSID_PrismConvolutionEffect) {
            *ppEffect = new PrismConvolutionEffect();
            return S_OK;
        }
        if (effectId == CLSID_PrismVignetteEffect) {
            *ppEffect = new PrismVignetteEffect();
            return S_OK;
        }
        if (effectId == CLSID_PrismToneMappingEffect) {
            *ppEffect = new PrismToneMappingEffect();
            return S_OK;
        }
        if (effectId == CLSID_PrismBlendEffect) {
            *ppEffect = new PrismBlendEffect();
            return S_OK;
        }
        if (effectId == CLSID_PrismChromaticAberrationEffect) {
            *ppEffect = new PrismChromaticAberrationEffect();
            return S_OK;
        }

        *ppEffect = nullptr;
        return E_NOINTERFACE;
    }

    HRESULT CreateEffectGraph(IPrismEffectGraph** ppGraph) override {
        if (!ppGraph) return E_POINTER;
        *ppGraph = new PrismEffectGraphImpl();
        return S_OK;
    }
};

// Standalone C-style Factory API
inline HRESULT PrismCreateEffectContext(IPrismEffectContext** ppContext) {
    if (!ppContext) return E_POINTER;
    *ppContext = new PrismEffectContextImpl();
    return S_OK;
}

inline HRESULT PrismCreateEffect(const GUID& effectId, IPrismEffect** ppEffect) {
    if (!ppEffect) return E_POINTER;
    PrismEffectContextImpl ctx;
    return ctx.CreateEffect(effectId, ppEffect);
}

inline HRESULT PrismCreateImage(uint32_t width, uint32_t height, const uint32_t* pPixels, IPrismImage** ppImage) {
    if (!ppImage) return E_POINTER;
    *ppImage = new PrismImageImpl(width, height, pPixels);
    return S_OK;
}

} // namespace prismx::effects
