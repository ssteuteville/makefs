makefs: makefs.o make_generator.o meta_system.o
	gcc -g -o makefs makefs.o make_generator.o meta_system.o `pkg-config fuse --libs`

makefs.o: makefs.c parameters.h
	gcc `pkg-config fuse --cflags` -c makefs.c
make_generator.o: make_generator.c make_generator.h
	gcc `pkg-config fuse --cflags` -c make_generator.c
meta_system.o: meta_system.c meta_system.h
	gcc `pkg-config fuse --cflags` -c meta_system.c
clean:
	rm -f makefs *.o
