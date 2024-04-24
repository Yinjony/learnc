//循环队列，总长不变，类似于通道，用数组实现，需要用MAXSIZE来进行头尾相交的判断或者空出一个位置来
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAXSIZE 50
typedef char Data;
typedef struct{
    Data data[MAXSIZE];
    int front;//头
    int rear;//尾
}Queue;

void Init(Queue *Q){//初始化循环队列
    Q->front=Q->rear=0;
}

void Visit(Queue Q){
    for(int i=Q.front;i<=Q.rear;i++){
        printf("%c",Q.data[i]);
    }
}

bool Enter(Queue *Q,Data x){//入队，使用MAXSIZE，利用余数完成循环
    if ((Q->rear+1)%MAXSIZE==Q->front){//如果追上则报错
        return false;
    }
    Q->data[Q->rear]=x;
    Q->rear=(Q->rear+1)%MAXSIZE;
    return true;
}

bool Delete(Queue *Q,Data *x){//出队
    if(Q->front==Q->rear){
        return false;
    }
    *x=Q->data[Q->front];
    Q->front=(Q->front+1)%MAXSIZE;
    return true;
}

int main(){//测试
    Queue Q;
    Init(&Q);
    char c;
    printf("输入数据：");
    while((c=getchar())!='\n'){
        Enter(&Q,c);
    }
    Visit(Q);
    char x;
    Delete(&Q,&x);
    printf("\n出队之后：");
    Visit(Q);
}