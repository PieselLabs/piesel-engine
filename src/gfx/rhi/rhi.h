#pragma once
#include <memory>

struct GLFWwindow;

namespace gfx::rhi {

struct CommandList {
  virtual void Begin() = 0;
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
struct ComputePipelineDesc {
  ShaderRef &Shader;
  PipelineLayoutRef &Layout;
  const char *Entry;
};

struct RHI {
  virtual CommandListRef CreateCommandList() = 0;
  virtual TextureRef CreateTexture(const TextureDesc &desc) = 0;
  virtual BufferRef CreateBuffer(const BufferDesc &desc) = 0;
  virtual DescriptorSetRef CreateDescriptorSet(const DescriptorSetDesc &desc) = 0;
  virtual ShaderRef CreateShader(const ShaderDesc &desc) = 0;
  virtual GraphicsPipelineRef CreateGraphicsPipeline(const GraphicsPipelineDesc &desc) = 0;
  virtual ComputePipelineRef CreateComputePipeline(const ComputePipelineDesc &desc) = 0;
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

RHIRef create_rhi(GLFWwindow *window, const Config &cfg);
} // namespace gfx::rhi