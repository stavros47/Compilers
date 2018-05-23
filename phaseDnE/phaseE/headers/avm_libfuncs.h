#ifndef _AVM_LIBFUNCS_H_
#define _AVM_LIBFUNCS_H_

typedef void (*library_func_t)(void);

void avm_calllibfunc(char* funcname);
library_func_t avm_getlibraryfunc(char*);
unsigned avm_totalactuals(void);
avm_memcell* avm_getactual(unsigned);

void avm_registerlibfunc(std::string id,library_func_t addr);

void libfunc_print(void);
void libfunc_typeof(void);
void libfunc_totalarguments(void);
void libfunc_input(void);
void libfunc_objectcopy(void);
void libfunc_objectmemberkeys(void);
void libfunc_objecttotalmembers(void);
void libfunc_argument(void);
void libfunc_sin(void);
void libfunc_cos(void);
void libfunc_sqrt(void);
void libfunc_strtonum(void);

#endif
