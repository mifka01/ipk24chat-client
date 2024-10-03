#pragma once
#include "State.hpp"

class ErrorState : public State {

public:
  ErrorState(Client &client) : State(client) {}

  void onEnter() override;
};
