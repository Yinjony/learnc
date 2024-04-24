//循环链表的队列，所以有尾指针，单设一个尾指针也可以，尾指针指的就是队尾元素，有头指针
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
typedef char Data;
typedef struct node{
    Data data;
    struct node *next;
}Node;

typedef struct 
{
    Node *front;
    Node *rear;
}Queue;

bool InitQueue(Queue *Q){//初始化队列
    Q->front=(Node*)malloc(sizeof(Node));
    if(Q->front!=NULL){
        Q->rear=Q->front;
        Q->front->next=NULL;
        return true;
    }
    else return false;
}

void Visit(Queue *Q){//从队头开始访问
    Node *p;
    p=Q->front->next;
    while(p!=NULL){
        printf("%c",p->data);
        p=p->next;
    }
}

bool IsEmpty(Queue Q){
    if(Q.rear==Q.front) return true;
    else return false;
}

bool EnterQueue(Queue *Q,Data x){//进入队列
    Node *newp;
    newp=(Node*)malloc(sizeof(Node));
    if(newp!=NULL){
        newp->data=x;
        newp->next=NULL;
        Q->rear->next=newp;//插入到尾结点
        Q->rear=newp;
        return true;
    }else return false;
}

bool DeleteQueue(Queue *Q,Data*x){//出队列
    Node *p;
    if(Q->front==Q->rear) 
        return false;
    
    p=Q->front->next;
    Q->front->next=p->next;//第一个元素出列
    if(Q->rear==p){//如果p就是最后一个结点
        Q->rear=Q->front;
    }
    *x=p->data;
    free(p);
    return true;
}

int main(){//测试
    Queue Q;
    InitQueue(&Q);
    char c;
    printf("输入数据：");
    while((c=getchar())!='\n'){
        EnterQueue(&Q,c);
    }
    Visit(&Q);
}