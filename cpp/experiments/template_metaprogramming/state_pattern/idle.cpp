#include "idle.h"

#include <iostream>

#include "context.h"
#include "run.h"

void state_pattern::idle::handle(context& p_context) {
  std::cout << "idle\n";
  p_context.set_state(new run());
}
