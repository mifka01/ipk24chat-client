#pragma once
#include <arpa/inet.h>
#include <netdb.h>
#include <poll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
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
  void auth(const std::string& username, const std::string& password);
};

}  // namespace Client
//
