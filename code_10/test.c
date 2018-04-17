#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <fcntl.h>
#include <unistd.h>
#include "uthread.h"
#include "uthread_mutex_cond.h"

uthread_mutex_t mx;
uthread_cond_t cond;

void a() {
	printf("a\n");
}

void b() {
	printf("b\n");
}
void c() {
	printf("c\n");
}
void d() {
	printf("d\n");
}
void thread1(void* v){
	a();
	uthread_mutex_lock(mx);
	b();
	uthread_cond_wait(cond);
	uthread_mutex_unlock(mx);
}

void thread2(void* v) {
	uthread_mutex_lock(mx);
	c();
	uthread_cond_signal(cond);
	d();
	uthread_mutex_unlock(mx);
}

int main(void) {
	mx = uthread_mutex_create();
	cond = uthread_cond_create(mx);
	uthread_join(uthread_create(thread1, 0), 0);
	uthread_join(uthread_create(thread2, 0), 0);
}