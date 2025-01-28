#pragma once
#include <memory>

struct GLFWwindow;

namespace gfx::rhi {

struct CommandList {};
using CommandListRef = std::shared_ptr<CommandList>;
struct CommandListDesc {};

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
  ShaderRef &shader;
  PipelineLayoutRef &layout;
  const char *entry;
};

struct RHI {
  virtual CommandListRef create_command_list(const CommandListDesc &desc) = 0;
  virtual TextureRef create_texture(const TextureDesc &desc) = 0;
  virtual BufferRef create_buffer(const BufferDesc &desc) = 0;
  virtual DescriptorSetRef create_descriptor_set(const DescriptorSetDesc &desc) = 0;
  virtual ShaderRef create_shader(const ShaderDesc &desc) = 0;
  virtual GraphicsPipelineRef create_graphics_pipeline(const GraphicsPipelineDesc &desc) = 0;
  virtual ComputePipelineRef create_compute_pipeline(const ComputePipelineDesc &desc) = 0;
};

using RHIRef = std::shared_ptr<RHI>;

enum class Backend {
  Vulkan,
};

struct Config {
  Backend backend = Backend::Vulkan;
  bool debug{false};
};

RHIRef create_rhi(GLFWwindow *window, const Config &cfg);
} // namespace gfx::rhi