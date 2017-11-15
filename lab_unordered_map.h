#ifndef LAB_UNORDERED_MAP_H
#define LAB_UNORDERED_MAP_H

#include "labafx.h"
typedef struct hash_list_node
{
    struct hash_list_node next;
    struct hash_list_node prev;
    Pair* pair;
}HashListNode;
typedef struct hash_bucket
{
    HashListNode* first;
}HashBucket;
struct lab__unordered_map_st
{
    HashBucket* begin;
    HashBucket* end;
    Hasher hashfunc;
    int size;
};

struct lab__unordered_map_iter_st{

};

// DO NOT MODIFY BELOW
typedef struct lab__unordered_map_st UnorderedMapDescriptor;
typedef struct lab__unordered_map_iter_st UnorderedMapIterator;

struct lab__unordered_map_api_st{
    UnorderedMapDescriptor (*constructor)(Hasher hashfunc);
    int (*size)(UnorderedMapDescriptor* desc);
    void (*insert)(UnorderedMapDescriptor* desc,Pair kvpair);
    void (*erase)(UnorderedMapDescriptor* desc,UnorderedMapIterator iter);
    void (*clear)(UnorderedMapDescriptor* desc);
    UnorderedMapIterator (*begin)(UnorderedMapDescriptor* desc);
    UnorderedMapIterator (*end)(UnorderedMapDescriptor* desc);
    UnorderedMapIterator (*iter_next)(UnorderedMapIterator it);
    UnorderedMapIterator (*iter_prev)(UnorderedMapIterator it);
    Pair (*iter_dereference)(UnorderedMapIterator it);
    UnorderedMapIterator (*find)(UnorderedMapDescriptor* desc,void* key,int keysize);
    void (*destructor)(UnorderedMapDescriptor *desc);
};

typedef struct lab__unordered_map_api_st UnorderedMapAPI;
extern UnorderedMapAPI um;

#endif
UnorderedMapDescriptor constructor(Hasher hashfunc)
{
    UnorderedMapDescriptor temp;
    temp.begin=(HashBucket*)malloc(sizeof(HashBucket)*53);
    temp.end=temp.begin+52;
    temp.hashfunc=hashfunc;
    temp.size=0;
    return temp;
}
int size(UnorderedMapDescriptor* desc)
{
    return (desc->size);
}
void rehash(int hash_size,UnorderedMapDescriptor* desc)
{
    unsigned long int prime_hash_list[26]={53,97,193,389,769,1543,3079,6151,12289,24593,49157,98317,196613,393241,
                                    786433,1572869,3145739,6291469,12582917,25165843,50331653,100663319,
                                     201326611,402653189,805306457,1610612741};
    for(int i=0;i<26;i++)
    {
        if(prime_hash_list[i]>hash_size)
        {
            hash_size=prime_hash_list[i];
            break;
        }
    }
    HashBucket* new_bucket=(HashBucket*)malloc(sizeof(HashBucket)*hash_size);
    int size=desc->end-desc->begin;
    for(int i=0;i<size;i++)
    {
        new_bucket[i].first=desc->begin[i].first;
    }
    free(desc->begin);
    desc->begin=new_bucket;
    desc->end=desc->begin+hash_size-1;
}
void insert(UnorderedMapDescriptor* desc,Pair kvpair)
{
    unsigned int hash=desc->hashfunc(kvpair.key,kvpair.keysize);
    if(hash>(desc->end-desc->begin-1))
    {
        rehash(hash,desc);
    }
    HashListNode* new_node=(HashListNode*)malloc(sizeof(HashListNode));
    Pair* new_pair=(Pair*)malloc(sizeof(Pair));
    void* new_key=malloc(kvpair.keysize);
    void* new_value=malloc(kvpair.valuesize);
    memcpy(new_key,kvpair.key,kvpair.keysize);
    memcpy(new_value,kvpair.value,kvpair.valuesize);
    new_pair->valuesize=kvpair.valuesize;
    new_pair->keysize=kvpair.keysize;
    new_pair->key=new_key;
    new_pair->value=new_value;
    new_node->pair=new_pair;
    new_node->next=NULL;
    if(desc->begin[hash].first!=NULL)
    {
        HashListNode* p=desc->begin[hash].first;
        for(;p->next!=NULL;)
        {
            p=p->next;
        }
        p->next=new_node;
        new_node->prev=p;
    }
    else
    {
        desc->begin[hash].first=new_node;
        new_node->prev=NULL;
    }
}
void (*erase)(UnorderedMapDescriptor* desc,UnorderedMapIterator iter);
void clear(UnorderedMapDescriptor* desc)
{
    int size=desc->end-desc->begin;
    for(int i=0;i<size;i++)
    {
        if(desc->begin[i].first!=NULL)
        {
            HashListNode* p=desc->begin[i].first;
            for(;p->next!=NULL;)
            {
                free(p->pair->value);
                free(p->pair->key);
                free(p->pair);
                p=p->next;
                free(p->prev);
            }
            free(p->pair->value);
            free(p->pair->key);
            free(p->pair);
            free(p);
            desc->begin[i].first=NULL;
        }
    }
}
UnorderedMapIterator (*begin)(UnorderedMapDescriptor* desc);
UnorderedMapIterator (*end)(UnorderedMapDescriptor* desc);
UnorderedMapIterator (*iter_next)(UnorderedMapIterator it);
UnorderedMapIterator (*iter_prev)(UnorderedMapIterator it);
Pair (*iter_dereference)(UnorderedMapIterator it);
UnorderedMapIterator (*find)(UnorderedMapDescriptor* desc,void* key,int keysize);
void (*destructor)(UnorderedMapDescriptor *desc);