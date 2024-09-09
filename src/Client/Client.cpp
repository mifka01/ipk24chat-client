#include "Client/Client.hpp"
#include "Client/State/StartState.hpp"

Client::Client(ServerInfo server, Protocol &protocol)
    : server(server), protocol(protocol),
      state(std::make_unique<StartState>(*this)) {
  protocol.init();
}

void Client::changeState(std::unique_ptr<State> newState) {
  state = std::move(newState);
}

void Client::run() {}
