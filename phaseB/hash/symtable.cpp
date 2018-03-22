#ifndef SYMTABLE_H
#define SYMTABLE_H
#include "symtable.h"

HashTable::HashTable(){
	totalScope=SCOPE_SIZE;
	SymTable = (Symbol**)malloc(sizeof(Symbol*)*HASH_SIZE);
	ScopeHead = (Symbol**)malloc(sizeof(Symbol*)*totalScope);
}

unsigned int HashTable::hashfunc(std::string name){
	unsigned int hash = 0U;
	for (int i = 0; name[i] != '\0'; i++)
		hash +=hash*3 + name[i]*7;

	return hash%HASH_SIZE;
}

void HashTable::insert(Symbol* ptr){
	int pos=hashfunc(ptr->getName());
	
	if(SymTable[pos]==NULL){
		SymTable[pos]=ptr;		
	}else{
		ptr->setNext(SymTable[pos]);
		SymTable[pos]=ptr;
	}

	if(ptr->getScope()>=totalScope){
		totalScope+=SCOPE_SIZE;
		ScopeHead = (Symbol**)realloc(ScopeHead,totalScope*sizeof(Symbol*));
		if(!ScopeHead){
			fprintf(stderr,"reallocation error in file: %s at line:%d\n",__FILE__,__LINE__);
                        exit(-1);

		}
	}

	if(ScopeHead[ptr->getScope()]==NULL){
		ScopeHead[ptr->getScope()]=ptr;
	}else{
		ptr->setScopeNext(ScopeHead[ptr->getScope()]);
		ScopeHead[ptr->getScope()]=ptr;
	}
}

Symbol* HashTable::lookup(std::string name){

	Symbol* iter;
	iter = SymTable[hashfunc(name)];

	while(iter){
		if(!iter->getName().compare(name))
			return iter;

		iter=iter->getNext();
	}

	return NULL;	
}

Symbol* HashTable::lookup(std::string name,int scope){
	Symbol* iter;
	iter = ScopeHead[scope];

	while(iter){
                if(!iter->getName().compare(name))
                        return iter;

                iter=iter->getScopeNext();
	}

	return NULL;
}

std::string HashTable::toString(){
	Symbol* iter;
	std::ostringstream buffer;
	
	for(int i=0;i<509;i++){
		iter=SymTable[i];
		while(iter!=NULL){
			buffer<<iter->toString()<<std::endl;
			iter=iter->getNext();
		}
	}

	return buffer.str();
}

std::string HashTable::scopetoString(int scope){
	Symbol* iter;
	std::ostringstream buffer;

	iter = ScopeHead[scope];

	while(iter!=NULL){
		buffer<<iter->toString()<<std::endl;
		iter=iter->getScopeNext();
	}
	return buffer.str();
}

std::string HashTable::allscopestoString(){
	std::ostringstream buffer;
	
	for(int i=0;i<8 && ScopeHead[i]!=NULL;i++){
		buffer<<i<<":\n"<<scopetoString(i)<<std::endl;
	}

	return buffer.str();
}
#endif
