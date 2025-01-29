#include "device.h"
#include "vk_defs.h"
#include <VkBootstrap.h>

namespace gfx::rhi::vk {

VulkanDevice::VulkanDevice(GLFWwindow *window, const Config &cfg) : cfg(cfg), window(window), currentFrame(0) {
  vkb::InstanceBuilder builder;

  // make the vulkan instance, with basic debug features
  auto instRet = builder.set_app_name("Example Vulkan Application")
                     .request_validation_layers(cfg.Debug)
                     .use_default_debug_messenger()
                     .require_api_version(1, 3, 0)
                     .build();

  vkb::Instance vkbInst = instRet.value();

  // grab the instance
  instance = vkbInst.instance;
  debugMessenger = vkbInst.debug_messenger;

  VK_SAFE_CALL(glfwCreateWindowSurface(instance, window, nullptr, &surface));

  VkPhysicalDeviceVulkan13Features features{.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES};
  features.dynamicRendering = true;
  features.synchronization2 = true;

  // vulkan 1.2 features
  VkPhysicalDeviceVulkan12Features features12{.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES};
  features12.bufferDeviceAddress = true;
  features12.descriptorIndexing = true;

  vkb::PhysicalDeviceSelector selector{vkbInst};
  vkb::PhysicalDevice vkbPhysicalDevice = selector.set_minimum_version(1, 3)
                                              .set_required_features_13(features)
                                              .set_required_features_12(features12)
                                              .set_surface(surface)
                                              .select()
                                              .value();

  vkb::DeviceBuilder deviceBuilder{vkbPhysicalDevice};
  vkb::Device vkbDevice = deviceBuilder.build().value();

  device = vkbDevice.device;

  physicalDevice = vkbPhysicalDevice.physical_device;
  graphicsQueue = vkbDevice.get_queue(vkb::QueueType::graphics).value();
  graphicsFamily = vkbDevice.get_queue_index(vkb::QueueType::graphics).value();

  VkCommandPoolCreateInfo commandPoolInfo = {};
  commandPoolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
  commandPoolInfo.pNext = nullptr;
  commandPoolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
  commandPoolInfo.queueFamilyIndex = graphicsFamily;

  VK_SAFE_CALL(vkCreateCommandPool(device, &commandPoolInfo, nullptr, &commandPool));
}

VulkanDevice::~VulkanDevice() {
  vkDeviceWaitIdle(device);
  vkDestroyCommandPool(device, commandPool, nullptr);
  vkDestroySurfaceKHR(instance, surface, nullptr);
  vkDestroyDevice(device, nullptr);
  vkb::destroy_debug_utils_messenger(instance, debugMessenger);
  vkDestroyInstance(instance, nullptr);
}

Config VulkanDevice::GetCfg() { return cfg; }
VkInstance VulkanDevice::GetInstance() { return instance; }
VkDebugUtilsMessengerEXT VulkanDevice::GetDebugMessenger() { return debugMessenger; }
VkPhysicalDevice VulkanDevice::GetPhysicalDevice() { return physicalDevice; }
VkDevice VulkanDevice::GetDevice() { return device; }
VkSurfaceKHR VulkanDevice::GetSurface() { return surface; }
VkQueue VulkanDevice::GetGraphicsQueue() { return graphicsQueue; }
uint32_t VulkanDevice::GetGraphicsFamily() { return graphicsFamily; }
VkCommandPool VulkanDevice::GetCommandPool() { return commandPool; }
GLFWwindow *VulkanDevice::GetWindow() { return window; }
uint64_t VulkanDevice::GetCurrentFrame() { return currentFrame; }

} // namespace gfx::rhi::vk