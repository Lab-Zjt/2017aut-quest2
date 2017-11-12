#ifndef LAB_PRIORITY_QUEUE
#define LAB_PRIORITY_QUEUE

#include <cstdlib>
#include "labafx.h"

typedef double DataType;
struct lab__priority_queue_st
{
    DataType *begin;
    DataType *end;
    DataType *storage_end;
    Comparator cmp;
};


// DO NOT MODIFY BELOW

typedef struct lab__priority_queue_st PriorityQueueDescriptor;
// typedef struct lab__priority_queue_iter_st PriorityQueueIterator;

struct lab__priority_queue_api_st{
    PriorityQueueDescriptor (*constructor)(Comparator compfunc);
    int (*size)(PriorityQueueDescriptor* desc);
    void (*push)(PriorityQueueDescriptor* desc,void* key,int size);
    void* (*top)(PriorityQueueDescriptor* desc);
    void (*pop)(PriorityQueueDescriptor* desc);
    void (*clear)(PriorityQueueDescriptor* desc);
    void (*destructor)(PriorityQueueDescriptor* desc);
};

typedef struct lab__priority_queue_api_st PriorityQueueAPI;
extern PriorityQueueAPI prq;

#endif
int default_compfunc_max_heap(void* a,int asize,void* b,int bsize)
{
    if(*(DataType*)a>(*(DataType*)b))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
PriorityQueueDescriptor constructor(Comparator compfunc)
{
    PriorityQueueDescriptor temp;
    temp.begin=(DataType *)malloc(sizeof(double)*2);
    temp.storage_end=&(temp.begin[1]);
    temp.end=temp.storage_end;
    if(compfunc!=NULL)
    {
        temp.cmp=compfunc;
    }
    else
    {
        temp.cmp=default_compfunc_max_heap;
    }
    return temp;
}
int size(PriorityQueueDescriptor* desc)
{
    return (desc->end-desc->begin-1);
}
void push(PriorityQueueDescriptor* desc,void* key,int size)
{
    if(desc->end==desc->storage_end)
    {
        int now_size = desc->end-desc->begin;
        DataType *p = desc->begin;
        DataType *temp = (DataType *) malloc(sizeof(DataType) * now_size*2);
        for (int i = 0 ; i < now_size ; i ++)
        {
            temp[i] = p[i];
        }
        p = &(p[1]);
        free(desc->begin);
        desc->begin = temp;
        desc->end = &(temp[now_size]);
        desc->storage_end = &(temp[now_size*2]);
    }
    desc->end[0]=*((DataType*)key);
    desc->end=&(desc->end[1]);
    int p=desc->end-desc->begin-1;
    for(;(p/2)!=0&&desc->cmp(&(desc->begin[p]),size,&(desc->begin[p/2]),size);p/=2)
    {
        DataType t=desc->begin[p];
        desc->begin[p]=desc->begin[p/2];
        desc->begin[p/2]=t;
    }
}
void* top(PriorityQueueDescriptor* desc)
{
    return &(desc->begin[1]);
}
void pop(PriorityQueueDescriptor* desc)
{
    desc->begin[1]=desc->end[-1];
    desc->end[-1]=0;
    desc->end=&(desc->end[-1]);
    int p=size(desc);
    for(int i=1;i*2<=p;)
    {
        int max;
        if(i*2==p)
        {
            max=p;
        }
        else
        {
            max=(desc->cmp(&desc->begin[i*2],NULL,&desc->begin[i*2+1],NULL))?(i*2):(i*2+1);
        }
        if(desc->begin[i]>=desc->begin[max])
        {
            break;
        }
        else
        {
            DataType t=desc->begin[i];
            desc->begin[i]=desc->begin[max];
            desc->begin[max]=t;
            i=max;
        }
    }
}
void clear(PriorityQueueDescriptor* desc)
{
    DataType *p=&(desc->begin[1]);
    for(;p<desc->end;)
    {
        *p=0;
        p=&(p[1]);
    }
    desc->end=&desc->begin[1];
}
void destructor(PriorityQueueDescriptor* desc)
{
    free(desc->begin);
}