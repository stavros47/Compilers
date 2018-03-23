al: scanner.cpp parser.cpp symtable.cpp	symtable.h
	g++ scanner.cpp parser.cpp symtable.cpp -o al

scanner.cpp : scanner.l
	flex scanner.l

parser.cpp: parser.y
	bison --yacc --defines --output=parser.cpp parser.y -v

clean:
	rm parser.cpp scanner.cpp parser.hpp al parser.output
