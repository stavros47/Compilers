%{
	#include "instructions.h"

	quad*    quads = (quad*) 0;

	unsigned programVarOffset=0;
	unsigned functionLocalOffset=0;
	unsigned formalArgOffset=0;

	unsigned error=0;

	unsigned inFunction = 0; 
	unsigned inside_loop=0;
	unsigned validSpecial=0;

	unsigned tempcounter=0;

	unsigned total=1;
	unsigned currQuad =1;
	
	unsigned suffixNum=0;
	unsigned currScope=0;
	unsigned currRange=1;
	unsigned currOffset=0;

	HashTable SymTable;
	std::fstream error_buffer;
	std::fstream grammar_buffer;
	std::stack<unsigned> offsetStack,labelStack,validSpecialStack;
	std::stack<std::list<unsigned>> returnStack,breakStack,continueStack;
	std::list<unsigned> returnList,breakList,continueList;
%}

%start program

%expect 1

%token	ID INTCONST STRING REALCONST IF ELSE WHILE FOR FUNCTION RETURN BREAK CONTINUE NIL LOCAL AND NOT OR TRUE FALSE SCOPE
%token NOT_EQUAL EQUAL_EQUAL DOT_DOT GREATER_EQUAL LESS_EQUAL MINUS_MINUS

%union{
	int intVal;
	char* strVal;
	double realVal;
	struct Symbol* sym;
	struct expr *node;
	struct indexed* index;
	struct forPrefix *prefix;
	struct callsuffix *call;
}


%right	'='
%left	OR
%left	AND
%nonassoc EQUAL_EQUAL NOT_EQUAL
%nonassoc '>' GREATER_EQUAL '<' LESS_EQUAL
%left	'+' '-'
%left	'*' '/' '%'
%right 	NOT PLUS_PLUS MINUS_MINUS UMINUS
%left	'.' DOT_DOT
%left	'[' ']'
%left	'(' ')'


%type <intVal> INTCONST funcbody ifprefix elseprefix N M whilestart whilecond 
%type <realVal> REALCONST
%type <strVal> ID STRING funcname
%type <node> lvalue member primary assignexpr call term objectdef const expr exprs elist
%type <sym> funcprefix funcdef
%type <prefix> forprefix
%type <index>	indexed indexeds indexedelem
%type <call>	callsuffix methodcall normcall
%%

program:	stmts	{grammar_buffer<<"Program <- stmts"<<std::endl;}
		|	{grammar_buffer<<"Program <- (empty)"<<std::endl;}
		;

stmts:		stmts stmt	{
					tempcounter=0;
					grammar_buffer<<"stmts <- stmts stmt"<<std::endl;
				}
		|stmt		{
					tempcounter=0;
					grammar_buffer<<"stmts <- stmt"<<std::endl;
				}
		;

stmt:		expr';'		{
					$1 = checkexpr($1);
					grammar_buffer<<"stmt <- expr(;)"<<std::endl;
				}
		| ifstmt	{grammar_buffer<<"stmt <- ifstmt"<<std::endl;}
		| whilestmt	{grammar_buffer<<"stmt <- whilestmt"<<std::endl;}
		| forstmt	{grammar_buffer<<"stmt <- forstmt"<<std::endl;}
		| returnstmt	{grammar_buffer<<"stmt <- returnstmt"<<std::endl;}
		| BREAK';'	{ 
					if(validSpecial!=inFunction || !inside_loop){
						error_buffer << "Line: "<< yylineno <<" \n\t";
						error_buffer<<"Invalid use of break" << std::endl;
					}
					breakList.push_back(nextquadlabel());
					emit(jump,(expr*)0,(expr*)0,(expr*)0,0,yylineno);
					grammar_buffer<<"stmt <- break(;)"<<std::endl;
				}
		| CONTINUE';'	{
					if(validSpecial!=inFunction || !inside_loop){
						error_buffer << "Line: "<< yylineno <<" \n\t";
						error_buffer<<"Invalid use of continue" << std::endl;
					}
					continueList.push_back(nextquadlabel());
					emit(jump,(expr*)0,(expr*)0,(expr*)0,0,yylineno);
					grammar_buffer<<"stmt <- continue(;)"<<std::endl;
				}
		| block		{grammar_buffer<<"stmt <- block"<<std::endl;}
		| funcdef	{grammar_buffer<<"stmt <- funcdef"<<std::endl;}
		| ';'		{grammar_buffer<<"stmt <- semicolon(;)"<<std::endl;}
		;

