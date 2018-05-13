#include "quad.h"


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

Symbol* newtemp(){
	Symbol* tmp;
	std::string name = newtempname();
	tmp = SymTable.lookup(name,currScope,1);
	if(tmp==NULL || ((tmp->scope==currScope || tmp->scope==0) || (tmp->range==currRange || tmp->range==currRange-1))){

		tmp=construct_Symbol(name, ((currScope) ? 1 : 0), yylineno, currScope,currRange, currScopeSpace(), currScopeOffset());
		tmp= SymTable.insert(tmp);
		incCurrScopeOffset();
	}

	return tmp;
}

scopespace_t currScopeSpace(){
	if (currRange == 1){
		return programVar;
	}
	else if (currRange % 2 == 0){
		return formalArg;
	}
	else{
		return functionLocal;
	}
}

int currentScope(){
	return currScope;
}

unsigned currScopeOffset(){
	switch(currScopeSpace()){
		case programVar : 	return programVarOffset;
		case functionLocal : 	return functionLocalOffset;
		case formalArg	:	return formalArgOffset;
		default	:		assert(0);
	}
}

void incCurrScopeOffset(){
	switch (currScopeSpace()){
		case programVar: 	++programVarOffset;break;
		case functionLocal:	++functionLocalOffset;break;
		case formalArg:		++formalArgOffset;break;
		default:		assert(0);
	}
}

unsigned nextquadlabel(){
	return currQuad;
}

void patchlabel(unsigned quadNo,unsigned label){
	assert(quadNo < currQuad);
	quads[quadNo].label = label;
}

void patchlabel(std::list<unsigned> list,unsigned label){	
	for(unsigned i : list){
		patchlabel(i,label);
	}
}


expr* backpatch(expr* myexpr){
	expr* result = newexpr(boolexpr_e);
	result -> sym = newtemp();

        patchlabel(myexpr->trueList,nextquadlabel());
        emit(assign,newexpr_constbool_e(true),(expr*)0,result,0,yylineno);
        emit(jump,(expr*)0,(expr*)0,(expr*)0,nextquadlabel()+2,yylineno);
        patchlabel(myexpr->falseList,nextquadlabel());
      	emit(assign,newexpr_constbool_e(false),(expr*)0,result,0,yylineno);
	return result;
}

expr* checkexpr(expr* e){
	assert(e);
	if(e->type==boolexpr_e)
		return backpatch(e);

	return e;
}

std::list<unsigned> mergeList(std::list<unsigned> dest,std::list<unsigned> src){
	dest.splice(dest.end(),src);
        return dest;
}

expr* lvalue_expr(Symbol *sym){
	assert(sym);
	expr* e = new expr();
	std::memset(e,0,sizeof(expr));

	e->next = (expr*)0;
	e->sym = sym;

	switch ( sym->type){
		case GLOBAL_VAR:
		case LOCAL_VAR:
		case FUNC_ARG:		e->type = var_e;break;
		case PROGRAM_FUNC:	e->type = programfunc_e;break;
		case LIBRARY_FUNC:	e->type = libraryfunc_e;break;
		default:		assert(0);
	}

	return e;
}

expr* newexpr(expr_t type){
	expr* e = new expr();
	e->type = type;
	e->next=NULL;
	return e;
}

expr* newexpr_constbool_e(bool b){
	expr* e = newexpr(constbool_e);
	e->boolConst = b;
	return e;
}

expr* newexpr_constnum_e(double x){
	expr* e = newexpr(constnum_e);
	e->numConst = x;
	return e;
}

expr* newexpr_conststring_e(char* str){
	expr* e = newexpr(conststring_e);
	e->strConst = strdup(str);
	return e;

}

bool isValid_arithop(expr* arg){
	 switch(arg->type){	
		case programfunc_e:
		case libraryfunc_e:
		case newtable_e:
		case constbool_e:
		case conststring_e:
		case boolexpr_e:
		case nil_e:	return false;
		default:	return true;
	}
}

bool isValid_relop(expr* arg){
	 switch(arg->type){	
		case programfunc_e:
		case libraryfunc_e:
		case newtable_e:
		case constbool_e:
		case boolexpr_e:
		case conststring_e:
		case nil_e:	return false;
		default:	return true;
	}
}

expr* call_emits(expr* list,expr* lvalue){
	expr* func = emit_iftableitem(lvalue);
	while(list!=NULL){
		emit(param,(expr*)0,(expr*)0,list,0,yylineno);
		list=list->next;
	}

	emit(call,(expr*)0,(expr*)0,func,0,yylineno);
	expr* result = newexpr(var_e);
	result->sym = newtemp();
	emit(getretval,(expr*)0,(expr*)0,result,0,yylineno);
	return result;
}

expr* arithop_emits(iopcode op,expr* arg1,expr* arg2){
	if(!isValid_arithop(arg1) || !(isValid_arithop(arg2))){
			error_buffer << "Line: "<< yylineno <<" \n\t";
			error_buffer<<"Invalid use of operator: "<<iopcode_toString(op)<<std::endl;
        }
	expr* result = newexpr(arithexpr_e);
	result->sym = newtemp();
	emit(op,arg1,arg2,result,0,yylineno);
	return result;
}

