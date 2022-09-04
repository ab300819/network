#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

#define MESSAGE_SIZE 102400

void send_data(int);

int main(int argc, char const *argv[]) {
	int sock_fd;
	struct sockaddr_in serv_addr;

	if (argc != 2) fprintf(stdout, "usage: client <IPaddress>");

	sock_fd = socket(AF_INET, SOCK_STREAM, 0);

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(12345);
	inet_pton(AF_INET, argv[1], &serv_addr.sin_addr);
	int connect_rt =
		connect(sock_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	if (connect_rt < 0) {
		fprintf(stdout, "connect failed ");
	}

	send_data(sock_fd);

	return EXIT_SUCCESS;
}

void send_data(int sock_fd) {
	char *query;
	query = malloc(MESSAGE_SIZE + 1);
	for (int i = 0; i < MESSAGE_SIZE; i++) {
		query[i] = 'a';
	}
	query[MESSAGE_SIZE] = '\0';

	const char *cp;
	cp = query;
	size_t remaining = strlen(query);
	while (remaining) {
		ssize_t n_written = send(sock_fd, cp, remaining, 0);
		fprintf(stdout, "send into buffer %zd \n", n_written);
		if (n_written <= 0) {
			fprintf(stdout, "send failed");
			return;
		}
		remaining -= n_written;
		cp += n_written;
	}
}
