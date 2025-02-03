#include "command_list.h"

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

void VulkanCommandList::Begin() { vkResetCommandBuffer(commandBuffers[rhi->GetCurrentFrame()], 0); }
} // namespace gfx::rhi::vk