expr:		assignexpr	{grammar_buffer<<"expr <- assignexpr"<<std::endl;}
		| expr '+' expr	{
					$$=arithop_emits(add,$1,$3);
					grammar_buffer<<"expr + expr"<<std::endl;
				}
		| expr '-' expr	{
					$$=arithop_emits(sub,$1,$3);
					grammar_buffer<<"expr - expr"<<std::endl;
				}
		| expr '*' expr	{
					$$=arithop_emits(mul,$1,$3);
					grammar_buffer<<"expr * expr"<<std::endl;
				}
		| expr '/' expr	{
					$$=arithop_emits(Div,$1,$3);
					grammar_buffer<<"expr / expr"<<std::endl;
				}
		| expr '%' expr	{
					$$=arithop_emits(mod,$1,$3);
					grammar_buffer<<"expr % expr"<<std::endl;
				}
		| expr '>' expr	{
					$$=relop_emits(if_greater,$1,$3);
					grammar_buffer<<"expr > expr"<<std::endl;
				}
		| expr '<' expr	{
					$$=relop_emits(if_less,$1,$3);
					grammar_buffer<<"expr < expr"<<std::endl;
				}
		| expr GREATER_EQUAL expr 	{
							$$=relop_emits(if_greatereq,$1,$3);
							grammar_buffer<<"expr >= expr"<<std::endl;
						}
		| expr LESS_EQUAL expr	{
						$$=relop_emits(if_lesseq,$1,$3);
						grammar_buffer<<"expr <= expr"<<std::endl;
					}
		| expr NOT_EQUAL expr	{
						$1=checkexpr($1);
						$3=checkexpr($3);
						$$=boolop_emits(if_noteq,$1,$3);
						grammar_buffer<<"expr!=expr"<<std::endl;
					}
		| expr EQUAL_EQUAL expr	{
						$1=checkexpr($1);
						$3=checkexpr($3);
						$$=boolop_emits(if_eq,$1,$3);
						grammar_buffer<<"expr == expr"<<std::endl;
					}
		| expr OR 		{
						if($1->type!=boolexpr_e){
							$1 = boolop_emits(if_eq,$1,newexpr_constbool_e(true));
						}
					} 
		M expr			{
						if($5->type!=boolexpr_e){
							$5 = boolop_emits(if_eq,$5,newexpr_constbool_e(true));
						}
					
						patchlabel($1->falseList,$4);

						$$ = newexpr(boolexpr_e);
					
						$$->trueList = mergeList($1->trueList,$5->trueList);
	
						$$->falseList = $5->falseList;

						grammar_buffer<<"expr or M expr"<<std::endl;
					}
		| expr AND		{
						if($1->type!=boolexpr_e){
							$1=boolop_emits(if_eq,$1,newexpr_constbool_e(true));
						}
					}
		 M expr			{
						if($5->type!=boolexpr_e){
							$5=boolop_emits(if_eq,$5,newexpr_constbool_e(true));
						}
					
						patchlabel($1->trueList,$4);

						$$ = newexpr(boolexpr_e);

						$$->trueList = $5->trueList;

						$$->falseList =mergeList($1->falseList,$5->falseList);

						grammar_buffer<<"expr and M expr"<<std::endl;
					}
		| term		{grammar_buffer<<"expr <- term"<<std::endl;}
		;



