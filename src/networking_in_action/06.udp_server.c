//
// Created by mason on 2022/4/23.
//
#include "common.h"

#include "utils.h"

static int count;

static void recvfrom_int(int signo) {
	printf("\nreceived %d datagrams\n", count);
	exit(0);
}

int main() {
	int socket_fd;
	socket_fd = socket(AF_INET, SOCK_DGRAM, 0);

	struct sockaddr_in server_addr;
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(SERV_PORT);

	bind(socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
	socklen_t client_len;
	char message[MAX_LINE];
	count = 0;

	signal(SIGINT, recvfrom_int);

	struct sockaddr_in client_addr;
	client_len = sizeof(client_addr);
	for (;;) {
		int n = recvfrom(socket_fd, message, MAX_LINE, 0,
						 (struct sockaddr *)&client_addr, &client_len);
		message[n] = 0;
		printf("received %d bytes: %s\n", n, message);

		char send_line[MAX_LINE];
		sprintf(send_line, "Hi, %s", message);

		sendto(socket_fd, send_line, strlen(send_line), 0,
			   (struct sockaddr *)&client_addr, client_len);
		count++;
	}

	return EXIT_SUCCESS;
}
