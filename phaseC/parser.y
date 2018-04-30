%{
	#include "quad.h"

	struct forPrefix{
		int test;
		int enter;
	};

	/*If > 1 return is in a function block. 
	Increase +1 when entering a function and reduce -1 when exiting*/
	int inFunction = 0; 
	/*-----------------------------*/
	unsigned tempcounter=0;
	quad*    quads = (quad*) 0;
	unsigned total=1;
	unsigned currQuad =1;

	unsigned programVarOffset=0;
	unsigned functionLocalOffset=0;
	unsigned formalArgOffset=0;

	unsigned suffixNum=0;
	unsigned currScope=0;
	unsigned currRange=1;
	unsigned currOffset=0;
	HashTable SymTable;
	std::fstream buffer;
	std::stack<unsigned> offsetStack,labelStack;
	std::list<unsigned> funcReturnsList;
	std::stack<std::list<unsigned>> returnStack;

unsigned breakChecker=0;
unsigned continueChecker=0;
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
}


%right	'='
%left 	OR
%left	AND
%nonassoc EQUAL_EQUAL NOT_EQUAL
%nonassoc '>' GREATER_EQUAL '<' LESS_EQUAL
%left	'+' '-'
%left	'*' '/' '%'
%right 	NOT PLUS_PLUS MINUS_MINUS UMINUS
%left	'.' DOT_DOT
%left	'[' ']'
%left	'(' ')'


%type <intVal> INTCONST funcbody op ifprefix elseprefix N M whilestart whilecond
%type <realVal> REALCONST
%type <strVal> ID STRING funcname
%type <node> lvalue member primary assignexpr call term objectdef const expr exprs elist normcall methodcall 
%type <sym> funcprefix funcdef
%type <prefix> forprefix
%type <index>	indexed indexeds indexedelem

%%

program:	stmts	{std::cout<<"Program <- stmts"<<std::endl;}
		|	{std::cout<<"Program <- (empty)"<<std::endl;}
		;

stmts:		stmts stmt	{
					//tempcounter=0;
					std::cout<<"stmts <- stmts stmt"<<std::endl;
				}
		|stmt		{
					//tempcounter=0;
					std::cout<<"stmts <- stmt"<<std::endl;
				}
		;

stmt:		expr';'		{std::cout<<"stmt <- expr(;)"<<std::endl;}
		| ifstmt	{std::cout<<"stmt <- ifstmt"<<std::endl;}
		| whilestmt	{std::cout<<"stmt <- whilestmt"<<std::endl;}
		| forstmt	{std::cout<<"stmt <- forstmt"<<std::endl;}
		| returnstmt	{std::cout<<"stmt <- returnstmt"<<std::endl;}
		| BREAK';'	{ 
					if(breakChecker==0){
						buffer << "Line: "<< yylineno <<" \n\t";
						buffer<<"Invalid use of break : " << std::endl;
					}
					std::cout<<"stmt <- break(;)"<<std::endl;}
		| CONTINUE';'	{
						if(continueChecker==0){
						buffer << "Line: "<< yylineno <<" \n\t";
						buffer<<"Invalid use of break : " << std::endl;
					}
					std::cout<<"stmt <- continue(;)"<<std::endl;}
		| block		{std::cout<<"stmt <- block"<<std::endl;}
		| funcdef	{std::cout<<"stmt <- funcdef"<<std::endl;}
		| ';'		{std::cout<<"stmt <- semicolon(;)"<<std::endl;}
		;

expr:		assignexpr	{std::cout<<"expr <- assignexpr"<<std::endl;}
		| expr op	{
					$$=quads[currQuad-$2].result;
					if(quads[currQuad-$2].label!=0) quads[currQuad-$2].result=NULL;//relop
					quads[currQuad-$2].arg1= $1;
					std::cout<<"expr <- expr op"<<std::endl;
				}
		| term		{std::cout<<"expr <- term"<<std::endl;}
		;

