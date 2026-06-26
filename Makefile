C3 = c3c

.PHONY: all build static clean

all: build

build:
	$(C3) build

static:
	$(C3) build --static

clean:
	rm -rf build/

