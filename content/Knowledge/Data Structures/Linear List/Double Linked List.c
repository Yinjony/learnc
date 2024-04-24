#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef char Data;

typedef struct Node{
    struct Node *prior; 
    Data data;
    struct Node *next;
}List;

void Init(List **L){//初始化
    *L=(List*)malloc(sizeof(List));
    (*L)->prior=NULL;
    (*L)->next=NULL;
}

void Visit(List *L){//访问双向链表
    List *p=L;
    printf("\n输入顺序：");
    while(1){
        char c=getchar();
        if(c=='p'){
            p=p->prior;
            printf("%c",p->data);
        }else if(c=='n'){
            p=p->next;
            printf("%c",p->data);
        }else if(c=='\n') break;
    }
}

void Create(List *L){//创建双向链表
    printf("输入数据：");
    List* p=L;
    char c=getchar();
    while(c!='\n'){
        List* q=(List*)malloc(sizeof(List));
        q->next=NULL;
        q->data=c;

        p->next=q;
        q->prior=p;
        p=p->next;
        c=getchar();
    }
}

bool Insert(List *L,int i,Data data){//插入操作，先改前，再改后
    if(i<1) return false;//插入位置不合法

    List *p=L;
    List *temp=(List*)malloc(sizeof(List));
    
    for(int t=0;t<i;t++) p=p->next;//移到插入位置
    if(temp){//开始插入
        temp->data=data;
        temp->prior=p->prior;
        p->prior->next=temp;
        temp->next=p;
        p->prior=temp;
        return true;
    }else return false;
}

bool Delete(List *L,int i,Data *x){//删除操作，先改前再改后
    if(i<1) return false;//删除位置不合法

    List *p=L;
    for(int t=0;t<i;t++) p=p->next;//移到删除位置
    *x=p->data;
    p->prior->next=p->next;//进行删除
    p->next->prior=p->prior;
    free(p);

    return true;
}
int main(){//测试
    List *L;
    Init(&L);
    Create(L);
    Visit(L);
    Insert(L,2,'j');
    Visit(L);
    char *x;
    Delete(L,3,&x);
    Visit(L);
}