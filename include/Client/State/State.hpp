#pragma once

#include "Client/Client.hpp"

class Client;

class State {

protected:
  Client &client;

public:
  State(Client &client) : client(client) {}
  using MessageConverter = std::function<void(const Message &)>;
  const std::unordered_map<MessageType, MessageConverter> messageConverters = {
      {MessageType::REPLY,
       [this](const Message &message) {
         handleReplyMessage(dynamic_cast<const ReplyMessage &>(message));
       }},
      {MessageType::ERR,
       [this](const Message &message) {
         handleErrMessage(dynamic_cast<const ErrMessage &>(message));
       }},

      {MessageType::BYE,
       [this](const Message &message) {
         handleByeMessage(dynamic_cast<const ByeMessage &>(message));
       }},
  };

  virtual void handleInput() {}

  virtual void handleResponse() {}

  virtual void onEnter() {}

  virtual void handleReplyMessage(const ReplyMessage &message);
  virtual void handleErrMessage(const ErrMessage &message);
  virtual void handleByeMessage(const ByeMessage &message);
};
