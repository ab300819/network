#include "common.h"
#include <stdlib.h>
int main(int argc, char **argv) {
	if (argc != 2) {
		error(1, 0, "usage: 07.tcp_server <local unix_socket path>");
	}

	int listen_fd, connect_fd;
	socklen_t client_len;
	struct sockaddr_un client_addr, server_addr;

	listen_fd = socket(AF_LOCAL, SOCK_STREAM, 0);
	if (listen_fd < 0) {
		error(1, errno, "socket create failed");
	}

	char *local_path = argv[1];
	unlink(local_path);
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sun_family = AF_LOCAL;
	strcpy(server_addr.sun_path, local_path);

	if (bind(listen_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) <
		0) {
		error(1, errno, "listen failed");
	}

	if (listen(listen_fd, LISTENQ) < 0) {
		error(1, errno, "listen failed");
	}

	client_len = sizeof(client_addr);
	if ((connect_fd = accept(listen_fd, (struct sockaddr *)&client_addr,
							 &client_len)) < 0) {
		if (errno == EINTR) {
			error(1, errno, "accept failed");
		} else {
			error(1, errno, "accept failed");
		}
	}

	char buf[BUFFER_SIZE];

	while (1) {
		memset(buf, 0, sizeof(buf));
		if (read(connect_fd, buf, BUFFER_SIZE) == 0) {
			printf("client quit");
			break;
		}
		printf("receive: %s", buf);

		char sen_line[MAXLINE];
		sprintf(sen_line, "Hi, %s", buf);

		int n_bytes = sizeof(sen_line);

		if (write(connect_fd, sen_line, n_bytes) != n_bytes) {
			error(1, errno, "write error");
		}
	}

	close(listen_fd);
	close(connect_fd);
	return EXIT_SUCCESS;
}