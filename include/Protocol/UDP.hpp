#pragma once
#include <string>
#include "Message/Message.hpp"
#include "Protocol.hpp"

namespace Protocol {
class UDP : public Protocol {
 public:
  UDP(Client::Session& session) : Protocol(session){};
  inline int socketType() override { return SOCK_DGRAM; }
  inline std::string toString() override { return "UDP"; }
  inline Type getType() override { return Type::UDP; }

  void send(int socket, std::unique_ptr<Message::Message> message) override;
  std::unique_ptr<Message::Message> receive(int socket) override;
};

}  // namespace Protocol
