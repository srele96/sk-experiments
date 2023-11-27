#pragma once

#include "state.h"

namespace state_pattern {

class context {
 public:
  context();

  void set_state(state* p_state);

  void handle();

 private:
  state* m_state;
};

}  // namespace state_pattern
