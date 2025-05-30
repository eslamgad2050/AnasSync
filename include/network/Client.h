#include "asio/io_context.hpp"
#include "asio/ip/udp.hpp"
using asio::ip::udp;
class Client {
public:
  Client(asio::io_context& context);

private:
  void descover_server();
  asio::io_context context;
  udp::endpoint server_endpoint;
};
