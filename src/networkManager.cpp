#include "asio/io_context.hpp"
#include "asio/ip/udp.hpp"
#include "asio/placeholders.hpp"
#include "asio/registered_buffer.hpp"
#include <functional>
#include <iostream>
#include <netwrokManager.h>
NetworkManager::NetworkManager() {}

UDP_server::UDP_server(asio::io_context &context)
    : socket_(context, udp::endpoint(udp::v4(), 13)) {
  start_receive();
};
void UDP_server::start_receive() {
  socket_.async_receive_from(asio::buffer(receive_buffer), remote_endpoint,
                             std::bind(&UDP_server::handle_receive, this,
                                       asio::placeholders::error,
                                       asio::placeholders::bytes_transferred));
}
void UDP_server::handle_send(std::shared_ptr<std::string>,
                             const std::error_code &error, size_t) {}
void UDP_server::handle_receive(const std::error_code &error, size_t b) {
  if (!error) {
    std::shared_ptr<std::string> message(new std::string("ansSync test"));
    socket_.async_send_to(asio::buffer(*message), remote_endpoint,
                          std::bind(&UDP_server::handle_send, this,
                                    message, asio::placeholders::error,
                                    asio::placeholders::bytes_transferred));
    start_receive();
  }
}
