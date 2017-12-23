#include<stdio.h>
#include<stdlib.h>

#define OVERFLOW -2
#define OK 1
#define ERROR 0
#define TRUE 1
#define ERROR 0

typedef int ElemType;
typedef int Status;

#define LIST_INIT_SIZE 100  // 线性表存储空间的初始分配量
#define LISTINCREMENT 10    // 线性表存储空间的分配增量

typedef struct
{
    ElemType *elem;     // 存储空间基址
    int length;         // 当前长度
    int listsize;       // 当前分配的存储容量
}SqList;

// 构造一个空的线性表L
Status InitList_Sq(SqList &L)
{
    L.elem = (ElemType *)malloc(LIST_INIT_SIZE*sizeof(ElemType));
    if(!L.elem)exit(OVERFLOW);  // 存储分配失败
    L.length = 0;               // 空表长度为0
    L.listsize = LIST_INIT_SIZE;// 初始存储容量
    return OK;
}

// 获取表中第i个元素并赋值给e
Status GetElem(SqList L, int i, ElemType &e)
{
    if(i < 1 || i > L.length)return ERROR;  // i值不合法
    e = L.elem[i-1];                        // 所需元素的值赋给e
    return OK;
}

// 在顺序线性表L中第i个位置之前插入新的元素e
Status ListInsert_Sq(SqList &L,int i,ElemType e)
{
    ElemType *newbase = 0;
    if(i < 1 ||i > L.length+1) return ERROR; // i值不合法
    if(L.length >= L.listsize)               // 若当前存储空间已满，增加分配
    {
        newbase = (ElemType *)realloc(L.elem,(L.listsize + LISTINCREMENT) * sizeof(ElemType));
        if(!newbase)exit(OVERFLOW); // 存储分配失败
        L.elem = newbase;           // 新基址
        L.listsize += LISTINCREMENT;// 增加存储容量
    }
    for(int j = L.length-1; j >= i-1; --j) 
        L.elem[j+1] = L.elem[j];    // 插入位置及之后的元素右移
    L.elem[i-1] = e;// 插入e
    ++L.length;     // 表长增1
    return OK;
}

// 获取表长
int ListLength(SqList L)
{
    return L.length;
}

// 在顺序线性表L中删除第i个元素，并用e返回其值
Status ListDelete_Sq(SqList &L,int i,ElemType &e)
{
    if((i < 1) || (i > L.length))return ERROR; // i值不合法
    e = L.elem[i-1];
    for(int j = i-1; j < L.length-1; ++j)      // 被删除元素之后的元素左移
        L.elem[j] = L.elem[j+1];               // 表长减1
    --L.length;
    return OK;
}

//  在顺序线性表L中查找第1个与e相等的元素的位序
int LocateElem_Sq(SqList L, ElemType e)
{
    int i = 1;
    while(i <= L.length && L.elem[i-1]!=e)i++;
    if(i <= L.length)return i;
    return 0;
}

// 已知顺序线性表La和Lb的元素按值非递减排列
// 归并La和Lb得到新的顺序线性表Lc，Lc的元素也按值非递减排列
void Merge_Sq(SqList La, SqList Lb, SqList &Lc)
{
    int pos_a, pos_b, pos_c;            // 定义变量表示各表的记录位置
    pos_a = pos_b = pos_c = 1;
    int elem_a, elem_b;
    while(pos_b <= ListLength(Lb) && pos_a <= ListLength(La))
    {
        GetElem(La, pos_a, elem_a);     // 获取表La元素elem_a
        GetElem(Lb, pos_b, elem_b);     // 获取表Lb元素elem_b
        if(elem_a < elem_b)                         // 若elem_a小于elem_b
        {
            ListInsert_Sq(Lc, pos_c++, elem_a);     // 将elem_a插入表Lc，表Lc记录位置后移
            pos_a++;                                // 表La记录位置后移
        }
        else if(elem_a == elem_b)                   // 若elem_a等于elem_b
        {
            ListInsert_Sq(Lc, pos_c++, elem_a);     // 将elem_a插入表Lc，表Lc记录位置后移
            ListInsert_Sq(Lc, pos_c++, elem_b);     // 将elem_b插入表Lc，表Lc记录位置后移
            pos_a++;pos_b++;                        // 表La,Lb记录位置后移
        }
        else                                        // 若elem_a大于elem_b
        {
            ListInsert_Sq(Lc, pos_c++, elem_b);     // 将elem_b插入表Lc，表Lc记录位置后移
            pos_b++;                                // 表Lb记录位置后移
        }
    }

    // 若表Lb记录位置到达表尾，将表La剩余元素插入表Lc
    while(pos_a <= ListLength(La))                  
    {
        GetElem(La, pos_a, elem_a);
        ListInsert_Sq(Lc, pos_c++, elem_a);
        pos_a++;
    }

    // 若表La记录位置到达表尾，将表Lb剩余元素插入表Lc
    while(pos_b <= ListLength(Lb))                  
    {
        GetElem(Lb, pos_b, elem_b);
        ListInsert_Sq(Lc, pos_c++, elem_b);
        pos_b++;
    }
}

int main(void)
{
    SqList L;
    if(InitList_Sq(L) != OK)printf("初始化失败\n");
    else printf("初始化成功\n");

    // ListInsert_Sq()测试代码
    int i;
    for(i = 1; i <= 10; i++)
    {
        if(ListInsert_Sq(L, i, 100+i-1) == ERROR)printf("插入失败\n");   
        else printf("%d ", L.elem[i-1]);
    }
    printf("\n");

    // ListDelete_Sq()测试代码
    ElemType e;
    ListInsert_Sq(L, 1, 100+i-1);
    if(ListDelete_Sq(L, 1, e) == ERROR)printf("删除失败\n");
    else printf("删除的元素e为%d\n", e);
    
    // Merge_Sq()测试代码
    SqList La, Lb, Lc;
    InitList_Sq(La);
    InitList_Sq(Lb);
    InitList_Sq(Lc);
    for(i = 1; i <= 5; i++)
    {
        ListInsert_Sq(La, i, i*2);
        ListInsert_Sq(Lb, i, i);
    }
    Merge_Sq(La, Lb, Lc);
    for(i = 1; i <= 10; i++)
        printf("%d ", Lc.elem[i-1]);
    return 0;
}