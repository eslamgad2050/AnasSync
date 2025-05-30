#include "asio/io_context.hpp"
#include "asio/ip/udp.hpp"
#include <array>
#include <asio.hpp>
#include <memory>
#include <system_error>
using asio::ip::udp;
class NetworkManager {
public:
  NetworkManager();

  void start_discovery_broadcast_lan();
};
class UDP_server {
public:
  UDP_server(asio::io_context &context);
  void start_server();
  void receive_response();

private:
  udp::socket socket_;
  udp::endpoint remote_endpoint;
  std::array<char, 1> receive_buffer;
  void handle_send(std::shared_ptr<std::string>, const std::error_code &error,
                   size_t);
  void handle_receive(const std::error_code &error, size_t);
  void start_receive();
};
