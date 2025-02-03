#pragma once

#include <vulkan/vulkan.h>

namespace gfx::rhi::vk {
VkImageSubresourceRange ImageSubResourceRange(VkImageAspectFlags aspectMask);

void TransitionImage(VkCommandBuffer cmd, VkImage image, VkImageLayout currentLayout, VkImageLayout newLayout);
} // namespace gfx::rhi::vk