#include <stdio.h>//头为栈顶
#include <stdbool.h>
#include <stdlib.h>

#define SIZE 10

typedef char Data;
typedef struct node{
    Data data;
    struct node *next;
}LinkStackNode,*LinkStack;

void Init(LinkStackNode **top){//初始化
    (*top)=(LinkStackNode*)malloc(sizeof(LinkStackNode));
    (*top)->next=NULL;
}

void Visit(LinkStackNode *top){//访问
    LinkStackNode *p=top->next;
    while(p!=NULL){
        printf("%c",p->data);
        p=p->next;
    }
}

bool Push(LinkStackNode *top,Data x){//链栈的入栈操作，只是在链头进行入栈，出栈操作
    LinkStackNode *temp;
    temp=(LinkStackNode*)malloc(sizeof(LinkStackNode));
    if(temp==NULL) return false;
    temp->data=x;
    temp->next=top->next;
    top->next=temp;
    return true;
}
bool Pop(LinkStackNode *top,Data *x){//链栈的出栈操作
    LinkStackNode *temp;
    temp=top->next;
    if(temp==NULL) return false;
    top->next=temp->next;
    *x=temp->data;
    free(temp);
    return true;
}

int main(){//测试
    // LinkStackNode *top;
    // Init(&top);
    // char c;
    // printf("输入数据：");
    // while((c=getchar())!='\n'){
    //     Push(top,c);
    // }
    // Visit(top);
    // char x;
    // Pop(top,&x);
    // printf("\n%c\n",x);
    // Visit(top);

    LinkStack top[SIZE];//多栈运算操作
    for(int i=0;i<SIZE;i++){
        Init(&(top[i]));
    }
    char c;
    printf("输入量：");//填入数据的量
    int x;
    scanf("%d",&x);
    int num[x];
    printf("输入位置：");//位置
    for(int i=0;i<x;i++){
        int a;
        scanf("%1d",&a);
        num[i]=a;
    }

    printf("输入数据：");
    for(int i=0;i<x;i++){
        c=getchar();
        Push(top[num[i]],c);
    }
    
    for(int i=0;i<SIZE;i++){
        printf("%d:",i);
        Visit(top[i]);
    }
}