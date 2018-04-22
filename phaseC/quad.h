#include <stack>
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
        mul,            div,            mod,
        uminus,         and,            or,
        not,            if_eq,          if_noteq,
        if_lesseq,      if_greatereq,   if_less,
        ret,            getretval,      funcstart,
        funcend,        tablecrate,     tablegetelem,
        tablesetelem
};

struct quad {
	iopcode	op;
	expr* result;
	expr* arg1;
	expr* arg2;
	unsigned line;
	unsigned label;
};

struct expr{
	expr_t type;
	symbol* sym;
	expr*	index;
	double numConst;
	char* strConst;
	unsigned char boolConst;
	expr* next;
};

quad*	quads = (quad*) 0;
unsigned total=0;
unsigned currQuad = 0;

#define EXPAND_SIZE 1024;
#define CURR_SIZE (total*sizeof(quad))
#define NEW_SIZE (EXPAND_SIZE*sizeof(quad) + CURR_SIZE)


void expand(void);
void emit(iopcode op,expr* arg1,expr* arg2,expr* result,unsigned label,unsigned line);
