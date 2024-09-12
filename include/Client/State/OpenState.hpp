#pragma once
#include "State.hpp"

class OpenState : public State {

public:
  OpenState(Client &client) : State(client) {}
  void handleInput() override;
  void handleResponse() override;
};
