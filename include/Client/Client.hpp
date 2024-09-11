/**
 * @file include/Client/Client.hpp
 * @author Radim Mifka (xmifka00)
 * @date March 2024
 */
#pragma once

#include "Message/ErrMessage.hpp"
#include "Protocol/Protocol.hpp"
#include "SocketPoller.hpp"
#include "State/State.hpp"
#include <memory>
#include <netdb.h>
#include <string>

class State;

struct ServerInfo {
  const std::string &address;
  const int &port;
};

class Client {

private:
  const ServerInfo &server;
  const Protocol &protocol;
  std::unique_ptr<State> state;
  struct addrinfo *addrinfo;
  int socket;
  std::unique_ptr<std::string> displayName = nullptr;

  struct addrinfo *getAddrInfo() const;

public:
  SocketPoller poller;

  Client(ServerInfo &server, Protocol &protocol);
  ~Client();

  void changeState(std::unique_ptr<State> newState);

  void handleError(const ErrMessage &error);

  void send(const Message &message) const;

  void run();

  void setDisplayName(const std::string &displayName);
  const std::string &getDisplayName() const;
};
