#include "headers/avm.h"
#include <stdarg.h>
avm_memcell stack[AVM_STACKSIZE];

const char* typeStrings[] = {
        "number_m",
        "string_m",
        "bool_m",
        "table_m",
        "userfunc_m",
        "libfunc_m",
        "nil_m",
        "undef_m"
};

double  consts_getnumber(unsigned u){
        return numConsts[u];
}

char*   consts_getstring(unsigned u){
        return const_cast<char*>(strConsts[u].c_str());
}

char*   libfuncs_getused(unsigned u){
        return const_cast<char*>(libFuncs[u].c_str());
}

userfunc* avm_getfuncinfo(unsigned u){
        return userFuncs[u];
}

avm_memcell* avm_translate_operand(vmarg* arg,avm_memcell* reg){
        switch(arg->type){
                case global_a:  return &stack[AVM_STACKSIZE - 1 - arg->val];
                case local_a:   return &stack[topsp - arg->val];
                case formal_a:  return &stack[topsp + AVM_STACKENV_SIZE + 1 + arg->val];
                case retval_a:  return &retval;
                case number_a:  {
                        reg->type = number_m;
                        reg->data.numVal = consts_getnumber(arg->val);
                        return reg;
                }
                case string_a:  { 
                        reg->type = string_m;
                        reg->data.strVal = consts_getstring(arg->val);
                        return reg;
                }
                case bool_a:    { 
                        reg->type = bool_m; 
                        reg->data.boolVal = arg->val;
                        return reg;
                }
                case nil_a:     { 
                        reg->type = nil_m;
                        return reg;
                }
                case userfunc_a: {
                        reg->type = userfunc_m;
                        reg->data.funcVal = arg->val;
                        return reg;
                }
                case libfunc_a: { 
                        reg->type = libfunc_m; 
                        reg->data.libfuncVal = libfuncs_getused(arg->val);
                        return reg;
                }
                default:       std::cout<<pc<<std::endl<<arg->type<<std::endl; assert(0);
        }
}

static void avm_initstack(void){
        for(unsigned i = 0; i<AVM_STACKSIZE; ++i){
                AVM_WIPEOUT(stack[i]);
                stack[i].type = undef_m;
        }
}

void avm_warning(const char* fmt,...){
        va_list args;
        va_start(args, fmt);
        std::cout<<"[WARNING]:";
        while (*fmt != '\0') {
                if(*fmt == '%'){
                        ++fmt;
                        if (*fmt == 'd') {
                                int i = va_arg(args, int);
                                printf("%d", i);
                        } else if (*fmt == 'c') {
                                // note automatic conversion to integral type
                                int c = va_arg(args, int);
                                printf("%c", c);
                        } else if (*fmt == 'f') {
                                double d = va_arg(args, double);
                                printf("%f", d);
                        } else if(*fmt == 's'){
                                char* s = va_arg(args,char*);
                                printf("%s",s);
                        }else{
                                printf("%%");
                                printf("%c",*fmt);                        
                        }
                        
                }else{
                        printf("%c",*fmt);
                }
                ++fmt;
        }
        va_end(args);
}

void avm_error(const char* fmt,...){
        executionFinished=1;
        va_list args;
        va_start(args, fmt);
        std::cout<<"[ERROR]:";
        while (*fmt != '\0') {
                if(*fmt == '%'){
                        ++fmt;
                        if (*fmt == 'd') {
                                int i = va_arg(args, int);
                                printf("%d", i);
                        } else if (*fmt == 'c') {
                                // note automatic conversion to integral type
                                int c = va_arg(args, int);
                                printf("%c", c);
                        } else if (*fmt == 'f') {
                                double d = va_arg(args, double);
                                printf("%f", d);
                        } else if(*fmt == 's'){
                                char* s = va_arg(args,char*);
                                printf("%s",s);
                        }else{
                                printf("%%");
                                printf("%c",*fmt);                        
                        }
                        
                }else{
                        printf("%c",*fmt);
                }
                ++fmt;
        }
        va_end(args);
}

void avm_callsaveenviroment(void){
        avm_pushenvvalue(totalActuals);
        avm_pushenvvalue(pc+1);
        avm_pushenvvalue(topsp);
        avm_pushenvvalue(top + totalActuals + 2);        
}

