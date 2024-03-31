#include "Protocol/TCP.hpp"
#include <unistd.h>
#include <regex>
#include "Client/Client.hpp"
#include "Message/ByeMessage.hpp"
#include "Message/ErrMessage.hpp"
#include "Message/MsgMessage.hpp"
#include "Message/ReplyMessage.hpp"
#include "iostream"
#include "utils.hpp"

namespace Protocol {

void TCP::send(int socket, std::unique_ptr<Message::Message> message) {
  std::string msg = message->tcpSerialize();
  ::send(socket, msg.c_str(), msg.size(), 0);
  client.session.messagesSent++;
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

bool TCP::processCommand(const std::string& message) {
  for (const auto& [name, command] : client.commandRegistry.commands) {
    if (command->match(message)) {
      command->execute(client.protocol, message, client.session);
      return true;
    }
  }
  return false;
}

void TCP::processInput() {
  Client::State state = client.getState();
  if (state == Client::State::AUTH) {
    return;
  }

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

  if (state == Client::State::START) {
    if (message == "BYE") {
      client.protocol->send(client.session.socket,
                            client.protocol->toMessage(Message::Type::BYE, {}));
      state = Client::State::END;
      return;
    }
  }
  if (state == Client::State::OPEN) {
    if (message == "BYE") {
      client.protocol->send(client.session.socket,
                            client.protocol->toMessage(Message::Type::BYE, {}));
      state = Client::State::END;
      return;
    }
    client.protocol->send(
        client.session.socket,
        client.protocol->toMessage(Message::Type::MSG, {message}));
    return;
  }

  std::cerr << "ERR: trying to send a message in non-open state\n";
}

void TCP::processReply() {
  std::unique_ptr<Message::Message> reply =
      client.protocol->receive(client.session.socket);
  reply->accept(*client.visitor);
}

void TCP::run() {
  client.poller.addSocket(STDIN_FILENO, POLLIN);
  client.poller.addSocket(client.session.socket, POLLIN);

  while (true) {
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

}  // namespace Protocol
