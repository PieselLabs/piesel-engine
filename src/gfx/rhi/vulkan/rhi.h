#pragma once

#include "device.h"
#include "gfx/rhi/rhi.h"
#include "swapchain.h"
#include <glfw/glfw3.h>
#include <vulkan/vulkan.h>

namespace gfx::rhi::vk {
struct VulkanCommandList : public CommandList {};
struct VulkanTexture : public Texture {};
struct VulkanBuffer : public Buffer {};
struct VulkanDescriptorSet : public DescriptorSet {};
struct VulkanShader : public Shader {
  VkShaderModule shader;
};
struct VulkanGraphicsPipeline : public GraphicsPipeline {};
struct VulkanComputePipeline : public ComputePipeline {};

template <typename T, typename VkT> struct VkTypeMapImpl {
  using Type = VkT;
};

template <typename T> struct VkTypeMap {};

template <> struct VkTypeMap<CommandList> : VkTypeMapImpl<CommandList, VulkanCommandList> {};
template <> struct VkTypeMap<Shader> : VkTypeMapImpl<Shader, VulkanShader> {};

template <typename T> auto rhi_cast(const std::shared_ptr<T> &val) {
  return std::static_pointer_cast<typename VkTypeMap<T>::Type>(val);
}

template <typename T> auto rhi_cast(std::shared_ptr<T> &&val) {
  return std::static_pointer_cast<typename VkTypeMap<T>::Type>(val);
}

class VulkanRHI : public RHI {
public:
  VulkanRHI(GLFWwindow *window, const Config &cfg);

  CommandListRef create_command_list(const CommandListDesc &desc) override;
  TextureRef create_texture(const TextureDesc &desc) override;
  BufferRef create_buffer(const BufferDesc &desc) override;
  DescriptorSetRef create_descriptor_set(const DescriptorSetDesc &desc) override;
  ShaderRef create_shader(const ShaderDesc &desc) override;
  GraphicsPipelineRef create_graphics_pipeline(const GraphicsPipelineDesc &desc) override;
  ComputePipelineRef create_compute_pipeline(const ComputePipelineDesc &desc) override;

private:
  std::shared_ptr<Device> context_;
  std::shared_ptr<Swapchain> swapchain_;
};
} // namespace gfx::rhi::vk