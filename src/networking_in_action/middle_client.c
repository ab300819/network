#include "common.h"

#define  MAX_LINE 1024

int main(int argc, char **argv) {
    int sock_fd = tcp_client("127.0.0.1", 8090);

    char recv_line[MAX_LINE], send_line[MAX_LINE];
    memset(send_line, 0, MAX_LINE);

    fd_set read_fd;
    FD_ZERO(&read_fd);
    int max_fdp = sock_fd + 1;

    for (;;) {
        FD_SET(fileno(stdin), &read_fd);
        FD_SET(sock_fd, &read_fd);

        if (select(max_fdp, &read_fd, NULL, NULL, NULL) == -1) {
            perror("select error");
            exit(1);
        }

        if (FD_ISSET(sock_fd, &read_fd)) { // socket is readable
            int n = read(sock_fd, recv_line, MAXLINE);
            if (n < 0) {
                perror("read error");
                exit(1);
            } else if (n == 0) { // server closed connection
                printf("Server closed the connection.\n");
                exit(0);
            }
            recv_line[n] = 0; // null terminate
            fputs(recv_line, stdout);
        }

        if (FD_ISSET(fileno(stdin), &read_fd)) { // input is readable
            if (fgets(send_line, MAXLINE, stdin) == NULL) break; // EOF
            if (send(sock_fd, send_line, strlen(send_line), 0) < 0) {
                perror("send error");
                exit(1);
            }
        }
    }

    close(sock_fd);
    return EXIT_SUCCESS;
}
