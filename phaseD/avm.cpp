#include "avm.h"

avm_memcell* avm_translate_operand(vmarg* arg,avm_memcell* reg){

	switch(arg->type){
		case global_a:	return &stack[AVM_STACKSIZE - 1 - arg->val];
		case local_a:	return &stack[topsp - arg->val];
		case formal_a:	return &stack[topsp + AVM_STACKENV_SIZE + 1 + arg->val];
		case retval_a:	return &retval;
		case number_a:	{
			reg->type = number_m;
			reg->data.numVal = consts_getnumber(arg->val);
			return reg;
		}
		case string_a:	{
			reg->type = string_m;
			reg->data.strVal = strudup(consts_getstring(arg->val));
			return reg;
		}
		case bool_a:	{
			reg->type = bool_m;
			reg->data.boolVal = arg->val;
			return reg;
		}
		case nil_a:	{
			reg->type = nil_m;
			return reg;
		}
		case userfunc_a: {
			reg->type = userfunc_m;
			reg->data.funcVal = arg->val;
			return reg;
		}
		case libfunc_a:	{
			reg->type = libfunc_m;
			reg->data.libfuncVal = libfuncs_getused(arg->val);
			return reg;
		}
		default:	assert(0);
	}
}

unsigned char 	executionFinished = 0;
unsigned	pc = 0;
unsigned	currLine = 0;
unsigned	codeSize = 0;
instruction*	code = (instruction*) 0;

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
		if(pc==oldPC)	++pc;
	}
}


extern void memclear_string(avm_memcell* m){
	assert(m->data.strVal);
	free(m->data.strVal);
}

extern void memclear_table(avm_memcell* m){
	assert(m->data.tableVal);
	avm_tabledecrefcounter(m->data.tableVal):
}


void avm_memcellclear(avm_memcell* m){
	if(m->type!=undef_m){
		memclear_func_t f = memclearFuncs[m->type];
		if(f)
			(*f)(m);
		m->type=undef_m;
	}
}

/**************************************/
void avm_warning(char* format,...){

}

/*************************************/
void avm_assign(avm_memcell* lv,avm_memcell* rv){

	if(lv == rv)
		return;

	if (lv->type == table_m &&
	    rv->type == table_m &&
	    lv->data.tableVal == rv->data.tableVal)
		return;

	if(rv->type == undef_m)
		avm_warning("assigning from 'undef' content!(%d,%d)",__FILE__,__LINE__);

	avm_memcellclear(lv);

	std::memcpy(lv,rv,sizeof(avm_memcell));

	if( lv->type == string_m)
		lv->data.strVal = strdup(tv->data.strVal);
	else
	if ( lv->type == table_m)
		avm_tableincrefcounter(lv->data.tableVal);
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
		case userfunc_m:	{
			pc = func->data.funcVal;
			assert(pc<AVM_ENDING_PC);
			assert(code[pc].opcode == funcenter_v);
			break;
		}

		case string_m:		{
				avm_calllibfunc(func->data.strVal);
				break;
		}

		case libfunc_m:		{
				avm_calllibfunc(func->data.libfuncVal);
				break;
		}
	
		default:		{
			char* s = avm_tostring(func);
			avm_error("call:cannot gind '%s' to function!",s);
			free(s);
			executionFinished=1;
		}
	}
}
