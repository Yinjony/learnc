#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#define ENDKEY 0

typedef int KeyType;
typedef char OtherType;

typedef struct node{
    KeyType key;
    struct node *lchild,*rchild;
}BSTNode,*BSTree;//二叉排序树
void InsertBST(BSTree *bst,KeyType key){//插入结点
    BSTree s;
    if(*bst==NULL){//要是为空就新建
        s=(BSTree)malloc(sizeof(BSTNode));
        s->key=key;
        s->lchild=NULL;s->rchild=NULL;
        *bst=s;
    }
    else if(key<(*bst)->key) InsertBST(&((*bst)->lchild),key);//小于就插入左子树
    else if(key>(*bst)->key) InsertBST(&((*bst)->rchild),key);//大于就插入右子树
}
void CreateBST(BSTree *bst){//创建二叉排序树
    KeyType k;
    *bst=NULL;
    printf("输入数据:");
    scanf("%d",&k);
    while(k!=ENDKEY){
        InsertBST(bst,k);
        scanf("%d",&k);
    }
}
BSTNode *SearchBST(BSTree bst,KeyType key){//查找递归算法
    if(!bst) return NULL;
    else if(bst->key==key) return bst;
    else if(bst->key>key) return SearchBST(bst->lchild,key);
    else return SearchBST(bst->rchild,key);

    // BSTree q;//查找非递归算法
    // q=bst;
    // while(q){
    //     if(q->key==key) return q;
    //     else if(q->key>key) q=q->lchild;
    //     else q=q->rchild;
    // }
    // return NULL;
}
BSTNode *DelBST(BSTree bst,KeyType key){//删去某个结点
    BSTNode *p,*f,*s,*q;
    p=bst;f=NULL;
    while(p){
        if(p->key==key) break;
        f=p;//让f指向p的双亲结点
        if(p->key>key) p=p->lchild;
        else p=p->rchild;
    }
    if(p==NULL) return bst;//没找到就返回原来的树
    if(p->lchild==NULL){
        if(f==NULL) bst=p->rchild;//说明p就是根，直接换就行
        else if(f->lchild==p) f->lchild=p->rchild;//如果p是左孩子放左链
        else f->rchild=p->rchild;//右孩子放右链
        free(p);
    }else{//p有左子树
        q=p;s=p->lchild;
        while(s->rchild){//p的左子树最右下结点就是中序直接前驱
            q=s;s=s->rchild;
        }
        if(q==p) q->lchild=s->lchild;//左子树的右子树为空，直接把左子树的左子树接到q的左链上
        else q->rchild=s->lchild;//否则接到右链上
        p->key=s->key;//把p的值改为q的
        free(s);
    }
    return bst;//返回修改后的树
}