op:		'+' expr 	{
					expr* e = newexpr(assignexpr_e);
					e->sym = newtemp();
					emit(add,(expr*)0,$2,e,0,yylineno);
					$$=1;
					std::cout<<"op <- + expr"<<std::endl;
				}
		| '-' expr 	{
					expr* e = newexpr(assignexpr_e);
					e->sym = newtemp();
					emit(sub,(expr*)0,$2,e,0,yylineno);
					$$=1;						
					std::cout<<"op <- - expr"<<std::endl;
				}
		| '*' expr 	{
					expr* e = newexpr(assignexpr_e);
					e->sym = newtemp();
					emit(mul,(expr*)0,$2,e,0,yylineno);
					$$=1;						
					std::cout<<"op <- * expr"<<std::endl;
				}
		| '/' expr 	{
					expr* e = newexpr(assignexpr_e);
					e->sym = newtemp();
					emit(Div,(expr*)0,$2,e,0,yylineno);
					$$=1;						
					std::cout<<"op <- / expr"<<std::endl;
				}
		| '%' expr	{
					expr* e = newexpr(assignexpr_e);
					e->sym = newtemp();
					emit(mod,(expr*)0,$2,e,0,yylineno);
					$$=1;						
					std::cout<<"op <- % expr"<<std::endl;
				}
		
		|'>' expr	{
					expr *e=newexpr(assignexpr_e);
					e->sym=newtemp();
					emit(if_greater,$2,(expr*)0,e,currQuad+2,yylineno);
					emit(jump,(expr*)0,(expr*)0,(expr*)0,currQuad+3,yylineno);
					emit(assign,newexpr_constbool_e(true),(expr*)0,e,0,yylineno);
					emit(jump,(expr*)0,(expr*)0,(expr*)0,currQuad+2,yylineno);
					emit(assign,newexpr_constbool_e(false),(expr*)0,e,0,yylineno);
					$$ = 5;
					std::cout<<"op <- > expr"<<std::endl;
				}
		| GREATER_EQUAL expr	{
						expr *e=newexpr(assignexpr_e);
						e->sym=newtemp();
						emit(if_greatereq,$2,newexpr_constnum_e(currQuad+2),e,0,yylineno);
						emit(jump,(expr*)0,(expr*)0,(expr*)0,currQuad+3,yylineno);
						emit(assign,newexpr_constbool_e(true),(expr*)0,e,0,yylineno);
						emit(jump,(expr*)0,(expr*)0,(expr*)0,currQuad+2,yylineno);
						emit(assign,newexpr_constbool_e(false),(expr*)0,e,0,yylineno);
						$$ = 5;
						std::cout<<"op <- >= expr"<<std::endl;
					}
		| '<' expr	{
					expr *e=newexpr(assignexpr_e);
					e->sym=newtemp();
					emit(if_less,$2,newexpr_constnum_e(currQuad+2),e,0,yylineno);
					emit(jump,(expr*)0,(expr*)0,(expr*)0,currQuad+3,yylineno);
					emit(assign,newexpr_constbool_e(true),(expr*)0,e,0,yylineno);
					emit(jump,(expr*)0,(expr*)0,(expr*)0,currQuad+2,yylineno);
					emit(assign,newexpr_constbool_e(false),(expr*)0,e,0,yylineno);
					$$ = 5;
					std::cout<<"op <- < expr"<<std::endl;
				}
		| LESS_EQUAL expr	{
						expr *e=newexpr(assignexpr_e);
						e->sym=newtemp();
						emit(if_lesseq,$2,newexpr_constnum_e(currQuad+2),e,0,yylineno);
						emit(jump,(expr*)0,(expr*)0,(expr*)0,currQuad+3,yylineno);
						emit(assign,newexpr_constbool_e(true),(expr*)0,e,0,yylineno);
						emit(jump,(expr*)0,(expr*)0,(expr*)0,currQuad+2,yylineno);
						emit(assign,newexpr_constbool_e(false),(expr*)0,e,0,yylineno);
						$$ = 5;
						std::cout<<"op <- <= expr"<<std::endl;
					}
		| NOT_EQUAL expr{
					expr *e=newexpr(assignexpr_e);
					e->sym=newtemp();
					emit(if_noteq,$2,newexpr_constnum_e(currQuad+2),e,0,yylineno);
					emit(jump,(expr*)0,(expr*)0,(expr*)0,currQuad+3,yylineno);
					emit(assign,newexpr_constbool_e(true),(expr*)0,e,0,yylineno);
					emit(jump,(expr*)0,(expr*)0,(expr*)0,currQuad+2,yylineno);
					emit(assign,newexpr_constbool_e(false),(expr*)0,e,0,yylineno);
					$$ = 5;
					std::cout<<"op <- != expr"<<std::endl;
				}
		| AND expr	{
					expr *e=newexpr(assignexpr_e);
					e->sym=newtemp();
					emit(And,(expr*)0,$2,e,0,yylineno);
					$$ = 1;
					std::cout<<"op <- && expr"<<std::endl;
				}
		| OR expr	{
					expr *e=newexpr(assignexpr_e);
					e->sym=newtemp();
					emit(Or,(expr*)0,$2,e,0,yylineno);
					$$ = 1;
					std::cout<<"op <- || expr"<<std::endl;
				}
		| EQUAL_EQUAL expr	{
						expr *e=newexpr(assignexpr_e);
						e->sym=newtemp();
						emit(if_eq,$2,newexpr_constnum_e(currQuad+2),e,0,yylineno);
						emit(jump,(expr*)0,(expr*)0,(expr*)0,currQuad+3,yylineno);
						emit(assign,newexpr_constbool_e(true),(expr*)0,e,0,yylineno);
						emit(jump,(expr*)0,(expr*)0,(expr*)0,currQuad+2,yylineno);
						emit(assign,newexpr_constbool_e(false),(expr*)0,e,0,yylineno);
						$$ = 5;
						std::cout<<"op <- == expr"<<std::endl;
					}
		;

