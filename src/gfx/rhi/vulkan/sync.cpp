#include "sync.h"

namespace gfx::rhi::vk {
VulkanSemaphore::VulkanSemaphore(std::shared_ptr<VulkanRHI> inRhi) : rhi(std::move(inRhi)) {

  for (int i = 0; i < rhi->GetCfg().InFlightFrames; i++) {

    VkSemaphoreCreateInfo info = {.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO, .pNext = nullptr, .flags = 0};

    VK_SAFE_CALL(vkCreateSemaphore(rhi->GetDevice(), &info, nullptr, &semaphores[i]));
  };
}

const VkSemaphore &VulkanSemaphore::Get() { return semaphores[rhi->GetCurrentFrame()]; }

VulkanSemaphore::~VulkanSemaphore() {
  for (int i = 0; i < rhi->GetCfg().InFlightFrames; i++) {
    vkDestroySemaphore(rhi->GetDevice(), semaphores[i], nullptr);
  }
}

VulkanFence::VulkanFence(std::shared_ptr<VulkanRHI> inRhi) : rhi(std::move(inRhi)) {

  for (int i = 0; i < rhi->GetCfg().InFlightFrames; i++) {
    VkFenceCreateInfo info = {
        .sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO, .pNext = nullptr, .flags = VK_FENCE_CREATE_SIGNALED_BIT};

    VK_SAFE_CALL(vkCreateFence(rhi->GetDevice(), &info, nullptr, &fences[i]));
  };
}

const VkFence &VulkanFence::Get() { return fences[rhi->GetCurrentFrame()]; }

VulkanFence::~VulkanFence() {
  for (int i = 0; i < rhi->GetCfg().InFlightFrames; i++) {
    vkDestroyFence(rhi->GetDevice(), fences[i], nullptr);
  }
}

void VulkanFence::Wait() { VK_SAFE_CALL(vkWaitForFences(rhi->GetDevice(), 1, &Get(), true, 1000000000)); }

void VulkanFence::Reset() { vkResetFences(rhi->GetDevice(), 1, &Get()); }

} // namespace gfx::rhi::vk