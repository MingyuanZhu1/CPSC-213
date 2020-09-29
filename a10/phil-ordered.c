#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <time.h>
#include "uthread.h"
#include "uthread_mutex_cond.h"

#define MAX_THINKING_TIME 25000

#ifdef VERBOSE
#define VERBOSE_PRINT(S, ...) printf (S, ##__VA_ARGS__)
#else
#define VERBOSE_PRINT(S, ...) ((void) 0) // do nothing
#endif

typedef struct fork {
  uthread_mutex_t lock;
  uthread_cond_t forfree;
  long free;
} fork_t;

int num_phils, num_meals;    
fork_t *forks;

void deep_thoughts() {
  usleep(random() % MAX_THINKING_TIME);
}

void initfork(int i) {
  forks[i].lock    = uthread_mutex_create();
  forks[i].forfree = uthread_cond_create(forks[i].lock);
  forks[i].free    = 1;
}

long getfork(long i) {
  // lock critical session
  uthread_mutex_lock(forks[i].lock);
  // check cond
  while(!forks[i].free){
    uthread_cond_wait(forks[i].forfree);
  }
  // change forks[i].free to 0
  forks[i].free = 0;
  // unlock
  uthread_mutex_unlock(forks[i].lock);
  return 1;
}

void putfork(long i) {
  // start with locking critical session
  uthread_mutex_lock(forks[i].lock);
  forks[i].free = 1;
  uthread_cond_signal(forks[i].forfree);
  // unlock critical session
  uthread_mutex_unlock(forks[i].lock);  
}

int leftfork(long i) {
  return i;
}

int rightfork(long i) {
  return (i + 1) % num_phils;
}

void *phil_thread(void *arg) {
  long id = *(long*) arg;
  int meals = 0;
  if(rightfork(id) < leftfork(id)){
    while (meals < num_meals) {
    // initial deep thought before getting any fork
    deep_thoughts();

    getfork(rightfork(id));
    printf("pick right fork.\n");
    // deep thoughts after getting the rightfork
    deep_thoughts();

    getfork(leftfork(id));
    printf("pick left fork.\n");
    // deep thoughts after getting the leftfork
    deep_thoughts();
    meals++;            
    printf("eat one time.\n");
    //put down both forks
    putfork(rightfork(id));
    putfork(leftfork(id));
    printf("drop both forks.\n");
    // deep thoughts after dropped both fork
    deep_thoughts();
    printf("done.\n");
  }

  } else {
    while (meals < num_meals) {
    // initial deep thought before getting any fork
    deep_thoughts();
    getfork(leftfork(id));
    printf("pick right fork.\n");
    // deep thoughts after getting the rightfork
    deep_thoughts();
    getfork(rightfork(id));
    printf("pick left fork.\n");
    // deep thoughts after getting the leftfork
    deep_thoughts();
    meals++;            
    printf("eat one time.\n");
    //put down both forks
    putfork(rightfork(id));
    putfork(leftfork(id));
    //deep thoughts after dropped both fork
    printf("drop both forks.\n");
    deep_thoughts();
    printf("done.\n");
  }
}
  return 0;
}

int main(int argc, char **argv) {
  uthread_t *p;
  uintptr_t i;
  
  if (argc != 3) {
    fprintf(stderr, "Usage: %s num_philosophers num_meals\n", argv[0]);
    return 1;
  }

  num_phils = strtol(argv[1], 0, 0);
  num_meals = strtol(argv[2], 0, 0);
  
  forks = malloc(num_phils * sizeof(fork_t));
  p = malloc(num_phils * sizeof(uthread_t));
  uthread_init(num_phils);
  srandom(time(0));
  for (i = 0; i < num_phils; ++i) {
    initfork(i);
  }

  /* TODO: Create num_phils threads, all calling phil_thread with a
   * different ID, and join all threads.
   */
    
    int list_of_phils[num_phils];
  // create threads
   for (i = 0; i < num_phils; i++) {
     list_of_phils[i] = i;
     p[i] = uthread_create(phil_thread, &list_of_phils[i]);
  }

  // join all threads
  for(int i = 0; i < num_phils; i++){
    uthread_join(p[i], NULL);
  }
  return 0;
}
