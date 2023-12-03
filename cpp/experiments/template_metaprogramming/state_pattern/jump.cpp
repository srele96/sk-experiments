#include "jump.h"

#include <iostream>

#include "context.h"
#include "idle.h"

void state_pattern::jump::handle(context& p_context) {
  std::cout << "jump\n";
  p_context.set_state(new idle{});
}
