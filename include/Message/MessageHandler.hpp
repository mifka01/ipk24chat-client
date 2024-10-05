#pragma once
#include "Message.hpp"
#include "Message/ByeMessage.hpp"
#include "Message/ConfirmMessage.hpp"
#include "Message/ErrMessage.hpp"
#include "Message/MsgMessage.hpp"
#include "Message/ReplyMessage.hpp"
#include <stdexcept>

class MessageHandler {
protected:
  MessageHandler() = default;

public:
  virtual ~MessageHandler() = default;

  virtual void handleMessage(const Message &message) {
    switch (message.type) {
    case MessageType::REPLY:
      handleReplyMessage(dynamic_cast<const ReplyMessage &>(message));
      break;
    case MessageType::ERR:
      handleErrMessage(dynamic_cast<const ErrMessage &>(message));
      break;
    case MessageType::MSG:
      handleMsgMessage(dynamic_cast<const MsgMessage &>(message));
      break;
    case MessageType::BYE:
      handleByeMessage(dynamic_cast<const ByeMessage &>(message));
      break;
    case MessageType::CONFIRM:
      handleConfirmMessage(dynamic_cast<const ConfirmMessage &>(message));
      break;
    default:
      handleUnknownMessage(message);
      break;
    }
  }

  virtual void handleUnknownMessage(const Message &message) {
    (void)message;
    throw std::runtime_error("Unknown message type");
  }

  virtual void handleConfirmMessage(const ConfirmMessage &message) {
    (void)message;
  }
  virtual void handleReplyMessage(const ReplyMessage &message) = 0;
  virtual void handleErrMessage(const ErrMessage &message) = 0;
  virtual void handleMsgMessage(const MsgMessage &message) = 0;
  virtual void handleByeMessage(const ByeMessage &message) = 0;
};
