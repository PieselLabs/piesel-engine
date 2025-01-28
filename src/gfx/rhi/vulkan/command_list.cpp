#include "command_list.h"

namespace gfx::rhi::vk {
VulkanCommandList::VulkanCommandList(std::shared_ptr<Device> device) : device(std::move(device)) {
  VkCommandBufferAllocateInfo cmdAllocInfo{};
  cmdAllocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  cmdAllocInfo.pNext = nullptr;
  cmdAllocInfo.commandPool = device->command_pool;
  cmdAllocInfo.commandBufferCount = device->cfg.inFlightFrames;
  cmdAllocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;

  VK_SAFE_CALL(vkAllocateCommandBuffers(device->device, &cmdAllocInfo, commandBuffers));
}

void VulkanCommandList::begin() { vkResetCommandBuffer(commandBuffers[device->current_frame], 0); }
} // namespace gfx::rhi::vk