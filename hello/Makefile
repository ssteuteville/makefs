runnable: hello.o hello1.o hello2.o hello3.o main.o
	gcc -Wall -pedantic -g -o runnable hello.o hello1.o hello2.o hello3.o main.o

main.o: main.c hello.h hello1.h hello2.h hello3.h
	gcc -Wall -pedantic -c main.c

hello.o: hello.c hello.h
	gcc -Wall -pedantic -c hello.c

hello1.o: hello1.c hello1.h
	gcc -Wall -pedantic -c hello1.c

hello2.o: hello2.c hello2.h
	gcc -Wall -pedantic -c hello2.c

hello3.o: hello3.c hello3.h
	gcc -Wall -pedantic -c hello3.c
