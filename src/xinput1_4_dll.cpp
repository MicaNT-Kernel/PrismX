// ============================================================================
// PrismX: xinput1_4.dll — Official Microsoft XInput 1.4 Gamepad Shared Library
// ============================================================================

#include "prismx/directx_system32_dll_exports.hpp"

#if defined(_WIN32)
#define PRISMX_DLLEXPORT __declspec(dllexport)
#else
#define PRISMX_DLLEXPORT __attribute__((visibility("default")))
#endif

extern "C" {

PRISMX_DLLEXPORT uint32_t XInputGetState(
    uint32_t dwUserIndex,
    void* pState)
{
    return prismx::system32::Export_XInputGetState(dwUserIndex, pState);
}

PRISMX_DLLEXPORT uint32_t XInputSetState(
    uint32_t dwUserIndex,
    void* pVibration)
{
    return prismx::system32::Export_XInputSetState(dwUserIndex, pVibration);
}

} // extern "C"
