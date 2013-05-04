makefs : makefs.o
	gcc -g -o makefs makefs.o `pkg-config fuse --libs`

makefs.o : makefs.c parameters.h
	gcc -g -Wall `pkg-config fuse --cflags` -c makefs.c


clean:
	rm -f makefs *.o
