#pragma once
#include <map>
#include <regex>
#include <string>
#include "Message/Message.hpp"
#include "Protocol.hpp"

namespace Protocol {
class TCP : public Protocol {
  const std::string clrf = "\\r\\n";

  const std::map<Message::Type, std::regex> regexes = {
      {Message::Type::MSG,
       std::regex("MSG FROM " + Message::Pattern::username + " IS " +
                  Message::Pattern::content + clrf)},
      {Message::Type::REPLY,
       std::regex("REPLY (OK|NOK) IS " + Message::Pattern::content + clrf)},
      {Message::Type::ERR,
       std::regex("ERR FROM " + Message::Pattern::displayName + " IS " +
                  Message::Pattern::content + clrf)},
      {Message::Type::BYE, std::regex("BYE" + clrf)},
  };

  bool processCommand(const std::string& message);
  void processInput();
  void processReply();

 public:
  TCP(Client::Client& client) : Protocol(client){};
  inline int socketType() override { return SOCK_STREAM; }
  inline std::string toString() override { return "TCP"; }
  inline Type getType() override { return Type::TCP; }

  void run() override;

  void send(std::unique_ptr<Message::Message> message) override;
  std::unique_ptr<Message::Message> receive() override;
};

}  // namespace Protocol
