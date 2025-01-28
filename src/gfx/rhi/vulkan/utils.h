#pragma once
#include <cassert>
#include <vulkan/vulkan.h>

#define VK_SAFE_CALL(expr) assert((expr) == VK_SUCCESS)