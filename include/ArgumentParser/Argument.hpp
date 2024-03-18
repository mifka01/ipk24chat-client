#pragma once

#include <string>
#include <vector>
#include "Type.hpp"

namespace ArgumentParser {
class Argument {
  const std::string name;
  const std::string shortcut;
  const Type type;
  const std::string help;
  const std::string defaultValue;
  const std::vector<std::string> choices;
  const int nargs;

  void validate() const;

 public:
  Argument(const std::string& name,
           const Type type,
           const std::string& help = "",
           const std::vector<std::string>& choices = {},
           const int nargs = 1);

  Argument(const std::string& name,
           const std::string& shortcut,
           const Type type,
           const std::string& help = "",
           const std::string& defaultValue = "",
           const std::vector<std::string>& choices = {},
           const int nargs = 1,
           bool required = false);

  bool isRequired;
  bool isPositional;
  std::string getName() const;
  std::string getShortcut() const;
  int getNargs() const;
  Type getType() const;
  std::string getDefaultValue() const;
  std::string getHelp() const;
  std::vector<std::string> getChoices() const;
};
}  // namespace ArgumentParser
