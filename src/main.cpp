#include "app/app.h"
#include "gfx/rhi/rhi.h"

int main() {
  AppConfig cfg;
  cfg.RhiConfig.Debug = true;
  cfg.RhiConfig.InFlightFrames = 3;
  App app(cfg);
  app.run();
}