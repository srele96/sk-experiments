#include "context.h"

#include "idle.h"
#include "state.h"

state_pattern::context::context() : m_state{new idle{}} {}

void state_pattern::context::set_state(state* p_state) { m_state = p_state; }

void state_pattern::context::handle() { m_state->handle(*this); }
