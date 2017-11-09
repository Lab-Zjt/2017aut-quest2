#ifndef LAB_VECTOR_H
#define LAB_VECTOR_H

typedef int DataType ;
struct lab__vector_st
{
    struct lab__vector_api_st* vector;
};

struct lab__vector_iter_st
{
    DataType* ptr;
};

// NOT MODIFY BELOW
typedef struct lab__vector_st VectorDescriptor;
typedef struct lab__vector_iter_st VectorIterator;

struct lab__vector_api_st{
    VectorIterator first;
    VectorIterator last;
    VectorIterator storage_end;
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
VectorDescriptor constructor()//???????
{
    VectorDescriptor temp;
    temp.vector->first.ptr=(DataType*)malloc(sizeof(DataType));
    temp.vector->last.ptr=temp.vector->first.ptr;
    temp.vector->storage_end.ptr=temp.vector->first.ptr;
    temp.vector->begin=begin;
    temp.vector->end=end;
    temp.vector->push_back=push_back;
    temp.vector->size=size;
    temp.vector->capacity=capacity;
    temp.vector->reserve=reserve;
    temp.vector->clear=clear;
    temp.vector->pop_back=pop_back;
    temp.vector->destructor=destructor;
    temp.vector->shrink_to_fit=shrink_to_fit;
    temp.vector->iter_move=iter_move;
    temp.vector->iter_dereference=iter_dereference;
    temp.vector->erase=erase;
    return temp;
}
void push_back(VectorDescriptor* desc,void* elem,int size)
{
    if(desc->vector->last==desc->vector->storage_end)
    {
        reserve(desc,desc->vector->capacity(desc)*2);
    }
    desc->vector->last.ptr[0]=*elem;
    desc->vector->last.ptr=&desc->vector->last.ptr[1];
}
void* iter_dereference(VectorIterator iter)//?????
{
    return iter.ptr;
}
void clear(VectorDescriptor* desc)
{
    for(int i=0;i<desc->size;i++)
    {
        desc->vector->first[i]=0;
    }
    desc->vector->last=desc->vector->first;
}
void destructor(VectorDescriptor* desc)
{
    clear(desc);
    free(desc->vector->first);
}
VectorIterator begin(VectorDescriptor* desc)//??????
{
    return desc->vector->first;
}
VectorIterator end(VectorDescriptor* desc)//??????
{
    return desc->vector->last;
}
VectorIterator iter_move(VectorIterator iter,int delta)////????
{
    return (&iter[delta]);
}
void pop_back(VectorDescriptor* desc)
{
    *desc->vector->last=NULL;
    desc->vector->last=desc->vector->last-1;
}
int capacity(VectorDescriptor* desc)
{
    return (desc->vector->storage_end-desc->vector->first);
}
int size(VectorDescriptor* desc)
{
    return (desc->vector->last-desc->vector->first-1);
}
void erase(VectorDescriptor* desc,VectorIterator iter)//????
{
    for(;iter.ptr!=desc->vector->last.ptr-1;)
    {
        iter.ptr[0]=iter.ptr[1];
        iter.ptr++;
    }
    desc->vector->last.ptr=iter.ptr;
}
void shrink_to_fit(VectorDescriptor* desc)
{
    free(desc->vector->storage_end.ptr);
    desc->vector->storage_end.ptr=desc->vector->last.ptr;
}
void reserve(VectorDescriptor* desc,int resv_size)
{
    if(resv_size>desc->vector->capacity())
    {
        DataType *temp = (DataType *) malloc(sizeof(DataType) * resv_size);
        for (int i = 0 ; i < desc->size ; i ++)
        {
            temp[i] = desc->vector.first[i];
        }
        free(desc->vector->first.ptr);
        desc->vector->first.ptr = temp;
        desc->vector->storage_end.ptr = temp + resv_size;
        desc->vector->last.ptr=desc->vector->first.ptr+desc->vector->size(desc)+1;
    }
    else
    {
        printf("The new size is small than old size.\n");
    }
}