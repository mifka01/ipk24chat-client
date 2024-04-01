/**
 * @file include/Protocol/Protocol.hpp
 * @author Radim Mifka (xmifka00)
 * @date March 2024
 */
#pragma once
#include <poll.h>
#include <sys/socket.h>
#include <memory>
#include <string>

#include "Client/State.hpp"
#include "Message/Message.hpp"
#include "Type.hpp"

// Forward declaration
namespace Client {
class Client;
}

namespace Protocol {

/**
 * @class Protocol
 * @brief Represents the protocol used in the communication.
 *
 * The Protocol class provides functionality for defining the protocol used in
 * the communication.
 */
class Protocol {
 protected:
  const size_t BUFFER_SIZE = 1024;
  Client::Client& client;

 public:
  /**
   * @brief Constructs a new Protocol object.
   * @param client The client to use the protocol for.
   */
  Protocol(Client::Client& client) : client(client) {}
  virtual ~Protocol() = default;

  /**
   * @brief Retrieves the socket type of the protocol.
   * @return The socket type of the protocol.
   */
  virtual int socketType() = 0;

  /**
   * @brief Retrieves the socket type of the protocol.
   * @return The socket type of the protocol.
   */
  virtual std::string toString() = 0;

  /**
   * @brief Retrieves the type of the protocol.
   * @return The type of the protocol.
   */
  virtual Type getType() = 0;

  /**
   * @brief Runs the protocol.
   */
  virtual void run() = 0;

  /**
   * @brief Sets the next state of the client.
   * @param state The next state of the client.
   */
  virtual void setNextState(Client::State state) = 0;

  /**
   * @brief Sends a message.
   * @param message The message to send.
   */
  virtual void send(std::unique_ptr<Message::Message> message) = 0;

  /**
   * @brief Receives a message.
   * @return The received message.
   */
  virtual std::unique_ptr<Message::Message> receive() = 0;

  /**
   * @brief Processes a command.
   * @param message The message to process.
   * @return True if the command was processed successfully, otherwise false.
   */
  bool processCommand(const std::string& message);

  /**
   * @brief Processes the input.
   *
   * The input is read from the standard input and processed.
   */
  void processInput();

  /**
   * @brief Processes the reply.
   *
   * The reply is read from the socket and processed.
   */
  void processReply();

  /**
   * @brief Creates a message from the given parameters.
   *
   * @param message The message type.
   * @param parameters The message parameters.
   * @return The created message.
   */
  std::unique_ptr<Message::Message> toMessage(
      const Message::Type message,
      const std::vector<std::string>& parameters);

  /**
   * @brief Creates a protocol object from the given string.
   * @param protocol The protocol string.
   * @param client The client to use the protocol for.
   * @return The created protocol object.
   */
  static std::shared_ptr<Protocol> fromString(const std::string& protocol,
                                              Client::Client& client);
};

}  // namespace Protocol
