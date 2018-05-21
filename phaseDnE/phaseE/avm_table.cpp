#include "headers/avm.h"

avm_table* avm_tablenew(void){
        avm_table* t =(avm_table*)malloc(sizeof(avm_table));
        AVM_WIPEOUT(*t);

        t->refCounter = t->total = 0;
        avm_table_bucketsinit(t->numIndexed);
        avm_table_bucketsinit(t->strIndexed);

        return t;
}

void avm_table_destroy(avm_table* t){
        avm_tablebucketdestroy(t->strIndexed);
        avm_tablebucketdestroy(t->numIndexed);
        free(t);
}

unsigned hashFunction(unsigned key){
        return key%AVM_TABLE_HASHSIZE;
}

unsigned hashFunction(char* key){
        unsigned int hash = 0U;
	for (int i = 0; key[i] != '\0'; i++)
		hash +=hash*3 + key[i]*7;

	return (unsigned)hash%AVM_TABLE_HASHSIZE;
}

avm_table_bucket* insert(avm_table_bucket** p,unsigned pos, avm_memcell key, avm_memcell value){
        avm_table_bucket* ptr = new avm_table_bucket();
        ptr->key = key;
        ptr->value = value;
        ptr->next = p[pos];
        p[pos] = ptr;        
        return ptr;
}

avm_memcell* get(avm_table_bucket* p,avm_memcell* key){
        avm_table_bucket* tmp = p;
        while(tmp){
                check_eq_func_t f = check_eqFuncs[key->type];
                if(f){
                        
                        if((*f)(&tmp->key,key))
                                return &tmp->value;
                }else{
                        assert(0);
                }
                tmp=tmp->next;
        }
        return (avm_memcell*)0;

}

avm_memcell* avm_tablegetelem(avm_table* table,avm_memcell* key){
        if(key->type==number_m){
                return get(table->numIndexed[hashFunction(key->data.numVal)],key);
        }else if(key->type==string_m){
                return get(table->strIndexed[hashFunction(key->data.strVal)],key);
        }

        avm_error("Invalid type of key");
        return (avm_memcell*)0;  
}

void avm_tablesetelem(avm_table* table,avm_memcell* key,avm_memcell* value){
        avm_table_bucket** p;
        avm_table_bucket *tmp,*ptr;
        unsigned pos;

        if(key->type == number_m){
                tmp=insert(table->numIndexed,hashFunction(key->data.numVal),*key,*value);
        }
        else if (key->type == string_m){
                tmp=insert(table->strIndexed,hashFunction(key->data.strVal),*key,*value);
        }                
        else{
                avm_error("Invalid type of key");
                return;
        }

        if(table->head){
                ptr = table->head;
                while(ptr->nextOrder){
                        ptr = ptr->nextOrder;
                }

                ptr->nextOrder=tmp;
        }else{
                table->head = tmp;
        }

        // for(int i=0;i<AVM_TABLE_HASHSIZE;i++){
        //         if(table->strIndexed[i])
        //                 std::cout<<"KEY:"<<avm_tostring(&table->strIndexed[i]->key)
        //                         <<"VALUE:"<<avm_tostring(&table->strIndexed[i]->value)<<std::endl;
        // }

        // for(int i=0;i<AVM_TABLE_HASHSIZE;i++){
        //         if(table->numIndexed[i])
        //                 std::cout<<"KEY:"<<avm_tostring(&table->numIndexed[i]->key)
        //                         <<"VALUE:"<<avm_tostring(&table->numIndexed[i]->value)<<std::endl;
        // }

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

