/**
 * @file include/ArgumentParser/Parser.hpp
 * @author Radim Mifka (xmifka00)
 * @date March 2024
 */
#pragma once

#include <string>
#include <vector>
#include "Argument.hpp"
#include "Validator.hpp"

namespace ArgumentParser {
/**
 * @class Parser
 *
 * The `Parser` class is responsible for parsing command-line arguments. It
 * provides methods to add arguments and parse the command-line arguments. The
 * `Parser` class also provides methods to print the usage and help messages.
 */
/**
 * @brief The Parser class is responsible for parsing command line arguments and
 * storing them in a data structure.
 */
class Parser {
  Validator validator;
  std::vector<Argument> positional;
  std::vector<Argument> options;
  std::vector<Argument> flags;

  /**
   * @brief Find the argument in the list of arguments.
   *
   * @param args The list of arguments.
   * @param name The name of the argument.
   * @param shortcut The shortcut of the argument.
   * @return std::vector<std::string>::const_iterator The iterator to the
   * argument.
   */
  inline std::vector<std::string>::const_iterator findArg(
      const std::vector<std::string>& args,
      const std::string& name,
      const std::string& shortcut);

  /**
   * @brief Parses the positional arguments from the given vector of strings and
   * stores the parsed arguments in the provided unordered map.
   *
   * @param args The vector of strings containing the positional arguments.
   * @param parsedArgs The unordered map to store the parsed arguments.
   */
  void parsePositional(
      const std::vector<std::string>& args,
      std::unordered_map<std::string, std::string>& parsedArgs);

  /**
   * @brief Parses the argument options from the given vector of strings and
   * stores the parsed arguments in the provided unordered map.
   *
   * @param args The vector of strings containing the options.
   * @param parsedArgs The unordered map to store the parsed arguments.
   */
  void parseOptions(const std::vector<std::string>& args,
                    std::unordered_map<std::string, std::string>& parsedArgs);

  /**
   * @brief Parses the argument flags from the given vector of strings and
   * stores the parsed arguments in the provided unordered map.
   *
   * @param args The vector of strings containing the flags.
   * @param parsedArgs The unordered map to store the parsed arguments.
   */
  void parseFlags(const std::vector<std::string>& args,
                  std::unordered_map<std::string, std::string>& parsedArgs);

 public:
  std::string programName;

  /**
   * @brief Constructs a Parser object with the given program name.
   *
   * @param programName The name of the program.
   */
  Parser(std::string programName);

  /**
   * @brief Adds a flag argument to the parser.
   *
   * @param name The name of the flag.
   * @param shortcut The shortcut of the flag.
   * @param help The help message for the flag.
   * @param required Specifies whether the flag is required or not.
   */
  void addArgument(const std::string& name,
                   const std::string& shortcut,
                   const std::string& help = "",
                   const bool& required = false);

  /**
   * @brief Adds a positional argument to the parser.
   *
   * @param name The name of the positional argument.
   * @param type The type of the positional argument.
   * @param help The help message for the positional argument.
   * @param nargs The number of arguments expected for the positional argument.
   */
  void addArgument(const std::string& name,
                   const Type& type,
                   const std::string& help = "",
                   const int& nargs = 1);

  /**
   * @brief Adds a positional argument with choices to the parser.
   *
   * @param name The name of the positional argument.
   * @param type The type of the positional argument.
   * @param help The help message for the positional argument.
   * @param choices The list of choices for the positional argument.
   * @param nargs The number of arguments expected for the positional argument.
   */
  void addArgument(const std::string& name,
                   const Type& type,
                   const std::string& help = "",
                   const std::vector<std::string>& choices = {},
                   const int& nargs = 1);

  /**
   * @brief Adds an option argument to the parser.
   *
   * @param name The name of the option argument.
   * @param shortcut The shortcut of the option argument.
   * @param type The type of the option argument.
   * @param help The help message for the option argument.
   * @param required Specifies whether the option argument is required or not.
   * @param defaultValue The default value for the option argument.
   * @param choices The list of choices for the option argument.
   * @param nargs The number of arguments expected for the option argument.
   */
  void addArgument(const std::string& name,
                   const std::string& shortcut,
                   const Type& type,
                   const std::string& help = "",
                   const bool& required = false,
                   const std::string& defaultValue = "",
                   const std::vector<std::string>& choices = {},
                   const int& nargs = 1);

  /**
   * @brief Parses the command line arguments and returns a map of parsed
   * arguments.
   *
   * @param argc The number of command line arguments.
   * @param argv The array of command line arguments.
   * @return std::unordered_map<std::string, std::string> The map of parsed
   * arguments.
   */
  std::unordered_map<std::string, std::string> parse(int argc, char* argv[]);

  /**
   * @brief Validates the choices for a given type.
   *
   * @param type The type of the argument.
   * @param choices The list of choices for the argument.
   */
  inline void validateChoices(const Type& type,
                              const std::vector<std::string>& choices);

  /**
   * @brief Prints the help message.
   */
  void printHelp();

  /**
   * @brief Prints the usage message.
   */
  void printUsage();
};
}  // namespace ArgumentParser
