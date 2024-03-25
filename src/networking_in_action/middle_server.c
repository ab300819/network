//
// Created by mason on 2024/3/23.
//
#include <stdio.h> // 引入printf()函数所在的库
#include <stdlib.h> // 引入system()函数所在的库
#include <string.h> // 引入strcpy()函数所在的库
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

void read_and_response_data(int sock_fd) {
    char buffer[1024];
    size_t bytes_read = read(sock_fd, buffer, sizeof(buffer) - 1);
    if (bytes_read < 0) {
        error(1, errno, "read failed");
    }

    buffer[bytes_read] = '\0'; // 确保字符串以null终止
    printf("Received: %s\n", buffer); // 打印接收到的数据

    char *execResult = executeCmd(substring(buffer, 0, bytes_read));

    if (execResult == NULL) {
        execResult = "Failed to run command\n"; // 向客户端发送响应
    }
    write(sock_fd, execResult, strlen(execResult)); // 向客户端发送响应
}

int main(int argc, char **argv) {
//    if (argc != 2) {
//        error(1, 0, "usage: middle_server <local unix_socket path>");
//    }

    int listen_fd;
    int connect_fd;

    socklen_t client_len;
    struct sockaddr_in client_addr;
    struct sockaddr_in server_addr;

    listen_fd = socket(AF_INET, SOCK_STREAM, 0);

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(8090);

    bind(listen_fd, (struct sockaddr *) &server_addr, sizeof(server_addr));
    listen(listen_fd, 1024);
    for (;;) {
        client_len = sizeof(client_addr);
        connect_fd = accept(listen_fd, (struct sockaddr *) &client_addr, &client_len);
        for (;;) {
            read_and_response_data(connect_fd);
        }
    }

    return EXIT_SUCCESS;
}
