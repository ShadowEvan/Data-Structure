#include<stdio.h>
#include<stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OVERFLOW -2
#define MAXQSIZE 30     // 最大队列长度

typedef int Status;
typedef int QElemType;

typedef struct
{
    QElemType *base;    // 初始化的动态分配存储空间
    int front;          // 头指针，若队列不空，指向队列头元素
    int rear;           // 尾指针，若队列不空，指向队列尾元素的下一个位置
}SqQueue;

// 构造一个空队列Q
Status InitQueue(SqQueue &Q)
{
    Q.base = (QElemType *)malloc(MAXQSIZE * sizeof(QElemType));
    if(!Q.base)exit(OVERFLOW);  // 存储分配失败
    Q.front = 0;
    Q.rear = 0;
    return OK;
}

// 若队列不满，插入元素e为Q的新的队尾元素
Status EnQueue(SqQueue &Q, QElemType e)
{
    if((Q.rear + 1) % MAXQSIZE == Q.front)return ERROR; // 特殊情况——队列满
    Q.base[Q.rear] = e;
    Q.rear = (Q.rear + 1) % MAXQSIZE;
    return OK;
}

// 若队列不空，则删除Q的队头元素，用e返回其值，并返回OK
Status DeQueue(SqQueue &Q, QElemType e)
{
    if(Q.front == Q.rear)return ERROR;  // 特殊情况——队列空
    e = Q.base[Q.front];
    Q.front = (Q.front + 1) % MAXQSIZE;
    return OK;
}

// 返回Q的元素个数，即队列的长度
int QueueLength(SqQueue Q)
{
    return ((Q.rear - Q.front + MAXQSIZE) % MAXQSIZE);
}

int main(void)
{
    return 0;
}