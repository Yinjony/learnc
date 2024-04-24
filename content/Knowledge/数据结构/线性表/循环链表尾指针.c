//循环链表，有个尾指针
#include <stdio.h>
#include <stdlib.h>
typedef struct 
{
    char name;
} Data;

typedef struct Node
{
    Data data;
    struct Node *next;
} List;

void Init(List **L){
    *L=(List*)malloc(sizeof(List));
    (*L)->next=*L;//循环链表，指向的不再是null而是本身
}

void Create(List *L){
    List *rear,*s;
    char c;
    rear=L;
    printf("输入字符：");
    scanf("%c",&c);
    while (c!='0')
    {
        s=(List*)malloc(sizeof(List));
        s->data.name=c;
        rear->next=s;
        rear=s;
        scanf("%c",&c);
    }
    rear->next=L;
} 
List* merge_1(List *A,List *B){//头指针遍历合并
    List *p,*q;
    p=A;
    q=B;
    while (p->next!=A)
    {
        p=p->next;
    }
    while (q->next!=B)
    {
        q=q->next;
    }
    q->next=A;
    p->next=B->next;
    free(B);
    return A;
}
List* merge_2(List *RA,List *RB){//均是尾指针
    List *p;
    p=RA->next;
    RA->next=RB->next->next;
    free(RB->next);
    RB->next=p;
    return RB;
}
int main(){
   
}