#ifndef __INSTRUCTIONS_H__
#define __INSTRUCTIONS_H__
#include "quad.h"

unsigned consts_newstring (char* s);
unsigned consts_newnumber (double n);
unsigned libfuncs_newused (char* s);
unsigned userfuncs_newfunc (Symbol* sym);

enum vmopcode{
        assign_v,         add_v,            sub_v,
        mul_v,            div_v,            mod_v,
        not_v,            jeq_v,            jne_v,
        jle_v,            jge_v,            jlt_v,
	    jgt_v,	          call_v,		    pusharg_v,
        funcenter_v,      funcexit_v,       newtable_v,    
        tablegetelem_v,   tablesetelem_v,	nop_v	
};

enum vmarg_t{
    label_a =0,
    globlal_a=1,
    formal_a=2,
    local_a=3,
    number_a=4,
    string_a=5,
    bool_a=6,
    nil_a=7,
    userfunc_a=8,
    libfunc_a=9,
    retval_a=10
};

typedef struct {
    vmarg_t type;
    unsigned val;
}vmarg;

typedef struct{
    vmopcode opcode;
    vmarg result;
    vmarg arg1;
    vmarg arg2;
    unsigned srcLine;

} instructions;

typedef struct {
    unsigned address;
    unsigned localSize;
    char* id;
}userfunc;

double* numConsts;
unsigned totalNumConsts;
char** stringConsts;
unsigned totalStringConsts;
char** namedLibfuncs;
unsigned totalNamedLibfunc;
userfunc* userFuncs;
unsigned totalUserFuncs;

void emit_instruction(instructions);

void make_operand(expr* , vmarg*);

void make_numberoperand(vmarg* , double );

void make_booloperand(vmarg*, unsigned );

void make_retvaloperand(vmarg*);

typedef struct{
    unsigned instrNo;
    unsigned iaddress;
    incomplete_jump* next;
}incomplete_jump;

incomplete_jump* ij_head=(incomplete_jump*) 0; //std::list??
unsigned ij_total=0;

void add_icomplete_jump(unsigned ,unsigned );

void generate(vmopcode,quad*);
extern void generate_ADD (quad*);
extern void generate_SUB (quad*);
extern void generate_MUL (quad*);
extern void generate_DIV (quad*);
extern void generate_MOD (quad*);
extern void generate_NEWTABLE (quad*);
extern void generate_TABLEGETELEM (quad*);
extern void generate_TABLESETELEM (quad*);
extern void generate_ASSIGN (quad*);
extern void generate_NOP (quad*);
extern void generate_JUMP (quad*);
extern void generate_IF_EQ (quad*);
extern void generate_IF_NOTEQ (quad*);
extern void generate_IF_GREATER (quad*);
extern void generate_IF_GREATEREQ (quad*);
extern void generate_IF_LESS (quad*);
extern void generate_IF_LESSEQ (quad*);
extern void generate_NOT (quad*);
extern void generate_PARAM (quad*);
extern void generate_CALL (quad*);
extern void generate_GETRETVAL (quad*);
extern void generate_FUNCSTART (quad*);
extern void generate_RETURN (quad*);
extern void generate_FUNCEND (quad*);

typedef void (*generator_func_t)(quad*);

generator_func_t generators[] = {
 generate_ADD ,
 generate_SUB ,
 generate_MUL ,
 generate_DIV ,
 generate_MOD ,
 generate_NEWTABLE ,
 generate_TABLEGETELEM ,
 generate_TABLESETELEM ,
 generate_ASSIGN ,
 generate_NOP ,
 generate_JUMP ,
 generate_IF_EQ ,
 generate_IF_NOTEQ ,
 generate_IF_GREATER ,
 generate_IF_GREATEREQ,
 generate_IF_LESS ,
 generate_IF_LESSEQ ,
 generate_NOT ,
 generate_PARAM ,
 generate_CALL ,
 generate_GETRETVAL ,
 generate_FUNCSTART ,
 generate_RETURN ,
 generate_FUNCEND 
};
#endif