/**
 * @file include/Command/Parameter.hpp
 * @author Radim Mifka (xmifka00)
 * @date March 2024
 */
#pragma once
#include <string>

/**
 * @class Parameter
 * @brief Represents a parameter for a command.
 *
 * The Parameter class provides functionality for defining a parameter for a
 * command.
 */
class Parameter {
private:
  const std::string &name;
  const std::string &pattern;
  const int &maxlen;

public:
  /**
   * @brief Constructs a new parameter.
   * @param name The name of the parameter.
   * @param pattern The pattern of the parameter.
   * @param maxlen The maximum length of the parameter.
   */
  Parameter(const std::string &name, const std::string &pattern,
            const int &maxlen)
      : name(name), pattern(pattern), maxlen(maxlen) {}

  /**
   * @brief get the name of the parameter
   * @return the name of the parameter
   */
  const std::string &getName() const { return name; }
  /**
   * @brief get maximum length of the parameter
   * @return the maximum length of the parameter
   */
  const int &getMaxLength() const { return maxlen; }
  /**
   * @brief get the pattern of the parameter
   * @return the pattern of the parameter
   */
  const std::string getPattern() const {
    return pattern + "{1," + std::to_string(getMaxLength()) + "}";
  }
};
