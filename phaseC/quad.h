#ifndef	_QUAD_H_
#define _QUAD_H_

#include "HashTable.h"

#define EXPAND_SIZE 1024
#define CURR_SIZE (total*sizeof(quad))
#define NEW_SIZE (EXPAND_SIZE*sizeof(quad) + CURR_SIZE)

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
	if_greater,	call,		param,
        ret,            getretval,      funcstart,
        funcend,        tablecreate,     tablegetelem,
        tablesetelem,	jump	
};

struct expr{
	expr_t type;
	Symbol* sym;
	expr*	index;
	double numConst;
	std::string strConst;
	unsigned char boolConst;
	std::list<unsigned> trueList,falseList;
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

struct indexed{
	expr* key;
	expr* value;
	indexed* next;
};

struct callsuffix{
	expr* list;
	bool method;
	char* name;
};

struct forPrefix{
        int test;
	int enter;
};

void expand(void);
void emit(iopcode op,expr* arg1,expr* arg2,expr* result,unsigned label,unsigned line);

std::string newtempname();
Symbol *newtemp();

scopespace_t currScopeSpace();
int currentScope();
unsigned currScopeOffset();
void incCurrScopeOffset();
void enterScopeSpace();
void exitScopeSpace();

unsigned nextquadlabel();
void patchlabel(unsigned,unsigned);
void patchlabel(std::list<unsigned>,unsigned);
expr* backpatch(expr*);
expr* checkexpr(expr*);

expr *lvalue_expr(Symbol*);
expr* newexpr(expr_t);
expr* newexpr_constbool_e(bool);
expr* newexpr_constnum_e(double);
expr* newexpr_conststring_e(char*);

expr* call_emits(expr*,expr*);
expr* arithop_emits(iopcode,expr*,expr*);
expr* relop_emits(iopcode,expr*,expr*);
expr* boolop_emits(iopcode,expr*,expr*,unsigned);

expr* member_item(expr*,char*);
expr* member_item(expr*,double);
expr* emit_iftableitem(expr*);

std::string iopcode_toString();
std::string expr_toString(expr*);
std::string quads_toString();

extern quad*	quads;
extern unsigned programVarOffset;
extern unsigned functionLocalOffset;
extern unsigned formalArgOffset;
extern unsigned error;
extern unsigned inFucntion;
extern unsigned tempcounter;
extern unsigned total;
extern unsigned currQuad;
extern int yyerror(const char* yaccProvidedMessage);
extern int yylex(void);
extern int yylineno;
extern char* yytext;
extern FILE* yyin;
extern HashTable SymTable; 
extern std::fstream error_buffer,grammar_buffer;
extern std::stack<unsigned> offsetStack;
extern unsigned suffixNum;
extern unsigned currScope;
extern unsigned currRange;
extern unsigned currOffset;

#endif


