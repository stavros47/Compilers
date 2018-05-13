#ifndef _AVM_DISPATCHERS_H_
#define _AVM_DISPATCHERS_H_

/************MEMCLEAR*********************/
typedef void (*memclear_func_t)(avm_memcell*);

extern void memclear_string(avm_memcell*);
extern void memclear_table(avm_memcell*);

extern memclear_func_t memclearFuncs[];

/***********TOSTRING*************************/
typedef char* (*tostring_func_t)(avm_memcell*);

extern tostring_func_t tostringFuncs[];

extern char* number_tostring(avm_memcell*);
extern char* string_tostring(avm_memcell*);
extern char* bool_tostring(avm_memcell*);
extern char* table_tostring(avm_memcell*);
extern char* userfunc_tostring(avm_memcell*);
extern char* libfunc_tostring(avm_memcell*);
extern char* nil_tostring(avm_memcell*);
extern char* undef_tostring(avm_memcell*);

extern char* avm_tostring(avm_memcell*);
/******************ARITHMETIC**********************/
typedef double (*arithmetic_func_t)(double x,double y);

extern arithmetic_func_t arithmeticFuncs[];

extern double add_impl(double x,double y);
extern double sub_impl(double x,double y);
extern double mul_impl(double x,double y);
extern double div_impl(double x,double y);
extern double mod_impl(double x,double y);

/*******************TOBOOL*************************/
typedef unsigned char (*tobool_func_t)(avm_memcell*);

extern tobool_func_t toboolFuncs[];

extern unsigned char number_tobool(avm_memcell*);
extern unsigned char string_tobool(avm_memcell*);
extern unsigned char bool_tobool(avm_memcell*);
extern unsigned char table_tobool(avm_memcell*);
extern unsigned char userfunc_tobool(avm_memcell*);
extern unsigned char libfunc_tobool(avm_memcell*);
extern unsigned char nil_tobool(avm_memcell*);
extern unsigned char undef_tobool(avm_memcell*);

unsigned char avm_tobool(avm_memcell*);

#endif
