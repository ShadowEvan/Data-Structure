#include<stdio.h>
#include<stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OVERFLOW -2

typedef int Status;
typedef int TElemType;

// A binary tree node has data, pointer to left child and
// a pointer to right child
typedef struct BiTNode
{
    TElemType data;
    struct BiTNode *Lchild, *Rchild;
}BiTNode, *BiTree;

void InitBiTree(BiTree &T)
{
    T = NULL;
}

Status InsertChild(BiTree &T, BiTree p, int LR, BiTree c)
{
    if(!T)
    {
        T = c;
        return OK;
    }
    if(!p || LR < 0 || LR > 1)return ERROR;
    if(LR == 0)p->Lchild = c;
    else p->Rchild = c;
    return OK;
}

BiTree MakeNode(TElemType e)
{
    BiTree p = (BiTNode *)malloc(sizeof(BiTNode));
    if(!p)return NULL;
    p->data = e;
    p->Lchild = NULL;
    p->Rchild = NULL;
    return p;
}

// Given a binary tree, print its nodes in preorder
void PreTraverse(BiTree T)
{
    if(!T)return;
    printf("%d ", T->data);
    PreTraverse(T->Lchild);
    PreTraverse(T->Rchild);
}

// Given a binary tree, print its nodes in inorder
void InorderTraverse(BiTree T)
{
    if(!T)return;
    InorderTraverse(T->Lchild);
    printf("%d ", T->data);
    InorderTraverse(T->Rchild);
}

// Given a binary tree, print its nodes in postorder
void PostTraverse(BiTree T)
{
    if(!T)return;
    PostTraverse(T->Lchild);
    PostTraverse(T->Rchild);
    printf("%d ", T->data);
}

// A function to print the whole leaf nodes and count the number of leaves  
void Leaves_1(BiTree T, int &count)
{
    if(!T)return;
    if(!(T->Lchild) && !(T->Rchild))
    {
        count++;
        printf("%d ", T->data);
    }
    Leaves_1(T->Lchild, count);
    Leaves_1(T->Rchild, count);    
}

// A function to print the whole leaf nodes and count the number of leaves
int Leaves_2(BiTree T)
{
    if(!T)return 0;
    if(!(T->Lchild) && !(T->Rchild))return 1;
    return (Leaves_2(T->Lchild) + Leaves_2(T->Rchild));
}

// Given a binary tree, get its depth
void Depth_1(BiTree T, int lev, int &dep)
{
    if(!T)return;
    printf(" %d ", T->data);
    printf(" %d\n", lev);
    if(lev > dep)dep = lev;
    Depth_1(T->Lchild, lev+1, dep);
    Depth_1(T->Rchild, lev+1, dep);
}

// Given a binary tree, get its depth
int Depth_2(BiTree T)
{
    if(!T)return 0;
    int l,r;
    l = Depth_2(T->Lchild);
    r = Depth_2(T->Rchild);
    return l > r ? l+1 : r+1;
}

void CreateBiTree(BiTree &T, int *def, int &i)
{
    if(def[i] == -1)
    {
        T = NULL;
        i++;
    }
    else
    {
        if(!(T=(BiTree)malloc(sizeof(BiTNode))))exit(OVERFLOW);
        T->data = def[i];
        ++i;
        CreateBiTree(T->Lchild, def, i);
        CreateBiTree(T->Rchild, def, i);
    }
}

// Driver program to test above functions
int main(void)
{
    BiTree T;
    BiTree p;
    InitBiTree(T);
    InitBiTree(p);
    BiTree temp;
    temp = MakeNode(100);
    InsertChild(T, NULL, 0, temp);
    temp = MakeNode(200);
    InsertChild(p, NULL, 0, temp);
    InsertChild(T, T, 1, p);
    temp = MakeNode(300);
    InsertChild(T, p, 0, temp);
    temp = MakeNode(400);
    InsertChild(T, T, 0, temp);
    temp = MakeNode(500);
    InsertChild(T, p, 1, temp);

    PreTraverse(T);
    // InorderTraverse(T);
    // PostTraverse(T);
    printf("\n");
    int num_leaves = 0, dep = 0;
    Leaves_1(T, num_leaves);
    // num_leaves = Leaves_2(T);
    printf("\n num_leaves = %d\n", num_leaves);
    Depth_1(T, 1, dep);
    // dep = Depth_2(T);
    printf(" dep = %d", dep);
}