term:		'('expr')'		{
						$$=$2;
						grammar_buffer<<"term <- ( expr )"<<std::endl;
					}
		| '-'expr %prec UMINUS	{
						if(!isValid_arithop($2)){
							error_buffer << "Line: "<< yylineno <<" \n\t";
							error_buffer<<"Invalid use of prefix operator -(UMINUS) : " << $2->sym->name << " refers to a function type."<<std::endl;
						}
						$$ = newexpr(arithexpr_e);
						$$->sym = newtemp();
						expr* uminus = newexpr_constnum_e(-1);
						emit(mul,$2,uminus,$$,0,yylineno);
						grammar_buffer<<"term <- - expr (UMINUS)"<<std::endl;
					}
		| NOT expr		{
						$2 = boolop_emits(if_eq,$2,newexpr_constbool_e(true));
						$$ = newexpr(boolexpr_e);
						$$->sym = $2->sym;
						$$->trueList = $2->falseList;
						$$->falseList = $2->trueList;
						
						
						grammar_buffer<<"term <- ! expr"<<std::endl;}
		| PLUS_PLUS lvalue	{
						if(!isValid_arithop($2)){
							error_buffer << "Line: "<< yylineno <<" \n\t";
							error_buffer<<"Invalid use of prefix operator ++ : " << $2->sym->name << " refers to a function type."<<std::endl;
						}else if($2->sym==NULL){
                                                        error_buffer<<"Line: " <<yylineno<< ":";
                                                        error_buffer<<"Undeclared variable."<<std::endl;
                                                }

						if($2->type==tableitem_e){
							$$ = emit_iftableitem($2);
							emit(add,$$,newexpr_constnum_e(1),$$,0,yylineno);
							emit(tablesetelem,$2->index,$$,$2,0,yylineno);
							
						}else{
							emit(add,$2,newexpr_constnum_e(1),$2,0,yylineno);
							$$= newexpr(arithexpr_e);
							$$->sym = newtemp();
							emit(assign,$2,(expr*)0,$$,0,yylineno);
						}

						grammar_buffer<<"term <- ++ lvalue"<<std::endl;
					}
		| lvalue PLUS_PLUS	{
						if(!isValid_arithop($1)){
							error_buffer<<"Invalid use of suffix operator ++ : " << $1->sym->name << " refers to a function type."<<std::endl;
						}else if($1->sym==NULL){
							error_buffer<<"Line: " <<yylineno<< ":\n\t";
							error_buffer<<"undeclared variable."<<std::endl;
						}

						expr* e = newexpr(var_e);
						e->sym = newtemp();
						if($1->type==tableitem_e){
							expr* value;
							value = emit_iftableitem($1);
							emit(assign,$1,(expr*)0,e,0,yylineno);
							emit(add,value,newexpr_constnum_e(1),value,0,yylineno);
							emit(tablesetelem,$1->index,value,$1,0,yylineno);
							
						}else{
							emit(assign,$1,(expr*)0,e,0,yylineno);
							emit(add,$1,newexpr_constnum_e(1),$1,0,yylineno);
						}

						$$ = e;

						grammar_buffer<<"term <- lvalue ++"<<std::endl;
					}
		| MINUS_MINUS lvalue	{
						if(($2!=NULL) && ($2->type == libraryfunc_e || $2->type == programfunc_e)){
							error_buffer << "Line: "<< yylineno <<" \n\t";
							error_buffer<<"Invalid use of prefix operator -- : " << $2->sym->name << " refers to a function type.\n";
						}else if($2->sym==NULL){
                                                        error_buffer<<"Line: " <<yylineno<< ":\n\t";
                                                        error_buffer<<"undeclared variable."<<std::endl;
                                                }

						if($2->type==tableitem_e){
							$$ = emit_iftableitem($2);
							emit(sub,$$,newexpr_constnum_e(1),$$,0,yylineno);
							emit(tablesetelem,$2->index,$$,$2,0,yylineno);							
						}else{
							emit(sub,$2,newexpr_constnum_e(1),$2,0,yylineno);
							$$= newexpr(arithexpr_e);
							$$->sym = newtemp();
							emit(assign,$2,(expr*)0,$$,0,yylineno);
						}

						grammar_buffer<<"term <- -- lvalue"<<std::endl;
					}
		| lvalue MINUS_MINUS	{
						if(($1!=NULL) && ($1->type == libraryfunc_e || $1->type == programfunc_e)){
							error_buffer << "Line: "<< yylineno <<" \n\t";
							error_buffer<<"Invalid use of suffix operator -- : " << $1->sym->name << " refers to a function type.\n";
						}else if($1->sym==NULL){
                                                        error_buffer<<"Line: " <<yylineno<< ":\n\t";
                                                        error_buffer<<"undeclared variable."<<std::endl;
                                                }

						expr* e = newexpr(var_e);
						e->sym = newtemp();
						if($1->type==tableitem_e){
							expr* value;
							value = emit_iftableitem($1);
							emit(assign,$1,(expr*)0,e,0,yylineno);
							emit(sub,value,newexpr_constnum_e(1),value,0,yylineno);
							emit(tablesetelem,$1->index,value,$1,0,yylineno);
							
						}else{
							emit(assign,$1,(expr*)0,e,0,yylineno);
							emit(sub,$1,newexpr_constnum_e(1),$1,0,yylineno);
						}
						$$ = e;

						grammar_buffer<<"term <- lvalue --"<<std::endl;
					}
		| primary		{
						$$=$1;
						grammar_buffer<<"term <- primary"<<std::endl;
					}
		;

assignexpr:	lvalue	'=' expr	{
						if(($1!=NULL) && ($1->type == libraryfunc_e || $1->type == programfunc_e)){
							error_buffer << "Line: "<< yylineno <<"\n\t";
							error_buffer<<"Invalid use of assignment operator = : " << $1->sym->name << " refers to a function type and cannot be assigned a value.\n";
						}else if($1->sym==NULL){
							error_buffer<<"Line: " <<yylineno<< ":\n\t";
							error_buffer<<"undeclared variable."<<std::endl;
						}

						$3 = checkexpr($3);

						if($1->type ==tableitem_e){
							emit(tablesetelem,$1->index,$3,$1,0,yylineno);
							$$ = emit_iftableitem($1);
							$$ -> type = assignexpr_e;
						}else{
							emit(assign,$3,(expr*)0,$1,0,yylineno);

							$$ = newexpr(assignexpr_e);
							$$->sym = newtemp();

							emit(assign,$1,(expr*)0,$$,0,yylineno);
						}
						
						grammar_buffer<<"assignexpr <- lvalue = expr"<<std::endl;
					}
		;

