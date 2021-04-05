//#include <boost/asio.hpp>

#include <iostream>

#include "EventApplication.h"

int main() {
  EventApplication app;
  std::cout << "Starting loop" << std::endl;
  app.run();
  std::cout << "loop stopped" << std::endl;
  return 0;
}