mygcc: alpha_token_t.cpp main.cpp 
	g++ alpha_token_t.cpp main.cpp -o al -g -std=c++11

main.cpp: verb.l
	flex verb.l
clean:
	rm al main.cpp
