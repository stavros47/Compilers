#include <string>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
class Symbol{

	public:
		enum Type {UNDEFINED,VARIABLE,FUNC_ARG,LIBRARY_FUNC,PROGRAM_FUNC};

		Symbol();
		Symbol(std::string,int,int,int,bool);

		std::string getName();
		void setName(std::string);

		int getLineno();
		void setLineno(int);

		int getScope();
		void setScope(int newScope);
		void up_scope();
		void down_scope();

		bool isHidden();
		void hide();
		void unhide();

		Symbol* getScopeNext();
		void setScopeNext(Symbol*);

		Symbol* getNext();
		void setNext(Symbol*);

		Type getType();
		std::string getTypeasString();
		void setType(Type newType);

		std::string toString();

	private:
		std::string name;
		Type type;
/*		union{
			int intVal;
			double realVal;
			char* strVal;
		};	*/
		int lineno;
		int scope;
		bool hidden;
		Symbol* scopeNext;
		Symbol* next;
};
