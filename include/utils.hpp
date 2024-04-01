/**
 * @file include/utils.hpp
 * @author Radim Mifka (xmifka00)
 * @date March 2024
 */
#pragma once
#include <cstdint>
#include <string>
#include <vector>

/**
 * @brief Splits the string into tokens.
 *
 * @param str The string to split.
 * @return std::vector<std::string> The vector of tokens.
 */
std::vector<std::string> totokens(const std::string& str);

/**
 * @brief Adds the bytes of the string to the vector.
 *
 * @param dst The vector to add the bytes to.
 * @param str The string to add the bytes from.
 */
void addBytes(std::vector<uint8_t>& dst, const std::string& str);