primary:	lvalue			{
						$$=emit_iftableitem($1);
						grammar_buffer<<"primary <- lvalue"<<std::endl;
					}
		| call			{grammar_buffer<<"primary <- call"<<std::endl;}
		| objectdef		{grammar_buffer<<"primary <- objectdef"<<std::endl;}
		| '('funcdef')'		{
						$$ = newexpr(programfunc_e);
						$$->sym = $2;
						grammar_buffer<<"primary <- ( funcdef )"<<std::endl;
					}
		| const			{grammar_buffer<<"primary <- const"<<std::endl;}
		;

lvalue:		ID		{
					Symbol* tmp;
					Symbol* newSym=construct_Symbol($1,((currScope) ? 1 : 0),yylineno,currScope,currRange,currScopeSpace(),currScopeOffset());

					tmp = SymTable.lookup($1,currScope,1);
					if(tmp==NULL || tmp->hidden){
						tmp=SymTable.insert(newSym);
						incCurrScopeOffset();
					}else{
						if(!((tmp->range==currRange || tmp->range==currRange-1) || tmp->scope==0
							|| tmp->type==LIBRARY_FUNC || tmp->type==PROGRAM_FUNC)){
							error_buffer << "Line: "<< yylineno <<"\t"<<tmp->range<<"\t"<<currRange<<" \n\t";
							error_buffer<<"ID:Cannot access "<<$1<<" already defined here: "<< tmp->lineno <<std::endl;
						}
					}

					$$=lvalue_expr(tmp);
					
					grammar_buffer<<"lvalue <- ID"<<std::endl;
				}
		| LOCAL ID	{
					Symbol* tmp;
					Symbol* newSym=construct_Symbol($2,(currScope) ? 1 : 0,yylineno,currScope,currRange,currScopeSpace(),currScopeOffset());
					tmp = SymTable.lookup($2,currScope,1);

					if(tmp==NULL){
						tmp=SymTable.insert(newSym);
						incCurrScopeOffset();
					}else{
						if((tmp->scope!=currScope || tmp->hidden)  && (tmp->type!=LIBRARY_FUNC)){
							tmp=SymTable.insert(newSym);
							incCurrScopeOffset();
						}else if(tmp->type==LIBRARY_FUNC){
							error_buffer << "Line " << yylineno << ":\n\t"<<$2<<" is a Library Function.\n\t";
							error_buffer<<"Library functions cannot be shadowed:"<<$2<<" already defined here:" << tmp->lineno<<std::endl;
						}
					}
					$$=lvalue_expr(tmp);

					grammar_buffer<<"lvalue <- LOCAL ID"<<std::endl;
				}
		| SCOPE ID	{
					Symbol* tmp;
					tmp=SymTable.lookup($2,0);

					if(tmp==NULL){
						error_buffer << "Line: "<< yylineno <<" \n\t";
						error_buffer<<"Could not find Global variable:  \""<<$2<<"\" ,is not defined"<<std::endl;
					}
				
					$$=lvalue_expr(tmp);
					grammar_buffer<<"lvalue <- SCOPE ID"<<std::endl;
				}
		| member	{grammar_buffer<<"lvalue <- member"<<std::endl;}
		;

member:		lvalue'.'ID	{ 
					$$ = member_item($1,$3);
					grammar_buffer<<"member <- lvalue.ID"<<std::endl;
				}
		| lvalue '['expr']'	{
						$3 = checkexpr($3);
						
						if($3->type==constnum_e){
							$$=member_item($1,$3->numConst);
						}
						else if($3->type==conststring_e){
							$$=member_item($1,const_cast<char*>($3->strConst.c_str()));
						}else{
							$$ = member_item($1,const_cast<char*>($3->sym->name.c_str()));
						}

						grammar_buffer<<"member <- lvalue [expr]"<<std::endl;
					}
		| call '.' ID		{
						$$ = member_item($1,$3);
						grammar_buffer<<"member <- call.ID"<<std::endl;
					}
		| call '[' expr ']'	{
						$3=checkexpr($3);

						if($3->type==constnum_e){
							$$=member_item($1,$3->numConst);
						}
						else if($3->type==conststring_e){
							$$=member_item($1,const_cast<char*>($3->strConst.c_str()));
						}else{
							$$ = member_item($1,const_cast<char*>($3->sym->name.c_str()));
						}
						grammar_buffer<<"member <- call[expr]"<<std::endl;
					}
		;

