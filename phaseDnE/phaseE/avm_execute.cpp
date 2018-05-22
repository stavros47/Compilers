#include "headers/avm.h"

execute_func_t executeFuncs[]= {
         execute_assign,
         execute_add,
         execute_sub,
         execute_mul,
         execute_div,
         execute_mod,
         execute_not,
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

void execute_call( instruction* instr){
        avm_memcell* func = avm_translate_operand(&instr->result,&ax);
        assert(func);
        avm_callsaveenviroment();

        switch( func->type){
                case userfunc_m:        {
                        pc =avm_getfuncinfo(func->data.funcVal)->address;
                        assert(pc<AVM_ENDING_PC);
                        assert(code[pc].opcode == funcenter_v);
                        break;
                }

                case string_m:          {
                                avm_calllibfunc(func->data.strVal);
                                break;
                }

                case libfunc_m:         {
                                avm_calllibfunc(func->data.libfuncVal);
                                break;
                }
                //case table_m:
                                
                default:                {
                        char* s = const_cast<char*>(avm_tostring(func).c_str());
                        avm_error("call:cannot bind '%s' to function!",s);
                        //free(s);
                }
        }
}

void execute_not(instruction* instr){}////////////////////////////////////////

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

void execute_jgt(instruction* instr){
        assert(instr->result.type == label_a);
        avm_memcell* rv1 = avm_translate_operand(&instr->arg1,&ax);
        avm_memcell* rv2 = avm_translate_operand(&instr->arg2,&bx);
        unsigned char result = 0;

        result = jump_leChecks(rv1,rv2);
                
        if(!executionFinished && !result)
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

        while(oldTop++<=top)
                avm_memcellclear(&stack[oldTop]);
}

void execute_newtable    (instruction* instr){
        avm_memcell* lv = avm_translate_operand(&instr->result,(avm_memcell*)0);
        assert(lv && (&stack[AVM_STACKSIZE] > lv && &stack[top] < lv || lv == &retval));

        avm_memcellclear(lv);

        lv->type = table_m;
        lv->data.tableVal = avm_tablenew();
        avm_tableincrefcounter(lv->data.tableVal);
}

void execute_tablegetelem(instruction* instr){
        avm_memcell* lv = avm_translate_operand(&instr->result,(avm_memcell*)0);
        avm_memcell* table = avm_translate_operand(&instr->arg1,(avm_memcell*)0);
        avm_memcell* key = avm_translate_operand(&instr->arg2,&ax);

        assert(lv && (&stack[AVM_STACKSIZE] > lv && &stack[top] < lv || lv ==&retval));
        assert(table && (&stack[AVM_STACKSIZE] > table && &stack[top] < table));
        assert(key);

        avm_memcellclear(lv);
        lv->type = nil_m;

        if(table->type !=table_m){
                avm_error("illegal use of type %s as table!",typeStrings[table->type]);
                executionFinished=1;
        }else{
                avm_memcell* content = avm_tablegetelem(table->data.tableVal,key);
                if(content)
                        avm_assign(lv,content);
                else{
                        char* ks = const_cast<char*>(avm_tostring(table).c_str());
                        char* vs = const_cast<char*>(avm_tostring(key).c_str());

                        avm_warning("%s[%s] not found!",ks,vs);
                        // free(ks);
                        // free(vs);
                }
        }
}

void execute_tablesetelem(instruction* instr){
        avm_memcell* t = avm_translate_operand(&instr->result,(avm_memcell*)0);
        avm_memcell* key = avm_translate_operand(&instr->arg1,&ax);
        avm_memcell* value = avm_translate_operand(&instr->arg2,&bx);
        
        assert(t && &stack[AVM_STACKSIZE] > t && &stack[top] < t);
        assert(key && value);

        if(t->type!=table_m){
                avm_error("illegal use of type %s as table!",typeStrings[t->type]);
        }else{
                avm_tablesetelem(t->data.tableVal,key,value);
        }
}

void execute_nop(instruction* instr){}

unsigned char jump_eqChecks(avm_memcell* rv1,avm_memcell* rv2){
        
        if(rv1->type == undef_m || rv2->type == undef_m){
                avm_error("'undef' involved in equality!");
        }else
        if(rv1->type == bool_m || rv2->type == bool_m){

                return (avm_tobool(rv1) == avm_tobool(rv2));
        }else
        if(rv1->type == nil_m || rv2->type == nil_m){
                return (avm_tobool(rv1) == avm_tobool(rv2));
        }else
        if(rv1->type != rv2->type){
        avm_error("%s==%s is illegal!",
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
                avm_error("'undef' involved in equality!");
        }else
        if(rv1->type == bool_m || rv2->type == bool_m){
                return (avm_tobool(rv1) <= avm_tobool(rv2));
        }else
        if(rv1->type == nil_m || rv2->type == nil_m){
                return (avm_tobool(rv1) <= avm_tobool(rv2));
        }else
        if(rv1->type != rv2->type){
        avm_error("%s<=%s is illegal!",
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
                avm_error("'undef' involved in equality!");
        }else
        if(rv1->type == bool_m || rv2->type == bool_m){
                return (avm_tobool(rv1) >= avm_tobool(rv2));
        }else
        if(rv1->type == nil_m || rv2->type == nil_m){
                return (avm_tobool(rv1) >= avm_tobool(rv2));
        }else
        if(rv1->type != rv2->type){
        avm_error("%s>=%s is illegal!",
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


