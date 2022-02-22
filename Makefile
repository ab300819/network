CC=clang

all:client server
.PHONY:all

client:src/networking_in_action/client.c
	${CC} src/networking_in_action/client.c -o client 

server:src/networking_in_action/server.c
	${CC} src/networking_in_action/server.c -o server

daytimetcpcli:src/unp/daytimetcpcli.c 
	${CC} src/unp/daytimetcpcli.c -o daytimetcpcli

thread01: src/core_in_c/thread01.c
	${CC} src/core_in_c/thread01.c -o thread01 -lpthread

thread02: src/core_in_c/thread02.c
	${CC} src/core_in_c/thread02.c -o thread02 -lpthread

.PHONY:clean
clean:
	-rm -v thread01 thread02 client server daytimetcpcli *.o
