#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
	clock_t startTime = clock();
	for (int i = 0; i < 100000000; i++) {
	}
	clock_t endTime = clock();
	printf("Consumed CPU time is %fs\n",
		   (double)(endTime - startTime) / CLOCKS_PER_SEC);
	return EXIT_SUCCESS;
}