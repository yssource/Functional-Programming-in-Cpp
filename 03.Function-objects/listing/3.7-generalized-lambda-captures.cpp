#include <iostream>
#include <memory>
#include <functional>
#include <string>
#include <utility>
#include <ctime>

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
std::time_t current_time();

int main() {
  server_t server;

  std::unique_ptr<session_t> session{ create_session() };

  auto request{ server.request("GET /", session->id()) };

  request.on_completed(
    [ session = std::move(session),
      time = current_time()
    ](response_t response) {
    std::cout
      << "Got response: " << response
      << " for session: " << session;
      << " the request took: "
      << (current_time() - time)
      << "milliseconds";
  });
}
