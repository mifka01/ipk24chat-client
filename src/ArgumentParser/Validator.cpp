#include "ArgumentParser/Validator.hpp"

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
}

bool Validator::validate(Type type, std::string value) {
  auto validator = validators.find(type);

  if (validator != validators.end()) {
    return validator->second(value);
  }

  return false;
}

}  // namespace ArgumentParser