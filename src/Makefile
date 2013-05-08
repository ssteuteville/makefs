makefs : makefs.o make_generator.o
	gcc -g -o makefs makefs.o make_generator.o `pkg-config fuse --libs`

makefs.o: makefs.c parameters.h
	gcc -g -Wall `pkg-config fuse --cflags` -c makefs.c
make_generator.o: make_generator.c make_generator.h
	gcc -g -Wall `pkg-config fuse --cflags` -c make_generator.c

clean:
	rm -f makefs *.o
