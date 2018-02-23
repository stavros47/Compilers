class alpha_token_t {

private:
	unsigned int lineno;
	char* token_content;
	static int token_counter;
	enum token_cat {KEYWORD,OPERATOR,INTCONST,DOUBLECONST,STRING,IDENT,COMMENT1,COMMENT2};
//	enum keyword_cat {IF,ELSE,WHILE,FOR,FUNCTION,RETURN,BREAK,CONTINUE,AND,NOT,OR,LOCAL,FALSE,NIL};
//	enum operand_cat {=,+,-,*,/,%,==,!=,++,--,>,<,>=,<=};
//	enum punctuation_cat {{,},[,],(,),;,,,:,::,.,..};

public:
	alpha_token_t();

	~alpha_token_t();

	void set_lineno(int);

	unsigned int get_lineno();

	void set_content(const char*);

	char* get_token_content();

	unsigned int get_tokcnt();

};
