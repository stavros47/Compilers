#ifndef _AVM_DISPATCHERS_H_
#define _AVM_DISPATCHERS_H_

/************MEMCLEAR*********************/
typedef void (*memclear_func_t)(avm_memcell*);
extern memclear_func_t memclearFuncs[];

void avm_memcellclear(avm_memcell*);

void memclear_string(avm_memcell*);
void memclear_table(avm_memcell*);

/***********TOSTRING*************************/
typedef std::string (*tostring_func_t)(avm_memcell*);
extern tostring_func_t tostringFuncs[];

std::string avm_tostring(avm_memcell*);

std::string number_tostring(avm_memcell*);
std::string string_tostring(avm_memcell*);
std::string bool_tostring(avm_memcell*);
std::string table_tostring(avm_memcell*);
std::string userfunc_tostring(avm_memcell*);
std::string libfunc_tostring(avm_memcell*);
std::string nil_tostring(avm_memcell*);
std::string undef_tostring(avm_memcell*);

/*******************TOBOOL*************************/
typedef unsigned char (*tobool_func_t)(avm_memcell*);
extern tobool_func_t toboolFuncs[];

unsigned char avm_tobool(avm_memcell*);

unsigned char number_tobool(avm_memcell*);
unsigned char string_tobool(avm_memcell*);
unsigned char bool_tobool(avm_memcell*);
unsigned char table_tobool(avm_memcell*);
unsigned char userfunc_tobool(avm_memcell*);
unsigned char libfunc_tobool(avm_memcell*);
unsigned char nil_tobool(avm_memcell*);
unsigned char undef_tobool(avm_memcell*);

/*******************Compare*************************/
/*******************EQUAL*************************/
typedef unsigned char (*check_eq_func_t)(avm_memcell*,avm_memcell*);
extern check_eq_func_t check_eqFuncs[];

unsigned char number_check_eq(avm_memcell* first,avm_memcell* second);
unsigned char string_check_eq(avm_memcell*,avm_memcell*);
unsigned char bool_check_eq(avm_memcell*,avm_memcell*);
unsigned char table_check_eq(avm_memcell*,avm_memcell*);
unsigned char userfunc_check_eq(avm_memcell*,avm_memcell*);
unsigned char libfunc_check_eq(avm_memcell*,avm_memcell*);

/*******************LESS EQUAL*************************/
typedef unsigned char (*check_le_func_t)(avm_memcell*,avm_memcell*);
extern check_le_func_t check_leFuncs[];

unsigned char number_check_le(avm_memcell* first,avm_memcell* second);
unsigned char string_check_le(avm_memcell*,avm_memcell*);
unsigned char table_check_le(avm_memcell*,avm_memcell*);

/*******************GREATER EQUAL*************************/
typedef unsigned char (*check_ge_func_t)(avm_memcell*,avm_memcell*);
extern check_ge_func_t check_geFuncs[];

unsigned char number_check_ge(avm_memcell* first,avm_memcell* second);
unsigned char string_check_ge(avm_memcell*,avm_memcell*);
unsigned char table_check_ge(avm_memcell*,avm_memcell*);

/******************ARITHMETIC**********************/
typedef double (*arithmetic_func_t)(double x,double y);
extern arithmetic_func_t arithmeticFuncs[];

double add_impl(double x,double y);
double sub_impl(double x,double y);
double mul_impl(double x,double y);
double div_impl(double x,double y);
double mod_impl(double x,double y);

#endif
