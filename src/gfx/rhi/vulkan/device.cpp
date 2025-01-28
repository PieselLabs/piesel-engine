#include "device.h"
#include "vk_defs.h"
#include <VkBootstrap.h>

namespace gfx::rhi::vk {

Device::Device(GLFWwindow *window, const Config &cfg) : cfg(cfg), window(window), current_frame(0) {
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
  debug_messenger = vkb_inst.debug_messenger;

  VK_SAFE_CALL(glfwCreateWindowSurface(instance, window, nullptr, &surface));

  VkPhysicalDeviceVulkan13Features features{.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES};
  features.dynamicRendering = true;
  features.synchronization2 = true;

  // vulkan 1.2 features
  VkPhysicalDeviceVulkan12Features features12{.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES};
  features12.bufferDeviceAddress = true;
  features12.descriptorIndexing = true;

  vkb::PhysicalDeviceSelector selector{vkb_inst};
  vkb::PhysicalDevice physicalDevice = selector.set_minimum_version(1, 3)
                                           .set_required_features_13(features)
                                           .set_required_features_12(features12)
                                           .set_surface(surface)
                                           .select()
                                           .value();

  vkb::DeviceBuilder deviceBuilder{physicalDevice};
  vkb::Device vkbDevice = deviceBuilder.build().value();

  device = vkbDevice.device;
  physical_device = physicalDevice.physical_device;

  graphics_queue = vkbDevice.get_queue(vkb::QueueType::graphics).value();
  graphics_family = vkbDevice.get_queue_index(vkb::QueueType::graphics).value();

  VkCommandPoolCreateInfo commandPoolInfo = {};
  commandPoolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
  commandPoolInfo.pNext = nullptr;
  commandPoolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
  commandPoolInfo.queueFamilyIndex = graphics_family;

  VK_SAFE_CALL(vkCreateCommandPool(device, &commandPoolInfo, nullptr, &command_pool));
}

Device::~Device() {
  vkDeviceWaitIdle(device);
  vkDestroyCommandPool(device, command_pool, nullptr);
  vkDestroySurfaceKHR(instance, surface, nullptr);
  vkDestroyDevice(device, nullptr);
  vkb::destroy_debug_utils_messenger(instance, debug_messenger);
  vkDestroyInstance(instance, nullptr);
}
} // namespace gfx::rhi::vk