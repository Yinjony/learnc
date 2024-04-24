#define SIZE 50//基础栈操作
typedef struct 
{
    Data data[SIZE];
    int top;
}Stack;
typedef struct 
{
    int a;
}Data;

void Init(Stack *S){//初始化
    S->top=-1;
}
int Push(Stack *S,Data x){//压栈
    if(S->top==SIZE-1){//判满Isfull
        return 0;
    }
    S->top++;
    S->data[S->top]=x;
    return 1;
}
int Pop(Stack *S,Data *x){//出栈
    if (S->top==-1){//判空Isempty
        return 0;
    }
    else {
        *x=S->data[S->top];
        S->top--;
        return 1;
    }
}
int GetTop(Stack *S,Data *x){//读取栈
    if(S->top==-1){
        return 0;
    }
    else {
        *x=S->data[S->top];
        return 1;
    }
}
void ClearStack(Stack *S){//清空栈
    S->top=-1;
}