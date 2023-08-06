#pragma once

#include "minicc/Mutex.hh"
#include "minicc/Noncopyable.hh"
#include <pthread.h>

namespace minicc {
class Condition : Noncopyable {
public:
  Condition(Mutex &mutex) : _mutex(mutex) { pthread_cond_init(&_cond, NULL); }
  ~Condition() { pthread_cond_destroy(&_cond); }

  void wait() { pthread_cond_wait(&_cond, _mutex.getRawMutex()); }

  template <typename Predicate> void wait(Predicate p) {
    while (!p()) {
      wait();
    }
  }

  void notify() { pthread_cond_signal(&_cond); }
  void notifyAll() { pthread_cond_broadcast(&_cond); }

private:
  pthread_cond_t _cond;
  Mutex &_mutex;
};
} // namespace minicc
