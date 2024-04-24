//循环链表，有个尾指针指向尾结点,一般也是直接访问尾结点再访问头结点,有头指针的
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef char Data;
typedef struct Node
{
    Data data;
    struct Node *next;
} List;

void Init(List **L){
    *L=(List*)malloc(sizeof(List));
    (*L)->next=*L;//循环链表，指向的不再是null而是本身
}

void Visit(List *L){
    List *rear=L->next->next;//直接访问头结点的数据
    for(;rear!=L->next;rear=rear->next){
        printf("%c",rear->data);
    }
}

void Create(List **L){//填充链表
    List *rear,*s;
    char c;
    rear=*L;
    printf("输入字符：");
    c=getchar();
    while (c!='\n')
    {
        s=(List*)malloc(sizeof(List));
        s->data=c;
        rear->next=s;
        rear=s;
        c=getchar();
    }
    rear->next=*L;//此时L为一个不储存内容的结点，然后前驱是尾结点，其后是头结点
    *L=rear;//然后L指向尾结点
}

List* merge_1(List *A,List *B){//头指针遍历合并
    List *p,*q;
    p=A;
    q=B;
    while (p->next!=A) p=p->next;//到A的尾结点
    while (q->next!=B) q=q->next;//到B的尾结点
    q->next=A;//B的尾结点指向A的头指针
    p->next=B->next;//A的尾结点指向B的头结点
    free(B);
    return q;
}

List* merge_2(List *RA,List *RB){//均是尾指针
    List *p;
    p=RA->next;
    RA->next=RB->next->next;
    free(RB->next);
    RB->next=p;
    return RB;
}

bool Enter(List **L, Data x)//增加数据（和队列那里一样的思路用法）
{
    if((*L)==NULL) return false;
	List *pnew;
	pnew=(List*)malloc(sizeof(List));
	if(pnew==NULL) return false;
	pnew->data=x;
	pnew->next=(*L)->next;
	(*L)->next=pnew;
	(*L)=(*L)->next;
	return true;
}

bool Delete(List **L, Data *x)//删除链头（队头）数据
{
    if((*L)->next==(*L)) return false;
    List *p;
    p=(*L)->next->next;
    *x=(*L)->next->next->data;
    (*L)->next->next=(*L)->next->next->next;//next不等价于(*L)
    if(p==(*L)){
        (*L)=(*L)->next;
    }
    if(p==NULL) return false;
    free(p);
    return true;
}

int main(){
   List *L;//测试循环链表
   Init(&L);
   Create(&L);
   Visit(L);
//    printf("\n输入添加数据：");
//    char x=getchar();
//    Enter(&L,x);
//    Visit(L);
   char a;
   Delete(&L,&a);
   printf("\n删除后的链表：");
   Visit(L);
    // List *A,*B;//测试merge1
    // Init(&A);Init(&B);
    // Create(&A);
    // Create(&B);
    // List *C,*D;
    // C=merge_1(A->next,B->next);
    // Visit(C);
    // List *A,*B;//测试merge2
    // Init(&A);Init(&B);
    // Create(&A);
    // Create(&B);
    // List *C,*D;
    // C=merge_2(A,B);
    // Visit(C);
}