#define HASH_SIZE 733
#define SCOPE_SIZE 8
#include <string>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

class HashTable{
	private:
		Symbol **SymTable;
		Symbol **ScopeHead;
	public:
		HashTable();
		HashTable(int);

		unsigned int hashfunc(std::string);
		void insert(Symbol*);
		Symbol* lookup(std::string);
		Symbol* lookup(std::string,int);
		std::string toString();
		std::string scopetoString(int);
		std::string allscopestoString();
};
