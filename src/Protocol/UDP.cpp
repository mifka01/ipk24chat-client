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

void UDP::receive() const {
  // Recieve data using the UDP protocol.
}

const std::string UDP::convertAuthMessage(const AuthMessage &message) const {}

int UDP::getSocketType() const { return SOCK_DGRAM; }
