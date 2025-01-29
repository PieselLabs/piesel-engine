#include "app.h"
#include "gfx/rhi/rhi.h"

App::App(const AppConfig &config) {
  glfwInit();
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
  window = glfwCreateWindow(config.WindowWidth, config.WindowHeight, "Vulkan", nullptr, nullptr);
  rhi = gfx::rhi::CreateRhi(window, config.RhiConfig);
}

App::~App() {
  glfwDestroyWindow(window);
  glfwTerminate();
}

void App::run() {
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    update();
  }
}