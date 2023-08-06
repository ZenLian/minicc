#include <iostream>
#include <thread>

#include "minicc/Mutex.hh"

using namespace minicc;

static const int kNrThreads = 10;
static const int kMaxCount = 10000;

static int count = 0;
static Mutex mtx;

static void thread_work(void) {
  for (int i = 0; i < kMaxCount; i++) {
    LockGuard lock(mtx);
    count++;
  }
}

int main(int argc, char *argv[]) {
  std::thread threads[kNrThreads];

  for (auto &t : threads) {
    t = std::thread(thread_work);
  }

  for (auto &t : threads) {
    t.join();
  }

  std::cout << "count = " << count << std::endl;

  return 0;
}
