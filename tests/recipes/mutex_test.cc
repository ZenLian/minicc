#include <iostream>
#include <mutex>
#include <thread>

static const int kNrThreads = 10;
static const int kMaxCount = 10000;

static int count = 0;
static std::mutex mtx;

static void thread_work(void) {
  for (int i = 0; i < kMaxCount; i++) {
    std::lock_guard<std::mutex> lock(mtx);
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
