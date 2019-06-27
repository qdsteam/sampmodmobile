#ifndef TIMERHPP
#define TIMERHPP
#include <chrono>
#include <functional>
class Timer {
public:
  Timer();
  void add(std::chrono::milliseconds delay,
           std::function<void ()> callback,
           bool asynchronous = true);
};
#endif