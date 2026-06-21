CC = gcc
CFLAGS = -Wall -Wextra $(shell pkg-config --cflags libxml-2.0)
LDFLAGS =  $(shell pkg-config --libs libxml-2.0)

.PHONY: all

all: build

build: structure.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

static: structure.c
	$(CC) $(CFLAGS) -o build-static $^ \
		$(shell pkg-config --cflags --static libxml-2.0) \
		$(shell pkg-config --libs --static libxml-2.0) \

clean:
	rm -f build build-static

