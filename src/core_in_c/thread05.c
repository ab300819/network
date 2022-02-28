#include <stdio.h>
#include <stdlib.h>
#include <threads.h>

mtx_t mutex;
cnd_t cond;
int done = 0;

int run(void* data) {
	mtx_lock(&mutex);
    done=1;
    cnd_signal(&cond);
    mtx_unlock(&mutex);
	return thrd_success;
}

int main(void) {
#ifndef __STDC_NO_THREADS__
	mtx_init(&mutex, mtx_plain);
	cnd_init(&cond);
	thrd_t thread;
	thrd_create(&thread, run, NULL);
	mtx_lock(&mutex);
	while (done == 0) {
		cnd_wait(&cond, &mutex);
	}
	mtx_unlock(&mutex);
	printf("The value of done is: %d", done);
	mtx_destroy(&mutex);
	cnd_destroy(&cond);
#endif

	return EXIT_SUCCESS;
}