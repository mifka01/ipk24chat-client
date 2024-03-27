#pragma once
#include <arpa/inet.h>
#include <netdb.h>
#include <poll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <Command/CommandRegistry.hpp>
#include <Protocol/Type.hpp>
#include <string>

namespace Client {
class Client {
  const std::string& host;
  const int& port;
  const Protocol::Type& protocol;
  int socket;

  addrinfo* getAddress();

  void send(const std::string& message);

  std::string receive();

  void close();

 public:
  Client(const std::string& host,
         const int& port,
         const Protocol::Type& protocol);
  ~Client();

  void run();
  Command::CommandRegistry commandRegistry;
};

}  // namespace Client
//
