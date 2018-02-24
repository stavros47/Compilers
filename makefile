mygcc: alpha_token_t.cpp main.cpp
	g++ alpha_token_t.cpp main.cpp -o mygcc

main.cpp: verb.l
	flex verb.l
clean:
	rm mygcc main.cpp
