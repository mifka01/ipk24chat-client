#pragma once
#include <string>

namespace Message {

class Pattern {
  Pattern() = delete;

 public:
  static const std::string username;
  static const std::string displayName;
  static const std::string content;
  static const std::string channelID;
  static const std::string secret;
  static const std::string clrf;
};

}  // namespace Message
