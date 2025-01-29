#pragma once
#include "device.h"
#include <memory>
#include <vector>

namespace gfx::rhi::vk {
class Swapchain {
public:
  explicit Swapchain(std::shared_ptr<Device> ctx);

  ~Swapchain();

private:
  std::shared_ptr<Device> ctx;
  VkSwapchainKHR swapchain;
  VkFormat format;

  std::vector<VkImage> images;
  std::vector<VkImageView> views;
  VkExtent2D extent;
};
} // namespace gfx::rhi::vk