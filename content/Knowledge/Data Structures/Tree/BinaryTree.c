#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef char DataType;
typedef struct Node{
    DataType data;
    struct Node *LChild;
    struct Node *RChild;
}BiTNode,*BiTree;
int depth=0;

/*遍历口诀
先序遍历： 先根 再左 再右

中序遍历： 先左 再根 再右

后序遍历： 先左 再右 再根*/ 

void InitBiTree(BiTree *bt){//初始化为空二叉树
    (*bt)=NULL;
}

void CreateBiTree(BiTree *bt){//先序遍历创建二叉链表，鉴定为中序后序创建十分鸡肋
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

bool Empty(BiTree bt){//判空
    if(bt==NULL) return true;
    else return false;
}

void Visit(DataType x){//访问结点
    printf("%c ",x);
}

void PreOrder(BiTree root){//先序遍历DLR
    if(root!=NULL){
        // if(root->LChild==NULL&&root->RChild==NULL) Visit(root->data);//先序遍历叶子结点
        Visit(root->data);//先序访问根结点，D，打印所有结点
        PreOrder(root->LChild);//遍历左子树，L
        PreOrder(root->RChild);//遍历右子树，R
    }
}
void InOrder(BiTree root){//中序遍历LDR
    if(root!=NULL){
        InOrder(root->LChild);//遍历左子树，L
        Visit(root->data);//访问根结点，D
        InOrder(root->RChild);//遍历右子树，R
    }
}
void PostOrder(BiTree root){//后序遍历LRD
    if(root!=NULL){
        PostOrder(root->LChild);//遍历左子树，L
        PostOrder(root->RChild);//遍历右子树，R
        Visit(root->data);//访问根结点，D
    }
}

void PrintTree(BiTree bt,int nLayer){//按横向树显示二叉树
    if(bt==NULL) return;
    PrintTree(bt->RChild,nLayer+1);//先右后左
    for(int i=0;i<nLayer;i++) printf(" ");//打出空格，有几层几个空格
    Visit(bt->data);
    printf("\n");
    PrintTree(bt->LChild,nLayer+1);
}

int Leaf(BiTree root){//后序输出二叉树叶子数，鉴定为中序，先序十分鸡肋
// 递归法
    if(root!=NULL){
        if(root->LChild==NULL&&root->RChild==NULL)
            return 1;
        else 
            return Leaf(root->LChild)+Leaf(root->RChild);
    }else return 0;
// 全局变量加法
//  if(root!=NULL){
//  Leaf(root->LChild);
//  Leaf(root->RChild);
//  if(root->LChild==NULL&&root->RChild==NULL)
//      LeafCount++;//全局变量
}

int PostTreeDepth(BiTree bt){//求二叉树高度，分沿法，每次两边遍历一遍
    int hl,hr,max;
    if(bt!=NULL){
        hl=PostTreeDepth(bt->LChild);//遍历左树
        hr=PostTreeDepth(bt->RChild);//遍历右树
        max=hl>hr?hl:hr;//从末尾开始累加
        return max+1;//返回值
    }
    else return 0;
}

void PreTreeDepth(BiTree bt,int h){//求二叉树高度，先序遍历，h初值为1
    if(bt!=NULL){
        if(h>depth) depth=h;//鉴定为，中序后序都可以，只是把此行换个位置的事
        PreTreeDepth(bt->LChild,h+1);//每下一层，h加一
        PreTreeDepth(bt->RChild,h+1);
    }
}

BiTNode* Root(BiTree root){//返回根节点
    if(root==NULL) return NULL;
    else return root;
}

BiTNode* Parent(BiTree bt,BiTNode* x){//寻找x结点的双亲结点
    BiTNode *parent;

    if(bt==NULL) return NULL;

    if(bt->LChild==x) return bt;
    else if(bt->RChild==x) return bt;
    
    parent=Parent(bt->LChild,x);
    if(parent!=NULL) return parent;
    parent=Parent(bt->RChild,x);
    if(parent!=NULL) return parent;

    return NULL;
    
}

BiTNode* LeftChild(BiTree bt,BiTNode* x){//求x的左孩子，如果无左孩子或者x不在二叉树内，返回NUll；找右孩子同理
    BiTNode* left;
    if(bt==NULL) return NULL;

    if(bt==x) return bt->LChild;

    left=LeftChild(bt->LChild,x);
    if(left!=NULL) return left;
    left=LeftChild(bt->RChild,x);
    if(left!=NULL) return left;
    
    return NULL;
}

bool IsLike(BiTree t1,BiTree t2){//判断两个二叉树是否相似
    int like1,like2;
    if(t1==NULL&&t2==NULL) return true;
    else if (t1==NULL||t2==NULL) return false;
    else{
        like1=IsLike(t1->LChild,t2->LChild);//左右子树分别进行
        like2=IsLike(t1->RChild,t2->RChild);
        return(like1&&like2);//最后进行交运算
    }
}
#define Stack_Size 50
bool Path(BiTree root,BiTNode *r){//从二叉树根节点找到r结点并把路径输出
    BiTNode *p,*q;
    int i,top=0;
    BiTree s[Stack_Size];
    q=NULL;
    p=root;
    while(p!=NULL||top!=0){
        while(p!=NULL){
            top++;
            if(top>=Stack_Size) return false;//栈溢出
            s[top]=p;
            if(p==r){
                for(i=1;i<=top;i++){
                    printf("%c ",s[i]->data);
                }
                return true;
            }
            p=p->LChild;//遍历左子树，从左子树到右子树进行查找
        }
        if(top>0){
            p=s[top];
            if(p->RChild==NULL||p->RChild==q){//为空的时候是到叶结点，为q的时候是访问过的右结点
                if(p!=r){//如果并不是，那么就出栈，然后p置空下一轮直接就进行判断，q则保存这个遍历过的结点
                    q=p;
                    top--;
                    p=NULL;
                }
            }else p=p->RChild;//向右转，最终达到遍历到目标路径
        }
    }
    return false;
}

//利用队列进行层次遍历二叉树
typedef struct node{
    BiTNode *data;
    struct node *next;
}Node;
typedef struct 
{
    Node *front;
    Node *rear;
}Queue;
bool InitQueue(Queue *Q){
    Q->front=(Node*)malloc(sizeof(Node));
    if(Q->front!=NULL){
        Q->rear=Q->front;
        Q->front->next=NULL;
        return true;
    }
    else return false;
}
bool EnterQueue(Queue *Q,BiTNode *x){
    Node *newp;
    newp=(Node*)malloc(sizeof(Node));
    if(newp!=NULL){
        newp->data=x;
        newp->next=NULL;
        Q->rear->next=newp;//插入到尾结点
        Q->rear=newp;
        return true;
    }else return false;
}
bool DeleteQueue(Queue *Q,BiTNode **x){
    Node *p;
    if(Q->front==Q->rear) 
        return false;
    
    p=Q->front->next;
    Q->front->next=p->next;//第一个元素出列
    if(Q->rear==p){//如果p就是最后一个结点
        Q->rear=Q->front;
    }
    (*x)=p->data;
    free(p);
    return true;
}
bool LayerOrder(BiTree bt){
    Queue Q;
    BiTNode *p;
    InitQueue(&Q);
    if(bt==NULL) return false;
    EnterQueue(&Q,bt);//第一层进
    while(!(Q.front==Q.rear)){
        DeleteQueue(&Q,&p);//出队列
        Visit(p->data);
        if(p->LChild) EnterQueue(&Q,p->LChild);//每次运行到这里进行一波左右入队，然后就从左往右遍历某层，顺便把其左右结点
        if(p->RChild) EnterQueue(&Q,p->RChild);
    }
    return true;
}

void Clear(BiTree *bt){//将二叉树置空
    (*bt)=NULL;
}

void DestoryBiTree(BiTree root){//销毁二叉树
    if(root!=NULL){//先序销毁
        DestoryBiTree(root->LChild);
        DestoryBiTree(root->RChild);
        free(root);
    }
    // if(root!=NULL){//后序销毁
    //     DestoryBiTree(root->RChild);
    //     DestoryBiTree(root->LChild);
    //     free(root);
    // }
}

int main(){
    BiTree bt;
    InitBiTree(&bt);
    printf("先序创建二叉树('.'为NULL):");//例如ABD.G...CE.H..F..
    CreateBiTree(&bt);
    // if(Empty(bt)) printf("二叉树为空\n");
    // else printf("二叉树不为空\n");
    // printf("先序遍历:");
    // PreOrder(bt);
    // printf("\n中序遍历:");
    // InOrder(bt);
    printf("\n后序遍历:");
    PostOrder(bt);
    // printf("\n二叉树叶子数:%d",Leaf(bt));
    // printf("\n二叉树高度(分沿法):%d",PostTreeDepth(bt));
    // int h=1;
    // PreTreeDepth(bt,h);
    // printf("\n二叉树高度(先序遍历):%d\n",depth);
    // int nLayer=0;
    // PrintTree(bt,nLayer);

    // if(Root(bt)) printf("查找根结点成功! %c\n",Root(bt)->data);
    // else printf("查找根结点失败\n");

    // if(Parent(bt,bt->RChild->LChild->RChild)) printf("查找双亲结点成功! %c\n",Parent(bt,bt->RChild->LChild->RChild)->data);
    // else printf("查找根结点失败\n");

    // if(LeftChild(bt,bt->RChild)) printf("查找左孩子结点成功! %c\n",LeftChild(bt,bt->RChild)->data);
    // else printf("查找左孩子结点失败\n"); 

    // printf("层次遍历二叉树:");
    // LayerOrder(bt);
    // BiTNode *p=bt->RChild->LChild->RChild;
    // printf("\n路径:");
    // Path(bt,p);

    // char c=getchar();
    // BiTree btx;
    // InitBiTree(&btx);
    // printf("\n先序创建二叉树('.'为NULL):");//例如ABD.G...CE.H..F..
    // CreateBiTree(&btx);
    // if(IsLike(bt,btx)) printf("相似");
    // else printf("不相似");
}