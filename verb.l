%{
#include "alpha_token_t.h"
#define YY_DECL	int alpha_yylex(void* yylval)
%}
%option outfile = "main.cpp"
%option noyywrap
%option yylineno

keyword         "if"|"else"|"while"|"for"|"function"|"return"|"break"|"continue"|"nil"|"local"|"and"|"not"|"or"|"true"|"false"
operand		([\>\<\!\=]=)|(((\+){2})|((\-){2}))|([\+\-\=\*\/\%\>\<])
intconst	[0-9]+
realconst	([0-9]*)(\.){1}([0-9]+)
string		\"(\\.|[^"\\])*\"
punctuation	\{|\}|\[|\]|\(|\)|\;|\,|\:|\::|\.|\..
comment		"//".*
id		[a-zA-Z][a-zA-Z_0-9]*
space		[\r\t\v\n ]

%x COMMENT

%%


"/*"		BEGIN(COMMENT);
<COMMENT>[^*]* 
<COMMENT>"*"+[^*/]* 
<COMMENT>"*"+"/"	BEGIN(INITIAL);

{keyword} {alpha_token_t tmp= *(alpha_token_t*)yylval;}
{operand} {fprintf(stderr,"Operand with value: %s\n",yytext);}
{realconst} {fprintf(stderr,"RealConst with value: %s\n",yytext);}
{intconst} {fprintf(stderr,"Intconst with value: %s\n",yytext);}
{punctuation} {fprintf(stderr,"Punctuation with value: %s\n",yytext);}
{string} {fprintf(stderr,"String with value: %s\n",yytext);}
{comment} {fprintf(stderr,"Comment with value: %s\n",yytext);}

{id} {fprintf(stderr,"Id with value: %s\n",yytext);}
{space} {}
. {fprintf(stderr,"Cannot match character: %s with any rule\n",yytext);}
%%



int main(int argc,char** argv)
{
	if(argc > 1){
		if(!(yyin = fopen(argv[1],"r"))){
			fprintf(stderr,"Cannot read file: %s\n",argv[1]);
			return 1;
		}
	}
	else{
		yyin=stdin;
	}
	alpha_token_t* instance=(alpha_token_t*)malloc(sizeof(alpha_token_t*));
	alpha_yylex(instance);
	return 0;
}
	
