#ifndef _AVM_H_
#define _AVM_H_

#include <stdlib.h>
#include <assert.h>
#include <string>
#include "../../phaseD/instructions.h"
#include <unordered_map>

#include "avm_utilities.h"
#include "avm_table.h"
#include "avm_execute.h"
#include "avm_dispatchers.h"
#include "avm_libfuncs.h"

extern unsigned int   executionFinished;
extern unsigned totalActuals;
extern std::unordered_map< std::string,library_func_t> registry;
extern unsigned max_global_offset;


#endif