term:		'('expr')'		{$$=$2;std::cout<<"term <- ( expr )"<<std::endl;}
		| '-'expr %prec UMINUS	{
						expr* e = newexpr(arithexpr_e);
						e->sym = newtemp();
						emit(uminus,$2,(expr*)0,e,0,yylineno);
						std::cout<<"term <- - expr (UMINUS)"<<std::endl;
					}
		| NOT expr		{ 
						emit(if_eq,$2,newexpr_constbool_e(true),(expr*)0,currQuad+4,yylineno);
						emit(jump,(expr*)0,(expr*)0,(expr*)0,currQuad+1,yylineno);
						expr *e = newexpr(assignexpr_e);
						e->sym=newtemp();
						emit(assign,newexpr_constbool_e(true),(expr*) 0,e,0,yylineno);
						emit(jump,(expr*)0,(expr*)0,(expr*)0,currQuad+2,yylineno);
						emit(assign,newexpr_constbool_e(false),(expr*)0,e,0,yylineno);
						std::cout<<"term <- ! expr"<<std::endl;}
		| PLUS_PLUS lvalue	{
						if(($2->sym!=NULL) && ($2->sym->type == LIBRARY_FUNC || $2->sym->type == PROGRAM_FUNC)){
							buffer << "Line: "<< yylineno <<" \n\t";
							buffer<<"Invalid use of prefix operator ++ : " << $2->sym->name << " refers to a function type."<<std::endl;
						}else if($2->sym==NULL){
                                                        buffer<<"Line: " <<yylineno<< ":";
                                                        buffer<<" undeclared variable."<<std::endl;
                                                }
						emit(add,$2,newexpr_constnum_e(1),$2,0,yylineno);
						expr* e = newexpr(arithexpr_e);
						e->sym = newtemp();
						emit(assign,$2,(expr*)0,e,0,yylineno);
						$$=$2;
						std::cout<<"term <- ++ lvalue"<<std::endl;
					}
		| lvalue PLUS_PLUS	{
						if(($1->sym!=NULL)&& ($1->sym->type == LIBRARY_FUNC || $1->sym->type == PROGRAM_FUNC)){
							buffer << "Line: "<< yylineno <<" \n\t";
							buffer<<"Invalid use of suffix operator ++ : " << $1->sym->name << " refers to a function type."<<std::endl;
						}else if($1->sym==NULL){
							buffer<<"Line: " <<yylineno<< ":\n\t";
							buffer<<"undeclared variable."<<std::endl;
						}
						expr* e = newexpr(arithexpr_e);
						e->sym = newtemp();
						emit(assign,$1,(expr*)0,e,0,yylineno);
						emit(add,$1,newexpr_constnum_e(1),$1,0,yylineno);
						$$ = e;
						std::cout<<"term <- lvalue ++"<<std::endl;
					}
		| MINUS_MINUS lvalue	{
						if(($2->sym!=NULL) && ($2->sym->type == LIBRARY_FUNC || $2->sym->type == PROGRAM_FUNC)){
							buffer << "Line: "<< yylineno <<" \n\t";
							buffer<<"Invalid use of prefix operator -- : " << $2->sym->name << " refers to a function type.\n";
						}else if($2->sym==NULL){
                                                        buffer<<"Line: " <<yylineno<< ":\n\t";
                                                        buffer<<"undeclared variable."<<std::endl;
                                                }
						emit(sub,$2,newexpr_constnum_e(1),$2,0,yylineno);
						expr* e = newexpr(arithexpr_e);
						e->sym = newtemp();
						emit(assign,$2,(expr*)0,e,0,yylineno);
						$$=$2;
						std::cout<<"term <- -- lvalue"<<std::endl;
					}
		| lvalue MINUS_MINUS	{
						if(($1->sym!=NULL) && ($1->sym->type == LIBRARY_FUNC || $1->sym->type == PROGRAM_FUNC)){
							buffer << "Line: "<< yylineno <<" \n\t";
							buffer<<"Invalid use of suffix operator -- : " << $1->sym->name << " refers to a function type.\n";
						}else if($1->sym==NULL){
                                                        buffer<<"Line: " <<yylineno<< ":\n\t";
                                                        buffer<<"undeclared variable."<<std::endl;
                                                }
						expr* e = newexpr(arithexpr_e);
						e->sym = newtemp();
						emit(assign,$1,(expr*)0,e,0,yylineno);
						emit(sub,$1,newexpr_constnum_e(1),$1,0,yylineno);
						$$ = e;
						std::cout<<"term <- lvalue --"<<std::endl;
					}
		| primary		{std::cout<<"term <- primary"<<std::endl;}
		;

