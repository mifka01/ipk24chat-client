#pragma once
#include <sys/socket.h>
#include <string>
#include "Client/Session.hpp"
#include "Message/Message.hpp"
#include "Type.hpp"

namespace Protocol {

class Protocol {
 protected:
  Client::Session& session;

 public:
  Protocol(Client::Session& session) : session(session) {}
  virtual int socketType() = 0;
  virtual std::string toString() = 0;
  virtual Type getType() = 0;
  virtual ~Protocol() = default;

  std::unique_ptr<Message::Message> toMessage(
      const Message::Type message,
      const std::vector<std::string>& parameters);

  static std::shared_ptr<Protocol> fromString(const std::string& protocol,
                                              Client::Session& session);

  virtual void send(int socket, std::unique_ptr<Message::Message> message) = 0;
  virtual std::unique_ptr<Message::Message> receive(int socket) = 0;
};

}  // namespace Protocol
