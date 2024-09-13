#include "Message/MsgMessage.hpp"

std::string MsgMessage::toString() const {
  return displayName + ": " + content;
}
