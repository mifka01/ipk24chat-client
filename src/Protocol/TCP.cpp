/**
 * @file src/Protocol/TCP.cpp
 * @author Radim Mifka (xmifka00)
 * @date March 2024
 */
#include "Protocol/TCP.hpp"
#include <cstring>
#include <netdb.h>
#include <regex>
#include <stdexcept>

void TCP::init(int socket, addrinfo *addrinfo) {
  if (::connect(socket, addrinfo->ai_addr, addrinfo->ai_addrlen) != 0) {
    throw std::runtime_error("TCP failed to connect.");
  }
}

void TCP::send(int socket, const Message &message) const {
  std::string msg = convertMessage(message);

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
      return std::make_unique<ByeMessage>();
    }

    tmp[bytes_received] = '\0';
    buffer.append(tmp);

    size_t pos = buffer.find(CRLF);
    if (pos != std::string::npos) {
      std::string message = buffer.substr(0, pos);
      buffer.erase(0, pos + strlen(CRLF));

      MessageType type = determineMessageType(message);

      // TODO not confirmed
      Message::received++;
      return convertResponse(type, message);
    }
  }
  throw std::runtime_error("TCP failed to receive.");
}

MessageType TCP::determineMessageType(const std::string &message) const {
  std::string type = message.substr(0, message.find(' '));
  std::transform(type.begin(), type.end(), type.begin(), ::toupper);
  return Message::StringToMessageType(type);
}

const std::string TCP::convertAuthMessage(const AuthMessage &message) const {
  return "AUTH " + message.username + " AS " + message.displayName + " USING " +
         message.secret + CRLF;
}

const std::string TCP::convertJoinMessage(const JoinMessage &message) const {
  return "JOIN " + message.channelId + " AS " + message.displayName + CRLF;
}

const std::string TCP::convertByeMessage(const ByeMessage &message) const {
  (void)message;
  return "BYE" + std::string(CRLF);
}

const std::string TCP::convertErrMessage(const ErrMessage &message) const {
  return "ERR FROM " + message.displayName + " IS " + message.content + CRLF;
}

const std::string TCP::convertMsgMessage(const MsgMessage &message) const {
  return "MSG FROM " + message.displayName + " IS " + message.content + CRLF;
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

  return std::make_unique<ReplyMessage>(success == "OK", content,
                                        Message::sent);
}

std::unique_ptr<ErrMessage>
TCP::handleErrMessage(const std::string &message) const {
  std::smatch match;
  std::regex pattern("ERR FROM " + std::string(MessagePattern::DISPLAY_NAME) +
                         " IS " + MessagePattern::CONTENT,
                     std::regex::icase);

  if (!std::regex_match(message, match, pattern)) {
    return nullptr;
  }

  std::string displayName = match[1];
  std::string content = match[2];

  return std::make_unique<ErrMessage>(displayName, content);
}

std::unique_ptr<MsgMessage>
TCP::handleMsgMessage(const std::string &message) const {
  std::smatch match;
  std::regex pattern("MSG FROM " + std::string(MessagePattern::DISPLAY_NAME) +
                         " IS " + MessagePattern::CONTENT,
                     std::regex::icase);

  if (!std::regex_match(message, match, pattern)) {
    return nullptr;
  }

  std::string displayName = match[1];
  std::string content = match[2];

  return std::make_unique<MsgMessage>(displayName, content);
}

std::unique_ptr<ByeMessage>
TCP::handleByeMessage(const std::string &message) const {
  if (message == "BYE") {
    return std::make_unique<ByeMessage>();
  }
  return nullptr;
}

int TCP::getSocketType() const { return SOCK_STREAM; }
