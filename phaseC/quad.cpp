#include "symtable.h"

void expand(void){
	assert(total==currQuad);
	quad* p = (quad*)malloc(NEW_SIZE);
	if( quads){
		std::memcpy(p,quads,CURR_SIZE);
		free(quads);
	}

	quads = p;
	total+=EXPAND_SIZE;
}

void emit(iopcode op,expr* arg1,expr* arg2,expr* result,unsigned label,unsigned line){
	if(currQuad == total)
		expand();

	quad* p = quads+currQuad++;
	p->op = op;
	p->arg1 = arg1;
	p->arg2 = arg2;
	p->result = result;
	p->label = label;
	p->line = line;
}

std::string newtempname(){
	std::string tempname="_t";
	return tempname + std::to_string(tempcounter++);
}

void resettmp(){
	tempcounter=0;
}

int currentScope(){
	return currScope;
}

scopespace_t currScopeSpace()
{
	if (currRange == 1)
	{
		return programVar;
	}
	else if (currRange % 2 == 0)
	{
		return formalArg;
	}
	else
	{
		return functionLocal;
	}
}

Symbol* newtemp(){
	Symbol* tmp;
	std::string name = newtempname();
	tmp = SymTable.lookup(name,currScope);
	if(tmp==NULL){
		return construct_Symbol(name,((currScope) ? 1: 0),yylineno,currScope,currScopeSpace(), currOffset);
	}else{
		return tmp;
	}
}

unsigned currScopeOffset(){
	switch(currScopeSpace()){
		case programVar : return programVarOffset;
		case functionLocal : return functionLocalOffset;
		case formalArg	:	return formalArgOffset;
		default	:	assert(0);
	}
}

void incCurrScopeOffset()
{
	switch (currScopeSpace())
	{
		case programVar: ++programVarOffset;break;
		case functionLocal:	++functionLocalOffset;break;
		case formalArg:	++formalArgOffset;break;
		default:	assert(0);
	}
}

void enterScopeSpace(){++currRange;}

void exitScopeSpace(){assert(currRange>1);--currRange;}


expr* lvalue_expr(Symbol *sym){
	assert(sym);
	expr* e = new expr();
	std::memset(e,0,sizeof(expr));

	e->next = (expr*)0;
	e->sym = sym;

	if ((sym->type == GLOBAL_VAR) || (sym->type == LOCAL_VAR) || (sym->type ==FUNC_ARG)){
		e->type = var_e;
	}else if(sym->type == PROGRAM_FUNC){
		e->type = programfunc_e;
	}else if(sym->type == LIBRARY_FUNC){
		e->type = libraryfunc_e;
	}else{
		assert(0);
	}

	return e;
}

expr* newexpr(expr_t type){
	expr* e = new expr();
	e->type = type;
	
	return e;
}