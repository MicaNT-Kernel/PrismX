// ============================================================================
// PrismX: dwrite.dll — Official Microsoft DirectWrite Shared Library Binary
// ============================================================================

#include "prismx/directx_system32_dll_exports.hpp"

#if defined(_WIN32)
#define PRISMX_DLLEXPORT __declspec(dllexport)
#else
#define PRISMX_DLLEXPORT __attribute__((visibility("default")))
#endif

extern "C" {

PRISMX_DLLEXPORT prismx::HRESULT DWriteCreateFactory(
    uint32_t factoryType,
    const prismx::IID& iid,
    prismx::IUnknown** factory)
{
    return prismx::system32::Export_DWriteCreateFactory(factoryType, iid, factory);
}

} // extern "C"
