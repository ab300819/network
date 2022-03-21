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

signal01: src/core_in_c/signal01.c
	${CC} src/core_in_c/signal01.c -o signal01

signal02: src/core_in_c/signal02.c
	${CC} src/core_in_c/signal02.c -o signal02

tenet: tenet.o
	cc -o tenet tenet.o
tenet.o: src/tenet/main.c
	cc -c src/tenet/main.c -o tenet.o

more:src/uup/more01.c
	cc -g src/uup/more01.c -o more
time01: src/core_in_c/time01.c
	${CC} src/core_in_c/time01.c -o time01

time02: src/core_in_c/time02.c
	${CC} src/core_in_c/time02.c -o time02

time03: src/core_in_c/time03.c
	${CC} src/core_in_c/time03.c -o time03

time04: src/core_in_c/time04.c
	${CC} src/core_in_c/time04.c -o time04 -lpthread

atof: src/core_gitin_c/atof.c
	${CC} src/core_in_c/atof.c -o atof

assert: src/core_in_c/assert01.c
	$(CC) src/core_in_c/assert01.c -o assert

errno01: src/core_in_c/errno01.c
	$(CC) src/core_in_c/errno01.c -o errno01 -lm

errno02: src/core_in_c/errno02.c
	$(CC) src/core_in_c/errno02.c -o errno02 -lm -lpthread

.PHONY:clean
clean:
	-rm -v thread* client server daytimetcpcli more tenet *.o