expr* relop_emits(iopcode op,expr* arg1,expr* arg2){
	if(!isValid_relop(arg1) || !(isValid_relop(arg2))){
			error_buffer << "Line: "<< yylineno <<" \n\t";
			error_buffer<<"Invalid use of operator: "<<iopcode_toString(op)<<std::endl;
        }
	
	expr* result = newexpr(boolexpr_e);
	result->sym = newtemp();

	result->trueList.push_back(nextquadlabel());
	result->falseList.push_back(nextquadlabel()+1);
	
	emit(op,arg1,arg2,(expr*)0,0,yylineno);
        emit(jump,(expr*)0,(expr*)0,(expr*)0,0,yylineno);

	return result;
}

expr* boolop_emits(iopcode op,expr* arg1,expr* arg2){
        expr* result = newexpr(boolexpr_e);
        result->sym = newtemp();

        result->trueList.push_back(nextquadlabel());
        result->falseList.push_back(nextquadlabel()+1);

        emit(op,arg1,arg2,(expr*)0,0,yylineno);
        emit(jump,(expr*)0,(expr*)0,(expr*)0,0,yylineno);

        return result;
}

expr* member_item(expr* e1,char* e2){
		e1 = emit_iftableitem(e1);
		expr* item = newexpr(tableitem_e);
		item->sym = e1->sym;
		item->index=newexpr_conststring_e(e2);
		return item;
}

expr* member_item(expr* e1,double e2){
		e1 = emit_iftableitem(e1);
		expr* item = newexpr(tableitem_e);
		item->sym = e1->sym;
		item->index=newexpr_constnum_e(e2);
		return item;
}

expr* emit_iftableitem(expr* e){
	if(e->type != tableitem_e)
		return e;
	else{
		expr* result = newexpr(var_e);
		result->sym = newtemp();
		emit(tablegetelem,e,e->index,result,0,yylineno);
		return result;
	}
}

std::string iopcode_toString(iopcode type){
	switch(type){
		case 0:	return "assign";
		case 1: return "add";
		case 2:	return "sub";
		case 3:	return "mul";
		case 4:	return "Div";
		case 5:	return "mod";
		case 6:	return "uminus";
		case 7:	return "And";
		case 8:	return "Or";
		case 9:	return "Not";
		case 10:	return "if_eq";
		case 11:	return "if_noteq";
		case 12:	return "if_lesseq";
		case 13:	return "if_greatereq";
		case 14:	return "if_less";
		case 15:	return "if_greater";
		case 16:	return "call";
		case 17:	return "param";
		case 18:	return "ret";
		case 19:	return "getretval";
		case 20:	return "funcstart";
		case 21:	return "funcend";
		case 22:	return "tablecreate";
		case 23:	return "tablegetelem";
		case 24:	return "tablesetelem";
		case 25:	return "jump";
		default:	assert(0);
	}
}

std::string expr_toString(expr* temp){
	switch(temp->type){
		case var_e:	
		case assignexpr_e:	
		case arithexpr_e: 
		case libraryfunc_e: 
		case programfunc_e: 
		case newtable_e:
		case boolexpr_e:
		case tableitem_e: return temp->sym->name;
		case constnum_e:	if((fmod(temp->numConst,1)==0)){
						return std::to_string((int)temp->numConst);
					}else {
						return std::to_string(temp->numConst);
					}
		case conststring_e:	return "\"" + temp->strConst + "\"";
		case constbool_e:	return (temp->boolConst) ? "TRUE" : "FALSE";
		case nil_e:	return "nil";
		default: return "INVALID";
	}

}

/* std::setw sets the width of the column for better print alignment */
std::string quads_toString(){
	std::ostringstream buffer;
	int width = 15;
	buffer<<"---------------------------------------------------------------------------------\n";
	buffer<<"#Quad"<<std::setw(width)<<"OpCode"<<std::setw(width)<<"result"<<std::setw(width)<<"arg1"<<std::setw(width)<<"arg2"<<std::setw(width)<<"label"<<std::endl;
	buffer<<"---------------------------------------------------------------------------------\n";
	
	for(int i=1;i<currQuad;i++){
		buffer<<std::setw((i > 9) ? 1 : 2)<<std::to_string(i)<<": ";

		int labelWidth = 60;
		buffer<<std::setw(width)<<iopcode_toString(quads[i].op);

		if(quads[i].result){
			std::string off = (quads[i].result->sym) ? std::to_string(quads[i].result->sym->offset) : "-1";
			buffer<<std::setw(15)<<"("<<off<<")"<<expr_toString(quads[i].result);
			labelWidth -= 15;
		}
		if(quads[i].arg1){
			std::string off = (quads[i].arg1->sym) ? std::to_string(quads[i].arg1->sym->offset) : "-1";
			buffer<<std::setw(15)<<"("<<off<<")"<<expr_toString(quads[i].arg1);
			labelWidth -= 15;
		}
		if(quads[i].arg2){
			std::string off = (quads[i].arg2->sym) ? std::to_string(quads[i].arg2->sym->offset) : "-1";
			buffer<<std::setw(15)<<"("<<off<<")"<<expr_toString(quads[i].arg2);
			labelWidth -= 15;
		}
		if(quads[i].label != 0){
			buffer<<std::setw(labelWidth)<<quads[i].label;
		}

		buffer<<std::endl;

	}
	buffer<<"--------------------------------------------------------------------------------\n";

	return buffer.str();
}