call: 		call '(' elist ')'		{
							$$ = call_emits($3,$1);
							grammar_buffer<<"call <- call ( elist )"<<std::endl;
						}
		| lvalue callsuffix	{
						if($2->method){
							expr* self = $1; 
							$1 = emit_iftableitem(member_item($1,$2->name));
							self->next = $2->list;
							$2->list=self;
						}

						$$ = call_emits($2->list,$1);
						grammar_buffer<<"call <- lvalue callsuffix"<<std::endl;
					}
		| '(' funcdef ')' '(' elist ')'	{
							expr* e = newexpr(programfunc_e);
							e->sym=$2;
							$$=call_emits($5,e);
							grammar_buffer<<"call <- (funcdef) (elist)"<<std::endl;
						}
		;


callsuffix:	normcall	{
					$$=$1;
					grammar_buffer<<"callsuffix <-normcall"<<std::endl;
				}
		| methodcall	{
					$$=$1;
					grammar_buffer<<"callsuffix <-methodcall"<<std::endl;
				}
		;


normcall:	'(' elist ')'	{	
					$$=new callsuffix();
					$$->list=$2;
					$$->method = false;	
					$$->name = NULL;
					
					grammar_buffer<<"normcall <- ( elist )"<<std::endl;
				}
		;

methodcall:	DOT_DOT ID '(' elist ')'{
						$$=new callsuffix();
						$$->list=$4;
						$$->method=true;
						$$->name=$2;
						grammar_buffer<<"methodcall <- ..ID(elist)"<<std::endl;
					}
		;

elist: 		elist exprs	{
					expr* tmp;
					tmp=$1;
					while(tmp->next!=NULL)
						tmp=tmp->next;

					tmp->next=$2;
					$$=$1;
					grammar_buffer<<"elist <- elist exprs"<<std::endl;
				}
		|expr		{
					$$ = checkexpr($1);
					grammar_buffer<<"elist <- expr"<<std::endl;
				}
		|		{
					$$=(expr*)0;
					grammar_buffer<<"elist <- "<<std::endl;
				}
		;

exprs: 		',' expr	{

					$$=checkexpr($2);
					grammar_buffer<<"exprs <- , expr"<<std::endl;
				}
		;

objectdef: 	'['elist']'	{
						unsigned table_cnt=0;
						expr* e = newexpr(newtable_e);
						e->sym = newtemp();
						emit(tablecreate,(expr*)0,(expr*)0,e,0,yylineno);
						while($2!=NULL){
							emit(tablesetelem,newexpr_constnum_e(table_cnt++),$2,e,0,yylineno);
							$2=$2->next;
						}
						$$=e;
						grammar_buffer<<"objectdef <- [ elist ]"<<std::endl;
				}
		|'['indexed']'	{
						expr* e = newexpr(newtable_e);
						e->sym = newtemp();
						emit(tablecreate,(expr*)0,(expr*)0,e,0,yylineno);
						while($2!=NULL){
							emit(tablesetelem,$2->key,$2->value,e,0,yylineno);
							$2=$2->next;
						}
						$$=e;
						grammar_buffer<<"objectdef <- [ indexed ]"<<std::endl;
				}
		;

indexed:	indexed indexeds	{
						$2->next=$1;
						$$=$2;
						grammar_buffer<<"indexed <- indexed indexeds"<<std::endl;
					}
		| indexedelem		{grammar_buffer<<"indexed <- indexedelem"<<std::endl;}
		;

indexeds: 	',' indexedelem	{
					$$=$2;
					grammar_buffer<<"indexeds <- , indexedelem"<<std::endl;
				}
		;


indexedelem:	'{' expr ':' expr '}'	{
						$2=checkexpr($2);
						$4=checkexpr($4);

						indexed* i = new indexed();
						i->key = $2;
						i->value = $4;
						$$=i;
						grammar_buffer<<"indexedelem <- { expr : expr }"<<std::endl;
					}
		;

block:		'{' 	{currScope++;}
		stmts
		'}'	{
				SymTable.hideScope(currScope);
				currScope--;
				grammar_buffer<<"block <- { stmts }"<<std::endl;
			}
		|'{'	{currScope++;}
		'}'	{
				SymTable.hideScope(currScope);
				currScope--;
				grammar_buffer<<"block <- { }"<<std::endl;
			}
		;