typedef struct Node{
    KeyType key;
    struct Node *lchild,*rchild;
    int bf;//平衡标志，大于2即为失衡
}AVLTNode,*AVLTree;//平衡二叉树
void ins_AVLtree(AVLTree *avlt,KeyType key){
    AVLTree S=(AVLTree)malloc(sizeof(AVLTNode));//制造key的结点
    S->key=key;
    S->lchild=S->rchild=NULL;
    S->bf=0;
    if(*avlt==NULL) *avlt=S;//如果为空，则初始化
    else{
        AVLTNode *A=*avlt;AVLTNode *FA=NULL;
        AVLTNode *B,*C;
        AVLTNode *p=*avlt;AVLTNode *fp=NULL;
        while(p!=NULL){
            if(p->bf!=0){//如果不平衡，那么赋值给A和FA
                A=p;FA=fp;
            }
            fp=p;//fp为插入位置，p用于寻找
            if(key<p->key) p=p->lchild;
            else p=p->rchild;
        }
        if(key<fp->key) fp->lchild=S;//找到插入位置后进行插入
        else fp->rchild=S;

        //确定B并修改A的平衡因子
        if(key<A->key){//插入值在左
            B=A->lchild;
            A->bf++;
        }else{//在右
            B=A->rchild;
            A->bf--;
        }

        p=B;//找到B
        while(p!=S){//寻找插入位置，顺便改变B到S路径上各个结点的平衡因子
            if(key<p->key){
                p->bf=1;
                p=p->lchild;
            }else{
                p->bf=-1;
                p=p->rchild;
            }
        }

        //判断失衡类型并进行相应处理
        if(A->bf==2&&B->bf==1){//LL
            A->lchild=B->rchild;//先进行修改二叉树
            B->rchild=A;
            A->bf=0;B->bf=0;
            if(FA==NULL) *avlt=B;//为根，则B就是改后的整个树
            else if(A==FA->lchild) FA->lchild=B;
            else FA->rchild=B;
        }else if(A->bf==2&&B->bf==-1){//LR
            C=B->rchild;
            B->rchild=C->lchild;
            A->lchild=C->rchild;
            C->lchild=B;C->rchild=A;
            if(S->key<C->key){//此处还需要进行对平衡值的修改
                A->bf=-1;
                B->bf=0;
                C->bf=0;
            }else if(S->key>C->key){
                A->bf=0;
                B->bf=1;
                C->bf=0;
            }else{
                A->bf=0;
                B->bf=0;
            }
            if(FA==NULL) *avlt=C;
            else if(A==FA->lchild) FA->lchild=C;
            else FA->rchild=C;
        }else if(A->bf==-2&&B->bf==1){//RL
            C=B->lchild;
            B->lchild=C->rchild;
            A->rchild=C->lchild;
            C->lchild=A;C->rchild=B;
            if(S->key<C->key){
                A->bf=0;
                B->bf=-1;
                C->bf=0;
            }else if(S->key>C->key){
                A->bf=1;
                B->bf=0;
                C->bf=0;
            }else{
                A->bf=0;
                B->bf=0;
            }
            if(FA==NULL) *avlt=C;
            else if(A==FA->lchild) FA->lchild=C;
            else FA->rchild=C;
        }else if(A->bf==-2&&B->bf==-1){//RR
            A->rchild=B->lchild;
            B->lchild=A;
            A->bf=0;B->bf=0;
            if(FA==NULL) *avlt=B;
            else if(A==FA->lchild) FA->lchild=B;
            else FA->rchild=B;
        }
    }
}

