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

.PHONY:clean
clean:
	-rm -rv client *.o
