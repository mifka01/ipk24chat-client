#pragma once

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
};
}  // namespace ArgumentParser
