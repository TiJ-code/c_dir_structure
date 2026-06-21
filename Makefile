CC = gcc
CFLAGS = -Wall -Wextra $(shell xml2-config --cflags)
LDFLAGS =  $(shell xml2-config --libs)

.PHONY: all

all: build

build: structure.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f *.rm -f *.oo

