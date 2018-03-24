#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/errno.h>
#include <assert.h>
#include "uthread.h"
#include "queue.h"
#include "disk.h"

queue_t pending_read_queue;

void interrupt_service_routine() {
	void* val;
	void* val2;
	void(*callback)(void*, void*);
	queue_dequeue(pending_read_queue, &val, &val2, &callback);
	callback(val, val2);
}

void handleOtherReads (void* resultv, void* countv) {
	int* next = (int*)resultv;
	int* count = (int*)countv;
	if (*count <= 1) {
		printf("%d\n", *next);
		exit(EXIT_SUCCESS);
	}
	*count = *count - 1;
	printf("The result is %d\n", *next);
	printf("The current count is %d\n", *count);
	printf("The blockno is %d ", *next);
	queue_enqueue(pending_read_queue, next, count, handleOtherReads);
	disk_schedule_read(next, *next);
}

void handleFirstRead (void* resultv, void* countv) {
	int* num_blocks = (int*)resultv;
	int* start = (int*)countv;
	*start = *num_blocks;
	printf("The first result is %d\n", *num_blocks);
	printf("%d\n", *start);
	queue_enqueue(pending_read_queue, num_blocks, start, handleOtherReads);
	disk_schedule_read(num_blocks, *num_blocks);
}

int main (int argc, char** argv) {
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
  int next_block;
  int i;
  queue_enqueue(pending_read_queue, &next_block, &i, handleFirstRead);
  disk_schedule_read(&next_block, starting_block_number);
  while (1); // inifinite loop so that main doesn't return before hunt completes
}
