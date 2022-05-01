//
// Created by mason on 2022/4/30.
//
#include "utils.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
void error(int status, int err, char *fmt, ...) {
	va_list ap;
	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	va_end(ap);
	if (err) {
		fprintf(stderr, ": %s (%d)\n", strerror(err), err);
	}

	if (status) {
		exit(status);
	}
}