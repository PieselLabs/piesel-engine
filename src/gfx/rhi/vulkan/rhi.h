#pragma once

#include "gfx/rhi/rhi.h"
#include "vk_defs.h"
#include <glfw/glfw3.h>
#include <memory>
#include <vector>
#include <vulkan/vulkan.h>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace gfx::rhi::vk {
class VulkanRHI : public RHI, public std::enable_shared_from_this<VulkanRHI> {
public:
  VulkanRHI(GLFWwindow *window, const Config &cfg);

  Config GetCfg();
  VkInstance GetInstance();
  VkDebugUtilsMessengerEXT GetDebugMessenger();
  VkPhysicalDevice GetPhysicalDevice();
  VkDevice GetDevice();
  VkSurfaceKHR GetSurface();
  VkQueue GetGraphicsQueue();
  uint32_t GetGraphicsFamily();
  VkCommandPool GetCommandPool();
  GLFWwindow *GetWindow();
  uint64_t GetCurrentFrame();

  VkSwapchainKHR GetSwapchain();
  VkImage GetCurrentSwapchainImage();
  VkFormat GetFormat();
  std::vector<VkImage> GetImages();
  std::vector<VkImageView> GetViews();
  VkExtent2D GetExtent();

  CommandListRef CreateCommandList() override;
  TextureRef CreateTexture(const TextureDesc &desc) override;
  BufferRef CreateBuffer(const BufferDesc &desc) override;
  DescriptorSetRef CreateDescriptorSet(const DescriptorSetDesc &desc) override;
  ShaderRef CreateShader(const ShaderDesc &desc) override;
  GraphicsPipelineRef CreateGraphicsPipeline(const GraphicsPipelineDesc &desc) override;
  ComputePipelineRef CreateComputePipeline(const ComputePipelineDesc &desc) override;
  SemaphoreRef CreateSemaphore() override;
  FenceRef CreateFence() override;

  void StartFrame(SemaphoreRef &semaphore) override;
  void EndFrame() override;

  void Submit(CommandListRef commandList, const std::vector<SemaphoreRef> &waitSemaphores,
              const std::vector<SemaphoreRef> &signalSemaphores, FenceRef signalFence) override;

  void Present(SemaphoreRef &semaphore) override;
  void WaitIdle() override;

  ~VulkanRHI();

private:
  // VulkanDevice;
  Config cfg;
  VkInstance instance;
  VkDebugUtilsMessengerEXT debugMessenger;
  VkPhysicalDevice physicalDevice;
  VkDevice device;
  VkSurfaceKHR surface;
  VkQueue graphicsQueue;
  uint32_t graphicsFamily;
  VkCommandPool commandPool;
  GLFWwindow *window;

  void InitVulkanDevice();

  // Swapchain
  VkSwapchainKHR swapchain;
  VkFormat format;
  std::vector<VkImage> images;
  std::vector<VkImageView> views;
  VkExtent2D extent;

  uint64_t currentFrame;
  uint32_t swapchainImgIdx;

  void InitSwapchain();
};
} // namespace gfx::rhi::vk