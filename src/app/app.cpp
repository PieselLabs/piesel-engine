#include "app.h"
#include "gfx/rhi/rhi.h"

App::App(const AppConfig &config) {
  glfwInit();
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
  window = glfwCreateWindow(config.WindowWidth, config.WindowHeight, "Vulkan", nullptr, nullptr);
  rhi = gfx::rhi::CreateRhi(window, config.RhiConfig);
  swapchainSemaphore = rhi->CreateSemaphore();
  renderFence = rhi->CreateFence();
}

App::~App() {
  glfwDestroyWindow(window);
  glfwTerminate();
}

void App::run() {
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();

    renderFence->Wait();
    renderFence->Reset();
    rhi->StartFrame(swapchainSemaphore);
    update();
    rhi->EndFrame();
  }
}