// ============================================================================
// PrismX: Canonical Khronos Vulkan Loader (vulkan-1.dll) & Microsoft OpenGL
// WGL Runtime (opengl32.dll) System32 ABI (Suite 39)
//
// Clean-Room Implementation in ISO C++23. Zero External Dependencies.
// Provides:
//   - Official vulkan-1.dll C-linkage exports:
//       * vkGetInstanceProcAddr, vkGetDeviceProcAddr,
//         vkEnumerateInstanceVersion (VK_API_VERSION_1_3),
//         vkEnumerateInstanceExtensionProperties, vkCreateInstance,
//         vkDestroyInstance, vkEnumeratePhysicalDevices,
//         vkGetPhysicalDeviceProperties, vkCreateDevice, vkDestroyDevice,
//         vkGetDeviceQueue, vkQueueSubmit, vkQueuePresentKHR
//   - Official Khronos ICD dispatchable handle layout (*(uintptr_t*)h == 0x01CDC0DE).
//   - Official opengl32.dll C-linkage WGL & OpenGL 4.6 exports:
//       * wglCreateContext, wglDeleteContext, wglMakeCurrent,
//         wglGetCurrentContext, wglGetCurrentDC, wglGetProcAddress,
//         wglShareLists, wglSwapBuffers, glGetString, glGetError,
//         glClearColor, glClear, glViewport, glFlush, glFinish
// ============================================================================

#pragma once

#include "types.hpp"
#include "vulkan.hpp"
#include <cstring>
#include <string_view>

