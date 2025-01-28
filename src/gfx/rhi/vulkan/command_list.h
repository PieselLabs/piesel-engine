#pragma once
#include "device.h"
#include "gfx/rhi/rhi.h"
#include "vk_defs.h"
#include <vulkan/vulkan.h>

namespace gfx::rhi::vk {
class VulkanCommandList : public CommandList {
public:
  VulkanCommandList(std::shared_ptr<Device> device);

  void begin() override;

private:
  VkCommandBuffer commandBuffers[MAX_FRAMES_IN_FLIGHT];

  std::shared_ptr<Device> device;
};
} // namespace gfx::rhi::vk