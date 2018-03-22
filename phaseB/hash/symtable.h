#define SIZE 100
#define HASH_SIZE 733
#define SCOPE_SIZE 8
#include "symbol.h"

class HashTable{
	public:
		Symbol **SymTable;
		Symbol **ScopeHead;
		int totalScope;
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
