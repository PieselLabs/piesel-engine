#include "app/app.h"

int main() {
  AppConfig cfg;
  App app(cfg);
  app.run();
}