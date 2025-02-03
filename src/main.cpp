#include "app/app.h"
#include "gfx/rhi/rhi.h"

class MyApp : public App {
public:
  MyApp(AppConfig &cfg) : App(cfg) {
    renderSemaphore = rhi->CreateSemaphore();
    commandList = rhi->CreateCommandList();
  }

  void update() override {
    frame++;
    commandList->Begin();
    commandList->Flash(frame);
    commandList->End();

    rhi->Submit(commandList, {swapchainSemaphore}, {renderSemaphore}, renderFence);
    rhi->Present(renderSemaphore);
  }

private:
  gfx::rhi::SemaphoreRef renderSemaphore;
  gfx::rhi::CommandListRef commandList;
  int frame = 0;
};

int main() {
  AppConfig cfg;
  cfg.RhiConfig.Debug = true;
  MyApp app(cfg);

  app.run();
}