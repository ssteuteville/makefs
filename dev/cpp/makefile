.PHONY: clean
CC = g++ 
CFLAGS = -g -Wall -pedantic 
OBJ = metaMakeTest.o makeGenerator.o metaSystem.o 

%%.o: %%.c
	$(CC) -c -o $@ $< $(CFLAGS)

cpp: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f cpp *.o
