#pragma once
#include <map>
#include <regex>
#include <string>
#include "Message/Message.hpp"
#include "Protocol.hpp"

namespace Protocol {
class TCP : public Protocol {
 protected:
  const std::map<Message::Type, std::regex> regexes = {
      {Message::Type::MSG,
       std::regex("MSG FROM " + Message::Pattern::USERNAME + " IS " +
                  Message::Pattern::CONTENT + Message::Pattern::CLRF)},
      {Message::Type::REPLY,
       std::regex("REPLY (OK|NOK) IS " + Message::Pattern::CONTENT +
                  Message::Pattern::CLRF)},
      {Message::Type::ERR,
       std::regex("ERR FROM " + Message::Pattern::DISPLAY_NAME + " IS " +
                  Message::Pattern::CONTENT + Message::Pattern::CLRF)},
      {Message::Type::BYE, std::regex("BYE" + Message::Pattern::CLRF)},
  };

 public:
  TCP(Client::Client& client) : Protocol(client){};
  ~TCP() override = default;

  int socketType() override { return SOCK_STREAM; }
  std::string toString() override { return "TCP"; }
  Type getType() override { return Type::TCP; }

  void setNextState(Client::State state) override;
  void run() override;
  void send(std::unique_ptr<Message::Message> message) override;
  std::unique_ptr<Message::Message> receive() override;
};

}  // namespace Protocol
