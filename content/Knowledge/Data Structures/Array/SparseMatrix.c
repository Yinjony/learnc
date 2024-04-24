//稀疏矩阵
//三元组
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#define MAXSIZE 1000

typedef int ElementType;

typedef struct {
    int row,col;//行，列坐标
    ElementType e;
}Triple;//定义三元组

typedef struct{
    Triple data[MAXSIZE+1];//不用data[0]
    int m,n,len;//矩阵行数，列数，非零数
}TSMatrix;

void TransMatrix(ElementType source[][MAXSIZE],ElementType dest[][MAXSIZE],int m,int n){//一般矩阵转置算法
    int i,j;
    for(i=0;i<m;i++){
        for(j=0;j<n;j++){
            dest[j][i]=source[i][j];
        }
    }
}
void TransposeTSMatrix(TSMatrix A,TSMatrix *B){//稀疏矩阵的列序递增转置法
    int i,j,k;
    B->m=A.n;B->n=A.m;B->len=A.len;
    if(B->len>0){
        j=1;
        for(k=1;k<=A.n;k++){//从A数组每一列开始，因为转置后是B数组的第一行
            for(i=1;i<=A.len;i++){
                if(A.data[i].col==k){//直接从非零数里找
                    B->data[j].row=A.data[i].col;
                    B->data[j].col=A.data[i].row;
                    B->data[j].e=A.data[i].e;
                    j++;//B数组多一位
                }
            }
        }
    }
}
void FastTransposeTSMatrix(TSMatrix A,TSMatrix *B){//稀疏矩阵一次定位快速转置算法
    int col,t,p,q;
    int num[MAXSIZE],postion[MAXSIZE];
    B->m=A.n;B->n=A.m;B->len=A.len;
    if(B->len){
        for(col=1;col<=A.n;col++) num[col]=0;//初始化数组

        for(t=1;t<=A.len;t++) num[A.data[t].col]++;//指定列位置数量加一

        postion[1]=1;//位置
        for(col=2;col<=A.n;col++) postion[col]=postion[col-1]+num[col-1];//按列排序，存储在B中的位置

        for(p=1;p<=A.len;p++){
            col=A.data[p].col;q=postion[col];//找到应该存放的B中位置，比如第一行第一个数据在第五列，则接下来在B的第五行位置存第一个数据，如果之后再次遇见这一列的，则往后加

            B->data[q].row=A.data[p].col;//行列互换
            B->data[q].col=A.data[p].row;
            B->data[q].e=A.data[p].e;
            postion[col]++;
        }
    }
}
void Create(TSMatrix *A){
    int m,n;
    printf("输入行列数:");
    scanf("%d,%d",&m,&n);
    int array[m][n];
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            array[i][j]=0;
        }
    }
    int num;
    printf("输入非零数:");
    scanf("%d",&num);

    srand((unsigned)time(NULL));
    for(int i=0;i<num;){
        int x=rand()%m;
        int y=rand()%n;
        if(array[x][y]==0){
            array[x][y]=rand();
            i++;
        }
    }

    A->m=m;A->n=n;A->len=num;
    int t=1;
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            if(array[i][j]!=0){
                A->data[t].e=array[i][j];
                A->data[t].row=i+1;
                A->data[t].col=j+1;
                t++;
            }
        }
    }
}
void Visit(TSMatrix A){
    printf("行号\t列号\t元素值\n");
    for(int i=1;i<=A.len;i++){
        printf("%d\t%d\t%d\n",A.data[i].row,A.data[i].col,A.data[i].e);
    }
}

bool add_matrix(const TSMatrix *pM, const TSMatrix *pN, TSMatrix *pQ){
    if(pM->m!=pN->m||pM->n!=pN->n) return false;
    pQ->m=pM->m;pQ->n=pM->n;pQ->len=0;

    int m=1,n=1;
    while(m<=pM->len&&n<=pN->len){
        if(pM->data[m].row==pN->data[n].row){
            if(pM->data[m].col==pN->data[n].col){//都相等则赋值
                if(pM->data[m].e+pN->data[n].e!=0){
                    pQ->len++;
                    pQ->data[pQ->len].e=pM->data[m].e+pN->data[n].e;
                    pQ->data[pQ->len].row=pM->data[m].row;
                    pQ->data[pQ->len].col=pM->data[m].col;
                    m++;
                    n++;
                }else {
                    m++;
                    n++;
                }
                
            }else if(pM->data[m].col>pN->data[n].col){
                pQ->len++;
                pQ->data[pQ->len].e=pN->data[n].e;
                pQ->data[pQ->len].row=pN->data[n].row;
                pQ->data[pQ->len].col=pN->data[n].col;
                n++;
            }else{
                pQ->len++;
                pQ->data[pQ->len].e=pM->data[m].e;
                pQ->data[pQ->len].row=pM->data[m].row;
                pQ->data[pQ->len].col=pM->data[m].col;
                m++;
            }
        }else if (pM->data[m].row>pN->data[n].row){
                pQ->len++;
                pQ->data[pQ->len].e=pN->data[n].e;
                pQ->data[pQ->len].row=pN->data[n].row;
                pQ->data[pQ->len].col=pN->data[n].col; 
                n++;
        }else{
                pQ->len++;
                pQ->data[pQ->len].e=pM->data[m].e;
                pQ->data[pQ->len].row=pM->data[m].row;
                pQ->data[pQ->len].col=pM->data[m].col;
                m++;
        }
    } 
    while(m<=pM->len){
        pQ->len++;
        pQ->data[pQ->len].e=pM->data[m].e;
        pQ->data[pQ->len].row=pM->data[m].row;
        pQ->data[pQ->len].col=pM->data[m].col;
        m++;
    }
    while(n<=pN->len){
        pQ->len++;
        pQ->data[pQ->len].e=pN->data[n].e;
        pQ->data[pQ->len].row=pN->data[n].row;
        pQ->data[pQ->len].col=pN->data[n].col; 
        n++;
    }
    return true;
}

int main(){
    TSMatrix A,B;
    Create(&A);
    Visit(A);
    // TransposeTSMatrix(A,&B);
    // FastTransposeTSMatrix(A,&B);
    // Visit(B);
    Create(&B);
    Visit(B);
    
    TSMatrix C;
    add_matrix(&A,&B,&C);
    Visit(C);
}