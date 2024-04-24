#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTEX_NUM 20
typedef enum{DG,DN,UDG,UDN} GraphKind;
typedef char VertexData;
typedef int OtherInfo;

typedef struct ArcNode{
    int tailvex,headvex;//弧头与弧尾（箭头所指为弧头）
    struct ArcNode *hlink,*tlink;//分别指向与弧头相同和与弧尾相同的下一条弧
    OtherInfo info;
}ArcNode;
typedef struct VertexNode{
    VertexData data;
    ArcNode *firstin,*firstout;//以该顶点为弧头的第一个弧，以该顶点为弧尾的第一个弧
}VertexNode;
typedef struct{
    VertexNode vertex[MAX_VERTEX_NUM];
    int vexnum,arcnum;
    GraphKind kind;
}OrthList;

int LocateVertex(OrthList *G,VertexData v){//求顶点位置
    for(int k=0;k<G->vexnum;k++){
        if(G->vertex[k].data==v) return k;
    }
}

void CrtOrthList(OrthList *G){//创建图的十字链表
    printf("输入顶点个数和弧的个数:");
    scanf("%d,%d",&G->vexnum,&G->arcnum);
    for(int i=0;i<G->vexnum;i++){
        scanf("%c",&(G->vertex[i].data));
        G->vertex[i].firstin=NULL;
        G->vertex[i].firstout=NULL;
    }
    char vt,vh;
    ArcNode *p;
    int i,j;
    for(int k=0;k<G->arcnum;k++){
        scanf("%c,%c",&vt,&vh);
        i=LocateVertex(G,vt);
        j=LocateVertex(G,vh);
        p=(ArcNode*)malloc(sizeof(ArcNode));
        p->tailvex=i;p->headvex=j;
        p->tlink=G->vertex[i].firstout;
        G->vertex[i].firstout=p;
        p->hlink=G->vertex[j].firstin;
        G->vertex[j].firstin=p;
    }
}