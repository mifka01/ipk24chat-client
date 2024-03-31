#include "Message/Pattern.hpp"

namespace Message {

const std::string Pattern::username = "[a-zA-Z0-9\\-]{1,20}";
const std::string Pattern::displayName = "[\\x21-\\x7E]{1,20}";
const std::string Pattern::content = "[\\x20-\\x7E]{1,1400}";
const std::string Pattern::channelID = "[a-zA-Z0-9\\-]{1,20}";
const std::string Pattern::secret = "[a-zA-Z0-9\\-]{1,128}";
const std::string Pattern::clrf = "\\r\\n";

}  // namespace Message