void copy_to_from(avm_table* dest,avm_table* src){
        avm_table_bucket *tmp,*s = src->head;
        
        while(s){
                switch(s->key.type){
                        case number_m:  
                                tmp=insert(dest->numIndexed,hashFunction(s->key.data.numVal),s->key,s->value);
                                break;
                        case string_m:  
                                tmp=insert(dest->strIndexed,hashFunction(s->key.data.strVal),s->key,s->value);
                                break;
                        case bool_m:  
                                tmp=insert(dest->boolIndexed,hashFunction(s->key.data.boolVal),s->key,s->value);
                                break;
                        case userfunc_m:  
                                tmp=insert(dest->userfuncIndexed,hashFunction(avm_getfuncinfo(s->key.data.funcVal)->address),s->key,s->value);
                                break;
                        case libfunc_m:  
                                tmp=insert(dest->libfuncIndexed,hashFunction(s->key.data.libfuncVal),s->key,s->value);
                                break;
                        case table_m:  
                                tmp=insert(dest->tableIndexed,hashFunction(s->key.data.tableVal),s->key,s->value);
                                break;
                        default : assert(0);
                }
                if(tmp){
                        dest->total++;
                        avm_table_bucket* t = dest->head;
                        if(!t) dest->head = tmp;
                        else{

                                while(t->nextOrder){
                                        t=t->nextOrder;
                                }
                                t->nextOrder=tmp;
                        }
                        tmp->nextOrder=NULL;
                        
                }
                s=s->nextOrder;
        }
}

void copy_to(avm_table* dest,avm_table* src){
        copy_deeptohash(dest->numIndexed,src->numIndexed);
        copy_deeptohash(dest->strIndexed,src->strIndexed);
        copy_deeptohash(dest->boolIndexed,src->boolIndexed);
        copy_deeptohash(dest->userfuncIndexed,src->userfuncIndexed);
        copy_deeptohash(dest->libfuncIndexed,src->libfuncIndexed);
        copy_deeptohash(dest->tableIndexed,src->tableIndexed);
        dest -> refCounter = src -> refCounter;
        dest -> total = src -> total;
        dest -> head = src -> head;
}

void copy_deeptohash(avm_table_bucket** dest,avm_table_bucket** src){
        for(unsigned i = 0; i< AVM_TABLE_HASHSIZE;i++){
                avm_table_bucket* s=src[i];
                avm_table_bucket* dest_b=dest[i];
                while(s){

                        if(s->value.type == string_m){
                                dest_b->value.data.strVal=strdup(s->value.data.strVal);                           
                        }else if(s->value.type == libfunc_m){
                                dest_b->value.data.libfuncVal=strdup(s->value.data.libfuncVal);                           
                        }else if(s->value.type == table_m){
                                copy_to(dest_b->value.data.tableVal,s->value.data.tableVal);
                        }else{
                                avm_assign(&dest_b->value,&s->value);
                        }

                        if(s->key.type == string_m){
                                dest_b->key.data.strVal=strdup(s->key.data.strVal);                                                        
                        }else if(s->value.type == libfunc_m){
                                dest_b->key.data.libfuncVal=strdup(s->key.data.libfuncVal);                           
                        }else if(s->key.type == table_m){
                                copy_to(dest_b->key.data.tableVal,s->key.data.tableVal);                                
                        }else{
                                avm_assign(&dest_b->key,&s->key);                                
                        }

                        s=s->next; 
                }
        }
}

void avm_assign(avm_memcell* lv,avm_memcell* rv){

        if(lv == rv)
                return;

        if (lv->type == table_m &&
            rv->type == table_m &&
            lv->data.tableVal == rv->data.tableVal)
                return;
        if(rv->type == undef_m){
                avm_warning("[%d]assigning from 'undef' content!\n",currLine);
        }
 
        avm_memcellclear(lv);
        std::memcpy(lv,rv,sizeof(avm_memcell));

        if(lv==&retval){
                if(rv->type==table_m){
                        //if any (char*) value exists in hashtables
                        copy_to(lv->data.tableVal,rv->data.tableVal);
                }
        }

        if( lv->type == string_m)
                lv->data.strVal = strdup(rv->data.strVal);
        else
        if ( lv->type == table_m)
                avm_tableincrefcounter(lv->data.tableVal);
        
}

