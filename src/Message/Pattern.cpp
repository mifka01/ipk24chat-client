/**
 * @file src/Message/Pattern.cpp
 * @author Radim Mifka (xmifka00)
 * @date March 2024
 */
#include "Message/Pattern.hpp"

namespace Message {

const std::string Pattern::USERNAME = "[a-zA-Z0-9\\-]{1,20}";
const std::string Pattern::DISPLAY_NAME = "[\\x21-\\x7E]{1,20}";
const std::string Pattern::CONTENT = "[\\x20-\\x7E]{1,1400}";
const std::string Pattern::CHANNEL_ID = "[a-zA-Z0-9\\-]{1,20}";
const std::string Pattern::SECRET = "[a-zA-Z0-9\\-]{1,128}";
const std::string Pattern::CLRF = "\\r\\n";

}  // namespace Message
