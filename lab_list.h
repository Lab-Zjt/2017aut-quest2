#ifndef LAB_LIST_H
#define LAB_LIST_H

typedef int DataType;
struct list_node
{
    DataType* data;
    struct list_node* next;
    struct list_node* prev;
};
typedef struct list_node Node;
struct lab__list_st
{
    struct lab__list_api_st* list;
    int size;
};

struct lab__list_iter_st
{
    Node* ptr;
};

// NOT MODIFY BELOW
typedef struct lab__list_st ListDescriptor;
typedef struct lab__list_iter_st ListIterator;

struct lab__list_api_st{
    ListIterator front;
    ListIterator back;
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
    Node* new_node=(Node*)malloc(sizeof(Node));
    temp.list->front.ptr=new_node;
    temp.list->back.ptr=new_node;
    temp.list->size=size;
    temp.size=0;
    temp.list->erase=erase;
    temp.list->iter_dereference=iter_dereference;
    temp.list->destructor=destructor;
    temp.list->pop_back=pop_back;
    temp.list->pop_front=pop_front;
    temp.list->clear=clear;
    temp.list->push_front=push_front;
    temp.list->push_back=push_back;
    temp.list->iter_next=iter_next;
    temp.list->iter_prev=iter_prev;
    temp.list->begin=begin;
    temp.list->end=end;
    return temp;
}
void push_back(ListDescriptor* desc,void* elem,int size)
{
    desc->list->back.ptr->data=*elem;
    Node* new_node=(Node*)malloc(sizeof(Node));
    new_node->prev=desc->list->back.ptr;
    new_node->next=desc->list->front.ptr;
    desc->list->back.ptr->next=new_node;
    desc->list->back.ptr=new_node;
    desc->list->front.ptr->prev=new_node;
    desc->size++;
}
void push_front(ListDescriptor* desc,void* elem,int size)
{
    Node* new_node=(Node*)malloc(sizeof(Node));
    new_node->data=*elem;
    new_node->next=desc->list->front.ptr;
    new_node->prev=desc->list->back.ptr;
    desc->list->front.ptr->prev=new_node;
    desc->list->back.ptr->next=new_node;
    desc->list->front.ptr=new_node;
    desc->size++;
}
ListIterator begin(ListDescriptor* desc)
{
    return desc->list->front;
}
ListIterator end(ListDescriptor* desc)
{
    return desc->list->back;
}
void* iter_dereference(ListIterator iter)
{
    return &iter.ptr->data;
}
ListIterator iter_next(ListIterator iter)
{
    return iter.ptr->next;
}
ListIterator iter_prev(ListIterator iter)
{
    return iter.ptr->prev;
}
int size(ListDescriptor* desc)
{
    return desc->size;
}
void pop_front(ListDescriptor* desc)
{
    Node* p=desc->list->front;
    desc->list->back->next=p->next;
    p.next->prev=desc->list->back;
    desc->list->front=p->next;
    desc->size--;
    free(p);
}
void pop_back(ListDescriptor* desc)
{
    Node* p=desc->list->back->prev;
    desc->list->back->prev=p->prev;
    p->prev->next=desc->list->back;
    desc->size--;
    free(p);
}
void erase(ListDescriptor* desc,ListIterator iter)
{
    iter.ptr->next->prev=iter.ptr->prev;
    iter.ptr->prev->next=iter.ptr->next;
    desc->size--;
    free(iter.ptr);
}
void clear(ListDescriptor* desc)
{
    Node* p=desc->list->front.ptr;
    for(;p!=desc->list->back.ptr;)
    {
        p->data=NULL;
        p=p->next;
    }
}
void destructor(ListDescriptor* desc)
{
    Node* p=desc->list->front;
    for(;p->next!=NULL;)
    {
        Node* t=p;
        p=p->next;
        free(t);
    }
    free(p);
}