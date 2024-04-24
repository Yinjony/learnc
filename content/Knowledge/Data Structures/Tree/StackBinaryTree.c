#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef char DataType;
typedef struct Node{
    DataType data;
    struct Node *LChild;
    struct Node *RChild;
}BiTNode,*BiTree;

#define SIZE 50
typedef struct 
{
    BiTree data[SIZE];
    int top;
}Stack;

#define m 100
BiTree s[m];

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

void Visit(DataType data){
    printf("%c ",data);
}

void Init(Stack *S){//初始化
    S->top=-1;
}

bool Push(Stack *S,BiTree x){//压栈
    if(S->top==SIZE-1){//判满Isfull
        return false;
    }
    S->top++;
    S->data[S->top]=x;
    return true;
}

bool Pop(Stack *S,BiTree *x){//出栈
    if (S->top==-1){//判空Isempty
        return false;
    }
    else {
        *x=S->data[S->top];
        S->top--;
        return true;
    }
}

bool GetTop(Stack *S,BiTree *x){//读取栈
    if(S->top==-1){
        return false;
    }
    else {
        *x=S->data[S->top];
        return true;
    }
}

void PreOrder(BiTree root){//先序遍历
    BiTNode *p;
    Stack S;
    Init(&S);
    p=root;
    while(p!=NULL||S.top!=-1){
        if(p!=NULL){
            Push(&S,p);
            Visit(p->data);
            p=p->LChild;//一直往左走
        }else{
            Pop(&S,&p);//弹栈
            p=p->RChild;
        }
    }
}
void inorder(BiTree root){//中序遍历，非递归，直接用栈
    int top=0;
    BiTNode *p=root;
    do{
        while (p!=NULL){
            if(top>m) return;//栈满
            top++;
            s[top]=p;//存栈
            p=p->LChild;//遍历左结点
        }
        if(top!=0){
            p=s[top];//原来的左结点
            top--;//出栈
            Visit(p->data);//访问
            p=p->RChild;//再遍历右结点，进入下一层循环
        }
    }while(p!=NULL||top!=0);//两个判断条件，栈不为空
}
void InOrder(BiTree root){//调用栈函数，实现中序遍历，思路与上述一样
    BiTNode *p;
    Stack S;
    Init(&S);
    p=root;
    while (p!=NULL||S.top!=-1)  {
        if(p!=NULL){
            Push(&S,p);//根指针进栈
            p=p->LChild;//遍历左子树
        }else{
            Pop(&S,&p);//根指针出栈
            Visit(p->data);
            p=p->RChild;//再遍历右子树
        }
    }   
}
void PostOrder(BiTree root){//调用栈函数，后序遍历
    BiTNode *p,*q;
    Stack S;
    Init(&S);
    q=NULL;
    p=root;
    while(p!=NULL||S.top!=-1){
        if(p!=NULL){
            Push(&S,p);
            p=p->LChild;
        }else{
            GetTop(&S,&p);//访问根指针
            if((p->RChild==NULL)||(p->RChild==q)){//无右孩子或者右孩子已经被访问
                Visit(p->data);
                q=p;//保存q
                Pop(&S,&p);//访问完弹栈
                p=NULL;
            }else{
                p=p->RChild;
            }
        }
    }
}




int main(){//test
    BiTree bt;
    InitBiTree(&bt);
    printf("先序创建二叉树('.'为NULL):");//例如ABD.G...CE.H..F..
    CreateBiTree(&bt);

    printf("先序遍历:");
    PreOrder(bt);
    printf("\n中序遍历:");
    InOrder(bt);
    printf("\n后序遍历:");
    PostOrder(bt);
}