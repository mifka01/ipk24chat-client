#pragma once
#include "Command/Command.hpp"

namespace Command {

class JOINCommand : public Command {
 public:
  JOINCommand();

  void execute(std::shared_ptr<Protocol::Protocol> protocol,
               const std::string& message,
               Client::Session& session) override;
};

}  // namespace Command
