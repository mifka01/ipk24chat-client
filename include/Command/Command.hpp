/**
 * @file include/Command/Command.hpp
 * @author Radim Mifka (xmifka00)
 * @date March 2024
 */
#pragma once
#include <regex>
#include <string>
#include <vector>

#include "Parameter.hpp"
#include "Protocol/Protocol.hpp"

namespace Command {

/**
 * @class Command
 * @brief Represents a command that can be executed by a client.
 *
 * The Command class provides functionality for matching a command with a
 * message, executing the command, and generating a regular expression for
 * matching the command.
 */
class Command {
 protected:
  std::string name;
  std::string prefix;
  std::vector<Parameter> parameters;
  std::regex regex;

  const std::string COMMAND_NAME_REGEX = "^[a-zA-Z0-9_\\-]+$";
  const std::string WHITESPACE_REGEX = "[^\\S\\n]*";

  /**
   * @brief Generates a regular expression for matching the command.
   *
   * The regular expression is generated based on the command's name and
   * parameters.
   * The regular expression is stored in the regex member variable.
   *
   **/
  void generateRegex();

 public:
  /**
   * @brief Constructs a new Command object.
   *
   * @param name The name of the command.
   * @param prefix The prefix of the command.
   * @param parameters The parameters of the command.
   */
  Command(const std::string& name,
          const std::string& prefix,
          const std::vector<Parameter>& parameters);

  /**
   * @brief Destroys the Command object and cleans up any resources.
   */
  virtual ~Command() = default;

  /**
   * @brief Matches the command with a message.
   * @param message The message to match.
   * @return True if the command matches the message, otherwise false.
   */
  bool match(const std::string& message) const;
  const std::string& getPrefix() const;

  /**
   * @brief Executes the command.
   * @param protocol The protocol to use for communication.
   * @param message The message to execute.
   * @param client The client that executed the command.
   */
  virtual void execute(std::shared_ptr<Protocol::Protocol> protocol,
                       const std::string& message,
                       Client::Client& client) = 0;
};

}  // namespace Command
