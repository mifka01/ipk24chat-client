#pragma once

#include <string>
#include "Type.hpp"

namespace ArgumentParser {
class Argument {
  const std::string name;
  const std::string shortcut;
  const Type type;
  const std::string help;
  const std::string defaultValue;
  const int nargs;

  void validate() const;

 public:
  Argument(const std::string& name,
           const Type type,
           const std::string& help = "",
           const int nargs = 1);

  Argument(const std::string& name,
           const std::string& shortcut,
           const Type type,
           const std::string& help = "",
           const std::string& defaultValue = "",
           const int nargs = 1,
           bool required = false);

  bool isRequired;
  std::string getName() const;
  std::string getShortcut() const;
  std::string getHelp() const;
};
}  // namespace ArgumentParser
