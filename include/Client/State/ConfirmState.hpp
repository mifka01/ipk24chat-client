#pragma once
#include "State.hpp"

class ConfirmState : public State {

public:
  ConfirmState(Client &client) : State(client) {}
  void handleInput() override;
  void handleResponse() override;
};
