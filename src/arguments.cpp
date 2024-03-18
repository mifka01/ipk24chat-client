#include "ArgumentParser/Parser.hpp"

std::unordered_map<std::string, std::string> parse_arguments(int argc,
                                                             char* argv[]) {
  ArgumentParser::Parser parser;

  parser.addArgument("--transport", "-t", ArgumentParser::Type::STRING,
                     "Transport protocol", true, "", {"UDP", "TCP"});

  parser.addArgument("--server", "-s", ArgumentParser::Type::HOST,
                     "Transport protocol", true);
  parser.addArgument("--port", "-p", ArgumentParser::Type::UINT16,
                     "Port number", false, "4567");

  parser.addArgument("--udptimeout", "-d", ArgumentParser::Type::UINT16,
                     "UDP confirmation timeout", false, "250");

  parser.addArgument("--retries", "-r", ArgumentParser::Type::UINT8,
                     "Maximum number of UDP retransmissions", false, "3");

  return parser.parse(argc, argv);
}
