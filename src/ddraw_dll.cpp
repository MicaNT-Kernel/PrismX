#include "../include/prismx/directx_system32_dll_exports.hpp"

#if defined(_WIN32)
#define PRISMX_DLL_EXPORT extern "C" __declspec(dllexport)
#else
#define PRISMX_DLL_EXPORT extern "C" __attribute__((visibility("default")))
#endif

PRISMX_DLL_EXPORT prismx::HRESULT DirectDrawCreateEx(
    const prismx::IID* lpGuid,
    void** lplpDD,
    const prismx::IID* iid,
    prismx::IUnknown* pUnkOuter) {
    if (!iid) return prismx::E_INVALIDARG;
    return prismx::system32::Export_DirectDrawCreateEx(lpGuid, lplpDD, *iid, pUnkOuter);
}

PRISMX_DLL_EXPORT prismx::HRESULT DirectDrawCreate(
    const prismx::IID* lpGUID,
    prismx::D3D10DSoundDDrawMFCom::IDirectDraw7** lplpDD,
    prismx::IUnknown* pUnkOuter) {
    return prismx::system32::Export_DirectDrawCreate(lpGUID, lplpDD, pUnkOuter);
}
