#include <lib/common.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	if (argc != 2) {
		error(1, 0, "usage: unix data server <local path>");
	}

	int socket_fd = socket(AF_LOCAL, SOCK_DGRAM, 0);
	if (socket_fd < 0) {
		error(1, errno, "socket create failed");
	}

	struct sockaddr_un server_addr;
	char *local_path = argv[1];
	unlink(local_path);
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sun_family = AF_LOCAL;
	strcpy(server_addr.sun_path, local_path);

	if (bind(socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) <
		0) {
		error(1, errno, "bind failed");
	}

	char buf[BUFFER_SIZE];
	struct sockaddr_un client_addr;
	socklen_t client_len = sizeof(client_addr);
	while (TRUE) {
		memset(buf, 0, sizeof(buf));
		if (recvfrom(socket_fd, buf, BUFFER_SIZE, 0,
					 (struct sockaddr *)&client_addr, &client_len) == 0) {
			printf("client quit");
			break;
		}
		printf("receive: %s \n", buf);

		char send_line[MAXLINE];
		memset(send_line, 0, MAXLINE);
		sprintf(send_line, "Hi, %s", buf);

		size_t n_bytes = strlen(send_line);
		printf("now sending: %s \n", send_line);
		if (sendto(socket_fd, send_line, n_bytes, 0,
				   (struct sockaddr *)&client_addr, client_len) != n_bytes) {
			error(1, errno, "sendto error");
		}
	}
	close(socket_fd);
	return EXIT_SUCCESS;
}