#include "avm.h"

unsigned totalActuals=0;
unsigned top,topsp;
avm_memcell retval;
avm_memcell ax,bx,cx;

avm_memcell stack[AVM_STACKSIZE];

unsigned char 	executionFinished = 0;
unsigned	pc = 0;
unsigned	currLine = 0;
unsigned	codeSize = 0;
instruction*	code = (instruction*) 0;

double  consts_getnumber(unsigned u){}
char*   consts_getstring(unsigned u){}
char*   libfuncs_getused(unsigned u){}
userfunc* avm_getfuncinfo(unsigned address){

}

void avm_calllibfunc(char* funcname){}
char* avm_tostring(avm_memcell*){char* s;return s;}
void avm_error(char*,...){}


void avm_callsaveenviroment(void){
	avm_push_envvalue(totalActuals);
	avm_push_envvalue(pc+1);
	avm_push_envvalue(top + totalActuals + 2);
	avm_push_envvalue(topsp);
}


memclear_func_t memclearFuncs[] = {
        0,                      /*number*/
        memclear_string,
        0,                      /*bool*/
        memclear_table,
        0,                      /*userfunc*/
        0,                      /*libfunc*/
        0,                      /*nil*/
        0                       /*undef*/

};

execute_func_t executeFuncs[]= {
         execute_assign,
         execute_add,
         execute_sub,
         execute_mul,
         execute_div,
         execute_mod,
         execute_uminus,
         execute_and,
         execute_or,
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
			reg->data.strVal = strdup(consts_getstring(arg->val));
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
	avm_tabledecrefcounter(m->data.tableVal);
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
//			avm_error("call:cannot gind '%s' to function!");//,s);
			free(s);
			executionFinished=1;
		}
	}
}

 void execute_add         (instruction* instr){}
 void execute_sub         (instruction* instr){}
 void execute_mul         (instruction* instr){}
 void execute_div         (instruction* instr){}
 void execute_mod         (instruction* instr){}
 void execute_uminus      (instruction* instr){}
 void execute_and         (instruction* instr){}
 void execute_or          (instruction* instr){}
 void execute_not         (instruction* instr){}
 void execute_jeq         (instruction* instr){}
 void execute_jne         (instruction* instr){}
 void execute_jle         (instruction* instr){}
 void execute_jge         (instruction* instr){}
 void execute_jlt         (instruction* instr){}
 void execute_jgt         (instruction* instr){}
 void execute_pusharg     (instruction* instr){}
void execute_funcenter   (instruction* instr){
	avm_memcell* func = avm_translate_operand(&instr->result,&ax);
	assert(func);
	assert(pc==func->data.funcVal);

	totalActuals = 0;
	userfunc funcInfo = avm_getfuncinfo(pc);
	topsp = top;
	top = top - funcInfo -> localSize;
}

void execute_funcexit    (instruction* instr){
	unsigned oldTop = top;
	top = avm_get_envvalue(topsp + AVM_SAVETOP_OFFSET);
	pc = avm_get_envvalue(topsp + AVM_SAVEPC_OFFSET);
	topsp = avm_get_envvalue(topsp + AVM_SAVETOPSP_OFFSET);

	while(oldTop++<=top)
		avm_memcellclear(&stack[oldTop]);
}

 void execute_newtable    (instruction* instr){}
 void execute_tablegetelem(instruction* instr){}
 void execute_tablesetelem(instruction* instr){}
 void execute_nop         (instruction* instr){}


void avm_dec_top(void){
	if(!top){
//		avm_error("stack overflow\n");
		executionFinished=1;
	}
	else
		--top;
}

void avm_push_envalue(unsigned val){
	stack[top].type = number_m;
	stack[top].data.numVal = val;
	avm_dec_top();
}

unsigned avm_get_envvalue(unsigned i){
	assert(stack[i].type = number_m);
	unsigned val = (unsigned) stack[i].data.numVal;
	assert(stack[i].data.numVal == ((double) val);
	return val;
}
