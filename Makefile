CC = gcc
CFLAGS = -Wall

all: server client

server: serv.c list.c
	$(CC) $(CFLAGS) -o server serv.c list.c

client: cli.c
	$(CC) $(CFLAGS) -o client cli.c

clean:
	rm -f server client
