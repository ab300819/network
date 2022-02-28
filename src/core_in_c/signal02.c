#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
	signal(SIGTERM, SIG_IGN);
	raise(SIGTERM);
	printf("Reachable!\n");
	return EXIT_SUCCESS;
}