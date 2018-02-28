%{

#include "alpha_token_t.h"
#include <fstream>

#define YY_DECL	int alpha_yylex(void* yylval)

std::vector<alpha_token_t> instance;
int start;
int insert(alpha_token_t::token_cat);
void parse_block_comment();
void parse_string();

%}

%option outfile = "flex.cpp"
%option noyywrap
%option yylineno

keyword         "if"|"else"|"while"|"for"|"function"|"return"|"break"|"continue"|"nil"|"local"|"and"|"not"|"or"|"true"|"false"
operator	([\>\<\!\=]=)|(((\+){2})|((\-){2}))|([\+\-\=\*\/\%\>\<])
intconst	[0-9]+
string		"\""
punctuation	\{|\}|\[|\]|\(|\)|\;|\,|\:|\::|\..|\.
realconst	([0-9]*)(\.){1}([0-9]+)
line_comment	"//".*
block_comment	"/*"
id		[a-zA-Z][a-zA-Z_0-9]*
space		[\r\t\v\n ]

%%

{keyword} {insert(alpha_token_t::KEYWORD);}
{operator} {insert(alpha_token_t::OPERATOR);}
{punctuation} {insert(alpha_token_t::PUNCTUATION);}
{realconst} {insert(alpha_token_t::REALCONST);}
{intconst} {insert(alpha_token_t::INTCONST);}
{block_comment}	{parse_block_comment();}
{string} {parse_string();}
{line_comment} {yytext=(char*)"";insert(alpha_token_t::COMMENT);}
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

	if(argc>1){
		freopen(argv[2],"w",stdout);
	}

	std::cout<<"\n------------------------------ Lexical Analysis ------------------------------\n\n";
	for(int i=0;i<instance.size();i++)
		std::cout<<instance[i].toString();

	fclose(stdout);
	return 0;
}

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

	std::ostringstream buffer;

	buffer<< start << "-"	<< yylineno;

	alpha_token_t tmp = alpha_token_t(start,strdup(buffer.str().c_str()),alpha_token_t::COMMENT);
        instance.push_back(tmp);

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

	alpha_token_t tmp = alpha_token_t(start,buffer,alpha_token_t::STRING);
        instance.push_back(tmp);
}

int insert(alpha_token_t::token_cat category){
        alpha_token_t tmp = alpha_token_t(yylineno,strdup(yytext),category);
        instance.push_back(tmp);

        return 0;
}



