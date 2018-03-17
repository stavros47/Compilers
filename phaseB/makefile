al: alpha_token_t.o flex.o
	g++ alpha_token_t.o flex.o -o al

alpha_token_t.o : alpha_token_t.cpp alpha_token_t.h
	g++ -c alpha_token_t.cpp -std=c++11

flex.cpp: verb.l
	flex verb.l

flex.o: flex.cpp
	g++ -c flex.cpp -std=c++11
clean:
	rm al flex.cpp *.o
