#include "avm.h"

unsigned totalActuals=0;
unsigned top,topsp;
avm_memcell retval;
avm_memcell ax,bx,cx;

avm_memcell stack[AVM_STACKSIZE];

unsigned char 	executionFinished = 0;
unsigned	pc = 0;
unsigned	currLine = 0;
unsigned	codeSize = 0;
instruction*	code = (instruction*) 0;

