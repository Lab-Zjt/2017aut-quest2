#ifndef _RBTREE_PARENTLINK_H
#define _RBTREE_PARENTLINK_H

#include "labafx.h"
#include <string.h>
typedef enum {red=1,black=0}RB_Color;
typedef struct rbnode
{
    void *key;
    rbnode* left;
    rbnode* right;
    rbnode* father;
    RB_Color color;
    int key_size;
}RB_Node;
RB_Node* RB_make_new_node(void* key,int size,RB_Node* father)
{
    RB_Node *new_node = (RB_Node *) malloc(sizeof(RB_Node));
    new_node->key=malloc(size);
    memcpy(new_node->key,key,size);
    new_node->key_size=size;
    new_node->color = red;
    new_node->father=father;
    new_node->left=NULL;
    new_node->right=NULL;
    return new_node;
}
RB_Node* RB_right_rotate(RB_Node *p)
{
    RB_Node *t = p->left;
    RB_Color temp_color = p->color;
    p->color = t->color;
    t->color = temp_color;
    t->father=p->father;
    p->father=t;
    if(t->right!=NULL)
    {
        t->right->father=p;
    }
    p->left = t->right;
    t->right = p;
    return t;
}
RB_Node* RB_left_rotate(RB_Node *p)
{
    RB_Node *t = p->right;
    RB_Color temp_color = p->color;
    p->color = t->color;
    t->color = temp_color;
    t->father=p->father;
    p->father=t;
    if(t->left!=NULL)
    {
        t->left->father=p;
    }
    p->right = t->left;
    t->left = p;
    return t;
}
RB_Node* RB_color_flip(RB_Node *p)
{
    p->left->color = black;
    p->right->color = black;
    p->color = red;
    return p;
}
RB_Color RB_show_color(RB_Node* p)
{
    if (p == NULL)
    {
        return black;
    }
    else
    {
        return p->color;
    }
}
RB_Node* RB_update(RB_Node* p)
{
    if (RB_show_color(p->left) && RB_show_color(p->right))
    {
        p = RB_color_flip(p);
    }
    if (RB_show_color(p->right))
    {
        p = RB_left_rotate(p);
    }
    if (RB_show_color(p->left) && RB_show_color(p->left->left))
    {
        p = RB_right_rotate(p);
    }
    if (RB_show_color(p->left) && RB_show_color(p->right))
    {
        p = RB_color_flip(p);
    }
    return p;
}
RB_Node* RB_insert(RB_Node* p,void* key,int size,Comparator cmp)
{
    if (cmp(key,size,p->key,p->key_size))
    {
        if (p->right != NULL)
        {
            p->right = RB_insert(p->right, key,size,cmp);
        }
        else
        {
            p->right = RB_make_new_node(key,size,p);
        }
    }
    else
    {
        if (p->left != NULL)
        {
            p->left = RB_insert(p->left, key,size,cmp);
        }
        else
        {
            p->left = RB_make_new_node(key,size,p);
        }
    }
    p = RB_update(p);
    return p;
}
RB_Node* RB_color_flip_when_delete(RB_Node* p)
{
    p->color=black;
    if(p->right!=NULL)
    {
        p->right->color=red;
    }
    if(p->left!=NULL)
    {
        p->left->color=red;
    }
    return p;
}
RB_Node* RB_delete_max(RB_Node* p)
{
    if (p->right != NULL)
    {
        if (RB_show_color(p->left))
        {
            p = RB_right_rotate(p);
        }
        else
        if (! (RB_show_color(p->left) || RB_show_color(p->right)))
        {
            p = RB_color_flip_when_delete(p);
        }
        p->right = RB_delete_max(p->right);
        if(p->right!=NULL)
        {
            p->right->father=p;
        }
        p = RB_update(p);
    }
    else
    if (RB_show_color(p->left))
    {
        p = RB_right_rotate(p);
        p->right = RB_delete_max(p->right);
    }
    else
    {
        if(p->left==NULL)
        {
            free(p);
            return NULL;
        }
        p = p->left;
        free(p->father);
    }
    return p;
}
RB_Node* RB_delete_min(RB_Node * p)
{
    if (p->left != NULL)
    {
        if (! RB_show_color(p->left))
        {
            p = RB_color_flip_when_delete(p);
        }
        p->left=RB_delete_min(p->left);
        if(p->left!=NULL)
        {
            p->left->father=p;
        }
        p=RB_update(p);
    }
    else
    {
        if(p->right==NULL)
        {
            free(p);
            return NULL;
        }
        p = p->right;
        free(p->father);
    }
    return p;
}

