#include <map>
#include "Command.hpp"

namespace Command {
class CommandRegistry {
 public:
  void add(const std::string& name, std::unique_ptr<Command> command);

  Command* getCommand(const std::string& name);

  std::map<std::string, std::unique_ptr<Command>> commands;
};
}  // namespace Command
