#pragma once

#include "Client/Client.hpp"

class Client;

class State : public MessageHandler {

protected:
  Client &client;

public:
  State(Client &client) : client(client) {}

  virtual void handleInput() {}

  virtual void handleResponse() {}

  virtual void onEnter() {}

  virtual void handleReplyMessage(const ReplyMessage &message) override;
  virtual void handleErrMessage(const ErrMessage &message) override;
  virtual void handleByeMessage(const ByeMessage &message) override;
};
