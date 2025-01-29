#include "rhi.h"
#include "gfx/rhi/vulkan/api.h"
#include <cassert>

struct GLFWwindow;

namespace gfx::rhi {
RHIRef CreateRhi(GLFWwindow *window, const Config &cfg) {
  switch (cfg.Backend) {
  case Backend::Vulkan:
    return vk::CreateRhi(window, cfg);
  }
  assert(false);
  return nullptr;
}

} // namespace gfx::rhi