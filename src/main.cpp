#include <iostream>
#include "ArgumentParser/Parser.hpp"

int main(int argc, char* argv[]) {
  ArgumentParser::Parser parser;
  parser.addArgument("--port", ArgumentParser::Type::UINT16, "-p",
                     "Port number", "4567");

  parser.parse(argc, argv);
  return 0;
}
