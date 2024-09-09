#pragma once

#include "Client/Client.hpp"

class Client;

class State {

protected:
  Client &client;

public:
  State(Client &client) : client(client) {}
};
