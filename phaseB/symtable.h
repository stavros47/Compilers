#define HASH_SIZE 733
#define SCOPE_SIZE 8
#include <string>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

enum Type {UNDEFINED,VARIABLE,FUNC_ARG,LIBRARY_FUNC,PROGRAM_FUNC};

struct Symbol{
	std::string name;
	Type type;
	int lineno;
	int scope;
	bool hidden;
	struct Symbol* next;
	struct Symbol* scopeNext;
};

typedef struct Symbol Symbol;

Symbol* construct_Symbol(std::string,int,int,int);
std::string getTypeasString(Symbol*);
std::string sym_toString(Symbol*);

class HashTable{
	private:
		Symbol **SymTable;
		Symbol **ScopeHead;
		int maxscopesize;
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
