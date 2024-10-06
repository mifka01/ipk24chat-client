#pragma once

#include "Client/Client.hpp"
#include "Message/MessageHandler.hpp"

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
  virtual void handleMsgMessage(const MsgMessage &message) override;
  virtual void handleByeMessage(const ByeMessage &message) override;

  virtual void handleSigInt() {}
};
