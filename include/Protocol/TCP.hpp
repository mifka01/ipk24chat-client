/**
 * @file include/Protocol/TCP.hpp
 * @author Radim Mifka (xmifka00)
 * @date March 2024
 */
#pragma once
#include "Protocol.hpp"

/**
 * @class TCP
 * @brief Represents the TCP protocol.
 *
 * The TCP class provides functionality for the TCP protocol.
 */
class TCP : public Protocol {

public:
  void init(int socket, addrinfo *addrinfo) override;
  void send(int socket, const Message &message) const override;
  void receive() const override;

  int getSocketType() const override;
};
