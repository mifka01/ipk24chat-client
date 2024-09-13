#pragma once
#include "Message.hpp"
#include "Message/AuthMessage.hpp"
#include "Message/ByeMessage.hpp"
#include "Message/ErrMessage.hpp"
#include "Message/ReplyMessage.hpp"
#include <memory>
#include <stdexcept>
#include <string>

class MessageConverter {
protected:
  MessageConverter() = default;

public:
  virtual ~MessageConverter() = default;

  virtual std::unique_ptr<Message>
  convertResponse(MessageType type, const std::string &message) const {
    switch (type) {
    case MessageType::REPLY:
      return handleReplyMessage(message);
    case MessageType::ERR:
      return handleErrMessage(message);
    case MessageType::BYE:
      return handleByeMessage(message);
    default:
      throw std::runtime_error(
          "Unsupported message type for response conversion");
    }
  }

  virtual std::string convertMessage(const Message &message) const {
    switch (message.type) {
    case MessageType::AUTH:
      return convertAuthMessage(dynamic_cast<const AuthMessage &>(message));
    case MessageType::BYE:
      return convertByeMessage(dynamic_cast<const ByeMessage &>(message));
    default:
      throw std::runtime_error("Unsupported message type for conversion");
    }
  }

  virtual MessageType
  determineMessageType(const std::string &message) const = 0;

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
};
