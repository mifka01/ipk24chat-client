#pragma once
#include <arpa/inet.h>
#include <netdb.h>
#include <poll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <Client/SocketPoller.hpp>
#include <Command/CommandRegistry.hpp>
#include <Protocol/Protocol.hpp>
#include <string>
#include "Session.hpp"

namespace Message {
class MessageVisitor;
}

namespace Client {
class Client {
  const std::string& host;
  const int& port;

  addrinfo* getAddress();

  void close();

  bool processCommand(const std::string& message);

  void processInput();
  void processReply();

 public:
  Client(const std::string& host,
         const int& port,
         Protocol::Protocol& protocol);
  ~Client();

  void run();
  inline State getState() const { return session.state; }
  inline void setState(State state) { session.state = state; }

  Command::CommandRegistry commandRegistry;
  Session session;
  Protocol::Protocol& protocol;
  std::unique_ptr<Message::MessageVisitor> visitor;
};

}  // namespace Client
//
