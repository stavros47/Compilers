#include <string>
#include <vector>
#include <iostream>
#include <sstream>

class alpha_token_t {
public:
	enum token_cat {KEYWORD,OPERATOR,INTCONST,REALCONST,STRING,IDENT,PUNCTUATION,COMMENT};

	alpha_token_t(unsigned int,std::string,token_cat);

	unsigned int get_lineno();

	unsigned int get_order();

	std::string get_content();

	token_cat get_cat();

	std::string get_cat_asString();

	std::string get_special_category();

	std::string find_special(std::string,std::string);

	std::string toString();

private:
	static int token_counter;
	unsigned int lineno;
	unsigned int order;
	std::string token_content;
	token_cat token_category;
	std::string token_special_category;
};
