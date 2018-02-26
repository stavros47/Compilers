%{

#include "alpha_token_t.h"
#include <vector>
#include <stdio.h>

#define YY_DECL	int alpha_yylex(void* yylval)

std::vector<alpha_token_t> instance;
int insert(alpha_token_t::token_cat);
void print_vector();
void parse_string();
%}

%option outfile = "main.cpp"
%option noyywrap
%option yylineno

keyword         "if"|"else"|"while"|"for"|"function"|"return"|"break"|"continue"|"nil"|"local"|"and"|"not"|"or"|"true"|"false"
operand		([\>\<\!\=]=)|(((\+){2})|((\-){2}))|([\+\-\=\*\/\%\>\<])
intconst	[0-9]+
realconst	([0-9]*)(\.){1}([0-9]+)
string		"\""
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

{keyword} {insert(alpha_token_t::KEYWORD);}
{operand} {}
{realconst} {fprintf(stderr,"RealConst with value: %s\n",yytext);}
{intconst} {fprintf(stderr,"Intconst with value: %s\n",yytext);}
{punctuation} {fprintf(stderr,"Punctuation with value: %s\n",yytext);}
{string} {parse_string();}
{comment} {fprintf(stderr,"Comment with value: %s\n",yytext);}

{id} {insert(alpha_token_t::IDENT);}
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

	alpha_yylex(&instance);
	print_vector();
	return 0;
}
void parse_string(){
	std::vector<char> buffer;
	int c,errchar=2;

	while((c=yyinput())!=EOF){
		if(c=='"'){
			errchar=0;
			break;
		}
		if(c=='\\'){
	                c=yyinput();

                        if(c=='n'){
                                buffer.push_back('\n');
                        }else if(c=='t'){
				buffer.push_back('\t');					
			}else if(c=='\\'){
				buffer.push_back('\\');
			}else if(c=='"'){
				buffer.push_back('"');
			}else{
				errchar=1;
				fprintf(stderr,"ERROR:string at line: %d contains invalid char(\\)<-- ...seriously?\n",yylineno);
				exit(-1);
			}
		}else{
			buffer.push_back(c);
		}

	}

	buffer.insert(buffer.end(),'\0');
	if(errchar==2){
		fprintf(stderr,"ERROR:string at line: %d reached the end of string and (\") not found<-- ...seriously?\n",yylineno);
		exit(-1);	
	}

        for(int i=0;i<buffer.size();i++){
                printf("%c",buffer[i]);
        }

//	printf("%s\n",yytext);

}	
int insert(alpha_token_t::token_cat category){
	alpha_token_t tmp = alpha_token_t(yylineno,strdup(yytext),category);
	
	instance.push_back(tmp);
	return 0;
}

void print_vector(){
	for(int i=0;i<instance.size();i++){
		instance[i].toString();
	}
}
