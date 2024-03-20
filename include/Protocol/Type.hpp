#pragma once
#include <sys/socket.h>
#include <string>

namespace Protocol {
enum class Type {
  TCP,
  UDP,
};

int socketType(Type type);

std::string toString(Type type);

}  // namespace Protocol