assignexpr:	lvalue	'=' expr	{
						if(($1->sym!=NULL) && ($1->sym->type == LIBRARY_FUNC || $1->sym->type == PROGRAM_FUNC)){
								buffer << "Line: "<< yylineno <<"\n\t";
								buffer<<"Invalid use of assignment operator = : " << $1->sym->name << " refers to a function type and cannot be assigned a value.\n";
						}else if($1->sym==NULL){
								buffer<<"Line: " <<yylineno<< ":\n\t";
								buffer<<"undeclared variable."<<std::endl;
						}

						emit(assign,$3,(expr*)0,$1,0,yylineno);

						$$ = newexpr(assignexpr_e);
						$$->sym = newtemp();
						emit(assign,$1,(expr*)0,$$,0,yylineno);

						std::cout<<"assignexpr <- lvalue = expr"<<std::endl;
					}
		;

primary:	lvalue			{std::cout<<"primary <- lvalue"<<std::endl;}
		| call			{std::cout<<"primary <- call"<<std::endl;}
		| objectdef		{std::cout<<"primary <- objectdef"<<std::endl;}
		| '('funcdef')'		{std::cout<<"primary <- ( funcdef )"<<std::endl;}
		| const			{std::cout<<"primary <- const"<<std::endl;}
		;

