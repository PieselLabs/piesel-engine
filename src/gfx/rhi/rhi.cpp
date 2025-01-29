#include "rhi.h"
#include "gfx/rhi/vulkan/api.h"
#include <cassert>

struct GLFWwindow;

namespace gfx::rhi {
RHIRef create_rhi(GLFWwindow *window, const Config &cfg) {
  switch (cfg.Backend) {
  case Backend::Vulkan:
    return vk::create_rhi(window, cfg);
  }
  assert(false);
  return nullptr;
}

} // namespace gfx::rhi