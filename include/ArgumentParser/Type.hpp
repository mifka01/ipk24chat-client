#pragma once
#include <string>

namespace ArgumentParser {

enum class Type {
  FLAG,
  UINT8,
  UINT16,
  INT8,
  INT16,
  FLOAT,
  DOUBLE,
  STRING,
  BOOL,
  HOST,
  HELP,

};
std::string toString(Type type);

}  // namespace ArgumentParser
