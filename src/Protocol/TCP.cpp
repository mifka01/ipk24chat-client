/**
 * @file src/Protocol/TCP.cpp
 * @author Radim Mifka (xmifka00)
 * @date March 2024
 */
#include "Protocol/TCP.hpp"
#include <unistd.h>
#include <regex>
#include "Client/Client.hpp"
#include "Client/State.hpp"
#include "Message/ByeMessage.hpp"
#include "Message/ErrMessage.hpp"
#include "Message/MsgMessage.hpp"
#include "Message/ReplyMessage.hpp"
#include "utils.hpp"

namespace Protocol {

void TCP::send(std::unique_ptr<Message::Message> message) {
  std::string msg = message->tcpSerialize();
  ::send(client.socket, msg.c_str(), msg.size(), 0);
  client.messagesSent++;
  lastSentMessage = std::move(message);
}

std::unique_ptr<Message::Message> TCP::receive() {
  char buffer[BUFFER_SIZE];
  int bytesReceived = recv(client.socket, buffer, BUFFER_SIZE, 0);
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
  send(toMessage(Message::Type::ERR, {"Invalid format of message"}));
  throw std::runtime_error("Invalid format of message");
}

void TCP::setNextState(Client::State state) {
  client.state = state;
}

void TCP::run() {
  client.poller.addSocket(STDIN_FILENO, POLLIN);
  client.poller.addSocket(client.socket, POLLIN);

  while (true) {
    if (client.state == Client::State::END) {
      if (lastSentMessage->type != Message::Type::BYE) {
        client.protocol->send(
            client.protocol->toMessage(Message::Type::BYE, {}));
      }
      break;
    } else {
      int events = client.poller.poll();
      if (events < 0) {
        throw std::runtime_error("Failed to poll");
      }

      if (client.poller.hasEvent(0, POLLIN)) {
        processInput();
      }
      if (client.poller.hasEvent(1, POLLIN)) {
        processReply();
      }
    }
  }
}

}  // namespace Protocol
