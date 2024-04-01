/**
 * @file include/Client/SocketPoller.hpp
 * @author Radim Mifka (xmifka00)
 * @date March 2024
 */
#pragma once
#include <poll.h>
#include <algorithm>
#include <vector>

namespace Client {

class SocketPoller {
 private:
  std::vector<pollfd> fds_;

 public:
  /**
   * @brief Adds a socket to the poller.
   *
   * @param socket The socket to add.
   * @param event The event to add.
   */
  void addSocket(int socket, int event);

  /**
   * @brief Removes a socket from the poller.
   *
   * @param socket The socket to remove.
   */
  void removeSocket(int socket);

  /**
   * @brief Polls the sockets for events.
   *
   * @param timeout The timeout for the poll in milliseconds (optional, default
   * is no timeout).
   * @return int The number of sockets with events.
   */
  int poll(int timeout = -1);

  /**
   * @brief Checks if the socket has the specified event.
   *
   * @param index The index of the socket.
   * @param event The event to check.
   * @return bool True if the socket has the event, false otherwise.
   */
  bool hasEvent(int index, int event);
};

}  // namespace Client
