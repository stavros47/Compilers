#include <map>
#include <string.h>

        std::map<std::string,std::string> punctuation_special = {
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

        std::map<std::string,std::string> operator_special = {
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

        std::map<std::string,std::string> keyword_special={
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



