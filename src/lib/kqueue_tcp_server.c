//
// Created by mason on 2022/10/30.
//
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/event.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
	int socket_listen_fd, port_no = 8988, client_len, socket_connection_fd, kq,
						  new_events;
	struct kevent change_event[4], event[4];
	struct sockaddr_in server_addr, client_addr;

	if (((socket_listen_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)) {
		perror("Error opening socket");
		exit(1);
	}

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_len = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(port_no);

	if (bind(socket_listen_fd, (struct sockaddr *)&server_addr,
			 sizeof(server_addr)) < 0) {
		perror("Error binding socket");
		exit(1);
	}

	listen(socket_listen_fd, 3);
	client_len = sizeof(client_addr);

	kq = kqueue();

	EV_SET(change_event, socket_listen_fd, EVFILT_READ, EV_ADD | EV_ENABLE, 0,
		   0, 0);

	if (kevent(kq, change_event, 1, NULL, 0, NULL) == -1) {
		perror("kevent");
		exit(1);
	}

	for (;;) {
		new_events = kevent(kq, NULL, 0, event, 1, NULL);
		if (new_events == -1) {
			perror("kevent");
			exit(1);
		}

		for (int i = 0; i < new_events; ++i) {
			printf("amount of new events:%d\n", new_events);
			int event_fd = event[i].ident;

			if (event[i].flags & EV_EOF) {
				printf("Client has disconnected\n");
				close(event_fd);
			} else if (event_fd == socket_listen_fd) {
				printf("New connection coming in...\n");

				socket_connection_fd =
					accept(event_fd, (struct sockaddr *)&client_addr,
						   (socklen_t *)&client_len);
				if (socket_connection_fd == -1) {
					perror("Accept socket error");
				}

				EV_SET(change_event, socket_connection_fd, EVFILT_READ, EV_ADD,
					   0, 0, NULL);
				if (kevent(kq, change_event, 1, NULL, 0, NULL) < 0) {
					perror("kevent error");
				}
			} else if (event[i].filter & EVFILT_READ) {
				char buf[1024];
				size_t bytes_read = recv(event_fd, buf, sizeof(buf), 0);
				printf("read %zu bytes\n", bytes_read);
			}
		}
	}

	return EXIT_SUCCESS;
}