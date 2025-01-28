#pragma once

#include "gfx/rhi/rhi.h"
#include <vulkan/vulkan.h>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace gfx::rhi::vk {
class Device {
public:
  Device(GLFWwindow *window, const Config &cfg);
  ~Device();

  Config cfg;

  VkInstance instance;
  VkDebugUtilsMessengerEXT debug_messenger;
  VkPhysicalDevice physical_device;
  VkDevice device;
  VkSurfaceKHR surface;

  VkQueue graphics_queue;
  uint32_t graphics_family;
  VkCommandPool command_pool;

  GLFWwindow *window;

  uint64_t current_frame;
};
} // namespace gfx::rhi::vk