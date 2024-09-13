/**
 * @file include/Protocol/TCP.hpp
 * @author Radim Mifka (xmifka00)
 * @date March 2024
 */
#pragma once
#include "Protocol.hpp"

/**
 * @class TCP
 * @brief Represents the TCP protocol.
 *
 * The TCP class provides functionality for the TCP protocol.
 */
class TCP : public Protocol {

private:
  std::string buffer;
  static constexpr const char *CRLF = "\r\n";

public:
  void init(int socket, addrinfo *addrinfo) override;

  void send(int socket, const Message &message) const override;

  const std::unique_ptr<Message> receive(int socket) override;

  MessageType determineMessageType(const std::string &message) const override;

  const std::string
  convertAuthMessage(const AuthMessage &message) const override;

  const std::string convertByeMessage(const ByeMessage &message) const override;

  const std::string convertErrMessage(const ErrMessage &message) const override;

  const std::string convertMsgMessage(const MsgMessage &message) const override;

  std::unique_ptr<ReplyMessage>
  handleReplyMessage(const std::string &message) const override;

  std::unique_ptr<ErrMessage>
  handleErrMessage(const std::string &message) const override;

  std::unique_ptr<MsgMessage>
  handleMsgMessage(const std::string &message) const override;

  std::unique_ptr<ByeMessage>
  handleByeMessage(const std::string &message) const override;

  int getSocketType() const override;
};
