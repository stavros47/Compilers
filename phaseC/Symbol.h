
#ifndef	_SYMBOL_H_
#define _SYMBOL_H_

#include <stack>
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <math.h>

enum Type {GLOBAL_VAR,LOCAL_VAR,FUNC_ARG,LIBRARY_FUNC,PROGRAM_FUNC};

enum scopespace_t {programVar,	functionLocal,	formalArg};

struct function{
	unsigned iaddress;
	unsigned totallocals;
	unsigned totalformals;
};

struct Symbol{
	std::string name;
	Type type;
	int lineno;
	int scope;
	int range;
	scopespace_t scopespace;
	int offset;
	bool hidden;
	struct function function;
	struct Symbol* next;
	struct Symbol* scopeNext;
};

typedef struct Symbol Symbol;

Symbol* construct_Symbol(std::string,int,int,int,unsigned,scopespace_t,int);
std::string getTypeasString(Symbol*);
std::string sym_toString(Symbol*);
std::string getScopeSpaceasString(Symbol*);

#endif
