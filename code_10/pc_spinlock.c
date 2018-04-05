#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "uthread.h"
#include "uthread_mutex_cond.h"
#include "spinlock.h"

#define MAX_ITEMS 10
const int NUM_ITERATIONS = 200;
const int NUM_CONSUMERS  = 2;
const int NUM_PRODUCERS  = 2;

int producer_wait_count;     // # of times producer had to wait
int consumer_wait_count;     // # of times consumer had to wait
int histogram [MAX_ITEMS+1]; // histogram [i] == # of times list stored i items

int items = 0;

spinlock_t t1;
spinlock_t t2;
spinlock_t t3;

void* producer (void* v) {
	for (int i = 0; i < NUM_ITERATIONS; i++) {
		while (1) {
			while (items >= MAX_ITEMS) {
				spinlock_lock(&t2);
				producer_wait_count++;
				spinlock_unlock(&t2);
			}
			spinlock_lock(&t1);
			if (items < MAX_ITEMS) {
				break;
			}
			spinlock_unlock(&t1);
		}
		items++;
		histogram[items]++;
		spinlock_unlock(&t1);
	}
  return NULL;
}

void* consumer (void* v) {
	for (int i = 0; i < NUM_ITERATIONS; i++) {
		while (1) {
			while (items <= 0) {
				spinlock_lock(&t3);
				consumer_wait_count++;
				spinlock_unlock(&t3);
			}
			spinlock_lock(&t1);
			if (items > 0) {
				break;
			}
			spinlock_unlock(&t1);
		}
		items--;
		histogram[items]++;
		spinlock_unlock(&t1);
	}
  return NULL;
}

int main (int argc, char** argv) {
  uthread_t t[4];

  uthread_init (4);
  
  spinlock_create(&t1);
  spinlock_create(&t2);
  spinlock_create(&t3);

  t[0] = uthread_create(producer, 0);
  t[1] = uthread_create(producer, 0);
  t[2] = uthread_create(consumer, 0);
  t[3] = uthread_create(consumer, 0);

  uthread_join(t[0], 0);
  uthread_join(t[1], 0);
  uthread_join(t[2], 0);
  uthread_join(t[3], 0);

  printf ("producer_wait_count=%d\nconsumer_wait_count=%d\n", producer_wait_count, consumer_wait_count);
  printf ("items value histogram:\n");
  int sum=0;
  for (int i = 0; i <= MAX_ITEMS; i++) {
    printf ("  items=%d, %d times\n", i, histogram [i]);
    sum += histogram [i];
  }
  assert (sum == sizeof (t) / sizeof (uthread_t) * NUM_ITERATIONS);
}
