#pragma once
#include <map>
#include <regex>
#include <string>
#include "Client/Session.hpp"
#include "Message/Message.hpp"
#include "Protocol.hpp"

namespace Protocol {
class TCP : public Protocol {
  const std::string username = "[a-zA-Z0-9\\-]{1,20}";
  const std::string secret = "[a-zA-Z0-9\\-]{1,128}";
  const std::string displayName = "[\\x21-\\x7E]{1,20}";
  const std::string content = "[\\x20-\\x7E]{1,1400}";
  const std::string channelID = "[a-zA-Z0-9\\-]{1,20}";
  const std::string clrf = "\\r\\n";

  const std::map<Message::Type, std::regex> regexes = {
      {Message::Type::MSG,
       std::regex("MSG FROM " + username + " IS " + content + clrf)},
      {Message::Type::REPLY, std::regex("REPLY (OK|NOK) IS " + content + clrf)},
      {Message::Type::ERR,
       std::regex("ERR FROM " + displayName + " IS " + content + clrf)},
      {Message::Type::BYE, std::regex("BYE" + clrf)},
  };

 public:
  int socketType() override;
  std::string toString() override;

  std::unique_ptr<Message::Message> toMessage(
      const Message::Type message,
      const std::vector<std::string>& parameters,
      Client::Session& session) override;

  void send(int socket, std::unique_ptr<Message::Message> message) override;
  std::unique_ptr<Message::Message> receive(int socket) override;
};

}  // namespace Protocol
