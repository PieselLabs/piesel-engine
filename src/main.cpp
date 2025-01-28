#include "app/app.h"

int main() {
  AppConfig cfg;
  cfg.rhi_config.debug = true;
  App app(cfg);
  app.run();
}