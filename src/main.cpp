/**
 * @file src/main.cpp
 * @author Radim Mifka (xmifka00)
 * @date March 2024
 */
#include "Client/Client.hpp"
#include "arguments.hpp"
#include <algorithm>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>

#include "Protocol/TCP.hpp"
#include "Protocol/UDP.hpp"

int main(int argc, char *argv[]) {
  try {
    std::unordered_map<std::string, std::string> args =
        parse_arguments(argc, argv);

    std::string protocol = args["transport"];
    transform(protocol.begin(), protocol.end(), protocol.begin(), ::toupper);

    ServerInfo server{args["server"], std::stoi(args["port"])};

    if (protocol == "TCP") {
      TCP tcp;
      Client client = Client(server, tcp);
      client.run();
    } else if (protocol == "UDP") {
      UDP udp;
      Client client = Client(server, udp);
      client.run();
    } else {
      throw std::invalid_argument("Invalid transport protocol.");
    }

    // client.retries = std::stoi(args["retries"]);

  } catch (std::invalid_argument &e) {
    std::cerr << "ERR: " << e.what() << std::endl;
    return 1;
  } catch (std::runtime_error &e) {
    std::cerr << "ERR: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}
