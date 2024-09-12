/**
 * @file include/Protocol/Protocol.hpp
 * @author Radim Mifka (xmifka00)
 * @date March 2024
 */
#pragma once

#include "Message/AuthMessage.hpp"
#include "Message/ByeMessage.hpp"
#include "Message/ErrMessage.hpp"
#include "Message/Message.hpp"
#include "Message/ReplyMessage.hpp"
#include <functional>
#include <memory>
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
      {MessageType::AUTH,
       [this](const Message &msg) {
         return convertAuthMessage(dynamic_cast<const AuthMessage &>(msg));
       }},
      {MessageType::BYE, [this](const Message &msg) {
         return convertByeMessage(dynamic_cast<const ByeMessage &>(msg));
       }}};

  using ResponseConverter =
      std::function<std::unique_ptr<Message>(const std::string &)>;
  const std::unordered_map<MessageType, ResponseConverter> responseConverter = {
      {MessageType::REPLY,
       [this](const std::string &msg) { return handleReplyMessage(msg); }},
      {MessageType::ERR,
       [this](const std::string &msg) { return handleErrMessage(msg); }},
      {MessageType::BYE,
       [this](const std::string &msg) { return handleByeMessage(msg); }}

  };

public:
  virtual void init(int socket, addrinfo *addrinfo) = 0;
  virtual void send(int socket, const Message &message) const = 0;
  virtual const std::unique_ptr<Message> receive(int socket) = 0;

  virtual const std::string
  convertAuthMessage(const AuthMessage &message) const = 0;

  virtual const std::string
  convertByeMessage(const ByeMessage &message) const = 0;

  virtual std::unique_ptr<ReplyMessage>
  handleReplyMessage(const std::string &message) const = 0;

  virtual std::unique_ptr<ErrMessage>
  handleErrMessage(const std::string &message) const = 0;

  virtual std::unique_ptr<ByeMessage>
  handleByeMessage(const std::string &message) const = 0;

  virtual int getSocketType() const = 0;
};
