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
class ConfirmMessage;

class MessageVisitor {
 private:
  Client::Client& client;

 public:
  MessageVisitor(Client::Client& client) : client(client){};

  void visit(ErrMessage& err);
  void visit(AuthMessage& auth);
  void visit(ReplyMessage& reply);
  void visit(MsgMessage& msg);
  void visit(ByeMessage& bye);
  void visit(JoinMessage& join);
  void visit(ConfirmMessage& confirm);
};

}  // namespace Message
