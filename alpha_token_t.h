#include <string>
#include <vector>
#include <iostream>
#include <sstream>

class alpha_token_t {
public:
	enum token_cat {KEYWORD,OPERATOR,INTCONST,REALCONST,STRING,IDENT,PUNCTUATION,COMMENT};

	alpha_token_t(unsigned int,const char*,token_cat);

	unsigned int get_lineno();

	unsigned int get_order();

	const char* get_content();

	token_cat get_cat();

	const char* get_cat_asString();

	const char* get_special_category();

	const char* find_special(const char*,const char*);

	std::string toString();

private:

	static int token_counter;
	unsigned int lineno;
	unsigned int order;
	const char* token_content;
	token_cat token_category;
	const char* token_special_category;

};
