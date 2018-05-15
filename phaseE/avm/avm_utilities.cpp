#include "headers/avm.h"

double  consts_getnumber(unsigned u){}
char*   consts_getstring(unsigned u){}
char*   libfuncs_getused(unsigned u){}

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
                        reg->data.strVal = strdup(consts_getstring(arg->val));
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
                default:        assert(0);
        }
}

static void avm_initstack(void){}

void avm_dec_top(void){
        if(!top){
//              avm_error("stack overflow\n");
                executionFinished=1;
        }
        else
                --top;
}

userfunc* avm_getfuncinfo(unsigned address){

}

void avm_warning(char* format,...){}
void avm_error(char*,...){}

void avm_callsaveenviroment(void){
        avm_pushenvvalue(totalActuals);
        avm_pushenvvalue(pc+1);
        avm_pushenvvalue(top + totalActuals + 2);
        avm_pushenvvalue(topsp);
}

void avm_assign(avm_memcell* lv,avm_memcell* rv){

        if(lv == rv)
                return;

        if (lv->type == table_m &&
            rv->type == table_m &&
            lv->data.tableVal == rv->data.tableVal)
                return;

        if(rv->type == undef_m){
                //avm_warning("assigning from 'undef' content!");
        }

        avm_memcellclear(lv);

        std::memcpy(lv,rv,sizeof(avm_memcell));

        if( lv->type == string_m)
                lv->data.strVal = strdup(rv->data.strVal);
        else
        if ( lv->type == table_m)
                avm_tableincrefcounter(lv->data.tableVal);
}


void avm_pushenvvalue(unsigned val){
        stack[top].type = number_m;
        stack[top].data.numVal = val;
        avm_dec_top();
}

unsigned avm_getenvvalue(unsigned i){
        assert(stack[i].type = number_m);
        unsigned val = (unsigned) stack[i].data.numVal;
        assert(stack[i].data.numVal == ((double) val));
        return val;
}

void avm_initialize(void){
        avm_initstack();

        avm_registerlibfunc("print",libfunc_print);
        avm_registerlibfunc("typeof",libfunc_typeof);
        avm_registerlibfunc("totalarguments",libfunc_totalarguments);
}

void execute_cycle(void){
        if(executionFinished){
                return;
        }else
        if (pc == AVM_ENDING_PC){
                executionFinished  = 1;
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

