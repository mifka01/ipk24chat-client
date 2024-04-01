/**
 * @file src/Command/CommandRegistry.cpp
 * @author Radim Mifka (xmifka00)
 * @date March 2024
 */
#include "Command/CommandRegistry.hpp"

namespace Command {

void CommandRegistry::add(const std::string& name,
                          std::unique_ptr<Command> command) {
  commands[name] = std::move(command);
  prefixes.push_back(commands[name]->getPrefix());
}

Command* CommandRegistry::getCommand(const std::string& name) {
  return commands[name].get();
}
}  // namespace Command
