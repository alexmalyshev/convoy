AR = ar
CC = ~/llvm-build/Release/bin/clang
CFLAGS = -std=c89 -pedantic -Wall -Wextra -O3 -I ./include/
SRCS = $(wildcard src/*.c)
OBJS = $(patsubst src/%.c, obj/%.o, $(SRCS))

static: libconvoy.a

shared: libconvoy.so

alex-install: includefolder libconvoy.a
	cp libconvoy.a /usr/local/lib/; cp include/* /usr/local/include/convoy

libconvoy.a: objfolder $(OBJS)
	$(AR) rcs $@ $(OBJS)

libconvoy.so: CFLAGS += -fPIC
libconvoy.so: objfolder $(OBJS)
	$(CC) -shared -Wl,-soname,libconvoy.so -o libconvoy.so $(OBJS)

obj/%.o: src/%.c FORCE
	$(CC) $(CFLAGS) $< -c -o $@

objfolder:
	mkdir -p obj

includefolder:
	mkdir -p /usr/local/include/convoy

.PHONY : FORCE
FORCE:

.PHONY : clean
clean:
	rm -rf *~ *.o *.a obj
