#ifndef LAB_SET_H
#define LAB_SET_H

#include "labafx.h"
extern "C"
{
#include "rbtree.h"
};

/*typedef double DataType;
typedef enum {black=0,red=1}RB_Color;
typedef struct rbtree_node
{
    struct rbtree_node* left;
    struct rbtree_node* right;
    RB_Color color;
    DataType *data;
}RB_Node;*/
struct lab__set_st
{
    RB_Node* root;
    int size;
    Comparator cmp;
};

struct lab__set_iter_st
{
    RB_Node* ptr;
};

// DO NOT MODIFY BELOW

typedef struct lab__set_st SetDescriptor;
typedef struct lab__set_iter_st SetIterator;

struct lab__set_api_st{
    SetDescriptor (*constructor)(Comparator compfunc);
    int (*size)(SetDescriptor* desc);
    void (*insert)(SetDescriptor* desc,void* key,int size);
    SetIterator (*find)(SetDescriptor* desc,void* key,int size);
    void (*erase)(SetDescriptor* desc,SetIterator it);
    SetIterator (*begin)(SetDescriptor* desc);
    SetIterator (*end)(SetDescriptor* desc);
    SetIterator (*iter_prev)(SetIterator it);
    void* (*iter_dereference)(SetIterator it);
    SetIterator (*iter_next)(SetIterator it);
    void (*clear)(SetDescriptor* desc);
    void (*destructor)(SetDescriptor* desc);
};

typedef struct lab__set_api_st SetAPI;
extern SetAPI set;

#endif

SetIterator iter_prev(SetIterator it)
{

}
SetIterator iter_next(SetIterator it)
{

}
int defalut_compfunc_max(void* a,int asize,void* b,int bsize)
{
    if(*((DataType*)a)>*((DataType*)b))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
SetDescriptor constructor(Comparator compfunc)
{
    SetDescriptor temp;
    temp.size=0;
    if(compfunc!=NULL)
    {
        temp.cmp=compfunc;
    }
    else
    {
        temp.cmp=defalut_compfunc_max;
    }
    RB_Node* root_node=(RB_Node*)malloc(sizeof(RB_Node));
    root_node->color=black;
    //root_node->data=NULL;
    root_node->left=NULL;
    root_node->right=NULL;
    temp.root=root_node;
    return temp;
}
int size(SetDescriptor* desc)
{
    return desc->size;
}
void insert(SetDescriptor* desc,void* key,int size)
{
    if(!desc->size)
    {
        desc->root->data=*((DataType*)key);
    }
    else
    {
        desc->root=RB_insert(desc->root,(*(DataType*)key));
    }
    if(desc->root->color==red)
    {
        desc->root->color=black;
    }
    desc->size++;
}
SetIterator find(SetDescriptor* desc,void* key,int size)
{
    SetIterator temp;
    temp.ptr=RB_find(desc->root,*((DataType*)key));
    return temp;
}
void erase(SetDescriptor* desc,SetIterator it)
{
    desc->root=RB_delete_pointed(it.ptr->data,desc->root);
    if(desc->root->color=red)
    {
        desc->root->color=black;
    }
    desc->size--;
}
SetIterator begin(SetDescriptor* desc)
{
    SetIterator temp;
    temp.ptr=RB_findmin(desc->root);
    return temp;
}
SetIterator end(SetDescriptor* desc)
{
    SetIterator temp;
    temp.ptr=RB_findmax(desc->root);
    return temp;
}
void* iter_dereference(SetIterator it)
{
    return &(it.ptr->data);
}
void clear(SetDescriptor* desc)
{
    RB_clear(desc->root);
    desc->root=(RB_Node*)malloc(sizeof(RB_Node));
    desc->root->right=NULL;
    desc->root->left=NULL;
    desc->size=0;
    desc->root->color=black;
}
void destructor(SetDescriptor* desc)
{
    RB_clear(desc->root);
    desc->root=NULL;
}