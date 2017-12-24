#include<stdio.h>
#include<stdlib.h>

#define OVERFLOW -2
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define STACK_INIT_SIZE 100 // 存储空间初始分配量
#define STACKINCREMENT 10   // 存储空间分配增量

typedef int Status;
typedef int SElemType;
typedef struct 
{
    SElemType *base;    // 栈底指针
    SElemType *top;     // 栈顶指针
    int stacksize;      // 栈的当前可使用的最大容量
}SqStack;

// 构造一个空栈
Status InitStack(SqStack &S)
{
    S.base = (SElemType *)malloc(STACK_INIT_SIZE*sizeof(SElemType));
    if(!S.base)exit(OVERFLOW);      // 存储分配失败
    S.top = S.base;
    S.stacksize = STACK_INIT_SIZE;  // 初始存储容量
    return OK;
}

// 插入元素e为新的栈顶元素
Status Push(SqStack &S, SElemType e)
{
    SElemType *newbase;
    if(S.top - S.base >= S.stacksize)   // 若当前存储空间已满，增加分配
    {
        newbase = (SElemType *)realloc(S.base, (STACK_INIT_SIZE + STACKINCREMENT)*sizeof(SElemType));
        if(!newbase)exit(OVERFLOW);
        S.base = newbase;
        S.stacksize += STACKINCREMENT;
    }
    *S.top = e;                         // 插入元素
    S.top++;                            // 提取元素
    return OK;
}

// 若栈为空栈，则返回TRUE,否则返回FALSE
Status IsEmpty(SqStack S)
{
    if(S.top == S.base)
    {
        // printf("栈为空");
        return TRUE;
    }
    return FALSE;
}

// 若栈不为空，则删除S的栈顶元素，用e返回其值，并返回OK，否则返回ERROR
Status Pop(SqStack &S, SElemType &e)
{
    if(IsEmpty(S))return ERROR;         // 栈为空
    S.top--;                            // 栈顶指针指向的位置前移
    e = *S.top;                         // 提取元素
    return OK;
}

// 若栈不为空，则用e返回S的栈顶元素，并返回OK，否则返回ERROR
Status GetTop(SqStack S, SElemType &e)
{
    if(IsEmpty(S))return ERROR;
    e = *(S.top-1);
    return OK;
}

// 数制转换——十进制数转换成八进制
void Conversation(int N)
{
    SqStack S;
    SElemType e;
    InitStack(S);
    while(N != 0)
    {
        Push(S, N%8);
        N = N/8;
    }
    printf("\n");
    while(!IsEmpty(S))
    {
        Pop(S, e);
        printf("%d", e);
    }
}

// 括号匹配的检验
Status Match(char *exp, int n)
{
    int i = 0;
    char ch;
    SqStack S;
    SElemType e;
    InitStack(S);
    while(i < n)
    {
        ch = exp[i];
        if(ch == '(' || ch == '[')Push(S, ch);
        else if(ch == ')')
        {
            if(IsEmpty(S))return ERROR;
            Pop(S, e);
            if(e != '(')return ERROR;
        }
        else if(ch == ']')
        {
            if(IsEmpty(S))return ERROR;
            Pop(S, e);
            if(e != '[')return ERROR;
        }
        i++;
    }
    if(!IsEmpty(S))return ERROR;
    return OK;
}

int main(void)
{
    
    SqStack S;
    SElemType temp = 0;
    InitStack(S);

    // 测试Push操作
    for(int i = 0; i < 101; i++)
    {
        Push(S, 100+i);
        printf("%d  ", S.base[i]);
    }
    // 测试Pop操作
    Pop(S, temp);
    printf("\n%d", temp);

    // Conversation()测试代码
    Conversation(1348);
    
    // Match()测试代码
    char s[4] = {'[', '(', ')', ']'};
    if(Match(s, 4))printf("\nSuccess in matching!");
    else printf("Fail!");
    return 0;
}
