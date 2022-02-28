#include <stdio.h>
#include <stdlib.h>
#include <threads.h>

#define THREAD_COUNT 10
#define THREAD_LOOP 10000

_Thread_local int counter = 0;

int run(void *data) {
	for (int i = 0; i < THREAD_LOOP; i++) {
		counter += 1;
	}

	return counter;
}

int main(int argc, char const *argv[]) {
	thrd_t threads[THREAD_COUNT];
	int sum = 0, result = 0;
	for (int i = 0; i < THREAD_COUNT; ++i) {
		thrd_create(&threads[i], run, NULL);
	}

	for (int i = 0; i < THREAD_COUNT; ++i) {
		thrd_join(threads[i], &result);
		sum += result;
	}
	printf("The value of count is %d.\n", sum);
	return EXIT_SUCCESS;
}