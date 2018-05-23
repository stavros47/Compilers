#include "headers/avm.h"

execute_func_t executeFuncs[]= {
         execute_assign,
         execute_add,
         execute_sub,
         execute_mul,
         execute_div,
         execute_mod,
         execute_jeq,
         execute_jne,
         execute_jle,
         execute_jge,
         execute_jlt,
         execute_jgt,
         execute_call,
         execute_pusharg,
         execute_funcenter,
         execute_funcexit,
         execute_newtable,
         execute_tablegetelem,
         execute_tablesetelem,
         execute_nop,
};

void execute_arithmetic(instruction* instr){
        avm_memcell* lv = avm_translate_operand(&instr->result,(avm_memcell*)0);
        avm_memcell* rv1 = avm_translate_operand(&instr->arg1,&ax);
        avm_memcell* rv2 = avm_translate_operand(&instr->arg2,&bx);

        assert(lv && (&stack[AVM_STACKSIZE] > lv && &stack[top] < lv || lv ==&retval));
        assert(rv1 && rv2);

        if(rv1->type != number_m || rv2->type != number_m){
                avm_error("not a number in arithmetic\n");
                executionFinished=1;
        }else{
                arithmetic_func_t op = arithmeticFuncs[instr->opcode - add_v];
                avm_memcellclear(lv);
                lv->type = number_m;
                lv->data.numVal = (*op)(rv1->data.numVal,rv2->data.numVal);
        }
}

void execute_assign(instruction* instr){
        avm_memcell* lv = avm_translate_operand(&instr->result, (avm_memcell*)0);
        avm_memcell* rv = avm_translate_operand(&instr->arg1 , &ax);

        assert(lv);
        assert(((&stack[AVM_STACKSIZE] > lv && &stack[top] < lv) || lv == &retval));
        assert(rv);

        avm_assign(lv,rv);
}

void execute_nop(instruction* instr){}



