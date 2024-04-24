//循环链表的队列，所以有尾指针，单设一个尾指针也可以，尾指针指的就是队尾元素
#include <stdlib.h>
typedef struct node{
    Data data;
    struct node *next;
}Node;
typedef struct{
    int a;
}Data;

typedef struct 
{
    Node *front;
    Node *rear;
}Queue;

int Init(Queue *Q){//初始化队列
    Q->front=(Node*)malloc(sizeof(Node));
    if(Q->front!=NULL){
        Q->rear=Q->front;
        Q->front->next=NULL;
        return 1;
    }
    else return 0;
}

int Enter(Queue *Q,Data x){//进入队列
    Node *newp;
    newp=(Node*)malloc(sizeof(Node));
    if(newp!=NULL){
        newp->data=x;
        newp->next=NULL;
        Q->rear->next=newp;
        Q->rear=newp;
        return 1;
    }
    else return 1;
}
int Delete(Queue *Q,Data*x){//出队列
    Node *p;
    if(Q->front==Q->rear) 
        return 0;
    p=Q->front->next;
    Q->front->next=p->next;
    if(Q->rear==p){
        Q->rear=Q->front;
    }
    *x=p->data;
    free(p);
    return 1;
}