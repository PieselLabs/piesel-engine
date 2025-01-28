#pragma once

#include <cstdint>
#include <glfw/glfw3.h>

#include "gfx/rhi/rhi.h"

struct AppConfig {
  uint32_t window_width{800};
  uint32_t window_height{600};

  gfx::rhi::Config rhi_config;
};

class App {
public:
  App(const AppConfig &config);

  virtual ~App();

  void run();

private:
  GLFWwindow *window_;
  gfx::rhi::RHIRef rhi_;
};