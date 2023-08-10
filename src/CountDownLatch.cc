#include "minicc/CountDownLatch.hh"
#include "minicc/Mutex.hh"

namespace minicc {
CountDownLatch::CountDownLatch(int count)
    : _count(count), _mutex(), _cond(_mutex) {}

void CountDownLatch::wait() {
  LockGuard lock(_mutex);
  while (_count > 0) {
    _cond.wait();
  }
}

void CountDownLatch::countDown() {
  LockGuard lock(_mutex);
  if (--_count <= 0)
    _cond.notifyAll();
}

int CountDownLatch::getCount() {
  LockGuard lock(_mutex);
  return _count;
}

} // namespace minicc
