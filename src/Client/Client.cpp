#include <Client/Client.hpp>
#include <Client/SocketPoller.hpp>
#include <iostream>

namespace Client {

Client::Client(const std::string& host,
               const int& port,
               const Protocol::Type& protocol)
    : host(host), port(port), protocol(protocol) {
  addrinfo* addr = getAddress();

  socket = ::socket(addr->ai_family, addr->ai_socktype, 0);
  if (socket <= 0) {
    freeaddrinfo(addr);
    throw std::runtime_error("Failed to create socket");
  }

  if (::connect(socket, addr->ai_addr, addr->ai_addrlen) < 0) {
    freeaddrinfo(addr);
    throw std::runtime_error("Failed to connect to server");
  }
  freeaddrinfo(addr);
}

addrinfo* Client::getAddress() {
  addrinfo hints, *addrinfo;
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = Protocol::socketType(protocol);

  if (getaddrinfo(host.c_str(), std::to_string(port).c_str(), &hints,
                  &addrinfo) != 0) {
    throw std::runtime_error("Failed to get address info");
  }
  return addrinfo;
}

void Client::send(const std::string& message) {
  if (::send(socket, message.c_str(), message.size(), 0) < 0) {
    throw std::runtime_error("Failed to send message");
  }
}

std::string Client::receive() {
  char buffer[1024];
  int bytes = ::recv(socket, buffer, sizeof(buffer), 0);
  if (bytes < 0) {
    throw std::runtime_error("Failed to receive message");
  }
  return std::string(buffer, bytes);
}

void Client::close() {
  if (socket > 0) {
    ::close(socket);
  }
}

void Client::run() {
  SocketPoller poller;

  poller.addSocket(STDIN_FILENO, POLLIN);
  poller.addSocket(socket, POLLIN);

  while (true) {
    int events = poller.poll();

    if (events < 0) {
      throw std::runtime_error("Failed to poll");
    }

    if (poller.hasEvent(0, POLLIN)) {
      std::string message;
      std::getline(std::cin, message);

      for (const auto& command : commandRegistry.commands) {
        if (command.second->match(message)) {
          message = command.second->generateMessage(protocol, message);
          send(message);
          break;
        }
      }
    }

    if (poller.hasEvent(1, POLLIN)) {
      std::string message = receive();
      std::cerr << "Received: " << message << std::endl;
    }
  }
}

Client::~Client() {
  close();
}
}  // namespace Client
