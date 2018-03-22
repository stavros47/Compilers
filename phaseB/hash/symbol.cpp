
#ifndef SYMBOL_H
#define SYMBOL_H

#include "symbol.h"

Symbol::Symbol(){
	this->name='\0';
	this->type=UNDEFINED;
	this->lineno=-1;
	this->scope = -1;
	this->hidden=false;
	this->scopeNext=NULL;
	this->next=NULL;
}

Symbol::Symbol(std::string newName,int newType,int newLineno,int newScope,bool newHide){
	this->name=newName;
	this->type=(Symbol::Type)newType;
	this->lineno=newLineno;
	this->scope=newScope;
	this->hidden=newHide;
	this->scopeNext=NULL;
	this->next=NULL;
}

std::string Symbol::getName(){
	return this->name;
}

void Symbol::setName(std::string newName){
	this->name = newName;
}

int Symbol::getLineno(){
	return this->lineno;
}

void Symbol::setLineno(int newLineno){
	this->lineno = newLineno;
}

int Symbol::getScope(){
	return this->scope;
}

void Symbol::setScope(int newScope){
	this->scope = newScope;
}

void Symbol::up_scope(){
	this->scope++;
}

void Symbol::down_scope(){
	this->scope--;
}

bool Symbol::isHidden(){
	return this->hidden;
}

void Symbol::hide(){
	hidden=true;
}

void Symbol::unhide(){
	hidden=false;
}

Symbol* Symbol::getScopeNext(){
	return this->scopeNext;
}

void Symbol::setScopeNext(Symbol* newScopeNext){
	this->scopeNext = newScopeNext;
}

Symbol* Symbol::getNext(){
	return this->next;
}

void Symbol::setNext(Symbol* newNext){
	this->next=newNext;
}

Symbol::Type Symbol::getType(){
	return this->type;
}

std::string Symbol::getTypeasString(){
	switch(this->type){
		case 0: return "UNDEFINED";break;
		case 1: return "VARIABLE";break;
		case 2: return "FUNC_ARG";break;
		case 3: return "LIB_FUNC";break;
		case 4: return "USER_FUNC";break;
	}
}

void Symbol::setType(Symbol::Type newType){
	this->type=newType;
}

std::string Symbol::toString(){
	std::ostringstream buffer;

	buffer<<this->name<<" | ";
	buffer<<this->getTypeasString()<<" | ";
	buffer<<this->lineno<<" | ";
	buffer<<this->scope<<" | ";
	buffer<<((this->hidden) ? "hidden" : "not hidden")<<" | ";

	return buffer.str();
}


#endif
