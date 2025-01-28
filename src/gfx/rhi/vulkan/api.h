#pragma once

#include "gfx/rhi/rhi.h"

struct GLFWwindow;

namespace gfx::rhi::vk {
RHIRef create_rhi(GLFWwindow *window, const Config &cfg);
} // namespace gfx::rhi::vk