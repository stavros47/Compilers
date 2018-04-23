#ifndef	_SYMTABLE_H_
#define _SYMTABLE_H_

#define HASH_SIZE 733
#define SCOPE_SIZE 8 
#define EXPAND_SIZE 1024
#define CURR_SIZE (total*sizeof(quad))
#define NEW_SIZE (EXPAND_SIZE*sizeof(quad) + CURR_SIZE)

#include <stack>
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

enum Type {GLOBAL_VAR,LOCAL_VAR,FUNC_ARG,LIBRARY_FUNC,PROGRAM_FUNC};

enum scopespace_t {programVar,	functionLocal,	formalArg};

struct Symbol{
	std::string name;
	Type type;
	int lineno;
	int scope;
	scopespace_t range;
	int offset;
	bool hidden;
	struct Symbol* next;
	struct Symbol* scopeNext;
};

typedef struct Symbol Symbol;

Symbol* construct_Symbol(std::string,int,int,int,scopespace_t,int);
std::string getTypeasString(Symbol*);
std::string sym_toString(Symbol*);
std::string getScopeSpaceasString(Symbol*);

class HashTable
{
  private:
	Symbol **SymTable;
	Symbol **ScopeHead;

  public:
	int maxscopesize;
	HashTable();
	HashTable(int);

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

enum expr_t{
	var_e,		tableitem_e,
	programfunc_e,	libraryfunc_e,
	arithexpr_e,	boolexpr_e,
	assignexpr_e,	newtable_e,
	constnum_e,	constbool_e,
	conststring_e,	nil_e
};

enum iopcode{
        assign,         add,            sub,
        mul,            Div,            mod,
        uminus,         And,            Or,
        Not,            if_eq,          if_noteq,
        if_lesseq,      if_greatereq,   if_less,
        ret,            getretval,      funcstart,
        funcend,        tablecrate,     tablegetelem,
        tablesetelem
};
/*
enum iopcode{
        ASSIGN,         ADD,            SUB,
        MUL,            DIV,            MOD,
        UMINUS,         AND,            OR,
        NOT,            IF_EQ,          IF_NOTEQ,
        IF_LESSEQ,      IF_GREATEREQ,   IF_LESS,
        RET,            GETRETVAL,      FUNCSTART,
        FUNCEND,        TABLECREATE,    TABLEGETELEM,
        TABLESETELEM
};
*/


struct expr{
	expr_t type;
	Symbol* sym;
	expr*	index;
	double numConst;
	std::string strConst;
	unsigned char boolConst;
	expr* next;
};

struct quad {
	iopcode	op;
	expr* result;
	expr* arg1;
	expr* arg2;
	unsigned line;
	unsigned label;
};

void expand(void);
void emit(iopcode op,expr* arg1,expr* arg2,expr* result,unsigned label,unsigned line);
std::string newtempname();
Symbol *newtemp();
void resettemp();
int currentScope();
scopespace_t currScopeSpace();

std::string quads_toString();
std::string expr_toString();
std::string iopcode_toString();
unsigned currScopeOffset();
void incCurrScopeOffset();
void enterScopeSpace();
void exitScopeSpace();
expr *lvalue_expr(Symbol*);
expr* newexpr(expr_t);

extern unsigned programVarOffset;
extern unsigned functionLocalOffset;
extern unsigned formalArgOffset;

extern int tempcounter;
extern quad*	quads;
extern unsigned total;
extern unsigned currQuad;
extern int yyerror(const char* yaccProvidedMessage);
extern int yylex(void);
extern int yylineno;
extern char* yytext;
extern FILE* yyin;
extern HashTable SymTable; 
extern std::fstream buffer;
extern std::stack<unsigned> offsetStack;
extern unsigned suffixNum;
extern unsigned currScope;
extern unsigned currRange;
extern unsigned currOffset;
#endif
