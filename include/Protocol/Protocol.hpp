#pragma once
#include <poll.h>
#include <sys/socket.h>
#include <string>
#include "Message/Message.hpp"
#include "Type.hpp"

namespace Client {
class Client;
}

namespace Protocol {

class Protocol {
 protected:
  Client::Client& client;

 public:
  Protocol(Client::Client& client) : client(client) {}
  virtual int socketType() = 0;
  virtual std::string toString() = 0;
  virtual Type getType() = 0;
  virtual ~Protocol() = default;

  virtual void run() = 0;

  std::unique_ptr<Message::Message> toMessage(
      const Message::Type message,
      const std::vector<std::string>& parameters);

  static std::shared_ptr<Protocol> fromString(const std::string& protocol,
                                              Client::Client& client);

  virtual void send(std::unique_ptr<Message::Message> message) = 0;
  virtual std::unique_ptr<Message::Message> receive() = 0;
};

}  // namespace Protocol
