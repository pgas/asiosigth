#ifndef EVENT_APPLICATION_H
#define EVENT_APPLICATION_H

#include <memory>

#include <boost/asio.hpp>

class SignalHandlerThread;

class EventApplication {

public:
  EventApplication();
  ~EventApplication();

  EventApplication(const EventApplication &) = delete;
  EventApplication &operator=(const EventApplication &) = delete;

  const boost::asio::io_context &getContext();
  int run();

private:
  boost::asio::io_context context_;
  boost::asio::signal_set signals_;
  std::unique_ptr<SignalHandlerThread> signalHandler_;
};

#endif