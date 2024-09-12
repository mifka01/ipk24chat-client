/**
 * @file include/Command/Command.hpp
 * @author Radim Mifka (xmifka00)
 * @date March 2024
 */
#pragma once
#include "Client/Client.hpp"
#include <string>

class Client;

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
  Client &client;
  const std::string name;

  static constexpr const char *PREFIX = "/";
  static constexpr const char *WHITESPACE_REGEX = "[\\s]*";
  static constexpr const char *SPACE_REGEX = "[ ]+";

public:
  /**
   * @brief Constructs a new Command object.
   *
   * @param name The name of the command.
   * @param parameters The parameters of the command.
   */
  Command(Client &client, const std::string &name)
      : client(client), name(name) {}

  /**
   * @brief Destroys the Command object and cleans up any resources.
   */
  virtual ~Command() = default;

  /**
   * @brief Executes the command.
   */
  virtual void execute() const = 0;
};
