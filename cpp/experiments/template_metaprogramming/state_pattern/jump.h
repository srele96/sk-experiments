#pragma once

#include "context.h"
#include "state.h"

namespace state_pattern {

class jump : public state {
 public:
  void handle(context& p_context) override;
};

}  // namespace state_pattern
