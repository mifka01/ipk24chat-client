/**
 * @file include/ArgumentParser/Argument.hpp
 * @author Radim Mifka (xmifka00)
 * @date March 2024
 */
#pragma once

#include <string>
#include <vector>
#include "Type.hpp"

namespace ArgumentParser {
/**
 * @class Argument
 * @brief Represents a command-line argument.
 *
 * The Argument class encapsulates the properties and behavior of a command-line
 * argument. It provides methods to access and manipulate the attributes of an
 * argument, such as its name, shortcut, type, help message, default value,
 * choices, and number of arguments.
 *
 */

class Argument {
  const std::string name;
  const std::string shortcut;
  const Type type;
  const std::string help;
  const std::string defaultValue;
  const std::vector<std::string> choices;
  const int nargs;

  /**
   * @brief Validates the argument.
   *
   * This method validates the argument based on its properties and throws an
   * exception if the argument is not valid.
   */
  void validate() const;

 public:
  /**
   * @brief Constructs an Argument object.
   *
   * @param name The name of the argument.
   * @param type The type of the argument.
   * @param help The help message for the argument (optional).
   * @param choices The choices for the argument (optional).
   * @param nargs The number of arguments for the argument (optional, default is
   * 1).
   */
  Argument(const std::string& name,
           const Type type,
           const std::string& help = "",
           const std::vector<std::string>& choices = {},
           const int nargs = 1);

  /**
   * @brief Constructs an Argument object.
   *
   * @param name The name of the argument.
   * @param shortcut The shortcut of the argument.
   * @param type The type of the argument.
   * @param help The help message for the argument (optional).
   * @param defaultValue The default value of the argument (optional).
   * @param choices The choices for the argument (optional).
   * @param nargs The number of arguments for the argument (optional, default is
   * 1).
   * @param required Indicates if the argument is required (optional, default is
   * false).
   */
  Argument(const std::string& name,
           const std::string& shortcut,
           const Type type,
           const std::string& help = "",
           const std::string& defaultValue = "",
           const std::vector<std::string>& choices = {},
           const int nargs = 1,
           bool required = false);

  bool isRequired;
  bool isPositional;

  /**
   * @brief Gets the name of the argument.
   *
   * @return The name of the argument.
   */
  std::string getName() const;

  /**
   * @brief Gets the output name of the argument.
   *
   * @return The output name of the argument.
   */
  std::string getOutputName() const;

  /**
   * @brief Gets the shortcut of the argument.
   *
   * @return The shortcut of the argument.
   */
  std::string getShortcut() const;

  /**
   * @brief Gets the number of arguments for the argument.
   *
   * @return The number of arguments for the argument.
   */
  int getNargs() const;

  /**
   * @brief Gets the type of the argument.
   *
   * @return The type of the argument.
   */
  Type getType() const;

  /**
   * @brief Gets the default value of the argument.
   *
   * @return The default value of the argument.
   */
  std::string getDefaultValue() const;

  /**
   * @brief Gets the help message for the argument.
   *
   * @return The help message for the argument.
   */
  std::string getHelp() const;

  /**
   * @brief Gets the choices for the argument.
   *
   * @return The choices for the argument.
   */
  std::vector<std::string> getChoices() const;
};
}  // namespace ArgumentParser
