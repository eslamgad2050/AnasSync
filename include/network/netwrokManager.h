#include "asio/io_context.hpp"
#include "asio/ip/tcp.hpp"
#include "asio/ip/udp.hpp"
#include "asio/steady_timer.hpp"
#include <array>
#include <asio.hpp>
#include <memory>
#include <system_error>

using asio::ip::tcp;
using asio::ip::udp;

class TCP_server {
public:
private:
  tcp::socket socket;
};

class UDP_server {
public:
  UDP_server(asio::io_context &context);
  void start_server();
  void receive_response();
  void scan(asio::io_context &context);
  void start_broadcasting(asio::io_context *context, asio::steady_timer* );

private:
  udp::socket socket_;
  char x[5];
  udp::endpoint remote_endpoint;
  std::array<char, 4> receive_buffer;
  void handle_send(std::shared_ptr<std::string>, const std::error_code &error,
                   size_t);
  void handle_receive(const std::error_code &error, size_t);
  void start_receive();
};
