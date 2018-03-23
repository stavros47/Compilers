%{
	#include <stdio.h>
	#include <iostream>
	#include <string>
	int yyerror(const char* yaccProvidedMessage);
	int yylex(void);

	extern int yylineno;
	extern char* yytext;
	extern FILE* yyin;
 
%}

%start program

%expect 1

%token	ID INTCONST STRING REALCONST IF ELSE WHILE FOR FUNCTION RETURN BREAK CONTINUE NIL LOCAL AND NOT OR TRUE FALSE SCOPE
%token NOT_EQUAL EQUAL_EQUAL DOT_DOT GREATER_EQUAL LESS_EQUAL MINUS_MINUS

%union{
	int intVal;
	char* strVal;
	double realVal;
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
		| PLUS_PLUS lvalue	{std::cout<<"term <- ++ lvalue"<<std::endl;}
		| lvalue PLUS_PLUS	{std::cout<<"term <- lvalue ++"<<std::endl;}	
		| MINUS_MINUS lvalue	{std::cout<<"term <- -- lvalue"<<std::endl;}
		| lvalue MINUS_MINUS	{std::cout<<"term <- lvalue --"<<std::endl;}
		| primary		{std::cout<<"term <- primary"<<std::endl;}
		;

assignexpr:	lvalue '=' expr		{std::cout<<"assignexpr <- lvalue = expr"<<std::endl;}
		;

primary:	lvalue			{std::cout<<"primary <- lvalue"<<std::endl;}
		| call			{std::cout<<"primary <- call"<<std::endl;}
		| objectdef		{std::cout<<"primary <- objectdef"<<std::endl;}
		| '('funcdef')'		{std::cout<<"primary <- ( funcdef )"<<std::endl;}
		| const			{std::cout<<"primary <- const"<<std::endl;}
		;

lvalue:		ID			{std::cout<<"lvalue <- ID"<<std::endl;}
		| LOCAL ID		{std::cout<<"lvalue <- LOCAL ID"<<std::endl;}
		| SCOPE ID		{std::cout<<"lvalue <- SCOPE ID"<<std::endl;}
		| member		{std::cout<<"lvalue <- member"<<std::endl;}
		;

member:		lvalue'.'ID		{std::cout<<"member <- lvalue.ID"<<std::endl;}
		| lvalue '['expr']'	{std::cout<<"member <- lvalue [expr]"<<std::endl;}
		| call '.' ID		{std::cout<<"member <- call.ID"<<std::endl;}
		| call '[' expr ']'	{std::cout<<"member <- call[ID]"<<std::endl;}
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
		;

exprs: 		',' expr	{std::cout<<"exprs <- , expr"<<std::endl;}
		;
		
objectdef: 	'['objectdefs']'	{std::cout<<"objectdef <- [ objectdefs ]"<<std::endl;}
		|'['']'			{std::cout<<"objectdef <- [ ]"<<std::endl;}
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

block:		'{' stmts '}'	{std::cout<<"block <- { stmts }"<<std::endl;}
		| '{' '}'	{std::cout<<"block <- { }"<<std::endl;}
		;

funcdef:	FUNCTION ID '('idlist')' block	{std::cout<<"funcdef <- FUNCTION ID (idlist) block"<<std::endl;}
		|FUNCTION '('idlist')' block	{std::cout<<"funcdef <- FUNCTION (idlist) block"<<std::endl;}
		;

const:		INTCONST 	{std::cout<<"const <- INTCONST"<<std::endl;}
		| REALCONST 	{std::cout<<"const <- REALCONST"<<std::endl;}
		| STRING 	{std::cout<<"const <- STRING"<<std::endl;}
		| NIL 		{std::cout<<"const <- NIL"<<std::endl;}
		| TRUE 		{std::cout<<"const <- TRUE"<<std::endl;}
		| FALSE 	{std::cout<<"const <- FALSE"<<std::endl;}
		;

idlist:		idlist idlists	{std::cout<<"idlist <- idlist idlists"<<std::endl;}
		|ID 		{std::cout<<"idlist <- (empty)"<<std::endl;}
		|
		;

idlists: 	',' ID		{std::cout<<"idlists <- , ID"<<std::endl;}
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



yyparse();
return 0;
}
