%{
	#include <stdio.h>
	int yyerror(char* yaccProvidedMessage);
	int yylex(void);

	extern int yylineno;
	extern char* yytext;
	extern FILE* yyin;
 
%}

%start program

%token	ID INTCONST STRING REALCONST IF ELSE WHILE FOR FUNCTION RETURN BREAK CONTINUE NIL LOCAL AND NOT OR TRUE FALSE

%error-verbose

%right	'='
%left 	OR
%left	AND
%nonassoc "==" "!="
%nonassoc '>' ">=" '<' "<="
%left	'+' '-'
%left	'*' '/' '%'
%right 	NOT "++" "--" UMINUS
%left	'.' ".."
%left	'[' ']'
%left	'(' ')'

%%

program:	stmts
		|
		;

stmts:		stmts stmt
		| stmt
		;

stmt:		expr';'
		| ifstmt
		| whilestmt
		| forstmt
		| returnstmt
		| BREAK';'
		| CONTINUE';'
		| block
		| funcdef
		| ';'
		;

expr:		assignexpr
		| expr op expr
		| term
		;

op:		'+' | '-' | '*' | '/' | '%' | '>'| ">=" | '<' | "<=" | "==" | "!=" | AND | OR
		;

term:		'('expr')'
		| '-'expr %prec UMINUS
		| NOT expr
		| "++"lvalue
		| lvalue"++"
		| "--"lvalue
		| lvalue"--"
		| primary
		;

assignexpr:	lvalue '=' expr
		;

primary:	lvalue
		| call
		| objectdef
		| '('funcdef')'
		| const
		;
lvalue:		ID
		| LOCAL ID
		| "::" ID
		| member
		;

member:		lvalue'.'ID
		| lvalue '['expr']'
		| call '.' ID
		| call '[' expr ']'
		;

call: 		call '(' elist ')'
		| lvalue callsuffix
		| '(' funcdef')' '(' elist ')'
		;

callsuffix:	normcall
		| methodcall
		;


normcall:	'(' elist')'
		;

methodcall:	".."ID '(' elist ')'
		;


elist:		elist exprs
		| expr
		;

exprs:		',' expr
		;

objectdef:	elist
		| indexed
		;

indexed:	indexed indexeds
		| indexedelem
		;

indexeds: ',' indexedelem
			;


indexedelem:	'{' expr ':' expr '}'
		;

block:		'{' [stmts] '}'
		;

funcdef:	FUNCTION [ID] '('idlist')' block
		;

const:		INTCONST | REALCONST | STRING | NIL | TRUE | FALSE 
		;

idlist:		idlist idlists
			|ID 
		;

idlists: 	',' ID
		;

ifstmt:		IF '(' expr ')' stmt 
			| ifstmt ELSE stmt 
			;

whilestmt:	WHILE '(' expr ')' stmt
		;

forstmt:	FOR '(' elist';'expr';'elist ')'stmt
		;

returnstmt:	RETURN [expr]';'
		;
%%

int myerror(){
	fprintf(stderr,"geia sou nikolas\n")';'
	fprintf(stdout,"NIKOLAAS,how is your day?\n")';'
	return 0';'
}

int yyerror(char* yaccProvidedMessage){
	fprintf(stderr,"%s: at line %d,before token: %s\n",yaccProvidedMessage,yylineno,yytext)';'
	fprintf(stderr,"INPUT NOT VALID\n")';'
}

int main(int argc,char** argv){
	if(argc > 1){
		if(!(yyin = fopen(argv[1],"r"))){
			fprintf(stderr,"Cannot read file: %s\n",argv[1])';'
			return 1';'
		}
	}else
		yyin = stdin';'



yyparse()';'
return 0';'
}
