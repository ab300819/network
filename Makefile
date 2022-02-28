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

thread03: src/core_in_c/thread03.c
	${CC} src/core_in_c/thread03.c -o thread03 -lpthread

thread04: src/core_in_c/thread04.c
	${CC} src/core_in_c/thread04.c -o thread04 -lpthread

thread05: src/core_in_c/thread05.c
	${CC} src/core_in_c/thread05.c -o thread05 -lpthread

thread06: src/core_in_c/thread06.c
	${CC} src/core_in_c/thread06.c -o thread06 -lpthread

.PHONY:clean
clean:
	-rm -v thread* client server daytimetcpcli *.o
