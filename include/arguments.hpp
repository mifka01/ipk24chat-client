/**
 * @file include/arguments.hpp
 * @author Radim Mifka (xmifka00)
 * @date March 2024
 */
#pragma once
#include <string>
#include <unordered_map>

/**
 * @brief Parses the arguments.
 *
 * @param argc The number of arguments.
 * @param argv The arguments.
 * @return std::unordered_map<std::string, std::string> The map of arguments.
 */
std::unordered_map<std::string, std::string> parse_arguments(int argc,
                                                             char* argv[]);
