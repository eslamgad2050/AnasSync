#include "asio/detail/chrono.hpp"
#include "asio/steady_timer.hpp"
#include <asio.hpp>
#include <exception>
#include <iostream>
#include <network/netwrokManager.h>
using namespace std;
int main() {
  while (true) {
    asio::io_context io;
    asio::steady_timer timer(io, asio::chrono::seconds(5));
    int x;
    cout << "wnter wahat you want to do "
            "\n1) for scan";
    cin >> x;
    switch (x) {
    case 1:
      cout << "\nscaning\n";
      try {
        asio::io_context context;
        UDP_server UD(context);
        cout << "no error";
        context.run();
      } catch (exception &e) {
        cerr << e.what() << endl;
        cout << "error";
      }
      break;
    case 2:
      break;
    default:
      break;
      break;
    }
  }
  cout << "program ended";
  return 0;
}
