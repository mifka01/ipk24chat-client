/**
 * @file src/main.cpp
 * @author Radim Mifka (xmifka00)
 * @date March 2024
 */
#include <iostream>
#include "Client/Client.hpp"
#include "arguments.hpp"

int main(int argc, char* argv[]) {
  try {
    std::unordered_map<std::string, std::string> args =
        parse_arguments(argc, argv);

    Client::Client client(args["server"], std::stoi(args["port"]),
                          Protocol::Type::TCP);

    client.run();

  } catch (std::invalid_argument& e) {
    std::cerr << "error: " << e.what() << std::endl;
    return 1;
  } catch (std::runtime_error& e) {
    std::cerr << "error: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}
