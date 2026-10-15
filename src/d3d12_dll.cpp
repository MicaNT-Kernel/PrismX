// ============================================================================
// PrismX: d3d12.dll — Official Microsoft Direct3D 12 Shared Library Binary
// ============================================================================

#include "prismx/directx_system32_dll_exports.hpp"

#if defined(_WIN32)
#define PRISMX_DLLEXPORT __declspec(dllexport)
#else
#define PRISMX_DLLEXPORT __attribute__((visibility("default")))
#endif

extern "C" {

PRISMX_DLLEXPORT prismx::HRESULT D3D12CreateDevice(
    prismx::IUnknown* pAdapter,
    uint32_t MinimumFeatureLevel,
    const prismx::IID& riid,
    void** ppDevice)
{
    return prismx::system32::Export_D3D12CreateDevice(pAdapter, MinimumFeatureLevel, riid, ppDevice);
}

PRISMX_DLLEXPORT prismx::HRESULT D3D12GetInterface(
    const prismx::IID& rclsid,
    const prismx::IID& riid,
    void** ppvDebug)
{
    return prismx::system32::Export_D3D12GetInterface(rclsid, riid, ppvDebug);
}

PRISMX_DLLEXPORT prismx::HRESULT D3D12GetDebugInterface(
    const prismx::IID& riid,
    void** ppvDebug)
{
    return prismx::system32::Export_D3D12GetDebugInterface(riid, ppvDebug);
}

PRISMX_DLLEXPORT prismx::HRESULT D3D12SerializeRootSignature(
    const void* pRootSignature,
    uint32_t Version,
    void** ppBlob,
    void** ppErrorBlob)
{
    return prismx::system32::Export_D3D12SerializeRootSignature(pRootSignature, Version, ppBlob, ppErrorBlob);
}

PRISMX_DLLEXPORT prismx::HRESULT D3D12SerializeVersionedRootSignature(
    const void* pRootSignature,
    void** ppBlob,
    void** ppErrorBlob)
{
    return prismx::system32::Export_D3D12SerializeVersionedRootSignature(pRootSignature, ppBlob, ppErrorBlob);
}

} // extern "C"
