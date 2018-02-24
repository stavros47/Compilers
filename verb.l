%option outfile = "main.cpp"
%option noyywrap

space		[\r\t\v\n ]
keyword         "if"|"else"|"while"|"for"|"function"|"return"|"break"|"continue"|"nil"|"local"|"and"|"not"|"or"|"true"|"false"
operand		([\>\<\!\=]=)|(((\+){2})|((\-){2}))|([\+\-\=\*\/\%\>\<])
intconst	[0-9]+
string		\"[^\n"]*\"
comment		"//".*
id		[a-zA-Z][a-zA-Z_0-9]*
%%

{space} {}
{keyword} {fprintf(stderr,"Keyword with value: %s\n",yytext);}
{operand} {fprintf(stderr,"Operand with value: %s\n",yytext);}
{intconst} {fprintf(stderr,"Intconst with value: %s\n",yytext);}
{string} {fprintf(stderr,"String with value: %s\n",yytext);}
{comment} {fprintf(stderr,"Comment with value: %s\n",yytext);}
{id} {fprintf(stderr,"Id with value: %s\n",yytext);}
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
	yylex();
	return 0;
}
	
