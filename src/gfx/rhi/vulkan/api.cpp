#include "rhi.h"

struct GLFWwindow;

namespace gfx::rhi::vk {
RHIRef create_rhi(GLFWwindow *window, const Config &cfg) { return std::make_shared<VulkanRHI>(window, cfg); }
} // namespace gfx::rhi::vk