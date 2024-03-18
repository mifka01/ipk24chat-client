#pragma once
#include <functional>
#include <unordered_map>
#include "Argument.hpp"
#include "Type.hpp"

namespace ArgumentParser {

class Validator {
  std::unordered_map<Type, std::function<bool(std::string)>> validators;

 public:
  Validator();
  bool validateType(const Type& type, const std::string& value);
  bool validateChoices(const std::string& value,
                       const std::vector<std::string>& choices);
  bool validate(const Argument& arg, const std::string& value);
};

}  // namespace ArgumentParser
