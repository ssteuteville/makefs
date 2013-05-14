.PHONY: clean
CC = gcc
DEPS = meta_system.h
OBJ = meta_system.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

runnable: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f runnable $(OBJ)
