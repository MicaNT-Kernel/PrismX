#include "../include/prismx/directx_system32_dll_exports.hpp"

#if defined(_WIN32)
#define PRISMX_DLL_EXPORT extern "C" __declspec(dllexport)
#else
#define PRISMX_DLL_EXPORT extern "C" __attribute__((visibility("default")))
#endif

PRISMX_DLL_EXPORT prismx::HRESULT D3D10CreateDevice1(
    prismx::IDXGIAdapter* pAdapter,
    uint32_t DriverType,
    void* Software,
    uint32_t Flags,
    uint32_t HardwareLevel,
    uint32_t SDKVersion,
    prismx::D3D10DSoundDDrawMFCom::ID3D10Device1** ppDevice) {
    return prismx::system32::Export_D3D10CreateDevice1(
        pAdapter, DriverType, Software, Flags, HardwareLevel, SDKVersion, ppDevice);
}

PRISMX_DLL_EXPORT prismx::HRESULT D3D10CreateDeviceAndSwapChain1(
    prismx::IDXGIAdapter* pAdapter,
    uint32_t DriverType,
    void* Software,
    uint32_t Flags,
    uint32_t HardwareLevel,
    uint32_t SDKVersion,
    const void* pSwapChainDesc,
    prismx::IDXGISwapChain** ppSwapChain,
    prismx::D3D10DSoundDDrawMFCom::ID3D10Device1** ppDevice) {
    return prismx::system32::Export_D3D10CreateDeviceAndSwapChain1(
        pAdapter, DriverType, Software, Flags, HardwareLevel, SDKVersion, pSwapChainDesc, ppSwapChain, ppDevice);
}

PRISMX_DLL_EXPORT prismx::HRESULT D3D10CreateDevice(
    prismx::IDXGIAdapter* pAdapter,
    uint32_t DriverType,
    void* Software,
    uint32_t Flags,
    uint32_t SDKVersion,
    prismx::D3D10DSoundDDrawMFCom::ID3D10Device** ppDevice) {
    return prismx::system32::Export_D3D10CreateDevice(
        pAdapter, DriverType, Software, Flags, SDKVersion, ppDevice);
}

PRISMX_DLL_EXPORT prismx::HRESULT D3D10CreateBlob(
    size_t NumBytes,
    void** ppBuffer) {
    return prismx::system32::Export_D3DCreateBlob(NumBytes, ppBuffer);
}
