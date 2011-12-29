AR = ar
CC = gcc
CFLAGS = -std=c89 -pedantic -Wall -Wextra -O3 -I ./include/
SRCS = $(wildcard src/*.c)
OBJS = $(patsubst src/%.c, obj/%.o, $(SRCS))

static: libconvoy.a

shared: libconvoy.so

alex-install: libconvoy.a
	cp $^ /usr/local/lib/; cp include/* /usr/local/include/convoy

libconvoy.a: folder $(OBJS)
	$(AR) rcs $@ $(OBJS)

libconvoy.so: CFLAGS += -fPIC
libconvoy.so: folder $(OBJS)
	$(CC) -shared -Wl,-soname,libconvoy.so -o libconvoy.so $(OBJS)

obj/%.o: src/%.c FORCE
	$(CC) $(CFLAGS) $< -c -o $@

folder:
	mkdir -p obj

.PHONY : FORCE
FORCE:

.PHONY : clean
clean:
	rm -rf *~ *.o *.a obj
