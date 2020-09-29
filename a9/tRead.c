#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <sys/errno.h>
#include <assert.h>
#include "queue.h"
#include "disk.h"
#include "uthread.h"

queue_t      pending_read_queue;
unsigned int sum = 0;

void interrupt_service_routine () {
  void *t;
  queue_dequeue(pending_read_queue, &t, NULL, NULL);
  uthread_unblock(t);
}

void *read_block (void *arg) {
  int* blockno = arg;
  int result;

  disk_schedule_read(&result, *blockno);
  queue_enqueue(pending_read_queue, uthread_self(), NULL, NULL);
  uthread_block();
  sum += result;
  return NULL;
}

int main (int argc, char** argv) {

  // Command Line Arguments
  static char* usage = "usage: tRead num_blocks";
  int num_blocks;
  char *endptr;
  if (argc == 2)
    num_blocks = strtol (argv [1], &endptr, 10);
  if (argc != 2 || *endptr != 0) {
    printf ("argument error - %s \n", usage);
    return EXIT_FAILURE;
  }

  // Initialize
  uthread_init (1);
  disk_start (interrupt_service_routine);
  pending_read_queue = queue_create();

  // Sum Blocks
    uthread_t threads[num_blocks];
    int blocknos[num_blocks];

    for (int i = 0; i < num_blocks; i++) {
        blocknos[i] = i;
        threads[i] = uthread_create(read_block, &blocknos[i]);
    }
    
    for (int j = 0; j < num_blocks; j++) {
        uthread_join(threads[j], NULL);
    }
    
    printf("%d\n", sum);
}

