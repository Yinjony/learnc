//用链表实现栈结构
#include <stdlib.h>
#define SIZE 10
typedef struct node{
    Data data;
    struct node *next;
}Node;
Node* top[SIZE];//多栈运算，多个链栈连在一起
typedef struct{
    int a;
}Data;
//此处只是单个链栈的操作
int Push(Node *top,Data x){//链栈的入栈操作
    Node *temp;
    temp=(Node*)malloc(sizeof(Node));
    if(temp==NULL) return 0;
    temp->data=x;
    temp->next=top->next;
    top->next=temp;
    return 1;
}
int Pop(Node *top,Data *x){//链栈的出栈操作
    Node *temp;
    temp=top->next;
    if(temp==NULL) return 0;
    top->next=temp->next;
    *x=temp->data;
    free(temp);
    return 1;
}