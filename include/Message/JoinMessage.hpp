#pragma once
#include "Message/Message.hpp"
#include <string>

class JoinMessage : public Message {

public:
  const std::string channelId;
  const std::string displayName;

  JoinMessage(const std::string channelId, const std::string displayName)
      : Message(MessageType::JOIN), channelId(channelId),
        displayName(displayName) {}

  JoinMessage(const u_int16_t id, const std::string channelId,
              const std::string displayName)
      : Message(MessageType::AUTH, id), channelId(channelId),
        displayName(displayName) {}
};
