#include "minicc/BlockingQueue.hh"
#include "minicc/CountDownLatch.hh"

#include <cstdio>
#include <iostream>
#include <string>
#include <thread>
#include <unistd.h>

using namespace minicc;
using namespace std;

const int kNrThreads = 10;
thread putThreads[kNrThreads];
CountDownLatch latch1(kNrThreads);
CountDownLatch latch2(1);

void work(int index) {
  printf("[thread %02d] ready\n", index);
  ::sleep(5);
  latch1.countDown();
  printf("[thread %02d] waiting\n", index);
  latch2.wait();
  printf("[thread %02d] done\n", index);
}

int main(int argc, char *argv[]) {

  for (int i = 0; i < kNrThreads; i++) {
    putThreads[i] = thread(work, i);
  }

  printf("main thread waiting...\n");
  latch1.wait();
  printf("main thread wait done.\n");
  ::sleep(5);
  latch2.countDown();

  for (auto &t : putThreads) {
    t.join();
  }

  return 0;
}
