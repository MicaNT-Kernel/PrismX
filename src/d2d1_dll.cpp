// ============================================================================
// PrismX: d2d1.dll — Official Microsoft Direct2D 1.3 Shared Library Binary
// ============================================================================

#include "prismx/directx_system32_dll_exports.hpp"

#if defined(_WIN32)
#define PRISMX_DLLEXPORT __declspec(dllexport)
#else
#define PRISMX_DLLEXPORT __attribute__((visibility("default")))
#endif

extern "C" {

PRISMX_DLLEXPORT prismx::HRESULT D2D1CreateFactory(
    uint32_t factoryType,
    const prismx::IID& riid,
    const void* pFactoryOptions,
    void** ppIFactory)
{
    return prismx::system32::Export_D2D1CreateFactory(factoryType, riid, pFactoryOptions, ppIFactory);
}

PRISMX_DLLEXPORT prismx::HRESULT D2D1CreateDevice(
    prismx::IDXGIDevice* dxgiDevice,
    const void* creationProperties,
    prismx::D2DWriteCompCom::ID2D1Device** d2dDevice)
{
    return prismx::system32::Export_D2D1CreateDevice(dxgiDevice, creationProperties, d2dDevice);
}

PRISMX_DLLEXPORT prismx::HRESULT D2D1CreateDeviceContext(
    prismx::IDXGISurface* dxgiSurface,
    const void* creationProperties,
    prismx::D2DWriteCompCom::ID2D1DeviceContext** d2dDeviceContext)
{
    return prismx::system32::Export_D2D1CreateDeviceContext(dxgiSurface, creationProperties, d2dDeviceContext);
}

PRISMX_DLLEXPORT void D2D1MakeRotateMatrix(
    float angle,
    prismx::D2DWriteCompCom::D2D1_POINT_2F center,
    prismx::D2DWriteCompCom::D2D1_MATRIX_3X2_F* matrix)
{
    prismx::system32::Export_D2D1MakeRotateMatrix(angle, center, matrix);
}

PRISMX_DLLEXPORT int32_t D2D1IsMatrixInvertible(
    const prismx::D2DWriteCompCom::D2D1_MATRIX_3X2_F* matrix)
{
    return prismx::system32::Export_D2D1IsMatrixInvertible(matrix);
}

PRISMX_DLLEXPORT int32_t D2D1InvertMatrix(
    prismx::D2DWriteCompCom::D2D1_MATRIX_3X2_F* matrix)
{
    return prismx::system32::Export_D2D1InvertMatrix(matrix);
}

} // extern "C"
