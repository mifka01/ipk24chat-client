#pragma once
#include "State.hpp"

class StartState : public State {

public:
  StartState(Client &client) : State(client) {}
  void processInput() override;
};
