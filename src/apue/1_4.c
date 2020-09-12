//
// Created by mason on 2018-12-19.
//

#include "apue.h"

#define BUFF_SIZE 4096

int main(int argc, char *argv[]) {

    int n;
    char buf[BUFF_SIZE];

    while ((n = read(STDIN_FILENO, buf, BUFF_SIZE)) > 0)
        if (write(STDOUT_FILENO, buf, n) != n)
            err_sys("write_error");

    if (n < 0)
        err_sys("read error");
    return 0;
}


