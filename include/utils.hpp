#pragma once
#include <cstdint>
#include <string>
#include <vector>

std::vector<std::string> totokens(const std::string& str);

void addBytes(std::vector<uint8_t>& dst, const std::string& str);
