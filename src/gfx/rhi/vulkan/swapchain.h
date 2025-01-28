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
  std::shared_ptr<const Device> ctx_;
  VkSwapchainKHR swapchain_;
  VkFormat format_;

  std::vector<VkImage> images_;
  std::vector<VkImageView> views_;
  VkExtent2D extent_;
};
} // namespace gfx::rhi::vk