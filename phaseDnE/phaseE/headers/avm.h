#ifndef _AVM_H_
#define _AVM_H_

#include <stdlib.h>
#include <assert.h>
#include <string>
#include <fstream>
#include <unordered_map>
#include "../../phaseD/instructions.h"

#include "avm_utilities.h"
#include "avm_table.h"
#include "avm_execute.h"
#include "avm_dispatchers.h"
#include "avm_libfuncs.h"

void read_binary(char*);
void open_txt(std::string);

extern std::unordered_map< std::string,library_func_t> registry;

extern unsigned int executionFinished;
extern unsigned     totalActuals;
extern unsigned     max_global_offset;

extern avm_memcell  ax,bx,cx;
extern avm_memcell  retval;
extern unsigned     top,topsp;

extern unsigned     pc;
extern unsigned     currLine;
extern unsigned     codeSize;
extern instruction* code;

extern unsigned     totalInstr;

#endif
