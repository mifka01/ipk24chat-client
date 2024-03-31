#include "Protocol/TCP.hpp"
#include <unistd.h>
#include <regex>
#include "Client/Client.hpp"
#include "Client/State.hpp"
#include "Message/ByeMessage.hpp"
#include "Message/ErrMessage.hpp"
#include "Message/MsgMessage.hpp"
#include "Message/ReplyMessage.hpp"
#include "iostream"
#include "utils.hpp"

namespace Protocol {

void TCP::send(std::unique_ptr<Message::Message> message) {
  std::string msg = message->tcpSerialize();
  ::send(client.socket, msg.c_str(), msg.size(), 0);
  client.messagesSent++;
}

std::unique_ptr<Message::Message> TCP::receive() {
  char buffer[4096];
  int bytesReceived = recv(client.socket, buffer, 1024, 0);
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

bool TCP::processCommand(const std::string& message) {
  for (const auto& [name, command] : client.commandRegistry.commands) {
    if (command->match(message)) {
      command->execute(client.protocol, message, client);
      return true;
    }
  }
  return false;
}

void TCP::processInput() {
  std::string message;
  std::getline(std::cin, message);
  if (message.empty()) {
    return;
  }
  if (processCommand(message)) {
    return;
  }

  if (std::any_of(client.commandRegistry.prefixes.begin(),
                  client.commandRegistry.prefixes.end(),
                  [&message](const std::string& prefix) {
                    return message.starts_with(prefix);
                  })) {
    std::cerr << "ERR: trying to process an unknown or otherwise malformed "
                 "command.\n";
    return;
  }

  if (message == "BYE") {
    client.protocol->send(client.protocol->toMessage(Message::Type::BYE, {}));
    client.state = Client::State::END;
    return;
  }

  client.protocol->send(
      client.protocol->toMessage(Message::Type::MSG, {message}));
}

void TCP::processReply() {
  std::unique_ptr<Message::Message> reply = client.protocol->receive();
  reply->accept(*client.visitor);
}

void TCP::run() {
  client.poller.addSocket(STDIN_FILENO, POLLIN);
  client.poller.addSocket(client.socket, POLLIN);

  while (true) {
    if (client.state == Client::State::START) {
      int events = client.poller.poll();
      if (events < 0) {
        throw std::runtime_error("Failed to poll");
      }
      if (client.poller.hasEvent(0, POLLIN)) {
        std::string message;
        std::getline(std::cin, message);
        if (message == "BYE") {
          client.state = Client::State::END;
          continue;
        } else if (!message.empty() && !processCommand(message)) {
          std::cerr << "ERR: trying to send a message in non-open state\n";
        }
      }
      if (client.poller.hasEvent(1, POLLIN)) {
        processReply();
      }
    } else if (client.state == Client::State::AUTH) {
      int events = client.poller.poll();
      if (events < 0) {
        throw std::runtime_error("Failed to poll");
      }

      if (client.poller.hasEvent(1, POLLIN)) {
        processReply();
      }
    } else if (client.state == Client::State::OPEN) {
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
    } else if (client.state == Client::State::END) {
      client.protocol->send(client.protocol->toMessage(Message::Type::BYE, {}));
      break;
    }
  }
}

}  // namespace Protocol