funcname: 	ID	{
				$$=$1;
				grammar_buffer<<"funcname <- ID"<<std::endl;
			}
		|	{
				std::string funcName = "$f";
				funcName += std::to_string(suffixNum++);
				$$=const_cast<char*>(funcName.c_str());
				grammar_buffer<<"funcname <- (anonymous)"<<std::endl;
			}
		;

funcprefix: FUNCTION funcname	{
					Symbol* tmp;
					Symbol* newSym=construct_Symbol($2,4,yylineno,currScope,currRange,currScopeSpace(),currOffset);
					tmp = SymTable.lookup($2,currScope);
	
					if(tmp==NULL){
						if((tmp = SymTable.lookup($2,0))!=NULL && tmp->type == LIBRARY_FUNC){
							error_buffer << "Line: "<< yylineno <<" \n\t";
							error_buffer<<"Invalid Name:  \""<<$2<<"\". Reserved keyword for a library function"<<std::endl;
						}else{
							tmp=SymTable.insert(newSym);
						}
					}
					else{
						error_buffer << "Line: "<< yylineno <<" \n\t";
						if(tmp->type == LIBRARY_FUNC){
							error_buffer<<"Invalid Name:  \""<<$2<<"\". Reserved keyword for a library function"<<std::endl;
						}else if(tmp->type == PROGRAM_FUNC){
							error_buffer<<"Function redefinition. "<<$2<<". already defined here: "<< tmp->lineno<<std::endl;
						}else{
							error_buffer<<"Cannot access "<<$2<<". already defined here: "<< tmp->lineno<<std::endl;
						}
					}


					$$=tmp;

					labelStack.push(nextquadlabel());
					emit(jump,(expr*)0,(expr*)0,(expr*)0,0,yylineno);

					$$->function.iaddress = nextquadlabel();
					emit(funcstart,(expr*)0,(expr*)0,lvalue_expr($$),0,yylineno);

					currScope++;
					currRange++;
					offsetStack.push(formalArgOffset);
					formalArgOffset = 0;
					grammar_buffer<<"funcprefix <-FUNCTION funcname"<<std::endl;
				}
		;
funcargs:	'('idlist')'	{
					currScope--;
					currRange++;
					offsetStack.push(functionLocalOffset);
					functionLocalOffset=0;
                                        returnStack.push(returnList);
                                        returnList.clear();
					inFunction++;
					grammar_buffer<<"funcargs <-( idlist )"<<std::endl;
				}
		;

funcbody: 	block		{
					currRange-=2;
					inFunction--;
					grammar_buffer<<"funcbody <- block"<<std::endl;
				}
		;

funcdef:	funcprefix funcargs funcbody	{
							$1->function.totallocals = functionLocalOffset;
							functionLocalOffset = offsetStack.top();
							offsetStack.pop();
							formalArgOffset = offsetStack.top();
							offsetStack.pop();

							patchlabel(returnList,nextquadlabel());
							emit(funcend,(expr*)0,(expr*)0,lvalue_expr($1),0,yylineno);

                                                        returnList=returnStack.top();
                                                        returnStack.pop();

							unsigned labels=labelStack.top();
							labelStack.pop();
							patchlabel(labels,nextquadlabel());

							grammar_buffer<<"funcdef <- funcprefix funcargs funcbody"<<std::endl;
						}
		;

const:		INTCONST 	{
					$$=newexpr_constnum_e($1);
					grammar_buffer<<"const <- INTCONST"<<std::endl;
				}
		| REALCONST 	{
					$$=newexpr_constnum_e($1);
					grammar_buffer<<"const <- REALCONST"<<std::endl;
				}
		| STRING 	{
					$$ = newexpr_conststring_e($1);
					grammar_buffer<<"const <- STRING"<<std::endl;
				}
		| NIL 		{
					$$=newexpr(nil_e);
					grammar_buffer<<"const <- NIL"<<std::endl;
				}
		| TRUE 		{
					$$=newexpr_constbool_e(true);
					grammar_buffer<<"const <- TRUE"<<std::endl;
				}
		| FALSE 	{
					$$=newexpr_constbool_e(false);
					grammar_buffer<<"const <- FALSE"<<std::endl;
				}
		;

