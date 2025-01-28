#include "rhi.h"

namespace gfx::rhi::vk {

VulkanRHI::VulkanRHI(GLFWwindow *window, const Config &cfg)
    : context_(std::make_shared<Device>(window, cfg)), swapchain_(std::make_shared<Swapchain>(context_)) {}

CommandListRef VulkanRHI::create_command_list(const CommandListDesc &desc) { return nullptr; }
TextureRef VulkanRHI::create_texture(const TextureDesc &desc) { return nullptr; }
BufferRef VulkanRHI::create_buffer(const BufferDesc &desc) { return nullptr; }
DescriptorSetRef VulkanRHI::create_descriptor_set(const DescriptorSetDesc &desc) { return nullptr; }
ShaderRef VulkanRHI::create_shader(const ShaderDesc &desc) { return nullptr; }
GraphicsPipelineRef VulkanRHI::create_graphics_pipeline(const GraphicsPipelineDesc &desc) { return nullptr; }
ComputePipelineRef VulkanRHI::create_compute_pipeline(const ComputePipelineDesc &desc) {
  auto shader = rhi_cast(desc.shader);
  return nullptr;
}
} // namespace gfx::rhi::vk