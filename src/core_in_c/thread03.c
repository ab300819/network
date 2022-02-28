#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <threads.h>

#define COUNT 10
#define LOOP 10000

mtx_t mutex;
long counter = 0;

int run(void* args) {
	for (int i = 0; i < LOOP; i++) {
		mtx_lock(&mutex);
		counter++;
		mtx_unlock(&mutex);
	}
	printf("Thread %d terminate.\n", *((int*)args));
    return thrd_success;
}

int main(void) {
#ifndef __STDC_NO_THREADS__
	int ids[COUNT];
	mtx_init(&mutex, mtx_plain);
	thrd_t threads[LOOP];

	for (int i = 0; i < COUNT; i++) {
		ids[i] = i + 1;
		thrd_create(&threads[i], run, ids + i);
	}

	for (int i = 0; i < COUNT; i++) {
		thrd_join(threads[i], NULL);
	}
	printf("Counter value is %ld.\n", counter);
	mtx_destroy(&mutex);
#endif
	return EXIT_SUCCESS;
}