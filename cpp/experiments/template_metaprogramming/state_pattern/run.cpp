#include "run.h"

#include <iostream>

#include "context.h"
#include "jump.h"

void state_pattern::run::handle(context& p_context) {
  std::cout << "run\n";
  p_context.set_state(new jump{});
}
