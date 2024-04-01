/**
 * @file src/Client/SocketPoller.cpp
 * @author Radim Mifka (xmifka00)
 * @date March 2024
 */
#include "Client/SocketPoller.hpp"

namespace Client {

void SocketPoller::addSocket(int socket, int event) {
  pollfd pfd;
  pfd.fd = socket;
  pfd.events = event;
  fds_.push_back(pfd);
}

void SocketPoller::removeSocket(int socket) {
  fds_.erase(
      std::remove_if(fds_.begin(), fds_.end(),
                     [socket](const pollfd& pfd) { return pfd.fd == socket; }),
      fds_.end());
}

int SocketPoller::poll(int timeout) {
  return ::poll(fds_.data(), fds_.size(), timeout);
}

bool SocketPoller::hasEvent(int index, int event) {
  return fds_[index].revents & event;
}

}  // namespace Client
