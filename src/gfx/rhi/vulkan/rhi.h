#pragma once

#include "device.h"
#include "gfx/rhi/rhi.h"
#include "swapchain.h"
#include <glfw/glfw3.h>
#include <vulkan/vulkan.h>

namespace gfx::rhi::vk {
class VulkanRHI : public RHI {
public:
  VulkanRHI(GLFWwindow *window, const Config &cfg);

  CommandListRef create_command_list() override;
  TextureRef create_texture(const TextureDesc &desc) override;
  BufferRef create_buffer(const BufferDesc &desc) override;
  DescriptorSetRef create_descriptor_set(const DescriptorSetDesc &desc) override;
  ShaderRef create_shader(const ShaderDesc &desc) override;
  GraphicsPipelineRef create_graphics_pipeline(const GraphicsPipelineDesc &desc) override;
  ComputePipelineRef create_compute_pipeline(const ComputePipelineDesc &desc) override;

private:
  std::shared_ptr<Device> device;
  std::shared_ptr<Swapchain> swapchain_;
};
} // namespace gfx::rhi::vk