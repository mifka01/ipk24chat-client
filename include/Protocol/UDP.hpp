/**
 * @file include/Protocol/UDP.hpp
 * @author Radim Mifka (xmifka00)
 * @date March 2024
 */
#pragma once
#include "Protocol.hpp"
#include <unordered_set>

/**
 * @class UDP
 * @brief Represents the UDP protocol.
 *
 * The UDP class provides functionality for the UDP protocol.
 */
class UDP : public Protocol {

private:
  std::unordered_set<u_int16_t> receivedMessages;

public:
  void init(int socket, addrinfo *addrinfo) override;
  void send(int socket, const Message &message) const override;
  const std::unique_ptr<Message> receive(int socket) override;

  MessageType determineMessageType(const std::string &message) const override;

  uint16_t determineMessageId(uint8_t high, uint8_t low) const;

  uint16_t determineMessageId(const std::string &message) const;

  void addMessageHeader(std::string &message, const MessageType &type,
                        const uint16_t &id) const;

  const std::string
  convertAuthMessage(const AuthMessage &message) const override;

  const std::string
  convertJoinMessage(const JoinMessage &message) const override;

  const std::string convertByeMessage(const ByeMessage &message) const override;

  const std::string convertErrMessage(const ErrMessage &message) const override;

  const std::string convertMsgMessage(const MsgMessage &message) const override;

  const std::string
  convertConfirmMessage(const ConfirmMessage &message) const override;

  std::unique_ptr<ReplyMessage>
  handleReplyMessage(const std::string &message) const override;

  std::unique_ptr<ErrMessage>
  handleErrMessage(const std::string &message) const override;

  std::unique_ptr<MsgMessage>
  handleMsgMessage(const std::string &message) const override;

  std::unique_ptr<ByeMessage>
  handleByeMessage(const std::string &message) const override;

  std::unique_ptr<ConfirmMessage>
  handleConfirmMessage(const std::string &message) const override;

  int getSocketType() const override;

  bool needConfirmation() const override { return true; };
};
