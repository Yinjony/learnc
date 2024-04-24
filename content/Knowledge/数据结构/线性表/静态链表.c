//用数组实现的链表结构，数组下标0位，没有元素
#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 10
typedef struct 
{
    char name;
    int a;
}Info;

typedef struct 
{
    Info data;
    int cursor;
}StaticList[MAXSIZE];

void Init(StaticList L,int* av){//初始化，cursor保存的是链表下一个位置的数组位置，如此可以串联起这个数组，然后链表内的数组顺序一般是无序的
    int k;
    L[0].cursor=-1;
    for(k=1;k<MAXSIZE-1;k++) L[k].cursor=k+1;
    L[MAXSIZE-1].cursor=-1;
    *av=1;
}
int Get(StaticList L,int* av){
    int i;
    i=*av;
    *av=L[*av].cursor;
    return i;
}
void Free(StaticList L,int* av,int k){//从备用链表单链表中回收序号为k的结点，现在k是备用链表头结点了
    L[k].cursor=*av;
    *av=k;
}
int main(){
    StaticList L;
    int av;
    Init(L,&av);
    int i=Get(L,&av);
    L[i].data.a=242;
    L[i].data.name='k';
    printf("%c,%d",L[i].data.name,L[i].data.a);
    
}