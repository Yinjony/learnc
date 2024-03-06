#include <stdio.h>
#include <malloc.h>
#define LEN sizeof(struct student)
struct student
{
    int num;
    float score;
    struct student *next;
};
int main()
{
    struct student *head,*p;
    head=p=(struct student *)malloc(LEN);
    scanf("%d,%f",&p->num,&p->score);
    head->next=p;
    p->next=NULL;
    p=head;
    printf("\n结点 1:%d,%6.2f\n",p->num,p->score);
    p=p->next;
    printf("结点 2:%d,%6.2f\n",p->num,p->score);
    return 0;
}