#define m 3//阶数，最多子树数
typedef int Boolean;
typedef struct Mbtnode{
    struct Mbtnode *parent;
    int keynum;//关键字数量
    KeyType key[m+1];//储存关键字，从1开始，1,2,3...m,m不放关键字，放了说明满了
    struct Mbtnode *ptr[m+1];//子树数0,1,2...m-1，m处没有关键字所以m号子结点废弃，子树仅比关键字数多1
}Mbtnode,*Mbtree;
//在结点中寻找关键字，如果为key则就是目标结点，如果小于key则相当于找到了插入位置，接着为移动到下一层提供参考
int Search(Mbtree mbt,KeyType key){
    int n=mbt->keynum;
    int i=1;
    while(i<=n&&mbt->key[i]<=key) i++;//要是key所在小于1，则说明在0号子结点，要是大于x小于x+1，则说明在x号子结点内
    return i-1;
}
//找到了之后，将结点地址存在np中，内置序号存在pos中
Boolean srch_mbtree(Mbtree mbt,KeyType key,Mbtree *np,int *pos){
    Mbtnode *p=mbt;
    Mbtnode *fp=NULL;
    bool found=false;//是否找到
    int i=0;
    while(p!=NULL&&!found){
        i=Search(p,key);
        if(i>0&&p->key[i]==key) found=true;//找到了目标，则found为true
        else{//没有找到就移动到下一层的结点
            fp=p;//fp为p的双亲结点
            p=p->ptr[i];//转下一个子树
        }
    }
    if(found){//找到了
        *np=p;
        *pos=i;
        return true;
    }else{//不存在
        *np=fp;
        *pos=i;//返回应该插入的位置
        return false;
    }

}
void Init(Mbtree *mbt){
    *mbt=NULL;
}
//在mbp->key[ipos+1]处插入key，在mbp->ptr[ipos+1]处插入rp
void Insert(Mbtree mbp,int ipos,KeyType key,Mbtree rp){
    for(int j=mbp->keynum;j>=ipos+1;j--){//先将各个值向后移一位，空出位置
        mbp->key[j+1]=mbp->key[j];
        mbp->ptr[j+1]=mbp->ptr[j];
    }
    mbp->key[ipos+1]=key;//然后插入该值，因为目的是插入到ipos+1的位置
    mbp->ptr[ipos+1]=rp;
    if(rp) rp->parent=mbp;//接上双亲结点
    mbp->keynum++;
}
//分裂过程，当关键字数为m个时，单纯将结点分裂成两个而已
void Split(Mbtree oldp,Mbtree *newp){//旧结点成为中间值的左结点，新结点成为右结点
    int s=ceil((float)m/2);//拆成s，n
    int n=m-s;
    *newp=(Mbtree)malloc(sizeof(Mbtnode));
    (*newp)->keynum=n;
    (*newp)->ptr[0]=oldp->ptr[s];
    if(oldp->ptr[s]) oldp->ptr[s]->parent=(*newp);
    for(int i=1;i<=n;i++){
        (*newp)->key[i]=oldp->key[s+i];
        (*newp)->ptr[i]=oldp->ptr[s+i];
        if(oldp->ptr[s+i]) oldp->ptr[s+i]->parent=(*newp);
    }
    oldp->keynum=s-1;//旧结点的关键字值都没变，但由于长度被切了一半又减去了中间值，所以当作后面的值都被删了
}
void ins_mbtree(Mbtree *mbt,KeyType key,Mbtree q,int i){//如果mbt为空，q=NULL，i=0，否则，q指向某个最下层非终端结点，k应该插入q->key[i+1]处，如果keynum>m-1则进行分裂处理
    Mbtree q1,ap;
    if(*mbt==NULL){
        *mbt=(Mbtree)malloc(sizeof(Mbtnode));
        (*mbt)->keynum=1;(*mbt)->parent=NULL;
        (*mbt)->key[1]=key;
        (*mbt)->ptr[0]=NULL;//两个子树均为空
        (*mbt)->ptr[1]=NULL;
    }else{
        int x=key;//插到q->key[i+1]处
        ap=NULL;//插到q->ptr[i+1]处
        bool finished=false;
        while(q!=NULL&&!finished){//q为NULL说明到了根节点
            Insert(q,i,x,ap);//在q结点，i+1处，插入x
            if(q->keynum<m) finished=true;//最后关键字数没有超
            else{//关键字数超了，需要进行分裂
                int s=ceil((float)m/2);//向上取整，得到中间位置的值，成为第一个结点
                Split(q,&q1);//进行分裂，得到左右结点
                x=q->key[s];//然后得到中间值
                ap=q1;//保存一下右结点，和作为中间值右结点一起插入，
                q=q->parent;//到上一层，旧结点的位置不变，仍然是原来的位置，只是关键字数量改变了而已
                if(q!=NULL) i=Search(q,x);//如果不为空，则插入中间值，然后重复流程
            }
        }
        if(!finished){//根分裂要产生新根
            Mbtree new_root=(Mbtree)malloc(sizeof(Mbtnode));
            new_root->keynum=1;
            new_root->parent=NULL;
            new_root->key[1]=x;
            new_root->ptr[0]=*mbt;
            if((*mbt)) (*mbt)->parent=new_root;//产生的新根依然需要进行连接双亲结点，因为没有走insert函数
            new_root->ptr[1]=ap;
            if(ap) ap->parent=new_root;
            *mbt=new_root;
        }
    }
}

int main(){
    // BSTree bst;
    // CreateBST(&bst);

    // KeyType key;

    // printf("输入查找目标:");
    // scanf("%d",&key);
    // BSTNode *p=SearchBST(bst,key);
    // printf("查找结果:%d",p->key);

    // printf("\n输入删除目标:");
    // scanf("%d",&key);
    // DelBST(bst,key);



    // AVLTree avlt;
    // KeyType key;
    // avlt=NULL;
    // printf("输入数据:");
    // scanf("%d",&key);
    // while(key!=ENDKEY){
    //     ins_AVLtree(&avlt,key);
    //     scanf("%d",&key);
    // }

    Mbtree mbt;
    Init(&mbt);
    printf("输入数据:");
    int key;
    scanf("%d",&key);
    while(key!=-1){
        Mbtree p;
        int ipos;
        if(srch_mbtree(mbt,key,&p,&ipos)) {
            printf("已插入\n");
        }else ins_mbtree(&mbt,key,p,ipos);
        scanf("%d",&key);
    }
    printf("xxx");
}