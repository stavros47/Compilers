#include "headers/avm.h"

void avm_calllibfunc(char* funcname){
        library_func_t f = avm_getlibraryfunc(funcname);
        if(!f){
                avm_error("unsupported lib func '%s' called!",funcname);
        }else{
                topsp = top;
                totalActuals = 0;
                (*f)();
                if(!executionFinished){
                        execute_funcexit((instruction*)0);
                }
        }
}

library_func_t avm_getlibraryfunc(char* id){
        std::unordered_map<std::string,library_func_t>::iterator it;

        it = registry.find(id);

        if(it!=registry.end())
                return it->second;
         
        return NULL;
}

unsigned avm_totalactuals(void){
        return avm_getenvvalue(topsp + AVM_NUMACTUALS_OFFSET);
}

avm_memcell* avm_getactual(unsigned i){
        assert(i<avm_totalactuals());
        return &stack[topsp + i +  AVM_STACKENV_SIZE+ 1];
}

void avm_registerlibfunc(std::string id,library_func_t addr){
        registry.insert({id,addr});
}

void libfunc_print(void){
        unsigned n = avm_totalactuals();
        for(unsigned i = 0; i < n; ++i){
                std::string s = avm_tostring(avm_getactual(i));
                std::cout<<s;
        }
}

void libfunc_typeof(void){
	unsigned n = avm_totalactuals();

	if(n!=1){
		avm_error("one argument (not %d) expected in 'typeof'!",n);
	}else{
		avm_memcellclear(&retval);
		retval.type = string_m;
		retval.data.strVal = strdup(typeStrings[avm_getactual(0)->type].c_str());
	}
}

void libfunc_totalarguments(void){
	unsigned p_topsp = avm_getenvvalue(topsp + AVM_SAVEDTOPSP_OFFSET);
	avm_memcellclear(&retval);

	if(!p_topsp){
		avm_error("totalarguments' called outside a function!");
		retval.type = nil_m;
	}else{
		retval.type = number_m;
		retval.data.numVal = avm_getenvvalue(p_topsp + AVM_NUMACTUALS_OFFSET);
	}
}

void libfunc_sin(void){
        unsigned n = avm_totalactuals();

        if(n!=1){
		avm_error("one argument (not %d) expected in 'sin'!",n);
	}else{
                if(avm_getactual(0)->type!=number_m){
                        avm_error("numeric argument expected in 'sin'!",n);
                }
                else{
		avm_memcellclear(&retval);
		retval.type = number_m;
		retval.data.numVal = sin(avm_getactual(0)->data.numVal*(3.1415 / 180));
                }
	}
}

void libfunc_cos(void){
        unsigned n = avm_totalactuals();

        if(n!=1){
		avm_error("one argument (not %d) expected in 'cos'!",n);
	}else{
                if(avm_getactual(0)->type!=number_m)
                        avm_error("numeric argument expected in 'cos'!",n);
                else{
		avm_memcellclear(&retval);
		retval.type = number_m;
		retval.data.numVal = cos(avm_getactual(0)->data.numVal*(3.1415 / 180));
                }
	}
}

void libfunc_sqrt(void){
        unsigned n = avm_totalactuals();

        if(n!=1){ 
		avm_error("one argument (not %d) expected in 'sqrt'!",n);
	}else{
                if(avm_getactual(0)->data.numVal<0)
                        avm_error("argument expected possitive in 'sqrt'!",n);
                if(avm_getactual(0)->type==string_m)
                        avm_error("numeric argument expected in 'sqrt'!",n);
                else{
		avm_memcellclear(&retval);
		retval.type = number_m;
		retval.data.numVal = sqrt(avm_getactual(0)->data.numVal);
                }
	}
}

void libfunc_strtonum(void){
        unsigned n = avm_totalactuals();
        //check error from stavros       
        if(n!=1){ 
		avm_error("one argument (not %d) expected in 'sqrt'!",n);
	}else{
                if(avm_getactual(0)->type!=string_m){
                        avm_error("Type is wrong, expected string\n");
                }
                avm_memcellclear(&retval);
                retval.type = number_m;
                retval.data.numVal = std::stod(avm_getactual(0)->data.strVal);
        }
}