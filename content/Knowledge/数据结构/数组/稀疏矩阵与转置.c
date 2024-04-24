//稀疏矩阵
//三元组
#define MAXSIZE 1000

typedef int ElementType;

typedef struct {
    int row,col;//行，列坐标
    ElementType e;
}Triple;

typedef struct{
    Triple data[MAXSIZE-1];
    int m,n,len;//矩阵行数，列数，非零数
}TSMatrix;

int m,n;

void TransMatrix(ElementType source[m][n],ElementType dest[n][m]){//一般矩阵转置算法
    int i,j;
    for(i=0;i<m;i++){
        for(j=0;j<n;j++){
            dest[j][i]=source[i][j];
        }
    }
}
void TransposeTSMatrix(TSMatrix A,TSMatrix*B){//稀疏矩阵的列序递增转置法
    int i,j,k;
    B->m=A.n;B->n=A.m;B->len=A.len;
    if(B->len>0){
        j=1;
        for(k=1;k<=A.n;k++){
            for(i=1;i<=A.len;i++){
                if(A.data[i].col==k){
                    B->data[j].row=A.data[i].col;
                    B->data[j].col=A.data[i].row;
                    B->data[j].e=A.data[i].e;
                    j++;
                }
            }
        }
    }
}
void FastTransposeTSMatrix(TSMatrix A,TSMatrix *B){
    int col,t,p,q;
    int num[MAXSIZE],postion[MAXSIZE];
    B->m=A.n;B->n=A.m;B->len=A.len;
    if(B->len){
        for(col=1;col<=A.n;col++)num[col]=0;
        for(t=1;t<=A.len;t++)num[A.data[t].col]++;//数量加一
        postion[1]=1;//位置
        for(col=2;col<=A.n;col++)postion[col]=postion[col-1]+num[col-1];//按列排序，存储B中应该存放的位置
        for(p=1;p<A.len;p++){
            col=A.data[p].col;q=postion[col];//找到应该存放的B中位置
            B->data[q].row=A.data[p].col;//行列互换
            B->data[q].col=A.data[p].row;
            B->data[q].e=A.data[p].e;
            postion[col]++;
        }
    }
}