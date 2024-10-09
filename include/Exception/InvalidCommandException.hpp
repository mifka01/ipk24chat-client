#pragma once
#include <exception>
#include <string>

class InvalidCommandException : public std::exception {
private:
  std::string message;

public:
  InvalidCommandException(const std::string &msg) : message(msg) {}

  const char *what() const noexcept override { return message.c_str(); }
};
