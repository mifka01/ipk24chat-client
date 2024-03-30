#pragma once

namespace Client {
class Client;
}

namespace Message {
class ErrMessage;
class AuthMessage;
class ReplyMessage;
class MsgMessage;
class ByeMessage;
class JoinMessage;
class AuthMessage;

class MessageVisitor {
  Client::Client& client;

 public:
  MessageVisitor(Client::Client& client) : client(client){};
  void visit(ErrMessage& err);
  void visit(ReplyMessage& reply);
  void visit(MsgMessage& msg);
  void visit(ByeMessage& bye);
  void visit(JoinMessage& bye);
  void visit(AuthMessage& bye);
};
}  // namespace Message
