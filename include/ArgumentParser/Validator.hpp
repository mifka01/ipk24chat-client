#pragma once
#include <functional>
#include <unordered_map>
#include "Type.hpp"

namespace ArgumentParser {

class Validator {
  std::unordered_map<Type, std::function<bool(std::string)>> validators;

 public:
  Validator();
  bool validate(Type type, std::string value);
};

}  // namespace ArgumentParser
