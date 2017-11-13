#ifndef LAB_VECTOR_H
#define LAB_VECTOR_H

#include <string.h>

struct lab__vector_st
{
    void *begin;
    void *end;
    void *storage_end;
    int data_size;
};

struct lab__vector_iter_st
{
    void *ptr;
    int data_size;
};

// NOT MODIFY BELOW
typedef struct lab__vector_st VectorDescriptor;
typedef struct lab__vector_iter_st VectorIterator;

struct lab__vector_api_st{
    VectorDescriptor (*constructor)();
    void (*push_back)(VectorDescriptor* desc,void* elem,int size);
    VectorIterator (*begin)(VectorDescriptor* desc);
    VectorIterator (*end)(VectorDescriptor* desc);
    void* (*iter_dereference)(VectorIterator iter);
    VectorIterator (*iter_move)(VectorIterator iter,int delta); // simulates: iter+8;
    int (*size)(VectorDescriptor* desc);
    void (*pop_back)(VectorDescriptor* desc);
    void (*erase)(VectorDescriptor* desc,VectorIterator iter);
    void (*clear)(VectorDescriptor* desc);
    void (*destructor)(VectorDescriptor* desc);
    int (*capacity)(VectorDescriptor* desc);
    void (*shrink_to_fit)(VectorDescriptor* desc);
    void (*reserve)(VectorDescriptor* desc,int resv_size);
};

typedef struct lab__vector_api_st VectorAPI;

extern VectorAPI vector;

#endif
VectorDescriptor constructor()
{
    VectorDescriptor temp;
    temp.begin=NULL;
    temp.storage_end=NULL;
    temp.end=NULL;
    temp.data_size=0;
    return temp;
}
int size(VectorDescriptor* desc)
{
    int  size=((char*)desc->end-(char*)desc->begin);
    return size/desc->data_size;
}
void reserve(VectorDescriptor* desc,int resv_size)
{
    int data_size=desc->data_size;
    int now_size=(char*)desc->end-(char*)desc->begin+data_size;
    if(now_size<resv_size)
    {
        void *temp=malloc(resv_size);
        for(int i=0;i<now_size;i+=desc->data_size)
        {
            memcpy(temp+i,desc->begin+i,data_size);
        }
        free(desc->begin);
        desc->begin=temp;
        desc->end=temp+now_size-data_size;
        desc->storage_end=temp+resv_size-data_size;
    }
    /*else
    {
        printf("Error.The new size is NOT large than now.\n");
    }*/
}
void push_back(VectorDescriptor* desc,void* elem,int size)
{
    if(!desc->data_size)
    {
        desc->begin=malloc(size*2);
        desc->data_size=size;
        desc->end=desc->begin;
        desc->storage_end=desc->begin+desc->data_size;
        memcpy(desc->end,elem,desc->data_size);
        desc->end += desc->data_size;
    }
    else
    if(size!=desc->data_size)
    {
        // printf("The size of elements MUST be same in the same vector.\n");
    }
    else
    {
        if (desc->end == desc->storage_end)
        {
            reserve(desc, ((char*)desc->end - (char*)desc->begin+desc->data_size) * 2);
        }
        memcpy(desc->end,elem,desc->data_size);
        desc->end += desc->data_size;
    }
}
VectorIterator begin(VectorDescriptor* desc)
{
    VectorIterator temp;
    temp.ptr=desc->begin;
    temp.data_size=desc->data_size;
    return temp;
}
VectorIterator end(VectorDescriptor* desc)
{
    VectorIterator temp;
    temp.ptr=desc->end;
    temp.data_size=desc->data_size;
    return temp;
}
void* iter_dereference(VectorIterator iter)
{
    return iter.ptr;
}
VectorIterator iter_move(VectorIterator iter,int delta)
{
    iter.ptr+=iter.data_size;
    return iter;
}// simulates: iter+8;
void pop_back(VectorDescriptor* desc)
{
    desc->end-=desc->data_size;
}
void erase(VectorDescriptor* desc,VectorIterator iter)
{
    int data_size=desc->data_size;
    for(;iter.ptr<desc->end;)
    {
        memcpy(iter.ptr,iter.ptr+data_size,data_size);
        iter.ptr+=data_size;
    }
    desc->end-=data_size;
}
void clear(VectorDescriptor* desc)
{
    desc->end=desc->begin;
}
void destructor(VectorDescriptor* desc)
{
    free(desc->begin);
}
int capacity(VectorDescriptor* desc)
{
    return ((char*)desc->storage_end-(char*)desc->begin+desc->data_size)/(desc->data_size);
}
void shrink_to_fit(VectorDescriptor* desc)
{
    desc->storage_end=desc->end;
}
