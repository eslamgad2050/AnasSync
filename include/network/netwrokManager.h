#include "asio/io_context.hpp"
#include "asio/ip/udp.hpp"
#include "asio/steady_timer.hpp"
#include <array>
#include <asio.hpp>
#include <cstddef>
#include <memory>
#include <string>
#include <system_error>
#include <vector>

using asio::ip::udp;

class Device {
public:
  Device(udp::endpoint &e, std::string &h) {
    endpoint = e;
    host_name = h;
  }

  udp::endpoint endpoint;
  std::string host_name;
};
class UDP_server {
public:
  UDP_server(asio::io_context &context);
  void start_server();
  void receive_response();
  void scan(asio::io_context &context);

private:
  std::string host_name = "", local_address = "";
  std::vector<Device> devices;
  udp::socket socket_;
  char x[1024];
  udp::endpoint remote_endpoint, local_endpoint;
  std::array<char, 4> receive_buffer;
  void handle_send(std::shared_ptr<std::string>, const std::error_code &error,
                   size_t);
  void handle_receive(const std::error_code &error, size_t);
  void start_receive();
  void start_broadcasting(asio::io_context *context, asio::steady_timer *);
  void start_send(udp::endpoint, const std::string &);
};
