// ============================================================================
// PrismX: d3d11.dll — Official Microsoft Direct3D 11 Shared Library Binary
// ============================================================================

#include "prismx/directx_system32_dll_exports.hpp"

#if defined(_WIN32)
#define PRISMX_DLLEXPORT __declspec(dllexport)
#else
#define PRISMX_DLLEXPORT __attribute__((visibility("default")))
#endif

extern "C" {

PRISMX_DLLEXPORT prismx::HRESULT D3D11CreateDevice(
    prismx::IUnknown* pAdapter,
    uint32_t DriverType,
    void* Software,
    uint32_t Flags,
    const uint32_t* pFeatureLevels,
    uint32_t FeatureLevels,
    uint32_t SDKVersion,
    void** ppDevice,
    uint32_t* pFeatureLevel,
    void** ppImmediateContext)
{
    return prismx::system32::Export_D3D11CreateDevice(
        pAdapter, DriverType, Software, Flags, pFeatureLevels,
        FeatureLevels, SDKVersion, ppDevice, pFeatureLevel, ppImmediateContext);
}

PRISMX_DLLEXPORT prismx::HRESULT D3D11CreateDeviceAndSwapChain(
    prismx::IUnknown* pAdapter,
    uint32_t DriverType,
    void* Software,
    uint32_t Flags,
    const uint32_t* pFeatureLevels,
    uint32_t FeatureLevels,
    uint32_t SDKVersion,
    const prismx::DXGI_SWAP_CHAIN_DESC* pSwapChainDesc,
    void** ppSwapChain,
    void** ppDevice,
    uint32_t* pFeatureLevel,
    void** ppImmediateContext)
{
    return prismx::system32::Export_D3D11CreateDeviceAndSwapChain(
        pAdapter, DriverType, Software, Flags, pFeatureLevels,
        FeatureLevels, SDKVersion, pSwapChainDesc, ppSwapChain,
        ppDevice, pFeatureLevel, ppImmediateContext);
}

} // extern "C"
