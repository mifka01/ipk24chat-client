/**
 * @file src/main.cpp
 * @author Radim Mifka (xmifka00)
 * @date March 2024
 */
#include <iostream>
#include "Client/Client.hpp"
#include "Command/AUTHCommand.hpp"
#include "Command/HELPCommand.hpp"
#include "Command/JOINCommand.hpp"
#include "Command/RENAMECommand.hpp"
#include "Protocol/TCP.hpp"
#include "arguments.hpp"

int main(int argc, char* argv[]) {
  try {
    std::unordered_map<std::string, std::string> args =
        parse_arguments(argc, argv);

    Protocol::TCP protocol = Protocol::TCP();

    Client::Client client(args["server"], std::stoi(args["port"]), protocol);

    client.commandRegistry.add("AUTH",
                               std::make_unique<Command::AUTHCommand>());
    client.commandRegistry.add("JOIN",
                               std::make_unique<Command::JOINCommand>());
    client.commandRegistry.add("RENAME",
                               std::make_unique<Command::RENAMECommand>());
    client.commandRegistry.add("HELP",
                               std::make_unique<Command::HELPCommand>());
    client.run();

  } catch (std::invalid_argument& e) {
    std::cerr << "ERR: " << e.what() << std::endl;
    return 1;
  } catch (std::runtime_error& e) {
    std::cerr << "ERR: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}
