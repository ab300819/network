//
// Created by 孟伸 on 2020/9/16.

//

#include <errno.h>

#include "apue.h"

int main(int argc, char *argv[]) {
	fprintf(stderr, "EACCES: %s\n", strerror(EACCES));

	errno = EACCES;
	perror(argv[0]);
	return EXIT_SUCCESS;
}