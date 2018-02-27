#include <map>

/*        std::map<char*,const char*> punctuation_special = {
		{"\/\/","LINE_COMMENT"},
		{"/*","BLOCK_COMMNET"}
	};
*/
        const char* find_special(const char*,const char*);

        std::map<const char*,const char*> punctuation_special = {
		{"{","LCURLY"},
		{"}","RCURLY"},
		{"[","LSQUARE"},
		{"]","RSQUARE"},
		{"(","LPARENTHESIS"},
		{")","RPARENTHESIS"},
		{";","SEMICOLON"},
		{",","COMMA"},
		{":","COLON"},
		{"::","SCOPE"},
		{".","DOT"},
		{"..","DOTDOT"}
	};

        std::map<const char*,const char*> operator_special = {
		{"=","EQUAL"},
		{"+","PLUS"},
		{"-","MINUS"},
		{"*","MUL"},
		{"/","DIV"},
		{">","GREATER"},
		{"<","LESS"},
		{"==","EQUAL_EQUAL"},
		{"!=","NOT_EQUAL"},
		{"++","PLUS_PLUS"},
		{"--","MINUS_MINUS"},
		{">=","GREATER_EQUAL"},
		{"<=","LESS_EQUAL"}
	};

        std::map<const char*,const char*> keyword_special={
		{"while","WHILE"},
		{"if","IF"},
		{"else","ELSE"},
		{"for","FOR"},
		{"function","FUNCTION"},
		{"return","RETURN"},
		{"break","BREAK"},
		{"continue","CONTINUE"},
		{"and","AND"},
		{"not","NOT"},
		{"or","OR"},
		{"local","LOCAL"},
		{"false","FALSE"},
		{"nil","NIL"}
	};