void avm_dec_top(void){
        if(!top){
                avm_error("[%d]stack overflow\n",currLine);
                executionFinished=1;
        }
        else
                --top;
        
}

void avm_pushenvvalue(unsigned val){
        stack[top].type = number_m;
        stack[top].data.numVal = val;
        avm_dec_top();
}

unsigned avm_getenvvalue(unsigned i){
        assert(stack[i].type == number_m);
        unsigned val = (unsigned) stack[i].data.numVal;
        assert(stack[i].data.numVal == ((double) val));
        return val;
}

void avm_initialize(void){
        avm_initstack();

        /* offsets start from 0    *
         * AVM_STACKSIZE 4096(N-1) */
        top = topsp = AVM_STACKSIZE - 1 - (max_global_offset+1);

        avm_registerlibfunc("print",libfunc_print);
        avm_registerlibfunc("typeof",libfunc_typeof);
        avm_registerlibfunc("totalarguments",libfunc_totalarguments);
        avm_registerlibfunc("input",libfunc_input);
        avm_registerlibfunc("objecttotalmembers",libfunc_objecttotalmembers);
        avm_registerlibfunc("argument",libfunc_argument);
        avm_registerlibfunc("sin",libfunc_sin);
        avm_registerlibfunc("cos",libfunc_cos);
        avm_registerlibfunc("sqrt",libfunc_sqrt);
        avm_registerlibfunc("strtonum",libfunc_strtonum);
        avm_registerlibfunc("objectmemberkeys",libfunc_objectmemberkeys);
        avm_registerlibfunc("objectcopy",libfunc_objectcopy);
}

void execute_cycle(void){
        if(executionFinished){
                std::cout<<"executionFinished\n"<<executionFinished<<"\n";
                return;
        }else
        if (pc == AVM_ENDING_PC){
                executionFinished  = 1;
                std::cout<<"\npc == AVM_ENDING_PC\n";
                return;
        } else{
                assert(pc < AVM_ENDING_PC);
                instruction* instr = code + pc;

                assert(
                        instr->opcode >= 0 &&
                        instr->opcode <= AVM_MAX_INSTRUCTIONS
                );
                if(instr->srcLine)
                        currLine = instr->srcLine;
                unsigned oldPC = pc;
                (*executeFuncs[instr->opcode])(instr);
                if(pc==oldPC)   ++pc;
        }
}

void test_global(vmarg r){
	if(r.type == global_a){
		if(r.val>max_global_offset)
			max_global_offset=r.val;
	}
}

void expand_instr(void){
	instruction* p = new instruction[I_NEW_SIZE];
	if(code){
		std::memcpy(p,code,I_CURR_SIZE);
		delete[] code;
	}
	code = p;
	totalInstr+=I_EXPAND_SIZE;
}

void print_stack(){
	for(int i=AVM_STACKSIZE-1;i>=0;i--){
		if(stack[i].type != undef_m)
			std::cout<<"["<<i<<"]:"<<avm_tostring(&stack[i])<<std::endl;
	}
}

void print_info(){
	std::cout<<"string consts\n";
	for(std::string i : strConsts)
		std::cout<<"\t"<<i<<std::endl;
	std::cout<<"num consts\n";
	for(double i : numConsts)
		std::cout<<"\t"<<i<<std::endl;
	std::cout<<"lib funcs\n";
	for(std::string i : libFuncs)
		std::cout<<"\t"<<i<<std::endl;
	std::cout<<"userfuncs\n";
	for(userfunc* i : userFuncs)
		std::cout<<"\t"<<i->id<<"\t"<<i->address<<"\t"<<i->localSize<<std::endl;
	for(int i=1;i<codeSize;i++){
		printf("%d:", i);
		//printf("%d:", code[i].srcLine);
		printf("\t%d", code[i].opcode);
		printf("\t%d:", code[i].result.type);
		printf("%d", code[i].result.val);
		printf("\t%d:", code[i].arg1.type);
		printf("%d", code[i].arg1.val);
		printf("\t%d:", code[i].arg2.type);
		printf("%d\n", code[i].arg2.val);
	}
}