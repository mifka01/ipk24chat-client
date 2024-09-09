/**
 * @file src/Protocol/TCP.cpp
 * @author Radim Mifka (xmifka00)
 * @date March 2024
 */
#include "Protocol/TCP.hpp"
#include <iostream>

void TCP::init() {
  std::cout << port << std::endl;
  port = 80;
  std::cout << port << std::endl;
}

void TCP::send() const {
  // Send data using the TCP protocol.
}

void TCP::recieve() const {
  // Recieve data using the TCP protocol.
}
