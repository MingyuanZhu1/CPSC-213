#include <stdlib.h>
#include <stdio.h>
#include "uthread.h"
#include "uthread_mutex_cond.h"

#define NUM_THREADS 3
uthread_t threads[NUM_THREADS];
uthread_mutex_t mut_lock;
uthread_cond_t cond;

void randomStall() {
  int i, r = random() >> 16;
  while (i++<r);
}

void waitForAllOtherThreads() {
    if(uthread_self() == threads[NUM_THREADS-1]) {
    uthread_cond_broadcast(cond);
  } else {
    uthread_cond_wait(cond);
  }
}

void* p(void* v) {
  uthread_mutex_lock(mut_lock);
  randomStall();
  printf("a\n");
  waitForAllOtherThreads();
  printf("b\n");
  uthread_mutex_unlock(mut_lock);
  return NULL;
}

int main(int arg, char** arv) {
  uthread_init(4);
  mut_lock = uthread_mutex_create();
  cond = uthread_cond_create (mut_lock);
  for (int i=0; i<NUM_THREADS; i++)
    threads[i] = uthread_create(p, &mut_lock);
  for (int i=0; i<NUM_THREADS; i++)
    uthread_join (threads[i], NULL);
  printf("------\n");
}