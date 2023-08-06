#include "minicc/BlockingQueue.hh"

#include <cstdio>
#include <iostream>
#include <string>
#include <thread>

using namespace minicc;
using namespace std;

const int kNrThreads = 10;

thread takeThread;
thread putThreads[kNrThreads];
BlockingQueue<string> blkQ;

void take() {
  while (true) {
    string s = blkQ.pop();
    cout << s << endl;
  }
}

void put(int index) {
  for (int i = 0; i < 10; i++) {
    char buf[128];
    snprintf(buf, 128, "[thread %02d] %d", index, i);
    blkQ.push(string(buf));
  }
}

int main(int argc, char *argv[]) {
  takeThread = thread(take);
  for (int i = 0; i < kNrThreads; i++) {
    putThreads[i] = thread(put, i);
  }

  for (auto &t : putThreads) {
    t.join();
  }

  takeThread.join();

  return 0;
}
