#include "Client/State/EndState.hpp"

void EndState::onEnter() { client.disconnect(); }
