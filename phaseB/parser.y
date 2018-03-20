%{
	#include <stdio.h>
	#include <string>
	int yyerror(const char* yaccProvidedMessage);
	int yylex(void);

	extern int yylineno;
	extern char* yytext;
	extern FILE* yyin;
 
%}

%start program

%token	ID INTCONST STRING REALCONST IF ELSE WHILE FOR FUNCTION RETURN BREAK CONTINUE NIL LOCAL AND NOT OR TRUE FALSE SCOPE
%token NOT_EQUAL EQUAL_EQUAL DOT_DOT GREATER_EQUAL LESS_EQUAL MINUS_MINUS

%union{
	int intVal;
	char* strVal;
	double realVal;
}
%error-verbose

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

expr:	assignexpr
		| expr op expr
		| term
		;

op:		'+' | '-' | '*' | '/' | '%' | '>'| GREATER_EQUAL | '<' | LESS_EQUAL | MINUS_MINUS | NOT_EQUAL | AND | OR | PLUS_PLUS |EQUAL_EQUAL
		;

term:		'('expr')'
		| '-'expr %prec UMINUS
		| NOT expr
		| PLUS_PLUS lvalue
		| lvalue PLUS_PLUS
		| MINUS_MINUS lvalue
		| lvalue MINUS_MINUS
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
		| SCOPE ID
		| member
		;

member:		lvalue'.'ID
		| lvalue '['expr']'
		| call '.' ID
		| call '[' expr ']'
		;

call: 	  call '(' elist ')'
		| lvalue callsuffix
		| '(' funcdef')' '(' elist ')'
		;

callsuffix:	normcall
		| methodcall
		;


normcall:	'(' elist')'
		;

methodcall:	DOT_DOT ID '(' elist ')'
		;

elist: 	elist exprs
		|expr
		;

exprs: ',' expr
		;
		
objectdef: '['objectdefs']'
			|'['']'
			;		

objectdefs:	elist
		| indexed
		;


indexed:	indexed indexeds
		| indexedelem
		;

indexeds: ',' indexedelem
			;


indexedelem:	'{' expr ':' expr '}'
		;

block:		'{' stmts '}'
			|'{' '}'
		;

funcdef:	FUNCTION ID '('idlist')' block
			|FUNCTION '('idlist')' block
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

returnstmt:	RETURN expr';'
			|RETURN ';'
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
