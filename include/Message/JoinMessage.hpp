/**
 * @file include/Message/JoinMessage.hpp
 * @author Radim Mifka (xmifka00)
 * @date March 2024
 */
#pragma once
#include <string>

#include "Message.hpp"

namespace Message {

/**
 * @class JoinMessage
 * @brief Represents the JOIN message.
 *
 * The JOIN message is used to join a chat channel.
 */
class JoinMessage : public Message {
 public:
  std::string channelID;
  std::string displayName;

  /**
   * @brief Constructs a JOIN message.
   * @param messageID The message ID.
   * @param channelID The channel ID to join.
   * @param displayName The display name of the user.
   */
  JoinMessage(const uint16_t messageID,
              const std::string& channelID,
              const std::string& displayName);

  /** @brief accept method for visitor pattern
   * @param visitor visitor to be accepted
   */
  [[maybe_unused]] void accept(MessageVisitor& visitor) override;

  /**
   * @brief Constructs a JOIN message for TCP protocol.
   * @return The serialized JOIN message.
   */
  std::string tcpSerialize() const override;

  /**
   * @brief Constructs a JOIN message for UDP protocol.
   * @return The serialized JOIN message.
   */
  std::vector<uint8_t> udpSerialize() const override;
};

}  // namespace Message
