#include "Protocol/TCP.hpp"
#include <regex>
#include "Message/ByeMessage.hpp"
#include "Message/ErrMessage.hpp"
#include "Message/MsgMessage.hpp"
#include "Message/ReplyMessage.hpp"
#include "utils.hpp"

namespace Protocol {

void TCP::send(int socket, std::unique_ptr<Message::Message> message) {
  std::string msg = message->tcpSerialize();
  ::send(socket, msg.c_str(), msg.size(), 0);
  session.messagesSent++;
}

std::unique_ptr<Message::Message> TCP::receive(int socket) {
  char buffer[4096];
  int bytesReceived = recv(socket, buffer, 1024, 0);
  if (bytesReceived == -1) {
    throw std::runtime_error("Failed to receive message");
  }

  if (bytesReceived == 0) {
    return std::make_unique<Message::ByeMessage>(Message::ByeMessage(0));
  }

  std::string msg(buffer, bytesReceived);

  std::vector<std::string> tokens = totokens(msg);

  for (const auto& [type, regex] : regexes) {
    switch (type) {
      case Message::Type::ERR: {
        if (std::regex_match(msg, regex)) {
          std::string content = msg.substr(msg.find(tokens[4]));
          content.erase(content.size() - 2);
          return std::make_unique<Message::ErrMessage>(
              Message::ErrMessage(0, tokens[2], content));
        }
        break;
      }
      case Message::Type::REPLY: {
        if (std::regex_match(msg, regex)) {
          std::string content = msg.substr(msg.find(tokens[3]));
          content.erase(content.size() - 2);
          return std::make_unique<Message::ReplyMessage>(
              Message::ReplyMessage(0, tokens[1] == "OK", content));
        }
        break;
      }
      case Message::Type::MSG: {
        if (std::regex_match(msg, regex)) {
          std::string content = msg.substr(msg.find(tokens[4]));
          content.erase(content.size() - 2);
          return std::make_unique<Message::MsgMessage>(
              Message::MsgMessage(0, tokens[2], content));
        }
        break;
      }
      case Message::Type::BYE: {
        if (std::regex_match(msg, regex)) {
          return std::make_unique<Message::ByeMessage>(Message::ByeMessage(0));
        }
        break;
      }
      default:
        throw std::runtime_error("Invalid message type");
    }
  }
  throw std::runtime_error("Failed to parse message");
}

}  // namespace Protocol
