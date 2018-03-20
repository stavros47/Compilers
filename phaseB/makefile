al: scanner.cpp parser.cpp
	g++ scanner.cpp parser.cpp -o al

scanner.cpp : scanner.l
	flex scanner.l

parser.cpp: parser.y
	bison --yacc --defines --output=parser.cpp parser.y

clean:
	rm parser.cpp scanner.cpp parser.hpp al
