#ifndef _AVM_UTILITIES_H_
#define _AVM_UTILITIES_H_

enum avm_memcell_t{
        number_m        = 0,
        string_m        = 1,
        bool_m          = 2,
        table_m         = 3,
        userfunc_m      = 4,
        libfunc_m       = 5,
        nil_m           = 6,
        undef_m         = 7,
};

extern std::string typeStrings[];

struct avm_table;

struct avm_memcell{
        avm_memcell_t type;
        union{
                double          numVal;
                char*           strVal;
                unsigned char   boolVal;
                avm_table*      tableVal;
                unsigned        funcVal;
                char*           libfuncVal;
        }data;
};

extern avm_memcell ax,bx,cx;
extern avm_memcell retval;
extern unsigned top,topsp;

double  consts_getnumber(unsigned);
char*   consts_getstring(unsigned);
char*   libfuncs_getused(unsigned);
userfunc* avm_getfuncinfo(unsigned);

avm_memcell* avm_translate_operand(vmarg*,avm_memcell*);

/***********STACK******************/
#define AVM_STACKSIZE 4096
#define AVM_STACKENV_SIZE 4
#define AVM_WIPEOUT(m)  memset(&(m),0,sizeof(m))

extern avm_memcell stack[];

static void avm_initstack(void);

extern unsigned        pc;
extern unsigned        currLine;
extern unsigned        codeSize;
extern instruction*    code;

#define AVM_ENDING_PC   codeSize

extern void avm_warning(const char*,...);
extern void avm_error(const char*,...);
extern void avm_callsaveenviroment(void);
extern void avm_assign(avm_memcell*,avm_memcell*);

#define AVM_NUMACTUALS_OFFSET   4
#define AVM_SAVEDPC_OFFSET      3
#define AVM_SAVEDTOPSP_OFFSET   2
#define AVM_SAVEDTOP_OFFSET     1

extern void avm_dec_top(void);
extern void avm_pushenvvalue(unsigned);
extern unsigned avm_getenvvalue(unsigned);

void avm_initialize(void);
void execute_cycle(void);

#endif
