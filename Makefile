AR = ar
CC = gcc
CFLAGS = -std=c99 -pedantic -Wall -Wextra -O3 -I ./include/
SRCS = $(wildcard src/*.c)
OBJS = $(patsubst src/%.c, lib/%.o, $(SRCS))

libconvoy.a: folder $(OBJS)
	$(AR) rcs $@ $(OBJS)

lib/%.o: src/%.c
	$(CC) $(CFLAGS) $^ -c -o $@

folder:
	mkdir lib

clean:
	rm -rf *~ *.o *.a lib
