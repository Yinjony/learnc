//用数组，头尾两边各有一个栈
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define SIZE 100
typedef int Data;
typedef struct 
{
    Data data[SIZE];
    int top[2];
}DqStack;

void InitStack(DqStack *S){//对两端进行初始化
    S->top[0]=-1;
    S->top[1]=SIZE;
}

void Visit(DqStack S){
    printf("左端：");
    for(int i=0;i<=S.top[0];i++){
        printf("%d",S.data[i]);
    }
    printf("右端：");
    for(int i=SIZE-1;i>=S.top[1];i--){
        printf("%d",S.data[i]);
    }
}

bool Push(DqStack *S,Data x,int i){//入栈操作
    if (S->top[0]+1==S->top[1]){//判断是否满
        return false;
    }
    switch (i){//插入位置
        case 0:
            S->top[0]++;
            S->data[S->top[0]]=x;
            break;
        case 1:
            S->top[1]--;
            S->data[S->top[1]]=x;
            break;
        default:
            return false;
    }
    return true;
}

bool Pop(DqStack *S,Data *x,int i){//出栈操作
    switch (i){
        case 0:
            if(S->top[0]==-1) return false;//判断是否为空
            *x=S->data[S->top[0]];
            S->top[0]--;
            break;
        case 1:
            if(S->top[1]==-1) return false;
            *x=S->data[S->top[1]];
            S->top[1]++;
            break;
        default:
            return false;
    }
    return true;
}

int main(){
    DqStack S;//数组栈，没必要设指针
    InitStack(&S);
    printf("输入量：");
    int x;
    scanf("%d",&x);
    int num[x];
    printf("入栈位置；");
    for(int i=0,t;i<x;i++){
        scanf("%1d",&t);
        num[i]=t;
    }
    printf("输入数据：");
    for(int i=0,k;i<x;i++){
        scanf("%1d",&k);
        Push(&S,k,num[i]);
    }
    Visit(S);
    Data t;
    Pop(&S,&t,0);
    printf("\n%d\n",t);
    Visit(S);
}