/**
 * @file include/Message/MessageVisitor.hpp
 * @author Radim Mifka (xmifka00)
 * @date March 2024
 */
#pragma once

// Forward declaration
namespace Client {
class Client;
}

namespace Message {

// Forward declaration
class ErrMessage;
class AuthMessage;
class ReplyMessage;
class MsgMessage;
class ByeMessage;
class JoinMessage;
class ConfirmMessage;

/**
 * @class MessageVisitor
 * @brief Represents a message visitor.
 *
 * The MessageVisitor class is used to visit messages.
 */
class MessageVisitor {
 private:
  Client::Client& client;

 public:
  /**
   * @brief Constructs a message visitor.
   * @param client The client.
   */
  MessageVisitor(Client::Client& client) : client(client){};

  /**
   * @brief Visits an error message.
   * @param err The error message.
   */
  void visit(ErrMessage& err);

  /**
   * @brief Visits an auth message.
   * @param auth The auth message.
   */
  [[maybe_unused]] void visit(AuthMessage& auth);

  /**
   * @brief Visits a reply message.
   * @param reply The reply message.
   */
  void visit(ReplyMessage& reply);

  /**
   * @brief Visits a msg message.
   * @param msg The msg message.
   */
  void visit(MsgMessage& msg);

  /**
   * @brief Visits a bye message.
   * @param bye The bye message.
   */
  void visit(ByeMessage& bye);

  /**
   * @brief Visits a join message.
   * @param join The join message.
   */
  [[maybe_unused]] void visit(JoinMessage& join);

  /**
   * @brief Visits a confirm message.
   * @param confirm The confirm message.
   */
  [[maybe_unused]] void visit(ConfirmMessage& confirm);
};

}  // namespace Message
