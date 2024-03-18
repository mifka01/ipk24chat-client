/**
 * @file include/ArgumentParser/Validator.hpp
 * @author Radim Mifka (xmifka00)
 * @date March 2024
 */
#pragma once
#include <functional>
#include <unordered_map>
#include "Argument.hpp"
#include "Type.hpp"

namespace ArgumentParser {
/**
 * @brief The Validator class provides functionality to validate argument
 * values.
 *
 * The Validator class contains methods to validate argument values based on
 * their type and choices. It uses a collection of validators to perform the
 * validation.
 */
/**
 * @class Validator
 * @brief Class responsible for validating argument values.
 */
class Validator {
  std::unordered_map<Type, std::function<bool(std::string)>> validators;

 public:
  /**
   * @brief Default constructor for Validator class.
   */
  Validator();

  /**
   * @brief Validates the given value against the specified type.
   * @param type The type to validate against.
   * @param value The value to be validated.
   * @return True if the value is valid for the given type, false otherwise.
   */
  bool validateType(const Type& type, const std::string& value);

  /**
   * @brief Validates the given value against the specified choices.
   * @param value The value to be validated.
   * @param choices The list of valid choices.
   * @return True if the value is one of the valid choices, false otherwise.
   */
  bool validateChoices(const std::string& value,
                       const std::vector<std::string>& choices);

  /**
   * @brief Validates the given value against the specified argument type and
   * choices.
   * @param arg The argument to be validated against.
   * @param value The value to be validated.
   * @return True if the value is valid for the argument, false otherwise.
   */
  bool validate(const Argument& arg, const std::string& value);
};

}  // namespace ArgumentParser
