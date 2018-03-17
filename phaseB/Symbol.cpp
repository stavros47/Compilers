#include <Symbol.h>

Symbol::Symbol() {}

void Symbol::setName(string name){
    name = name;
}

string Symbol::getName(){
    return name; 
}  

void Symbol::setType(string type){
    type = type;
}

string Symbol::getType(){
    return type;
}

void Symbol::setScope(int scope){
    scope = scope;
}

int Symbol::getScope(){
    return scope;
}

void Symbol::setLineNumber(int lineNumber){
    lineNumber = lineNumber;
}
int Symbol::getLineNumber(){
    return lineNumber;
}

void Symbol::insertFunctionArgument(Symbol newArgument){
    //TODO:
}