#include <stdio.h>
#include <stdlib.h>
#define TREE 0
#define PRE 1
#define POST 1
typedef char DataType;
typedef struct Node{
    DataType data;
    int Ltag;//0左子树，1前驱结点
    int Rtag;//0右子树，1后继结点
    struct Node *LChild;
    struct Node *RChild;
}BiTNode,*BiTree;
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
        if((*bt)->LChild!=NULL) (*bt)->Ltag=TREE;
        CreateBiTree(&((*bt)->RChild));
        if((*bt)->RChild!=NULL) (*bt)->Rtag=TREE;
    }
}
void Visit(DataType x){//print
    printf("%c ",x);
}

//中序线索树
BiTNode *pre=NULL;
BiTNode *next=NULL;
void Inthread(BiTree root){//对已有的二叉树线索化,pre指向刚访问过的结点，初始值为NULL
    if(root!=NULL){
        Inthread(root->LChild);//线索化左子树
        if(root->LChild==NULL){//左子树为空，指向前驱
            root->LChild=pre;
            root->Ltag=PRE;
        }
        if(pre!=NULL&&pre->RChild==NULL){//当前驱右子树为空，让前驱指向后继
            pre->RChild=root;
            pre->Rtag=POST;
        }
        pre=root;
        Inthread(root->RChild);//线索化右子树
    }else return;
}
BiTNode *InPre(BiTNode *p){//中序线索树寻找前驱结点
    if(p->Ltag==PRE) pre=p->LChild;//有前驱
    else {//无前驱
        BiTree q;
        for(q=p->LChild;q->Rtag==TREE;q=q->RChild);//在p的左子树中查找最右下端结点
        pre=q;
    }
    return pre;
}
BiTNode *InNext(BiTNode *p){//中序线索树寻找后继结点
    if(p->RChild==NULL) return NULL;
    if(p->Rtag==POST) next=p->RChild;//有后继
    else{
        BiTree q;
        for(q=p->RChild;q->Ltag==TREE;q=q->LChild);//在p的右子树中查找最左下端结点
        next=q;
    }
    return next;
}
BiTNode *InFirst(BiTree Bt){//中序线索树里求中序遍历的第一个结点
    BiTNode *p=Bt;
    if (!p) return NULL;
    while (p->Ltag==TREE) p=p->LChild;//找到最左结点
    return p;
}
void TInOrder(BiTree Bt){//遍历中序线索树
    BiTNode *p;
    p=InFirst(Bt);
    while(p){
        Visit(p->data);
        p=InNext(p);//遍历后继结点
    }
}

//先序线索树
void Prethread(BiTree root){
    if(root!=NULL){
        Prethread(root->RChild);//线索化右子树，直到遇到末尾
        Prethread(root->LChild);//然后线索化左子树
        if(root->RChild==NULL){//root的后继
            root->RChild=next;
            root->Rtag=POST;
        }        
        if(next!=NULL&&next->LChild==NULL){//当后继左子树为空，后继的前驱为root
            next->LChild=root;
            next->Ltag=PRE;
        }
        next=root;
    }else return;
}
// BiTNode *PrePre(BiTNode *p)找前驱比较麻烦且鸡肋
BiTNode *PreNext(BiTNode *p){//找后继
    if(p->Ltag==TREE) next=p->LChild;//左子树便是后继
    else next=p->RChild;//若左子树是前驱，那么右子树便是后继，不管是不是线索
    return next;
}
BiTNode *PreFirst(BiTree Bt){//找第一个
    BiTNode *p=Bt;
    if(!p) return NULL;
    return p;
}
void TPreOrder(BiTree Bt){//遍历
    BiTNode *p;
    p=PreFirst(Bt);
    while(p){
        Visit(p->data);
        p=PreNext(p);
    }
}

//后序线索树
void Postthread(BiTree root){//与先序不同，先线索化左子树再紧接着线索化右子树
    if(root!=NULL){
        Postthread(root->LChild);
        Postthread(root->RChild);
        if(root->LChild==NULL){
            root->LChild=pre;
            root->Ltag=PRE;
        }
        if(pre!=NULL&&pre->RChild==NULL){
            pre->RChild=root;
            pre->Rtag=POST;
        }
        pre=root;
    }else return;
}
BiTNode *PostPre(BiTNode *p){
    if(p->Rtag==TREE) pre=p->RChild;//右子树便是前驱
    else pre=p->LChild;//没有右子树，左子树不管是不是线索都是前驱
    return pre;
}
// BiTNode *PostNext(BiTNode *p)找后继比较麻烦且鸡肋
BiTNode *PostFirst(BiTree Bt){//找到第一个结点
    BiTNode *p;
    p=Bt;
    if(!p) return NULL;
    while (p->Ltag==TREE) p=p->LChild;//找到左子树末端
    while (p->Rtag==TREE) p=p->RChild;//再找是否有右子树，找末端
    return p;
}
BiTNode *PostLast(BiTree Bt){//找到最后一个结点
    BiTNode *p=Bt;
    if(!p) return NULL;
    return p;
}
void TPostOrder(BiTree Bt){//倒序遍历后序线索树
    BiTNode *p;
    p=PostLast(Bt);
    while(p){
        Visit(p->data);
        p=PostPre(p);
    }
}

int main(){//测试
    BiTree bt;
    InitBiTree(&bt);
    printf("先序创建二叉树('.'为NULL):");//例如ABD.G...CE.H..F..
    CreateBiTree(&bt);
    printf("选择一种线索树\n0:先序\t1:中序\t2:后序\n");
    int x;
    scanf("%d",&x);
    switch(x){
        case 0:{
            Prethread(bt);
            printf("遍历:");
            TPreOrder(bt);
            break;
        }
        case 1:{
            Inthread(bt);
            printf("遍历:");
            TInOrder(bt);
            BiTNode *p=InPre(bt->RChild->RChild);
            printf("\nF的前驱:");
            Visit(p->data);
            break;
        }
        case 2:{
            Postthread(bt);
            printf("倒序遍历:");
            TPostOrder(bt);
            BiTNode *p=PostFirst(bt);
            printf("\n第一个结点:");
            Visit(p->data);
            break;
        }
    }
}

