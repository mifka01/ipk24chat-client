#pragma once
#include <string>

namespace Command {

class Parameter {
 private:
  const std::string& name;
  const std::string& pattern;
  const int& maxlen;

 public:
  Parameter(const std::string& name,
            const std::string& pattern,
            const int& maxlen)
      : name(name), pattern(pattern), maxlen(maxlen) {}

  const std::string& getName() const { return name; }
  const int& getMaxLength() const { return maxlen; }
  const std::string getPattern() const {
    return pattern + "{1," + std::to_string(getMaxLength()) + "}";
  }
};

}  // namespace Command
