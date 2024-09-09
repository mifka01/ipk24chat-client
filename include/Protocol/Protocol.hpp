/**
 * @file include/Protocol/Protocol.hpp
 * @author Radim Mifka (xmifka00)
 * @date March 2024
 */
#pragma once

/**
 * @class Protocol
 * @brief Represents the protocol used in the communication.
 *
 * The Protocol class provides functionality for defining the protocol used in
 * the communication.
 */
class Protocol {
public:
  int port = 0;
  virtual void init() = 0;
  virtual void send() const = 0;
  virtual void recieve() const = 0;
};
