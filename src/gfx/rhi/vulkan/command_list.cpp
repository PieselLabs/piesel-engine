#include "command_list.h"
#include "utils.h"
#include <cmath>

namespace gfx::rhi::vk {
VulkanCommandList::VulkanCommandList(std::shared_ptr<VulkanRHI> inRhi) : rhi(std::move(inRhi)) {
  VkCommandBufferAllocateInfo cmdAllocInfo{};
  cmdAllocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  cmdAllocInfo.pNext = nullptr;
  cmdAllocInfo.commandPool = rhi->GetCommandPool();
  cmdAllocInfo.commandBufferCount = rhi->GetCfg().InFlightFrames;
  cmdAllocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;

  VK_SAFE_CALL(vkAllocateCommandBuffers(rhi->GetDevice(), &cmdAllocInfo, commandBuffers));
}

VkCommandBuffer VulkanCommandList::Get() { return commandBuffers[rhi->GetCurrentFrame()]; }

void VulkanCommandList::Begin() {
  vkResetCommandBuffer(commandBuffers[rhi->GetCurrentFrame()], 0);

  VkCommandBufferBeginInfo info = {};
  info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
  info.pNext = nullptr;

  info.pInheritanceInfo = nullptr;
  info.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

  VK_SAFE_CALL(vkBeginCommandBuffer(Get(), &info));
}

void VulkanCommandList::End() { VK_SAFE_CALL(vkEndCommandBuffer(Get())); }

void VulkanCommandList::Flash(int frame) {
  VkImage img = rhi->GetImages()[rhi->GetCurrentFrame()];
  TransitionImage(Get(), img, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_GENERAL);

  VkClearColorValue clearValue;
  float flash = std::abs(std::sin(frame / 120.f));
  clearValue = {{0.0f, 0.0f, flash, 1.0f}};

  VkImageSubresourceRange clearRange = ImageSubResourceRange(VK_IMAGE_ASPECT_COLOR_BIT);

  vkCmdClearColorImage(Get(), img, VK_IMAGE_LAYOUT_GENERAL, &clearValue, 1, &clearRange);

  TransitionImage(Get(), img, VK_IMAGE_LAYOUT_GENERAL, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR);
}

} // namespace gfx::rhi::vk