lvalue:		ID		{
					Symbol* tmp;
					Symbol* newSym=construct_Symbol($1,((currScope) ? 1 : 0),yylineno,currScope,currRange,currScopeSpace(),currScopeOffset());

					tmp = SymTable.lookup($1,currScope,1);
					if(tmp==NULL || (tmp->hidden && tmp->scope==currScope)){
						tmp=SymTable.insert(newSym);
						incCurrScopeOffset();
					}else{
						if(!((tmp->range==currRange || tmp->range==currRange-1) || tmp->scope==0
							|| tmp->type==LIBRARY_FUNC || tmp->type==PROGRAM_FUNC)){
								buffer << "Line: "<< yylineno <<"\t"<<tmp->range<<"\t"<<currRange<<" \n\t";
								buffer<<"ID:Cannot access "<<$1<<" already defined here: "<< tmp->lineno <<std::endl;
						}
					}

					$$=lvalue_expr(tmp);
					std::cout<<"lvalue <- ID"<<std::endl;
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
							buffer << "Line " << yylineno << ":\n\t"<<$2<<" is a Library Function.\n\t";
							buffer<<"Library functions cannot be shadowed:"<<$2<<" already defined here:" << tmp->lineno<<std::endl;
						}
					}

					$$=lvalue_expr(tmp);

					std::cout<<"lvalue <- LOCAL ID"<<std::endl;
				}
		| SCOPE ID	{
					Symbol* tmp;
					tmp=SymTable.lookup($2,0);

					if(tmp==NULL){
						buffer << "Line: "<< yylineno <<" \n\t";
						buffer<<"Could not find Global variable:  \""<<$2<<"\" ,is not defined"<<std::endl;
					}

					$$=lvalue_expr(tmp);
					std::cout<<"lvalue <- SCOPE ID"<<std::endl;
				}
		| member	{$$->sym->type=LOCAL_VAR;std::cout<<"lvalue <- member"<<std::endl;}
		;

member:		lvalue'.'ID		{ expr *e = newexpr(tableitem_e);
							e->sym=newtemp();
							emit(tablegetelem,$1,newexpr_conststring_e($3),e,0,yylineno);
							$$=e;
							
							std::cout<<"member <- lvalue.ID"<<std::endl;}
		| lvalue '['expr']'	{std::cout<<"member <- lvalue [expr]"<<std::endl;}
		| call '.' ID		{std::cout<<"member <- call.ID"<<std::endl;}
		| call '[' expr ']'	{std::cout<<"member <- call[expr]"<<std::endl;}
		;

call: 		call '(' elist ')'		{
							call_emits($3,$1);
							$$=$1;
							std::cout<<"call <- call ( elist )"<<std::endl;
						}
		| lvalue normcall 		{	
							call_emits($2,$1);
							$$=$1;
							std::cout<<"call <- lvalue callsuffix"<<std::endl;
						}
		| lvalue methodcall		{
							$1->next = $2;
							quads[currQuad-1].arg1=$1;
							call_emits($1,quads[currQuad-1].result);
							$$=quads[currQuad-1].result;
						}
		| '(' funcdef ')' '(' elist ')'	{
							expr* e = lvalue_expr($2);
							call_emits($5,e);
							$$=e;
							std::cout<<"call <- (funcdef) (elist)"<<std::endl;
						}
		;



normcall:	'(' elist ')'	{$$=$2;std::cout<<"normcall <- ( elist )"<<std::endl;}
		;

methodcall:	DOT_DOT ID '(' elist ')'	{	
							expr* e = newexpr(assignexpr_e);
							e->sym = newtemp();
							emit(tablegetelem,(expr*)0,newexpr_conststring_e($2),e,0,yylineno);
							$$=$4;
							std::cout<<"methodcall <- ..ID(elist)"<<std::endl;
						}
		;

elist: 		elist exprs	{
					$2->next=$1;
					$$=$2;
					std::cout<<"elist <- elist exprs"<<std::endl;
				}
		|expr		{
					std::cout<<"elist <- expr"<<std::endl;
				}
		|		{
					$$=(expr*)0;
				}
		;

