DEPS = Symbol.h HashTable.h quad.h
obj = parser.o scanner.o Symbol.o HashTable.o quad.o
FLAGS = -std=c++11 -g
CC = g++

%.o: %.cpp $(DEPS)
	$(CC) -c $(FLAGS) $< -o $@ 

al: $(obj) $(DEPS)
	$(CC) $(FLAGS) $^ -o $@ -g

parser.cpp: parser.y
	bison --yacc --defines --output=parser.cpp parser.y -v

scanner.cpp : scanner.l
	flex scanner.l

clean:
	rm al parser.cpp scanner.cpp parser.hpp parser.output *.o *.txt
