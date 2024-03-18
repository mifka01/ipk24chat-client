/**
 * @file include/arguments.hpp
 * @author Radim Mifka (xmifka00)
 * @date March 2024
 */
#pragma once
#include <string>
#include <unordered_map>

std::unordered_map<std::string, std::string> parse_arguments(int argc,
                                                             char* argv[]);
