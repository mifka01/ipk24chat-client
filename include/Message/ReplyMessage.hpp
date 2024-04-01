/**
 * @file include/Message/ReplyMessage.hpp
 * @author Radim Mifka (xmifka00)
 * @date March 2024
 */
#pragma once
#include <string>

#include "Message.hpp"
#include "MessageVisitor.hpp"

namespace Message {
/**
 * @class ReplyMessage
 * @brief Represents the REPLY message.
 *
 * The REPLY message is used to reply to a message.
 */
class ReplyMessage : public Message {
 public:
  bool success;
  std::string content;
  uint16_t refMessageID;

  /**
   * @brief Constructs a REPLY message.
   * @param messageID The message ID.
   * @param success The success of the message.
   * @param content The content of the message.
   * @param refMessageID The reference message ID. (used in UDP)
   */
  ReplyMessage(const uint16_t messageID,
               bool success,
               const std::string& content,
               const uint16_t refMessageID = 0);

  /** @brief accept method for visitor pattern
   * @param visitor visitor to be accepted
   */
  void accept(MessageVisitor& visitor) override;

  /**
   * @brief Constructs a REPLY message for TCP protocol.
   * @return The serialized REPLY message.
   */
  std::string tcpSerialize() const override;

  /**
   * @brief Constructs a REPLY message for UDP protocol.
   * @return The serialized REPLY message.
   */
  std::vector<uint8_t> udpSerialize() const override;
};

}  // namespace Message
