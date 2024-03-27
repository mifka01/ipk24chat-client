#include "Command/Command.hpp"

namespace Command {

class AUTHCommand : public Command {
 public:
  AUTHCommand();

  std::string generateMessage(Protocol::Type protocol,
                              std::string message) override;
};

}  // namespace Command
