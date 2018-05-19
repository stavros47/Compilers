#include "headers/avm.h"

memclear_func_t memclearFuncs[] = {
        0,                      /*number*/
        memclear_string,
        0,                      /*bool*/
        memclear_table,
        0,                      /*userfunc*/
        0,                      /*libfunc*/
        0,                      /*nil*/
        0                       /*undef*/

};

extern void memclear_string(avm_memcell* m){
        assert(m->data.strVal);
        free(m->data.strVal);
}

extern void memclear_table(avm_memcell* m){
        assert(m->data.tableVal);
        avm_tabledecrefcounter(m->data.tableVal);
}


tostring_func_t tostringFuncs[] = {
        number_tostring,
        string_tostring,
        bool_tostring,
        table_tostring,
        userfunc_tostring,
        libfunc_tostring,
        nil_tostring,
        undef_tostring
};

std::string number_tostring(avm_memcell* m){
        if((fmod(m->data.numVal,1)==0)){
                return std::to_string((int)m->data.numVal);
        }else {
                return std::to_string(m->data.numVal);
        }
}

std::string string_tostring(avm_memcell* m){
        return m->data.strVal;
}

std::string bool_tostring(avm_memcell* m){
        return (m->data.boolVal) ? "TRUE" : "FALSE";
}

std::string table_tostring(avm_memcell* m){ /////////////////////
        return "TABLE:GAMATO";
}

std::string userfunc_tostring(avm_memcell* m){
        return std::to_string(userFuncs[m->data.numVal]->address);
}

std::string libfunc_tostring(avm_memcell* m){
        return m->data.libfuncVal;
}

std::string nil_tostring(avm_memcell* m){
        return "nil";
}

std::string undef_tostring(avm_memcell* m){
        return "undef";
}

std::string avm_tostring(avm_memcell* m){
        assert(m->type >=0 && m->type < undef_m);
        return (*tostringFuncs[m->type])(m);
}
/********************************************************/
void avm_memcellclear(avm_memcell* m){
        if(m->type!=undef_m){
                memclear_func_t f = memclearFuncs[m->type];
                if(f)
                        (*f)(m);
                m->type=undef_m;
        }
}

arithmetic_func_t arithmeticFuncs[] = {
        add_impl,
        sub_impl,
        mul_impl,
        div_impl,
        mod_impl
};

double add_impl(double x,double y){return x+y;}
double sub_impl(double x,double y){return x-y;}
double mul_impl(double x,double y){return x*y;}
double div_impl(double x,double y){
        if(!y) avm_error("Invalid operation");
        return x/y;
}

double mod_impl(double x,double y){
        if(!y) avm_error("Invalid operation");
        return (unsigned)x%(unsigned)y;
}


tobool_func_t toboolFuncs[] = {
        number_tobool,
        string_tobool,
        bool_tobool,
        table_tobool,
        userfunc_tobool,
        libfunc_tobool,
        nil_tobool,
        undef_tobool

};

unsigned char number_tobool(avm_memcell* m){return (m->data.numVal) ? 1 : 0;}
unsigned char string_tobool(avm_memcell* m){return m->data.strVal[0]!=0;}
unsigned char bool_tobool(avm_memcell* m){return m->data.boolVal;}
unsigned char table_tobool(avm_memcell* m){return 1;}
unsigned char userfunc_tobool(avm_memcell* m){return 1;}
unsigned char libfunc_tobool(avm_memcell* m){return 1;}
unsigned char nil_tobool(avm_memcell* m){return 0;}
unsigned char undef_tobool(avm_memcell* m){return 0;}

unsigned char avm_tobool(avm_memcell* m){
        assert(m->type >=0  && m->type < undef_m);
        return (*toboolFuncs[m->type])(m);
}

check_eq_func_t check_eqFuncs[] = {
        number_check_eq,
        string_check_eq,
        0,
        table_check_eq,
        userfunc_check_eq,
        libfunc_check_eq,
        0,
        0

};

unsigned char number_check_eq(avm_memcell* rv1,avm_memcell* rv2){
        return (rv1->data.numVal == rv2->data.numVal);
}
unsigned char string_check_eq(avm_memcell* rv1,avm_memcell* rv2){
        return unsigned(strcmp(rv1->data.strVal,rv2->data.strVal));
}
unsigned char table_check_eq(avm_memcell* rv1,avm_memcell* rv2){
        /*TO BE CONTINUED */
        return 0;
}
unsigned char userfunc_check_eq(avm_memcell* rv1,avm_memcell* rv2){ //??
        return (rv1->data.funcVal == rv2->data.funcVal);
}
unsigned char libfunc_check_eq(avm_memcell* rv1,avm_memcell* rv2){
        return unsigned(strcmp(rv1->data.libfuncVal,rv2->data.libfuncVal));
}

check_le_func_t check_leFuncs[] = {
        number_check_le,
        string_check_le,
        0,
        table_check_le,
        userfunc_check_le,
        libfunc_check_le,
        0,
        0

};

unsigned char number_check_le(avm_memcell* rv1,avm_memcell* rv2){
        return (rv1->data.numVal <= rv2->data.numVal);
}
unsigned char string_check_le(avm_memcell* rv1,avm_memcell* rv2){
        return unsigned(strcmp(rv1->data.strVal,rv2->data.strVal));
}
unsigned char table_check_le(avm_memcell* rv1,avm_memcell* rv2){
        /*TO BE CONTINUED */
        return 0;
}
unsigned char userfunc_check_le(avm_memcell* rv1,avm_memcell* rv2){ //??
        return (rv1->data.funcVal <= rv2->data.funcVal);
}
unsigned char libfunc_check_le(avm_memcell* rv1,avm_memcell* rv2){
        return unsigned(strcmp(rv1->data.libfuncVal,rv2->data.libfuncVal));
}

check_ge_func_t check_geFuncs[] = {
        number_check_ge,
        string_check_ge,
        0,
        table_check_ge,
        userfunc_check_ge,
        libfunc_check_ge,
        0,
        0

};

unsigned char number_check_ge(avm_memcell* rv1,avm_memcell* rv2){
        return (rv1->data.numVal >= rv2->data.numVal);
}
unsigned char string_check_ge(avm_memcell* rv1,avm_memcell* rv2){
        return unsigned(strcmp(rv1->data.strVal,rv2->data.strVal));
}
unsigned char table_check_ge(avm_memcell* rv1,avm_memcell* rv2){
        /*TO BE CONTINUED */
        return 0;
}
unsigned char userfunc_check_ge(avm_memcell* rv1,avm_memcell* rv2){ //??
        return (rv1->data.funcVal >= rv2->data.funcVal);
}
unsigned char libfunc_check_ge(avm_memcell* rv1,avm_memcell* rv2){
        return unsigned(strcmp(rv1->data.libfuncVal,rv2->data.libfuncVal));
}