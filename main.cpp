#include <asio.hpp>
#include <exception>
#include <iostream>
#include <network/netwrokManager.h>
#include <thread>
using namespace std;
int main() {
  {
    try {
      asio::io_context context;
      UDP_server UD(context);
      std::thread th([&context] { context.run(); });
      cout << "no error\n";
      UD.scan(context);
      th.join();
    } catch (exception &e) {
      cerr << e.what() << endl;
      cout << "error";
    }
    int x;
    cout << "wahat you want to do "
            "\n1) for scan";
    cin >> x;
    switch (x) {
    case 1:
      cout << "\nscaning\n";
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
