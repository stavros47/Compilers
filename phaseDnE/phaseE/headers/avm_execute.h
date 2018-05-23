#ifndef _AVM_EXECUTE_H_
#define _AVM_EXECUTE_H_

typedef void (*execute_func_t)(instruction*);

extern execute_func_t executeFuncs[];

void execute_arithmetic(instruction*);

#define AVM_MAX_INSTRUCTIONS (unsigned)nop_v

/* avm_execute.cpp */
void execute_assign      (instruction*);
void execute_add         (instruction*);
void execute_sub         (instruction*);
void execute_mul         (instruction*);
void execute_div         (instruction*);
void execute_mod         (instruction*);
void execute_nop         (instruction*);

/* avm_execute_jump.cpp */
void execute_jeq         (instruction*);
void execute_jne         (instruction*);
void execute_jle         (instruction*);
void execute_jge         (instruction*);
void execute_jlt         (instruction*);
void execute_jgt         (instruction*);
unsigned char jump_eqChecks(avm_memcell*,avm_memcell*);
unsigned char jump_leChecks(avm_memcell*,avm_memcell*);
unsigned char jump_geChecks(avm_memcell*,avm_memcell*);

/* avm_execute_function.cpp */
void execute_call        (instruction*);
void execute_pusharg     (instruction*);
void execute_funcenter   (instruction*);
void execute_funcexit    (instruction*);

/* avm_execute_table.cpp */
void execute_newtable    (instruction*);
void execute_tablegetelem(instruction*);
void execute_tablesetelem(instruction*);

#define execute_add execute_arithmetic
#define execute_sub execute_arithmetic
#define execute_mul execute_arithmetic
#define execute_div execute_arithmetic
#define execute_mod execute_arithmetic

#endif
