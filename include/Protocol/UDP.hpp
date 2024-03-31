#pragma once
#include <string>
#include "Message/Message.hpp"
#include "Protocol.hpp"

namespace Protocol {
class UDP : public Protocol {
  bool processCommand(const std::string& message);
  bool processInput();
  void processReply();

 public:
  UDP(Client::Client& client) : Protocol(client){};
  inline int socketType() override { return SOCK_DGRAM; }
  inline std::string toString() override { return "UDP"; }
  inline Type getType() override { return Type::UDP; }

  void run() override;

  void send(std::unique_ptr<Message::Message> message) override;
  std::unique_ptr<Message::Message> receive() override;
};

}  // namespace Protocol
