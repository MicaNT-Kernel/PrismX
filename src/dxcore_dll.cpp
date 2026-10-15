#include "../include/prismx/dxcore_com_abi.hpp"

#if defined(_WIN32)
#define PRISMX_DLL_EXPORT extern "C" __declspec(dllexport)
#else
#define PRISMX_DLL_EXPORT extern "C" __attribute__((visibility("default")))
#endif

PRISMX_DLL_EXPORT prismx::HRESULT DXCoreCreateAdapterFactory(
    const prismx::GUID* riid,
    void** ppvFactory) {
    if (!riid) return prismx::E_INVALIDARG;
    return prismx::DXCoreComAbi::DXCoreCreateAdapterFactory(*riid, ppvFactory);
}
