#include <Client/Client.hpp>
#include <Message/MessageVisitor.hpp>
#include <iostream>

namespace Client {

Client::Client(const std::string& host,
               const int& port,
               const std::string& protocolName)
    : host(host),
      port(port),
      protocol(Protocol::Protocol::fromString(protocolName, session)) {
  visitor = std::make_unique<Message::MessageVisitor>(*this);
  address = getAddress();

  session.socket = ::socket(address->ai_family, address->ai_socktype, 0);
  if (session.socket <= 0) {
    throw std::runtime_error("Failed to create socket");
  }
  session.serverAddr = address->ai_addr;

  if (protocol->socketType() == SOCK_STREAM &&
      ::connect(session.socket, address->ai_addr, address->ai_addrlen) != 0) {
    throw std::runtime_error("Failed to connect");
  }
}

addrinfo* Client::getAddress() {
  addrinfo hints, *addrinfo;
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = protocol->socketType();

  if (getaddrinfo(host.c_str(), std::to_string(port).c_str(), &hints,
                  &addrinfo) != 0) {
    throw std::runtime_error("Failed to get address info");
  }
  return addrinfo;
}

void Client::close() {
  if (session.socket > 0) {
    ::close(session.socket);
  }
}

bool Client::processCommand(const std::string& message) {
  for (const auto& [name, command] : commandRegistry.commands) {
    if (command->match(message)) {
      command->execute(protocol, message, session);
      return true;
    }
  }
  return false;
}

void Client::processInput() {
  State state = getState();
  if (state == State::AUTH) {
    return;
  }

  std::string message;
  std::getline(std::cin, message);
  if (message.empty()) {
    return;
  }
  if (processCommand(message)) {
    return;
  }

  if (std::any_of(commandRegistry.prefixes.begin(),
                  commandRegistry.prefixes.end(),
                  [&message](const std::string& prefix) {
                    return message.starts_with(prefix);
                  })) {
    std::cerr << "ERR: trying to process an unknown or otherwise malformed "
                 "command.\n";
    return;
  }

  if (state == State::START) {
    if (message == "BYE") {
      protocol->send(session.socket,
                     protocol->toMessage(Message::Type::BYE, {}));
      state = State::END;
      return;
    }
  }
  if (state == State::OPEN) {
    if (message == "BYE") {
      protocol->send(session.socket,
                     protocol->toMessage(Message::Type::BYE, {}));
      state = State::END;
      return;
    }
    protocol->send(session.socket,
                   protocol->toMessage(Message::Type::MSG, {message}));
    return;
  }

  std::cerr << "ERR: trying to send a message in non-open state\n";
}

void Client::processReply() {
  std::unique_ptr<Message::Message> reply = protocol->receive(session.socket);
  reply->accept(*visitor);
}

void Client::run() {
  SocketPoller poller;

  poller.addSocket(STDIN_FILENO, POLLIN);
  poller.addSocket(session.socket, POLLIN);

  while (true) {
    int events = poller.poll();

    if (events < 0) {
      throw std::runtime_error("Failed to poll");
    }

    if (poller.hasEvent(0, POLLIN)) {
      processInput();
    }
    if (poller.hasEvent(1, POLLIN)) {
      processReply();
    }
  }
}

Client::~Client() {
  close();
  freeaddrinfo(address);
}
}  // namespace Client
