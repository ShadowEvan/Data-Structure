#include<stdio.h>
#include<stdlib.h>

#define OVERFLOW -2
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef int SElemType;
typedef int Status;

typedef struct LSNode
{
    SElemType data;         // 数据域
    struct LSNode *next;    // 指针域
}LSNode, *LStack;

Status InitStack(LStack &S)
{
    S = (LStack)malloc(sizeof(LSNode));
    if(!S)exit(OVERFLOW);
    S->next = NULL;
    return OK;
}

Status Push(LStack &S, SElemType e)
{
    LSNode *p = (LStack)malloc(sizeof(LSNode));
    if(!S)return ERROR;
    p->data = e;    
    
    // 入栈操作，头插法插入新结点
    p->next = S->next;
    S->next = p;
    return OK;
}

Status Pop(LStack &S, SElemType &e)
{
    if(!S->next)return ERROR;
    LSNode *p = S->next;    // 指针指向要出栈的结点
    e = p->data;            // 取出要出栈的元素值
    S->next = p->next;      // 出栈操作
    free(p);                // 释放结点
    return OK;
}

int main(void)
{
    LStack S, p = 0;
    SElemType e;
    InitStack(S);
    Push(S, 100);
    Push(S, 20);
    for(p = S->next; p != NULL; p = p->next)
    printf("%d " ,p->data);
    Pop(S, e);
    printf("\n%d", e);
    return 0;
}
