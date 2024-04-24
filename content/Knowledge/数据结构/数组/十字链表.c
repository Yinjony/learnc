#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

typedef struct OLNode{
    int row,col;
    ElementType value;
    struct OLNode *right,*down;
}OLNode,*OLink;



typedef struct{
    OLink *row_head,*col_head;//行列的头指针
    int m,n,len;//行，列，非零元素的个数
}CrossList;

int m,n,t;

CreateCrossList(CrossList *M){//创建
    scanf(&m,&n,&t);//输入行数列数和非零元素个数
    M->m=m;M->n=n;M->len=t;
    if(!(M->row_head=(OLink*)malloc((m+1)*sizeof(OLink))))//为行，列创建指针，开辟一定数量的结点，加一有一列和一行是空的（？？还能这样？）
    exit(0);
    if(!(M->col_head=(OLink*)malloc((n+1)*sizeof(OLink))))
    exit(0);

    M->row_head[0]=M->col_head[0]=NULL;

    int i,j,e;
    for(scanf(&i,&j,&e);i!=0;scanf(&i,&j,&e)){
        OLNode* p;
        if(!(p=(OLNode*)malloc(sizeof(OLNode))))
        exit(0);
        p->row=i;p->col=j;p->value=e;//生成一个结点，并赋值

        if(M->row_head[i]==NULL){
            M->row_head[i]=p;//找到对应行结点，然后接上一个子结点
        }else if((p->col)<(M->row_head[i]->col)){//如果这一行已经有子结点，则判断列数是否在前，在前则这个位置变成第一个结点
            p->right=M->row_head[i];
            M->row_head[i]=p;
        }
        else{
            OLNode* q;
            for(q=M->row_head[i];q->right&&q->right->col<j;q=q->right);//q->right不为空，并且小，直到找到下一位比j大的位置
            p->right=q->right;q->right=p;
        }
        //列上同理 
        if(M->col_head[i]==NULL){
            M->col_head[i]=p;
        }else if((p->row)<(M->col_head[i]->row)){
            p->down=M->col_head[i];M->col_head[i]=p;
        }
        else{
            OLNode* q;
            for(q=M->col_head[i];q->down&&q->down->row<j;q=q->down);
            p->down=q->down;q->down=p;
        }
    }
}
