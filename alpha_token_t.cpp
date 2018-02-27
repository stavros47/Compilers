#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "alpha_token_t.h"
#include "special_maps.h"

int alpha_token_t::token_counter(0);

alpha_token_t::alpha_token_t(unsigned int line,const char* content,alpha_token_t::token_cat category){
	this->lineno =line;
	this->token_content = content;
	this->token_category = category;
	this->token_special_category= find_special(this->get_cat_asString(),this->get_content());
	this->order = ++alpha_token_t::token_counter;
}

alpha_token_t::~alpha_token_t(){
};

void alpha_token_t::set_lineno(int new_lineno){
	this->lineno = new_lineno;
}

unsigned int alpha_token_t::get_lineno(){
	return this->lineno;
}

/*void alpha_token_t::set_content(char* new_token_content){
	if(new_token_content == NULL){
		fprintf(stderr,"token content raised an error at file %s\n",__FILE__);
		exit(-1);
	}
	strncpy(this->token_content,new_token_content,strlen(new_token_content));
}*/

const char* alpha_token_t::get_content(){
	return this->token_content;
}

void alpha_token_t::set_order(unsigned int norder){
	this->order=norder;
}

unsigned int alpha_token_t::get_order(){
	return this->order;
}

void alpha_token_t::set_cat(alpha_token_t::token_cat new_token_cat){
	this->token_category = new_token_cat;
}

alpha_token_t::token_cat alpha_token_t::get_cat(){
	return this->token_category;
}

const char* alpha_token_t::get_cat_asString(){
	const char* type;
	switch (this->alpha_token_t::get_cat()){
		case alpha_token_t::KEYWORD : type ="KEYWORD";break;
		case alpha_token_t::OPERATOR: type = "OPERATOR"; break;
		case alpha_token_t::INTCONST: type = "INTCONST";break;
		case alpha_token_t::REALCONST: type = "DOUBLECONST";break;
		case alpha_token_t::STRING: type = "STRING";break;
		case alpha_token_t::IDENT: type = "IDENT";break;
		case alpha_token_t::PUNCTUATION: type = "PUNCTUATION";break;
		case alpha_token_t::COMMENT: type = "COMMENT";break;
		default: type = NULL;break;
	}
	return type;
}


const char* alpha_token_t::get_special_category(){
	return this->token_special_category;
}
void alpha_token_t::toString(){
	printf("%d: #%d \"%s\" %s %s\n",this->lineno,this->order,this->get_content(),this->get_cat_asString(),this->get_special_category());
}

const char* alpha_token_t::find_special(const char* category,const char* content){
        const char* special;

        if(!strcmp(category,"KEYWORD")){
                special = keyword_special.find(content)->second;
                printf("content: .%s.\n",content);
                printf("special: %s\n",keyword_special[content]);
        }
        else if(!strcmp(category,"OPERATOR")){
                special = operator_special[content];
                printf("content: %s\n",content);
                printf("special: %s\n",operator_special[content]);
        }
        else if(!strcmp(category,"PUNCTUATION")){
                special = punctuation_special[content];
                printf("content: %s\n",content);
                printf("special: %s\n",punctuation_special[content]);
        }
        else if((!strcmp(category,"INTCONST")) || (!strcmp(category,"DOUBLECONST"))
                || (!strcmp(category,"STRING")) || (!strcmp(category,"IDENT"))
                || (!strcmp(category,"COMMENT"))){
                special = content;
        }
        else{
                fprintf(stderr,"error with special category: %s",__FILE__);
                exit(-1);
        }

        return special;
}


