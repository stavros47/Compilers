#include "headers/avm.h"

std::unordered_map< std::string,library_func_t> registry;

unsigned int 	executionFinished = 0;
unsigned        totalActuals=0;
unsigned        max_global_offset=0;

avm_memcell     retval;
avm_memcell     ax,bx,cx;
unsigned        top,topsp;

unsigned	    pc = 1;
unsigned	    currLine = 1;
unsigned	    codeSize = 0;
instruction*	code = (instruction*) 0;

