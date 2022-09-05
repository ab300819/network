#include <lib/common.h>

void read_data(int);

int main(int argc, char const *argv[]) {
	int listen_fd, conn_fd;
	socklen_t clilen;
	struct sockaddr_in cli_addr, serv_addr;

	listen_fd = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(12345);

	bind(listen_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	listen(listen_fd, 1024);

	for (;;) {
		clilen = sizeof(cli_addr);
		conn_fd = accept(listen_fd, (struct sockaddr *)&cli_addr, &clilen);
		read_data(conn_fd);
		close(conn_fd);
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