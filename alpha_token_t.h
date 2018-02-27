class alpha_token_t {
public:
	enum token_cat {KEYWORD,OPERATOR,INTCONST,REALCONST,STRING,IDENT,PUNCTUATION,COMMENT};

	alpha_token_t(unsigned int,const char*,token_cat);

	~alpha_token_t();

	void set_lineno(int);

	unsigned int get_lineno();

	void set_order(unsigned int);

	unsigned int get_order();

	void set_content(char*);

	const char* get_content();

	void set_cat(token_cat);

	token_cat get_cat();

	const char* get_cat_asString();

	const char* get_special_category();

	const char* find_special(const char*,const char*);

	void toString();

private:

	static int token_counter;
	unsigned int lineno;
	unsigned int order;
	const char* token_content;
	token_cat token_category;
	const char* token_special_category;

};
