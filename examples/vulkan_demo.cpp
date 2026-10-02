// ============================================================================
// PrismX Example: Vulkan 1.3 Instance & Physical Device Query with PrismVK
// 
// Demonstrates Khronos Vulkan 1.3 ICD Loader interaction and device discovery.
// ============================================================================

#include "prismx.hpp"
#include <iostream>
#include <vector>

using namespace prismx;

int main() {
    std::cout << "[PrismX] Initializing Khronos Vulkan 1.3 Loader...\n";

    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "PrismX Vulkan Standalone Demo";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "PrismVK";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 3, 0);
    appInfo.apiVersion = VK_API_VERSION_1_3;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    VkInstance instance = VK_NULL_HANDLE;
    VkResult res = vkCreateInstance(&createInfo, nullptr, &instance);
    if (res != VK_SUCCESS) {
        std::cerr << "Failed to create Vulkan instance!\n";
        return 1;
    }

    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
    std::cout << "[PrismX] Discovered " << deviceCount << " Vulkan Physical Device(s):\n";

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

    for (uint32_t i = 0; i < deviceCount; ++i) {
        VkPhysicalDeviceProperties props{};
        vkGetPhysicalDeviceProperties(devices[i], &props);
        std::cout << "  [" << i << "] " << props.deviceName 
                  << " (Driver: " << props.driverVersion 
                  << ", API: " << VK_API_VERSION_1_3 << ")\n";
    }

    vkDestroyInstance(instance, nullptr);
    std::cout << "[PrismX] Vulkan teardown completed.\n";
    return 0;
}
