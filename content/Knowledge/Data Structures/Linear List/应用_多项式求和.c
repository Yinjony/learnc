#include <stdio.h>
#include <stdlib.h>
typedef struct Node
{
    int coef;
    int exp;
    struct Node *next;
}Polylist;

void Init(Polylist **L){
    *L=(Polylist*)malloc(sizeof(Polylist));
    if ((*L)==NULL) {
        printf("初始化未成功。");
        return;
    }
    Polylist *p=*L;
    p->exp=-1;
    while (1){
        Polylist *pnew=(Polylist*)malloc(sizeof(Polylist));
        scanf("%d",&(pnew->exp));
        if((pnew->exp)==-1){
            printf("结束输入。\n");
            p->next=NULL;
            free(pnew);
            break;
        }
        scanf("%d",&(pnew->coef));
        p->next=pnew;
        p=p->next;
    }
}
void PolyAdd(Polylist *polya,Polylist *polyb){
    Polylist *p,*q,*tail,*temp;
    int sum;
    if((polya->next)==NULL){
        printf("请先对多项式A输入数据。");
        return;
    }
    if((polyb->next)==NULL){
        printf("请先对多项式B输入数据。");
        return;
    }
    p=polya->next;
    q=polyb->next;
    tail=polya;
    while (p!=NULL&&q!=NULL)
    {
        if(p->exp<q->exp){
            tail->next=p;
            tail=p;
            p=p->next;
        }
        else if(p->exp==q->exp){
            sum=p->coef+q->coef;
            if(sum!=0){
                p->coef=sum;
                tail->next=p;
                tail=p;
                p=p->next;
                temp=q;
                q=q->next;
                free(temp);
            }
            else {
                temp=p;
                p=p->next;
                free(temp);
                temp=q;
                q=q->next;
                free(temp);
            }
        }
        else {
            tail->next=q;
            tail=q;
            q=q->next;
        }
    }
    if(p!=NULL){
        tail->next=p;
    }
    else {
        tail->next=q;
    }
    free(polyb);
}
void Printpoly(Polylist *L){
    if((L->next)==NULL){
        printf("数据为空");
    }
    Polylist *p=L->next;
    while ((p->next)!=NULL)
    {
        if((p->exp)==0){
            printf("%d+",p->coef);
            p=p->next;
        }
        else{
            printf("%dx^%d+",p->coef,p->exp);
            p=p->next;
        }
    }
    if((p->exp)==0){
        printf("%d",p->coef);
    }
    else {
        printf("%dx^%d",p->coef,p->exp);
    }
    printf("\n");
}

int main(){
    Polylist *polya,*polyb;
    Init(&polya);
    Printpoly(polya);
    Init(&polyb);
    Printpoly(polyb);
    PolyAdd(polya,polyb);
    Printpoly(polya);
}