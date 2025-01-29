#include "device.h"
#include "vk_defs.h"
#include <VkBootstrap.h>

namespace gfx::rhi::vk {

Device::Device(GLFWwindow *window, const Config &cfg) : cfg(cfg), window(window), currentFrame(0) {
  vkb::InstanceBuilder builder;

  // make the vulkan instance, with basic debug features
  auto inst_ret = builder.set_app_name("Example Vulkan Application")
                      .request_validation_layers(cfg.debug)
                      .use_default_debug_messenger()
                      .require_api_version(1, 3, 0)
                      .build();

  vkb::Instance vkb_inst = inst_ret.value();

  // grab the instance
  instance = vkb_inst.instance;
  debugMessenger = vkb_inst.debug_messenger;

  VK_SAFE_CALL(glfwCreateWindowSurface(instance, window, nullptr, &surface));

  VkPhysicalDeviceVulkan13Features features{.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES};
  features.dynamicRendering = true;
  features.synchronization2 = true;

  // vulkan 1.2 features
  VkPhysicalDeviceVulkan12Features features12{.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES};
  features12.bufferDeviceAddress = true;
  features12.descriptorIndexing = true;

  vkb::PhysicalDeviceSelector selector{vkb_inst};
  vkb::PhysicalDevice physical_device = selector.set_minimum_version(1, 3)
                                            .set_required_features_13(features)
                                            .set_required_features_12(features12)
                                            .set_surface(surface)
                                            .select()
                                            .value();

  vkb::DeviceBuilder deviceBuilder{physical_device};
  vkb::Device vkbDevice = deviceBuilder.build().value();

  device = vkbDevice.device;
  physicalDevice = physical_device.physical_device;

  graphicsQueue = vkbDevice.get_queue(vkb::QueueType::graphics).value();
  graphicsFamily = vkbDevice.get_queue_index(vkb::QueueType::graphics).value();

  VkCommandPoolCreateInfo commandPoolInfo = {};
  commandPoolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
  commandPoolInfo.pNext = nullptr;
  commandPoolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
  commandPoolInfo.queueFamilyIndex = graphicsFamily;

  VK_SAFE_CALL(vkCreateCommandPool(device, &commandPoolInfo, nullptr, &commandPool));
}

Device::~Device() {
  vkDeviceWaitIdle(device);
  vkDestroyCommandPool(device, commandPool, nullptr);
  vkDestroySurfaceKHR(instance, surface, nullptr);
  vkDestroyDevice(device, nullptr);
  vkb::destroy_debug_utils_messenger(instance, debugMessenger);
  vkDestroyInstance(instance, nullptr);
}

Config Device::GetCfg() { return cfg; }
VkInstance Device::GetInstance() { return instance; }
VkDebugUtilsMessengerEXT Device::GetDebugMessenger() { return debugMessenger; }
VkPhysicalDevice Device::GetPhysicalDevice() { return physicalDevice; }
VkDevice Device::GetDevice() { return device; }
VkSurfaceKHR Device::GetSurface() { return surface; }
VkQueue Device::GetGraphicsQueue() { return graphicsQueue; }
uint32_t Device::GetGraphicsFamily() { return graphicsFamily; }
VkCommandPool Device::GetCommandPool() { return commandPool; }
GLFWwindow *Device::GetWindow() { return window; }
uint64_t Device::GetCurrentFrame() { return currentFrame; }

} // namespace gfx::rhi::vk