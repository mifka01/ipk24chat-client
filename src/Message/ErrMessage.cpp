#include "Message/ErrMessage.hpp"

std::string ErrMessage::toString() const {
  return "ERR FROM " + displayName + ": " + content;
}
