#pragma once
#include <functional>
#include <unordered_map>
#include "Type.hpp"

namespace ArgumentParser {

class Validator {
  std::unordered_map<Type, std::function<bool(std::string)>> validators;

 public:
  Validator();
  bool validateType(Type type, std::string value);
  bool validateChoices(std::string value, std::vector<std::string> choices);
};

}  // namespace ArgumentParser
