#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define SIZE 50
typedef char Data;
typedef struct 
{
    Data data[SIZE];
    int top;
}Stack;

void Init(Stack *S){//初始化
    S->top=-1;
}

void Visit(Stack S){
    for(int i=0;i<=S.top;i++){
        printf("%c",S.data[i]);
    }
}

bool IsEmpty(Stack *S){//判空
    if(S->top==-1) return true;
    else return false;
}

bool IsFull(Stack *S){//判满
    if(S->top==SIZE-1) return true;
    else return false;
}

bool Push(Stack *S,Data x){//压栈
    if(IsFull(S)){//判满Isfull
        return false;
    }
    S->top++;
    S->data[S->top]=x;
    return true;
}

bool Pop(Stack *S,Data *x){//出栈
    if (IsEmpty(S)){//判空Isempty
        return false;
    }
    else {
        *x=S->data[S->top];
        S->top--;
        return true;
    }
}

bool GetTop(Stack *S,Data *x){//读取栈
    if(IsEmpty(S)){
        return false;
    }
    else {
        *x=S->data[S->top];
        return true;
    }
}

void ClearStack(Stack *S){//清空栈
    S->top=-1;
}


int main(){//测试
    Stack S;
    Init(&S);
    char c;
    printf("输入数据：");
    while((c=getchar())!='\n'){
        Push(&S,c);
    }
    Visit(S);
    char x;
    Pop(&S,&x);
    printf("\n%c\n",x);
    Visit(S);
}