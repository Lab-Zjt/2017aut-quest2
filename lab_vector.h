#ifndef LAB_VECTOR_H
#define LAB_VECTOR_H

#include <stdlib.h>

typedef double DataType;
struct lab__vector_st
{
    DataType *begin;
    DataType *end;
    DataType *storage_end;
};

struct lab__vector_iter_st
{
    DataType *ptr;
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
    temp.begin=(DataType *)malloc(sizeof(double)*2);
    temp.storage_end=&(temp.begin[1]);
    temp.end=temp.begin;
    return temp;
}
int size(VectorDescriptor* desc)
{
    return (desc->end-desc->begin);
}
void reserve(VectorDescriptor* desc,int resv_size)
{
    int now_size=size(desc);
    DataType *p=desc->begin;
    if(now_size<resv_size)
    {
        DataType *temp=(DataType*)malloc(sizeof(DataType)*resv_size);
        for(int i=0;i<now_size;i++)
        {
            temp[i]=p[i];
        }
        p=&(p[1]);
        /*for(;p!=desc->end;)
        {
            free(&(p[-1]));
        }*/
        free(desc->begin);
        desc->begin=temp;
        desc->end=&(temp[now_size]);
        desc->storage_end=&(temp[resv_size]);
    }
    else
    {
        printf("Error.The new size is NOT large than now.\n");
    }
}
void push_back(VectorDescriptor* desc,void* elem,int size)
{
    //memcpy(desc->end,elem,size);
    if(desc->end==desc->storage_end)
    {
        reserve(desc,(desc->end-desc->begin)*2);
    }
    desc->end[0]=*((DataType*)elem);
    desc->end=&(desc->end[1]);
}
VectorIterator begin(VectorDescriptor* desc)
{
    VectorIterator temp;
    temp.ptr=desc->begin;
    return temp;
}
VectorIterator end(VectorDescriptor* desc)
{
    VectorIterator temp;
    if(desc->end==desc->begin)
    {
        temp.ptr=desc->end;
        return temp;
    }
    temp.ptr=&(desc->end[-1]);
    return temp;
}
void* iter_dereference(VectorIterator iter)
{
    return iter.ptr;
}
VectorIterator iter_move(VectorIterator iter,int delta)
{
    iter.ptr=&(iter.ptr[delta]);
    return iter;
}// simulates: iter+8;
void pop_back(VectorDescriptor* desc)
{
    desc->end[-1]=0;
    desc->end=&(desc->end[-1]);
}
void erase(VectorDescriptor* desc,VectorIterator iter)
{
    for(;iter.ptr<desc->end;)
    {
        *(iter.ptr)=iter.ptr[1];
        iter.ptr++;
    }
    desc->end=&(desc->end[-1]);
}
void clear(VectorDescriptor* desc)
{
    DataType *p=desc->begin;
    for(;p<desc->end;)
    {
        *p=0;
        p=&(p[1]);
    }
    desc->end=desc->begin;
}
void destructor(VectorDescriptor* desc)
{
    /*DataType *p=&(desc->begin[1]);
    for(;p<=desc->end;)
    {
        free(&(p[-1]));
    }
    free(p);*/
    free(desc->begin);
}
int capacity(VectorDescriptor* desc)
{
    return (desc->storage_end-desc->begin);
}
void shrink_to_fit(VectorDescriptor* desc)
{
    /*DataType *p=&(desc->end[2]);
    for(;p!=desc->storage_end;)
    {
        free(&(p[-1]));
    }
    free(p);*/
    desc->storage_end=desc->end;
}
