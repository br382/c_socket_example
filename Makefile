CC=gcc
#CFLAGS="-Wimplicit-function-declaration"
port:=$(shell bash -c 'echo $$(( ((RANDOM<<15)|RANDOM) % 63001 + 2000 ))')

all: clean build run

build: server.c client.c
	$(CC) $(CFLAGS) server.c -o server
	$(CC) $(CFLAGS) client.c -o client

run: server client
	echo "Running with port $(port)"
	./server $(port) &
	sleep 1
	echo "Message to the Server" | ./client localhost $(port)

clean:
	rm server client || echo "Nothing to clean."

