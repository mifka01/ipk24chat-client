/**
 * @file include/Client/Client.hpp
 * @author Radim Mifka (xmifka00)
 * @date March 2024
 */
#pragma once

#include "Protocol/Protocol.hpp"
#include "State/State.hpp"
#include <string>

class State;

struct ServerInfo {
  const std::string &address;
  const int &port;
};

class Client {

private:
  const ServerInfo server;
  const Protocol &protocol;
  std::unique_ptr<State> state;

public:
  Client(ServerInfo server, Protocol &protocol);

  void changeState(std::unique_ptr<State> newState);

  void run();
};
