#include "EventApplication.h"

#include <future>
#include <iostream>
#include <thread>
#include <vector>

#include <signal.h>

class SignalHandlerThread {

public:
  SignalHandlerThread(sigset_t *oset) {
    std::thread([=]() {
      // restore the original mask in the handler thread
      if (pthread_sigmask(SIG_SETMASK, oset, nullptr) != 0) {
        std::cerr << "Failed to set sigmask" << std::endl;
      }
      // just wait until this and stop are destroyed
      stop_.get_future().wait();
    }).detach();
  }

  SignalHandlerThread(const SignalHandlerThread &) = delete;
  SignalHandlerThread &operator=(const SignalHandlerThread &) = delete;

private:
  std::promise<void> stop_;
};

EventApplication::EventApplication() : signals_(context_) {
  // list of signal handled by the application
  const std::vector<int> event_application_signals{SIGINT, SIGTERM};

  // Block signals for present and future threads
  sigset_t set;
  sigset_t oset;
  sigemptyset(&set);
  for (const int si : event_application_signals) {
    sigaddset(&set, si);
  }

  if (pthread_sigmask(SIG_BLOCK, &set, &oset) != 0) {
    std::cerr << "Failed to set sigmask" << std::endl;
  }

  // exit the loop if a signal is received
  for (const int si : event_application_signals) {
    signals_.add(si);
  }
  signals_.async_wait(
      [this](const boost::system::error_code &, int) { context_.stop(); });

  // start the thread that will handle the signals
  signalHandler_ = std::make_unique<SignalHandlerThread>(&oset);
}

EventApplication::~EventApplication() {}

const boost::asio::io_context &EventApplication::getContext() {
  return context_;
}

int EventApplication::run() {
  context_.run();
  return 0;
}