%{

#include "alpha_token_t.h"
#include <stdio.h>
#include <vector>

#define YY_DECL	int alpha_yylex(void* yylval)

std::vector<alpha_token_t> instance;
int insert(alpha_token_t::token_cat);
void print_vector();
void parse_block_comment();
void parse_string();

%}

%option outfile = "main.cpp"
%option noyywrap
%option yylineno

keyword         "if"|"else"|"while"|"for"|"function"|"return"|"break"|"continue"|"nil"|"local"|"and"|"not"|"or"|"true"|"false"
operator	([\>\<\!\=]=)|(((\+){2})|((\-){2}))|([\+\-\=\*\/\%\>\<])
intconst	[0-9]+
realconst	([0-9]*)(\.){1}([0-9]+)
string		"\""
punctuation	\{|\}|\[|\]|\(|\)|\;|\,|\:|\::|\.|\..
line_comment	"//".*
id		[a-zA-Z][a-zA-Z_0-9]*
space		[\r\t\v\n ]

%x BLOCK_COMMENT

%%


"/*"		BEGIN(BLOCK_COMMENT);printf("%s",yytext);
<BLOCK_COMMENT>[^*]* printf("%s",yytext);
<BLOCK_COMMENT>"*"+[^*/]* printf("%s",yytext);
<BLOCK_COMMENT>"*"+"/"	parse_block_comment();BEGIN(INITIAL);

{keyword} {insert(alpha_token_t::KEYWORD);}
{operator} {insert(alpha_token_t::OPERATOR);}
{realconst} {insert(alpha_token_t::REALCONST);}
{intconst} {insert(alpha_token_t::INTCONST);}
{punctuation} {insert(alpha_token_t::PUNCTUATION);}
{string} {parse_string();}
{line_comment} {insert(alpha_token_t::COMMENT);}
{id} {insert(alpha_token_t::IDENT);}
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
	print_vector();
	return 0;
}

void	parse_block_comment(){
	printf("%s",yytext);

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


