#ifndef _INSTRUCTIONS_H_
#define _INSTRUCTIONS_H_
#include <vector>
#include "quad.h"
#define MAGICNUMBER (unsigned)474747

unsigned consts_newstring (std::string s);
unsigned consts_newnumber (double n);
unsigned libfuncs_newused (std::string s);
unsigned userfuncs_newfunc (Symbol* sym);
extern unsigned currInstruction;

enum vmopcode{
        assign_v,         add_v,            sub_v,
        mul_v,            div_v,            mod_v,
        jeq_v,            jne_v,            jle_v,
        jge_v,            jlt_v,    	    jgt_v,
        call_v,		      pusharg_v,        funcenter_v,
        funcexit_v,       newtable_v,       tablegetelem_v,
        tablesetelem_v,	  nop_v	
};

enum vmarg_t{
    label_a =0,     global_a=1,     formal_a=2,
    local_a=3,      number_a=4,     string_a=5,
    bool_a=6,       nil_a=7,        userfunc_a=8,
    libfunc_a=9,    retval_a=10
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

} instruction;

typedef struct {
    unsigned address;
    unsigned localSize;
    std::string id;
}userfunc;

extern unsigned totalStrings ;
extern unsigned totalNumConsts;
extern unsigned totalLibFuncs ;
extern unsigned totalUserFuncs;

extern std::vector<std::string> strConsts;
extern std::vector<double> numConsts; 
extern std::vector<std::string> libFuncs;
extern std::vector<userfunc*> userFuncs;

extern instruction* instructions;

template <class T>
void vector_to_file(std::vector<T> constArray, std::string name);

void make_instructions(quad*);
void generate_output();
unsigned nextinstructionlabel();
void emit_instruction(instruction);

void generate_binary();
void instructions_tobinary(FILE*);
void vmarg_tobinary(vmarg,FILE*);
void vectors_tobinary(FILE*);
void num_tobinary(FILE*);
void str_tobinary(FILE*);
void libfunc_tobinary(FILE*);
void userfunc_tobinary(FILE*);

void make_operand(expr* , vmarg*);
void make_numberoperand(vmarg* , double );
void make_booloperand(vmarg*, unsigned );
void make_retvaloperand(vmarg*);

typedef void (*generator_func_t)(quad*);
extern generator_func_t generators[] ;

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

std::string vmopcode_toString();
std::string vmarg_toString(vmarg temp);
std::string instr_to_String();

#endif