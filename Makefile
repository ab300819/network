all:client server
.PHONY:all

client:client.o
	cc -o client client.o
client.o:src/geek_time/client.c
	cc -c  src/geek_time/client.c
server:server.o
	cc -o server server.o
server.o:src/geek_time/server.c
	cc -c src/geek_time/server.c
daytimetcpcli:daytimetcpcli.o
	cc -o daytimetcpcli daytimetcpcli.o
daytimetcpcli.o:src/unp/daytimetcpcli.c
	cc -c src/unp/daytimetcpcli.c

demo01: src/core_in_c/demo01.c
	cc src/core_in_c/demo01.c -o demo01 -lpthread

.PHONY:clean
clean:
	-rm -rv demo01 client server daytimetcpcli *.o
