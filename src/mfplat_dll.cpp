#include "../include/prismx/mfplat_mfreadwrite_com_abi.hpp"

#if defined(_WIN32)
#define PRISMX_DLL_EXPORT extern "C" __declspec(dllexport)
#else
#define PRISMX_DLL_EXPORT extern "C" __attribute__((visibility("default")))
#endif

PRISMX_DLL_EXPORT prismx::HRESULT MFStartup(uint32_t Version, uint32_t dwFlags) {
    return prismx::MediaFoundationCom::MFStartup(Version, dwFlags);
}

PRISMX_DLL_EXPORT prismx::HRESULT MFShutdown() {
    return prismx::MediaFoundationCom::MFShutdown();
}

PRISMX_DLL_EXPORT prismx::HRESULT MFCreateAttributes(
    prismx::MediaFoundationCom::IMFAttributes** ppMFAttributes,
    uint32_t cInitialSize) {
    return prismx::MediaFoundationCom::MFCreateAttributes(ppMFAttributes, cInitialSize);
}

PRISMX_DLL_EXPORT prismx::HRESULT MFCreateMediaType(
    prismx::MediaFoundationCom::IMFMediaType** ppMFType) {
    return prismx::MediaFoundationCom::MFCreateMediaType(ppMFType);
}

PRISMX_DLL_EXPORT prismx::HRESULT MFCreateMemoryBuffer(
    uint32_t cbMaxLength,
    prismx::MediaFoundationCom::IMFMediaBuffer** ppBuffer) {
    return prismx::MediaFoundationCom::MFCreateMemoryBuffer(cbMaxLength, ppBuffer);
}

PRISMX_DLL_EXPORT prismx::HRESULT MFCreateSample(
    prismx::MediaFoundationCom::IMFSample** ppIMFSample) {
    return prismx::MediaFoundationCom::MFCreateSample(ppIMFSample);
}

PRISMX_DLL_EXPORT prismx::HRESULT MFCreateDXGIDeviceManager(
    uint32_t* resetToken,
    prismx::MediaFoundationCom::IMFDXGIDeviceManager** ppDeviceManager) {
    return prismx::MediaFoundationCom::MFCreateDXGIDeviceManager(resetToken, ppDeviceManager);
}
