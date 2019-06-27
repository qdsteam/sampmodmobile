#include "timer.hpp"
#include <thread>

Timer::Timer() {
}
void Timer::add(std::chrono::milliseconds delay,
                std::function<void()> callback,
                bool asynchronous) {
  if (asynchronous) {
    std::thread([=]() {
      std::this_thread::sleep_for(std::chrono::milliseconds(delay));
      callback();
    }).detach();
  }
  else {
    std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    callback();
  }
}

  // USING:       Timer timer;
  // USING:       timer.add(std::chrono::milliseconds(1000), bar, true);
  // USING:       timer.add(std::chrono::milliseconds(500), foo);
  // USING:       timer.add(std::chrono::milliseconds(2000), []{}, false);