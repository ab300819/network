#include <lib/common.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	if (argc != 2) {
		error(1, 0, "usage: unix data client <local path>");
	}

	int sock_fd = socket(AF_LOCAL, SOCK_DGRAM, 0);
	struct sockaddr_un client_addr, server_addr;
	if (sock_fd < 0) {
		error(1, errno, "create socket failed");
	}

	memset(&client_addr, 0, sizeof(client_addr));
	client_addr.sun_family = AF_LOCAL;
	strcpy(client_addr.sun_path, tmpnam(NULL));

	if (bind(sock_fd, (struct sockaddr *)&client_addr, sizeof(client_addr)) <
		0) {
		error(1, errno, "bind failed");
	}

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sun_family = AF_LOCAL;
	strcpy(server_addr.sun_path, argv[1]);

	char send_line[MAXLINE];
	memset(send_line, 0, MAXLINE);
	char recv_line[MAXLINE];

	while (fgets(send_line, MAXLINE, stdin) != NULL) {
		int i = strlen(send_line);
		if (send_line[i - 1] == '\n') {
			send_line[i - 1] = 0;
		}
		size_t n_bytes = strlen(send_line);
		printf("now sending %s \n", send_line);

		if (sendto(sock_fd, send_line, n_bytes, 0,
				   (struct sockaddr *)&server_addr,
				   sizeof(server_addr)) != n_bytes) {
			error(1, errno, "sendto error");
		}

		int n = recvfrom(sock_fd, recv_line, MAXLINE, 0, NULL, NULL);
		recv_line[n] = 0;

		fputs(recv_line, stdout);
		fputs("\n", stdout);
	}

	return EXIT_SUCCESS;
}