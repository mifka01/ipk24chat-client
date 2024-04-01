/**
 * @file include/Message/AuthMessage.hpp
 * @author Radim Mifka (xmifka00)
 * @date March 2024
 */
#pragma once
#include <string>

#include "Message.hpp"

namespace Message {

/**
 * @class AuthMessage
 * @brief Represents the AUTH message.
 *
 * The AUTH message is used to authenticate a user on the chat server.
 */
class AuthMessage : public Message {
 public:
  std::string username;
  std::string displayName;
  std::string secret;

  /**
   * @brief Constructs an AUTH message.
   * @param messageID The message ID.
   * @param username The username to authenticate.
   * @param displayName The display name to authenticate.
   * @param secret The secret to authenticate.
   */
  AuthMessage(const uint16_t messageID,
              const std::string& username,
              const std::string& displayName,
              const std::string& secret);

  /** @brief accept method for visitor pattern
   * @param visitor visitor to be accepted
   */
  void accept(MessageVisitor& visitor) override;

  /**
   * @brief Constructs an AUTH message for TCP protocol.
   * @return The serialized AUTH message.
   */
  std::string tcpSerialize() const override;

  /**
   * @brief Constructs an AUTH message for UDP protocol.
   * @return The serialized AUTH message.
   */
  std::vector<uint8_t> udpSerialize() const override;
};

}  // namespace Message
