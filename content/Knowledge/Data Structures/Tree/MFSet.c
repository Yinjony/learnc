#include <stdio.h>//并查集就是双亲型树的森林状态
#include <stdlib.h>
#include <stdbool.h>
#define MAX 100
typedef char DataType;
typedef struct TNode
{
    DataType data;
    int parent;
}TNode;
typedef struct 
{
    TNode tree[MAX];
    int nodenum;
}ParentTree;

typedef struct{
    DataType elem[MAX];
    int last;
}SeqList;
typedef ParentTree ParentForest;
typedef ParentForest MFSet;

void Initial(MFSet *SS,SeqList *S){//初始化，在并查集中创建各个根结点
    int i;
    SS->nodenum=S->last+1;
    for(i=0;i<SS->nodenum;i++){
        SS->tree[i].data=S->elem[i];
        SS->tree[i].parent=-1;
    }
}
void Create(MFSet *SS){
    printf("目前双亲结点个数:%d\n",SS->nodenum);
    char data;
    int parent;
    do{
        char c=getchar();
        printf("输入结点数据及其双亲位置:");
        scanf("%c%d",&data,&parent);
        if(parent==-1) break;
        SS->tree[SS->nodenum].data=data;
        SS->tree[SS->nodenum++].parent=parent;
    }while(1);
}

int Locate(MFSet *SS,DataType x){//定位x在并查集中的位置下标
    for(int i=0;i<SS->nodenum;i++){
        if(SS->tree[i].data==x){
            return i;
        }
    }
    return -1;//找不到则返回-1
}
int Find_1(MFSet *SS,DataType x){//查找元素
    int pos=Locate(SS,x);
    if(pos<0) return -1;
    int i=pos;
    while(SS->tree[i].parent>0) i=SS->tree[i].parent;//回溯，找到根结点
    return i;
}
int Find_2(MFSet *SS,DataType x){//查找元素并把其所有双亲结点变为根结点的子结点
    int pos=Locate(SS,x);
    if(pos<0) return -1;
    int i=pos;
    while(SS->tree[i].parent>0) i=SS->tree[i].parent;
    int root=i;
    i=pos;
    while(i!=root){//变为子结点的操作
        int temp=SS->tree[i].parent;
        SS->tree[i].parent=root;
        i=temp;
    }
    return root;
}

bool Merge_1(MFSet *SS,int root1,int root2){//合并并查集
    if(root1<0||root1>SS->nodenum-1) return false;
    if(root2<0||root2>SS->nodenum-1) return false;
    SS->tree[root2].parent=root1;//简单合并
    return true;
}
bool Merge_2(MFSet *SS,int root1,int root2){
    if(root1<0||root1>SS->nodenum-1) return false;
    if(root2<0||root2>SS->nodenum-1) return false;
    if(SS->tree[root1].parent<SS->tree[root2].parent){//root1个数多这里需要是双亲树结构，一棵一棵树连续排列那种，本次使用的只是根结点排列的那种，结构不一样
        SS->tree[root2].parent=root1;
        SS->tree[root1].parent+=SS->tree[root2].parent;
    }else{
        SS->tree[root1].parent=root2;
        SS->tree[root2].parent+=SS->tree[root1].parent;
    }
    return true;
}

int main(){
    MFSet SS;
    SeqList S;
    printf("输入根结点数目:");
    int num;
    scanf("%d",&num);
    S.last=num-1;
    for(int i=0;i<num;i++){
        char c=getchar();
        printf("输入根结点数据:");
        char data;
        scanf("%c",&data);
        S.elem[i]=data;
    }
    Initial(&SS,&S);
    Create(&SS);
    printf("G元素的根结点:%c",SS.tree[Find_1(&SS,'G')]);
    Merge_1(&SS,0,1);
}