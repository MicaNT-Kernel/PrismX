#include "../include/prismx/vulkan1_opengl32_system32_abi.hpp"

#if defined(_WIN32)
#define PRISMX_DLL_EXPORT extern "C" __declspec(dllexport)
#else
#define PRISMX_DLL_EXPORT extern "C" __attribute__((visibility("default")))
#endif

PRISMX_DLL_EXPORT prismx::VulkanOpenGLSystem32::HGLRC wglCreateContext(
    prismx::VulkanOpenGLSystem32::HDC hdc) {
    return prismx::VulkanOpenGLSystem32::wglCreateContext(hdc);
}

PRISMX_DLL_EXPORT int32_t wglDeleteContext(
    prismx::VulkanOpenGLSystem32::HGLRC hglrc) {
    return prismx::VulkanOpenGLSystem32::wglDeleteContext(hglrc);
}

PRISMX_DLL_EXPORT int32_t wglMakeCurrent(
    prismx::VulkanOpenGLSystem32::HDC hdc,
    prismx::VulkanOpenGLSystem32::HGLRC hglrc) {
    return prismx::VulkanOpenGLSystem32::wglMakeCurrent(hdc, hglrc);
}

PRISMX_DLL_EXPORT prismx::VulkanOpenGLSystem32::HGLRC wglGetCurrentContext() {
    return prismx::VulkanOpenGLSystem32::wglGetCurrentContext();
}

PRISMX_DLL_EXPORT void* wglGetProcAddress(const char* lpszProc) {
    return prismx::VulkanOpenGLSystem32::wglGetProcAddress(lpszProc);
}

PRISMX_DLL_EXPORT int32_t wglSwapBuffers(
    prismx::VulkanOpenGLSystem32::HDC hdc) {
    return prismx::VulkanOpenGLSystem32::wglSwapBuffers(hdc);
}

PRISMX_DLL_EXPORT const uint8_t* glGetString(uint32_t name) {
    return prismx::VulkanOpenGLSystem32::glGetString(name);
}

PRISMX_DLL_EXPORT uint32_t glGetError() {
    return prismx::VulkanOpenGLSystem32::glGetError();
}

PRISMX_DLL_EXPORT void glViewport(int32_t x, int32_t y, int32_t width, int32_t height) {
    prismx::VulkanOpenGLSystem32::glViewport(x, y, width, height);
}

PRISMX_DLL_EXPORT void glClearColor(float r, float g, float b, float a) {
    prismx::VulkanOpenGLSystem32::glClearColor(r, g, b, a);
}

PRISMX_DLL_EXPORT void glClear(uint32_t mask) {
    prismx::VulkanOpenGLSystem32::glClear(mask);
}
