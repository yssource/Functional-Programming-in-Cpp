#include <iostream>
#include <memory>
#include <functional>
#include <string>

class response_t;

class session_t {
public:
  auto id() -> int;
};

class request_t {
public:
  auto on_completed(std::function<void(response_t)>) -> void;
};

class server_t {
public:
  auto request(std::string, int) -> request_t;
};

auto create_session() -> session_t;

std::ostream& operator<<(std::ostream& os, response_t);
std::ostream& operator<<(std::ostream& os, session_t);

int main() {
  server_t server;

  std::unique_ptr<session_t> session{ create_session() };

  auto request{ server.request("GET /", session->id()) };

  request.on_completed(
    // Error: there's no copy-constructor for std::unique_ptr<session_t>.
    [session](response_t response) {
    std::cout << "Got response: " << response
      << " for session: " << session;
  });
}
