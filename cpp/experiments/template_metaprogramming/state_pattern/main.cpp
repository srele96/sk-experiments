#include "context.h"
#include "run.h"

int main() {
  state_pattern::context context{};
  context.handle();
  context.handle();
  context.handle();
  context.handle();

  return 0;
}
