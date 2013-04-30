runnable: hello.o main.o
	g++ -Wall -pedantic -g -o runnable hello.o main.o

hello.o: hello.h hello.c
	g++ -Wall -pedantic -g -c hello.c

main.o: hello.o
	g++ -Wall -pedantic -g -c main.c

clean:
	rm -f runnable *.o
