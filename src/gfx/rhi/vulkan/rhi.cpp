#include "rhi.h"
#include "command_list.h"

namespace gfx::rhi::vk {

VulkanRHI::VulkanRHI(GLFWwindow *window, const Config &cfg)
    : device(std::make_shared<Device>(window, cfg)), swapchain_(std::make_shared<Swapchain>(device)) {}

CommandListRef VulkanRHI::create_command_list() { return std::make_shared<VulkanCommandList>(device); }
TextureRef VulkanRHI::create_texture(const TextureDesc &desc) { return nullptr; }
BufferRef VulkanRHI::create_buffer(const BufferDesc &desc) { return nullptr; }
DescriptorSetRef VulkanRHI::create_descriptor_set(const DescriptorSetDesc &desc) { return nullptr; }
ShaderRef VulkanRHI::create_shader(const ShaderDesc &desc) { return nullptr; }
GraphicsPipelineRef VulkanRHI::create_graphics_pipeline(const GraphicsPipelineDesc &desc) { return nullptr; }
ComputePipelineRef VulkanRHI::create_compute_pipeline(const ComputePipelineDesc &desc) { return nullptr; }
} // namespace gfx::rhi::vk