#include "asio/detail/chrono.hpp"
#include "asio/io_context.hpp"
#include "asio/ip/address_v4.hpp"
#include "asio/ip/udp.hpp"
#include "asio/placeholders.hpp"
#include "asio/socket_base.hpp"
#include "asio/steady_timer.hpp"
#include "asio/thread.hpp"
#include <functional>
#include <iostream>
#include <memory>
#include <network/netwrokManager.h>
#include <string>

void UDP_server::scan(asio::io_context &context) {
  asio::io_context c;
  std::cout << "start scan \n";
  asio::steady_timer timer(c, asio::chrono::milliseconds(1));
  timer.async_wait(
      std::bind(&UDP_server::start_broadcasting, this, &c, &timer));
std:
  asio::thread t([&c]{c.run();});
  t.join();
}

void UDP_server::start_broadcasting(asio::io_context *context,
                                    asio::steady_timer *timer) {
  std::cout << std::endl << "start_broadcasting" << std::endl;
  asio::ip::udp::socket socket(*context);
  socket.open(asio::ip::udp::v4());
  socket.set_option(asio::socket_base::broadcast(true));
  socket.set_option(asio::socket_base::reuse_address(true));
  asio::ip::udp::endpoint broadcast_endpoint(asio::ip::address_v4::broadcast(),
                                             8080);
  std::shared_ptr<std::string> message(new std::string("hello AnasSync"));
  socket.async_send_to(asio::buffer(*message), broadcast_endpoint,
                       std::bind(&UDP_server::handle_send, this, message,
                                 asio::placeholders::error,
                                 asio::placeholders::bytes_transferred));
  std::cout << "\nsend the message\n";
  socket.close();
  timer->expires_at(timer->expiry() + asio::chrono::milliseconds(10000));
  timer->async_wait(
      std::bind(&UDP_server::start_broadcasting, this, context, timer));
  start_receive();
}

UDP_server::UDP_server(asio::io_context &context)
    : socket_(context, udp::endpoint(asio::ip::address_v4::any(), 8080)) {
  socket_.set_option(asio::socket_base::reuse_address(true));
  start_receive();
}

void UDP_server::start_receive() {
  socket_.async_receive_from(asio::buffer(x), remote_endpoint,
                             std::bind(&UDP_server::handle_receive, this,
                                       asio::placeholders::error,
                                       asio::placeholders::bytes_transferred));
}
void UDP_server::handle_send(std::shared_ptr<std::string> m,
                             const std::error_code &error, size_t) {
  // std::cout << std::endl << error;
}
void UDP_server::handle_receive(const std::error_code &error, size_t b) {
  if (!error) {
    std::cout << "\n buffer=" << receive_buffer.data() << "\n";
    std::cout << "\n x =" << x << "\n";
    std::shared_ptr<std::string> message(
        new std::string("hello anasSync using udp server sending"));
    socket_.async_send_to(asio::buffer(*message), remote_endpoint,
                          std::bind(&UDP_server::handle_send, this, message,
                                    asio::placeholders::error,
                                    asio::placeholders::bytes_transferred));
    start_receive();
  }
}
