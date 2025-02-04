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
  gfx::rhi::FenceRef renderFence = rhi->CreateFence();

  gfx::rhi::SemaphoreRef swapchainSemaphore = rhi->CreateSemaphore();
  gfx::rhi::SemaphoreRef renderSemaphore = rhi->CreateSemaphore();
  gfx::rhi::CommandListRef commandList = rhi->CreateCommandList();

  int frame = 0;
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();

    renderFence->Wait();
    renderFence->Reset();
    rhi->StartFrame(swapchainSemaphore);

    frame++;
    commandList->Begin();
    commandList->Flash(frame);
    commandList->End();

    rhi->Submit(commandList, {swapchainSemaphore}, {renderSemaphore}, renderFence);
    rhi->Present(renderSemaphore);

    rhi->EndFrame();
  }

  rhi->WaitIdle();
}