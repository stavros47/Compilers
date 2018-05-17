#ifndef _AVM_LIBFUNCS_H_
#define _AVM_LIBFUNCS_H_

typedef void (*library_func_t)(void);

extern void avm_calllibfunc(char* funcname);
library_func_t avm_getlibraryfunc(char*);
unsigned avm_totalactuals(void);
avm_memcell* avm_getactual(unsigned);

void avm_registerlibfunc(std::string id,library_func_t addr);

void libfunc_print(void);
void libfunc_typeof(void);
void libfunc_totalarguments(void);
#endif
