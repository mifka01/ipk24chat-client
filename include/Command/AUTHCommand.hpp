#pragma once
#include "Command/Command.hpp"

namespace Command {

class AUTHCommand : public Command {
 public:
  AUTHCommand();

  void execute(Protocol::Protocol& protocol,
               const std::string& message,
               Client::Session& session) override;
};

}  // namespace Command
