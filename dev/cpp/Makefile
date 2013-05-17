.PHONY: clean
CC = g++
DEPS = MetaSystem.h
OBJ = MetaSystem.o test1.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

runnable: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f runnable $(OBJ)
