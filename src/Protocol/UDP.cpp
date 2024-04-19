/**
 * @file src/Protocol/UDP.cpp
 * @author Radim Mifka (xmifka00)
 * @date March 2024
 */
#include "Protocol/UDP.hpp"
#include <iostream>
#include <string>
#include <vector>
#include "Client/Client.hpp"
#include "Message/ByeMessage.hpp"
#include "Message/ConfirmMessage.hpp"
#include "Message/ErrMessage.hpp"
#include "Message/MsgMessage.hpp"
#include "Message/ReplyMessage.hpp"

namespace Protocol {

void UDP::send(std::unique_ptr<Message::Message> message) {
  std::vector<uint8_t> serialized = message->udpSerialize();
  ssize_t sent = sendto(client.socket, serialized.data(), serialized.size(), 0,
                        client.serverAddr, sizeof(*client.serverAddr));
  if (sent == -1) {
    throw std::runtime_error("Failed to send message");
  }

  if (message->type == Message::Type::CONFIRM) {
    return;
  }

  if (client.state != Client::State::CONFIRM) {
    lastState = client.state;
  }
  lastSentMessage = std::move(message);
  client.state = Client::State::CONFIRM;
  client.messagesSent++;
}

std::unique_ptr<Message::Message> UDP::receive() {
  char buffer[BUFFER_SIZE];
  socklen_t serverAddrLen = sizeof(*client.serverAddr);
  ssize_t received = recvfrom(client.socket, buffer, sizeof(buffer), 0,
                              client.serverAddr, &serverAddrLen);

  if (received == -1) {
    throw std::runtime_error("Failed to receive message");
  }

  if (received == 0) {
    return std::make_unique<Message::ByeMessage>(Message::ByeMessage(0));
  }

  Message::Type type =
      static_cast<Message::Type>(static_cast<unsigned char>(buffer[0]));
  uint16_t messageId = ntohs((buffer[1] << 8) | buffer[2]);

  switch (type) {
    case Message::Type::ERR: {
      char* displayNameStart = buffer + 3;
      std::string displayName = std::string(displayNameStart);

      char* displayNameEnd =
          std::find(displayNameStart, buffer + received, '\0');

      char* messageContentsStart = displayNameEnd + 1;
      std::string content = std::string(messageContentsStart);

      return std::make_unique<Message::ErrMessage>(
          Message::ErrMessage(messageId, displayName, content));
    }
    case Message::Type::REPLY: {
      uint8_t result = buffer[3];
      uint16_t refMessageId = buffer[4] << 8 | buffer[5];
      char* messageContents = buffer + 6;

      return std::make_unique<Message::ReplyMessage>(Message::ReplyMessage(
          messageId, result, messageContents, refMessageId));
    }
    case Message::Type::MSG: {
      char* displayNameStart = buffer + 3;
      std::string displayName = std::string(displayNameStart);

      char* displayNameEnd =
          std::find(displayNameStart, buffer + received, '\0');

      char* messageContentsStart = displayNameEnd + 1;

      std::string content = std::string(messageContentsStart);
      return std::make_unique<Message::MsgMessage>(
          Message::MsgMessage(messageId, displayName, content));
    }
    case Message::Type::BYE: {
      return std::make_unique<Message::ByeMessage>(
          Message::ByeMessage(messageId));
    }
    case Message::Type::CONFIRM: {
      return std::make_unique<Message::ConfirmMessage>(
          Message::ConfirmMessage(messageId));
    }
    default:
      break;
  }
  send(toMessage(Message::Type::CONFIRM, {std::to_string(messageId)}));
  send(toMessage(Message::Type::ERR, {"Invalid format of message"}));
  throw std::runtime_error("Invalid format of message");
}

void UDP::setNextState(Client::State state) {
  nextState = state;
}

void UDP::processReply() {
  std::unique_ptr<Message::Message> reply = client.protocol->receive();
  auto it = std::find(std::begin(receivedMessages), std::end(receivedMessages),
                      reply->id);

  if (it != std::end(receivedMessages) &&
      reply->type != Message::Type::CONFIRM) {
    send(toMessage(Message::Type::CONFIRM, {std::to_string(reply->id)}));
    return;
  }

  if (reply->type != Message::Type::CONFIRM) {
    receivedMessages.push_back(reply->id);
  }

  if (reply->type == Message::Type::CONFIRM) {
    confirm(reply->id);
    return;
  }
  reply->accept(*client.visitor);
  send(toMessage(Message::Type::CONFIRM, {std::to_string(reply->id)}));
}

void UDP::confirm(uint16_t messageID) {
  if (lastSentMessage->id == messageID) {
    curRetries = client.retries;
    client.state = nextState;
  }
}

void UDP::run() {
  client.poller.addSocket(STDIN_FILENO, POLLIN);
  client.poller.addSocket(client.socket, POLLIN);

  while (true) {
    curRetries = 0;
    if (client.state == Client::State::END) {
      if (lastSentMessage->type != Message::Type::BYE) {
        client.protocol->send(
            client.protocol->toMessage(Message::Type::BYE, {}));
      }
      break;
    } else if (client.state == Client::State::CONFIRM) {
      while (curRetries < client.retries) {
        int events = client.poller.poll(client.timeout);
        if (events < 0) {
          throw std::runtime_error("Failed to poll");
        }

        if (client.poller.hasEvent(1, POLLIN)) {
          // sets the curRetries to max when a message is confirmed
          processReply();
          // If the message was confirmed, break out of the loop
          if (curRetries == client.retries) {
            break;
          }
        }

        curRetries++;
        send(std::move(lastSentMessage));
      }
      if (client.state == Client::State::CONFIRM) {
        std::cerr << "ERR: message lost in transit" << std::endl;
        client.state = lastState;
      }
    } else {
      int events = client.poller.poll();
      if (events < 0) {
        throw std::runtime_error("Failed to poll");
      }
      if (client.poller.hasEvent(0, POLLIN)) {
        processInput();
      }
      if (client.poller.hasEvent(1, POLLIN)) {
        processReply();
      }
    }
  }
}

}  // namespace Protocol
