#ifndef _AVM_H_
#define _AVM_H_

#include <stdlib.h>
#include <assert.h>
#include <string>
#include "instructions.h"


enum avm_memcell_t{
	number_m	= 0,
	string_m	= 1,
	bool_m		= 2,
	table_m		= 3,
	userfunc_m	= 4,
	libfunc_m	= 5,
	nil_m		= 6,
	undef_m		= 7,
};

struct avm_table;

struct avm_memcell{
	avm_memcell_t type;
	union{
		double		numVal;
		char*		strVal;
		unsigned char	boolVal;
		avm_table*	tableVal;
		unsigned	funcVal;
		char*		libfuncVal;
	}data;
};

#define AVM_STACKSIZE 4096
#define	AVM_WIPEOUT(m)	memset(&(m),0,sizeof(m))

extern avm_memcell stack[];

static void avm_initstack(void);

avm_table*	avm_tablenew(void);
void		avm_tabledestroy(avm_table*);
avm_memcell*	avm_tablegetelem(avm_memcell*);
void		avm_tablesetelem(avm_memcell*,avm_memcell*);

#define	AVM_TABLE_HASHSIZE 211

struct avm_table_bucket{
	avm_memcell key;
	avm_memcell value;
	avm_table_bucket* next;
};

struct avm_table{
	unsigned		refCounter;
	avm_table_bucket*	strIndexed[AVM_TABLE_HASHSIZE];
	avm_table_bucket*	numIndexed[AVM_TABLE_HASHSIZE];
	unsigned		total;
};

void avm_tableincrefcounter(avm_table*);
void avm_tabledecrefcounter(avm_table*);
void avm_table_bucketsinit(avm_table_bucket**);
void avm_memcellclear(avm_memcell*);
void avm_tablebucketdestroy(avm_table_bucket**);

#define AVM_STACKENV_SIZE 4
extern avm_memcell ax,bx,cx;
extern avm_memcell retval;
extern unsigned top,topsp;

double 	consts_getnumber(unsigned);
char* 	consts_getstring(unsigned);
char*	libfuncs_getused(unsigned);

avm_memcell* avm_translate_operand(vmarg*,avm_memcell*);

typedef void (*execute_func_t)(instruction*);

#define AVM_MAX_INSTRUCTIONS (unsigned)nop_v

extern void execute_assign 	(instruction*);
extern void execute_add 	(instruction*);
extern void execute_sub 	(instruction*);
extern void execute_mul 	(instruction*);
extern void execute_div		(instruction*);
extern void execute_mod    	(instruction*);
extern void execute_uminus	(instruction*);
extern void execute_and		(instruction*);
extern void execute_or     	(instruction*);
extern void execute_not    	(instruction*);
extern void execute_jeq    	(instruction*);
extern void execute_jne    	(instruction*);
extern void execute_jle    	(instruction*);
extern void execute_jge    	(instruction*);
extern void execute_jlt    	(instruction*);
extern void execute_jgt    	(instruction*);
extern void execute_call   	(instruction*);
extern void execute_pusharg	(instruction*);
extern void execute_funcenter	(instruction*);
extern void execute_funcexit	(instruction*);
extern void execute_newtable	(instruction*);
extern void execute_tablegetelem(instruction*);
extern void execute_tablesetelem(instruction*);
extern void execute_nop 	(instruction*);

extern execute_func_t executeFuncs[];

extern unsigned char   executionFinished;
extern unsigned        pc;
extern unsigned        currLine;
extern unsigned        codeSize;
extern instruction*    code;
#define AVM_ENDING_PC   codeSize

void execute_cycle(void);

typedef void (*memclear_func_t)(avm_memcell*);

extern void memclear_string(avm_memcell*);
extern void memclear_table(avm_memcell*);

extern memclear_func_t memclearFuncs[];

extern void avm_warning(const char*,...);
extern void avm_error(const char*,...);
extern char* avm_tostring(avm_memcell*);
extern void avm_callsaveenviroment(void);
extern void avm_calllibfunc(char* funcname);
extern void avm_assign(avm_memcell*,avm_memcell*);

#define AVM_NUMACTUALS_OFFSET 	4
#define AVM_SAVEDPC_OFFSET	3
#define AVM_SAVEDTOPSP_OFFSET	2
#define AVM_SAVEDTOP_OFFSET	1

extern unsigned top;
extern void avm_dec_top(void);
extern userfunc* avm_getfuncinfo(unsigned);
extern void avm_pushenvvalue(unsigned);
extern unsigned avm_getenvvalue(unsigned);

#endif
