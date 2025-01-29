#pragma once
#include "device.h"
#include <memory>
#include <vector>

namespace gfx::rhi::vk {
class Swapchain {
public:
  explicit Swapchain(std::shared_ptr<VulkanDevice> ctx);

  ~Swapchain();

  std::shared_ptr<VulkanDevice> GetCtx();
  VkSwapchainKHR GetSwapchain();
  VkFormat GetFormat();
  std::vector<VkImage> GetImages();
  std::vector<VkImageView> GetViews();
  VkExtent2D GetExtent();

private:
  std::shared_ptr<VulkanDevice> ctx;
  VkSwapchainKHR swapchain;
  VkFormat format;

  std::vector<VkImage> images;
  std::vector<VkImageView> views;
  VkExtent2D extent;
};
} // namespace gfx::rhi::vk