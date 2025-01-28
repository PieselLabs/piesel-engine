#include "app.h"
#include "gfx/rhi/rhi.h"

App::App(const AppConfig &config) {
  glfwInit();
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
  window_ = glfwCreateWindow(config.window_width, config.window_height, "Vulkan", nullptr, nullptr);
  rhi_ = gfx::rhi::create_rhi(window_, config.rhi_config);
}

App::~App() {
  glfwDestroyWindow(window_);
  glfwTerminate();
}

void App::run() {
  while (!glfwWindowShouldClose(window_)) {
    glfwPollEvents();
  }
}