// ============================================================================
// PrismX: d3dcompiler_47.dll — Official Microsoft HLSL FXC Compiler DLL
// ============================================================================

#include "prismx/directx_system32_dll_exports.hpp"

#if defined(_WIN32)
#define PRISMX_DLLEXPORT __declspec(dllexport)
#else
#define PRISMX_DLLEXPORT __attribute__((visibility("default")))
#endif

extern "C" {

PRISMX_DLLEXPORT prismx::HRESULT D3DCreateBlob(
    size_t Size,
    void** ppBlob)
{
    return prismx::system32::Export_D3DCreateBlob(Size, ppBlob);
}

PRISMX_DLLEXPORT prismx::HRESULT D3DCompile(
    const void* pSrcData,
    size_t SrcDataSize,
    const char* pSourceName,
    const void* pDefines,
    void* pInclude,
    const char* pEntrypoint,
    const char* pTarget,
    uint32_t Flags1,
    uint32_t Flags2,
    void** ppCode,
    void** ppErrorMsgs)
{
    return prismx::system32::Export_D3DCompile(
        pSrcData, SrcDataSize, pSourceName, pDefines, pInclude,
        pEntrypoint, pTarget, Flags1, Flags2, ppCode, ppErrorMsgs);
}

PRISMX_DLLEXPORT prismx::HRESULT D3DCompile2(
    const void* pSrcData,
    size_t SrcDataSize,
    const char* pSourceName,
    const void* pDefines,
    void* pInclude,
    const char* pEntrypoint,
    const char* pTarget,
    uint32_t Flags1,
    uint32_t Flags2,
    uint32_t SecondaryDataFlags,
    const void* pSecondaryData,
    size_t SecondaryDataSize,
    void** ppCode,
    void** ppErrorMsgs)
{
    return prismx::system32::Export_D3DCompile2(
        pSrcData, SrcDataSize, pSourceName, pDefines, pInclude,
        pEntrypoint, pTarget, Flags1, Flags2, SecondaryDataFlags,
        pSecondaryData, SecondaryDataSize, ppCode, ppErrorMsgs);
}

PRISMX_DLLEXPORT prismx::HRESULT D3DDisassemble(
    const void* pSrcData,
    size_t SrcDataSize,
    uint32_t Flags,
    const char* szComments,
    void** ppDisassembly)
{
    return prismx::system32::Export_D3DDisassemble(
        pSrcData, SrcDataSize, Flags, szComments, ppDisassembly);
}

} // extern "C"