RB_Node* RB_delete_pointed(void* key,int size,Comparator cmp,RB_Node* p)
{
    if (! memcmp(key, p->key, size))
    {
        if (p->left == NULL && p->right == NULL)
        {
            free(p);
            return NULL;
        }
        else
        {
            RB_Node *s = p;
            if (s->right != NULL)
            {
                s = s->right;
                for (; s->left != NULL ;)
                {
                    s = s->left;
                }
                memcpy(p->key,s->key,s->key_size);
                if (! (RB_show_color(p->left) && RB_show_color(p->right)))
                {
                    p = RB_color_flip_when_delete(p);
                }
                p->right = RB_delete_min(p->right);
            }
            else
            {
                s = s->left;
                for (; s->right != NULL ;)
                {
                    s = s->right;
                }
                memcpy(p->key,s->key,s->key_size);
                if (! (RB_show_color(p->left) && RB_show_color(p->right)))
                {
                    p = RB_color_flip_when_delete(p);
                }
                p->left = RB_delete_max(p->left);
            }
        }
    }
    else
    if (cmp(key,size,p->key,p->key_size))
    {
        if (p->right != NULL)
        {
            if (RB_show_color(p->left))
            {
                p = RB_right_rotate(p);
            }
            else if (! (RB_show_color(p->left) || RB_show_color(p->right)))
            {
                p = RB_color_flip_when_delete(p);
            }
            p->right = RB_delete_pointed(key,size,cmp, p->right);
            if(p->right!=NULL)
            {
                p->father->father=p;
            }
        }
        else
        {
            printf("No result.\n");
        }
    }
    else

    {
        if (p->left != NULL)
        {
            if (! RB_show_color(p->left))
            {
                p = RB_color_flip_when_delete(p);
            }
            p->left = RB_delete_pointed(key,size,cmp, p->left);
            if(p->left!=NULL)
            {
                p->left->father=p;
            }

        }
        else
        {
            printf("No result\n");
        }
    }
    if (p != NULL)
    {
        p = RB_update(p);
    }
    return p;
}
RB_Node* RB_find(RB_Node* p,void* target,int size,Comparator cmp)
{
    RB_Node* t;
    if(!memcmp(target,p->key,size))
    {
        t=p;
    }
    else
    if(cmp(target,size,p->key,p->key_size))
    {
        if(p->right!=NULL)
        {
            t=RB_find(p->right,target,size,cmp);
        }
        else
        {
            return NULL;
        }
    }
    else
    {
        if(p->left!=NULL)
        {
            t=RB_find(p->left,target,size,cmp);
        }
        else
        {
            return NULL;
        }
    }
    return t;
}
RB_Node* RB_findmin(RB_Node* p)
{
    RB_Node* t;
    if(p->left!=NULL)
    {
        t=RB_findmin(p->left);
    }
    else
    {
        t=p;
    }
    return t;
}
RB_Node* RB_findmax(RB_Node* p)
{
    RB_Node *t;
    if (p->right != NULL)
    {
        t = RB_findmax(p->right);
    }
    else
    {
        t = p;
    }
    return t;
}
RB_Node* RB_next(RB_Node* p)
{
    RB_Node* t=p;
    if(p->right!=NULL)
    {
        t=p->right;
        for(;t->left!=NULL;)
        {
            t=t->left;
        }
    }
    else
    {
        for (;t->father!=NULL && t != t->father->left ;)
        {
            t = t->father;
        }
        t = t->father;
    }
    return t;
}
RB_Node* RB_prev(RB_Node* p)
{
    RB_Node *t = p;
    if(t->key_size==0)
    {
        t=p->father;
        free(p);
    }
    else
    if (p->left != NULL)
    {
        for (; t->right != NULL ;)
        {
            t = t->right;
        }
    }
    else
    {
        for (; t->father != NULL && t != t->father->right ;)
        {
            t = t->father;
        }
        t = t->father;
    }
    return t;
}
void RB_clear(RB_Node* p)
{
    if(p->left!=NULL)
    {
        RB_clear(p->left);
    }
    if(p->right!=NULL)
    {
        RB_clear(p->right);
    }
    free(p);
}
#endif
