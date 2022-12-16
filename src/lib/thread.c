//
// Created by mengshen on 2022/7/29.
//
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define THREAD_NUM 5

// https://hanbingyan.github.io/2016/03/07/pthread_on_linux/#%E7%BA%BF%E7%A8%8B%E7%9A%84%E5%88%9B%E5%BB%BA%E5%92%8C%E7%AE%A1%E7%90%86

void *printHello(void *thread_id) {
  long tid;
  tid = (long)thread_id;
  printf("Hello World! It's me, thread #%ld!\n", tid);
  pthread_exit(NULL);
}

int main() {
  pthread_t threads[THREAD_NUM];
  int rc;
  long t;
  for (t = 0; t < THREAD_NUM; ++t) {
    printf("In main: create thread %d\n", t);
    rc = pthread_create(&threads[t], NULL, printHello, (void *)t);
    if (rc) {
      printf("ERROR; return code from pthread_create() is %d\n", rc);
      exit(-1);
    }
  }

  pthread_exit(NULL);
}