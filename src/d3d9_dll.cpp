// ============================================================================
// PrismX: d3d9.dll — Official Microsoft Direct3D 9 / 9Ex Shared Library Binary
// ============================================================================

#include "prismx/directx_system32_dll_exports.hpp"

#if defined(_WIN32)
#define PRISMX_DLLEXPORT __declspec(dllexport)
#else
#define PRISMX_DLLEXPORT __attribute__((visibility("default")))
#endif

extern "C" {

PRISMX_DLLEXPORT prismx::D3D9Com::IDirect3D9* Direct3DCreate9(uint32_t SDKVersion) {
    return prismx::system32::Export_Direct3DCreate9(SDKVersion);
}

PRISMX_DLLEXPORT prismx::HRESULT Direct3DCreate9Ex(
    uint32_t SDKVersion,
    prismx::D3D9Com::IDirect3D9Ex** ppD3D)
{
    return prismx::system32::Export_Direct3DCreate9Ex(SDKVersion, ppD3D);
}

PRISMX_DLLEXPORT int32_t D3DPERF_BeginEvent(uint32_t col, const wchar_t* wszName) {
    return prismx::system32::Export_D3DPERF_BeginEvent(col, wszName);
}

PRISMX_DLLEXPORT int32_t D3DPERF_EndEvent() {
    return prismx::system32::Export_D3DPERF_EndEvent();
}

PRISMX_DLLEXPORT void D3DPERF_SetMarker(uint32_t col, const wchar_t* wszName) {
    prismx::system32::Export_D3DPERF_SetMarker(col, wszName);
}

PRISMX_DLLEXPORT uint32_t D3DPERF_GetStatus() {
    return prismx::system32::Export_D3DPERF_GetStatus();
}

} // extern "C"
