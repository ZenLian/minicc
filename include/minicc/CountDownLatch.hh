#pragma once

#include "minicc/Condition.hh"
#include "minicc/Mutex.hh"
#include "minicc/Noncopyable.hh"

namespace minicc {

class CountDownLatch : Noncopyable {
public:
  explicit CountDownLatch(int count);
  void wait();
  void countDown();
  int getCount();

private:
  int _count;
  Mutex _mutex;
  Condition _cond;
};

} // namespace minicc
