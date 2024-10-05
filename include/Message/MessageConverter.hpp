#pragma once
#include "Message.hpp"
#include "Message/AuthMessage.hpp"
#include "Message/ByeMessage.hpp"
#include "Message/ConfirmMessage.hpp"
#include "Message/ErrMessage.hpp"
#include "Message/MsgMessage.hpp"
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
    case MessageType::MSG:
      return handleMsgMessage(message);
    case MessageType::BYE:
      return handleByeMessage(message);
    case MessageType::CONFIRM:
      return handleConfirmMessage(message);
    default:
      throw std::runtime_error(
          "Unsupported message type for response conversion");
    }
  }

  virtual std::string convertMessage(const Message &message) const {
    switch (message.type) {
    case MessageType::AUTH:
      return convertAuthMessage(dynamic_cast<const AuthMessage &>(message));
    case MessageType::ERR:
      return convertErrMessage(dynamic_cast<const ErrMessage &>(message));
    case MessageType::MSG:
      return convertMsgMessage(dynamic_cast<const MsgMessage &>(message));
    case MessageType::BYE:
      return convertByeMessage(dynamic_cast<const ByeMessage &>(message));
    case MessageType::CONFIRM:
      return convertConfirmMessage(
          dynamic_cast<const ConfirmMessage &>(message));
    default:
      throw std::runtime_error("Unsupported message type for conversion");
    }
  }

  virtual MessageType
  determineMessageType(const std::string &message) const = 0;

  virtual const std::string
  convertAuthMessage(const AuthMessage &message) const = 0;
  virtual const std::string
  convertErrMessage(const ErrMessage &message) const = 0;
  virtual const std::string
  convertMsgMessage(const MsgMessage &message) const = 0;
  virtual const std::string
  convertByeMessage(const ByeMessage &message) const = 0;
  virtual const std::string
  convertConfirmMessage(const ConfirmMessage &message) const {
    (void)message;
    return "";
  }

  virtual std::unique_ptr<ReplyMessage>
  handleReplyMessage(const std::string &message) const = 0;
  virtual std::unique_ptr<ErrMessage>
  handleErrMessage(const std::string &message) const = 0;
  virtual std::unique_ptr<MsgMessage>
  handleMsgMessage(const std::string &message) const = 0;
  virtual std::unique_ptr<ByeMessage>
  handleByeMessage(const std::string &message) const = 0;
  virtual std::unique_ptr<ConfirmMessage>
  handleConfirmMessage(const std::string &message) const {
    (void)message;
    return nullptr;
  }
};
