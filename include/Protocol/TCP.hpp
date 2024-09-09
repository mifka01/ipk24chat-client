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
  void init() override;
  void send() const override;
  void recieve() const override;
};
