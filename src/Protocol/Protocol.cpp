#include "Protocol/Protocol.hpp"
#include <string>
#include <vector>
#include "Client/Session.hpp"
#include "Message/AuthMessage.hpp"
#include "Message/ByeMessage.hpp"
#include "Message/ErrMessage.hpp"
#include "Message/JoinMessage.hpp"
#include "Message/MsgMessage.hpp"
#include "Protocol/TCP.hpp"
#include "Protocol/UDP.hpp"

namespace Protocol {

std::unique_ptr<Message::Message> Protocol::toMessage(
    const Message::Type message,
    const std::vector<std::string>& parameters) {
  switch (message) {
    case Message::Type::JOIN: {
      return std::make_unique<Message::JoinMessage>(
          session.messagesSent, parameters[0], session.displayName);
    }
    case Message::Type::AUTH: {
      return std::make_unique<Message::AuthMessage>(
          session.messagesSent, parameters[0], parameters[1], parameters[2]);
    }
    case Message::Type::MSG: {
      return std::make_unique<Message::MsgMessage>(
          session.messagesSent, session.displayName, parameters[0]);
    }
    case Message::Type::BYE: {
      return std::make_unique<Message::ByeMessage>(session.messagesSent);
    }
    case Message::Type::ERR: {
      return std::make_unique<Message::ErrMessage>(
          session.messagesSent, session.displayName, parameters[0]);
    }
    default:
      throw std::runtime_error("Invalid message type");
  }
}

std::shared_ptr<Protocol> Protocol::fromString(const std::string& protocol,
                                               Client::Session& session) {
  if (protocol == "TCP") {
    return std::make_shared<TCP>(session);
  } else if (protocol == "UDP") {
    return std::make_shared<UDP>(session);
  } else {
    throw std::invalid_argument("Invalid protocol");
  }
}

}  // namespace Protocol
