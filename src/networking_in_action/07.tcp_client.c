#include "common.h"
#include <stdlib.h>
int main(int argc, char **argv) {
	if (argc != 2) {
		error(1, 0, "usage: unix stream client <local path>");
	}

	int sock_fd;
	struct sockaddr_un server_addr;

	sock_fd = socket(AF_LOCAL, SOCK_STREAM, 0);
	if (sock_fd < 0) {
		error(1, errno, "create socket");
	}

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sun_family = AF_LOCAL;
	strcpy(server_addr.sun_path, argv[1]);

	if (connect(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) <
		0) {
		error(1, errno, "connect failed");
	}

	char send_line[MAXLINE];
	memset(send_line, 0, MAXLINE);
	char recv_line[MAXLINE];

	while (fgets(send_line, MAXLINE, stdin) != NULL) {
		int n_bytes = sizeof(send_line);
		if (write(sock_fd, send_line, n_bytes) != n_bytes) {
			error(1, errno, "write error");
		}
		if (read(sock_fd, recv_line, MAXLINE) == 0) {
			error(1, errno, "server terminated prematurely");
		}
		fputs(recv_line, stdout);
	}

	return EXIT_SUCCESS;
}