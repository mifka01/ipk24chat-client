#pragma once
#include <string>

namespace Message {

class Pattern {
  Pattern() = delete;

 public:
  static const std::string USERNAME;
  static const std::string DISPLAY_NAME;
  static const std::string CONTENT;
  static const std::string CHANNEL_ID;
  static const std::string SECRET;
  static const std::string CLRF;
};

}  // namespace Message
