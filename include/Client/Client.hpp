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

} // namespace Message

namespace Client {

class Client {
 private:
  const std::string& host;
  const int& port;
  addrinfo* address;

  addrinfo* getAddress();
  void close();

 public:
  Client(const std::string& host, const int& port, const std::string& protocol);
  ~Client();

  int socket;
  int messagesSent = 1;
  sockaddr* serverAddr;
  std::string displayName = "";
  State state = State::START;
  uint16_t timeout = 250;
  uint8_t retries = 3;

  Command::CommandRegistry commandRegistry;
  SocketPoller poller;
  std::shared_ptr<Protocol::Protocol> protocol;
  std::unique_ptr<Message::MessageVisitor> visitor;

  void run();
};

}  // namespace Client