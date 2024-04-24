//循环队列，总长不变，类似于通道，用数组实现，需要用MAXSIZE来进行头尾相交的判断或者空出一个位置来
#define MAXSIZE 50
typedef struct{
    Data data[MAXSIZE];
    int front;
    int rear;
}Queue;
typedef struct{
    int a;
}Data;

void Init(Queue *Q){//初始化循环队列
    Q->front=Q->rear=0;
}
int Enter(Queue *Q,Data x){
    if ((Q->rear+1)%MAXSIZE==Q->front){//使用MAXSIZE，利用余数完成循环
        return 0;
    }
    Q->data[Q->rear]=x;
    Q->rear=(Q->rear+1)%MAXSIZE;
    return 1;
}
int Delete(Queue *Q,Data *x){
    if(Q->front==Q->rear){
        return 0;
    }
    *x=Q->data[Q->front];
    Q->front=(Q->front+1)%MAXSIZE;
    return 1;
}