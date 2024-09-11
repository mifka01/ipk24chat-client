/**
 * @file src/Command/AuthCommand.cpp
 * @author Radim Mifka (xmifka00)
 * @date March 2024
 */
#include "Command/AuthCommand.hpp"

const std::regex
    AuthCommand::PATTERN("^" + std::string(WHITESPACE_REGEX) + PREFIX +
                             COMMAND_NAME + SPACE_REGEX + USERNAME_REGEX +
                             SPACE_REGEX + SECRET_REGEX + SPACE_REGEX +
                             DISPLAY_NAME_REGEX + WHITESPACE_REGEX + "$",
                         std::regex::icase);
