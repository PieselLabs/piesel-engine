#pragma once

#include <cstdint>
#include <glfw/glfw3.h>

#include "gfx/rhi/rhi.h"

struct AppConfig {
  uint32_t WindowWidth{800};
  uint32_t WindowHeight{600};

  gfx::rhi::Config RhiConfig;
};

class App {
public:
  App(const AppConfig &config);

  virtual ~App();

  void run();

  virtual void update() = 0;

  GLFWwindow *window;
  gfx::rhi::RHIRef rhi;
};