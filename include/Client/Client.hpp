/**
 * @file include/Client/Client.hpp
 * @author Radim Mifka (xmifka00)
 * @date March 2024
 */
#pragma once
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <string>

#include "Client/SocketPoller.hpp"
#include "Client/State.hpp"
#include "Command/CommandRegistry.hpp"
#include "Protocol/Protocol.hpp"

namespace Message {

class MessageVisitor;

}  // namespace Message

namespace Client {
/**
 * @class Client
 * @brief Represents a client for a chat application.
 *
 * The Client class provides functionality for connecting to a chat server,
 * sending and receiving messages, and managing the client's state.
 */
class Client {
 private:
  const std::string& host;
  const int& port;
  addrinfo* address;

  /**
   * @brief Retrieves the address information of the chat server.
   * @return The address information of the chat server.
   */
  addrinfo* getAddress();

  /**
   * @brief Closes the client's socket connection.
   */
  void close();

 public:
  /**
   * @brief Constructs a new Client object.
   * @param host The host address of the chat server.
   * @param port The port number of the chat server.
   * @param protocol The protocol to be used for communication.
   */
  Client(const std::string& host, const int& port, const std::string& protocol);

  /**
   * @brief Destroys the Client object and cleans up any resources.
   */
  ~Client();

  int socket;
  int messagesSent = 0;
  sockaddr* serverAddr;
  std::string displayName = "";
  State state = State::START;
  uint16_t timeout = 250;
  uint8_t retries = 3;

  Command::CommandRegistry commandRegistry;
  SocketPoller poller;
  std::shared_ptr<Protocol::Protocol> protocol;
  std::unique_ptr<Message::MessageVisitor> visitor;

  /**
   * @brief Runs the client and starts the chat application.
   */
  void run();
};

}  // namespace Client
