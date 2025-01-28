#pragma once
#include <cassert>
#include <vulkan/vulkan.h>

#define VK_SAFE_CALL(expr) assert((expr) == VK_SUCCESS)

namespace gfx::rhi::vk {
const size_t MAX_FRAMES_IN_FLIGHT = 3;
}