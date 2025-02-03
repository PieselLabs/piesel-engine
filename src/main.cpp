#include "app/app.h"
#include "gfx/rhi/rhi.h"

class MyApp : public App {
public:
  MyApp(AppConfig &cfg) : App(cfg) {
    renderFence = rhi->CreateFence();
    swapchainSemaphore = rhi->CreateSemaphore();
    renderSemaphore = rhi->CreateSemaphore();
    commandList = rhi->CreateCommandList();
  }

  void update() override {
    renderFence->Wait();
    renderFence->Reset();
  }

private:
  gfx::rhi::FenceRef renderFence;
  gfx::rhi::SemaphoreRef swapchainSemaphore;
  gfx::rhi::SemaphoreRef renderSemaphore;
  gfx::rhi::CommandListRef commandList;
};

int main() {
  AppConfig cfg;
  cfg.RhiConfig.Debug = true;
  MyApp app(cfg);

  app.run();
}