/**
 * @file include/Message/ByeMessage.hpp
 * @author Radim Mifka (xmifka00)
 * @date March 2024
 */
#pragma once
#include "Message.hpp"

namespace Message {

/**
 * @class ByeMessage
 * @brief Represents the BYE message.
 *
 * The BYE message is used to disconnect from the chat server.
 */
class ByeMessage : public Message {
 public:
  /**
   * @brief Constructs a BYE message.
   * @param messageID The message ID.
   */
  ByeMessage(const uint16_t messageID);

  /** @brief accept method for visitor pattern
   * @param visitor visitor to be accepted
   */
  void accept(MessageVisitor& visitor) override;

  /**
   * @brief Constructs a BYE message for TCP protocol.
   * @return The serialized BYE message.
   */
  std::string tcpSerialize() const override;

  /**
   * @brief Constructs a BYE message for UDP protocol.
   * @return The serialized BYE message.
   */
  std::vector<uint8_t> udpSerialize() const override;
};

}  // namespace Message
