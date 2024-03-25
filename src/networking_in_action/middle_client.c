#include "common.h"

#define  MAX_LINE 1024

int main(int argc, char **argv) {
    int sock_fd = tcp_client("127.0.0.1", 8090);

    char recv_line[MAX_LINE], send_line[MAX_LINE];
    memset(send_line, 0, MAX_LINE);

    while (fgets(send_line, MAXLINE, stdin) != NULL) {
        int n_bytes = sizeof(send_line);
        if (write(sock_fd, send_line, n_bytes) != n_bytes) {
            error(1, errno, "write error");
        }
        if (read(sock_fd, recv_line, MAX_LINE) == 0) {
            error(1, errno, "server terminated prematurely");
        }
        fputs(recv_line, stdout);
    }

    return EXIT_SUCCESS;
}
