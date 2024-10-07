#include "Client/Client.hpp"
#include "Client/State/AuthState.hpp"
#include <chrono>
#include <csignal>
#include <cstring>
#include <iostream>
#include <signal.h>
#include <stdexcept>
#include <unistd.h>

Client *clientInstance = nullptr;

void sigintHandler(int signum) {
  if (signum == SIGINT) {
    clientInstance->getState().handleSigInt();
  }
}

Client::Client(ServerInfo &server, Protocol &protocol)
    : server(server), state(std::make_unique<AuthState>(*this)),
      protocol(protocol) {

  addrinfo = getAddrInfo();

  socket = ::socket(addrinfo->ai_family, addrinfo->ai_socktype,
                    addrinfo->ai_protocol);
  if (socket <= 0) {
    throw std::runtime_error("Failed to create socket");
  }

  protocol.init(socket, addrinfo);

  poller.addSocket(STDIN_FILENO, POLLIN);
  poller.addSocket(socket, POLLIN);
}

void Client::changeState(std::unique_ptr<State> newState) {
  nextState = std::move(newState);
}

State &Client::getState() const { return *state; }

Client::~Client() {
  if (socket > 0) {
    close(socket);
  }
  freeaddrinfo(addrinfo);
}

void Client::send(std::unique_ptr<Message> message) {
  messageQueue.push(std::move(message));
}

const std::unique_ptr<Message> Client::receive() {
  return protocol.receive(socket);
}

void Client::processMessageQueue() {
  if (!messageQueue.empty()) {
    std::unique_ptr<Message> message = std::move(messageQueue.front());
    messageQueue.pop();
    protocol.send(socket, *message);

    if (protocol.needConfirmation() && message->type != MessageType::CONFIRM) {
      if (message->type != MessageType::CONFIRM) {
        waitingForConfirm = std::move(message);
      }
    } else if (message->type == MessageType::AUTH ||
               message->type == MessageType::JOIN) {
      waitingForReply = std::move(message);
    }

  } else if (nextState != nullptr) {
    state = std::move(nextState);
    nextState = nullptr;
  }
}

void Client::handleConfirmation(
    std::chrono::steady_clock::time_point &last_unconfirmed_time,
    int &retries) {

  if (!protocol.needConfirmation())
    return;

  auto current_time = std::chrono::steady_clock::now();
  auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(
      current_time - last_unconfirmed_time);

  if (elapsed_time.count() < confirmationTimeout)
    return;

  if (waitingForConfirm != nullptr && retries < 3) {
    protocol.send(socket, *waitingForConfirm);
    retries++;
  } else {
    waitingForConfirm = nullptr;
    retries = 0;
    processMessageQueue();
  }
  last_unconfirmed_time = std::chrono::steady_clock::now();
}

void Client::run() {
  clientInstance = this;

  signal(SIGINT, sigintHandler);

  isRunning = true;

  auto last_unconfirmed_time = std::chrono::steady_clock::now();
  int retries = maxRetries;

  while (true) {
    state->onEnter();
    if (!isRunning) {
      break;
    }

    int events = poller.poll(pollTimeout);

    if (protocol.needConfirmation()) {
      handleConfirmation(last_unconfirmed_time, retries);
    } else {
      processMessageQueue();
    }

    if (events < 0) {
      if (errno == EINTR) {
        continue;
      }
      throw std::runtime_error("Failed to poll");
    }

    if (poller.hasEvent(1, POLLIN)) {
      state->handleResponse();
    }

    if (poller.hasEvent(0, POLLIN)) {
      state->handleInput();
    }
  }
}

void Client::disconnect() { isRunning = false; }

void Client::error(const std::string &message) const {
  std::cerr << "ERR: " << message << std::endl;
}

addrinfo *Client::getAddrInfo() const {
  struct addrinfo hints, *addrinfo;
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = protocol.getSocketType();

  if (getaddrinfo(server.address.c_str(), std::to_string(server.port).c_str(),
                  &hints, &addrinfo) != 0) {
    throw std::runtime_error("Failed to get address info");
  }
  return addrinfo;
}

void Client::setDisplayName(const std::string &displayName) {
  if (displayName.empty()) {
    this->displayName = nullptr;
    return;
  }
  this->displayName = std::make_unique<std::string>(displayName);
}

const std::string &Client::getDisplayName() const { return *displayName; }

void Client::setChannelId(const std::string &channelId) {
  this->channelId = channelId;
}

const std::string &Client::getChannelId() const { return channelId; }

void Client::setConfirmationTimeout(int timeout) {
  confirmationTimeout = timeout;
}

void Client::setMaxRetries(int retries) { maxRetries = retries; }
