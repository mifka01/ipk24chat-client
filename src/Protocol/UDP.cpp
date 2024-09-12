/**
 * @file src/Protocol/UDP.cpp
 * @author Radim Mifka (xmifka00)
 * @date March 2024
 */
#include "Protocol/UDP.hpp"
#include <netdb.h>

void UDP::init(int socket, addrinfo *addrinfo) {
  // Initialize the UDP protocol.
}

void UDP::send(int socket, const Message &message) const {
  // Send data using the TCP protocol.
}

const std::unique_ptr<Message> UDP::receive(int socket) {
  // Receive data using the TCP protocol.
  return nullptr;
}

const std::string UDP::convertAuthMessage(const AuthMessage &message) const {}

const std::string UDP::convertByeMessage(const ByeMessage &message) const {}

std::unique_ptr<ReplyMessage>
UDP::handleReplyMessage(const std::string &message) const {}

std::unique_ptr<ErrMessage>
UDP::handleErrMessage(const std::string &message) const {}

std::unique_ptr<ByeMessage>
UDP::handleByeMessage(const std::string &message) const {}

int UDP::getSocketType() const { return SOCK_DGRAM; }
