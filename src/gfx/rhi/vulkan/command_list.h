#pragma once
#include "rhi.h"
#include "vk_defs.h"
#include <vulkan/vulkan.h>

namespace gfx::rhi::vk {
class VulkanCommandList : public CommandList {
public:
  VulkanCommandList(std::shared_ptr<VulkanRHI> rhi);

  VkCommandBuffer Get();

  void Begin() override;

  void End() override;

  void Flash(int frame) override;

private:
  VkCommandBuffer commandBuffers[MAX_FRAMES_IN_FLIGHT];

  std::shared_ptr<VulkanRHI> rhi;
};
} // namespace gfx::rhi::vk