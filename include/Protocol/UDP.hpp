/**
 * @file include/Protocol/UDP.hpp
 * @author Radim Mifka (xmifka00)
 * @date March 2024
 */
#pragma once
#include "Protocol.hpp"

/**
 * @class UDP
 * @brief Represents the UDP protocol.
 *
 * The UDP class provides functionality for the UDP protocol.
 */
class UDP : public Protocol {

public:
  void init(int socket, addrinfo *addrinfo) override;
  void send(int socket, const Message &message) const override;
  void receive() const override;

  int getSocketType() const override;
};
