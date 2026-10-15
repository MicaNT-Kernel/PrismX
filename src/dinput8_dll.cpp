// ============================================================================
// PrismX: dinput8.dll — Official Microsoft DirectInput 8 Shared Library Binary
// ============================================================================

#include "prismx/directx_system32_dll_exports.hpp"

#if defined(_WIN32)
#define PRISMX_DLLEXPORT __declspec(dllexport)
#else
#define PRISMX_DLLEXPORT __attribute__((visibility("default")))
#endif

extern "C" {

PRISMX_DLLEXPORT prismx::HRESULT DirectInput8Create(
    void* hinst,
    uint32_t dwVersion,
    const prismx::IID& riidltf,
    void** ppvOut,
    prismx::IUnknown* punkOuter)
{
    return prismx::system32::Export_DirectInput8Create(hinst, dwVersion, riidltf, ppvOut, punkOuter);
}

} // extern "C"
