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

void libfunc_input(void){
        std::string input;       
        avm_memcellclear(&retval);
        std::cin >> input;
        std::istringstream iss(input);
        double d;
        int flag = 0; //0 string - 1 double - 2 integer -3 bool - 4 nil
        iss >> std::noskipws >> d; // noskipws considers leading whitespace invalid        
      
        if(flag == 0){ //Integer
                for(int i = 0; i < input.size();i++){
                        flag = (std::isdigit(input[i])) ? 2 : 0;
                        if(flag == 0){ break ;}
                }
                if(flag == 2){
                        retval.type = number_m;
                        retval.data.numVal = std::stoi(input);
                        return;
                }
              
        
        }else if(iss.eof() && !iss.fail()){//Double - Check the entire string was consumed and if either failbit or badbit is set         
                flag = 1;
                retval.type = number_m;
                retval.data.numVal = std::stod(input);
                return;
        }       

        if(flag == 0){
                if (input.find("true") != std::string::npos || input.find("TRUE") != std::string::npos) {
                        flag = 3;
                        retval.type = bool_m;
                        retval.data.boolVal = 1;
                        return;
                }else if(input.find("false") != std::string::npos || input.find("FALSE") != std::string::npos){
                        flag = 3;
                        retval.type = bool_m;
                        retval.data.boolVal = 0;
                        return;
                }else if(input.find("nil") != std::string::npos){
                        flag = 4;
                        retval.type = nil_m;
                        return;
                }else{
                        retval.type = string_m;
                        retval.data.strVal = strdup(const_cast<char*>(input.c_str()));
                        return;
                }
        }
       
}

void libfunc_objecttotalmembers(void){
        unsigned n = avm_totalactuals();

	if(n!=1){
		avm_error("one argument (not %d) expected in 'typeof'!",n);
	}else{
		avm_memcellclear(&retval);
		avm_table_bucket * tempTableList = avm_getactual(0)->data.tableVal->head;
                int memberCounter = 0;

                while(tempTableList){ 
                        memberCounter++;
                        tempTableList = tempTableList->nextOrder;
                }
                retval.type = number_m;
                retval.data.numVal = memberCounter;
	}
}

void libfunc_argument(void){
        unsigned n = avm_totalactuals();
        unsigned p_topsp = avm_getenvvalue(topsp + AVM_SAVEDTOPSP_OFFSET);

        if(n!=1){
		avm_error("One argument (not %d) expected in 'argument'!",n);
	}else{
		if(!p_topsp){
		        avm_error("'argument' called outside a function!");
		        retval.type = nil_m;
	        }else{
		        retval.type = number_m;
                        for(int i=AVM_STACKSIZE-1;i>=0;i--){
		        if(stack[i].type != undef_m)
			        std::cout<<avm_tostring(&stack[i])<<std::endl;
	                }
                        unsigned int pos = p_topsp + avm_getactual(0)->data.numVal +  AVM_NUMACTUALS_OFFSET;
                        retval.data.numVal = stack[pos].data.numVal;//avm_getactual(p_topsp + avm_getactual(0)->data.numVal)->data.numVal;
                        
                        if(avm_getactual(0)->data.numVal <= avm_getenvvalue(p_topsp + AVM_NUMACTUALS_OFFSET)){
                                //retval.data.numVal = avm_getactual(p_topsp + avm_getactual(0)->data.numVal)->data.numVal;
        
                        }
                        
	        }
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