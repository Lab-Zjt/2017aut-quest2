#ifndef LAB_PRIORITY_QUEUE
#define LAB_PRIORITY_QUEUE

#include <string.h>
#include "labafx.h"


struct lab__priority_queue_st
{
    void *begin;
    void *end;
    void *storage_end;
    Comparator cmp;
    int data_size;
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
/*int default_compfunc_max_heap(void* a,int asize,void* b,int bsize)
{
    if(*(DataType*)a>(*(DataType*)b))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}*/
PriorityQueueDescriptor constructor(Comparator compfunc)
{
    PriorityQueueDescriptor temp;
    temp.begin=NULL;
    temp.storage_end=NULL;
    temp.end=NULL;
    temp.cmp=compfunc;
    temp.data_size=0;
    return temp;
}
int size(PriorityQueueDescriptor* desc)
{
    return ((char*)desc->end-(char*)desc->begin)/desc->data_size-1;
}
void push(PriorityQueueDescriptor* desc,void* key,int size)
{
    if(!desc->data_size)
    {
        desc->begin=malloc(sizeof(size)*2);
        desc->data_size=size;
        desc->end=desc->begin+size;
        desc->storage_end=desc->end;
    }
    if(desc->end==desc->storage_end)
    {
        int now_size=(char*)desc->storage_end-(char*)desc->begin+size;
        void* temp=malloc(now_size*2);
        for(int i=0;i<now_size;i+=size)
        {
            memcpy(temp+i,desc->begin+i,size);
        }
        free(desc->begin);
        desc->begin=temp;
        desc->end=desc->begin+now_size-size;
        desc->storage_end=desc->begin+now_size*2-size;
    }
    memcpy(desc->end,key,size);
    desc->end+=size;
    int p=(char*)desc->end-(char*)desc->begin-desc->data_size;
    for(int father=p/2-(p/2)%size;father>=size&&desc->cmp(desc->begin+p,size,desc->begin+father,size);p=father,father=p/2-(p/2)%size)
    {
        void* t=malloc(size);
        memcpy(t,desc->begin+p,size);
        memcpy(desc->begin+p,desc->begin+father,size);
        memcpy(desc->begin+father,t,size);
        free(t);
    }
}
void* top(PriorityQueueDescriptor* desc)
{
    return (desc->begin+desc->data_size);
}
void pop(PriorityQueueDescriptor* desc)
{
    memcpy(desc->begin+desc->data_size,desc->end-desc->data_size,desc->data_size);
    desc->end=desc->end-desc->data_size;
    int p=(char*)desc->end-(char*)desc->begin;
    const int ds=desc->data_size;
    for(int i=ds;i*2<=p;)
    {
        int max;
        if(i*2==p)
        {
            max=p;
        }
        else
        {
            max=(desc->cmp(desc->begin+i*2,ds,desc->begin+i*2+ds,ds))?(i*2):(i*2+ds);
        }
        if(desc->cmp(desc->begin+i,ds,desc->begin+max,ds))
        {
            break;
        }
        else
        {
            void *t=malloc(ds);
            memcpy(t,desc->begin+i,ds);
            memcpy(desc->begin+i,desc->begin+max,ds);
            memcpy(desc->begin+max,t,ds);
            free(t);
            i=max;
        }
    }
}
void clear(PriorityQueueDescriptor* desc)
{
    desc->end=desc->begin+desc->data_size;
}
void destructor(PriorityQueueDescriptor* desc)
{
    free(desc->begin);
}
PriorityQueueAPI prq=
        {
                constructor,
                size,
                push,
                top,
                pop,
                clear,
                destructor
        };