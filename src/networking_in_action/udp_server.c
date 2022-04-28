//
// Created by mason on 2022/4/23.
//
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/socket.h>

#define MAXLINE 4096

static int count;

int main() {
	int socket_fd;
	socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
	struct sockaddr_in server_addr;
	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htonl(6321);

	bind(socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
	socklen_t client_len;
	char message[MAXLINE];
	count = 0;

	signal(SIGINT, recvfrom);

	struct sockaddr_in client_addr;
	client_len = sizeof(client_addr);
	for (;;) {
		int n = recvfrom(socket_fd, message, MAXLINE, 0,
						 (struct sockaddr *)&client_addr, &client_len);
		message[n] = 0;
		printf("received %d bytes:%s\n", n, message);

		char send_line[MAXLINE];
		sprintf(send_line, "Hi, %s", message);

		sendto(socket_fd, send_line, strlen(send_line), 0,
			   (struct sockaddr *)&client_addr, client_len);
		count++;
	}

	return EXIT_SUCCESS;
}
