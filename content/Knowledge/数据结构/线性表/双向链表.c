//前后互指
#include <stdio.h>
#include <stdlib.h>
typedef struct {
    char c
}Data;


typedef struct Node{
    struct Node *prior; 
    Data data;
    struct Node *next;
}List;
void Init(List **L){
    *L=(List*)malloc(sizeof(List));
    (*L)->prior=NULL;
    (*L)->next=NULL;
}
void Create(List* L){
    List* p=L;
    for(int i=2;i<=3;i++){
        List* q=(List*)malloc(sizeof(List));
        q->prior=NULL;
        q->next=NULL;
        q->data.c='o';

        p->next=q;
        q->prior=p;
        p=p->next;
    }
}
void Insert(List* L,Data data,int add){
    List* p=L;
    List* temp=(List*)malloc(sizeof(List));
    temp->data=data;
    temp->prior=NULL;
    temp->next=NULL;

    if(add==1){
        temp->next=p->next;
        p->next->prior=temp;
        p->next=temp;
        temp->prior=p;
    }
    else {
        List* tp;
        for(int i=1;i<add;i++){
            p=p->next;
        }
        if(p->next==NULL){
            p->next=temp;
            temp->prior=p;
        }
        else {
            temp->next=p->next;
            p->next->prior=temp;
            p->next=temp;
            temp->prior=p;
        }
    }
}
