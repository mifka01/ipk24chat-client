#include "Client/Client.hpp"
#include "Client/State/StartState.hpp"
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <unistd.h>

Client::Client(ServerInfo &server, Protocol &protocol)
    : server(server), protocol(protocol),
      state(std::make_unique<StartState>(*this)) {

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
  state = std::move(newState);
}

Client::~Client() {
  if (socket > 0) {
    close(socket);
  }
  freeaddrinfo(addrinfo);
}

void Client::send(const Message &message) const {
  protocol.send(socket, message);
}

const std::unique_ptr<Message> Client::receive() {
  return protocol.receive(socket);
}

void Client::run() {
  isRunning = true;

  while (true) {
    state->onEnter();
    if (!isRunning) {
      break;
    }

    int events = poller.poll();

    if (events < 0) {
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
