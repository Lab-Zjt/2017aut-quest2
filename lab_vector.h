#ifndef LAB_VECTOR_H
#define LAB_VECTOR_H

typedef int DataType ;
struct lab__vector_st
{
    DataType * begin;
    int size;
    int capacity;
};

struct lab__vector_iter_st
{
    DataType* ptr;
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
VectorDescriptor constructor()//???????
{
    VectorDescriptor temp;
    temp.begin=(DataType*)malloc(sizeof(DataType));
    temp.capacity=1;
    temp.size=1;
    return temp;
}
void push_back(VectorDescriptor* desc,void* elem,int size)
{
    if(desc->size>=desc->capacity)
    {
        reserve(desc,desc->capacity*2);
    }
    desc[desc->size]=*elem;
    desc->size++;
}
void* iter_dereference(VectorIterator iter)//?????
{
    free(iter.begin);
}
void clear(VectorDescriptor* desc)
{
    for(int i=0;i<desc->size;i++)
    {
        desc->begin[i]=0;
    }
    desc->size=0;
}
void destructor(VectorDescriptor* desc)
{
    clear(desc);
    free(desc);
}
VectorIterator begin(VectorDescriptor* desc)//??????
{
    VectorIterator temp;
    temp.ptr=desc->begin;
    return temp;
}
VectorIterator end(VectorDescriptor* desc)//??????
{
    VectorIterator temp;
    temp.ptr=&desc->begin[desc->size];
    return temp;
}
VectorIterator iter_move(VectorIterator iter,int delta)////????
{
    iter.ptr=&iter.ptr[delta];
}
void pop_back(VectorDescriptor* desc)
{
    desc->begin[desc->size]=0;
    desc->size--;
}
int capacity(VectorDescriptor* desc)
{
    return desc->capacity;
}
int size(VectorDescriptor* desc)
{
    return desc->size;
}
void erase(VectorDescriptor* desc,VectorIterator iter)//????
{

}
void shrink_to_fit(VectorDescriptor* desc)
{
    desc->capacity=desc->size;
}
void reserve(VectorDescriptor* desc,int resv_size)
{
    if(resv_size>desc->capacity)
    {
        DataType *temp = (VectorDescriptor *) malloc(sizeof(DataType) * resv_size);
        for (int i = 0 ; i < desc->size ; i ++)
        {
            temp[i] = desc->begin[i];
        }
        DataType *t = desc->begin;
        desc->begin = temp;
        free(t);

    }
}
int main()
{
    VectorDescriptor testvd;
    VectorAPI testvt;
    printf("%d",testvt.begin(testvd).ptr);
}