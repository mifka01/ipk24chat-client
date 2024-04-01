/**
 * @file include/Message/ErrMessage.hpp
 * @author Radim Mifka (xmifka00)
 * @date March 2024
 */
#pragma once
#include <string>

#include "Message.hpp"

namespace Message {

/**
 * @class ErrMessage
 * @brief Represents the ERR message.
 *
 * The ERR message is used to send an error message to the client.
 */
class ErrMessage : public Message {
 public:
  std::string displayName;
  std::string content;

  /**
   * @brief Constructs an ERR message.
   *
   * @param messageID The message ID.
   * @param displayName The display name of the message.
   * @param content The content of the message.
   */
  ErrMessage(const uint16_t messageID,
             const std::string& displayName,
             const std::string& content);

  /** @brief accept method for visitor pattern
   * @param visitor visitor to be accepted
   */
  void accept(MessageVisitor& visitor) override;

  /**
   * @brief Constructs an ERR message for TCP protocol.
   * @return The serialized ERR message.
   */
  std::string tcpSerialize() const override;

  /**
   * @brief Constructs an ERR message for UDP protocol.
   * @return The serialized ERR message.
   */
  std::vector<uint8_t> udpSerialize() const override;
};

}  // namespace Message
