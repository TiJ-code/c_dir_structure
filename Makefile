CC = gcc
CFLAGS = -Wall -Wextra $(shell pkg-config --cflags libxml-2.0)
LDFLAGS =  $(shell pkg-config --libs libxml-2.0)

.PHONY: all

all: build

build: structure.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f *.rm -f *.oo

