#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define N 20//叶子数
#define M 2*N-1//结点数
typedef struct{//静态三叉链表哈夫曼树
    int weight;
    int parent;
    int LChild;
    int RChild;
}HTNode,HuffmanTree[M+1];//0号元不用
typedef char *HuffmanCode[N+1];//存放哈夫曼编码串的头指针数组

void select(HuffmanTree ht,int n,int *s1,int *s2){//挑选最小两个值
    int x=0;//判断是否是第一个有效值
    int min1;
    int min2;
    (*s1)=0;
    (*s2)=0;
    for(int i=1;i<=n;i++){
        if(ht[i].parent!=0) continue;
        if(x==0) {
            min1=ht[i].weight;
            (*s1)=i;
            x=1;
        }
        if(min1>ht[i].weight){
            min1=ht[i].weight;
            (*s1)=i;
        }
    }
    x=0;
    for(int i=1;i<=n;i++){
        if(ht[i].parent!=0||i==(*s1)) continue;
        if(x==0) {
            min2=ht[i].weight;
            (*s2)=i;
            x=1;
        }
        if(min2>ht[i].weight){
            min2=ht[i].weight;
            (*s2)=i;
        }
    }

    if(min1==min2){
        if((*s1)<(*s2)){
            int t;
            t=(*s1);
            (*s1)=(*s2);
            (*s2)=t;
        }
    }
}
void CrtHuffmanTree(HuffmanTree ht,int w[],int n){//创建哈夫曼树
    for(int i=1;i<=n;i++){//1-n号单元存放叶子结点
        ht[i].weight=w[i-1];
        ht[i].parent=0;
        ht[i].LChild=0;
        ht[i].RChild=0;
    }
    int m=2*n-1;
    for(int i=n+1;i<=m;i++){//之后的单元存放非叶子结点
        ht[i].weight=0;
        ht[i].parent=0;
        ht[i].LChild=0;
        ht[i].RChild=0;
    }
    for(int i=n+1;i<=m;i++){//开始初始化
        int s1,s2;
        select(ht,i-1,&s1,&s2);//找出权值最小的，且parent=0的两个结点，赋给s1,s2
        ht[i].weight=ht[s1].weight+ht[s2].weight;
        ht[s1].parent=i;ht[s2].parent=i;
        ht[i].LChild=s1;ht[i].RChild=s2;
    }
}

void CrtHuffmanCode(HuffmanTree ht,HuffmanCode hc,int n){
    char *cd;
    cd=(char*)malloc(n*sizeof(char));//分配所求当前编码的工作空间
    cd[n-1]='\0';//首先存放编码结束符
    for(int i=1;i<=n;i++){//求n个叶子结点所对应编码
        int start=n-1;//起始指针
        int c=i;int p=ht[i].parent;//找双亲结点
        while(p!=0){
            start--;
            if(ht[p].LChild==c) cd[start]='1';//左1右0
            else cd[start]='0';
            c=p;p=ht[p].parent;//逆流而上
        }
        hc[i]=(char*)malloc((n-start)*sizeof(char));//多一个位子放'\0'
        strcpy(hc[i],&cd[start]);
    }
    free(cd);
}
void VisitCode(HuffmanCode hc,int n){
    for(int i=1;i<=n;i++){
        printf("%s\n",hc[i]);
    }
}
int main(){
    HuffmanTree ht;
    int n;
    printf("输入叶子结点个数:");
    scanf("%d",&n);
    int w[n];
    printf("输入权值:");
    for(int i=0;i<n;i++){
        scanf("%d",&(w[i]));
    }
    CrtHuffmanTree(ht,w,n);

    HuffmanCode hc;
    CrtHuffmanCode(ht,hc,n);
    VisitCode(hc,n);
}