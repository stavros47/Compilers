#include "Symbol.h"

Symbol* construct_Symbol(std::string newName,int newType,int newLineno,int newScope,unsigned newRange,scopespace_t newSpace,int newOffset){
        Symbol* tmp = new Symbol();
        tmp->name=newName;
        tmp->type=(Type)newType;
        tmp->lineno=newLineno;
        tmp->scope=newScope;
	tmp->range=newRange;
	tmp->scopespace = newSpace;
	tmp->offset=newOffset;
        tmp->hidden=false;
        tmp->scopeNext=NULL;
        tmp->next=NULL;
	return tmp;
}

std::string getTypeasString(Symbol* sym){
        switch(sym->type){
                case 0: return "GLOBAL";break;
                case 1: return "LOCAL";break;
                case 2: return "FUNC_ARG";break;
                case 3: return "LIB_FUNC";break;
                case 4: return "USER_FUNC";break;
        }
}

std::string getScopeSpaceasString(Symbol* sym){
		switch(sym->scopespace){
			case 0: return "Program Variable";break;
			case 1: return "Function Local";break;
			case 2: return "Formal Argument";break;
		}
}

std::string sym_toString(Symbol* sym){
        std::ostringstream buffer;

        buffer<<"\""<<sym->name<<"\" ";
        buffer<<"["<<getTypeasString(sym)<<"] ";
        buffer<<"(line:"<<sym->lineno<<") ";
        buffer<<"(scope:"<<sym->scope<<") ";
	buffer<<"(scospace:"<<getScopeSpaceasString(sym)<<") ";
	buffer<<"(offset:"<<sym->offset<<") ";
        buffer<<((sym->hidden) ? "[hidden]" : "[not hidden]");

        return buffer.str();
}
