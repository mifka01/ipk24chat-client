#include "utils.hpp"
#include <sstream>

std::vector<std::string> totokens(const std::string& str) {
  std::stringstream ss(str);
  std::string word;
  std::vector<std::string> tokens;

  while (ss >> word) {
    tokens.push_back(word);
  }

  return tokens;
}

void addBytes(std::vector<uint8_t>& dst, const std::string& str) {
  for (char c : str) {
    dst.push_back(c);
  }
  dst.push_back(0);
}
