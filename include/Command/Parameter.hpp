#pragma once

#include <string>

namespace Command {

class Parameter {
  const std::string& name;
  const std::string& pattern;
  const int& maxlen;

 public:
  Parameter(const std::string& name,
            const std::string& pattern,
            const int& maxlen)
      : name(name), pattern(pattern), maxlen(maxlen) {}

  const std::string& getName() const { return name; }
  const std::string getPattern() const {
    return pattern + "{1," + std::to_string(getMaxLength()) + "}";
  }
  const int& getMaxLength() const { return maxlen; }
};

}  // namespace Command
