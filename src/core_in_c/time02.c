#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
	time_t current_time = time(NULL);
	if (current_time != (time_t)(-1)) {
		char buff[64];
		struct tm* tm = localtime(&current_time);
		if (strftime(buff, sizeof buff, "%A %c", tm)) {
			printf("The current local time is: %s", buff);
		}
	}

	return EXIT_SUCCESS;
}