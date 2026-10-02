// ============================================================================
// PrismX: Sovereign Graphics Architecture - Core Types & COM Foundations
// 
// Strict Clean-Room Implementation in ISO C++23
// ============================================================================

#pragma once

#include <cstdint>
#include <cstring>
#include <memory>
#include <string>

namespace prismx {

// ============================================================================
// Basic Window & Display Geometries
// ============================================================================

#ifndef _WINDEF_
struct RECT {
    int32_t left;
    int32_t top;
    int32_t right;
    int32_t bottom;
};

struct POINT {
    int32_t x;
    int32_t y;
};
#endif

#ifndef _NTDEF_
struct LUID {
    uint32_t LowPart;
    int32_t  HighPart;
};
#endif

// ============================================================================
// Standard COM Result Codes & Macros
// ============================================================================

using HRESULT = int32_t;

inline constexpr HRESULT S_OK            = 0L;
inline constexpr HRESULT S_FALSE         = 1L;
inline constexpr HRESULT E_FAIL          = static_cast<HRESULT>(0x80004005L);
inline constexpr HRESULT E_INVALIDARG    = static_cast<HRESULT>(0x80070057L);
inline constexpr HRESULT E_OUTOFMEMORY   = static_cast<HRESULT>(0x8007000EL);
inline constexpr HRESULT E_NOTIMPL       = static_cast<HRESULT>(0x80004001L);
inline constexpr HRESULT E_NOINTERFACE   = static_cast<HRESULT>(0x80004002L);
inline constexpr HRESULT E_POINTER       = static_cast<HRESULT>(0x80004003L);

constexpr bool SUCCEEDED(HRESULT hr) noexcept { return hr >= 0; }
constexpr bool FAILED(HRESULT hr) noexcept    { return hr < 0; }

// ============================================================================
// Globally Unique Identifier (GUID / IID)
// ============================================================================

struct IID {
    uint32_t Data1;
    uint16_t Data2;
    uint16_t Data3;
    uint8_t  Data4[8];

    constexpr bool operator==(const IID& other) const noexcept {
        if (Data1 != other.Data1 || Data2 != other.Data2 || Data3 != other.Data3) return false;
        for (int i = 0; i < 8; ++i) {
            if (Data4[i] != other.Data4[i]) return false;
        }
        return true;
    }

    constexpr bool operator!=(const IID& other) const noexcept {
        return !(*this == other);
    }
};

using GUID = IID;

inline constexpr IID IID_IUnknown = 
    { 0x00000000, 0x0000, 0x0000, { 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46 } };

// ============================================================================
// IUnknown Base COM Interface
// ============================================================================

class IUnknown {
public:
    virtual HRESULT QueryInterface(const IID& riid, void** ppvObject) = 0;
    virtual uint32_t AddRef() = 0;
    virtual uint32_t Release() = 0;
    virtual ~IUnknown() = default;
};

// ============================================================================
// ComPtr - Lightweight C++23 RAII Smart Pointer for COM Interfaces
// ============================================================================

template <typename T>
class ComPtr {
public:
    ComPtr() noexcept : m_ptr(nullptr) {}
    ComPtr(std::nullptr_t) noexcept : m_ptr(nullptr) {}
    
    explicit ComPtr(T* ptr) noexcept : m_ptr(ptr) {
        if (m_ptr) m_ptr->AddRef();
    }

    ComPtr(const ComPtr& other) noexcept : m_ptr(other.m_ptr) {
        if (m_ptr) m_ptr->AddRef();
    }

    ComPtr(ComPtr&& other) noexcept : m_ptr(other.m_ptr) {
        other.m_ptr = nullptr;
    }

    ~ComPtr() {
        Reset();
    }

    ComPtr& operator=(std::nullptr_t) noexcept {
        Reset();
        return *this;
    }

    ComPtr& operator=(const ComPtr& other) noexcept {
        if (this != &other) {
            Reset();
            m_ptr = other.m_ptr;
            if (m_ptr) m_ptr->AddRef();
        }
        return *this;
    }

    ComPtr& operator=(ComPtr&& other) noexcept {
        if (this != &other) {
            Reset();
            m_ptr = other.m_ptr;
            other.m_ptr = nullptr;
        }
        return *this;
    }

    T* Get() const noexcept { return m_ptr; }
    T* operator->() const noexcept { return m_ptr; }
    T& operator*() const noexcept { return *m_ptr; }
    T** GetAddressOf() noexcept { return &m_ptr; }
    T** ReleaseAndGetAddressOf() noexcept {
        Reset();
        return &m_ptr;
    }

    void** PutVoid() noexcept {
        Reset();
        return reinterpret_cast<void**>(&m_ptr);
    }

    void Reset() noexcept {
        if (m_ptr) {
            T* temp = m_ptr;
            m_ptr = nullptr;
            temp->Release();
        }
    }

    T* Detach() noexcept {
        T* temp = m_ptr;
        m_ptr = nullptr;
        return temp;
    }

    void Attach(T* ptr) noexcept {
        Reset();
        m_ptr = ptr;
    }

    explicit operator bool() const noexcept { return m_ptr != nullptr; }

private:
    T* m_ptr{ nullptr };
};

} // namespace prismx