exprs: 		',' expr	{
					$$=$2;
					std::cout<<"exprs <- , expr"<<std::endl;
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
						std::cout<<"objectdef <- [ elist ]"<<std::endl;
				}
		|'['indexed']'	{
						expr* e = newexpr(newtable_e);
						e->sym = newtemp();
						emit(tablecreate,(expr*)0,(expr*)0,e,0,yylineno);
						while($2!=NULL){
							emit(tablesetelem,$2->key,$2->value,e,0,yylineno);
							$2=$2->next;
						}
						std::cout<<"objectdef <- [ elist ]"<<std::endl;
				}
		;

indexed:	indexed indexeds	{
						$2->next=$1;
						$$=$2;
						std::cout<<"indexed <- indexed indexeds"<<std::endl;
					}
		| indexedelem		{std::cout<<"indexed <- indexedelem"<<std::endl;}
		;

indexeds: 	',' indexedelem	{$$=$2;std::cout<<"indexeds <- , indexedelem"<<std::endl;}
		;


indexedelem:	'{' expr ':' expr '}'	{
						indexed* i = new indexed();
						i->key = $2;
						i->value = $4;
						$$=i;
						std::cout<<"indexedelem <- { expr : expr }"<<std::endl;
					}
		;

block:		'{' 	{currScope++;}
		stmts
		'}'	{
				SymTable.hideScope(currScope);
				currScope--;
				std::cout<<"block <- { stmts }"<<std::endl;
			}
		|'{'	{currScope++;}
		'}'	{
				SymTable.hideScope(currScope);
				currScope--;
				std::cout<<"block <- { }"<<std::endl;
			}
		;



funcname: 		ID {$$=$1;}
			|	{
					std::string funcName = "$f";
					funcName += std::to_string(suffixNum++);
					$$=const_cast<char*>(funcName.c_str());
				}
			;

funcprefix: FUNCTION funcname{
				Symbol* tmp;
				Symbol* newSym=construct_Symbol($2,4,yylineno,currScope,currRange,currScopeSpace(),currOffset);
				tmp = SymTable.lookup($2,currScope);
	
				if(tmp==NULL){
					if((tmp = SymTable.lookup($2,0))!=NULL && tmp->type == LIBRARY_FUNC){
						buffer << "Line: "<< yylineno <<" \n\t";
						buffer<<"Invalid Name:  \""<<$2<<"\". Reserved keyword for a library function"<<std::endl;
					}else{
						tmp=SymTable.insert(newSym);
					}
				}
				else{
					buffer << "Line: "<< yylineno <<" \n\t";
					if(tmp->type == LIBRARY_FUNC){
						buffer<<"Invalid Name:  \""<<$2<<"\". Reserved keyword for a library function"<<std::endl;
					}else if(tmp->type == PROGRAM_FUNC){
						buffer<<"Function redefinition. "<<$2<<". already defined here: "<< tmp->lineno<<std::endl;
					}else{
						buffer<<"Cannot access "<<$2<<". already defined here: "<< tmp->lineno<<std::endl;
					}
				}


				$$=tmp;
				labelStack.push(currQuad);
				emit(jump,(expr*)0,(expr*)0,(expr*)0,0,yylineno);
				$$->function.iaddress = nextquadlabel();
				emit(funcstart,(expr*)0,(expr*)0,lvalue_expr($$),0,yylineno);
				currScope++;
				currRange++;
				offsetStack.push(formalArgOffset);
				offsetStack.push(functionLocalOffset);
				formalArgOffset = 0;
			}
		;
funcargs:	'('idlist')'	{
					currScope--;currRange++;functionLocalOffset=0;inFunction++;
					returnStack.push(funcReturnsList);
					funcReturnsList.clear();
				}
		;

funcbody: 	block		{
					currRange-=2;
					inFunction--;
				}
		;

