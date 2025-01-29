#include "swapchain.h"
#include <GLFW/glfw3.h>
#include <VkBootstrap.h>

namespace gfx::rhi::vk {
Swapchain::Swapchain(std::shared_ptr<Device> inCtx) : ctx(std::move(inCtx)) {
  vkb::SwapchainBuilder swapchainBuilder{ctx->GetPhysicalDevice(), ctx->GetDevice(), ctx->GetSurface()};

  format = VK_FORMAT_B8G8R8A8_UNORM;

  int width, height;
  glfwGetWindowSize(ctx->GetWindow(), &width, &height);

  vkb::Swapchain vkbSwapchain =
      swapchainBuilder
          //.use_default_format_selection()
          .set_desired_format(VkSurfaceFormatKHR{.format = format, .colorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR})
          // use vsync present mode
          .set_desired_present_mode(VK_PRESENT_MODE_FIFO_KHR)
          .set_desired_extent(width, height)
          .add_image_usage_flags(VK_IMAGE_USAGE_TRANSFER_DST_BIT)
          .build()
          .value();

  extent = vkbSwapchain.extent;
  // store swapchain and its related images
  swapchain = vkbSwapchain.swapchain;
  images = vkbSwapchain.get_images().value();
  views = vkbSwapchain.get_image_views().value();
}

Swapchain::~Swapchain() {
  vkDestroySwapchainKHR(ctx->GetDevice(), swapchain, nullptr);
  for (int i = 0; i < views.size(); i++) {
    vkDestroyImageView(ctx->GetDevice(), views[i], nullptr);
  }
}
} // namespace gfx::rhi::vk