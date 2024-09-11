/**
 * @file src/Protocol/TCP.cpp
 * @author Radim Mifka (xmifka00)
 * @date March 2024
 */
#include "Protocol/TCP.hpp"
#include <netdb.h>
#include <stdexcept>

void TCP::init(int socket, addrinfo *addrinfo) {
  if (::connect(socket, addrinfo->ai_addr, addrinfo->ai_addrlen) != 0) {
    throw std::runtime_error("TCP failed to connect.");
  }
}

void TCP::send(int socket, const Message &message) const {
  // Send data using the TCP protocol.
}

void TCP::receive() const {
  // Recieve data using the TCP protocol.
}

int TCP::getSocketType() const { return SOCK_STREAM; }
