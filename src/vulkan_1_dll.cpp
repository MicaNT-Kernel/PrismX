#include "../include/prismx/vulkan1_opengl32_system32_abi.hpp"

#if defined(_WIN32)
#define PRISMX_DLL_EXPORT extern "C" __declspec(dllexport)
#else
#define PRISMX_DLL_EXPORT extern "C" __attribute__((visibility("default")))
#endif

PRISMX_DLL_EXPORT prismx::VulkanOpenGLSystem32::PFN_vkVoidFunction vkGetInstanceProcAddr(
    prismx::VulkanOpenGLSystem32::VkInstance instance,
    const char* pName) {
    return prismx::VulkanOpenGLSystem32::vkGetInstanceProcAddr(instance, pName);
}

PRISMX_DLL_EXPORT prismx::VulkanOpenGLSystem32::PFN_vkVoidFunction vkGetDeviceProcAddr(
    prismx::VulkanOpenGLSystem32::VkDevice device,
    const char* pName) {
    return prismx::VulkanOpenGLSystem32::vkGetDeviceProcAddr(device, pName);
}

PRISMX_DLL_EXPORT int32_t vkCreateInstance(
    const prismx::VulkanOpenGLSystem32::VkInstanceCreateInfo* pCreateInfo,
    const void* pAllocator,
    prismx::VulkanOpenGLSystem32::VkInstance* pInstance) {
    return prismx::VulkanOpenGLSystem32::vkCreateInstance(pCreateInfo, pAllocator, pInstance);
}

PRISMX_DLL_EXPORT void vkDestroyInstance(
    prismx::VulkanOpenGLSystem32::VkInstance instance,
    const void* pAllocator) {
    prismx::VulkanOpenGLSystem32::vkDestroyInstance(instance, pAllocator);
}

PRISMX_DLL_EXPORT int32_t vkEnumeratePhysicalDevices(
    prismx::VulkanOpenGLSystem32::VkInstance instance,
    uint32_t* pPhysicalDeviceCount,
    prismx::VulkanOpenGLSystem32::VkPhysicalDevice* pPhysicalDevices) {
    return prismx::VulkanOpenGLSystem32::vkEnumeratePhysicalDevices(
        instance, pPhysicalDeviceCount, pPhysicalDevices);
}

PRISMX_DLL_EXPORT void vkGetPhysicalDeviceProperties(
    prismx::VulkanOpenGLSystem32::VkPhysicalDevice physicalDevice,
    prismx::VulkanOpenGLSystem32::VkPhysicalDeviceProperties* pProperties) {
    prismx::VulkanOpenGLSystem32::vkGetPhysicalDeviceProperties(physicalDevice, pProperties);
}

PRISMX_DLL_EXPORT int32_t vkCreateDevice(
    prismx::VulkanOpenGLSystem32::VkPhysicalDevice physicalDevice,
    const prismx::VulkanOpenGLSystem32::VkDeviceCreateInfo* pCreateInfo,
    const void* pAllocator,
    prismx::VulkanOpenGLSystem32::VkDevice* pDevice) {
    return prismx::VulkanOpenGLSystem32::vkCreateDevice(
        physicalDevice, pCreateInfo, pAllocator, pDevice);
}

PRISMX_DLL_EXPORT void vkDestroyDevice(
    prismx::VulkanOpenGLSystem32::VkDevice device,
    const void* pAllocator) {
    prismx::VulkanOpenGLSystem32::vkDestroyDevice(device, pAllocator);
}

PRISMX_DLL_EXPORT int32_t vkEnumerateInstanceExtensionProperties(
    const char* pLayerName,
    uint32_t* pPropertyCount,
    void* pProperties) {
    return prismx::VulkanOpenGLSystem32::vkEnumerateInstanceExtensionProperties(
        pLayerName, pPropertyCount, pProperties);
}
