#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTEX_NUM 20
typedef enum{DG,DN,UDG,UDN} GraphKind;
typedef char VertexData;

typedef struct EdgeNode{
    int mark,ivex,jvex;//mark表示是否被访问过，连接的i，j两个顶点
    struct EdgeNode *ilink,*jlink;//分别指向与i，j连接的下一个边
}EdgeNode;
typedef struct{
    VertexData data;
    EdgeNode *firstedge;
}VertexNode;
typedef struct{
    VertexNode vertex[MAX_VERTEX_NUM];
    int vexnum,arcnum;
    GraphKind kind;
}AdjMultiList;