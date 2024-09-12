/**
 * @file src/Protocol/TCP.cpp
 * @author Radim Mifka (xmifka00)
 * @date March 2024
 */
#include "Protocol/TCP.hpp"
#include <cstring>
#include <iostream>
#include <netdb.h>
#include <regex>
#include <stdexcept>

void TCP::init(int socket, addrinfo *addrinfo) {
  if (::connect(socket, addrinfo->ai_addr, addrinfo->ai_addrlen) != 0) {
    throw std::runtime_error("TCP failed to connect.");
  }
}

void TCP::send(int socket, const Message &message) const {
  auto converter = messageConverters.find(message.type);
  if (converter == messageConverters.end()) {
    throw std::runtime_error("TCP failed to send: Unknown message type.");
  }
  std::string msg = converter->second(message);

  ::send(socket, msg.c_str(), msg.size(), 0);
  Message::sent++;
}

const std::unique_ptr<Message> TCP::receive(int socket) {
  char tmp[256];

  ssize_t bytes_received;
  while (true) {
    bytes_received = ::recv(socket, tmp, 256 - 1, 0);

    if (bytes_received == -1) {
      throw std::runtime_error("TCP failed to receive.");
    }

    if (bytes_received == 0) {
      std::cout << "Connection closed by peer." << std::endl;
      break;
    }

    tmp[bytes_received] = '\0';
    buffer.append(tmp);

    size_t pos = buffer.find(CRLF);
    if (pos != std::string::npos) {
      std::string message = buffer.substr(0, pos);
      buffer.erase(0, pos + strlen(CRLF));
      std::string type = message.substr(0, message.find(' '));
      auto converter =
          responseConverter.find(Message::StringToMessageType(type));
      if (converter != responseConverter.end()) {
        Message::received++;
        return converter->second(message);
      }
    }
  }
  throw std::runtime_error("TCP failed to receive.");
}

const std::string TCP::convertAuthMessage(const AuthMessage &message) const {
  return "AUTH " + message.username + " AS " + message.displayName + " USING " +
         message.secret + CRLF;
}

const std::string TCP::convertByeMessage(const ByeMessage &message) const {
  (void)message;
  return "BYE" + std::string(CRLF);
}

std::unique_ptr<ReplyMessage>
TCP::handleReplyMessage(const std::string &message) const {
  std::smatch match;
  std::regex pattern("REPLY (OK|NOK) IS " +
                         std::string(MessagePattern::CONTENT),
                     std::regex::icase);

  if (!std::regex_match(message, match, pattern)) {
    return nullptr;
  }

  std::string success = match[1];
  std::string content = match[2];
  std::cout << "Received: " << success << " " << content << std::endl;

  return std::make_unique<ReplyMessage>(success == "OK", content,
                                        Message::sent);
}

std::unique_ptr<ErrMessage>
TCP::handleErrMessage(const std::string &message) const {
  std::cout << "Received: " << message << std::endl;
  std::smatch match;
  std::regex pattern("ERR FROM IS " + std::string(MessagePattern::CONTENT),
                     std::regex::icase);

  if (!std::regex_match(message, match, pattern)) {
    return nullptr;
  }

  std::string displayName = match[1];
  std::string content = match[2];

  return std::make_unique<ErrMessage>(displayName, content);
}

std::unique_ptr<ByeMessage>
TCP::handleByeMessage(const std::string &message) const {
  if (message == "BYE") {
    return std::make_unique<ByeMessage>();
  }
  return nullptr;
}

int TCP::getSocketType() const { return SOCK_STREAM; }
