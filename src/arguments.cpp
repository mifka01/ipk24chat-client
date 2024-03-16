#include "ArgumentParser/Parser.hpp"

std::unordered_map<std::string, std::string> parse_arguments(int argc,
                                                             char* argv[]) {
  ArgumentParser::Parser parser;

  parser.addArgument("NUMBER", ArgumentParser::Type::UINT8, "Number of items");
  parser.addArgument("--port", "-p", ArgumentParser::Type::UINT16,
                     "Port number", "4567");
  parser.addArgument("COUNT", ArgumentParser::Type::UINT8, "Count of items");

  return parser.parse(argc, argv);
}
