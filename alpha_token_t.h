class alpha_token_t {
public:
	enum token_cat {KEYWORD,OPERATOR,INTCONST,DOUBLECONST,STRING,IDENT,COMMENT};

private:
	enum keyword_cat {IF,ELSE,WHILE,FOR,FUNCTION,RETURN,BREAK,CONTINUE,AND,NOT,OR,LOCAL,FALSE,NIL};
	enum operand_cat {EQUAL,PLUS,MINUS,MUL,DIV,PERCENT,EQUAL_EQUAL,NOT_EQUAL,PLUS_PLUS,MINUS_MINUS,GREATER,LESS,GREATER_EQUAL,LESS_EQUAL};
	enum punctuation_cat {LCURLY,RCURLY,LSQUARE,RSQUARE,LPARENTHESIS,RPARENTHESIS,SEMICOLON,COMMA,COLON,SCOPE,DOT,DOT_DOT};
	enum comment_cat {LINE_COMMENT,BLOCK_COMMENT};

	static int token_counter;
	unsigned int lineno;
	unsigned int order;
	char* token_content;
	token_cat token_category;
	keyword_cat keyword_special;
	operand_cat operand_special;
	punctuation_cat punctuation_special;
public:
	alpha_token_t(unsigned int,char*,token_cat);

	~alpha_token_t();

	void set_lineno(int);

	unsigned int get_lineno();

	void set_order(unsigned int);

	unsigned int get_order();

	void set_content(char*);

	char* get_content();

	void set_cat(token_cat);

	token_cat get_cat();

	const char* get_cat_asString();

	void toString();
};
