#pragma once
#include <sys/socket.h>
#include <string>
#include "Client/Session.hpp"
#include "Message/Message.hpp"

namespace Protocol {

class Protocol {
 public:
  virtual int socketType() = 0;
  virtual std::string toString() = 0;

  virtual std::unique_ptr<Message::Message> toMessage(
      const Message::Type message,
      const std::vector<std::string>& parameters,
      Client::Session& session) = 0;

  virtual void send(int socket, std::unique_ptr<Message::Message> message) = 0;
  virtual std::unique_ptr<Message::Message> receive(int socket) = 0;
};

}  // namespace Protocol
