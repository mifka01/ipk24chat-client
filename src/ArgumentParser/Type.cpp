/**
 * @file src/ArgumentParser/Type.cpp
 * @author Radim Mifka (xmifka00)
 * @date March 2024
 */
#include "ArgumentParser/Type.hpp"

namespace ArgumentParser {

std::string toString(Type type) {
  switch (type) {
    case Type::BOOL:
      return "BOOL";
    case Type::UINT8:
      return "UINT8";
    case Type::INT8:
      return "INT8";
    case Type::UINT16:
      return "UINT16";
    case Type::INT16:
      return "INT16";
    case Type::FLOAT:
      return "FLOAT";
    case Type::DOUBLE:
      return "DOUBLE";
    case Type::STRING:
      return "STRING";
    case Type::HOST:
      return "HOST";
    case Type::FLAG:
      return "FLAG";
    case Type::HELP:
      return "HELP";
    default:
      return "UNKNOWN";
  }
}
}  // namespace ArgumentParser
