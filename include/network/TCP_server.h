
#include "asio/io_context.hpp"
#include "asio/ip/tcp.hpp"
#include <array>
#include <asio.hpp>
#include <memory>
#include <system_error>
using asio::ip::tcp;
class TCP_server {
public:
private:
  tcp::socket socket;
  asio::io_context context;
};
