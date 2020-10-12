#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>

void read_data(int);
size_t readn(int, void *, size_t);

int main(int argc, char const *argv[]) {
	int listenfd, connfd;
	socklen_t clilen;
	struct sockaddr_in cliaddr, servaddr;

	listenfd = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(12345);

	bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	listen(listenfd, 1024);

	for (;;) {
		clilen = sizeof(cliaddr);
		connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);
		read_data(connfd);
		close(connfd);
	}

	return EXIT_SUCCESS;
}

void read_data(int sockfd) {
	size_t n;
	char buf[1024];

	int time = 0;
	for (;;) {
		fprintf(stdout, "block in read\n");
		if ((n = readn(sockfd, buf, 2014)) == 0) return;

		time++;
		fprintf(stdout, "1k read for %d \n", time);
		usleep(1000);
	}
}

size_t readn(int fd, void *buffer, size_t size) {
	char *buffer_pointer = buffer;
	int length = size;

	while (length > 0) {
		int result = read(fd, buffer_pointer, length);
		if (result < 0) {
			if (errno == EINTR)
				continue;
			else
				return -1;
		} else if (result == 0) {
			break;
		}

		length -= result;
		buffer_pointer += result;
	}

	return size - length;
}