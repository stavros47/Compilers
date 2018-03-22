CC=g++
DEPS=symbol.h symtable.h
OBJ=symbol.o symtable.o main.o
CFLAGS=

%.o:%.c $(DEPS)
	$(CC) -c $(CFLAGS) $< -o $@
hash: $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm hash *.o
