#include "app/app.h"
#include "gfx/rhi/rhi.h"

int main() {
  AppConfig cfg;
  cfg.rhi_config.debug = true;
  App app(cfg);

  gfx::rhi::CommandListRef commandList = app.rhi->create_command_list();

  app.run();
}