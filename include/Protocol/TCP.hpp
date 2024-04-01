/**
 * @file include/Protocol/TCP.hpp
 * @author Radim Mifka (xmifka00)
 * @date March 2024
 */
#pragma once
#include <map>
#include <regex>
#include <string>

#include "Message/Message.hpp"
#include "Protocol.hpp"

namespace Protocol {
/**
 * @class TCP
 * @brief Represents the TCP protocol.
 *
 * The TCP class provides functionality for the TCP protocol.
 */
class TCP : public Protocol {
 protected:
  const std::map<Message::Type, std::regex> regexes = {
      {Message::Type::MSG,
       std::regex("MSG FROM " + Message::Pattern::USERNAME + " IS " +
                  Message::Pattern::CONTENT + Message::Pattern::CLRF)},
      {Message::Type::REPLY,
       std::regex("REPLY (OK|NOK) IS " + Message::Pattern::CONTENT +
                  Message::Pattern::CLRF)},
      {Message::Type::ERR,
       std::regex("ERR FROM " + Message::Pattern::DISPLAY_NAME + " IS " +
                  Message::Pattern::CONTENT + Message::Pattern::CLRF)},
      {Message::Type::BYE, std::regex("BYE" + Message::Pattern::CLRF)},
  };

 public:
  /**
   * @brief Constructs a new TCP object.
   * @param client The client to use the protocol for.
   */
  TCP(Client::Client& client) : Protocol(client){};
  ~TCP() override = default;

  /**
   * @brief Retrieves the socket type of the protocol.
   * @return The socket type of the protocol.
   */
  int socketType() override { return SOCK_STREAM; }

  /**
   * @brief Retrieves the string representation of the protocol.
   * @return The string representation of the protocol.
   */
  std::string toString() override { return "TCP"; }

  /**
   * @brief Retrieves the type of the protocol.
   * @return The type of the protocol.
   */
  Type getType() override { return Type::TCP; }

  /**
   * @brief Sets the next state of the client.
   * @param state The next state of the client.
   */
  void setNextState(Client::State state) override;

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
