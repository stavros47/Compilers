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
        avm_memcell* rv1 = avm_translate_operand(&instr->result,&ax);
        avm_memcell* rv2 = avm_translate_operand(&instr->result,&bx);

        assert(lv && (&stack[0] <= lv && &stack[top] > lv || lv ==&retval));
        assert(rv1 && rv2);

        if(rv1->type != number_m || rv2->type != number_m){
//              avm_error("not a number in arithmetic\n");
                executionFinished=1;
        }else{
                arithmetic_func_t op = arithmeticFuncs[instr->opcode - add_v];
                avm_memcellclear(lv);
                lv->type = number_m;
                lv->data.numVal = (*op)(rv1->data.numVal,rv2->data.numVal);
        }
}

void execute_assign(instruction* instr){
        avm_memcell* lv = avm_translate_operand(&instr->result , (avm_memcell*)0);
        avm_memcell* rv = avm_translate_operand(&instr->arg1 , &ax);

        assert(lv && (&stack[0] <= lv && &stack[top] > lv || lv == &retval));
        assert(rv);

        avm_assign(lv,rv);
}

void execute_call( instruction* instr){
        avm_memcell* func = avm_translate_operand(&instr->result,&ax);
        assert(func);
        avm_callsaveenviroment();

        switch( func->type){
                case userfunc_m:        {
                        pc = func->data.funcVal;
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
        
                default:                {
                        char* s = avm_tostring(func);
//                      avm_error("call:cannot gind '%s' to function!");//,s);
                        free(s);
                        executionFinished=1;
                }
        }
}

void execute_not(instruction* instr){}
void execute_jeq(instruction* instr){
        assert(instr->result.type == label_a);
        avm_memcell* rv1 = avm_translate_operand(&instr->arg1,&ax);
        avm_memcell* rv2 = avm_translate_operand(&instr->arg1,&bx);

        unsigned char result = 0;

        if(rv1->type == undef_m || rv2->type ==undef_m){
                //avm_error("'undef' involved in equality!");
                executionFinished=1;
        }else
        if(rv1->type == bool_m || rv2->type == bool_m){
                result = (avm_tobool(rv1) == avm_tobool(rv2));
        }else
        if(rv1->type == nil_m || rv2->type == nil_m){
                result = (avm_tobool(rv1) == avm_tobool(rv2));
        }else
        if(rv1->type != rv2->type){
/*                avm_error("%s==%s is illegal!",
                                typeStrings[rv1->type],
                                typeStrings[rv2->type]);*/
                executionFinished = 1;
        }else{
                /*Equality checkwith dispatching */
        }
                
        if(!executionFinished && result)
                pc = instr->result.val;
        
}

void execute_jne(instruction* instr){}
void execute_jle(instruction* instr){}
void execute_jge(instruction* instr){}
void execute_jlt(instruction* instr){}
void execute_jgt(instruction* instr){}
void execute_pusharg     (instruction* instr){
        avm_memcell* arg = avm_translate_operand(&instr->arg1,&ax);
        assert(arg);
        avm_assign(&stack[top],arg);
        ++totalActuals;
        avm_dec_top;
}

void execute_funcenter   (instruction* instr){
        avm_memcell* func = avm_translate_operand(&instr->result,&ax);
        assert(func);
        assert(pc==func->data.funcVal);

        totalActuals = 0;
        userfunc* funcInfo = avm_getfuncinfo(pc);
        topsp = top;
        top = top - funcInfo -> localSize;
}

void execute_funcexit    (instruction* instr){
        unsigned oldTop = top;
        top = avm_getenvvalue(topsp + AVM_SAVEDTOP_OFFSET);
        pc = avm_getenvvalue(topsp + AVM_SAVEDPC_OFFSET);
        topsp = avm_getenvvalue(topsp + AVM_SAVEDTOPSP_OFFSET);

        while(oldTop++<=top)
                avm_memcellclear(&stack[oldTop]);
}

void execute_newtable    (instruction* instr){
        avm_memcell* lv = avm_translate_operand(&instr->result,(avm_memcell*)0);
        assert(lv && (&stack[0] <= lv && &stack[top] > lv || lv == &retval));

        avm_memcellclear(lv);

        lv->type = table_m;
        lv->data.tableVal = avm_tablenew();
        avm_tableincrefcounter(lv->data.tableVal);
}

void execute_tablegetelem(instruction* instr){
        avm_memcell* lv = avm_translate_operand(&instr->result,(avm_memcell*)0);
        avm_memcell* k = avm_translate_operand(&instr->arg1,(avm_memcell*)0);
        avm_memcell* v = avm_translate_operand(&instr->arg2,&ax);

        assert(lv && (&stack[0] <= lv && &stack[top] > lv || lv ==&retval));
        assert(k && (&stack[0] <= k && &stack[top] > k));
        assert(v);

        avm_memcellclear(lv);
        lv->type = nil_m;

        if(k->type !=table_m){
//              avm_error("illegal use of type %s astable!",typeString[t->type]);
                executionFinished=1;
        }else{
                avm_memcell* content = avm_tablegetelem(k->data.tableVal,v);
                if(content)
                        avm_assign(lv,content);
                else{
                        char* ks = avm_tostring(k);
                        char* vs = avm_tostring(v);

                        //avm_warning("%s[%s] not found!",ks,vs);
                        free(ks);
                        free(vs);
                }
        }
}

void execute_tablesetelem(instruction* instr){
        avm_memcell* t = avm_translate_operand(&instr->result,(avm_memcell*)0);
        avm_memcell* i = avm_translate_operand(&instr->arg1,&ax);
        avm_memcell* c = avm_translate_operand(&instr->arg2,&bx);
        
        assert(t && (&stack[0] <= t && &stack[top] > t));
        assert(i && c);

        if(t->type!=table_m){
                //avm_error("illegal use of type %s as table!",typeString[t->type]);
        }else{
                avm_tablesetelem(t->data.tableVal,i,c);
        }
}
 void execute_nop(instruction* instr){}



