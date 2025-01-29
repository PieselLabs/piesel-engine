#include "rhi.h"
#include "command_list.h"

namespace gfx::rhi::vk {

VulkanRHI::VulkanRHI(GLFWwindow *window, const Config &cfg)
    : device(std::make_shared<Device>(window, cfg)), swapchain(std::make_shared<Swapchain>(device)) {}

CommandListRef VulkanRHI::CreateCommandList() { return std::make_shared<VulkanCommandList>(device); }
TextureRef VulkanRHI::CreateTexture(const TextureDesc &desc) { return nullptr; }
BufferRef VulkanRHI::CreateBuffer(const BufferDesc &desc) { return nullptr; }
DescriptorSetRef VulkanRHI::CreateDescriptorSet(const DescriptorSetDesc &desc) { return nullptr; }
ShaderRef VulkanRHI::CreateShader(const ShaderDesc &desc) { return nullptr; }
GraphicsPipelineRef VulkanRHI::CreateGraphicsPipeline(const GraphicsPipelineDesc &desc) { return nullptr; }
ComputePipelineRef VulkanRHI::CreateComputePipeline(const ComputePipelineDesc &desc) { return nullptr; }
} // namespace gfx::rhi::vk