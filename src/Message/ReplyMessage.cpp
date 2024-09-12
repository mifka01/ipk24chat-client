#include "Message/ReplyMessage.hpp"

std::string ReplyMessage::toString() const {
  if (success) {
    return "Success: " + content;
  }
  return "Failure: " + content;
}
