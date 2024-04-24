//用数组实现的链表结构，数组下标0位，没有元素
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAXSIZE 10
typedef char DataType;
typedef struct 
{
    DataType data;
    int cursor;//cursor保存的是链表下一个位置的数组位置
}StaticList[MAXSIZE];//本身就是个指针似乎

void Init(StaticList space,int* av){//初始化，如此可以串联起这个数组
    int k;
    space[0].cursor=-1;
    for(k=1;k<MAXSIZE-1;k++) space[k].cursor=k+1;//连链
    space[MAXSIZE-1].cursor=-1;//标记链尾
    *av=1;//备用空间的头指针
}

void Visit(StaticList space,int av){
    int i=1;
    while(i!=av){
        printf("%c",space[i].data);
        i=space[i].cursor;
    }
}

int Get(StaticList space,int* av){//分配结点
    int i;
    i=*av;//使用备用空间头指针
    *av=space[*av].cursor;//指针指向下一个空间
    return i;
}

void Create(StaticList space,int *av){
    printf("请输入数据：");
    char c=getchar();
    int i;

    while(c!='\n'){
        i=Get(space,av);
        space[i].data=c;
        c=getchar();
    }
}

void Free(StaticList space,int* av,int k){//从备用链表单链表中回收序号为k的结点，现在k是备用链表头结点了
    space[k].cursor=*av;
    *av=k;
}

int main(){//测试静态链表
    StaticList space;
    int av;
    Init(space,&av);
    Create(space,&av);
    Visit(space,av);
}