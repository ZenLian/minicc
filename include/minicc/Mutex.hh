#pragma once

#include "minicc/Noncopyable.hh"
#include <pthread.h>

namespace minicc {

class Mutex : Noncopyable {
public:
  Mutex() { pthread_mutex_init(&_mutex, NULL); }
  ~Mutex() { pthread_mutex_destroy(&_mutex); }
  void lock() { pthread_mutex_lock(&_mutex); }
  void unlock() { pthread_mutex_unlock(&_mutex); }
  pthread_mutex_t *getRawMutex() { return &_mutex; }

private:
  pthread_mutex_t _mutex;
};

class LockGuard : Noncopyable {
public:
  explicit LockGuard(Mutex &mutex) : _mutex(mutex) { _mutex.lock(); }
  ~LockGuard() { _mutex.unlock(); }

private:
  Mutex &_mutex;
};

} // namespace minicc

#define LockGuard(x) error "missing object name"
