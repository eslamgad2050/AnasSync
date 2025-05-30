#include "asio/io_context.hpp"
#include <exception>
#include <iostream>
#include <netwrokManager.h>
using namespace std;
int main() {
  try {
    asio::io_context context;
    UDP_server UDP_server(context);
    cout << "no errror";
    context.run();
  } catch (exception &e) {
    cerr << e.what() << endl;
    cout << "error";
  }
  cout << "progrmam has done";
  return 0;
}
