/**
 * @file include/Protocol/Protocol.hpp
 * @author Radim Mifka (xmifka00)
 * @date March 2024
 */
#pragma once

#include "Message/Message.hpp"
#include "Message/MessageConverter.hpp"
#include "Message/MessageHandler.hpp"
#include <memory>
#include <netdb.h>

/**
 * @class Protocol
 * @brief Represents the protocol used in the communication.
 *
 * The Protocol class provides functionality for defining the protocol used in
 * the communication.
 */
class Protocol : public MessageConverter {

public:
  virtual void init(int socket, addrinfo *addrinfo) = 0;
  virtual void send(int socket, const Message &message) const = 0;
  virtual const std::unique_ptr<Message> receive(int socket) = 0;
  virtual int getSocketType() const = 0;
};
