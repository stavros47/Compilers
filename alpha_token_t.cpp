#include <stdio.h>
#include <string.h>
#include "alpha_token_t.h"

int alpha_token_t::token_counter(0);

alpha_token_t::alpha_token_t(unsigned int line,char* content,alpha_token_t::token_cat category){
	this->lineno =line;
	this->token_content = content;
	this->token_category = category;
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

void alpha_token_t::set_content(char* new_token_content){
//	strncpy(this->token_content,new_token_content,strlen(new_token_content));
	this->token_content = new_token_content;
}

char* alpha_token_t::get_content(){
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
		case alpha_token_t::DOUBLECONST: type = "DOUBLECONST";break;
		case alpha_token_t::STRING: type = "STRING";break;
		case alpha_token_t::IDENT: type = "IDENT";break;
		case alpha_token_t::COMMENT: type = "COMMENT";break;
		default: type = NULL;break;
	}
	return type;
}



void alpha_token_t::toString(){
	printf("%d: #%d \"%s\" %s\n",this->lineno,this->order,this->get_content(),this->get_cat_asString());
}
