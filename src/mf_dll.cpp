#include "../include/prismx/directx_system32_dll_exports.hpp"

#if defined(_WIN32)
#define PRISMX_DLL_EXPORT extern "C" __declspec(dllexport)
#else
#define PRISMX_DLL_EXPORT extern "C" __attribute__((visibility("default")))
#endif

PRISMX_DLL_EXPORT prismx::HRESULT MFCreateMediaSession(
    prismx::MediaFoundationCom::IMFAttributes* pConfiguration,
    prismx::D3D10DSoundDDrawMFCom::IMFMediaSession** ppMediaSession) {
    return prismx::system32::Export_MFCreateMediaSession(pConfiguration, ppMediaSession);
}

PRISMX_DLL_EXPORT prismx::HRESULT MFCreateTopology(
    prismx::D3D10DSoundDDrawMFCom::IMFTopology** ppTopo) {
    return prismx::system32::Export_MFCreateTopology(ppTopo);
}
