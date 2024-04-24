#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100
typedef char DataType;
typedef struct Node{
    DataType data;
    struct Node *LChild;
    struct Node *RChild;
}BiTNode,*BiTree;
typedef struct CSNode
{
    DataType data;
    struct CSNode *FirstChild;
    struct CSNode *NextSibling;
}CSNode,*CSTree;

void Visit(DataType x){//print
    printf("%c ",x);
}
void PreOrder(BiTree root){
    if(root!=NULL){
        Visit(root->data);
        PreOrder(root->LChild);
        PreOrder(root->RChild);
    }
}
void RootFirst(CSTree root){
    if(root!=NULL){
        Visit(root->data);
        RootFirst(root->FirstChild);
        RootFirst(root->NextSibling);
    }else return;
}

void CreateCSTree(CSTree *cst){//创建兄弟树
    (*cst)=(CSTree)malloc(sizeof(CSNode));
    printf("输入结点数据:");
    char c;
    c=getchar();
    (*cst)->data=c;
    printf("是否有孩子兄弟(1/0):");
    int x,y;
    scanf("%1d%1d",&x,&y);
    char a=getchar();//吞换行符
    if(x) CreateCSTree(&((*cst)->FirstChild));
    else (*cst)->FirstChild=NULL;
    if(y) CreateCSTree(&((*cst)->NextSibling));
    else (*cst)->NextSibling=NULL;
}
void CreateCSForest(CSTree csts[],int num){//创建兄弟森林
    char c=getchar();
    for(int i=0;i<num;i++){
        printf(".....树%d:\n",i+1);
        CSTree cst;
        CreateCSTree(&cst);
        csts[i]=cst;
    }
}

void TreeToBitree(CSTree cst,BiTree *bt){//兄弟树转二叉树
    if(cst==NULL) {
        (*bt)=NULL;
        return;
    }
    (*bt)=(BiTree)malloc(sizeof(BiTNode));
    (*bt)->data=cst->data;
    TreeToBitree(cst->FirstChild,&((*bt)->LChild));
    TreeToBitree(cst->NextSibling,&((*bt)->RChild));
}

void ForestToBitree(CSTree csts[],BiTree *bt,int num){//森林转二叉树
    BiTree bts[num];
    for(int i=0;i<num;i++){
        TreeToBitree(csts[i],&(bts[i]));//全部转二叉树
    }
    for(int i=1;i<num;i++){
        bts[i-1]->RChild=bts[i];//二叉树合并
    }
    (*bt)=(BiTree)malloc(sizeof(BiTNode));
    (*bt)=bts[0];
}

void InitBiTree(BiTree *bt){
    (*bt)=NULL;
}
void CreateBiTree(BiTree *bt){
    char ch;
    ch=getchar();
    if(ch=='.') *bt=NULL;
    else{
        *bt=(BiTree)malloc(sizeof(BiTNode));
        (*bt)->data=ch;
        CreateBiTree(&((*bt)->LChild));
        CreateBiTree(&((*bt)->RChild));
    }
}
void BitreeToTree(BiTree bt,CSTree *cst){//二叉树转树
    if(bt!=NULL){
        *cst=(CSTree)malloc(sizeof(CSNode));
        (*cst)->data=bt->data;
        BitreeToTree(bt->LChild,&((*cst)->FirstChild));
        BitreeToTree(bt->RChild,&((*cst)->NextSibling));
    }else (*cst)=NULL;
}
int BitreeToForest(BiTree bt,CSTree csts[MAX]){//二叉树转森林
    int i=0;
    BiTree p=bt;
    do{
        csts[i]=(CSTree)malloc(sizeof(CSNode));
        csts[i]->data=p->data;
        csts[i]->NextSibling=NULL;
        BitreeToTree(p->LChild,&(csts[i++]->FirstChild));
        p=p->RChild;
    }while(p!=NULL);
    return i;
}

int main(){
    //树转二叉树
    // CSTree cst;
    // CreateCSTree(&cst);
    // BiTree bt;
    // TreeToBitree(cst,&bt);
    // PreOrder(bt);

    //森林转二叉树
    // printf("输入创建的树个数:");
    // int num;
    // scanf("%d",&num);
    // CSTree csts[num];
    // CreateCSForest(csts,num);
    // BiTree BT;
    // ForestToBitree(csts,&BT,num);
    // PreOrder(BT);

    //二叉树转森林
    BiTree bt;
    InitBiTree(&bt);
    printf("先序创建二叉树('.'为NULL):");//例如ABD.G...CE.H..F..
    CreateBiTree(&bt);
    CSTree csts[MAX];
    int num=BitreeToForest(bt,csts);
    for(int i=0;i<num;i++){
        printf("树%d:",i);
        RootFirst(csts[i]);
        printf("\n");
    }
}