#include "alpha_token_t.h"
#include "special_maps.h"

int alpha_token_t::token_counter(0);

alpha_token_t::alpha_token_t(unsigned int line,std::string content,alpha_token_t::token_cat category){
	this->lineno =line;
	(this->token_content).replace((this->token_content).begin(),(this->token_content).end(),content);
	this->token_category = category;
	(this->token_special_category).replace((this->token_special_category).begin(),(this->token_special_category).end(),find_special(this->get_cat_asString(),content));
	this->order = ++alpha_token_t::token_counter;
}

unsigned int alpha_token_t::get_lineno(){
	return this->lineno;
}

std::string alpha_token_t::get_content(){
	return this->token_content;
}

unsigned int alpha_token_t::get_order(){
	return this->order;
}

alpha_token_t::token_cat alpha_token_t::get_cat(){
	return this->token_category;
}

std::string alpha_token_t::get_special_category(){
	return this->token_special_category;
}

std::string alpha_token_t::get_cat_asString(){
	std::string type;
	switch (this->alpha_token_t::get_cat()){
		case alpha_token_t::KEYWORD : type.replace(type.begin(),type.end(),"KEYWORD");break;
		case alpha_token_t::OPERATOR: type.replace(type.begin(),type.end(),"OPERATOR"); break;
		case alpha_token_t::INTCONST: type.replace(type.begin(),type.end(),"INTCONST");break;
		case alpha_token_t::REALCONST: type.replace(type.begin(),type.end(),"DOUBLECONST");break;
		case alpha_token_t::STRING: type.replace(type.begin(),type.end(),"STRING");break;
		case alpha_token_t::IDENT: type.replace(type.begin(),type.end(),"IDENT");break;
		case alpha_token_t::PUNCTUATION: type.replace(type.begin(),type.end(),"PUNCTUATION");break;
		case alpha_token_t::COMMENT: type.replace(type.begin(),type.end(),"COMMENT");break;
		default: type = '\0';break;
	}
	return type;
}

std::string alpha_token_t::find_special(std::string category,std::string content){

	std::string special;

        if(!category.std::string::compare("KEYWORD")){
		special = keyword_special[content];
	}
        else if(!category.std::string::compare("OPERATOR")){
		special = operator_special[content];
        }
        else if(!category.std::string::compare("PUNCTUATION")){
		special = punctuation_special[content];
        }else if((!category.std::string::compare("COMMENT"))){
		if(!category.std::string::compare(content)){
			special = "LINE_COMMENT";
		}else{
			special = "BLOCK_COMMENT";
		}
	}
        else if((!category.std::string::compare("INTCONST")) || (!category.std::string::compare("DOUBLECONST"))
                || (!category.std::string::compare("STRING")) || (!category.std::string::compare("IDENT"))){
		special = content;
        }
        else{
                fprintf(stderr,"error with special category: %s\n",__FILE__);
                exit(-1);
        }

        return special;
}

std::string alpha_token_t::toString(){
	std::ostringstream buffer;

	buffer << this->lineno << ": #" << this->order << " \"" << this->get_content() << "\" " << this->get_cat_asString()<<" ";
	if(!(this->get_cat_asString()).std::string::compare("STRING") || !(this->get_cat_asString()).std::string::compare("IDENT")){
		buffer << "\""<< this->token_special_category<<"\" ";
	}else{
		buffer << this->token_special_category;
	}
	buffer<<std::endl;

	return buffer.str();
}
