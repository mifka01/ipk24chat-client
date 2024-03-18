/**
 * @file src/ArgumentParser/Validator.cpp
 * @author Radim Mifka (xmifka00)
 * @date March 2024
 */
#include "ArgumentParser/Validator.hpp"
#include <regex>

namespace ArgumentParser {

Validator::Validator() {
  validators[Type::UINT8] = [](std::string value) {
    try {
      auto uint8 = std::stoul(value);
      return uint8 <= std::numeric_limits<uint8_t>::max();
    } catch (std::invalid_argument&) {
      return false;
    } catch (std::out_of_range&) {
      return false;
    }
  };

  validators[Type::UINT16] = [](std::string value) {
    try {
      auto uint16 = std::stoul(value);
      return uint16 <= std::numeric_limits<uint16_t>::max();
    } catch (std::invalid_argument&) {
      return false;
    } catch (std::out_of_range&) {
      return false;
    }
  };

  validators[Type::STRING] = [](std::string value) { return !value.empty(); };

  validators[Type::HOST] = [](std::string value) {
    std::regex hostPattern(
        "^([a-zA-Z0-9]|[a-zA-Z0-9][a-zA-Z0-9\\-]{0,61}[a-zA-"
        "Z0-9])(\\.([a-zA-Z0-"
        "9]|[a-zA-Z0-9][a-zA-Z0-9\\-]{0,61}[a-zA-Z0-9]))*$");
    return std::regex_match(value, hostPattern);
  };
}

bool Validator::validateType(const Type& type, const std::string& value) {
  auto validator = validators.find(type);

  if (validator != validators.end()) {
    return validator->second(value);
  }

  return false;
}

bool Validator::validateChoices(const std::string& value,
                                const std::vector<std::string>& choices) {
  if (choices.empty()) {
    return true;
  }

  std::string upperValue = value;

  transform(upperValue.begin(), upperValue.end(), upperValue.begin(),
            ::toupper);
  return std::find(choices.begin(), choices.end(), upperValue) != choices.end();
}

bool Validator::validate(const Argument& arg, const std::string& value) {
  return validateType(arg.getType(), value) &&
         validateChoices(value, arg.getChoices());
}

}  // namespace ArgumentParser
