#include "HashTable.h"

HashTable::HashTable(){
	maxscopesize=SCOPE_SIZE;
	SymTable = (Symbol**)malloc(sizeof(Symbol*)*HASH_SIZE);
	ScopeHead = (Symbol**)malloc(sizeof(Symbol*)*maxscopesize);
}

unsigned int HashTable::hashfunc(std::string name){
	unsigned int hash = 0U;
	for (int i = 0; name[i] != '\0'; i++)
		hash +=hash*3 + name[i]*7;

	return hash%HASH_SIZE;
}

Symbol* HashTable::insert(Symbol* ptr){
	int pos=hashfunc(ptr->name);
	if(SymTable[pos]==NULL){
		SymTable[pos]=ptr;
	}else{
		ptr->next=SymTable[pos];
		SymTable[pos]=ptr;
	}
	
	if(ptr->scope>=maxscopesize){
		maxscopesize+=SCOPE_SIZE;
		Symbol** tmp = (Symbol**)malloc(sizeof(Symbol*)*maxscopesize);
		if(!tmp){
			fprintf(stderr,"reallocation error in file: %s at line:%d\n",__FILE__,__LINE__);
                        exit(-1);

		}

		for(int i=0;i<maxscopesize-SCOPE_SIZE;i++){
			tmp[i] = ScopeHead[i];
		}

		ScopeHead=tmp;
	}

	if(ScopeHead[ptr->scope]==NULL){
		ScopeHead[ptr->scope]=ptr;
	}else{
		ptr->scopeNext=ScopeHead[ptr->scope];
		ScopeHead[ptr->scope]=ptr;
	}

	return ptr;
}

Symbol* HashTable::lookup(std::string name){

	Symbol* iter;
	iter = SymTable[hashfunc(name)];

	while(iter){
		if(!iter->name.compare(name))
			return iter;

		iter=iter->next;
	}

	return NULL;	
}

Symbol* HashTable::lookup(std::string name,int scope){
	return lookup(name,scope,0);
}

Symbol* HashTable::lookup(std::string name,int scope,int flag){
	Symbol* iter;
	iter = ScopeHead[scope];

	while(iter){
                if(!iter->name.compare(name))
                        return iter;

                iter=iter->scopeNext;
	}

	if(flag){
		for(int i=scope-1;i>=0;i--){
			return lookup(name,scope-1,1);
		}
	}

	return NULL;
}

void HashTable::hideScope(int scope){
	Symbol* iter;
	iter=ScopeHead[scope];

	while(iter){
		iter->hidden=true;
		iter=iter->scopeNext;
	}
}

std::string HashTable::toString(){
	Symbol* iter;
	std::ostringstream buffer;
	
	for(int i=0;i<733;i++){
		iter=SymTable[i];
		if(iter!=NULL)buffer<<"Position:"<<i<<std::endl;
		while(iter!=NULL){
			buffer<<sym_toString(iter)<<std::endl;
			iter=iter->next;
		}
	}

	return buffer.str();
}

std::string HashTable::scopetoString(int scope){
	Symbol* iter;
	std::ostringstream buffer;

	iter = ScopeHead[scope];
	while(iter!=NULL){
		buffer<<sym_toString(iter)<<std::endl;
		iter=iter->scopeNext;
	}
	return buffer.str();
}

std::string HashTable::allscopestoString(){
	std::ostringstream buffer;
	
	for(int i=0;i<maxscopesize;i++){
		if(ScopeHead[i]==NULL) {continue;}
		buffer<<"---------------      Scope #"<<i<<"      ---------------"<<std::endl;
		buffer<<scopetoString(i)<<std::endl;

	}

	return buffer.str();
}



