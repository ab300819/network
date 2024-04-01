//
// Created by mason on 2024/4/1.
//
#include <stdio.h> // 引入printf()函数所在的库
#include <stdlib.h> // 引入system()函数所在的库
#include <string.h> // 引入strcpy()函数所在的库
#include <event2/event.h>
#include <event2/listener.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include "common.h"

void rtrim(char *str) {
    int i;
    int len = strlen(str);

    // 从字符串的末尾开始向前遍历
    for (i = len - 1; i >= 0; i--) {
        if (str[i] == '\n' || str[i] == '\r') {
            str[i] = '\0'; // 将\r或\n替换为字符串终止符
        } else {
            // 一旦遇到非\r或\n字符，停止处理
            break;
        }
    }
}

char *substring(const char *source, int start, int length) {
    size_t sourceLength = strlen(source);
    if (start > sourceLength) {
        return NULL; // 起始位置超出源字符串长度
    }

    int maxLength = sourceLength - start; // 实际可截取的最大长度
    int subLength = length < maxLength ? length : maxLength;

    char *subStr = (char *) malloc(subLength + 1); // +1 for null terminator
    if (subStr == NULL) {
        return NULL; // 内存分配失败
    }

    strncpy(subStr, source + start, subLength);
    subStr[subLength] = '\0'; // 确保子字符串以null终止

    return subStr;
}

char *executeCmd(char *cmd) {
    FILE *fp;
    char *result = malloc(1);
    char buff[1024];
    if (result == NULL) {
        return NULL;
    }
    result[0] = '\0';

    rtrim(cmd);
    fp = popen(cmd, "r");
    if (fp == NULL) {
        printf("Failed to run command\n");
        free(result);
        return NULL;
    }

    while (fgets(buff, sizeof(buff), fp) != NULL) {
        size_t newLen = strlen(result) + strlen(buff);

        char *newResult = realloc(result, newLen);
        if (newResult == NULL) {
            free(result);
            return NULL;
        }

        result = newResult;
        strcat(result, buff);
    }

    if (pclose(fp) == -1) {
        printf("Command not found or exited with error status\n");
        free(result);
        return NULL;
    }

    return result;
}


void error_cb(struct bufferevent *bev, short error, void *ctx) {
    if (error & BEV_EVENT_EOF) {
        printf("Client close the connection.\n");
    } else if (error & BEV_EVENT_ERROR) {
        printf("Got an error on the connection: %s\n", strerror(errno));
    }
    buffer_free(bev);
}

void read_cb(struct bufferevent *bev, void *ctx) {
    struct evbuffer *input = bufferevent_get_input(bev);
    char buffer[1024];
    int n = evbuffer_remove(input, buffer, sizeof(buffer) - 1);
    if (n > 0) {
        buffer[n] = '\0';
        printf("Receive: %s", buffer);

        char *exec_result = executeCmd(buffer);
        if (exec_result == NULL) {
            exec_result = "Failed to run command\n";
        }
        bufferevent_write(bev, exec_result, strlen(exec_result));
    }
}

void accept_conn_cb(struct evconnlistener *listener,
                    evutil_socket_t fd,
                    struct sockaddr *address,
                    int socklen,
                    void *ctx) {
    struct event_base *base = evconnlistener_get_base(listener);
    struct bufferevent *bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);

    bufferevent_setcb(bev, read_cb, NULL, error_cb, NULL);
    bufferevent_enable(bev, EV_READ | EV_WRITE);
}


int main(int argc, char *argv[]) {
    struct sockaddr_in server_addr;

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(8090);

    struct event_base *base = event_base_new();
    struct evconnlistener *listener = evconnlistener_new_bind(base, accept_conn_cb,
                                                              NULL,
                                                              LEV_OPT_CLOSE_ON_FREE | LEV_OPT_REUSEABLE,
                                                              -1,
                                                              (struct sockaddr *) &server_addr,
                                                              sizeof(server_addr));
    if (!listener) {
        perror("Cannot create listener");
        return EXIT_FAILURE;
    }

    event_base_dispatch(base);

    evconnlistener_free(listener);
    event_base_free(base);

    return EXIT_SUCCESS;
}
