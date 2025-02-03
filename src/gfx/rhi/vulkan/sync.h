#pragma once
#include "rhi.h"
#include "vk_defs.h"
#include <vulkan/vulkan.h>

namespace gfx::rhi::vk {
class VulkanSemaphore : public Semaphore {
public:
  VulkanSemaphore(std::shared_ptr<VulkanRHI> rhi);

  virtual ~VulkanSemaphore();

  const VkSemaphore &Get();

private:
  VkSemaphore semaphores[MAX_FRAMES_IN_FLIGHT];

  std::shared_ptr<VulkanRHI> rhi;
};

class VulkanFence : public Fence {
public:
  VulkanFence(std::shared_ptr<VulkanRHI> rhi);

  virtual ~VulkanFence();

  const VkFence &Get();

  void Wait() override;

  void Reset() override;

private:
  VkFence fences[MAX_FRAMES_IN_FLIGHT];

  std::shared_ptr<VulkanRHI> rhi;
};
} // namespace gfx::rhi::vk