funcdef:	funcprefix funcargs funcbody	{
							$1->function.totallocals = functionLocalOffset;
							$1->function.totalformals = formalArgOffset;
							functionLocalOffset = offsetStack.top();
							offsetStack.pop();
							formalArgOffset = offsetStack.top();
							offsetStack.pop();

						
							//patch the return jumps
							for(unsigned jumpLabel : funcReturnsList){
								patchlabel(jumpLabel, nextquadlabel());
							}
							emit(funcend,(expr*)0,(expr*)0,lvalue_expr($1),0,yylineno);
							funcReturnsList=returnStack.top();
							returnStack.pop();
							
							unsigned labels=labelStack.top();
							labelStack.pop();
							patchlabel(labels,currQuad);
							std::cout<<"funcdef <- FUNCTION (idlist) block"<<std::endl;
						}
		;

const:		INTCONST 	{
					$$=newexpr_constnum_e($1);
					std::cout<<"const <- INTCONST"<<std::endl;
				}
		| REALCONST 	{
					$$=newexpr_constnum_e($1);
					std::cout<<"const <- REALCONST"<<std::endl;
				}
		| STRING 	{
					$$ = newexpr_conststring_e($1);
					std::cout<<"const <- STRING"<<std::endl;
				}
		| NIL 		{
					$$=newexpr(nil_e);
					std::cout<<"const <- NIL"<<std::endl;
				}
		| TRUE 		{
					$$=newexpr_constbool_e(true);
					std::cout<<"const <- TRUE"<<std::endl;
				}
		| FALSE 	{
					$$=newexpr_constbool_e(false);
					std::cout<<"const <- FALSE"<<std::endl;
				}
		;

idlist:		idlist idlists	{std::cout<<"idlist <- idlist idlists"<<std::endl;}
		|ID 		{
					Symbol* tmp;
					Symbol* newSym=construct_Symbol($1,2,yylineno,currScope,currRange,currScopeSpace(),currScopeOffset());

					tmp = SymTable.lookup($1,currScope,1);

					if(tmp==NULL){
						tmp=SymTable.insert(newSym);
						incCurrScopeOffset();
					}else{
						if(tmp->type == LIBRARY_FUNC){
							buffer << "Line " << yylineno << ":\n\t"<<$1<< " is a Library Function.\n";
						}else if(!tmp->hidden && tmp->scope==currScope){
							buffer << "Line: "<< yylineno <<" \n\t";
							buffer<<"Variable: "<<$1<<" is already defined at line: "<< tmp->lineno <<std::endl;
						}else{
							tmp=SymTable.insert(newSym);
							incCurrScopeOffset();
						}

                    			}

					std::cout<<"idlist <- ID "<<std::endl;
				}
		|		{std::cout<<"idlist <- (empty)"<<std::endl;}
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
							buffer << "Line " << yylineno << ":\n\t"<<$2<< " is a Library Function.\n";
						}else if(!tmp->hidden && tmp->scope==currScope){
							buffer << "Line: "<< yylineno <<" \n\t";
							buffer<<"Variable: "<<$2<<" is already defined at line: "<< tmp->lineno <<std::endl;
						}else{
							tmp=SymTable.insert(newSym);
							incCurrScopeOffset();
						}
					}

					std::cout<<"idlists <- , ID"<<std::endl;
				}
		;

ifprefix:	IF '(' expr ')'	{
					emit(if_eq,$3,newexpr_constbool_e(true),(expr*)0,currQuad+2,yylineno);
					$$=nextquadlabel();
					emit(jump,(expr*)0,(expr*)0,(expr*)0,0,yylineno);
				}
		;

elseprefix:	ELSE	{
                                $$=nextquadlabel();
                                emit(jump,(expr*)0,(expr*)0,(expr*)0,0,yylineno);
			}
		;

ifstmt:		ifstmt elseprefix stmt 	{
						patchlabel($2,nextquadlabel());
						std::cout<<"ifstmt <- ifstmt ELSE stmt"<<std::endl;
					}
		|ifprefix stmt 		{
						patchlabel($1,nextquadlabel());
						std::cout<<"ifstmt <- IF ( expr ) stmt"<<std::endl;
					}
