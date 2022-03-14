#include <cassert>
#include <exception>
#include <iostream>
#include <new>
#include <string>
#include <list>
#include <deque>
#include <map>
#include <vector>

#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <pthread.h>

#include <openframe/openframe.h>

typedef openframe::ThreadQueue<char *> thread_q_t;
typedef openframe::Stopwatch stopwatch_t;

void *thread1_test(void *args) {
  thread_q_t *tc = static_cast<thread_q_t *>(args);

  for(int i=0; i < 1000000; i++) {
    std::cout << "Publishing" << std::endl;
    tc->enqueue(new char[5]);
//    sleep(10);
    usleep(5000);
  } // for

  return NULL;
} // thread1_test

void *thread2_test(void *args) {
  thread_q_t *tc = static_cast<thread_q_t *>(args);

  for(int i=0; i < 250000; i++) {
    stopwatch_t sw;
    sw.Start();
    char *c;
    std::cout << "tid2 Waiting to dequeue " << i << std::endl;
    bool ok = tc->dequeue_block(c);
    assert(ok);
    std::cout << "tid2 Dequeued " << ok << " after " << int(sw.Time() * 1000) << "ms" << std::endl;
  } // for

  return NULL;
} // thread2_test

void *thread3_test(void *args) {
  thread_q_t *tc = static_cast<thread_q_t *>(args);

  for(int i=0; i < 25000; i++) {
    stopwatch_t sw;
    sw.Start();
    char *c;
    std::cout << "tid3 Waiting to dequeue " << i << std::endl;
    bool ok = tc->dequeue_block(c);
    assert(ok);
    std::cout << "tid3 Dequeued " << ok << " after " << int(sw.Time() * 1000) << "ms" << std::endl;
  } // for

  return NULL;
} // thread3_test

void *thread4_test(void *args) {
  thread_q_t *tc = static_cast<thread_q_t *>(args);

  for(int i=0; i < 25000; i++) {
    stopwatch_t sw;
    sw.Start();
    char *c;
    std::cout << "tid4 Waiting to dequeue " << i << std::endl;
    bool ok = tc->dequeue_timed_block(c, 3);
    if (!ok) std::cout << "tid4 Timed out!" << std::endl;
    std::cout << "tid4 Dequeued " << ok << " after " << int(sw.Time() * 1000) << "ms" << std::endl;
  } // for

  return NULL;
} // thread3_test

int main(int argc, char **argv) {

  thread_q_t tq;

  openframe::Stopwatch sw;

  sw.Start();
  for(size_t i=0; i < 500000; i++) {
    char *c = new char[5];
    tq.push_back(c);
  } // for
  std::cout << "TQ Push Back " << std::fixed << sw.Time() << std::endl;

  sw.Start();
  for(size_t i=0; i < 500000; i++) {
    char *c = new char[5];
    tq.push_front(c);
  } // for
  std::cout << "TQ Push Front " << std::fixed << sw.Time() << std::endl;

  sw.Start();
  for(size_t i=0; i < 1024; i++) {
    size_t len = tq.size();
  } // for
  std::cout << "TQ " << std::fixed << sw.Time() << std::endl;

  sw.Start();
  while( !tq.empty() ) {
    char *c;
    if ( tq.dequeue(c) ) delete c;
  } // for
  std::cout << "TQ Dequeue " << std::fixed << sw.Time() << std::endl;

  pthread_t tid1, tid2, tid3, tid4;
  pthread_create(&tid1, NULL, thread1_test, &tq);
  pthread_create(&tid2, NULL, thread2_test, &tq);
  pthread_create(&tid3, NULL, thread3_test, &tq);
  pthread_create(&tid4, NULL, thread4_test, &tq);

  std::cout << "Joining thread 1" << std::endl;
  pthread_join(tid1, NULL);
  std::cout << "Joining thread 2" << std::endl;
  pthread_join(tid2, NULL);

  std::cout << "Joining thread 3" << std::endl;
  pthread_join(tid3, NULL);

  std::cout << "Joining thread 4" << std::endl;
  pthread_join(tid4, NULL);

  return 0;
} // main
