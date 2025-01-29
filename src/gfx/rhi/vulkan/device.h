#pragma once

#include "gfx/rhi/rhi.h"
#include <vulkan/vulkan.h>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace gfx::rhi::vk {
class VulkanDevice {
public:
  VulkanDevice(GLFWwindow *window, const Config &cfg);
  ~VulkanDevice();

  Config GetCfg();
  VkInstance GetInstance();
  VkDebugUtilsMessengerEXT GetDebugMessenger();
  VkPhysicalDevice GetPhysicalDevice();
  VkDevice GetDevice();
  VkSurfaceKHR GetSurface();
  VkQueue GetGraphicsQueue();
  uint32_t GetGraphicsFamily();
  VkCommandPool GetCommandPool();
  GLFWwindow *GetWindow();
  uint64_t GetCurrentFrame();

private:
  Config cfg;

  VkInstance instance;
  VkDebugUtilsMessengerEXT debugMessenger;
  VkPhysicalDevice physicalDevice;
  VkDevice device;
  VkSurfaceKHR surface;

  VkQueue graphicsQueue;
  uint32_t graphicsFamily;
  VkCommandPool commandPool;

  GLFWwindow *window;

  uint64_t currentFrame;
};
} // namespace gfx::rhi::vk