#include "vk_engine.h"

int main(int argc, char *argv[]) {
  VulkanEngine engine;
  fmt::println("hello my friend\n");
  engine.init();

  engine.run();

  engine.cleanup();

  return 0;
}
