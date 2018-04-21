%{
	#include "symtable.h"

	int yyerror(const char* yaccProvidedMessage);
	int yylex(void);
	int suffixNum = 0;
	extern int yylineno;
	extern char* yytext;
	extern FILE* yyin;

	int currScope=0;
	int currRange=0;
	HashTable SymTable; 
	std::fstream buffer;
%}

%start program

%expect 1 

%token	ID INTCONST STRING REALCONST IF ELSE WHILE FOR FUNCTION RETURN BREAK CONTINUE NIL LOCAL AND NOT OR TRUE FALSE SCOPE
%token NOT_EQUAL EQUAL_EQUAL DOT_DOT GREATER_EQUAL LESS_EQUAL MINUS_MINUS

%union{
	int intVal;
	char* strVal;
	double realVal;
	struct Symbol *node;
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


%type <intVal> INTCONST
%type <realVal> REALCONST
%type <strVal> ID STRING
%type <node> lvalue 
%%

program:	stmts	{std::cout<<"Program <- stmts"<<std::endl;}
		|	{std::cout<<"Program <- (empty)"<<std::endl;}
		;

stmts:		stmts stmt	{std::cout<<"stmts <- stmts stmt"<<std::endl;}
		|stmt		{std::cout<<"stmts <- stmt"<<std::endl;}
		;

stmt:		expr';'		{std::cout<<"stmt <- expr(;)"<<std::endl;}
		| ifstmt	{std::cout<<"stmt <- ifstmt"<<std::endl;}
		| whilestmt	{std::cout<<"stmt <- whilestmt"<<std::endl;}
		| forstmt	{std::cout<<"stmt <- forstmt"<<std::endl;}
		| returnstmt	{std::cout<<"stmt <- returnstmt"<<std::endl;}
		| BREAK';'	{std::cout<<"stmt <- break(;)"<<std::endl;}
		| CONTINUE';'	{std::cout<<"stmt <- continue(;)"<<std::endl;}
		| block		{std::cout<<"stmt <- block"<<std::endl;}
		| funcdef	{std::cout<<"stmt <- funcdef"<<std::endl;}
		| ';'		{std::cout<<"stmt <- semicolon(;)"<<std::endl;}
		;

expr:		assignexpr	{std::cout<<"expr <- assignexpr"<<std::endl;}
		| expr op	{std::cout<<"expr <- expr op"<<std::endl;}
		| term		{std::cout<<"expr <- term"<<std::endl;}
		;

op:		'+' expr 		{std::cout<<"op <- + expr"<<std::endl;}
		| '-' expr 		{std::cout<<"op <- - expr"<<std::endl;}
		| '*' expr 		{std::cout<<"op <- * expr"<<std::endl;}	
		| '/' expr 		{std::cout<<"op <- / expr"<<std::endl;}
		| '%' expr		{std::cout<<"op <- % expr"<<std::endl;}
		| '>' expr		{std::cout<<"op <- > expr"<<std::endl;}
		| GREATER_EQUAL expr	{std::cout<<"op <- >= expr"<<std::endl;}
		| '<' expr		{std::cout<<"op <- < expr"<<std::endl;}
		| LESS_EQUAL expr	{std::cout<<"op <- <= expr"<<std::endl;}
		| NOT_EQUAL expr 	{std::cout<<"op <- != expr"<<std::endl;}
		| AND expr		{std::cout<<"op <- && expr"<<std::endl;}
		| OR expr		{std::cout<<"op <- || expr"<<std::endl;}
		| EQUAL_EQUAL expr	{std::cout<<"op <- == expr"<<std::endl;}
		;

term:		'('expr')'		{std::cout<<"term <- ( expr )"<<std::endl;}
		| '-'expr %prec UMINUS	{std::cout<<"term <- - expr (UMINUS)"<<std::endl;}
		| NOT expr		{std::cout<<"term <- ! expr"<<std::endl;}
		| PLUS_PLUS lvalue	{
						if(($2!=NULL) && ($2->type == LIBRARY_FUNC || $2->type == PROGRAM_FUNC)){
							buffer << "Line: "<< yylineno <<" \n\t";
							buffer<<"Invalid use of prefix operator ++ : " << $2->name << " refers to a function type."<<std::endl;
						}else if($2==NULL){
                                                        buffer<<"Line: " <<yylineno<< ":";
                                                        buffer<<" undeclared variable."<<std::endl;
                                                }

						std::cout<<"term <- ++ lvalue"<<std::endl;					
					}
		| lvalue PLUS_PLUS	{
						if(($1!=NULL)&& ($1->type == LIBRARY_FUNC || $1->type == PROGRAM_FUNC)){
							buffer << "Line: "<< yylineno <<" \n\t";
							buffer<<"Invalid use of suffix operator ++ : " << $1->name << " refers to a function type."<<std::endl;
						}else if($1==NULL){
                                                        buffer<<"Line: " <<yylineno<< ":\n\t";
                                                        buffer<<"undeclared variable."<<std::endl;
                                                }

						std::cout<<"term <- lvalue ++"<<std::endl;
					}	
		| MINUS_MINUS lvalue	{
						if(($2!=NULL) && ($2->type == LIBRARY_FUNC || $2->type == PROGRAM_FUNC)){
							buffer << "Line: "<< yylineno <<" \n\t";
							buffer<<"Invalid use of prefix operator -- : " << $2->name << " refers to a function type.\n";
						}else if($2==NULL){
                                                        buffer<<"Line: " <<yylineno<< ":\n\t";
                                                        buffer<<"undeclared variable."<<std::endl;
                                                }

						std::cout<<"term <- -- lvalue"<<std::endl;
					}
		| lvalue MINUS_MINUS	{
						if(($1!=NULL) && ($1->type == LIBRARY_FUNC || $1->type == PROGRAM_FUNC)){
							buffer << "Line: "<< yylineno <<" \n\t";
							buffer<<"Invalid use of suffix operator -- : " << $1->name << " refers to a function type.\n";
						}else if($1==NULL){
                                                        buffer<<"Line: " <<yylineno<< ":\n\t";
                                                        buffer<<"undeclared variable."<<std::endl;
                                                }

						std::cout<<"term <- lvalue --"<<std::endl;
					}
		| primary		{std::cout<<"term <- primary"<<std::endl;}
		;

assignexpr:	lvalue	'=' expr	{
						if(($1!=NULL) && ($1->type == LIBRARY_FUNC || $1->type == PROGRAM_FUNC)){
                                                        buffer << "Line: "<< yylineno <<"\n\t";
                                                        buffer<<"Invalid use of assignment operator = : " << $1->name << " refers to a function type and cannot be assigned a value.\n";
                                                }else if($1==NULL){
                                                        buffer<<"Line: " <<yylineno<< ":\n\t";
                                                        buffer<<"undeclared variable."<<std::endl;
                                                }
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
					Symbol* newSym=construct_Symbol($1,((currScope) ? 1 : 0),yylineno,currScope,currRange);

					tmp = SymTable.lookup($1,currScope,1);
					if(tmp==NULL || (tmp->hidden && tmp->scope==currScope)){
						tmp=SymTable.insert(newSym);
					}else{
						if(!(tmp->range==currRange || tmp->scope==0 
							|| tmp->type==LIBRARY_FUNC || tmp->type==PROGRAM_FUNC)){
								buffer<<"range:"<<tmp->range<<" curr:"<<currRange;
								buffer << "Line: "<< yylineno <<" \n\t";
								buffer<<"ID:Cannot access "<<$1<<" already defined here: "<< tmp->lineno <<std::endl;
					
						}
					}

					$$=tmp;
					std::cout<<"lvalue <- ID"<<std::endl;
				}
		| LOCAL ID	{
					Symbol* tmp;
					Symbol* newSym=construct_Symbol($2,(currScope) ? 1 : 0,yylineno,currScope,currRange);
					tmp = SymTable.lookup($2,currScope,1);

					if(tmp==NULL){
						tmp=SymTable.insert(newSym);
					}else{
						if((tmp->scope!=currScope || tmp->hidden)  && (tmp->type!=LIBRARY_FUNC)){
							tmp=SymTable.insert(newSym);
						}else if(tmp->type==LIBRARY_FUNC){
							buffer << "Line " << yylineno << ":\n\t"<<$2<<" is a Library Function.\n\t"; 
							buffer<<"Library functions cannot be shadowed:"<<$2<<" already defined here:" << tmp->lineno<<std::endl; 
						}
					}

					$$=tmp;

					std::cout<<"lvalue <- LOCAL ID"<<std::endl;
				}
		| SCOPE ID	{
					Symbol* tmp;
					tmp=SymTable.lookup($2,0);

					if(tmp==NULL){
						buffer << "Line: "<< yylineno <<" \n\t";
						buffer<<"Could not find Global variable:  \""<<$2<<"\" ,is not defined"<<std::endl;
					}

					$$=tmp;
					std::cout<<"lvalue <- SCOPE ID"<<std::endl;
				}
		| member	{$$->type=LOCAL_VAR;std::cout<<"lvalue <- member"<<std::endl;}
		;

member:		lvalue'.'ID		{std::cout<<"member <- lvalue.ID"<<std::endl;}
		| lvalue '['expr']'	{std::cout<<"member <- lvalue [expr]"<<std::endl;}
		| call '.' ID		{std::cout<<"member <- call.ID"<<std::endl;}
		| call '[' expr ']'	{std::cout<<"member <- call[expr]"<<std::endl;}
		;

call: 		call '(' elist ')'		{std::cout<<"call <- call ( elist )"<<std::endl;}
		| lvalue callsuffix		{std::cout<<"call <- lvalue callsuffix"<<std::endl;}
		| '(' funcdef ')' '(' elist ')'	{std::cout<<"call <- (funcdef) (elist)"<<std::endl;}
		;	

callsuffix:	normcall	{std::cout<<"callsuffix <- normcall"<<std::endl;}
		| methodcall	{std::cout<<"callsuffix <- methodcall"<<std::endl;}
		;


normcall:	'(' elist ')'	{std::cout<<"normcall <- ( elist )"<<std::endl;}
		;

methodcall:	DOT_DOT ID '(' elist ')'	{std::cout<<"methodcall <- ..ID(elist)"<<std::endl;}
		;

elist: 		elist exprs	{std::cout<<"elist <- elist exprs"<<std::endl;}
		|expr		{std::cout<<"elist <- expr"<<std::endl;}
		|
		;

exprs: 		',' expr	{std::cout<<"exprs <- , expr"<<std::endl;}
		;
		
objectdef: 	'['objectdefs']'	{std::cout<<"objectdef <- [ objectdefs ]"<<std::endl;}
		;		

objectdefs:	elist		{std::cout<<"objectdefs <- elist"<<std::endl;}
		| indexed	{std::cout<<"objectdefs <- indexed"<<std::endl;}
		;


indexed:	indexed indexeds	{std::cout<<"indexed <- indexed indexeds"<<std::endl;}
		| indexedelem		{std::cout<<"indexed <- indexedelem"<<std::endl;}
		;

indexeds: 	',' indexedelem	{std::cout<<"indexeds <- , indexedelem"<<std::endl;}
		;


indexedelem:	'{' expr ':' expr '}'	{std::cout<<"indexedelem <- { expr : expr }"<<std::endl;}
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

funcdef:	FUNCTION ID 	{ 
					Symbol* tmp;
					Symbol* newSym=construct_Symbol($2,4,yylineno,currScope,currRange);
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
				}
		'('		{currScope++;currRange++;}
		idlist		
		')'		{currScope--;} 
		block		{currRange--;std::cout<<"funcdef <- FUNCTION ID (idlist) block"<<std::endl;}
		|FUNCTION 	{
					Symbol* tmp;
					std::string funcName = "$f";
					funcName += std::to_string(suffixNum++);
					Symbol* newSym=construct_Symbol(funcName,4,yylineno,currScope,currRange);
				
					tmp=SymTable.insert(newSym);
				} 
		'('		{currScope++;currRange++;}
		idlist
		')'		{currScope--;} 
		block		{currRange--;std::cout<<"funcdef <- FUNCTION (idlist) block"<<std::endl;}
		;

const:		INTCONST 	{std::cout<<"const <- INTCONST"<<std::endl;}
		| REALCONST 	{std::cout<<"const <- REALCONST"<<std::endl;}
		| STRING 	{std::cout<<"const <- STRING"<<std::endl;}
		| NIL 		{std::cout<<"const <- NIL"<<std::endl;}
		| TRUE 		{std::cout<<"const <- TRUE"<<std::endl;}
		| FALSE 	{std::cout<<"const <- FALSE"<<std::endl;}
		;

idlist:		idlist idlists	{std::cout<<"idlist <- idlist idlists"<<std::endl;}
		|ID 		{
					Symbol* tmp;
					Symbol* newSym=construct_Symbol($1,2,yylineno,currScope,currRange);

					tmp = SymTable.lookup($1,currScope,1);

					if(tmp==NULL){
						tmp=SymTable.insert(newSym);
					}else{
						if(tmp->type == LIBRARY_FUNC){
							buffer << "Line " << yylineno << ":\n\t"<<$1<< " is a Library Function.\n";
						}else if(!tmp->hidden && tmp->scope==currScope){
							buffer << "Line: "<< yylineno <<" \n\t";
							buffer<<"Variable: "<<$1<<" is already defined at line: "<< tmp->lineno <<std::endl;
						}else{
							tmp=SymTable.insert(newSym);
						}

                            		}		
					std::cout<<"idlist <- ID "<<std::endl;
				}
		|		{std::cout<<"idlist <- (empty)"<<std::endl;}
		;

idlists: 	',' ID		{
					Symbol* tmp;
					Symbol* newSym=construct_Symbol($2,2,yylineno,currScope,currRange);
					tmp = SymTable.lookup($2,currScope,1);

					if(tmp==NULL){
						tmp=SymTable.insert(newSym);
					}else{
						if(tmp->type == LIBRARY_FUNC){
							buffer << "Line " << yylineno << ":\n\t"<<$2<< " is a Library Function.\n";
						}else if(tmp->hidden){
							tmp=SymTable.insert(newSym);
						
						}else{
							buffer << "Line: "<< yylineno <<" \n\t";
							buffer<<"Variable: "<<$2<<" is already defined at line: "<< tmp->lineno <<std::endl;
						}
					}
					std::cout<<"idlists <- , ID"<<std::endl;
				}
		;

ifstmt:		ifstmt ELSE stmt 	{std::cout<<"ifstmt <- ifstmt ELSE stmt"<<std::endl;}
		|IF '(' expr ')' stmt 	{std::cout<<"ifstmt <- IF ( expr ) stmt"<<std::endl;}
		;

whilestmt:	WHILE '(' expr ')' stmt	{std::cout<<"whilestmt <- WHILE ( expr ) stmt"<<std::endl;}
		;

forstmt:	FOR '(' elist';'expr';'elist ')'stmt	{std::cout<<"forstmt <- FOR ( elist ; expr ; elist ) stmt"<<std::endl;}
		;

returnstmt:	RETURN expr';'	{std::cout<<"returnstmt <- RETURN expr ;"<<std::endl;}
		|RETURN ';'	{std::cout<<"returnstmt <- RETURN ;"<<std::endl;}
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

	SymTable.insert(construct_Symbol("print",3,0,0,0));
	SymTable.insert(construct_Symbol("input",3,0,0,0));
	SymTable.insert(construct_Symbol("objectmemberkeys",3,0,0,0));
	SymTable.insert(construct_Symbol("objecttotalmembers",3,0,0,0));
	SymTable.insert(construct_Symbol("objectcopy",3,0,0,0));
	SymTable.insert(construct_Symbol("totalarguments",3,0,0,0));
	SymTable.insert(construct_Symbol("argument",3,0,0,0));
	SymTable.insert(construct_Symbol("typeof",3,0,0,0));
	SymTable.insert(construct_Symbol("strtonum",3,0,0,0));
	SymTable.insert(construct_Symbol("sqrt",3,0,0,0));
	SymTable.insert(construct_Symbol("cos",3,0,0,0));
	SymTable.insert(construct_Symbol("sin",3,0,0,0));

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

return 0;
}
