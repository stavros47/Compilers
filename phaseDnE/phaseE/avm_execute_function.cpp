#include "headers/avm.h"

void execute_call( instruction* instr){
        avm_memcell* func = avm_translate_operand(&instr->result,&ax);
        assert(func);
        avm_callsaveenviroment();
        switch( func->type){
                case userfunc_m:        {
                        pc = avm_getfuncinfo(func->data.funcVal)->address;
                        assert(pc<AVM_ENDING_PC);
                        assert(code[pc].opcode == funcenter_v);
                        break;
                }
                case string_m:  {
                        avm_calllibfunc(func->data.strVal);
                        break;
                }
                case libfunc_m: {
                        avm_calllibfunc(func->data.libfuncVal);
                        break;
                }
                case table_m:   {
                        avm_memcell* t = &stack[top + AVM_STACKENV_SIZE];
                        unsigned i =0;
                        for(i = top;i<top+AVM_STACKENV_SIZE;i++){
                                avm_assign(&stack[i],&stack[i+1]);
                        }
                        avm_assign(&stack[i],func);
                        stack[i-1].data.numVal++;
                        avm_dec_top();
                        pc = avm_getfuncinfo(get(func->data.tableVal->strIndexed[hashFunction("()")],"()")->data.funcVal)->address;
                        assert(pc<AVM_ENDING_PC);
                        assert(code[pc].opcode == funcenter_v);
                        break;
                }        
                default:                {
                        char* s = const_cast<char*>(avm_tostring(func).c_str());
                        avm_error("call:cannot bind '%s' to function!",s);
                        //free(s);
                }
        }
}

void execute_pusharg(instruction* instr){
        avm_memcell* arg = avm_translate_operand(&instr->result,&ax);
        assert(arg);
        avm_assign(&stack[top],arg);
        ++totalActuals;
        avm_dec_top();
}

void execute_funcenter(instruction* instr){
        avm_memcell* func = avm_translate_operand(&instr->result,&ax);
        assert(func);
        assert(pc==avm_getfuncinfo(func->data.funcVal)->address);

        totalActuals = 0;
        userfunc* funcInfo = avm_getfuncinfo(func->data.funcVal);
        topsp = top;
        top = top - funcInfo -> localSize;
}

void execute_funcexit(instruction* instr){
        unsigned oldTop = top;

        top = avm_getenvvalue(topsp + AVM_SAVEDTOP_OFFSET);
        pc = avm_getenvvalue(topsp + AVM_SAVEDPC_OFFSET);
        topsp = avm_getenvvalue(topsp + AVM_SAVEDTOPSP_OFFSET);

        while(oldTop++<=top){
                avm_memcellclear(&stack[oldTop]);
        }
}

