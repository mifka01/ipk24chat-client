/**
 * @file include/Message/MsgMessage.hpp
 * @author Radim Mifka (xmifka00)
 * @date March 2024
 */
#pragma once
#include <string>

#include "Message.hpp"

namespace Message {

/**
 * @class MsgMessage
 * @brief Represents the MSG message.
 *
 * The MSG message is used to send a message to the chat server.
 */
class MsgMessage : public Message {
 public:
  std::string displayName;
  std::string content;

  /**
   * @brief Constructs an MSG message.
   * @param messageID The message ID.
   * @param displayName The display name of the message.
   * @param content The content of the message.
   */
  MsgMessage(const uint16_t messageID,
             const std::string& displayName,
             const std::string& content);

  /** @brief accept method for visitor pattern
   * @param visitor visitor to be accepted
   */
  void accept(MessageVisitor& visitor) override;

  /**
   * @brief Constructs an MSG message for TCP protocol.
   * @return The serialized MSG message.
   */
  std::string tcpSerialize() const override;

  /**
   * @brief Constructs an MSG message for UDP protocol.
   * @return The serialized MSG message.
   */
  std::vector<uint8_t> udpSerialize() const override;
};

}  // namespace Message
