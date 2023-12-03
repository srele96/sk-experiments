#pragma once

namespace state_pattern {

class context;

class state {
 public:
  virtual void handle(context& p_context) = 0;
  virtual ~state() = default;
};

}  // namespace state_pattern
