#ifndef LAB_SET_H
#define LAB_SET_H

#include "rbtree_parentlink.h"
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
    RB_Node* t;
    t=RB_prev(it.ptr);
    if(t==NULL)
    {
        printf("It is the BEGIN iterator.The operation is illegal.\n");
    }
    else
    {
        it.ptr=t;
    }
    return it;
}
SetIterator iter_next(SetIterator it)
{
    if(it.ptr->key_size==0)
    {
        printf("It is the END iterator.The operation is illegal.\n");
    }
    else
    {
        RB_Node *t;
        t = RB_next(it.ptr);
        if (t == NULL)
        {
            RB_Node* end_node=(RB_Node*)malloc(sizeof(RB_Node));
            end_node->father=it.ptr;
            end_node->key_size=0;
            it.ptr=end_node;
        }
        else
        {
            it.ptr=t;
        }
    }
    return it;
}

SetDescriptor constructor(Comparator compfunc)
{
    SetDescriptor temp;
    temp.size=0;
    temp.cmp=compfunc;
    RB_Node* root_node=(RB_Node*)malloc(sizeof(RB_Node));
    root_node->color=black;
    root_node->key=NULL;
    root_node->key_size=0;
    root_node->father=NULL;
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
        desc->root->key=malloc(size);
        memcpy(desc->root->key,key,size);
        desc->root->key_size=size;
    }
    else
    {
        desc->root=RB_insert(desc->root,key,size,desc->cmp);
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
    temp.ptr=RB_find(desc->root,key,size,desc->cmp);
    return temp;
}
void erase(SetDescriptor* desc,SetIterator it)
{
    desc->root=RB_delete_pointed(it.ptr->key,it.ptr->key_size,desc->cmp,desc->root);
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
    temp=iter_next(temp);
    return temp;
}
void* iter_dereference(SetIterator it)
{
    return it.ptr->key;
}
void clear(SetDescriptor* desc)
{
    RB_clear(desc->root);
    desc->root=(RB_Node*)malloc(sizeof(RB_Node));
    desc->root->right=NULL;
    desc->root->left=NULL;
    desc->root->key_size=0;
    desc->root->key=NULL;
    desc->size=0;
    desc->root->color=black;
}
void destructor(SetDescriptor* desc)
{
    RB_clear(desc->root);
    desc->root=NULL;
}
SetAPI set=
        {
                constructor,
                size,
                insert,
                find,
                erase,
                begin,
                end,
                iter_prev,
                iter_dereference,
                iter_next,
                clear,
                destructor
        };