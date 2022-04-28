//
// Created by mason on 2022/3/27.
//
#include <netinet/in.h>
#include <pthread.h>
#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h>
#include <string.h>
#include <unistd.h>

#include "libs/helpers.h"
#include "libs/macros.h"
#include "libs/structs.h"

atomic_int thread_count = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void renew_thread(void* arg) {
	int* acceptedSocket = (int*)arg;
	close(*acceptedSocket);
	pthread_mutex_lock(&mutex);
	thread_count--;
	pthread_cond_signal(&cond);
	pthread_mutex_unlock(&mutex);
}

noreturn void* accept_conn(void* arg) {
	acceptParams* ap = (acceptParams*)arg;
	int acceptedSocket;

	while (1) {
		pthread_cleanup_push(renew_thread, &acceptedSocket);

		if ((acceptedSocket = accept(ap->serverFd, ap->addr, ap->addrLen)) <
			0) {
			perror("In accept");
			pthread_exit(NULL);
		}

		char reqBuf[HTTP_REQ_BUF];
		bzero(reqBuf, HTTP_REQ_BUF);

		const size_t receivedBytes = read(acceptedSocket, reqBuf, HTTP_REQ_BUF);
		if (receivedBytes > 0) {
			char resBuf[HTTP_RES_BUF];

			pthread_mutex_lock(&mutex);
			const int num = retrieveGETQueryIntValByKey(reqBuf, "num");
			pthread_mutex_unlock(&mutex);

			int fibResult = calcFibonacci(num);
			sprintf(resBuf,
					"HTTP/1.1 200 OK\r\n"
					"Content-type: text/plain\r\n"
					"Content-length: %d\r\n\r\n%d",
					calcDigits(fibResult), fibResult);
			write(acceptedSocket, resBuf, strlen(resBuf));
		}
		close(acceptedSocket);
		pthread_cleanup_pop(0);
	}
}

int main(int argc, const char* argv[]) {
	serverSettings ss = {.thread_count = 4};
	setupServerSettings(argc, argv, &ss);

	int serverFd;
	sockaddr_in address;
	int addrLen = sizeof(address);

	if ((serverFd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
		perror("In socket creation");
		exit(EXIT_FAILURE);
	}

	bzero(&address, addrLen);
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	if (bind(serverFd, (sockaddr*)&address, sizeof(address)) < 0) {
		perror("In bind");
		exit(EXIT_FAILURE);
	}

	if (listen(serverFd, MAX_LISTEN_CONN) < 0) {
		perror("In listen");
		exit(EXIT_FAILURE);
	}

	printf("\nServer is now listening at port %d:\n\n", PORT);

	while (1) {
		pthread_mutex_lock(&mutex);
		while (thread_count >= ss.thread_count)
			pthread_cond_wait(&cond, &mutex);
		pthread_mutex_unlock(&mutex);

		// create new thread to handle the request.
		pthread_t thread_id;
		acceptParams ap = {serverFd, (sockaddr*)&address, (socklen_t*)&addrLen};
		pthread_create(&thread_id, NULL, accept_conn, &ap);
		atomic_fetch_add(&thread_count, 1);
		printf("[Info] Thread Created: No.%d\n", thread_count);
	}

	return EXIT_SUCCESS;
}