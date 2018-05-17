#ifndef	_HASHTABLE_H_
#define _HASHTABLE_H_

#include "Symbol.h"

#define HASH_SIZE 733
#define SCOPE_SIZE 8 


class HashTable
{
  private:
	Symbol **SymTable;
	Symbol **ScopeHead;

  public:
	int maxscopesize;
	HashTable();

	unsigned int hashfunc(std::string);
	Symbol *insert(Symbol *);
	Symbol *lookup(std::string);
	Symbol *lookup(std::string, int);
	Symbol *lookup(std::string, int, int);
	void hideScope(int);
	std::string toString();
	std::string scopetoString(int);
	std::string allscopestoString();
};

#endif
