#pragma once
#include "State.hpp"

class AuthState : public State {

public:
  AuthState(Client &client) : State(client) {}
  void handleInput() override;
  void handleResponse() override;

  void handleReplyMessage(const ReplyMessage &message) override;
  void handleConfirmMessage(const ConfirmMessage &message) override;
};
