/**
 * @file include/Protocol/UDP.hpp
 * @author Radim Mifka (xmifka00)
 * @date March 2024
 */
#pragma once
#include <string>

#include "Client/State.hpp"
#include "Message/Message.hpp"
#include "Protocol.hpp"

namespace Protocol {
/**
 * @class UDP
 * @brief Represents the UDP protocol.
 *
 * The UDP class provides functionality for the UDP protocol.
 */
class UDP : public Protocol {
 protected:
  std::unique_ptr<Message::Message> lastSentMessage;
  Client::State nextState;
  Client::State lastState = Client::State::START;
  std::vector<uint16_t> receivedMessages;
  uint8_t curRetries = 0;

  /**
   * @brief Confirms the message with the given ID.
   * @param messageID The message ID.
   */
  void confirm(uint16_t messageID);

 public:
  /**
   * @brief Constructs a UDP protocol.
   * @param client The client to use the protocol for.
   */
  UDP(Client::Client& client) : Protocol(client){};
  ~UDP() override = default;

  /**
   * @brief Retrieves the socket type of the protocol.
   * @return The socket type of the protocol.
   */
  int socketType() override { return SOCK_DGRAM; }

  /**
   * @brief Retrieves string representation of the protocol.
   * @return The string representation of the protocol.
   */
  std::string toString() override { return "UDP"; }

  /**
   * @brief Retrieves the type of the protocol.
   * @return The type of the protocol.
   */
  Type getType() override { return Type::UDP; }

  /**
   * @brief Sets the next state.
   * @param state The next state.
   */
  void setNextState(Client::State state) override;

  /**
   * @brief Processes the reply.
   *
   * The reply is read from the socket and processed.
   */
  void processReply();

  /**
   * @brief Runs the protocol.
   */
  void run() override;

  /**
   * @brief Sends a message.
   * @param message The message to send.
   */
  void send(std::unique_ptr<Message::Message> message) override;

  /**
   * @brief Receives a message.
   * @return The received message.
   */
  std::unique_ptr<Message::Message> receive() override;
};

}  // namespace Protocol
