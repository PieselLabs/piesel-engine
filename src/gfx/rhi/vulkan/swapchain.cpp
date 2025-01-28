#include "swapchain.h"
#include <GLFW/glfw3.h>
#include <VkBootstrap.h>

namespace gfx::rhi::vk {
Swapchain::Swapchain(std::shared_ptr<Device> ctx) : ctx_(std::move(ctx)) {
  vkb::SwapchainBuilder swapchainBuilder{ctx->physical_device, ctx->device, ctx->surface};

  format_ = VK_FORMAT_B8G8R8A8_UNORM;

  int width, height;
  glfwGetWindowSize(ctx->window, &width, &height);

  vkb::Swapchain vkbSwapchain =
      swapchainBuilder
          //.use_default_format_selection()
          .set_desired_format(VkSurfaceFormatKHR{.format = format_, .colorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR})
          // use vsync present mode
          .set_desired_present_mode(VK_PRESENT_MODE_FIFO_KHR)
          .set_desired_extent(width, height)
          .add_image_usage_flags(VK_IMAGE_USAGE_TRANSFER_DST_BIT)
          .build()
          .value();

  extent_ = vkbSwapchain.extent;
  // store swapchain and its related images
  swapchain_ = vkbSwapchain.swapchain;
  images_ = vkbSwapchain.get_images().value();
  views_ = vkbSwapchain.get_image_views().value();
}

Swapchain::~Swapchain() {
  vkDestroySwapchainKHR(ctx_->device, swapchain_, nullptr);
  for (int i = 0; i < views_.size(); i++) {
    vkDestroyImageView(ctx_->device, views_[i], nullptr);
  }
}
} // namespace gfx::rhi::vk