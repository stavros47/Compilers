#ifndef _AVM_TABLE_H_
#define _AVM_TABLE_H_

#define AVM_TABLE_HASHSIZE 211

struct avm_table_bucket{
        avm_memcell key;
        avm_memcell value;
        avm_table_bucket* nextOrder;
        avm_table_bucket* next;
};

struct avm_table{
        unsigned                refCounter;
        avm_table_bucket*       strIndexed[AVM_TABLE_HASHSIZE];
        avm_table_bucket*       numIndexed[AVM_TABLE_HASHSIZE];
        avm_table_bucket*       userfuncIndexed[AVM_TABLE_HASHSIZE];
        avm_table_bucket*       libfuncIndexed[AVM_TABLE_HASHSIZE];
        avm_table_bucket*       boolIndexed[AVM_TABLE_HASHSIZE];
        avm_table_bucket*       tableIndexed[AVM_TABLE_HASHSIZE];
        avm_table_bucket*       head;
        unsigned                total;
};

avm_table*      avm_tablenew(void);
void            avm_tabledestroy(avm_table*);
avm_memcell*    avm_tablegetelem(avm_table*,avm_memcell*);
void            avm_tablesetelem(avm_table*,avm_memcell*,avm_memcell*);

void avm_tableincrefcounter(avm_table*);
void avm_tabledecrefcounter(avm_table*);
void avm_table_bucketsinit(avm_table_bucket**);
void avm_tablebucketdestroy(avm_table_bucket**);

unsigned hashFunction(avm_table*);
unsigned hashFunction(unsigned);
unsigned hashFunction(const char*);

avm_table_bucket* insert(avm_table_bucket**,unsigned,avm_memcell, avm_memcell);
avm_table_bucket* get_bucket(avm_table_bucket*,avm_memcell*);
avm_memcell* get(avm_table_bucket*,const char*);
avm_memcell* get(avm_table_bucket*,avm_memcell*);
void mydelete(avm_table_bucket*,avm_memcell*);
void deleteKey(avm_table* table,avm_memcell* key);
std::string hash_toString(avm_table_bucket**);

#endif
