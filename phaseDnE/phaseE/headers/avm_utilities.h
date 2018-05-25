#ifndef _AVM_UTILITIES_H_
#define _AVM_UTILITIES_H_

#define AVM_STACKSIZE 4096
#define AVM_STACKENV_SIZE 4

#define AVM_WIPEOUT(m)  memset(&(m),0,sizeof(m))
#define AVM_ENDING_PC   codeSize

#define AVM_NUMACTUALS_OFFSET   4
#define AVM_SAVEDPC_OFFSET      3
#define AVM_SAVEDTOPSP_OFFSET   2
#define AVM_SAVEDTOP_OFFSET     1

#define I_EXPAND_SIZE 2048
#define I_CURR_SIZE (totalInstr*sizeof(instruction))
#define I_NEW_SIZE (I_EXPAND_SIZE*sizeof(instruction) + I_CURR_SIZE)

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

struct avm_memcell;
struct avm_table;
struct avm_table_bucket;

extern const char* typeStrings[];
extern avm_memcell stack[];

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

double  consts_getnumber(unsigned);
char*   consts_getstring(unsigned);
char*   libfuncs_getused(unsigned);
userfunc* avm_getfuncinfo(unsigned);

avm_memcell* avm_translate_operand(vmarg*,avm_memcell*);

static void avm_initstack(void);

void avm_warning(const char*,...);
void avm_error(const char*,...);
void avm_callsaveenviroment(void);

void copy_to_from(avm_table*,avm_table*);
void copy_tohash(avm_table_bucket**,avm_table_bucket**);

void copy_to(avm_table*,avm_table*);
void copy_deeptohash(avm_table_bucket**,avm_table_bucket**);
void avm_assign(avm_memcell*,avm_memcell*);

void avm_dec_top(void);
void avm_pushenvvalue(unsigned);
unsigned avm_getenvvalue(unsigned);

void avm_initialize(void);
void execute_cycle(void);

void test_global(vmarg);
void expand_instr(void);
void print_stack();
void print_info();

#endif
