#include "command_list.h"

namespace gfx::rhi::vk {
VulkanCommandList::VulkanCommandList(std::shared_ptr<Device> inDevice) : device(std::move(inDevice)) {
  VkCommandBufferAllocateInfo cmdAllocInfo{};
  cmdAllocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  cmdAllocInfo.pNext = nullptr;
  cmdAllocInfo.commandPool = device->GetCommandPool();
  cmdAllocInfo.commandBufferCount = device->GetCfg().inFlightFrames;
  cmdAllocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;

  VK_SAFE_CALL(vkAllocateCommandBuffers(device->GetDevice(), &cmdAllocInfo, commandBuffers));
}

void VulkanCommandList::Begin() { vkResetCommandBuffer(commandBuffers[device->GetCurrentFrame()], 0); }
} // namespace gfx::rhi::vk