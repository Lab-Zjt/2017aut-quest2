#ifndef LAB_LIST_H
#define LAB_LIST_H

typedef int DataType;
struct node
{
    DataType* data;
    struct node* next;
    struct node* prev;
};
typedef struct node Node;
struct lab__list_st
{
    Node *begin;
    Node *end;
    int size;
};

struct lab__list_iter_st{

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
    temp.begin=NULL;
    temp.end=NULL;
    temp.size=0;
}
void push_back(ListDescriptor* desc,void* elem,int size)
{
    if(desc->end==NULL)
    {
        desc->end=(Node*)malloc(sizeof(Node));
        desc->end->data=(DataType *)elem;
        desc->begin=desc->end;
        desc->size=1;
        desc->end->next=NULL;
        desc->end->prev=NULL;
    }
    else
    {
        Node* new_node=(Node*)malloc(sizeof(Node));
        new_node->data=(DataType *)elem;
        new_node->prev=desc->end;
        new_node->next=NULL;
        desc->end=new_node;
        desc->size++;
    }
}
void push_front(ListDescriptor* desc,void* elem,int size)
{
    if(desc->begin==NULL)
    {
        desc->begin=(Node*)malloc(sizeof(Node));
        desc->begin->data=(DataType *)elem;
        desc->end=desc->begin;
        desc->size=1;
        desc->begin->next=NULL;
        desc->begin->prev=NULL;
    }
    else
    {
        Node* new_node=(Node*)malloc(sizeof(Node));
        new_node->data=(DataType *)elem;
        new_node->next=desc->begin;
        new_node->prev=NULL;
        desc->begin=new_node;
        desc->size++;
    }
}
ListIterator begin(ListDescriptor* desc);
ListIterator end(ListDescriptor* desc);
void* iter_dereference(ListIterator iter);
ListIterator iter_next(ListIterator iter);
ListIterator iter_prev(ListIterator iter);
int size(ListDescriptor* desc);
void pop_front(ListDescriptor* desc);
void pop_back(ListDescriptor* desc);
void erase(ListDescriptor* desc,ListIterator iter);
void clear(ListDescriptor* desc);
void destructor(ListDescriptor* desc);