#include "headers/avm.h"

void execute_jeq(instruction* instr){
        assert(instr->result.type == label_a);
        avm_memcell* rv1 = avm_translate_operand(&instr->arg1,&ax);
        avm_memcell* rv2 = avm_translate_operand(&instr->arg2,&bx);
        unsigned char result = 0;
        result = jump_eqChecks(rv1,rv2);
                
        if(!executionFinished && result)
                pc = instr->result.val;
        
}

void execute_jne(instruction* instr){
        assert(instr->result.type == label_a);
        avm_memcell* rv1 = avm_translate_operand(&instr->arg1,&ax);
        avm_memcell* rv2 = avm_translate_operand(&instr->arg2,&bx);
        unsigned char result = 0;

        result = jump_eqChecks(rv1,rv2);
                
        if(!executionFinished && !result)
                pc = instr->result.val;
}

void execute_jle(instruction* instr){
        assert(instr->result.type == label_a);
        avm_memcell* rv1 = avm_translate_operand(&instr->arg1,&ax);
        avm_memcell* rv2 = avm_translate_operand(&instr->arg2,&bx);
        unsigned char result = 0;

        result = jump_leChecks(rv1,rv2);
                
        if(!executionFinished && result)
                pc = instr->result.val;

}

void execute_jge(instruction* instr){
        assert(instr->result.type == label_a);
        avm_memcell* rv1 = avm_translate_operand(&instr->arg1,&ax);
        avm_memcell* rv2 = avm_translate_operand(&instr->arg2,&bx);
        unsigned char result = 0;

        result = jump_geChecks(rv1,rv2);
                
        if(!executionFinished && result)
                pc = instr->result.val;
}

void execute_jlt(instruction* instr){
        assert(instr->result.type == label_a);
        avm_memcell* rv1 = avm_translate_operand(&instr->arg1,&ax);
        avm_memcell* rv2 = avm_translate_operand(&instr->arg2,&bx);
        unsigned char result = 0;
        result = jump_geChecks(rv1,rv2);
                
        if(!executionFinished && !result)
                pc = instr->result.val;
}

void execute_jgt(instruction* instr){
        assert(instr->result.type == label_a);
        avm_memcell* rv1 = avm_translate_operand(&instr->arg1,&ax);
        avm_memcell* rv2 = avm_translate_operand(&instr->arg2,&bx);
        unsigned char result = 0;

        result = jump_leChecks(rv1,rv2);
                
        if(!executionFinished && !result)
                pc = instr->result.val;

}

unsigned char jump_eqChecks(avm_memcell* rv1,avm_memcell* rv2){
        
        if(rv1->type == undef_m || rv2->type == undef_m){
                avm_error("[%d]'undef' involved in equality!\n",currLine);
        }else
        if(rv1->type == bool_m || rv2->type == bool_m){

                return (avm_tobool(rv1) == avm_tobool(rv2));
        }else
        if(rv1->type == nil_m || rv2->type == nil_m){
                return (avm_tobool(rv1) == avm_tobool(rv2));
        }else
        if(rv1->type != rv2->type){
        avm_error("[%d]%s==%s is illegal!\n",currLine,
                typeStrings[rv1->type],
                typeStrings[rv2->type]);
        }else{
                
                check_eq_func_t f = check_eqFuncs[rv1->type];
                if(f){
                        return (*f)(rv1,rv2);
                }else {
                        assert(0);
                }
        }
}

unsigned char jump_leChecks(avm_memcell* rv1,avm_memcell* rv2){ //??
        if(rv1->type == undef_m || rv2->type == undef_m){
                avm_error("[%d]'undef' involved in equality!\n",currLine);
        }else
        if(rv1->type == bool_m || rv2->type == bool_m){
                return (avm_tobool(rv1) <= avm_tobool(rv2));
        }else
        if(rv1->type == nil_m || rv2->type == nil_m){
                return (avm_tobool(rv1) <= avm_tobool(rv2));
        }else
        if(rv1->type != rv2->type){
        avm_error("[%d]%s<=%s is illegal!\n",currLine,
                typeStrings[rv1->type],
                typeStrings[rv2->type]);
        }else{
                check_eq_func_t f = check_leFuncs[rv1->type];
                if(f){
                        return (*f)(rv1,rv2);
                }else {
                        assert(0);
                }
        }
}

unsigned char jump_geChecks(avm_memcell* rv1,avm_memcell* rv2){ //??
        if(rv1->type == undef_m || rv2->type == undef_m){
                avm_error("[%d]'undef' involved in equality!\n",currLine);
        }else
        if(rv1->type == bool_m || rv2->type == bool_m){
                return (avm_tobool(rv1) >= avm_tobool(rv2));
        }else
        if(rv1->type == nil_m || rv2->type == nil_m){
                return (avm_tobool(rv1) >= avm_tobool(rv2));
        }else
        if(rv1->type != rv2->type){
        avm_error("[%d]%s>=%s is illegal!\n",currLine,
                typeStrings[rv1->type],
                typeStrings[rv2->type]);
        }else{
                check_eq_func_t f = check_geFuncs[rv1->type];
                if(f){
                        return (*f)(rv1,rv2);
                }else {
                        assert(0);
                }
        }
}
