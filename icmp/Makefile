CC=gcc
FLAGS= -g -O0 -Wall
SERVER=server.o sendicmp.o util.o oncall.o
CLIENT=client.c sendicmp.c util.c

default:
	@echo 'server' \|\| 'client' \|\| 'clean'

client: ${CLIENT}
	${CC} ${FLAGS} -o client ${CLIENT}

clean:
	rm -f *.o client server
