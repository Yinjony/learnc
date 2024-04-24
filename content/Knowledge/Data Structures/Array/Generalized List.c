//广义表
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define YES "yes"
#define NO "no"
typedef char AtomType;
typedef enum {ATOM,LIST} ElemTag;//定义枚举tag
typedef struct GLNode
{
    ElemTag tag;
    union //联合，定义原子或者表
    {
        AtomType atom;//原子内容
        struct{struct GLNode *hp,*tp;}htp;//头尾指针，头指针深度，尾指针长度
    }atom_htp;
}GLNode,*GList;
// 同层
// typedef struct GLNode
// {
//     ElemTag tag;
//     union 
//     {
//         AtomType atom;
//         struct GLNode *hp;
//     }atom_htp;
//     struct GLNode *tp;
// }GLNode,*GList;
GList Head(GList L){//求广义表的表头
    if(L==NULL) return NULL;
    if(L->tag==ATOM) exit(0);
    else return L->atom_htp.htp.hp;
}
GList Tail(GList L){//求广义表的表尾
    if(L==NULL) return NULL;
    if(L->tag==ATOM) exit(0);
    else return L->atom_htp.htp.tp;
}
int Length(GList L){//求广义表长度
    int k=0;
    GLNode *s=L;
    if(L==NULL) return 0;
    if(L->tag==ATOM) exit (0);
    while(s!=NULL){
        k++;
        s=s->atom_htp.htp.tp;//移向下一个广义表节点
    }
    return k;
}
int Depth(GList L){//(a,(b,c))看括号层数，两层深度为2
    int d,max=0;
    GLNode *s=L;
    if(L==NULL) return 1;//空表深度为1，只有一个元素的(a)，深度也为1
    if(L->tag==ATOM) return 0;//原子节点深度为0
    while(s!=NULL){
        d=Depth(s->atom_htp.htp.hp);//向下深挖一层，看看深度
        if(d>max) max=d;
        s=s->atom_htp.htp.tp;//同层链表访问
    }
    return max+1;//递归思想
}
int CountAtom(GList L){//统计原子结点数目
    int n1,n2;
    if(L==NULL) return 0;
    if(L->tag==ATOM) return 1;
    n1=CountAtom(L->atom_htp.htp.hp);//表头中原子结点数目
    n2=CountAtom(L->atom_htp.htp.tp);//表尾原子结点数目
    return n1+n2;
}
bool CopyGlist(GList S,GList *T){//复制广义表
    if(S==NULL) {
        *T=NULL;
        return true;
    }
    *T=(GLNode*)malloc(sizeof(GLNode));
    if(*T==NULL) return false;
    (*T)->tag=S->tag;//复制标签
    if(S->tag==ATOM)(*T)->atom_htp.atom=S->atom_htp.atom;//复制原子
    else{
        CopyGlist(S->atom_htp.htp.hp,&((*T)->atom_htp.htp.hp));//复制表头
        CopyGlist(S->atom_htp.htp.tp,&((*T)->atom_htp.htp.tp));//复制表尾
    }
    return true;
}

void IniGList(GList *L){//初始化
    (*L)=(GList)malloc(sizeof(GLNode));
}

void CreateGList(GList *L){//创建
    char s[3];
    GList p=(GList)malloc(sizeof(GLNode));
    printf("请输入tag:");
    ElemTag tag;
    scanf("%d",&tag);
    switch(tag){
        case ATOM:{
            printf("输入原子值:");
            AtomType e;
            char c;
            c=getchar();
            scanf("%c",&e);
            p->tag=0;
            p->atom_htp.atom=e;
            (*L)=p;//赋值
            break;
        }
        case LIST:{
            p->tag=LIST;
            GList q=(GList)malloc(sizeof(GLNode));

            printf("是否拓展表头(yes/no):");
            scanf("%s",&s);
            if(strcmp(s,YES)==0){
                printf("正在纵向拓展...\n");
                CreateGList(&q);//头指针部分深挖递归
                p->atom_htp.htp.hp=q;
            }else if(strcmp(s,NO)==0){
                p->atom_htp.htp.tp=NULL;
            }
            
            printf("是否拓展表尾(yes/no):");
            scanf("%s",&s);
            if(strcmp(s,YES)==0){
                printf("正在横向拓展...\n");
                CreateGList(&q);//尾指针部分横向递归
                p->atom_htp.htp.tp=q;
            }else if(strcmp(s,NO)==0){
                p->atom_htp.htp.tp=NULL;
            }
            
            (*L)=p;
            break; 
        }
    }
}

void VisitGList(GList L){
    switch(L->tag){
        case ATOM:{
            printf("%c",L->atom_htp.atom);
            break;
        }
        case LIST:{
            if(L->atom_htp.htp.tp!=NULL){
                printf("(");
            }
            VisitGList(L->atom_htp.htp.hp);
            if(L->atom_htp.htp.tp!=NULL){
                printf(",");
                VisitGList(L->atom_htp.htp.tp);
            }else{
                printf(")");
            }
            break;
        }
    }
}

int main(){
    GList L;
    IniGList(&L);
    CreateGList(&L);
    VisitGList(L);

    printf("\n长度:%d\n深度:%d\n结点数目:%d\n",Length(L),Depth(L),CountAtom(L));
    GList H=Head(L);
    GList T=Tail(L);
    printf("表头:");
    VisitGList(H);
    printf("表尾:");
    VisitGList(T);


}