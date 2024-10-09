#pragma once
#include <exception>
#include <string>

class InvalidMessageException : public std::exception {
private:
  std::string message;

public:
  InvalidMessageException(const std::string &msg) : message(msg) {}

  const char *what() const noexcept override { return message.c_str(); }
};
