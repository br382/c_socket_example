CC=gcc
#CFLAGS="-Wimplicit-function-declaration"

all: server.c client.c
	$(CC) $(CFLAGS) server.c -o server
	$(CC) $(CFLAGS) client.c -o client
