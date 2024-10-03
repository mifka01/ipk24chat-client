#include "Client/State/ErrorState.hpp"
#include "Client/State/EndState.hpp"

void ErrorState::onEnter() {
  client.send(ByeMessage());
  client.changeState(std::make_unique<EndState>(client));
  return;
}
