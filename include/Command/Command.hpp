#pragma once
#include <regex>
#include <string>
#include <vector>
#include "Parameter.hpp"
#include "Protocol/Type.hpp"

namespace Command {

class Command {
  const std::string COMMAND_NAME_REGEX = "^[a-zA-Z0-9_\\-]+$";
  const std::string WHITESPACE_REGEX = "[^\\S\\n]*";

 protected:
  std::string name;
  std::string prefix;
  std::vector<Parameter> parameters;
  std::regex regex;

  void generateRegex();

 public:
  Command(const std::string& name,
          const std::string& prefix,
          const std::vector<Parameter>& parameters);

  bool match(const std::string& message) const;

  std::string& getPrefix() const;

  virtual std::string generateMessage(Protocol::Type protocol,
                                      std::string message) = 0;
  virtual ~Command() = default;
};

}  // namespace Command
