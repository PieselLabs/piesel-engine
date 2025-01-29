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

  CommandListRef CreateCommandList() override;
  TextureRef CreateTexture(const TextureDesc &desc) override;
  BufferRef CreateBuffer(const BufferDesc &desc) override;
  DescriptorSetRef CreateDescriptorSet(const DescriptorSetDesc &desc) override;
  ShaderRef CreateShader(const ShaderDesc &desc) override;
  GraphicsPipelineRef CreateGraphicsPipeline(const GraphicsPipelineDesc &desc) override;
  ComputePipelineRef CreateComputePipeline(const ComputePipelineDesc &desc) override;
  SemaphoreRef CreateSemphore() override;
  FenceRef CreateFence() override;

private:
  std::shared_ptr<VulkanDevice> device;
  std::shared_ptr<Swapchain> swapchain;
};
} // namespace gfx::rhi::vk