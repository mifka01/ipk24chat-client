#pragma once
#include <map>
#include "Command.hpp"

namespace Command {

class CommandRegistry {
 public:
  std::vector<std::string> prefixes;

  void add(const std::string& name, std::unique_ptr<Command> command);

  Command* getCommand(const std::string& name);

  std::map<std::string, std::unique_ptr<Command>> commands;
};
}  // namespace Command
