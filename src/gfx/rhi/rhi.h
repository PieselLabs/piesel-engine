#pragma once
#include <memory>
#include <vector>

struct GLFWwindow;

namespace gfx::rhi {

struct CommandList {
  virtual void Begin() = 0;
  virtual void End() = 0;
  virtual void Flash(int frame) = 0;
};
using CommandListRef = std::shared_ptr<CommandList>;

struct Texture {};
using TextureRef = std::shared_ptr<Texture>;
struct TextureDesc {};

struct Buffer {};
using BufferRef = std::shared_ptr<Buffer>;
struct BufferDesc {};

struct DescriptorSet {};
using DescriptorSetRef = std::shared_ptr<DescriptorSet>;
struct DescriptorSetDesc {};

struct Shader {};
using ShaderRef = std::shared_ptr<Shader>;
struct ShaderDesc {};

struct GraphicsPipeline {};
using GraphicsPipelineRef = std::shared_ptr<GraphicsPipeline>;
struct GraphicsPipelineDesc {};

struct PipelineLayout {};
using PipelineLayoutRef = std::shared_ptr<PipelineLayout>;
struct PipelineLayoutDesc {};

struct ComputePipeline {};
using ComputePipelineRef = std::shared_ptr<ComputePipeline>;
struct ComputePipelineDesc {};

struct Semaphore {};
using SemaphoreRef = std::shared_ptr<Semaphore>;

struct Fence {
  virtual void Wait() = 0;
  virtual void Reset() = 0;
};
using FenceRef = std::shared_ptr<Fence>;

struct RHI {
  virtual CommandListRef CreateCommandList() = 0;
  virtual TextureRef CreateTexture(const TextureDesc &desc) = 0;
  virtual BufferRef CreateBuffer(const BufferDesc &desc) = 0;
  virtual DescriptorSetRef CreateDescriptorSet(const DescriptorSetDesc &desc) = 0;
  virtual ShaderRef CreateShader(const ShaderDesc &desc) = 0;
  virtual GraphicsPipelineRef CreateGraphicsPipeline(const GraphicsPipelineDesc &desc) = 0;
  virtual ComputePipelineRef CreateComputePipeline(const ComputePipelineDesc &desc) = 0;
  virtual SemaphoreRef CreateSemaphore() = 0;
  virtual FenceRef CreateFence() = 0;
  virtual void StartFrame(SemaphoreRef &semaphore) = 0;
  virtual void EndFrame() = 0;
  virtual void Submit(CommandListRef commandList, const std::vector<SemaphoreRef> &waitSemaphores,
                      const std::vector<SemaphoreRef> &signalSemaphores, FenceRef signalFence) = 0;
  virtual void Present(SemaphoreRef &semaphore) = 0;
  virtual void WaitIdle() = 0;
  virtual ~RHI() = default;
};

using RHIRef = std::shared_ptr<RHI>;

enum class Backend {
  Vulkan,
};

struct Config {
  Backend Backend = Backend::Vulkan;
  bool Debug{false};
  int InFlightFrames{3}; // min 1, max 3
};

RHIRef CreateRhi(GLFWwindow *window, const Config &cfg);
} // namespace gfx::rhi