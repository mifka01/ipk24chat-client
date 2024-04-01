#pragma once
#include <poll.h>
#include <sys/socket.h>
#include <memory>
#include <string>
#include "Client/State.hpp"
#include "Message/Message.hpp"
#include "Type.hpp"

namespace Client {
class Client;
}

namespace Protocol {

class Protocol {
 protected:
  const size_t BUFFER_SIZE = 1024;
  Client::Client& client;

 public:
  Protocol(Client::Client& client) : client(client) {}
  virtual ~Protocol() = default;

  virtual int socketType() = 0;
  virtual std::string toString() = 0;
  virtual Type getType() = 0;
  virtual void run() = 0;
  virtual void setNextState(Client::State state) = 0;
  virtual void send(std::unique_ptr<Message::Message> message) = 0;
  virtual std::unique_ptr<Message::Message> receive() = 0;

  bool processCommand(const std::string& message);
  void processInput();
  void processReply();

  std::unique_ptr<Message::Message> toMessage(
    const Message::Type message,
    const std::vector<std::string>& parameters);

  static std::shared_ptr<Protocol> fromString(const std::string& protocol,
                        Client::Client& client);
};

}  // namespace Protocol
