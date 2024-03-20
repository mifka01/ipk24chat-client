#pragma once
#include <poll.h>
#include <vector>

namespace Client {
class SocketPoller {
  std::vector<pollfd> fds_;

 public:
  void addSocket(int socket, int event);

  void removeSocket(int socket);

  int poll(int timeout = -1);

  bool hasEvent(int index, int event);
};

}  // namespace Client
