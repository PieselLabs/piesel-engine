#include "sync.h"

namespace gfx::rhi::vk {
VulkanSemaphore::VulkanSemaphore(std::shared_ptr<VulkanDevice> inDevice) : device(std::move(inDevice)) {

  for (int i = 0; i < device->GetCfg().InFlightFrames; i++) {

    VkSemaphoreCreateInfo info = {.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO, .pNext = nullptr, .flags = 0};

    VK_SAFE_CALL(vkCreateSemaphore(device->GetDevice(), &info, nullptr, &semaphores[i]));
  };
}

const VkSemaphore &VulkanSemaphore::Get() { return semaphores[device->GetCurrentFrame()]; }

VulkanSemaphore::~VulkanSemaphore() {
  for (int i = 0; i < device->GetCfg().InFlightFrames; i++) {
    vkDestroySemaphore(device->GetDevice(), semaphores[i], nullptr);
  }
}

VulkanFence::VulkanFence(std::shared_ptr<VulkanDevice> inDevice) : device(std::move(inDevice)) {

  for (int i = 0; i < device->GetCfg().InFlightFrames; i++) {
    VkFenceCreateInfo info = {
        .sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO, .pNext = nullptr, .flags = VK_FENCE_CREATE_SIGNALED_BIT};

    VK_SAFE_CALL(vkCreateFence(device->GetDevice(), &info, nullptr, &fences[i]));
  };
}

const VkFence &VulkanFence::Get() { return fences[device->GetCurrentFrame()]; }

VulkanFence::~VulkanFence() {
  for (int i = 0; i < device->GetCfg().InFlightFrames; i++) {
    vkDestroyFence(device->GetDevice(), fences[i], nullptr);
  }
}

void VulkanFence::Wait() { VK_SAFE_CALL(vkWaitForFences(device->GetDevice(), 1, &Get(), true, 1000000)); }

void VulkanFence::Reset() { vkResetFences(device->GetDevice(), 1, &Get()); }

} // namespace gfx::rhi::vk