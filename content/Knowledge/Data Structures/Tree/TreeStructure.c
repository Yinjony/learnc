#include <stdio.h>//数组形式
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100
typedef char DataType;
void Visit(DataType x){//print
    printf("%C ",x);
}
//树的双亲表示法
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
void CreateParentTree(ParentTree *pt){//创建双亲树，遍历易得
    char c;
    printf("请输入数据(先data后parent):");
    int i=0;
    while((c=getchar())!='\n'){
        int d;
        printf("输入双亲位置:");
        scanf("%d",&d);
        pt->tree[i].data=c;
        pt->tree[i].parent=d;
        char x=getchar();
        printf("请输入数据(先data后parent):");
        i++;
    }
    pt->nodenum=i;
}

//树的孩子表示法
typedef struct ChildNode
{
    int Child;//该孩子结点在表中的位置
    struct ChildNode *next;//指向下一个孩子结点的指针
}ChildNode;
typedef struct
{
    DataType data;
    ChildNode *FirstChild;//指向孩子链表的头指针
}DataNode;
typedef struct
{
    DataNode nodes[MAX];
    int root;//根结点在表中的位置
    int num;//该树结点个数
}ChildTree;
void CreateChildTree(ChildTree *ct){//创建孩子树，遍历易得
    ct->root=0;
    int i=0;
    char c;
    printf("请输入结点数据:");
    while((c=getchar())!='\n'){
        ct->nodes[i].data=c;
        printf("是否有孩子结点(1/0):");
        int x;
        scanf("%d",&x);
        if(x){
            ChildNode *p=(ChildNode*)malloc(sizeof(ChildNode));
            printf("输入孩子结点位置:");
            int d;
            scanf("%d",&d);
            p->Child=d;
            ct->nodes[i].FirstChild=p;
            printf("是否还有孩子结点(1/0):");
            scanf("%d",&x);
            while(x){
                ChildNode *q=(ChildNode*)malloc(sizeof(ChildNode));
                printf("输入孩子结点位置:");
                scanf("%d",&d);
                q->Child=d;
                p->next=q;
                p=p->next;
                printf("是否还有孩子结点(1/0):");
                scanf("%d",&x);
            }
            p->next=NULL;
        }else ct->nodes[i].FirstChild=NULL;
        char a=getchar();
        printf("请输入结点数据:");
        i++;
    }
    ct->num=i;
}

//树的孩子兄弟表示法
typedef struct CSNode
{
    DataType data;
    struct CSNode *FirstChild;//指向孩子
    struct CSNode *NextSibling;//指向兄弟
}CSNode,*CSTree;
void CreateCSTree(CSTree *cst){//创建孩子兄弟树
    (*cst)=(CSTree)malloc(sizeof(CSNode));
    printf("输入结点数据:");
    char c;
    c=getchar();
    (*cst)->data=c;
    printf("是否有孩子兄弟(1/0):");//输入两个值
    int x,y;
    scanf("%1d%1d",&x,&y);
    char a=getchar();//吞换行符
    if(x) CreateCSTree(&((*cst)->FirstChild));
    else (*cst)->FirstChild=NULL;
    if(y) CreateCSTree(&((*cst)->NextSibling));
    else (*cst)->NextSibling=NULL;
}
//用孩子兄弟树，先根遍历，向左下遍历，遍历孩子，在对应的孩子底遍历同层兄弟
void RootFirst(CSTree root){//法一
    if(root!=NULL){
        Visit(root->data);
        RootFirst(root->FirstChild);
        RootFirst(root->NextSibling);
    }else return;
}
/*void RootFirst1(CSTree root){//法二
    CSTree p;
    if(root!=NULL){
        Visit(root->data);
        p=root->FirstChild;
        while(p!=NULL){
            RootFirst1(p);//先遍历孩子，再遍历兄弟
            p=p->NextSibling;
        }
    }else return;
}*/
void RootLast(CSTree root){
    if(root!=NULL){
        RootLast(root->FirstChild);
        RootLast(root->NextSibling);
        Visit(root->data);
    }else return;
}
void RootMedi(CSTree root){
    if(root!=NULL){
        RootMedi(root->FirstChild);
        Visit(root->data);
        RootMedi(root->NextSibling);
    }else return;
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


int main(){//测试
    //双亲
    // ParentTree pt;
    // CreateParentTree(&pt);
    // printf("%d",pt.nodenum);

    //孩子 
    // ChildTree ct;
    // CreateChildTree(&ct);
    // printf("%d",ct.num);

    //孩子兄弟
    // CSTree cst;
    // CreateCSTree(&cst);
    // RootFirst(cst);
    // printf("\n");
    // RootLast(cst);
    // printf("\n");
    // RootMedi(cst);

    //孩子兄弟森林，测试遍历
    printf("输入创建的树个数:");
    int num;
    scanf("%d",&num);
    CSTree csts[num];
    CreateCSForest(csts,num);
    printf("\n先序遍历:");
    for(int i=0;i<num;i++){
        RootFirst(csts[i]);
    }
    printf("\n中序遍历:");
    for(int i=0;i<num;i++){
        RootMedi(csts[i]);
    }
    printf("\n后序遍历:");
    for(int i=0;i<num;i++){
        RootLast(csts[i]);
    }
}