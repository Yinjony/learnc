#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct node
{
    int val;
    struct node *left;
    struct node *right;
    struct node *parent;
    int height;
} node_t;

int getheight(node_t *p){
    if(p==NULL) return 0;
    else return p->height;
}
node_t* avl_insert(node_t *root, int val){
    node_t *S=(node_t*)malloc(sizeof(node_t));//制造key的结点
    S->val=val;
    S->left=S->right=NULL;
    S->parent=NULL;
    S->height=1;
    if(root==NULL) root=S;//如果为空，则初始化
    else{
        node_t *A=root;node_t *FA=NULL;
        node_t *B,*C;
        node_t *p=root;node_t *fp=NULL;
        while(p!=NULL){        
            if(getheight(p->left)-getheight(p->right)!=0){//如果不平衡，那么赋值给A和FA
                A=p;FA=p->parent;
            }
            fp=p;
            if(val<p->val) p=p->left;
            else p=p->right;
        }
        S->parent=fp;
        if(val<fp->val) fp->left=S;//找到插入位置后进行插入
        else fp->right=S;
        //确定B并修改A的平衡因子
        A->height++;
        if(val<A->val){//插入值在左
            B=A->left;
        }else{//在右
            B=A->right;
        }

        p=B;//找到B
        while(p!=S){//寻找插入位置，顺便改变B到S路径上各个结点的平衡因子
            p->height++;
            if(val<p->val) p=p->left;
            else p=p->right;
        }
        //判断失衡类型并进行相应处理
        if(getheight(A->left)-getheight(A->right)==2&&getheight(B->left)-getheight(B->right)==1){//LL
            A->left=B->right;//先进行修改二叉树
            B->right=A;
            A->parent=B;
            if(A->left!=NULL) A->left->parent=A;
            B->parent=NULL;
            A->height=A->height+2;
            if(FA==NULL) root=B;//为根，则B就是改后的整个树
            else if(A==FA->left) FA->left=B;
            else FA->right=B;
        }else if(getheight(A->left)-getheight(A->right)==2&&getheight(B->left)-getheight(B->right)==-1){//LR
            C=B->right;
            B->right=C->left;
            A->left=C->right;
            C->left=B;C->right=A;
            A->parent=C;
            if(A->left!=NULL) A->left->parent=A;
            B->parent=C;
            if(B->right!=NULL) B->right->parent=B;
            C->parent=NULL;
            A->height=A->height+2;
            B->height=B->height-1;
            C->height=C->height+1;
            if(FA==NULL) root=C;
            else if(A==FA->left) FA->left=C;
            else FA->right=C;
        }else if(getheight(A->left)-getheight(A->right)==-2&&getheight(B->left)-getheight(B->right)==1){//RL
            C=B->left;
            B->left=C->right;
            A->right=C->left;
            C->left=A;C->right=B;
            A->parent=C;
            if(A->right!=NULL) A->right->parent=A;
            B->parent=C;
            if(B->left!=NULL) B->left->parent=B;
            C->parent=NULL;
            A->height=A->height+2;
            B->height=B->height-1;
            C->height=C->height+1;
            if(FA==NULL) root=C;
            else if(A==FA->left) FA->left=C;
            else FA->right=C;
        }else if(getheight(A->left)-getheight(A->right)==-2&&getheight(B->left)-getheight(B->right)==-1){//RR
            A->right=B->left;
            B->left=A;
            A->parent=B;
            if(A->right!=NULL) A->right->parent=A;
            B->parent=NULL;
            A->height=A->height+2;
            if(FA==NULL) root=B;
            else if(A==FA->left) FA->left=B;
            else FA->right=B;
        }
    }
    return root;
}

int main(){
    node_t *avlt;
    int key;
    avlt=NULL;
    printf("输入数据:");
    scanf("%d",&key);
    while(key!=-1){
        avlt=avl_insert(avlt,key);
        scanf("%d",&key);
    }

}

