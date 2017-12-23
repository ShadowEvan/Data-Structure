#include<stdio.h>
#include<stdlib.h>

#define OVERFLOW -2
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef int ElemType;
typedef int Status;

typedef struct LNode
{
    ElemType data;          // 数据域
    struct LNode *next;     // 指针域
}LNode, *LinkList;

Status InitList(LinkList &L)
{
    L = (LinkList)malloc(sizeof(LNode));
    if(!L)exit(OVERFLOW);   // 存储分配失败
    L->next = NULL;
    return OK;
}

// 当第i个元素存在时，其值赋给e并返回OK，否则返回ERROR
Status GetElem(LinkList L, int i, ElemType &e)
{
    LinkList p = L->next;   // p指向第一个结点
    int j = 1;              // j为计数器
    while(p && j < i)       // 顺链表向后查找，直到p指向第i个元素或p为空
    {
        p = p->next;
        ++j;
    }
    if(!p || j > i)return ERROR;    // 第i个元素不存在
    e = p->data;                    // 取所需元素并赋值给e
    return OK;
}

// 在带头结点的单链线性表L中第i个位置之前插入元素e
Status ListInsert(LinkList &L, int i, ElemType e)
{
    LinkList p = L;         // p指向头结点
    LinkList s = 0;
    int j = 0;
    while(p && j < i-1)     // 寻找第i-1个结点
    {
        p = p->next;
        ++j;
    }
    if(!p || j > i-1)return ERROR;          // i小于1或者大于表长加1
    // 生成新结点
    s = (LinkList)malloc(sizeof(LNode));    
    s->data = e;

    // 插入L中
    s->next = p->next;                                    
    p->next = s;
    return OK;
}

// 在带头结点的单链线性表L中，删除第i个元素，并由e返回其值
Status ListDelete(LinkList &L, int i, ElemType &e)
{
    LinkList p = L, q = 0;  // p指向头结点
    int j = 0;
    while(p && j < i-1)     // 寻找第i个结点，并令p指向其前趋
    {
        p = p->next;
        ++j;
    }
    if(!p || j > i-1)return ERROR;          // 删除位置不合理
    q = p->next;
    e = q->data;            // 取所删元素

    // 删除并释放结点
    p->next = q->next;
    free(q);
    return OK;
}

// 顺位序插入n个元素，建立带头结点的单链线性表L（尾插法）
void CreateList_tail(LinkList &L, int n, int data[])
{
    int i = 0;
    while(i < n)
    {
        ListInsert(L, i+1, data[i]);
        i++;
    }
}

// 逆位序插入n个元素，建立带头结点的单链线性表L（头插法）
void CreateList_head(LinkList &L, int n, int data[])
{
    int i = n-1;
    while(i >= 0)
    {
        ListInsert(L, 1, data[i]);
        i--;
    }
}

// 在带头结点的单链线性表L中，删除元素值为e的结点
Status ListDeleteElem(LinkList &L, ElemType e)
{
    LinkList p = L->next, q = L;
    while(p)
    {
        // p指向的元素值为e时，进行删除操作并跳出循环
        if(p->data == e)
        {
            q->next = p->next;
            free(p);
            break;
        }
        p = p->next;
        q = q->next;
    }
    if(!p)return ERROR;
    return OK;
}

int main(void)
{
    LinkList L, p = 0;
    int data[] = {1, 2, 3, 4, 5};
    int len = 5;
    ElemType e;
    if(InitList(L) != OK)printf("初始化失败\n");
    else printf("初始化成功\n");

    // 测试插入操作并创建链表
    // CreateList_head(L, len, data);
    CreateList_tail(L, len, data);
    p = L->next;
    while(p)
    {
        printf("%d  ", p->data);
        p = p->next;
    }
    printf("\n");

    // 测试删除操作
    ListDelete(L, 2, e);
    ListDeleteElem(L, 3);
    for(p = L->next;p != NULL; p = p->next)
        printf("%d  ", p->data);
    return 0;
}
