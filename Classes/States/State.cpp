#include "State.h"

using namespace States;

State::StateStatus State::sExecuting = "executing";
State::StateStatus State::sDeath = "death";

State::State(Properties::PropertyContainer& properties) : m_properties(properties) {

}

bool State::checkDeath() {
  return false;
}