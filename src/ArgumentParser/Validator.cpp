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

bool Validator::validateType(Type type, std::string value) {
  auto validator = validators.find(type);

  if (validator != validators.end()) {
    return validator->second(value);
  }

  return false;
}

bool Validator::validateChoices(std::string value,
                                std::vector<std::string> choices) {
  if (choices.empty()) {
    return true;
  }

  transform(value.begin(), value.end(), value.begin(), ::toupper);
  return std::find(choices.begin(), choices.end(), value) != choices.end();
}

}  // namespace ArgumentParser
