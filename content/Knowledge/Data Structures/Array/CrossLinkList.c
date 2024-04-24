#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
typedef int ElementType;

typedef struct OLNode{//行列链表
    int row,col;
    ElementType value;
    struct OLNode *right,*down;
}OLNode,*OLink;

typedef struct{
    OLink *row_head,*col_head;//行列的头指针（感觉是造一列数组）
    int m,n,len;//行，列，非零元素的个数
}CrossList;

void CreateCrossList(CrossList *M){//创建
    int m,n,t;
    printf("输入行列数和非零元素个数:");
    scanf("%d,%d,%d",&m,&n,&t);//输入行数列数和非零元素个数
    M->m=m;M->n=n;M->len=t;
    if(!(M->row_head=(OLink*)malloc((m+1)*sizeof(OLink))))//为行，列创建指针，开辟一定数量的结点，加一是为了有一列和一行是空的（？？还能这样？）
    exit(0);
    if(!(M->col_head=(OLink*)malloc((n+1)*sizeof(OLink))))//这些结点都是头结点
    exit(0);

    for(int i=0;i<m+1;i++) M->row_head[i]=NULL;
    for(int i=0;i<n+1;i++) M->col_head[i]=NULL;

    srand((unsigned)time(NULL));
    int i,j;//输入元素
    ElementType e;
    // printf("输入元素行列数及元:");
    // scanf("%d,%d,%d",&i,&j,&e);
    int num=0;
    while(num<M->len){
        OLNode* p;
        if(!(p=(OLNode*)malloc(sizeof(OLNode))))
        exit(0);
        i=rand()%M->m+1;j=rand()%M->n+1;e=rand();
        p->row=i;p->col=j;p->value=e;//生成一个结点，并赋值

        if(M->row_head[i]==NULL){
            M->row_head[i]=p;//找到对应行头结点（所以头结点不为空）
            M->row_head[i]->right=NULL;
        }else if((p->col)<(M->row_head[i]->col)){//如果这一行已经有子结点，则判断列数是否在前，在前则这个位置变成第一个结点
            p->right=M->row_head[i];
            M->row_head[i]=p;
        }
        else{
            OLNode* q;
            for(q=M->row_head[i];q->right!=NULL&&q->right->col<j;q=q->right);//q->right不为空，并且小，直到找到下一位比j大的位置
            if(q->right!=NULL&&q->right->col==j) continue;//随机数生成懒狗
            p->right=q->right;q->right=p;
        }
        //列同理 
        if(M->col_head[j]==NULL){
            M->col_head[j]=p;
            M->col_head[j]->down=NULL;
        }else if((p->row)<(M->col_head[j]->row)){
            p->down=M->col_head[j];M->col_head[j]=p;
        }
        else{
            OLNode* q;
            for(q=M->col_head[j];q->down!=NULL&&q->down->row<i;q=q->down);
            if(q->down!=NULL&&q->down->row==i) continue;
            p->down=q->down;q->down=p;
        }
        // printf("输入元素行列数及元:");
        // scanf("%d,%d,%d",&i,&j,&e);
        num++;
    }
}

void Visit(CrossList M){
    printf("行号\t列号\t元素值\n");
    for(int i=1;i<=M.m;i++){//行输出
        for(OLNode *x=M.row_head[i];x!=NULL;x=x->right){
            printf("%d\t%d\t%d\n",x->row,x->col,x->value);
        }
    }
    // for(int i=1;i<=M.n;i++){//列输出
    //     for(OLNode *x=M.col_head[i];x!=NULL;x=x->down){
    //         printf("%d\t%d\t%d\n",x->row,x->col,x->value);
    //     }
    // }
}

int init_cross_list(CrossList *L, const ElementType *A, int m,int n){//A为一维数组，赋值到十字链表里
    if(!(L->row_head=(OLink*)malloc((m+1)*sizeof(OLink)))) return 0;//初始化
    if(!(L->col_head=(OLink*)malloc((n+1)*sizeof(OLink)))) return 0;

    for(int i=0;i<m+1;i++) L->row_head[i]=NULL;
    for(int i=0;i<n+1;i++) L->col_head[i]=NULL;//设空指针

    L->m=m;L->n=n;L->len=0;//赋值

    OLNode *r,*c;
    for(int i=0;i<m*n;i++){
        if(A[i]!=0) L->len++;
        else continue;//非零与为零

        OLNode* p;
        if(!(p=(OLNode*)malloc(sizeof(OLNode)))) return 0;//设指针
        
        p->row=i/n+1;p->col=i%n+1;p->value=A[i];//赋值

        if(L->row_head[p->row]==NULL){//行头指针
            L->row_head[p->row]=p;
            L->row_head[p->row]->right=NULL;
            r=L->row_head[p->row];
        }else{
            r->right=p;
            r=r->right;
            r->right=NULL;
        }

        if(L->col_head[p->col]==NULL){
            L->col_head[p->col]=p;
            L->col_head[p->col]->down=NULL;
        }else{
            for(c=L->col_head[p->col];c->down!=NULL;c=c->down);
            c->down=p;
            c=c->down;
            c->down=NULL;
        }
    }
    return L->len;
}

int del_cross_list(CrossList *L, ElementType k){//删除值为k的元
    int num=0;
    for(int i=1;i<=L->m;i++){//行处理并计数
        for(OLNode *x=L->row_head[i];x!=NULL;){
            if(x->value==k){
                x=x->right;
                num++;
            }else{
                if(x->right!=NULL&&x->right->value==k){
                    x->right=x->right->right;
                    num++;
                }else{
                    x=x->right;
                }
            }
        }   
    }

    for(int i=1;i<=L->n;i++){//列处理
        for(OLNode *x=L->col_head[i];x!=NULL;){
            if(x->value==k){
                OLNode *p=L->col_head[i];
                x=x->down;
                free(p);
            }else{
                if(x->down!=NULL&&x->down->value==k){
                    OLNode *p=x->down;
                    x->down=x->down->down;
                    free(p);
                }else{
                    x=x->down;
                }
            }
        }
    }
    L->len-=num;
    return num;
}
int main(){//测试
    // CrossList M;
    // CreateCrossList(&M);
    // Visit(M);
    
    // icoding部分
    CrossList L;

    // printf("输入行列数:");
    // int m,n;
    // scanf("%d,%d",&m,&n);
    // int A[m*n];
    // for(int i=0;i<m*n;i++) A[i]=0;
    // srand((unsigned)time(NULL));
    // int num=rand()%(m*n)+1;
    // for(int i=0;i<num;){
    //     int p=rand()%(m*n);
    //     if(A[p]==0){
    //         A[p]=rand()+1;
    //         i++;
    //     }
    // }

    int m=3,n=4;
    int A[]={0,2,3,9,1,2,0,3,4,0,0,0};

    printf("矩阵:\n");
    for(int i=0;i<m*n;i++){
        if(i%n==0&&i!=0) printf("\n");
        printf("%d\t",A[i]);
    }
    printf("\n");
    printf("非零数:%d\n",init_cross_list(&L,A,m,n));
    Visit(L); 
    printf("删除个数:%d\n", del_cross_list(&L,3));
    Visit(L);
}