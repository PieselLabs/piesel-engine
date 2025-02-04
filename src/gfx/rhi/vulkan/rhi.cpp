#include "rhi.h"
#include "command_list.h"
#include "sync.h"
#include "utils.h"

#include <VkBootstrap.h>

namespace gfx::rhi::vk {

void VulkanRHI::InitVulkanDevice() {
  vkb::InstanceBuilder builder;

  // make the vulkan instance, with basic debug features
  auto instRet = builder.set_app_name("Example Vulkan Application")
                     .request_validation_layers(cfg.Debug)
                     .use_default_debug_messenger()
                     .require_api_version(1, 3, 0)
                     .build();

  vkb::Instance vkbInst = instRet.value();

  // grab the instance
  instance = vkbInst.instance;
  debugMessenger = vkbInst.debug_messenger;

  VK_SAFE_CALL(glfwCreateWindowSurface(instance, window, nullptr, &surface));

  VkPhysicalDeviceVulkan13Features features{.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES};
  features.dynamicRendering = true;
  features.synchronization2 = true;

  // vulkan 1.2 features
  VkPhysicalDeviceVulkan12Features features12{.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES};
  features12.bufferDeviceAddress = true;
  features12.descriptorIndexing = true;

  vkb::PhysicalDeviceSelector selector{vkbInst};
  vkb::PhysicalDevice vkbPhysicalDevice = selector.set_minimum_version(1, 3)
                                              .set_required_features_13(features)
                                              .set_required_features_12(features12)
                                              .set_surface(surface)
                                              .select()
                                              .value();

  vkb::DeviceBuilder deviceBuilder{vkbPhysicalDevice};
  vkb::Device vkbDevice = deviceBuilder.build().value();

  device = vkbDevice.device;

  physicalDevice = vkbPhysicalDevice.physical_device;
  graphicsQueue = vkbDevice.get_queue(vkb::QueueType::graphics).value();
  graphicsFamily = vkbDevice.get_queue_index(vkb::QueueType::graphics).value();

  VkCommandPoolCreateInfo commandPoolInfo = {};
  commandPoolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
  commandPoolInfo.pNext = nullptr;
  commandPoolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
  commandPoolInfo.queueFamilyIndex = graphicsFamily;

  VK_SAFE_CALL(vkCreateCommandPool(device, &commandPoolInfo, nullptr, &commandPool));
}

void VulkanRHI::InitSwapchain() {
  vkb::SwapchainBuilder swapchainBuilder{GetPhysicalDevice(), device, surface};

  format = VK_FORMAT_B8G8R8A8_UNORM;

  int width, height;
  glfwGetWindowSize(GetWindow(), &width, &height);

  vkb::Swapchain vkbSwapchain =
      swapchainBuilder
          //.use_default_format_selection()
          .set_desired_format(VkSurfaceFormatKHR{.format = format, .colorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR})
          // use vsync present mode
          .set_desired_present_mode(VK_PRESENT_MODE_FIFO_KHR)
          .set_desired_extent(width, height)
          .add_image_usage_flags(VK_IMAGE_USAGE_TRANSFER_DST_BIT)
          .build()
          .value();

  extent = vkbSwapchain.extent;
  // store swapchain and its related images
  swapchain = vkbSwapchain.swapchain;
  images = vkbSwapchain.get_images().value();
  views = vkbSwapchain.get_image_views().value();
}

VulkanRHI::VulkanRHI(GLFWwindow *window, const Config &cfg) : cfg(cfg), window(window), currentFrame(0) {
  InitVulkanDevice();
  InitSwapchain();
}

Config VulkanRHI::GetCfg() { return cfg; }
VkInstance VulkanRHI::GetInstance() { return instance; }
VkDebugUtilsMessengerEXT VulkanRHI::GetDebugMessenger() { return debugMessenger; }
VkPhysicalDevice VulkanRHI::GetPhysicalDevice() { return physicalDevice; }
VkDevice VulkanRHI::GetDevice() { return device; }
VkSurfaceKHR VulkanRHI::GetSurface() { return surface; }
VkQueue VulkanRHI::GetGraphicsQueue() { return graphicsQueue; }
uint32_t VulkanRHI::GetGraphicsFamily() { return graphicsFamily; }
VkCommandPool VulkanRHI::GetCommandPool() { return commandPool; }
GLFWwindow *VulkanRHI::GetWindow() { return window; }
uint64_t VulkanRHI::GetCurrentFrame() { return currentFrame; }

VkSwapchainKHR VulkanRHI::GetSwapchain() { return swapchain; }
VkImage VulkanRHI::GetCurrentSwapchainImage() { return images[swapchainImgIdx]; }

VkFormat VulkanRHI::GetFormat() { return format; }
std::vector<VkImage> VulkanRHI::GetImages() { return images; }
std::vector<VkImageView> VulkanRHI::GetViews() { return views; }
VkExtent2D VulkanRHI::GetExtent() { return extent; }

CommandListRef VulkanRHI::CreateCommandList() { return std::make_shared<VulkanCommandList>(shared_from_this()); }
TextureRef VulkanRHI::CreateTexture(const TextureDesc &desc) { return nullptr; }
BufferRef VulkanRHI::CreateBuffer(const BufferDesc &desc) { return nullptr; }
DescriptorSetRef VulkanRHI::CreateDescriptorSet(const DescriptorSetDesc &desc) { return nullptr; }
ShaderRef VulkanRHI::CreateShader(const ShaderDesc &desc) { return nullptr; }
GraphicsPipelineRef VulkanRHI::CreateGraphicsPipeline(const GraphicsPipelineDesc &desc) { return nullptr; }
ComputePipelineRef VulkanRHI::CreateComputePipeline(const ComputePipelineDesc &desc) { return nullptr; }
SemaphoreRef VulkanRHI::CreateSemaphore() { return std::make_shared<VulkanSemaphore>(shared_from_this()); }
FenceRef VulkanRHI::CreateFence() { return std::make_shared<VulkanFence>(shared_from_this()); }

VulkanRHI::~VulkanRHI() {
  vkDeviceWaitIdle(device);
  vkDestroyCommandPool(device, commandPool, nullptr);

  // Destroy Swapchain
  vkDestroySwapchainKHR(device, swapchain, nullptr);
  for (int i = 0; i < views.size(); i++) {
    vkDestroyImageView(device, views[i], nullptr);
  }

  vkDestroySurfaceKHR(instance, surface, nullptr);
  vkDestroyDevice(device, nullptr);
  vkb::destroy_debug_utils_messenger(instance, debugMessenger);
  vkDestroyInstance(instance, nullptr);
}

void VulkanRHI::StartFrame(SemaphoreRef &semaphore) {
  VulkanSemaphore *vkSemaphore = static_cast<VulkanSemaphore *>(semaphore.get());

  VK_SAFE_CALL(vkAcquireNextImageKHR(device, swapchain, 1000000000, vkSemaphore->Get(), nullptr, &swapchainImgIdx));
}

void VulkanRHI::EndFrame() { currentFrame = (currentFrame + 1) % cfg.InFlightFrames; }

void VulkanRHI::Submit(CommandListRef commandList, const std::vector<SemaphoreRef> &waitSemaphores,
                       const std::vector<SemaphoreRef> &signalSemaphores, FenceRef signalFence) {
  VulkanCommandList *vkCommandList = static_cast<VulkanCommandList *>(commandList.get());

  std::vector<VkSemaphoreSubmitInfo> vkWaitSemaphores(waitSemaphores.size());
  for (int i = 0; i < waitSemaphores.size(); i++) {
    VkSemaphore semaphore = static_cast<VulkanSemaphore *>(waitSemaphores[i].get())->Get();

    VkSemaphoreSubmitInfo info{};
    info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO;
    info.deviceIndex = 0;
    info.pNext = nullptr;
    info.value = 1;
    info.semaphore = semaphore;
    info.stageMask = VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT_KHR;

    vkWaitSemaphores[i] = info;
  }

  std::vector<VkSemaphoreSubmitInfo> vkSignalSemaphores(signalSemaphores.size());
  for (int i = 0; i < signalSemaphores.size(); i++) {
    VkSemaphore semaphore = static_cast<VulkanSemaphore *>(signalSemaphores[i].get())->Get();

    VkSemaphoreSubmitInfo info{};
    info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO;
    info.deviceIndex = 0;
    info.pNext = nullptr;
    info.value = 1;
    info.semaphore = semaphore;
    info.stageMask = VK_PIPELINE_STAGE_2_ALL_GRAPHICS_BIT;

    vkSignalSemaphores[i] = info;
  }

  VkCommandBufferSubmitInfo info{};
  info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_SUBMIT_INFO;
  info.commandBuffer = vkCommandList->Get();
  info.deviceMask = 0;
  info.pNext = nullptr;

  VkSubmitInfo2 submitInfo{};
  submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO_2;
  submitInfo.pNext = nullptr;
  submitInfo.waitSemaphoreInfoCount = waitSemaphores.size();
  submitInfo.pWaitSemaphoreInfos = vkWaitSemaphores.data();
  submitInfo.signalSemaphoreInfoCount = signalSemaphores.size();
  submitInfo.pSignalSemaphoreInfos = vkSignalSemaphores.data();
  submitInfo.commandBufferInfoCount = 1;
  submitInfo.pCommandBufferInfos = &info;

  VkFence vkSignalFence = static_cast<VulkanFence *>(signalFence.get())->Get();

  VK_SAFE_CALL(vkQueueSubmit2(graphicsQueue, 1, &submitInfo, vkSignalFence));
}

void VulkanRHI::Present(SemaphoreRef &semaphore) {
  VkSemaphore vkSemaphore = static_cast<VulkanSemaphore *>(semaphore.get())->Get();

  VkPresentInfoKHR presentInfo = {};
  presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
  presentInfo.pNext = nullptr;
  presentInfo.pSwapchains = &swapchain;
  presentInfo.swapchainCount = 1;

  presentInfo.pWaitSemaphores = &vkSemaphore;
  presentInfo.waitSemaphoreCount = 1;

  presentInfo.pImageIndices = &swapchainImgIdx;

  VK_SAFE_CALL(vkQueuePresentKHR(graphicsQueue, &presentInfo));
}

void VulkanRHI::WaitIdle() {
  vkQueueWaitIdle(graphicsQueue);
  vkDeviceWaitIdle(device);
}

} // namespace gfx::rhi::vk