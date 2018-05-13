
#include "avm.h"

static void avm_initstack(void){
        for(unsigned i = 0; i<AVM_STACKSIZE; ++i){
                AVM_WIPEOUT(stack[i]);
                stack[i].type = undef_m;
        }
}

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
/****************************************************/
avm_memcell* avm_tablegetelem(avm_table* table,avm_memcell* key){
	return (avm_memcell*)0;
}

void avm_tablesetelem(avm_table* table,avm_memcell* key,avm_memcell* value){
	
}
/****************************************************/

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

