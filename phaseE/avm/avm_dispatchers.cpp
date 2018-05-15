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

char* number_tostring(avm_memcell* m){
}

char* string_tostring(avm_memcell* m){
}

char* bool_tostring(avm_memcell* m){
}

char* table_tostring(avm_memcell* m){
}

char* userfunc_tostring(avm_memcell* m){
}

char* libfunc_tostring(avm_memcell* m){
}

char* nil_tostring(avm_memcell* m){
}

char* undef_tostring(avm_memcell* m){
}

char* avm_tostring(avm_memcell* m){
        assert(m->type >=0 && m->type < undef_m);
        return (*tostringFuncs[m->type])(m);
}

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
double div_impl(double x,double y){return x/y;}//ERROR CHECK (x/0)
double mod_impl(double x,double y){return (unsigned)x%(unsigned)y;}//ERROR CHECK


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

unsigned char number_tobool(avm_memcell* m){}
unsigned char string_tobool(avm_memcell* m){}
unsigned char bool_tobool(avm_memcell* m){}
unsigned char table_tobool(avm_memcell* m){}
unsigned char userfunc_tobool(avm_memcell* m){}
unsigned char libfunc_tobool(avm_memcell* m){}
unsigned char nil_tobool(avm_memcell* m){}
unsigned char undef_tobool(avm_memcell* m){}

unsigned char avm_tobool(avm_memcell* m){
        assert(m->type >=0  && m->type < undef_m);
        return (*toboolFuncs[m->type])(m);
}



