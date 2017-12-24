#include<stdio.h>
#include<stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OVERFLOW 0

typedef int QElemType;
typedef int Status;

typedef struct QNode
{
    QElemType data;
    struct QNode *next;
}QNode, *QueuePtr;

typedef struct
{
    QueuePtr front;
    QueuePtr rear;
}LinkQueue;

// 构造一个带头结点的空队列
Status InitQueue(LinkQueue &Q)
{
    QNode *p = (QueuePtr)malloc(sizeof(QNode));
    if(!p)exit(OVERFLOW);
    p->next = NULL;
    Q.front = Q.rear = p;
    return OK;
}

// 插入元素e为队列Q的新的队尾元素
Status EnQueue(LinkQueue &Q, QElemType e)
{
    QNode *p = (QueuePtr)malloc(sizeof(QNode));
    if(!p)return ERROR;
    p->next = NULL;
    p->data = e;
    Q.rear->next = p;
    Q.rear = p;
    return OK;
}

// 若Q为空队列，则返回TRUE，否则返回，FALSE
Status QueueEmpty(LinkQueue Q)
{
    if(Q.rear == Q.front)
    {
        printf("队列为空\n");
        return TRUE;
    }
    return FALSE;
}

// 删除Q的队头元素，并用e返回其值
Status DeQueue(LinkQueue &Q, QElemType &e)
{
    if(QueueEmpty(Q))return ERROR;
    QNode *p = Q.front->next;
    e = p->data;
    Q.front->next = p->next;
    if(p == Q.rear)Q.rear = Q.front;
    free(p);
    return OK;
}

int main(void)
{
    LinkQueue Q;
    QElemType e;
    InitQueue(Q);
    EnQueue(Q, 50);
    EnQueue(Q, 100);
    DeQueue(Q, e);
    printf("%d\n", e);
    DeQueue(Q, e);
    printf("%d\n", e);
    DeQueue(Q, e);
    return 0;
}