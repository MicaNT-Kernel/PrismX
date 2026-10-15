// ============================================================================
// PrismX: dcomp.dll — Official Microsoft DirectComposition Shared Library Binary
// ============================================================================

#include "prismx/directx_system32_dll_exports.hpp"

#if defined(_WIN32)
#define PRISMX_DLLEXPORT __declspec(dllexport)
#else
#define PRISMX_DLLEXPORT __attribute__((visibility("default")))
#endif

extern "C" {

PRISMX_DLLEXPORT prismx::HRESULT DCompositionCreateDevice(
    prismx::IDXGIDevice* dxgiDevice,
    const prismx::IID& iid,
    void** dcompositionDevice)
{
    return prismx::system32::Export_DCompositionCreateDevice(dxgiDevice, iid, dcompositionDevice);
}

PRISMX_DLLEXPORT prismx::HRESULT DCompositionCreateDevice2(
    prismx::IUnknown* renderingDevice,
    const prismx::IID& iid,
    void** dcompositionDevice)
{
    return prismx::system32::Export_DCompositionCreateDevice2(renderingDevice, iid, dcompositionDevice);
}

PRISMX_DLLEXPORT prismx::HRESULT DCompositionCreateDevice3(
    prismx::IUnknown* renderingDevice,
    const prismx::IID& iid,
    void** dcompositionDevice)
{
    return prismx::system32::Export_DCompositionCreateDevice3(renderingDevice, iid, dcompositionDevice);
}

PRISMX_DLLEXPORT prismx::HRESULT DCompositionCreateSurfaceHandle(
    uint32_t desiredAccess,
    void* securityAttributes,
    void** surfaceHandle)
{
    return prismx::system32::Export_DCompositionCreateSurfaceHandle(desiredAccess, securityAttributes, surfaceHandle);
}

} // extern "C"
