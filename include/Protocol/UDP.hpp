#pragma once
#include <string>

#include "Client/State.hpp"
#include "Message/Message.hpp"
#include "Protocol.hpp"

namespace Protocol {
class UDP : public Protocol {
 protected:
  std::unique_ptr<Message::Message> lastSentMessage;
  Client::State nextState;
  Client::State lastState = Client::State::START;
  std::vector<uint16_t> receivedMessages;
  uint8_t curRetries = 0;

  void confirm(uint16_t messageID);
  void processReply();

 public:
  UDP(Client::Client& client) : Protocol(client){};
  ~UDP() override = default;

  int socketType() override { return SOCK_DGRAM; }
  std::string toString() override { return "UDP"; }
  Type getType() override { return Type::UDP; }

  void setNextState(Client::State state) override;
  void run() override;
  void send(std::unique_ptr<Message::Message> message) override;
  std::unique_ptr<Message::Message> receive() override;
};

}  // namespace Protocol
