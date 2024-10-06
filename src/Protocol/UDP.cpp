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

  if (message.type != MessageType::CONFIRM) {
    Message::sent++;
  }
}

const std::unique_ptr<Message> UDP::receive(int socket) {
  char buffer[BUFFER_SIZE];

  ssize_t bytes_received;
  bytes_received = ::recv(socket, buffer, BUFFER_SIZE - 1, 0);

  if (bytes_received == -1) {
    throw std::runtime_error("UDP failed to receive.");
  }

  if (bytes_received == 0) {
    return std::make_unique<ByeMessage>();
  }

  std::string message = std::string(buffer, bytes_received);

  // check if message format is correct
  MessageType type = determineMessageType(message);

  std::unique_ptr<Message> response = convertResponse(type, message);

  if (receivedMessages.find(response->id) != receivedMessages.end()) {
    return nullptr;
  }

  if (response->type != MessageType::CONFIRM) {
    send(socket, ConfirmMessage(response->id));
    receivedMessages.insert(response->id);
    Message::received++;
  }

  return response;
}

MessageType UDP::determineMessageType(const std::string &message) const {
  return static_cast<MessageType>(static_cast<uint8_t>(message[0]));
}

uint16_t UDP::determineMessageId(uint8_t high, uint8_t low) const {
  return ntohs((high << 8) | low);
}

uint16_t UDP::determineMessageId(const std::string &message) const {
  return ntohs((message[1] << 8) | message[2]);
}

void UDP::addMessageHeader(std::string &message, const MessageType &type,
                           const uint16_t &id) const {
  uint16_t nId = htons(id);
  message += static_cast<char>(type);
  message += static_cast<char>(nId >> 8);
  message += static_cast<char>(nId & 0xFF);
}

const std::string UDP::convertAuthMessage(const AuthMessage &message) const {
  std::string converted;

  addMessageHeader(converted, message.type, message.id);

  converted += message.username + '\0';
  converted += message.displayName + '\0';
  converted += message.secret + '\0';

  return converted;
}

const std::string UDP::convertByeMessage(const ByeMessage &message) const {
  std::string converted;
  addMessageHeader(converted, message.type, message.id);
  return converted;
}

const std::string UDP::convertErrMessage(const ErrMessage &message) const {
  std::string converted;

  addMessageHeader(converted, message.type, message.id);

  converted += message.displayName + '\0';
  converted += message.content + '\0';

  return converted;
}

const std::string UDP::convertMsgMessage(const MsgMessage &message) const {
  std::string converted;

  addMessageHeader(converted, message.type, message.id);

  converted += message.displayName + '\0';
  converted += message.content + '\0';

  return converted;
}

const std::string
UDP::convertConfirmMessage(const ConfirmMessage &message) const {
  std::string converted;
  addMessageHeader(converted, message.type, message.refId);

  return converted;
}

std::unique_ptr<ReplyMessage>
UDP::handleReplyMessage(const std::string &message) const {
  uint16_t id = determineMessageId(message);
  uint8_t success = message[3];
  uint16_t refId = determineMessageId(message[4], message[5]);
  std::string content = message.substr(6);
  content = content.substr(0, content.size() - 1);

  return std::make_unique<ReplyMessage>(id, success, content, refId);
}

std::unique_ptr<ErrMessage>
UDP::handleErrMessage(const std::string &message) const {
  uint16_t id = determineMessageId(message);
  size_t displayNameEnd = message.find('\0', 3);

  std::string displayName = message.substr(3, displayNameEnd - 3);
  std::string content = message.substr(displayNameEnd + 1);
  content = content.substr(0, content.size() - 1);

  return std::make_unique<ErrMessage>(id, displayName, content);
}

std::unique_ptr<MsgMessage>
UDP::handleMsgMessage(const std::string &message) const {
  uint16_t id = determineMessageId(message);

  size_t displayNameEnd = message.find('\0', 3);
  std::string displayName = message.substr(3, displayNameEnd - 3);
  std::string content = message.substr(displayNameEnd + 1);
  content = content.substr(0, content.size() - 1);

  return std::make_unique<MsgMessage>(id, displayName, content);
}

std::unique_ptr<ByeMessage>
UDP::handleByeMessage(const std::string &message) const {
  uint16_t id = determineMessageId(message);

  return std::make_unique<ByeMessage>(id);
}

std::unique_ptr<ConfirmMessage>
UDP::handleConfirmMessage(const std::string &message) const {
  uint16_t refId = determineMessageId(message);

  return std::make_unique<ConfirmMessage>(refId);
}

int UDP::getSocketType() const { return SOCK_DGRAM; }
