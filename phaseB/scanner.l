
%{

#include "parser.hpp"
#include <fstream>
#include <string>
/*#define YY_DECL	int alpha_yylex(void* yylval)*/

unsigned int start;

char* parse_string();
void parse_block_comment();

%}

%option outfile = "scanner.cpp"
%option noyywrap
%option yylineno

	
intconst	[0-9]+
block_comment   "/*"
line_comment    "//".*
string		"\""
realconst	([0-9]*)(\.){1}([0-9]+)
id		[a-zA-Z][a-zA-Z_0-9]*
space		[\r\t\v\n ]

%%



"if"    {return IF ;}
"else"  {return ELSE ;}
"while" {return WHILE ;}
"for"   {return FOR ;}
"function"  {return FUNCTION ;}
"return"    {return RETURN ;}
"break"     {return BREAK ;}
"continue"  {return CONTINUE ;}
"nil"   {return NIL ;}
"local" {return LOCAL ;}
"and"   {return AND ;}
"not"   {return NOT ;}
"or"    {return OR ;}
"true"  {return TRUE ;}
"false" {return FALSE ;}
">="     {return GREATER_EQUAL ;}
"<="     {return LESS_EQUAL ;}
"!="     {return NOT_EQUAL ;}
"=="     {return EQUAL_EQUAL ;}
"++"     {return PLUS_PLUS ;}
"--"     {return MINUS_MINUS ;}
"::"     {return SCOPE ;}
".."     {return DOT_DOT ;}
"+"      {return '+' ;}
"-"      {return '-' ;}
"="      {return '=' ;}
"*"      {return '*' ;}
"/"      {return '/' ;}
"%"      {return '%' ;}
"<"      {return '<' ;}
">"      {return '>' ;}
"["      {return '[' ;}
"]"      {return ']' ;}
";"      {return ';' ;}
","      {return ',' ;}
":"      {return ':' ;}
"."      {return '.' ;}
"{"	 {return '{';}
"}"	{return '}';}
"("	{return '(';}
")"	{return ')';}

{realconst} {yylval.realVal = atof(yytext);return REALCONST;}
{intconst} {yylval.intVal = atoi(yytext); return INTCONST;}
{string} {yylval.strVal = parse_string(); return STRING;}
{id} {yylval.strVal = strdup(yytext); return ID;}
{block_comment} {parse_block_comment();}
{line_comment} {}
{space} {}

. {fprintf(stderr,"UNDEFINED CHARACTER:Cannot match character: %s with any rule\n",yytext);}

%%

void parse_block_comment(){
        int c,open=1;
        start = yylineno;

        while((c=yyinput())!=EOF){
                if(c=='/'){
                        if((c=yyinput())=='*'){
                                open++;
                        }else{
                                unput(c);
                        }
                }else if(c=='*'){
                        if((c=yyinput())=='/'){
                                open--;
                        }else
                                unput(c);
                }

                if(!open) break;
        }


        if(open){
                fprintf(stderr,"unterminated block comment\n");
                exit(-1);
        }

/*        std::ostringstream buffer;

        buffer<< start << "-"   << yylineno;*/
}

char* parse_string(){
        int c,errchar=2,index=0,buffersize=64;
	char* buffer = (char*)malloc(sizeof(char)*buffersize);

	if(!buffer){
		fprintf(stderr,"error alocating memory\n");
		exit(-1);
	}

	start=yylineno;
        while((c=yyinput())!=EOF){
		if(index>=buffersize){
			buffersize+=buffersize;
			buffer = (char*)realloc(buffer,buffersize);
			if(!buffer){
				fprintf(stderr,"error alocating memory\n");
				exit(-1);
			}
		}

                if(c=='"'){
                        errchar=0;
                        break;
                }

		if(c=='\\'){
                        c=yyinput();

                        if(c=='n'){
                                buffer[index]='\n';
                        }else if(c=='t'){
                                buffer[index]='\t';
                        }else if(c=='\\'){
                                buffer[index]='\\';
                        }else if(c=='"'){
                                buffer[index]='"';
                        }else{
                                errchar=1;
                                fprintf(stderr,"ERROR:string at line: %d contains invalid char(\\)<-- ...seriously?\n",yylineno);
                                exit(-1);
                        }
                }else{
                        buffer[index]=c;
                }

		index++;
        }

        buffer[index]='\0';
        if(errchar==2){
                fprintf(stderr,"ERROR:string at line: %d reached the end of string and (\") not found<-- ...seriously?\n",yylineno);
                exit(-1);
        }

        return buffer;
}




