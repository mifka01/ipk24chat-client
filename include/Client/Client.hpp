/**
 * @file include/Client/Client.hpp
 * @author Radim Mifka (xmifka00)
 * @date March 2024
 */
#pragma once

#include "Protocol/Protocol.hpp"
#include "SocketPoller.hpp"
#include "State/State.hpp"
#include <chrono>
#include <memory>
#include <netdb.h>
#include <queue>
#include <string>

class State;

struct ServerInfo {
  const std::string &address;
  const int &port;
};

class Client {

private:
  const ServerInfo &server;
  std::unique_ptr<State> state;
  std::unique_ptr<State> nextState = nullptr;
  struct addrinfo *addrinfo;
  int socket;
  std::unique_ptr<std::string> displayName = nullptr;
  std::string channelId = "general";
  int pollTimeout = 100;
  int confirmationTimeout = 250;
  int maxRetries = 3;

  bool isRunning = false;

  struct addrinfo *getAddrInfo() const;

public:
  Protocol &protocol;
  SocketPoller poller;
  std::unique_ptr<Message> waitingForReply = nullptr;
  std::unique_ptr<Message> waitingForConfirm = nullptr;
  std::queue<std::unique_ptr<Message>> messageQueue;

  Client(ServerInfo &server, Protocol &protocol);
  ~Client();

  void changeState(std::unique_ptr<State> newState);

  State &getState() const;

  void send(std::unique_ptr<Message> message);

  const std::unique_ptr<Message> receive();

  void processMessageQueue();

  void handleConfirmation(
      std::chrono::steady_clock::time_point &last_unconfirmed_time,
      int &retries);

  void run();

  void disconnect();

  void error(const std::string &message) const;

  void setDisplayName(const std::string &displayName);
  const std::string &getDisplayName() const;

  void setChannelId(const std::string &channelId);

  const std::string &getChannelId() const;

  void setConfirmationTimeout(int timeout);

  void setMaxRetries(int maxRetries);

  static void signalHandler(int signal);
};
