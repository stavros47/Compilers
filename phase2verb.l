%{

#include "alpha_token_t.h"
#include <fstream>

#define YY_DECL	int alpha_yylex(void* yylval)


unsigned int start;

void parse_string();

%}

%option outfile = "flex.cpp"
%option noyywrap
%option yylineno

	
intconst	[0-9]+
string		"\""
realconst	([0-9]*)(\.){1}([0-9]+)
id		[a-zA-Z][a-zA-Z_0-9]*
space		[\r\t\v\n ]

%%



"if"    {return "IF" ;}
"else"  {return "ELSE" ;}
"while" {return "WHILE" ;}
"for"   {return "FOR" ;}
"function"  {return "FUNCTION" ;}
"return"    {return "RETURN" ;}
"break"     {return "BREAK" ;}
"continue"  {return "CONTINUE" ;}
"nil"   {return "NIL" ;}
"local" {return "LOCAL" ;}
"and"   {return "AND" ;}
"not"   {return "NOT" ;}
"or"    {return "OR" ;}
"true"  {return "TRUE" ;}
"false" {return "FALSE" ;}
">="     {return '>=' ;}
"<="     {return '<=' ;}
"!="     {return '!=' ;}
"=="     {return '==' ;}
"++"     {return '++' ;}
"--"     {return '--' ;}
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
"::"     {return "::" ;}
".."     {return ".." ;}
"."      {return '.' ;}

{realconst} {yylval.intValue = atof(yytext);return REALCONST);}
{intconst} {yylval.intValue = atoi(yytext); return INTEGER}
{string} {yylval.stringVALUE = parse_string(); return STRING}
{id} {yylval.stringVALUE = strdup(yytext); return ID}
{space} {}

. {fprintf(stderr,"UNDEFINED CHARACTER:Cannot match character: %s with any rule\n",yytext);}

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

	alpha_yylex(&instance);

	if(argc>1){
		freopen(argv[2],"w",stdout);
	}

	std::cout<<"\n------------------------------ Lexical Analysis ------------------------------\n\n";
	for(int i=0;i<instance.size();i++)
		std::cout<<instance[i].toString();

	fclose(stdout);
	return 0;
}


void parse_string(){
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

        return std::STRING buffer
}




