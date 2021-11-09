CC=gcc
CFLAGS=-g -Wall -D_GNU_SOURCE -D_DEFAULT_SOURCE -I../
LIBS=-lncurses -ltinfo

SRCS=$(wildcard *.c)
BINS=$(patsubst %.c, %, $(SRCS))

all: $(BINS)

%: %.c ../charsl.h
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

clean:
	find . -type f -executable -delete
