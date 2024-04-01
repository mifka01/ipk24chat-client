#pragma once
#include <regex>
#include <string>
#include <vector>

#include "Parameter.hpp"
#include "Protocol/Protocol.hpp"

namespace Command {

class Command {
 protected:
  std::string name;
  std::string prefix;
  std::vector<Parameter> parameters;
  std::regex regex;

  const std::string COMMAND_NAME_REGEX = "^[a-zA-Z0-9_\\-]+$";
  const std::string WHITESPACE_REGEX = "[^\\S\\n]*";

  void generateRegex();

 public:
  Command(const std::string& name,
          const std::string& prefix,
          const std::vector<Parameter>& parameters);

  virtual ~Command() = default;

  bool match(const std::string& message) const;
  const std::string& getPrefix() const;

  virtual void execute(std::shared_ptr<Protocol::Protocol> protocol,
                       const std::string& message,
                       Client::Client& client) = 0;
};

}  // namespace Command
