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
  void init() override;
  void send() const override;
  void recieve() const override;
};
