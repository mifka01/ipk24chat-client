#pragma once
#include "Command/Command.hpp"

namespace Command {

class RENAMECommand : public Command {
 public:
  RENAMECommand();

  void execute(std::shared_ptr<Protocol::Protocol> protocol,
               const std::string& message,
               Client::Client& client) override;
};

}  // namespace Command
