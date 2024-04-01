/**
 * @file include/Message/Pattern.hpp
 * @author Radim Mifka (xmifka00)
 * @date March 2024
 */
#pragma once
#include <string>

namespace Message {

/**
 * @class Pattern
 * @brief Represents the patterns used in the messages.
 *
 * The Pattern class provides functionality for defining the patterns used in
 * the messages.
 */
class Pattern {
 public:
  static const std::string USERNAME;
  static const std::string DISPLAY_NAME;
  static const std::string CONTENT;
  static const std::string CHANNEL_ID;
  static const std::string SECRET;
  static const std::string CLRF;

  Pattern() = delete;
};

}  // namespace Message
