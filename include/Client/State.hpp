/**
 * @file include/Client/State.hpp
 * @author Radim Mifka (xmifka00)
 * @date March 2024
 */
#pragma once

namespace Client {
/**
 * @enum State
 * @brief Represents the possible states of a client.
 */
enum class State { AUTH, CONFIRM, END, OPEN, START };

}  // namespace Client
