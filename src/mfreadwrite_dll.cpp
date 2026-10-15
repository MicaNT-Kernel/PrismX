#include "../include/prismx/mfplat_mfreadwrite_com_abi.hpp"

#if defined(_WIN32)
#define PRISMX_DLL_EXPORT extern "C" __declspec(dllexport)
#else
#define PRISMX_DLL_EXPORT extern "C" __attribute__((visibility("default")))
#endif

PRISMX_DLL_EXPORT prismx::HRESULT MFCreateSourceReaderFromURL(
    const wchar_t* pwszURL,
    prismx::MediaFoundationCom::IMFAttributes* pAttributes,
    prismx::MediaFoundationCom::IMFSourceReader** ppSourceReader) {
    return prismx::MediaFoundationCom::MFCreateSourceReaderFromURL(pwszURL, pAttributes, ppSourceReader);
}

PRISMX_DLL_EXPORT prismx::HRESULT MFCreateSourceReaderFromByteStream(
    prismx::IUnknown* pByteStream,
    prismx::MediaFoundationCom::IMFAttributes* pAttributes,
    prismx::MediaFoundationCom::IMFSourceReader** ppSourceReader) {
    return prismx::MediaFoundationCom::MFCreateSourceReaderFromByteStream(pByteStream, pAttributes, ppSourceReader);
}

PRISMX_DLL_EXPORT prismx::HRESULT MFCreateSinkWriterFromURL(
    const wchar_t* pwszOutputURL,
    prismx::IUnknown* pByteStream,
    prismx::MediaFoundationCom::IMFAttributes* pAttributes,
    prismx::MediaFoundationCom::IMFSinkWriter** ppSinkWriter) {
    return prismx::MediaFoundationCom::MFCreateSinkWriterFromURL(
        pwszOutputURL, pByteStream, pAttributes, ppSinkWriter);
}
