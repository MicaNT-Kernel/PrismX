#include "../include/prismx/directx_system32_dll_exports.hpp"

#if defined(_WIN32)
#define PRISMX_DLL_EXPORT extern "C" __declspec(dllexport)
#else
#define PRISMX_DLL_EXPORT extern "C" __attribute__((visibility("default")))
#endif

PRISMX_DLL_EXPORT prismx::HRESULT DirectSoundCreate8(
    const prismx::IID* lpcGuidDevice,
    prismx::D3D10DSoundDDrawMFCom::IDirectSound8** ppDS8,
    prismx::IUnknown* pUnkOuter) {
    return prismx::system32::Export_DirectSoundCreate8(lpcGuidDevice, ppDS8, pUnkOuter);
}

PRISMX_DLL_EXPORT prismx::HRESULT DirectSoundCreate(
    const prismx::IID* lpcGuidDevice,
    prismx::D3D10DSoundDDrawMFCom::IDirectSound8** ppDS,
    prismx::IUnknown* pUnkOuter) {
    return prismx::system32::Export_DirectSoundCreate(lpcGuidDevice, ppDS, pUnkOuter);
}
