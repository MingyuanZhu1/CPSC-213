#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/errno.h>
#include <assert.h>
#include "uthread.h"
#include "queue.h"
#include "disk.h"
//ct
queue_t pending_read_queue;

void interrupt_service_routine() {
  //void queue_dequeue (queue_t q, void **val, void **arg, void (**callback) (void*, void*));
  //queue_t pending_read_queue;
  void *val;
  void *arg;
  void (*callback)(void*, void*);

  queue_dequeue(pending_read_queue,&val,&arg,&callback);
  callback(val,arg);
}
volatile int status = 0;

void handleOtherReads (void *resultv, void *countv) {
  int *countTemp= countv;
  int *resultTemp = resultv;
  (*countTemp)--;

  if(*countTemp != 0) {
    // status = 0;
    queue_enqueue(pending_read_queue, resultTemp, countTemp, handleOtherReads);
    disk_schedule_read(resultTemp, *resultTemp);
  } else {
    status = 1;
  }
}

void handleFirstRead (void *resultv, void *countv) {
  int *resultTemp = resultv;
  int *countTemp = countv;
  *countTemp = *resultTemp;

  if(*countTemp != 0) {
    // status = 0;
    queue_enqueue(pending_read_queue, resultTemp, countTemp, handleOtherReads);
    disk_schedule_read(resultTemp, *resultTemp);
  } else {
    status = 1;
  }
}

int main(int argc, char **argv) {
  // Command Line Arguments
  static char* usage = "usage: treasureHunt starting_block_number";
  int starting_block_number;
  char *endptr;
  if (argc == 2)
    starting_block_number = strtol (argv [1], &endptr, 10);
  if (argc != 2 || *endptr != 0) {
    printf ("argument error - %s \n", usage);
    return EXIT_FAILURE;
  }

  // Initialize
  uthread_init (1);
  disk_start (interrupt_service_routine);
  pending_read_queue = queue_create();


  // Start the Hunt
  int a, b;
  // TODO
  queue_enqueue(pending_read_queue,&a,&b,handleFirstRead);
  disk_schedule_read(&a,starting_block_number);
  while (status != 1)
    ; // infinite loop so that main doesn't return before hunt completes
  printf("%d\n",a);
  return 0;
}