idlist:		idlist idlists	{grammar_buffer<<"idlist <- idlist idlists"<<std::endl;}
		|ID 		{
					Symbol* tmp;
					Symbol* newSym=construct_Symbol($1,2,yylineno,currScope,currRange,currScopeSpace(),currScopeOffset());

					tmp = SymTable.lookup($1,currScope,1);

					if(tmp==NULL){
						tmp=SymTable.insert(newSym);
						incCurrScopeOffset();
					}else{
						if(tmp->type == LIBRARY_FUNC){
							error_buffer << "Line " << yylineno << ":\n\t"<<$1<< " is a Library Function.\n";
						}else if(!tmp->hidden && tmp->scope==currScope){
							error_buffer << "Line: "<< yylineno <<" \n\t";
							error_buffer<<"Variable: "<<$1<<" is already defined at line: "<< tmp->lineno <<std::endl;
						}else{
							tmp=SymTable.insert(newSym);
							incCurrScopeOffset();
						}

                    			}

					grammar_buffer<<"idlist <- ID "<<std::endl;
				}
		|		{grammar_buffer<<"idlist <- (empty)"<<std::endl;}
		;

idlists: 	',' ID		{
					Symbol* tmp;
					Symbol* newSym=construct_Symbol($2,2,yylineno,currScope,currRange,currScopeSpace(),currScopeOffset());
					tmp = SymTable.lookup($2,currScope,1);

					if(tmp==NULL){
						tmp=SymTable.insert(newSym);
						incCurrScopeOffset();
					}else{
						if(tmp->type == LIBRARY_FUNC){
							error_buffer << "Line " << yylineno << ":\n\t"<<$2<< " is a Library Function.\n";
						}else if(!tmp->hidden && tmp->scope==currScope){
							error_buffer << "Line: "<< yylineno <<" \n\t";
							error_buffer<<"Variable: "<<$2<<" is already defined at line: "<< tmp->lineno <<std::endl;
						}else{
							tmp=SymTable.insert(newSym);
							incCurrScopeOffset();
						}
					}

					grammar_buffer<<"idlists <- , ID"<<std::endl;
				}
		;

ifprefix:	IF '(' expr ')'	{
					$3 = checkexpr($3);

					emit(if_eq,$3,newexpr_constbool_e(true),(expr*)0,nextquadlabel()+2,yylineno);
					$$=nextquadlabel();
					emit(jump,(expr*)0,(expr*)0,(expr*)0,0,yylineno);
					grammar_buffer<<"ifprefix <- IF ( expr )"<<std::endl;
				}
		;

elseprefix:	ELSE	{
                                $$=nextquadlabel();
                                emit(jump,(expr*)0,(expr*)0,(expr*)0,0,yylineno);
				grammar_buffer<<"elseprefix <- ELSE"<<std::endl;
			}
		;

ifstmt:		ifprefix stmt elseprefix stmt 	{
							patchlabel($3,nextquadlabel());
							patchlabel($1,$3+1);
							grammar_buffer<<"ifstmt <- ifprefix stmt elseprefix stmt"<<std::endl;
						}
		| ifprefix stmt	{
					patchlabel($1,nextquadlabel());
					grammar_buffer<<"ifstmt <- ifprefix stmt"<<std::endl;
				}

whilestart:	WHILE	{
				$$ = nextquadlabel();
				grammar_buffer<<"whilestart <- WHILE"<<std::endl;
			}
		;

whilecond:	'(' expr ')' 	{
					$2 = checkexpr($2);

					emit(if_eq,newexpr_constbool_e(true),(expr*)0,$2,nextquadlabel()+2,yylineno);
					$$ = nextquadlabel();
					emit(jump,(expr*)0,(expr*)0,(expr*)0,0,yylineno);

					inside_loop++;

					breakStack.push(breakList);
					continueStack.push(continueList);
					breakList.clear();
					continueList.clear();
					validSpecialStack.push(validSpecial);
					validSpecial=inFunction;

					grammar_buffer<<"whilecond <- ( expr )"<<std::endl;
				}
		;

whilestmt:	whilestart whilecond  stmt	{
							emit(jump,(expr*)0,(expr*)0,(expr*)0,$1,yylineno);
							patchlabel($2,nextquadlabel());
						
							patchlabel(breakList,nextquadlabel());
							breakList = breakStack.top();
							breakStack.pop();

							patchlabel(continueList,$1);
							continueList = continueStack.top();
							continueStack.pop();

							validSpecial = validSpecialStack.top();
							validSpecialStack.pop();

							inside_loop--;
							grammar_buffer<<"whilestmt <- whilestart whilecond stmt"<<std::endl;
						}		
			;

N:			{
				$$=nextquadlabel();
				emit(jump,(expr*)0,(expr*)0,(expr*)0,0,yylineno);
				grammar_buffer<<"N <- (empty)"<<std::endl;
			}
		;

M: 			{
				$$=nextquadlabel();
				grammar_buffer<<"M <- (empty)"<<std::endl;
			}
		;

