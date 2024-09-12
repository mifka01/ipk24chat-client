#pragma once
#include "State.hpp"

class AuthState : public State {

public:
  AuthState(Client &client) : State(client) {}
  void processInput() override;
};
