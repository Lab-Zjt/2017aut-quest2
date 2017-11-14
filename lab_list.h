#ifndef LAB_LIST_H
#define LAB_LIST_H

#include <string.h>
typedef struct listnode
{
    void* data;
    struct listnode* next;
    struct listnode* prev;
}ListNode;
struct lab__list_st
{
    ListNode* first;
    ListNode* last;
    int size;
};

struct lab__list_iter_st
{
    ListNode* ptr;
};

// NOT MODIFY BELOW
typedef struct lab__list_st ListDescriptor;
typedef struct lab__list_iter_st ListIterator;

struct lab__list_api_st{
    ListDescriptor (*constructor)();
    void (*push_back)(ListDescriptor* desc,void* elem,int size);
    void (*push_front)(ListDescriptor* desc,void* elem,int size);
    ListIterator (*begin)(ListDescriptor* desc);
    ListIterator (*end)(ListDescriptor* desc);
    void* (*iter_dereference)(ListIterator iter);
    ListIterator (*iter_next)(ListIterator iter);
    ListIterator (*iter_prev)(ListIterator iter);
    int (*size)(ListDescriptor* desc);
    void (*pop_front)(ListDescriptor* desc);
    void (*pop_back)(ListDescriptor* desc);
    void (*erase)(ListDescriptor* desc,ListIterator iter);
    void (*clear)(ListDescriptor* desc);
    void (*destructor)(ListDescriptor* desc);
};

typedef struct lab__list_api_st ListAPI;

extern ListAPI list;

#endif

ListDescriptor constructor()
{
    ListDescriptor temp;
    ListNode* init_node=(ListNode*)malloc(sizeof(ListNode));
    temp.first=init_node;
    temp.last=init_node;
    temp.size=0;
    return temp;
}
void push_front(ListDescriptor* desc,void* elem,int size)
{
    ListNode* new_node=(ListNode*)malloc(sizeof(ListNode));
    new_node->data=malloc(size);
    memcpy(new_node->data,elem,size);
    if(desc->first!=desc->last)
    {
        new_node->next=desc->first;
        new_node->prev=desc->last;
        desc->last->next=new_node;
        desc->first->prev=new_node;
    }
    else
    {
        new_node->prev=desc->last;
        new_node->next=desc->last;
        desc->last->next=new_node;
        desc->last->prev=new_node;
    }
    desc->first=new_node;
    desc->size++;
}
void push_back(ListDescriptor* desc,void* elem,int size)
{
    if(desc->first!=desc->last)
    {
        ListNode* new_node=(ListNode*)malloc(sizeof(ListNode));
        new_node->data=malloc(size);
        memcpy(new_node->data,elem,size);
        new_node->next=desc->last;
        new_node->prev=desc->last->prev;
        desc->last->prev->next=new_node;
        desc->last->prev=new_node;
        desc->size++;
    }
    else
    {
        push_front(desc,elem,size);
    }
}
ListIterator begin(ListDescriptor* desc)
{
    ListIterator temp;
    temp.ptr=desc->first;
    return temp;
}
ListIterator end(ListDescriptor* desc)
{
    ListIterator temp;
    temp.ptr=desc->last->prev;
    return temp;
}
void* iter_dereference(ListIterator iter)
{
    return iter.ptr->data;
}
ListIterator iter_next(ListIterator iter)
{
    ListIterator temp;
    temp.ptr=iter.ptr->next;
    return temp;
}
ListIterator iter_prev(ListIterator iter)
{
    ListIterator temp;
    temp.ptr=iter.ptr->prev;
    return temp;
}
int size(ListDescriptor* desc)
{
    return desc->size;
}
void pop_front(ListDescriptor* desc)
{
    desc->first->next->prev=desc->last;
    desc->last->next=desc->first->next;
    free(desc->first);
    desc->first=desc->last->next;
    desc->size--;
}
void pop_back(ListDescriptor* desc)
{
    desc->last->prev=desc->last->prev->prev;
    free(desc->last->prev->next);
    desc->last->prev->next=desc->last;
    desc->size--;
}
void erase(ListDescriptor* desc,ListIterator iter)
{
    desc->size--;
    iter.ptr->next->prev=iter.ptr->prev;
    iter.ptr->prev->next=iter.ptr->next;
    free(iter.ptr);
}
void clear(ListDescriptor* desc)
{
    ListNode* p=desc->first;
    for(;p->next!=desc->last;)
    {
        p=p->next;
        free(p->prev);
    }
    free(p);
    desc->first=desc->last;
    desc->size=0;
}
void destructor(ListDescriptor* desc)
{
    clear(desc);
    free(desc->first);
}
ListAPI list=
        {
                constructor,
                push_back,
                push_front,
                begin,
                end,
                iter_dereference,
                iter_next,
                iter_prev,
                size,
                pop_front,
                pop_back,
                erase,
                clear,
                destructor
        };