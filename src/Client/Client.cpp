#include <Client/Client.hpp>
#include <Message/MessageVisitor.hpp>
#include "Protocol/Type.hpp"

namespace Client {

Client::Client(const std::string& host,
               const int& port,
               const std::string& protocolName)
    : host(host),
      port(port),
      protocol(Protocol::Protocol::fromString(protocolName, *this)) {
  visitor = std::make_unique<Message::MessageVisitor>(*this);
  address = getAddress();

  socket = ::socket(address->ai_family, address->ai_socktype, 0);
  if (socket <= 0) {
    throw std::runtime_error("Failed to create socket");
  }
  serverAddr = address->ai_addr;

  if (protocol->getType() == Protocol::Type::TCP &&
      ::connect(socket, address->ai_addr, address->ai_addrlen) != 0) {
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
  if (socket > 0) {
    ::close(socket);
  }
}

void Client::run() {
  protocol->run();
}

Client::~Client() {
  close();
  freeaddrinfo(address);
}
}  // namespace Client
