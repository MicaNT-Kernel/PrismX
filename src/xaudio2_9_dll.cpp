// ============================================================================
// PrismX: xaudio2_9.dll — Official Microsoft XAudio2 2.9 Shared Library Binary
// ============================================================================

#include "prismx/directx_system32_dll_exports.hpp"

#if defined(_WIN32)
#define PRISMX_DLLEXPORT __declspec(dllexport)
#else
#define PRISMX_DLLEXPORT __attribute__((visibility("default")))
#endif

extern "C" {

PRISMX_DLLEXPORT prismx::HRESULT XAudio2Create(
    prismx::XAudioDInputCom::IXAudio2** ppXAudio2,
    uint32_t Flags,
    uint32_t XAudio2Processor)
{
    return prismx::system32::Export_XAudio2Create(ppXAudio2, Flags, XAudio2Processor);
}

PRISMX_DLLEXPORT prismx::HRESULT CreateAudioVolumeMeter(prismx::IUnknown** ppApo) {
    return prismx::system32::Export_CreateAudioVolumeMeter(ppApo);
}

PRISMX_DLLEXPORT prismx::HRESULT CreateAudioReverb(prismx::IUnknown** ppApo) {
    return prismx::system32::Export_CreateAudioReverb(ppApo);
}

} // extern "C"
