/**
 * @file include/ArgumentParser/Type.hpp
 * @author Radim Mifka (xmifka00)
 * @date March 2024
 */
#pragma once
#include <string>

namespace ArgumentParser {
/**
 * @brief Defines the `Type` enumeration for argument types and provides a
 * function to convert the enumeration value to its string representation.
 */
enum class Type {
  BOOL,
  UINT8,
  INT8,
  UINT16,
  INT16,
  FLOAT,
  DOUBLE,
  STRING,
  HOST,
  FLAG,
  HELP,
};

/**
 * @brief Converts the given `Type` enumeration value to its string
 * representation.
 *
 * @param type The `Type` enumeration value to convert.
 * @return The string representation of the given `Type` value.
 */
std::string toString(Type type);

}  // namespace ArgumentParser
