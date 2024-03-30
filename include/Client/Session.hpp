#pragma once
#include <string>
#include "Client/State.hpp"

namespace Client {
class Session {
 public:
  int socket;
  std::string displayName = "";
  State state = State::START;
};

}  // namespace Client
