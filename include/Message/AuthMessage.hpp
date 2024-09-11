#include "Message/Message.hpp"
#include <string>

class AuthMessage : public Message {

public:
  const std::string username;
  const std::string displayName;
  const std::string secret;

  AuthMessage(const std::string username, const std::string displayName,
              const std::string secret)
      : username(username), displayName(displayName), secret(secret) {}
};
