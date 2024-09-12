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
  auto converter = messageConverters.find(message.type);
  if (converter == messageConverters.end()) {
    throw std::runtime_error("TCP failed to send: Unknown message type.");
  }
  std::string msg = converter->second(message);

  ::send(socket, msg.c_str(), msg.size(), 0);
  Message::sent++;
}

void TCP::receive() const {
  // Recieve data using the TCP protocol.
}

const std::string TCP::convertAuthMessage(const AuthMessage &message) const {
  return "AUTH " + message.username + " AS " + message.displayName + " USING " +
         message.secret + CRLF;
}

int TCP::getSocketType() const { return SOCK_STREAM; }
