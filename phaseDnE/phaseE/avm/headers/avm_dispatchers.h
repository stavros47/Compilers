#ifndef _AVM_DISPATCHERS_H_
#define _AVM_DISPATCHERS_H_

/************MEMCLEAR*********************/
typedef void (*memclear_func_t)(avm_memcell*);

extern void memclear_string(avm_memcell*);
extern void memclear_table(avm_memcell*);

extern memclear_func_t memclearFuncs[];

/***********TOSTRING*************************/
typedef std::string (*tostring_func_t)(avm_memcell*);

extern tostring_func_t tostringFuncs[];

extern std::string number_tostring(avm_memcell*);
extern std::string string_tostring(avm_memcell*);
extern std::string bool_tostring(avm_memcell*);
extern std::string table_tostring(avm_memcell*);
extern std::string userfunc_tostring(avm_memcell*);
extern std::string libfunc_tostring(avm_memcell*);
extern std::string nil_tostring(avm_memcell*);
extern std::string undef_tostring(avm_memcell*);

extern std::string avm_tostring(avm_memcell*);
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

typedef unsigned char (*check_eq_func_t)(avm_memcell*,avm_memcell*);

extern check_eq_func_t check_eqFuncs[];

unsigned char number_check_eq(avm_memcell* first,avm_memcell* second);

unsigned char string_check_eq(avm_memcell*,avm_memcell*);
unsigned char table_check_eq(avm_memcell*,avm_memcell*);
unsigned char userfunc_check_eq(avm_memcell*,avm_memcell*);
unsigned char libfunc_check_eq(avm_memcell*,avm_memcell*);

#endif
