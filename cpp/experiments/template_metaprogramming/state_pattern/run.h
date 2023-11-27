#pragma once

#include <iostream>

#include "jump.h"
#include "state.h"

namespace state_pattern {

class run : public state {
 public:
  void handle(context& p_context) override;
};

}  // namespace state_pattern
