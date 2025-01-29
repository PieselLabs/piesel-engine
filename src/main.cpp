#include "app/app.h"
#include "gfx/rhi/rhi.h"

int main() {
  AppConfig cfg;
  cfg.RhiConfig.Debug = true;
  App app(cfg);

  gfx::rhi::CommandListRef commandList = app.rhi->CreateCommandList();

  app.run();
}