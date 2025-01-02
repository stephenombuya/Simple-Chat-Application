CC=gcc
CFLAGS=-Wall -Wextra
TARGET=server client

all: $(TARGET)

server: src/server.c
	$(CC) $(CFLAGS) -o server src/server.c

client: src/client.c
	$(CC) $(CFLAGS) -o client src/client.c

clean:
	rm -f $(TARGET)

.PHONY: all clean
