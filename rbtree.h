#ifndef INC_2017AUT_QUEST2_RBTREE_H
#define INC_2017AUT_QUEST2_RBTREE_H

extern "C"
{
#include <stdlib.h>
#include <stdio.h>
};
typedef enum {black=0,red=1} RB_Color;
typedef double DataType;
typedef struct Node//结点由数据、颜色、通往左右结点的链接组成
{
    DataType data;
    struct Node *left;
    struct Node *right;
    RB_Color color;
}RB_Node;
RB_Node* RB_make_new_node(DataType data)
{
    RB_Node *new_node = (RB_Node *) malloc(sizeof(RB_Node));//新建结点
    new_node->data = data;//更新结点数据
    new_node->color = red;//新建结点的颜色必须为红
    return new_node;//返回新结点的指针
}
RB_Node* RB_right_rotate(RB_Node *p)
{
    RB_Node *t = p->left;
    RB_Color ct = p->color;
    p->color = t->color;
    t->color = ct;//交换当前结点与左结点的颜色
    p->left = t->right;//当前结点的左链接更新为左结点的右子树
    t->right = p;//左结点的右链接更新为当前结点
    return t;//当前结点更新为原结点的左结点
}
RB_Node* RB_left_rotate(RB_Node *p)
{
    RB_Node *t = p->right;
    RB_Color ct = p->color;
    p->color = t->color;
    t->color = ct;//交换当前结点与右结点的颜色
    p->right = t->left;//当前结点的右链接更新为右结点的左子树
    t->left = p;//右结点的左链接更新为当前结点
    return t;//当前结点更新为原结点的右结点
}
RB_Node* RB_color_flip(RB_Node *p)
{
    p->left->color = black;
    p->right->color = black;
    p->color = red;//左右子结点颜色变黑，当前结点颜色变红
    return p;
}
RB_Color RB_show_color(RB_Node* p)
{
    if (p == NULL)
    {
        return black;
    } else
    {
        return p->color;
    }
}
RB_Node* RB_update(RB_Node* p)
{
    if (RB_show_color(p->left) && RB_show_color(p->right))//若左右结点均为红，直接进行颜色转换操作比先左旋转再右旋转（左旋转和右旋转刚好相反，一起执行等于没执行）要快
    {
        p = RB_color_flip(p);
    }
    if (RB_show_color(p->right))//右结点为红时，进行左旋转操作
    {
        p = RB_left_rotate(p);
    }
    if (RB_show_color(p->left) && RB_show_color(p->left->left))//左结点及左结点的左子结点颜色为红时，进行右旋转操作
    {
        p = RB_right_rotate(p);
    }
    if (RB_show_color(p->left) && RB_show_color(p->right))//左右结点颜色均为红时，进行颜色转换操作
    {
        p = RB_color_flip(p);
    }
    return p;
}
RB_Node* RB_insert(RB_Node* p,DataType data)
{
    if (data >= p->data)//比当前结点大，向右寻找
    {
        if (p->right != NULL)//右结点不为空则继续向右寻找
        {
            p->right = RB_insert(p->right, data);
        } else//右结点为空则新建结点，并使其成为当前结点的右结点
        {
            p->right = RB_make_new_node(data);
        }
    } else//比当前结点小，向左寻找
    {
        if (p->left != NULL)//左结点不为空则继续向左寻找
        {
            p->left = RB_insert(p->left, data);
        } else//左结点为空则新建结点，并使其成为当前结点的左结点
        {
            p->left = RB_make_new_node(data);
        }
    }
    p = RB_update(p);//更新当前结点
    return p;
}
void RB_print_tree(RB_Node* p)
{
    if (p->left != NULL)
    {
        RB_print_tree(p->left);
    }
    printf("%.0lf ", p->data);
    if (p->right != NULL)
    {
        RB_print_tree(p->right);
    }
}
int RB_tree_length(RB_Node* p)
{
    int length = 1;
    if (p->left != NULL)
    {
        length = RB_tree_length(p->left);
        length ++;
    }
    return length;
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
    if (p->right != NULL)//最大值在右子树中，故向右寻找
    {
        if (RB_show_color(p->left))//若右结点不为空，且左结点为红色（根据左倾红黑树性质，此时右结点不可能为红色），则进行右旋转使得右结点为红色
        {
            p = RB_right_rotate(p);
        }
        else
        if (! (RB_show_color(p->left) || RB_show_color(p->right)))//若右结点不为空，且左右结点均为黑色，则进行颜色转换
        {
            p = RB_color_flip_when_delete(p);
        }
        p->right = RB_delete_max(p->right);//此时右结点必为红，继续向右寻找
        p = RB_update(p);//递归结束后，更新当前结点
    }
    else
    if (RB_show_color(p->left))//若右结点为空，左结点为红色，则进行右旋转
    {
        p = RB_right_rotate(p);
        p->right = RB_delete_max(p->right);
    }
    else//若右结点为空，左结点为黑色或不存在，当前结点更新为当前结点的左结点，相当于把当前结点的左子树接到上一结点的右结点上，然后原结点被遗弃
    {
        p = p->left;
    }
    return p;
}
RB_Node* RB_delete_min(RB_Node * p)
{
    if (p->left != NULL)//最小值在左子树，故向左寻找
    {
        if (! RB_show_color(p->left))//若左结点为黑色，进行颜色变换
        {
            p = RB_color_flip_when_delete(p);
        }
        p->left=RB_delete_min(p->left);//此时左结点必为红色，继续向左寻找
        p=RB_update(p);//递归结束后，更新当前结点
    }
    else
    {
        p = p->right;//若左结点为空，更新当前结点为当前结点的右子树，相当于把当前结点的右子树接到上一结点的左结点上，然后原节点被遗弃
    }
    return p;
}
RB_Node* RB_delete_pointed(DataType data,RB_Node* p)
{
    if(data>p->data)//若要删除的值比当前结点大，向右寻找
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
            p->right = RB_delete_pointed(data,p->right);//该过程与删除最大值时，向右寻找的过程相同，保证右结点为红色后，向右寻找
        }
        else
        {
            printf("No result.\n");
        }
    }
    else
    if(data<p->data)//若要删除的值比当前结点小，向左寻找
    {
        if (p->left != NULL)
        {
            if (! RB_show_color(p->left))
            {
                p = RB_color_flip_when_delete(p);
            }
            p->left=RB_delete_pointed(data,p->left);//该过程与删除最小值时，向左寻找的过程相同，保证左结点为红色后，向左寻找

        }
        else
        {
            printf("No result\n");
        }
    }
    else//若当前结点就是要删除的结点
    {
        if(p->left==NULL&&p->right==NULL)//若当前结点没有子树，直接删除该结点
        {
            p=NULL;
        }
        else
        {
            RB_Node *s = p;
            if (s->right != NULL)//若右子树不为空
            {
                s = s->right;
                for (; s->left != NULL ;)
                {
                    s = s->left;
                }
                p->data = s->data;//找到右子树中的最小值，复制到当前结点，然后删除找到的结点（与普通二叉树相同的思路，红黑树也是一种二叉树）
                if (! (RB_show_color(p->left) && RB_show_color(p->right)))
                {
                    p = RB_color_flip_when_delete(p);//删除过程中也要保证往下查找时下一个结点为红色
                }
                p->right = RB_delete_min(p->right);//删除右子树中值最小的结点
            } else//若右子树为空，左子树不为空
            {
                s = s->left;
                for (; s->right != NULL ;)
                {
                    s = s->right;
                }
                p->data = s->data;//找到左子树中的最大值，复制到当前结点，然后删除找到的结点
                if (! (RB_show_color(p->left) && RB_show_color(p->right)))
                {
                    p = RB_color_flip_when_delete(p);//删除过程中也要保证往下查找时下一个结点为红色
                }
                p->left = RB_delete_max(p->left);//删除左子树中值最大的结点
            }
        }
    }
    if(p!=NULL)
    {
        p = RB_update(p);
    }
    return p;
}
RB_Node* RB_find(RB_Node* p,DataType target)
{
    RB_Node* t;
    if(target>p->data)
    {
        if(p->right!=NULL)
        {
            t=RB_find(p->right,target);
        }
        else
        {
            return NULL;
        }
    }
    else
    if(target<p->data)
    {
        if(p->left!=NULL)
        {
            t=RB_find(p->left,target);
        }
        else
        {
            return NULL;
        }
    }
    else
    {
        t=p;
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
    RB_Node* t;
    if(p->right!=NULL)
    {
        t=RB_findmax(p->right);
    }
    else
    {
        t=p;
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
