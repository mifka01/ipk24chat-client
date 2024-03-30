#pragma once
#include <arpa/inet.h>
#include <string>
#include "Client/State.hpp"

namespace Client {
class Session {
 public:
  int socket;
  int messagesSent = 1;
  sockaddr* serverAddr;
  std::string displayName = "";
  State state = State::START;
};

}  // namespace Client
