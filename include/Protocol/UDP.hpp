#pragma once
#include <string>
#include "Client/State.hpp"
#include "Message/ConfirmMessage.hpp"
#include "Message/Message.hpp"
#include "Protocol.hpp"

namespace Protocol {
class UDP : public Protocol {
  bool processCommand(const std::string& message);
  bool processInput();
  void processReply();
  std::unique_ptr<Message::Message> lastSentMessage;
  Client::State nextState;
  Client::State lastState = Client::State::START;
  std::vector<uint16_t> receivedMessages;
  void confirm(uint16_t messageID);
  uint8_t curRetries = 0;

 public:
  UDP(Client::Client& client) : Protocol(client){};
  inline int socketType() override { return SOCK_DGRAM; }
  inline std::string toString() override { return "UDP"; }
  inline Type getType() override { return Type::UDP; }

  void setNextState(Client::State state) override;

  void run() override;

  void send(std::unique_ptr<Message::Message> message) override;
  std::unique_ptr<Message::Message> receive() override;
};

}  // namespace Protocol
