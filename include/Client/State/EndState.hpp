#pragma once
#include "State.hpp"

class EndState : public State {

public:
  EndState(Client &client) : State(client) {}

  void onEnter() override;
};
