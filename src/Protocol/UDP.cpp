/**
 * @file src/Protocol/UDP.cpp
 * @author Radim Mifka (xmifka00)
 * @date March 2024
 */
#include "Protocol/UDP.hpp"
#include <netdb.h>

void UDP::init(int socket, addrinfo *addrinfo) {
  (void)socket;
  (void)addrinfo;
  // Initialize the UDP protocol.
}

void UDP::send(int socket, const Message &message) const {
  (void)socket;
  (void)message;
  // Send data using the TCP protocol.
}

const std::unique_ptr<Message> UDP::receive(int socket) {
  (void)socket;
  // Receive data using the TCP protocol.
  return nullptr;
}

const std::string UDP::convertAuthMessage(const AuthMessage &message) const {
  (void)message;
  // Convert the AuthMessage to a string.
  return "";
}

const std::string UDP::convertByeMessage(const ByeMessage &message) const {
  (void)message;
  // Convert the ByeMessage to a string.
  return "";
}

std::unique_ptr<ReplyMessage>
UDP::handleReplyMessage(const std::string &message) const {
  (void)message;
  // Handle the ReplyMessage.
  return nullptr;
}

std::unique_ptr<ErrMessage>
UDP::handleErrMessage(const std::string &message) const {
  (void)message;
  // Handle the ErrMessage.
  return nullptr;
}

std::unique_ptr<ByeMessage>
UDP::handleByeMessage(const std::string &message) const {
  (void)message;
  // Handle the ByeMessage.
  return nullptr;
}

int UDP::getSocketType() const { return SOCK_DGRAM; }
