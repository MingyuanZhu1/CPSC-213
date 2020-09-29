#include <stdlib.h>
#include <stdio.h>
#include "uthread.h"
#include "uthread_mutex_cond.h"

uthread_t t0, t1, t2;
uthread_mutex_t mut_lock;
uthread_cond_t cond1, cond2;


void randomStall() {
  int i, r = random() >> 16;
  while (i++<r);
}

void* p0(void* v) {
  uthread_mutex_lock(mut_lock);
  randomStall();
  printf("zero\n");
  uthread_cond_signal(cond1);
  uthread_mutex_unlock(mut_lock);
  return NULL;
}

void* p1(void* v) {
  uthread_mutex_lock(mut_lock);

  while(uthread_self() != t1) {
    uthread_cond_wait(cond1);
  }

  randomStall();
  printf("one\n");
  uthread_cond_signal(cond2);
  uthread_mutex_unlock(mut_lock);
  return NULL;
}

void* p2(void* v) {
  uthread_mutex_lock(mut_lock);

  while (uthread_self() != t2) {
    uthread_cond_wait(cond2);
  }
  
  randomStall();
  printf("two\n");
  uthread_mutex_unlock(mut_lock);
}

int main(int arg, char** arv) {
  uthread_init(4);
  mut_lock = uthread_mutex_create();
  cond1 = uthread_cond_create(mut_lock);
  cond2 = uthread_cond_create(mut_lock);
  t0 = uthread_create(p0, NULL);
  t1 = uthread_create(p1, NULL);
  t2 = uthread_create(p2, NULL);
  randomStall();
  uthread_join (t0, NULL);
  uthread_join (t1, NULL);
  uthread_join (t2, NULL);
  printf("three\n");
  printf("------\n");
}
