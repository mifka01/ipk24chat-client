/**
 * @file include/Protocol/Protocol.hpp
 * @author Radim Mifka (xmifka00)
 * @date March 2024
 */
#pragma once

#include "Message/AuthMessage.hpp"
#include "Message/Message.hpp"
#include <functional>
#include <netdb.h>
#include <string>
#include <unordered_map>

/**
 * @class Protocol
 * @brief Represents the protocol used in the communication.
 *
 * The Protocol class provides functionality for defining the protocol used in
 * the communication.
 */
class Protocol {

protected:
  using MessageConverter = std::function<std::string(const Message &)>;
  const std::unordered_map<MessageType, MessageConverter> messageConverters = {
      {MessageType::AUTH, [this](const Message &msg) {
         return convertAuthMessage(dynamic_cast<const AuthMessage &>(msg));
       }}};

public:
  virtual void init(int socket, addrinfo *addrinfo) = 0;
  virtual void send(int socket, const Message &message) const = 0;
  virtual void receive() const = 0;

  virtual const std::string
  convertAuthMessage(const AuthMessage &message) const = 0;

  virtual int getSocketType() const = 0;
};