forprefix:	FOR'('elist ';' M expr ';'	{
							$6 = checkexpr($6);

							forPrefix* e = new forPrefix();
							e->test = $5;
							e->enter = nextquadlabel();
							$$ = e;
							emit(if_eq,$6,newexpr_constbool_e(true),(expr*)0,0,yylineno);

							inside_loop++;
							breakStack.push(breakList);
							continueStack.push(continueList);
							breakList.clear();
							continueList.clear();
				
								
							validSpecialStack.push(validSpecial);
							validSpecial=inFunction;
							
							grammar_buffer<<"forprefix <- FOR ( elist ; M expr ;"<<std::endl;
						}
		;

forstmt:	forprefix N elist')' N stmt N	{
							patchlabel($1->enter ,$5+1);
							patchlabel($2,nextquadlabel());
							patchlabel($5,$1->test);
							patchlabel($7,$2+1);
						
							patchlabel(breakList,nextquadlabel());
							breakList = breakStack.top();
							breakStack.pop();

							patchlabel(continueList,$2+1);
							continueList = continueStack.top();
							continueStack.pop();

							validSpecial = validSpecialStack.top();
							validSpecialStack.pop();

							inside_loop--;
							grammar_buffer<<"forstmt <- forprefix N elist ) N stmt N"<<std::endl;
						}
		;

returnstmt: RETURN expr';'	
			{
				$2 = checkexpr($2);	
				 if(inFunction > 0){
                                        emit(ret,(expr*)0,(expr*)0,$2,0,yylineno);
                                        returnList.push_back(nextquadlabel());
                                        emit(jump,(expr*)0,(expr*)0,(expr*)0,0,yylineno);
                                }else{
                                        error_buffer << "Line: "<< yylineno <<" \n\t";
                                        error_buffer<<"return statement not within a function. "<<std::endl;
                                }

				
				
				grammar_buffer<<"returnstmt <- RETURN expr ;"<<std::endl;
			}
			|RETURN ';'	
			{
				if(inFunction > 0){
                                        emit(ret,(expr*)0,(expr*)0,(expr*)0,0,yylineno);
                                        returnList.push_back(nextquadlabel());
                                        emit(jump,(expr*)0,(expr*)0,(expr*)0,0,yylineno);
                                }else{
                                        error_buffer << "Line: "<< yylineno <<" \n\t";
                                        error_buffer<<"return statement not within a function. "<<std::endl;
                                }

				grammar_buffer<<"returnstmt <- RETURN ;"<<std::endl;
			}
		;
%%

int yyerror(const char* yaccProvidedMessage){
	fprintf(stderr,"%s: at line %d,before token: %s\n",yaccProvidedMessage,yylineno,yytext);
	fprintf(stderr,"INPUT NOT VALID\n");
	error=1;
}

int main(int argc,char** argv){
	if(argc > 1){
		if(!(yyin = fopen(argv[1],"r"))){
			fprintf(stderr,"Cannot read file: %s\n",argv[1]);
			return 1;
		}
	}else
		yyin = stdin;

	error_buffer.open("alpha_errors.txt",std::ios::out);
	grammar_buffer.open("alpha_grammar.txt",std::ios::out);

	SymTable.insert(construct_Symbol("print",3,0,0,0,programVar,0));
	SymTable.insert(construct_Symbol("input",3,0,0,0,programVar,0));
	SymTable.insert(construct_Symbol("objectmemberkeys",3,0,0,0,programVar,0));
	SymTable.insert(construct_Symbol("objecttotalmembers",3,0,0,0,programVar,0));
	SymTable.insert(construct_Symbol("objectcopy",3,0,0,0,programVar,0));
	SymTable.insert(construct_Symbol("totalarguments",3,0,0,0,programVar,0));
	SymTable.insert(construct_Symbol("argument",3,0,0,0,programVar,0));
	SymTable.insert(construct_Symbol("typeof",3,0,0,0,programVar,0));
	SymTable.insert(construct_Symbol("strtonum",3,0,0,0,programVar,0));
	SymTable.insert(construct_Symbol("sqrt",3,0,0,0,programVar,0));
	SymTable.insert(construct_Symbol("cos",3,0,0,0,programVar,0));
	SymTable.insert(construct_Symbol("sin",3,0,0,0,programVar,0));

	yyparse();
	error_buffer.close();
	grammar_buffer.close();

	std::cout<<SymTable.allscopestoString()<<std::endl;

	std::ifstream errors("alpha_errors.txt");
	std::string line;
	if(errors.is_open()){
		while(getline(errors,line)){
			error=1;
			std::cout<<line<<std::endl;
		}
	}
	remove("alpha_errors.txt");

	if(!error){
		std::cout<<quads_toString()<<std::endl;
	//	make_instructions(quads);
	} 

return 0;
}
