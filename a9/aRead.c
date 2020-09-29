#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <sys/errno.h>
#include <assert.h>
#include "queue.h"
#include "disk.h"
#include "uthread.h"
//ct
queue_t      pending_read_queue;
volatile unsigned int sum = 0;
// You may add your own variables here
volatile unsigned int counter = 0;

void interrupt_service_routine () {
  void* val;
  void (*callback)(void*,void*);
  queue_dequeue (pending_read_queue, &val, NULL, &callback);
  callback (val, NULL);
}

void handle_read (void* resultv, void* not_used) {
  // TODO add result to sum
  int *result = resultv;
  sum += *result;
  counter += 1;
}

int main (int argc, char** argv) {

  // Command Line Arguments
  static char* usage = "usage: aRead num_blocks";
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
  /* TODO: Read disk blocks */
  int *read = malloc(num_blocks * sizeof(int));
  int i = 0;
  //void queue_enqueue (queue_t q, void* val, void* arg,   void (*callback)  (void*, void*));

  /**
 * Schedule a disk read for block number blockno
 *    the integer contained in that block is copied into *resultBuf when the read completes
 */
  //void disk_schedule_read (int* resultBuf, int blockno);
  while (i<num_blocks) {
    queue_enqueue(pending_read_queue, &read[i], NULL, handle_read);
    disk_schedule_read(&read[i], i);
    i++;
  }

  //loop until everything has been read
  //when num of blocks == counter value 
  //that increments everytime a block is read

  while (counter != num_blocks) 
    ;
  /* TODO: Clean up as appropriate */
  free(read);
  printf("%d\n", sum);
  return 0;
}
