#include "headers/avm.h"

unsigned totalActuals=0;
unsigned top,topsp;
avm_memcell retval;
avm_memcell ax,bx,cx;

avm_memcell stack[AVM_STACKSIZE];

unsigned int 	executionFinished = 0;
unsigned	pc = 1;
unsigned	currLine = 1;
unsigned	codeSize = 0;
instruction*	code = (instruction*) 0;
std::unordered_map< std::string,library_func_t> registry;
unsigned max_global_offset=0;

