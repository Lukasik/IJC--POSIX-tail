cflags=-std=c99 -pedantic -Wall -Wextra
cppflags=-std=c++11 -pedantic -Wall -Wextra

all: tail tail2 wordcount wordcount-dynamic

tail: tail.o
	gcc $(cflags) tail.o -o tail

tail2: tail2.o
	g++-4.7 $(cppflags) tail2.o -o tail2

wordcount: wordcount.o  libhtable-static io.o
	gcc $(cflags) -static wordcount.o io.o -L. -lhtable -o wordcount

wordcount-dynamic: wordcount.o  libhtable-dynamic io.o
	gcc $(cflags) -fPIC wordcount.o io.o -L. -lhtable -o wordcount-dynamic

libhtable-static: libhtable
	ar rcs libhtable.a hash_function.o htable_clear.o htable_foreach.o htable_free.o htable_lookup.o htable_remove.o htable_statistics.o htable_init.o

libhtable-dynamic: libhtable
	gcc $(cflags) -shared hash_function.o htable_clear.o htable_foreach.o htable_free.o htable_lookup.o htable_remove.o htable_statistics.o htable_init.o -o libhtable.so

libhtable: hash_function.o htable_clear.o htable_foreach.o htable_free.o htable_lookup.o htable_remove.o htable_statistics.o htable_init.o

clean:
	rm -f *.o tail tail2 libhtable* *.zip seg wordcount wordcount-dynamic

pack: clean
	zip xvokra00.zip *.c *.h *.cc Makefile

tail2.o: tail2.cc
	g++-4.7 $(cppflags) -c tail2.cc

io.o: io.c
	gcc $(cflags) -c io.c

tail.o: tail.c
	gcc $(cflags) -c tail.c

wordcount.o: wordcount.c
	gcc $(cflags) -c wordcount.c

%.o: %.c
	gcc $(cflags) -c $< -fPIC
