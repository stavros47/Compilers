#include "headers/avm.h"

avm_table* avm_tablenew(void){
        avm_table* t =(avm_table*)malloc(sizeof(avm_table));
        AVM_WIPEOUT(*t);

        t->refCounter = t->total = 0;
        avm_table_bucketsinit(t->numIndexed);
        avm_table_bucketsinit(t->strIndexed);
        avm_table_bucketsinit(t->userfuncIndexed);
        avm_table_bucketsinit(t->libfuncIndexed);
        avm_table_bucketsinit(t->boolIndexed);
        avm_table_bucketsinit(t->tableIndexed);
        return t;
}

void avm_table_destroy(avm_table* t){
        avm_tablebucketdestroy(t->strIndexed);
        avm_tablebucketdestroy(t->numIndexed);
        avm_tablebucketdestroy(t->userfuncIndexed);
        avm_tablebucketdestroy(t->libfuncIndexed);
        avm_tablebucketdestroy(t->boolIndexed);
        avm_tablebucketdestroy(t->tableIndexed);
        free(t);
}

avm_memcell* avm_tablegetelem(avm_table* table,avm_memcell* key){
        
        if(key->type==number_m){
                return get(table->numIndexed[hashFunction(key->data.numVal)],key);
        }else if(key->type==string_m){
                return get(table->strIndexed[hashFunction(key->data.strVal)],key);
        }else if(key->type==userfunc_m ){
                return get(table->userfuncIndexed[hashFunction(avm_getfuncinfo(key->data.funcVal)->address)],key);
        }else if(key->type==libfunc_m ){
                return get(table->libfuncIndexed[hashFunction(key->data.libfuncVal)],key);
        }else if(key->type==bool_m ){
                return get(table->boolIndexed[hashFunction(key->data.boolVal)],key);
        }else if(key->type==table_m){
                return get(table->tableIndexed[hashFunction(key->data.tableVal)],key);
        }
        avm_error("Invalid type of key");
        return (avm_memcell*)0;  
}

void avm_tablesetelem(avm_table* table,avm_memcell* key,avm_memcell* value){
        avm_table_bucket** p;
        avm_table_bucket *tmp,*ptr;
        unsigned pos;
        if(value->type == nil_m){
                deleteKey(table,key);
                table->total--;
                return ;
        }

        if(key->type == number_m){
                tmp=insert(table->numIndexed,hashFunction(key->data.numVal),*key,*value);
        }else
        if (key->type == string_m){
                tmp=insert(table->strIndexed,hashFunction(key->data.strVal),*key,*value);
        }else
        if(key->type==userfunc_m){
                tmp=insert(table->userfuncIndexed,hashFunction(avm_getfuncinfo(key->data.funcVal)->address),*key,*value);
        }else
        if(key->type==libfunc_m){
                tmp=insert(table->libfuncIndexed,hashFunction(key->data.libfuncVal),*key,*value);
        }else
        if(key->type==bool_m){
                tmp=insert(table->boolIndexed,hashFunction(key->data.boolVal),*key,*value);
        }else
        if(key->type == table_m){
                tmp=insert(table->tableIndexed,hashFunction(key->data.tableVal),*key,*value);
        }
        else{
                avm_error("Invalid type of key");
                return;
        }
        
        if(tmp){
                table->total++;
                tmp->nextOrder = table->head;
                table->head = tmp;
        }
}

void avm_tableincrefcounter(avm_table* t){
	++t->refCounter;
}

void avm_tabledecrefcounter(avm_table* t){
	assert(t->refCounter > 0);
        if(!--t->refCounter)
                avm_table_destroy(t);
}

void avm_table_bucketsinit(avm_table_bucket** p){
        for(unsigned i=0;i<AVM_TABLE_HASHSIZE; ++i) 
                p[i] = (avm_table_bucket*)0;
}

void avm_tablebucketdestroy(avm_table_bucket** p){
        for(unsigned i=0;i<AVM_TABLE_HASHSIZE; ++i){
                for(avm_table_bucket* b = *p;b;){
                        avm_table_bucket* del = b;
                        b=b->next;
                        avm_memcellclear(&del->key);
                        avm_memcellclear(&del->value);
                        free(del);
                }
                p[i] = (avm_table_bucket*)0;
        }
}

unsigned hashFunction(avm_table* key){
        return hashFunction(key->total + key->refCounter);
}

unsigned hashFunction(unsigned key){
        return key%AVM_TABLE_HASHSIZE;
}

unsigned hashFunction(const char* key){
        unsigned int hash = 0U;
	for (int i = 0; key[i] != '\0'; i++)
		hash +=hash*3 + key[i]*7;

	return (unsigned)hash%AVM_TABLE_HASHSIZE;
}

avm_table_bucket* insert(avm_table_bucket** p,unsigned pos, avm_memcell key, avm_memcell value){
        avm_memcell* m = get(p[pos],&key);
        if(m->type!=nil_m){
                avm_assign(m,&value);
                return NULL;
        }
                
        avm_table_bucket* ptr = new avm_table_bucket();
        ptr->key = key;
        ptr->value = value;
        ptr->next = p[pos];
        p[pos] = ptr;        
        return ptr;
}

avm_memcell* get(avm_table_bucket* p,const char* key){
        avm_memcell *ps = new avm_memcell();
        ps->data.strVal = const_cast<char*>(key);
        ps->type = string_m;
        return get(p,ps);
}

avm_memcell* get(avm_table_bucket* p,avm_memcell* key){
        avm_table_bucket* tmp = p;
        while(tmp){
                check_eq_func_t f = check_eqFuncs[key->type];
                if(f){
                        if((*f)(&tmp->key,key)){
                                return &tmp->value;
                        }
                }else{
                        assert(0);
                }
                tmp=tmp->next;
        }

        avm_memcell* t = new avm_memcell();
        t->type=nil_m;
        return t;

}

void mydelete(avm_table_bucket* p,avm_memcell* key){
        avm_table_bucket* tmp = p,*prev;
        while(tmp){
                check_eq_func_t f = check_eqFuncs[key->type];
                if(f && (*f)(&tmp->key,key)){
                        if(prev)prev->next = tmp->next;
                        else p = tmp->next;
                        break;
                }
                prev=tmp;
                tmp=tmp->next;
        }
}

void deleteKey(avm_table* table,avm_memcell* key){
        if(key->type == number_m){
                mydelete(table->numIndexed[hashFunction(key->data.numVal)],key);
        }
        else if (key->type == string_m){
                mydelete(table->strIndexed[hashFunction(key->data.strVal)],key);
        }else if(key->type==userfunc_m ){
                mydelete(table->userfuncIndexed[hashFunction(key->data.funcVal)],key);
        }else if(key->type==libfunc_m ){
                mydelete(table->libfuncIndexed[hashFunction(key->data.libfuncVal)],key);
        }else if(key->type==bool_m ){
                mydelete(table->boolIndexed[hashFunction(key->data.boolVal)],key);
        }else if(key->type==table_m ){
                mydelete(table->tableIndexed[hashFunction(key->data.tableVal)],key);
        }                             
        else{
                avm_error("Invalid type of key");
                return;
        }        
}

std::string hash_toString(avm_table_bucket** p){
        std::stringstream buffer;
        for(int i=0;i<AVM_TABLE_HASHSIZE;i++){
                if(p[i])
                        buffer<<"["<<i<<"]["<<avm_tostring(&p[i]->key)
                                <<" : ["<<avm_tostring(&p[i]->value)<<"] \n";
        }

        return buffer.str();
}