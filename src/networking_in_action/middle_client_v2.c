//
// Created by mason on 2024/3/30.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <event2/event.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <arpa/inet.h>
#include <unistd.h>

#define  MAX_LINE 1024

void read_cb(struct bufferevent *bev, void *ctx) {
    char recv_line[MAX_LINE];
    struct evbuffer *input = bufferevent_get_input(bev);
    while (evbuffer_get_length(input) > 0) {
        int n = evbuffer_remove(input, recv_line, sizeof(recv_line) - 1);
        if (n > 0) {
            recv_line[n] = '\0';
            printf("Receive: %s", recv_line);
        }
    }
}

void stdin_cb(evutil_socket_t fd, short event, void *ctx) {
    char send_line[MAX_LINE];
    struct bufferevent *bev = (struct bufferevent *) ctx;
    if (fgets(send_line, MAX_LINE, stdin) == NULL) {
        printf("End of input.\n");
        return;
    }
    bufferevent_write(bev, send_line, strlen(send_line));

}

void event_cb(struct bufferevent *bev, short events, void *ctx) {
    if (events & BEV_EVENT_CONNECTED) {
        printf("Connected to server.\n");
    } else if (events & (BEV_EVENT_ERROR | BEV_EVENT_EOF)) {
        if (events & BEV_EVENT_ERROR) {
            int err = bufferevent_socket_get_dns_error(bev);
            if (err) {
                printf("DNS error: %s\n", evutil_gai_strerror(err));
            }
        }
        bufferevent_free(bev);
        struct event_base *base = (struct event_base *) ctx;
        event_base_loopexit(base, NULL);
    }
}

int main(int argc, char *argv[]) {

    if (argc != 3) {
        printf("Usage: %s <ip> <port>\n", argv[0]);
        return EXIT_FAILURE;
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);

    struct event_base *base = event_base_new();
    struct bufferevent *bev = bufferevent_socket_new(base, -1, BEV_OPT_CLOSE_ON_FREE);

    bufferevent_setcb(bev, read_cb, NULL, event_cb, base);
    bufferevent_enable(bev, EV_READ | EV_WRITE);
    bufferevent_socket_connect(bev, (struct sockaddr *) &server_addr, sizeof(server_addr));

    struct event *ev_stdin = event_new(base, STDIN_FILENO, EV_READ | EV_PERSIST, stdin_cb, bev);

    event_add(ev_stdin, NULL);
    event_base_dispatch(base);
    event_free(ev_stdin);
    event_base_free(base);
    return EXIT_SUCCESS;
}