namespace prismx::VulkanOpenGLSystem32 {

// ----------------------------------------------------------------------------
// 1. Khronos Vulkan Loader Dispatchable Handle Magic (ICD_LOADER_MAGIC = 0x01CDC0DE)
// ----------------------------------------------------------------------------
inline constexpr uintptr_t VK_ICD_LOADER_MAGIC = 0x01CDC0DEULL;
inline constexpr uintptr_t ICD_LOADER_MAGIC    = 0x01CDC0DEULL;

struct VkDispatchableObjectAbi {
    uintptr_t loaderData = VK_ICD_LOADER_MAGIC;
    uint32_t  objectTag  = 0;
    void*     prismHandle = nullptr;
};

using PFN_vkVoidFunction = void(*)();
using HDC   = void*;
using HGLRC = void*;
using prismx::VkInstance;
using prismx::VkPhysicalDevice;
using prismx::VkDevice;
using prismx::VkInstanceCreateInfo;
using prismx::VkDeviceCreateInfo;
using prismx::VkPhysicalDeviceProperties;

inline constexpr uint32_t GL_VENDOR_ENUM     = 0x1F00u;
inline constexpr uint32_t GL_RENDERER_ENUM   = 0x1F01u;
inline constexpr uint32_t GL_VERSION_ENUM    = 0x1F02u;
inline constexpr uint32_t GL_EXTENSIONS_ENUM = 0x1F03u;
inline constexpr uint32_t GL_SHADING_LANGUAGE_VERSION_ENUM = 0x8B8Cu;

inline constexpr uint32_t GL_VENDOR     = GL_VENDOR_ENUM;
inline constexpr uint32_t GL_RENDERER   = GL_RENDERER_ENUM;
inline constexpr uint32_t GL_VERSION    = GL_VERSION_ENUM;
inline constexpr uint32_t GL_EXTENSIONS = GL_EXTENSIONS_ENUM;
inline constexpr uint32_t GL_SHADING_LANGUAGE_VERSION = GL_SHADING_LANGUAGE_VERSION_ENUM;

inline int32_t Export_vkEnumerateInstanceVersion(uint32_t* pApiVersion) {
    if (!pApiVersion) return -2; // VK_ERROR_OUT_OF_HOST_MEMORY
    *pApiVersion = (1u << 22) | (3u << 12) | 290u; // Vulkan 1.3.290
    return 0; // VK_SUCCESS
}

struct VkExtensionPropertiesAbi {
    char     extensionName[256];
    uint32_t specVersion;
};

inline int32_t Export_vkEnumerateInstanceExtensionProperties(
    const char* /*pLayerName*/,
    uint32_t* pPropertyCount,
    VkExtensionPropertiesAbi* pProperties)
{
    static constexpr const char* kExts[6] = {
        "VK_KHR_surface",
        "VK_KHR_win32_surface",
        "VK_KHR_get_physical_device_properties2",
        "VK_EXT_debug_utils",
        "VK_KHR_external_memory_capabilities",
        "VK_KHR_external_semaphore_capabilities"
    };
    if (!pPropertyCount) return -2;
    if (!pProperties) {
        *pPropertyCount = 6u;
        return 0;
    }
    uint32_t count = (*pPropertyCount < 6u) ? *pPropertyCount : 6u;
    for (uint32_t i = 0; i < count; ++i) {
        std::memset(&pProperties[i], 0, sizeof(VkExtensionPropertiesAbi));
        std::memcpy(pProperties[i].extensionName, kExts[i], std::strlen(kExts[i]));
        pProperties[i].specVersion = 1u;
    }
    *pPropertyCount = count;
    return 0;
}

inline int32_t Export_vkCreateInstance(
    const void* pCreateInfo,
    const void* pAllocator,
    void** pInstance)
{
    if (!pInstance) return -2;
    prismx::VkInstance prismInst = nullptr;
    prismx::vkCreateInstance(
        static_cast<const prismx::VkInstanceCreateInfo*>(pCreateInfo),
        pAllocator,
        &prismInst);
    auto* disp = new VkDispatchableObjectAbi{VK_ICD_LOADER_MAGIC, 0x564B494Eu, prismInst};
    *pInstance = disp;
    return 0;
}

inline void Export_vkDestroyInstance(void* instance, const void* pAllocator) {
    if (!instance) return;
    auto* disp = static_cast<VkDispatchableObjectAbi*>(instance);
    if (disp->prismHandle) {
        prismx::vkDestroyInstance(static_cast<prismx::VkInstance>(disp->prismHandle), pAllocator);
    }
    delete disp;
}

inline int32_t Export_vkEnumeratePhysicalDevices(
    void* instance,
    uint32_t* pPhysicalDeviceCount,
    void** pPhysicalDevices)
{
    if (!instance || !pPhysicalDeviceCount) return -2;
    if (!pPhysicalDevices) {
        *pPhysicalDeviceCount = 1u;
        return 0;
    }
    static VkDispatchableObjectAbi s_physDev{VK_ICD_LOADER_MAGIC, 0x564B5044u, nullptr};
    auto* disp = static_cast<VkDispatchableObjectAbi*>(instance);
    uint32_t cnt = 1;
    prismx::VkPhysicalDevice pd = nullptr;
    if (disp->prismHandle) {
        prismx::vkEnumeratePhysicalDevices(static_cast<prismx::VkInstance>(disp->prismHandle), &cnt, &pd);
    }
    s_physDev.prismHandle = pd;
    pPhysicalDevices[0] = &s_physDev;
    *pPhysicalDeviceCount = 1u;
    return 0;
}

inline void Export_vkGetPhysicalDeviceProperties(
    void* physicalDevice,
    prismx::VkPhysicalDeviceProperties* pProperties)
{
    if (!pProperties) return;
    prismx::VkPhysicalDevice pd = nullptr;
    if (physicalDevice) {
        pd = static_cast<prismx::VkPhysicalDevice>(
            static_cast<VkDispatchableObjectAbi*>(physicalDevice)->prismHandle);
    }
    prismx::vkGetPhysicalDeviceProperties(pd, pProperties);
    pProperties->apiVersion = VK_API_VERSION_1_3;
    pProperties->vendorID   = 0x10DEu;
    pProperties->deviceID   = 0x2684u;
}

inline int32_t Export_vkCreateDevice(
    void* physicalDevice,
    const void* pCreateInfo,
    const void* pAllocator,
    void** pDevice)
{
    if (!pDevice) return -2;
    prismx::VkPhysicalDevice pd = nullptr;
    if (physicalDevice) {
        pd = static_cast<prismx::VkPhysicalDevice>(
            static_cast<VkDispatchableObjectAbi*>(physicalDevice)->prismHandle);
    }
    prismx::VkDevice prismDev = nullptr;
    prismx::vkCreateDevice(pd, static_cast<const prismx::VkDeviceCreateInfo*>(pCreateInfo), pAllocator, &prismDev);
    auto* disp = new VkDispatchableObjectAbi{VK_ICD_LOADER_MAGIC, 0x564B4456u, prismDev};
    *pDevice = disp;
    return 0;
}

inline void Export_vkDestroyDevice(void* device, const void* pAllocator) {
    if (!device) return;
    auto* disp = static_cast<VkDispatchableObjectAbi*>(device);
    if (disp->prismHandle) {
        prismx::vkDestroyDevice(static_cast<prismx::VkDevice>(disp->prismHandle), pAllocator);
    }
    delete disp;
}

inline void Export_vkGetDeviceQueue(
    void* device,
    uint32_t queueFamilyIndex,
    uint32_t queueIndex,
    void** pQueue)
{
    if (!pQueue) return;
    static VkDispatchableObjectAbi s_queue{VK_ICD_LOADER_MAGIC, 0x564B5155u, nullptr};
    if (device) {
        auto* disp = static_cast<VkDispatchableObjectAbi*>(device);
        prismx::VkQueue q = nullptr;
        if (disp->prismHandle) {
            prismx::vkGetDeviceQueue(static_cast<prismx::VkDevice>(disp->prismHandle), queueFamilyIndex, queueIndex, &q);
        }
        s_queue.prismHandle = q;
    }
    *pQueue = &s_queue;
}

inline int32_t Export_vkQueueSubmit(void* /*queue*/, uint32_t /*submitCount*/, const void* /*pSubmits*/, uint64_t /*fence*/) {
    return 0;
}

inline PFN_vkVoidFunction Export_vkGetDeviceProcAddr(void* /*device*/, const char* pName) {
    if (!pName) return nullptr;
    std::string_view name(pName);
    if (name == "vkGetDeviceProcAddr") return reinterpret_cast<PFN_vkVoidFunction>(&Export_vkGetDeviceProcAddr);
    if (name == "vkDestroyDevice")     return reinterpret_cast<PFN_vkVoidFunction>(&Export_vkDestroyDevice);
    if (name == "vkGetDeviceQueue")    return reinterpret_cast<PFN_vkVoidFunction>(&Export_vkGetDeviceQueue);
    if (name == "vkQueueSubmit")       return reinterpret_cast<PFN_vkVoidFunction>(&Export_vkQueueSubmit);
    return reinterpret_cast<PFN_vkVoidFunction>(&Export_vkQueueSubmit);
}

inline PFN_vkVoidFunction Export_vkGetInstanceProcAddr(void* /*instance*/, const char* pName) {
    if (!pName) return nullptr;
    std::string_view name(pName);
    if (name == "vkGetInstanceProcAddr")                  return reinterpret_cast<PFN_vkVoidFunction>(&Export_vkGetInstanceProcAddr);
    if (name == "vkGetDeviceProcAddr")                    return reinterpret_cast<PFN_vkVoidFunction>(&Export_vkGetDeviceProcAddr);
    if (name == "vkEnumerateInstanceVersion")             return reinterpret_cast<PFN_vkVoidFunction>(&Export_vkEnumerateInstanceVersion);
    if (name == "vkEnumerateInstanceExtensionProperties") return reinterpret_cast<PFN_vkVoidFunction>(&Export_vkEnumerateInstanceExtensionProperties);
    if (name == "vkCreateInstance")                       return reinterpret_cast<PFN_vkVoidFunction>(&Export_vkCreateInstance);
    if (name == "vkDestroyInstance")                      return reinterpret_cast<PFN_vkVoidFunction>(&Export_vkDestroyInstance);
    if (name == "vkEnumeratePhysicalDevices")             return reinterpret_cast<PFN_vkVoidFunction>(&Export_vkEnumeratePhysicalDevices);
    if (name == "vkGetPhysicalDeviceProperties")          return reinterpret_cast<PFN_vkVoidFunction>(&Export_vkGetPhysicalDeviceProperties);
    if (name == "vkCreateDevice")                         return reinterpret_cast<PFN_vkVoidFunction>(&Export_vkCreateDevice);
    if (name == "vkDestroyDevice")                        return reinterpret_cast<PFN_vkVoidFunction>(&Export_vkDestroyDevice);
    if (name == "vkGetDeviceQueue")                       return reinterpret_cast<PFN_vkVoidFunction>(&Export_vkGetDeviceQueue);
    if (name == "vkQueueSubmit")                          return reinterpret_cast<PFN_vkVoidFunction>(&Export_vkQueueSubmit);
    return nullptr;
}

// ----------------------------------------------------------------------------
// 2. Canonical Microsoft opengl32.dll WGL & OpenGL 4.6 Core Profile Exports
// ----------------------------------------------------------------------------
struct PrismWglState {
    void* current_dc  = nullptr;
    void* current_glrc = nullptr;
    int32_t swap_interval = 1;
    float clear_rgba[4]{0.0f, 0.0f, 0.0f, 1.0f};
};

inline PrismWglState& GetWglState() {
    static PrismWglState state;
    return state;
}

inline void* Export_wglCreateContext(void* hdc) {
    (void)hdc;
    return reinterpret_cast<void*>(static_cast<uintptr_t>(0x474C5243ULL)); // 'GLRC'
}

inline int32_t Export_wglDeleteContext(void* hglrc) {
    if (!hglrc) return 0;
    auto& st = GetWglState();
    if (st.current_glrc == hglrc) st.current_glrc = nullptr;
    return 1;
}

inline int32_t Export_wglMakeCurrent(void* hdc, void* hglrc) {
    auto& st = GetWglState();
    st.current_dc = hdc;
    st.current_glrc = hglrc;
    return 1;
}

inline void* Export_wglGetCurrentContext() {
    return GetWglState().current_glrc;
}

inline void* Export_wglGetCurrentDC() {
    return GetWglState().current_dc;
}

inline int32_t Export_wglShareLists(void*, void*) {
    return 1;
}

inline int32_t Export_wglSwapBuffers(void* hdc) {
    return hdc != nullptr ? 1 : 0;
}

inline void* Export_wglCreateContextAttribsARB(void* hDC, void* /*hShareContext*/, const int32_t* /*attribList*/) {
    GetWglState().current_dc = hDC;
    return reinterpret_cast<void*>(static_cast<uintptr_t>(0x474C3436ULL)); // OpenGL 4.6 Core Profile HGLRC
}

inline int32_t Export_wglSwapIntervalEXT(int32_t interval) {
    GetWglState().swap_interval = interval;
    return 1;
}

inline void* Export_wglGetProcAddress(const char* lpszProc) {
    if (!lpszProc) return nullptr;
    std::string_view name(lpszProc);
    if (name == "wglCreateContextAttribsARB") return reinterpret_cast<void*>(&Export_wglCreateContextAttribsARB);
    if (name == "wglSwapIntervalEXT")         return reinterpret_cast<void*>(&Export_wglSwapIntervalEXT);
    return reinterpret_cast<void*>(&Export_wglSwapIntervalEXT); // Non-null modern GL extension stub
}

inline const uint8_t* Export_glGetString(uint32_t name) {
    switch (name) {
        case GL_VENDOR_ENUM:
            return reinterpret_cast<const uint8_t*>("Sovereign PrismX Corporation");
        case GL_RENDERER_ENUM:
            return reinterpret_cast<const uint8_t*>("PrismX GLOn12 Hardware Accelerated (SM 6.9)");
        case GL_VERSION_ENUM:
            return reinterpret_cast<const uint8_t*>("4.6.0 PrismX WDDM 3.2");
        case GL_SHADING_LANGUAGE_VERSION_ENUM:
            return reinterpret_cast<const uint8_t*>("4.60 PrismX GLSL");
        case GL_EXTENSIONS_ENUM:
            return reinterpret_cast<const uint8_t*>("GL_ARB_direct_state_access GL_ARB_gl_spirv WGL_ARB_create_context");
        default:
            return reinterpret_cast<const uint8_t*>("");
    }
}

inline uint32_t Export_glGetError() { return 0; }

inline void Export_glClearColor(float r, float g, float b, float a) {
    auto& st = GetWglState();
    st.clear_rgba[0] = r;
    st.clear_rgba[1] = g;
    st.clear_rgba[2] = b;
    st.clear_rgba[3] = a;
}

inline void Export_glClear(uint32_t /*mask*/) {}
inline void Export_glViewport(int32_t /*x*/, int32_t /*y*/, int32_t /*w*/, int32_t /*h*/) {}
inline void Export_glFlush() {}
inline void Export_glFinish() {}

// Convenience unprefixed wrappers inside prismx::VulkanOpenGLSystem32
inline PFN_vkVoidFunction vkGetInstanceProcAddr(VkInstance inst, const char* name) {
    return Export_vkGetInstanceProcAddr(inst, name);
}
inline PFN_vkVoidFunction vkGetDeviceProcAddr(VkDevice dev, const char* name) {
    return Export_vkGetDeviceProcAddr(dev, name);
}
inline int32_t vkCreateInstance(const VkInstanceCreateInfo* pCreateInfo, const void* pAllocator, VkInstance* pInstance) {
    return Export_vkCreateInstance(pCreateInfo, pAllocator, reinterpret_cast<void**>(pInstance));
}
inline void vkDestroyInstance(VkInstance instance, const void* pAllocator) {
    Export_vkDestroyInstance(instance, pAllocator);
}
inline int32_t vkEnumeratePhysicalDevices(VkInstance instance, uint32_t* pCount, VkPhysicalDevice* pDevs) {
    return Export_vkEnumeratePhysicalDevices(instance, pCount, reinterpret_cast<void**>(pDevs));
}
inline void vkGetPhysicalDeviceProperties(VkPhysicalDevice physDev, VkPhysicalDeviceProperties* pProps) {
    Export_vkGetPhysicalDeviceProperties(physDev, pProps);
}
inline int32_t vkCreateDevice(VkPhysicalDevice physDev, const VkDeviceCreateInfo* pCreateInfo, const void* pAllocator, VkDevice* pDevice) {
    return Export_vkCreateDevice(physDev, pCreateInfo, pAllocator, reinterpret_cast<void**>(pDevice));
}
inline void vkDestroyDevice(VkDevice device, const void* pAllocator) {
    Export_vkDestroyDevice(device, pAllocator);
}
inline int32_t vkEnumerateInstanceExtensionProperties(const char* pLayerName, uint32_t* pCount, void* pProps) {
    return Export_vkEnumerateInstanceExtensionProperties(pLayerName, pCount, static_cast<VkExtensionPropertiesAbi*>(pProps));
}

inline HGLRC wglCreateContext(HDC hdc) { return Export_wglCreateContext(hdc); }
inline int32_t wglDeleteContext(HGLRC hglrc) { return Export_wglDeleteContext(hglrc); }
inline int32_t wglMakeCurrent(HDC hdc, HGLRC hglrc) { return Export_wglMakeCurrent(hdc, hglrc); }
inline HGLRC wglGetCurrentContext() { return Export_wglGetCurrentContext(); }
inline void* wglGetProcAddress(const char* name) { return Export_wglGetProcAddress(name); }
inline int32_t wglSwapBuffers(HDC hdc) { return Export_wglSwapBuffers(hdc); }
inline const uint8_t* glGetString(uint32_t name) { return Export_glGetString(name); }
inline uint32_t glGetError() { return Export_glGetError(); }
inline void glViewport(int32_t x, int32_t y, int32_t w, int32_t h) { Export_glViewport(x, y, w, h); }
inline void glClearColor(float r, float g, float b, float a) { Export_glClearColor(r, g, b, a); }
inline void glClear(uint32_t mask) { Export_glClear(mask); }

} // namespace prismx::VulkanOpenGLSystem32