whilestart: WHILE
			{
				$$ = nextquadlabel();

			}
		;

whilecond: '(' expr ')' 
			{
				emit(if_eq,newexpr_constbool_e(true),(expr*)0,$2,nextquadlabel()+2,yylineno);
				$$ = nextquadlabel();
				emit(jump,(expr*)0,(expr*)0,(expr*)0,0,yylineno);
			}
			;

whilestmt:	whilestart whilecond  stmt	
			{
				emit(jump,(expr*)0,(expr*)0,(expr*)0,$1,yylineno);
				patchlabel($2,nextquadlabel());
				std::cout<<"whilestmt <- WHILE ( expr ) stmt"<<std::endl;
			}
		;

N:	{$$=currQuad;
	emit(jump,(expr*)0,(expr*)0,(expr*)0,0,yylineno);
	}
	;

M: {$$=currQuad;}
	;

forprefix:	FOR'('elist ';' M expr ';'	{
			struct forPrefix* e = (struct forPrefix*)malloc(sizeof(struct forPrefix));
			e->test = $5;
			e->enter = nextquadlabel();
			$$ = e;
			emit(if_eq,$6,newexpr_constbool_e(true),(expr*)0,0,yylineno);
			}
			;

forstmt:forprefix N elist')' N stmt N{
		patchlabel($1->enter ,$5+1);
		patchlabel($2,nextquadlabel());
		patchlabel($5,$1->test);
		patchlabel($7,$2+1);

		std::cout<<"forstmt <- FOR ( elist ; expr ; elist ) stmt"<<std::endl;
	}
	;


returnstmt: RETURN expr';'	
			{	
				/*Should be made a function in a general purpose utilities.h for commonly used functions*/
				if(inFunction > 0){
					emit(ret,(expr*)0,(expr*)0,$2,0,yylineno);
					funcReturnsList.push_back(nextquadlabel());
					emit(jump,(expr*)0,(expr*)0,(expr*)0,0,yylineno);
				}else{
					buffer << "Line: "<< yylineno <<" \n\t";
					buffer<<"return statement not within a function. "<<std::endl;
				}
				
				std::cout<<"returnstmt <- RETURN expr ;"<<std::endl;
			}
			|RETURN ';'	
			{
				/*Should be made a function in a general purpose utilities.h for commonly used functions*/
				if(inFunction > 0){
					emit(ret,(expr*)0,(expr*)0,(expr*)0,0,yylineno);
					funcReturnsList.push_back(nextquadlabel());
					emit(jump,(expr*)0,(expr*)0,(expr*)0,0,yylineno);
				}else{
					buffer << "Line: "<< yylineno <<" \n\t";
					buffer<<"return statement not within a function. "<<std::endl;
				}
				std::cout<<"returnstmt <- RETURN ;"<<std::endl;
			}
		;
%%

int yyerror(const char* yaccProvidedMessage){
	fprintf(stderr,"%s: at line %d,before token: %s\n",yaccProvidedMessage,yylineno,yytext);
	fprintf(stderr,"INPUT NOT VALID\n");
}

int main(int argc,char** argv){
	if(argc > 1){
		if(!(yyin = fopen(argv[1],"r"))){
			fprintf(stderr,"Cannot read file: %s\n",argv[1]);
			return 1;
		}
	}else
		yyin = stdin;

	buffer.open("alpha_compiler_Errors.txt",std::ios::out);

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
	buffer.close();

	std::cout<<SymTable.allscopestoString()<<std::endl;

	std::ifstream errors("alpha_compiler_Errors.txt");
	std::string line;
	if(errors.is_open()){
		while(getline(errors,line)){
			std::cout<<line<<std::endl;
		}
	}
	remove("alpha_compiler_Errors.txt");


	std::cout<<quads_toString()<<std::endl;
return 0;
}
