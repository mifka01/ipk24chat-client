#include "Protocol/Type.hpp"

namespace Protocol {

int socketType(Type type) {
  switch (type) {
    case Type::TCP:
      return SOCK_STREAM;
    case Type::UDP:
      return SOCK_DGRAM;
    default:
      return -1;
  }
}

std::string toString(Type type) {
  switch (type) {
    case Type::TCP:
      return "TCP";
    case Type::UDP:
      return "UDP";
    default:
      return "UNKNOWN";
  }
}
}  // namespace Protocol
