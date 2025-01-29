#pragma once

#include "gfx/rhi/rhi.h"

struct GLFWwindow;

namespace gfx::rhi::vk {
RHIRef CreateRhi(GLFWwindow *window, const Config &cfg);
} // namespace gfx::rhi::vk