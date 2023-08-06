#pragma once

#include "minicc/Condition.hh"
#include "minicc/Mutex.hh"
#include "minicc/Noncopyable.hh"

#include <cstddef>
#include <queue>

namespace minicc {

template <typename T> class BlockingQueue : Noncopyable {
public:
  BlockingQueue() : _mutex(), _cond(_mutex), _queue() {}
  // ~BlockingQueue();

  void push(const T &item) {
    {
      LockGuard lock(_mutex);
      _queue.push(item);
    }
    _cond.notify();
  }

  void push(T &&item) {
    {
      LockGuard lock(_mutex);
      _queue.push(std::move(item));
    }
    _cond.notify();
  }

  T pop() {
    LockGuard lock(_mutex);
    // _cond.wait([&] { return !_queue.empty(); });
    while (_queue.empty()) {
      _cond.wait();
    }
    T item(std::move(_queue.front()));
    _queue.pop();
    return item;
  }

  size_t size() {
    LockGuard lock(_mutex);
    return _queue.size();
  }

private:
  Mutex _mutex;
  Condition _cond;
  std::queue<T> _queue;
};
} // namespace minicc
