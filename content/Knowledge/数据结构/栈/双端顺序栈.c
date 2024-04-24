//用数组，头尾两边各有一个栈
#define SIZE 100
typedef struct 
{
    Data data[SIZE];
    int top[2];
}Stack;
typedef struct 
{
    int a;
}Data;

void InitStack(Stack *S){//对两端进行初始化
    S->top[0]=-1;
    S->top[1]=SIZE;
}
int Push(Stack *S,Data x,int i){//入栈操作
    if (S->top[0]+1==S->top[1]){//判断是否满
        return 0;
    }
    switch (i){
        case 0:
            S->top[0]++;
            S->data[S->top[0]]=x;
            break;
        case 1:
            S->top[1]++;
            S->data[S->top[1]]=x;
            break;
        default:
            return 0;
    }
    return 1;
}
int Pop(Stack *S,Data *x,int i){//出栈操作
    switch (i){
        case 0:
            if(S->top[0]==-1) return 0;//判断是否为空
            *x=S->data[S->top[0]];
            S->top[0]--;
            break;
        case 1:
            if(S->top[1]==-1) return 0;
            *x=S->data[S->top[1]];
            S->top[1]--;
            break;
        default:
            return 0;
    }
    return 1;
}