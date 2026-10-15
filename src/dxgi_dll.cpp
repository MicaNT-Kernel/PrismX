// ============================================================================
// PrismX: dxgi.dll — Official Microsoft DXGI 1.0–1.6 Shared Library Binary
// ============================================================================

#include "prismx/directx_system32_dll_exports.hpp"

#if defined(_WIN32)
#define PRISMX_DLLEXPORT __declspec(dllexport)
#else
#define PRISMX_DLLEXPORT __attribute__((visibility("default")))
#endif

extern "C" {

PRISMX_DLLEXPORT prismx::HRESULT CreateDXGIFactory(
    const prismx::IID& riid,
    void** ppFactory)
{
    return prismx::system32::Export_CreateDXGIFactory(riid, ppFactory);
}

PRISMX_DLLEXPORT prismx::HRESULT CreateDXGIFactory1(
    const prismx::IID& riid,
    void** ppFactory)
{
    return prismx::system32::Export_CreateDXGIFactory1(riid, ppFactory);
}

PRISMX_DLLEXPORT prismx::HRESULT CreateDXGIFactory2(
    uint32_t Flags,
    const prismx::IID& riid,
    void** ppFactory)
{
    return prismx::system32::Export_CreateDXGIFactory2(Flags, riid, ppFactory);
}

PRISMX_DLLEXPORT prismx::HRESULT DXGIGetDebugInterface1(
    uint32_t Flags,
    const prismx::IID& riid,
    void** pDebug)
{
    return prismx::system32::Export_DXGIGetDebugInterface1(Flags, riid, pDebug);
}

PRISMX_DLLEXPORT prismx::HRESULT DXGIDeclareAdapterRemovalSupport()
{
    return prismx::system32::Export_DXGIDeclareAdapterRemovalSupport();
}

} // extern "C"
