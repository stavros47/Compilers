#include <stdio.h>
#include <string.h>
#include "alpha_token_t.h"

int alpha_token_t::token_counter(0);

alpha_token_t::alpha_token_t(){
	alpha_token_t::token_counter++;
};

alpha_token_t::~alpha_token_t(){
};

void alpha_token_t::set_lineno(int new_lineno){
	this->lineno = new_lineno;
}

unsigned int alpha_token_t::get_lineno(){
	return this->lineno;
}

void alpha_token_t::set_content(const char* new_token_content){
	strncpy(this->token_content,new_token_content,strlen(new_token_content));
}

char* alpha_token_t::get_token_content(){
	return this->token_content;
}

unsigned int alpha_token_t::get_tokcnt(){
	return token_counter;
}

char* alpha_token_t::get_token_cat(){
}

void alpha_token_t::toString(){
	printf("%d: #%d \"%s\" %s\n",this->lineno,alpha_token_t::token_counter,alpha_token_t::get_token_content(),alpha_token_t::get_token_cat());
}
