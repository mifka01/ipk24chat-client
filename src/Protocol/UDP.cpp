/**
 * @file src/Protocol/UDP.cpp
 * @author Radim Mifka (xmifka00)
 * @date March 2024
 */
#include "Protocol/UDP.hpp"
#include "Message/ConfirmMessage.hpp"
#include <iostream>
#include <netdb.h>

void UDP::init(int socket, addrinfo *addrinfo) {
  if (::connect(socket, addrinfo->ai_addr, addrinfo->ai_addrlen) != 0) {
    throw std::runtime_error("TCP failed to connect.");
  }
}

void UDP::send(int socket, const Message &message) const {
  std::string msg = convertMessage(message);

  ::send(socket, msg.c_str(), msg.size(), 0);
}

const std::unique_ptr<Message> UDP::receive(int socket) {
  char buffer[256];

  ssize_t bytes_received;
  bytes_received = ::recv(socket, buffer, 256 - 1, 0);

  std::cout << bytes_received << std::endl;

  if (bytes_received == -1) {
    throw std::runtime_error("UDP failed to receive.");
  }

  if (bytes_received == 0) {
    return std::make_unique<ByeMessage>();
  }

  std::string message = buffer;

  // check if message format is correct
  MessageType type = determineMessageType(message);
  std::unique_ptr<Message> response = convertResponse(type, message);

  if (receivedMessages.find(response->id) != receivedMessages.end()) {
    return nullptr;
  }

  send(socket, ConfirmMessage(response->id));
  receivedMessages.insert(response->id);
  Message::received++;
  return response;
}

MessageType UDP::determineMessageType(const std::string &message) const {
  return static_cast<MessageType>(message[0]);
}

const std::string UDP::convertAuthMessage(const AuthMessage &message) const {
  std::string converted;
  uint16_t id = htons(message.id);

  converted += static_cast<char>(message.type);
  converted.append(reinterpret_cast<const char *>(&id), sizeof(id));

  converted += message.username + '\0';
  converted += message.displayName + '\0';
  converted += message.secret + '\0';

  return converted;
}

const std::string UDP::convertByeMessage(const ByeMessage &message) const {
  std::string converted;
  uint16_t id = htons(message.id);

  converted += static_cast<char>(message.type);
  converted.append(reinterpret_cast<const char *>(&id), sizeof(id));

  return converted;
}

const std::string UDP::convertErrMessage(const ErrMessage &message) const {
  std::string converted;
  uint16_t id = htons(message.id);

  converted += static_cast<char>(message.type);
  converted.append(reinterpret_cast<const char *>(&id), sizeof(id));

  converted += message.displayName + '\0';
  converted += message.content + '\0';

  return converted;
}

const std::string UDP::convertMsgMessage(const MsgMessage &message) const {
  std::string converted;
  uint16_t id = htons(message.id);

  converted += static_cast<char>(message.type);
  converted.append(reinterpret_cast<const char *>(&id), sizeof(id));

  converted += message.displayName + '\0';
  converted += message.content + '\0';

  return converted;
}

std::unique_ptr<ReplyMessage>
UDP::handleReplyMessage(const std::string &message) const {
  uint16_t id = ntohs((message[1] << 8) | message[2]);
  uint8_t success = message[3];
  uint16_t refId = ntohs(message[4] << 8 | message[5]);
  std::string content = message.substr(6);

  return std::make_unique<ReplyMessage>(id, success, content, refId);
}

std::unique_ptr<ErrMessage>
UDP::handleErrMessage(const std::string &message) const {
  uint16_t id = ntohs((message[1] << 8) | message[2]);
  std::string displayName = message.substr(3);
  std::string content = message.substr(3 + displayName.size() + 1);

  return std::make_unique<ErrMessage>(id, displayName, content);
}

std::unique_ptr<MsgMessage>
UDP::handleMsgMessage(const std::string &message) const {
  uint16_t id = ntohs((message[1] << 8) | message[2]);
  std::string displayName = message.substr(3);
  std::string content = message.substr(3 + displayName.size() + 1);

  return std::make_unique<MsgMessage>(id, displayName, content);
}

std::unique_ptr<ByeMessage>
UDP::handleByeMessage(const std::string &message) const {
  uint16_t id = ntohs((message[1] << 8) | message[2]);

  return std::make_unique<ByeMessage>(id);
}

int UDP::getSocketType() const { return SOCK_DGRAM; }
