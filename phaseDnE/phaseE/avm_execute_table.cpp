#include "headers/avm.h"

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
                avm_error("[%d]illegal use of type %s as table!\n",currLine,typeStrings[table->type]);
                executionFinished=1;
        }else{
                avm_memcell* content = avm_tablegetelem(table->data.tableVal,key);
                if(content)
                        avm_assign(lv,content);
                else{
                        avm_warning("[%d]%s[%s] not found!\n",currLine,
                                                                avm_tostring(table).c_str(),
                                                                avm_tostring(key).c_str());
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
                avm_error("[%d]illegal use of type %s as table!\n",currLine,typeStrings[t->type]);
        }else{
                avm_tablesetelem(t->data.tableVal,key,value);
        }
}