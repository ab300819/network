//
// Created by mason on 2022/3/26.
//
#pragma once
#ifndef UNIX_PROGRAMMING_LIBS_STRUCTS_H_
#define UNIX_PROGRAMMING_LIBS_STRUCTS_H_

#include <sys/socket.h>
typedef struct sockaddr_in sockaddr_in;
typedef struct sockaddr sockaddr;

typedef struct {
	int thread_count;
} serverSettings;

typedef struct {
	int serverFd;
	sockaddr* addr;
	socklen_t* addrLen;
} acceptParams;

#endif	// UNIX_PROGRAMMING_LIBS_STRUCTS_H_
