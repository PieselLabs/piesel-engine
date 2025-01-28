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

  VkInstance instance;
  VkDebugUtilsMessengerEXT debug_messenger;
  VkPhysicalDevice physical_device;
  VkDevice device;
  VkSurfaceKHR surface;
  GLFWwindow *window;
};
} // namespace gfx::rhi::vk