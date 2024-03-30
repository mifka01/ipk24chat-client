#pragma once
#include <regex>
#include <string>
#include <vector>
#include "Client/Session.hpp"
#include "Parameter.hpp"
#include "Protocol/Protocol.hpp"

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

  const std::string& getPrefix() const;

  virtual void execute(std::shared_ptr<Protocol::Protocol> protocol,
                       const std::string& message,
                       Client::Session& session) = 0;
  virtual ~Command() = default;
};

}  // namespace Command
