CC=gcc
CFLAGS=-g -Wall -D_GNU_SOURCE -D_DEFAULT_SOURCE -I../
LIBS=-lncurses -ltinfo
BINS=twinkle

all: $(BINS)

%: %.c ../charsl.h
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

clean:
	$(RM) $(BINS)
