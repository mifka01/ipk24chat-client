#pragma once
#include "Command/Command.hpp"

namespace Command {

class HELPCommand : public Command {
 public:
  HELPCommand();

  void execute(Protocol::Protocol& protocol,
               const std::string& message,
               Client::Session& session) override;
};

}  // namespace Command
