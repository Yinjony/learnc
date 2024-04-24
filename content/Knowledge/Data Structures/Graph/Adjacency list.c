#include <stdio.h>//大部分函数与邻接矩阵类似，便不再进行，具有很大差异的只有前几个基本的函数
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTEX_NUM 20
#define INFINITY 32768

typedef enum{DG,DN,UDG,UDN} GraphKind;
typedef int OtherInfo;
typedef char VertexData;

typedef struct ArcNode{//边表
    int adjvex;//这条边/弧指向的连接的顶点的位置
    struct ArcNode *nextarc;//下一条边/弧（多重边/弧）
    OtherInfo info;//与这条弧有关的信息
}ArcNode;
typedef struct VertexNode{//顶点表
    VertexData data;
    ArcNode *firstarc;//弧
}VertexNode;
typedef struct{
    VertexNode vertex[MAX_VERTEX_NUM];
    int vexnum,arcnum;
    GraphKind kind;
}AdjList;

char c;
void Visit(VertexData v){
    printf("%c ",v);
}

int LocateVertex(AdjList *G,VertexData v){//求顶点位置
    for(int k=0;k<G->vexnum;k++){
        if(G->vertex[k].data==v) return k;
    }
    return -1;
}
bool CreateDG(AdjList *G){//创建有向图
    int i,j,k;
    VertexData v1,v2;
    printf("输入顶点数和弧数:");
    scanf("%d,%d",&G->vexnum,&G->arcnum);
    c=getchar();
    printf("输入所有顶点数据:");
    for(i=0;i<G->vexnum;i++){
        scanf("%c",&G->vertex[i].data);
        G->vertex[i].firstarc=NULL;
    }
    printf("输入有向边始点以及终点:");
    for(k=0;k<G->arcnum;k++){
        c=getchar();
        scanf("%c%c",&v1,&v2);
        i=LocateVertex(G,v1);
        j=LocateVertex(G,v2);
        ArcNode *p=(ArcNode*)malloc(sizeof(ArcNode));
        p->adjvex=j;
        p->nextarc=NULL;
        if(G->vertex[i].firstarc!=NULL){
            ArcNode *q;
            for(q=G->vertex[i].firstarc;q->nextarc!=NULL;q=q->nextarc);
            q->nextarc=p;
        }else G->vertex[i].firstarc=p;
    }
    G->kind=DG;
    return true;
}
bool CreateDN(AdjList *G){//创建有向网
    int i,j,k,weight;
    VertexData v1,v2;
    printf("输入顶点数和弧数:");
    scanf("%d,%d",&G->vexnum,&G->arcnum);
    c=getchar();
    printf("输入所有顶点数据:");
    for(i=0;i<G->vexnum;i++){
        scanf("%c",&G->vertex[i].data);
        G->vertex[i].firstarc=NULL;
    }
    printf("输入始点终点以及之间的权值:");
    for(k=0;k<G->arcnum;k++){
        c=getchar();
        scanf("%c%c%d",&v1,&v2,&weight);
        i=LocateVertex(G,v1);
        j=LocateVertex(G,v2);
        ArcNode *p=(ArcNode*)malloc(sizeof(ArcNode));
        p->adjvex=j;
        p->info=weight;
        p->nextarc=NULL;
        if(G->vertex[i].firstarc!=NULL){
            ArcNode *q;
            for(q=G->vertex[i].firstarc;q->nextarc!=NULL;q=q->nextarc);
            q->nextarc=p;
        }else G->vertex[i].firstarc=p;
    }
    G->kind=DN;
    return true;
}
bool CreateUDG(AdjList *G){//创建无向图
    int i,j,k;
    VertexData v1,v2;
    printf("输入顶点数和弧数:");
    scanf("%d,%d",&G->vexnum,&G->arcnum);
    c=getchar();
    printf("输入所有顶点数据:");
    for(i=0;i<G->vexnum;i++){
        scanf("%c",&G->vertex[i].data);
        G->vertex[i].firstarc=NULL;
    }
    printf("输入相邻两顶点:");
    for(k=0;k<G->arcnum;k++){
        c=getchar();
        scanf("%c%c",&v1,&v2);
        i=LocateVertex(G,v1);
        j=LocateVertex(G,v2);

        ArcNode *out=(ArcNode*)malloc(sizeof(ArcNode));
        out->adjvex=j;
        out->nextarc=NULL;
        if(G->vertex[i].firstarc!=NULL){
            ArcNode *q;
            for(q=G->vertex[i].firstarc;q->nextarc!=NULL;q=q->nextarc);
            q->nextarc=out;
        }else G->vertex[i].firstarc=out;

        ArcNode *in=(ArcNode*)malloc(sizeof(ArcNode));
        in->adjvex=i;
        in->nextarc=NULL;
        if(G->vertex[j].firstarc!=NULL){
            ArcNode *q;
            for(q=G->vertex[j].firstarc;q->nextarc!=NULL;q=q->nextarc);
            q->nextarc=in;
        }else G->vertex[j].firstarc=in;
    }
    G->kind=UDG;
    return true;
}
bool CreateUDN(AdjList*G){//创建无向网
    int i,j,k,weight;
    VertexData v1,v2;
    printf("输入顶点数和弧数:");
    scanf("%d,%d",&G->vexnum,&G->arcnum);
    c=getchar();
    printf("输入所有顶点数据:");
    for(i=0;i<G->vexnum;i++){
        scanf("%c",&G->vertex[i].data);
        G->vertex[i].firstarc=NULL;
    }
    printf("输入两个顶点以及权值:");
    for(k=0;k<G->arcnum;k++){
        c=getchar();
        scanf("%c%c%d",&v1,&v2,&weight);
        i=LocateVertex(G,v1);
        j=LocateVertex(G,v2);
        ArcNode *out=(ArcNode*)malloc(sizeof(ArcNode));
        out->adjvex=j;
        out->info=weight;
        out->nextarc=NULL;
        if(G->vertex[i].firstarc!=NULL){
            ArcNode *q;
            for(q=G->vertex[i].firstarc;q->nextarc!=NULL;q=q->nextarc);
            q->nextarc=out;
        }else G->vertex[i].firstarc=out;

        ArcNode *in=(ArcNode*)malloc(sizeof(ArcNode));
        in->adjvex=i;
        in->info=weight;
        in->nextarc=NULL;
        if(G->vertex[j].firstarc!=NULL){
            ArcNode *q;
            for(q=G->vertex[j].firstarc;q->nextarc!=NULL;q=q->nextarc);
            q->nextarc=in;
        }else G->vertex[j].firstarc=in;
    }
    G->kind=UDN;
    return true;
}

int FirstAdjVertex(AdjList *G,VertexData v){//找到第一个邻接点，认为有向图中出度的才是连接点 
    int l=LocateVertex(G,v);
    if(l==-1) return -1;
    if(G->vertex[l].firstarc!=NULL) return G->vertex[l].firstarc->adjvex;
    return -1;
}
int NextAdjVertex(AdjList *G,VertexData v,VertexData w){//找到w邻接点之后的，（w也是v的邻接点）v的下一个邻接点
    int l=LocateVertex(G,v);
    int k=LocateVertex(G,w);
    if(l||k==-1) return -1;
    for(ArcNode *p=G->vertex[l].firstarc;p!=NULL;p=p->nextarc){
        if(G->vertex[p->adjvex].data==w){
            if(p->nextarc!=NULL){
                p=p->nextarc;
                return p->adjvex;
            }else return -1;
        }
    }
    return -1;
}

void InsertVertex(AdjList *G,VertexData u){//增加顶点
    for(int i=0;i<G->vexnum;i++){
        if(G->vertex[i].data==u) return;
    }
    G->vertex[G->vexnum].data=u;
    G->vertex[G->vexnum++].firstarc=NULL;
}
bool DeleteVertex(AdjList *G,VertexData v){//删除顶点
    int l=LocateVertex(G,v);
    if(l==-1) return false;
    ArcNode *p=G->vertex[l].firstarc;
    while(p!=NULL){
        ArcNode *q=p;
        p=p->nextarc;
        free(q);
        G->arcnum--;
    }
    for(int i=0;i<G->vexnum;i++){
        if(i==l) continue;
        ArcNode *p=G->vertex[i].firstarc;
        if(p==NULL) continue;
        if(p->adjvex==l){
            ArcNode *q=p;
            G->vertex[i].firstarc=p->nextarc;
            free(q);
            G->arcnum--;
        }else if(p->adjvex>l){
            p->adjvex--;
        }
        while(p->nextarc!=NULL){
            if(p->nextarc->adjvex==l){
                ArcNode *q=p->nextarc;
                p->nextarc=p->nextarc->nextarc;
                free(q);
                G->arcnum--;
            }else if(p->nextarc->adjvex>l){
                p->nextarc->adjvex--;
                p=p->nextarc;
            }else{
                p=p->nextarc;
            }
        }
    }
    for(int i=l;i<G->vexnum;i++){
        G->vertex[i]=G->vertex[i+1];
    }
    G->vexnum--;
    return true;
}

void InsertArc(AdjList *G,VertexData v,VertexData w){//增加边
    int i=LocateVertex(G,v);
    int j=LocateVertex(G,w);
    if(i==-1||j==-1) return;
    int weight;
    if(G->vertex[i].firstarc!=NULL){
        ArcNode *p;
        for(p=G->vertex[i].firstarc;p->nextarc!=NULL;p=p->nextarc);
        ArcNode *q=(ArcNode*)malloc(sizeof(ArcNode));
        q->adjvex=j;
        if(G->kind==DN||G->kind==DG){//??
            printf("输入权值:");
            scanf("%d",&weight);
            q->info=weight;
        }
        q->nextarc=NULL;
        p->nextarc=q;
    }
    if(G->kind==UDG||G->kind==UDN){
        ArcNode *p;
        for(p=G->vertex[j].firstarc;p->nextarc!=NULL;p=p->nextarc);
        ArcNode *q=(ArcNode*)malloc(sizeof(ArcNode));
        q->adjvex=i;
        if(G->kind==UDN){
            q->info=weight;
        }
        q->nextarc=NULL;
        p->nextarc=q;
    }
}
void DeleteArc(AdjList *G,VertexData v,VertexData w){//删除边
    int i=LocateVertex(G,v);
    int j=LocateVertex(G,w);
    if(i==-1||j==-1) return;
    if(i==-1||j==-1) return;
    ArcNode *p=G->vertex[i].firstarc;
    while(p->adjvex==j){
        ArcNode *q=p;
        G->vertex[i].firstarc=p->nextarc;
        free(q);
        G->arcnum--;
    }
    while(p->nextarc!=NULL){
        if(p->nextarc->adjvex==j){
            ArcNode *q;
            q=p->nextarc;
            p->nextarc=p->nextarc->nextarc;
            free(q);
            G->arcnum--;
        }
    }
    if(G->kind==UDG||G->kind==UDN){
        ArcNode *p=G->vertex[j].firstarc;
        while(p->adjvex==i){
            ArcNode *q=p;
            G->vertex[j].firstarc=p->nextarc;
            free(q);
            G->arcnum--;
        }
        while(p->nextarc!=NULL){
            if(p->nextarc->adjvex==i){
                ArcNode *q;
                q=p->nextarc;
                p->nextarc=p->nextarc->nextarc;
                free(q);
                G->arcnum--;
            }
        }
    }
}

typedef struct{
    int adjvex;//具有最小边值的那个顶点
    int lowcost;//最小边值
}Closedge[MAX_VERTEX_NUM];
int Minium(int n,Closedge closedge){//求数组里lowcost最小值
    int min,k,x=0;
    for(int i=0;i<n;i++){
        if(closedge[i].lowcost!=0&&x==0){
            min=closedge[i].lowcost;
            k=i;
            x=1;
        }else if(min>closedge[i].lowcost&&closedge[i].lowcost!=0){//找最小边要排除0
            min=closedge[i].lowcost;
            k=i;
        }
    }
    return k;
}
void MiniSpanTree_Prim(AdjList G,int u){//求最小生成树Prim算法
    Closedge closedge;
    closedge[u].adjvex=u;
    closedge[u].lowcost=0;
    for(int i=0;i<G.vexnum;i++){//初始化数组
        if(i!=u){
            closedge[i].adjvex=u;
            closedge[i].lowcost=INFINITY;
            for(ArcNode *p=G.vertex[u].firstarc;p!=NULL;p=p->nextarc){
                if(p->adjvex==i){
                    closedge[i].lowcost=p->info;
                }
            }
        }
    }
    for(int e=1;e<=G.vexnum-1;e++){
        int v=Minium(G.vexnum,closedge);
        int u=closedge[v].adjvex;//找到最小值
        printf("%c,%c ",G.vertex[u].data,G.vertex[v].data);//找到当前最小边
        closedge[v].lowcost=0;
        for(int i=0;i<G.vexnum;i++){
            int t=INFINITY;
            for(ArcNode *p=G.vertex[u].firstarc;p!=NULL;p=p->nextarc){//寻找是否有这个邻接点
                if(p->adjvex==i){
                    t=p->info;
                }
            }
            if(t<closedge[i].lowcost){//根据第二个结点，接着寻找其各个边值，对closedge数组进行修改
                closedge[i].lowcost=t;
                closedge[i].adjvex=v;
            }
        }
    }
}

#define SIZE 50
typedef int Data;
typedef struct 
{
    Data data[SIZE];
    int top;
}Stack;
void InitStack(Stack *S){
    S->top=-1;
}
bool IsEmptyStack(Stack *S){
    if(S->top==-1) return true;
    else return false;
}
bool IsFullStack(Stack *S){
    if(S->top==SIZE-1) return true;
    else return false;
}
bool Push(Stack *S,Data x){
    if(IsFullStack(S)){//判满Isfull
        return false;
    }
    S->top++;
    S->data[S->top]=x;
    return true;
}
bool Pop(Stack *S,Data *x){
    if (IsEmptyStack(S)){//判空Isempty
        return false;
    }
    else {
        *x=S->data[S->top];
        S->top--;
        return true;
    }
}
bool GetTop(Stack *S,Data *x){
    if(IsEmptyStack(S)){
        return false;
    }
    else {
        *x=S->data[S->top];
        return true;
    }
}

void FindID(AdjList G,int indegree[MAX_VERTEX_NUM]){//求入度
    int i;ArcNode *p;
    for(i=0;i<G.vexnum;i++) indegree[i]=0;
    for(i=0;i<G.vexnum;i++){
        ArcNode *p=G.vertex[i].firstarc;
        while(p!=NULL){
            indegree[p->adjvex]++;
            p=p->nextarc;
        }
    }
}
bool TopoSort(AdjList G){//拓扑排序
    int count=0,i,k;
    int indegree[MAX_VERTEX_NUM];
    Stack S;
    InitStack(&S);
    FindID(G,indegree);//得到入度序列
    for(i=0;i<G.vexnum;i++){
        if(indegree[i]==0) Push(&S,i);//找到入度为0的顶点，然后入栈
    }
    while (!IsEmptyStack(&S)){
        Pop(&S,&i);//弹栈，然后输出
        printf("%c",G.vertex[i].data);
        count++;//已经输出的顶点数
        ArcNode *p=G.vertex[i].firstarc;
        while(p!=NULL){
            k=p->adjvex;
            if(--indegree[k]==0) Push(&S,k);
            p=p->nextarc;
        }
    }
    if(count<G.vexnum) return false;//输出数小于顶点数，说明无法进行拓扑排序，具有回路
    else return true;
}
int ve[MAX_VERTEX_NUM];//最早发生时间的数组，也就是从源点到该点的最长路径
bool TopoOrder(AdjList G,Stack *T){//新拓扑，最早事件
    int count=0,i,j,k;
    ArcNode *p;
    int indegree[MAX_VERTEX_NUM];
    Stack S;
    InitStack(T);InitStack(&S);
    FindID(G,indegree);
    for(i=0;i<G.vexnum;i++){
        if(indegree[i]==0) Push(&S,i);
    }
    for(i=0;i<G.vexnum;i++) ve[i]=0;//初始化均为0
    while (!IsEmptyStack(&S)){
        Pop(&S,&j);
        Push(T,j);//按照拓扑排序入栈
        count++;
        p=G.vertex[j].firstarc;
        while(p!=NULL){
            k=p->adjvex;
            if(--indegree[k]==0) Push(&S,k);
            if(ve[j]+p->info>ve[k]) ve[k]=ve[j]+p->info;
            p=p->nextarc;
        }
    }
    if(count<G.vexnum) return false;
    else return true;
}
bool CriticalPath(AdjList G){//利用新拓扑求关键路径
    ArcNode *p;
    int i,j,k,dut,ei,li;
    char tag;
    int vl[MAX_VERTEX_NUM];//最晚发生时间的数组
    Stack T;
    if(!TopoOrder(G,&T)) return false;//先用拓扑排序得到逆拓扑序列T栈
    for(i=0;i<G.vexnum;i++) vl[i]=ve[i];//各个顶点事件vl值初始化为汇点的ve值
    while(!IsEmptyStack(&T)){//逆拓扑排序求各个顶点的vl值
        Pop(&T,&j);
        p=G.vertex[j].firstarc;
        while(p!=NULL){
            k=p->adjvex;
            dut=p->info;
            if(vl[k]-dut<vl[j]) vl[j]=vl[k]-dut;
            p=p->nextarc;
        }
    }
    for(j=0;j<G.vexnum;j++){
        p=G.vertex[j].firstarc;
        while(p!=NULL){
            k=p->adjvex;dut=p->info;
            ei=ve[j];li=vl[k]-dut;
            tag=(ei==li)?'*':' ';
            printf("%c,%c,%d,%d,%d,%c\n",G.vertex[j].data,G.vertex[k].data,dut,ei,li,tag);
            p=p->nextarc;
        }
    }
    return true;
}

typedef struct SeqList{
    char *a;//动态数组
    int size;
    int capacity;
}SeqList;
void InitList(SeqList *L){//初始化
    if(L==NULL) return;

    L->a=NULL;
    L->size=0;
    L->capacity=0;
}
void CheckCapacity(SeqList *L){//检查容量是否满
    if(L==NULL) return;
    if(L->size==L->capacity){
        int newcapacity;
        if(L->capacity==0) newcapacity=4;
        else newcapacity=2*L->capacity;
        char *p=(char*)realloc(L->a,newcapacity*sizeof(char));//进行扩充，不改变原有值
        if(p==NULL) return;
        L->a=p;
        L->capacity=newcapacity;
    }
}
void AddTail(SeqList *L,char x){//添加数据
    if(L==NULL) return;
    CheckCapacity(L);
    L->a[L->size]=x;
    L->size++;
}
bool Member(int x,SeqList *L){//查找是否在其中
    if(L==NULL) return false;
    for(int i=0;i<L->size;i++){
        if(L->a[i]==x) return true;
    }
    return false;
}
SeqList JoinList(SeqList L1,SeqList L2){//合并两个表
    SeqList L;
    int newcapacity=L1.capacity+L2.capacity;
    char *p=(char*)realloc(L1.a,newcapacity*sizeof(char));
    L.a=p;
    L.size=L1.size+L2.size-1;
    L.capacity=newcapacity;
    for(int i=1;i<L2.size;i++){
        L.a[L1.size+i-1]=L2.a[i];
    }
    return L;
}
typedef unsigned int WeightType;
void ShortestPath_DJS(AdjList G,int v0,WeightType dist[MAX_VERTEX_NUM],SeqList path[MAX_VERTEX_NUM]){
    SeqList S;//已找到最短路径的顶点的集合
    int k;
    for(int i=0;i<G.vexnum;i++) dist[i]=INFINITY;
    for(ArcNode *p=G.vertex[v0].firstarc;p!=NULL;p=p->nextarc) {
        dist[p->adjvex]=p->info;
        AddTail(&path[p->adjvex],G.vertex[v0].data);//相邻加入
        AddTail(&path[p->adjvex],G.vertex[p->adjvex].data);
    }
    InitList(&S);//再初始化一个表
    AddTail(&S,G.vertex[v0].data);//v0当作找到了最短路径
    for(int t=1;t<=G.vexnum-1;t++){//求v0到其他点的最短路径
        int min=INFINITY;
        for(int i=0;i<G.vexnum;i++){
            if(!Member(G.vertex[i].data,&S)&&dist[i]<min){//该顶点未找到最短路径，找到距离v0最近的顶点k
                k=i;min=dist[i];
            }
        }
        if(min==INFINITY) return;//没有说明没有路径，回退
        AddTail(&S,G.vertex[k].data);//k点就是找到了最短路径
        for(ArcNode *p=G.vertex[k].firstarc;p!=NULL;p=p->nextarc){
            if(!Member(G.vertex[p->adjvex].data,&S)&&(dist[k]+p->info<dist[p->adjvex])){
                dist[p->adjvex]=dist[k]+p->info;
                path[p->adjvex]=path[k];
                AddTail(&path[p->adjvex],G.vertex[p->adjvex].data);
            }
        }
    }
}
void ShortestPath_Floyd(AdjList G,WeightType dist[MAX_VERTEX_NUM][MAX_VERTEX_NUM],SeqList path[MAX_VERTEX_NUM][MAX_VERTEX_NUM]){
    for(int i=0;i<G.vexnum;i++){//初始化dist和path
        for(int i=0;i<G.vexnum;i++){
            for(int j=0;j<G.vexnum;j++){
                dist[i][j]=INFINITY;
            }
        }
        for(ArcNode *p=G.vertex[i].firstarc;p!=NULL;p=p->nextarc) {
            dist[i][p->adjvex]=p->info;
            AddTail(&path[i][p->adjvex],G.vertex[i].data);//相邻加入
            AddTail(&path[i][p->adjvex],G.vertex[p->adjvex].data);
        }
    }
    for(int k=0;k<G.vexnum;k++){//以k为中介点
        for(int i=0;i<G.vexnum;i++){
            for(int j=0;j<G.vexnum;j++){
                if(dist[i][k]+dist[k][j]<dist[i][j]){//小就换
                    dist[i][j]=dist[i][k]+dist[k][j];
                    path[i][j]=JoinList(path[i][k],path[k][j]);//换了之后说明包含k点的路径才是最短的，然后再修改path路经变为i到k，k到j
                }
            }
        }
    }
}



#define MAXLEN 3E38//最大浮点数
int CenterVex(AdjList G){//求中心顶点
    int i,j,k;
    float min,len;
    float A[MAX_VERTEX_NUM][MAX_VERTEX_NUM];//储存i与j之间的最短路径

    for(i=0;i<G.vexnum;i++){
        for(j=0;j<G.vexnum;j++){
            A[i][j]=INFINITY;
        }
        A[i][j]=0;
    }
    for(i=0;i<G.vexnum;i++){//初始化
        for(ArcNode *p=G.vertex[i].firstarc;p!=NULL;p=p->nextarc){
            A[i][p->adjvex]=p->info;
        }
    }
    for(k=0;k<G.vexnum;k++){//求每对顶点之间的最短路径长度
        for(i=0;i<G.vexnum;i++){
            for(j=0;j<G.vexnum;j++){
                if(A[i][k]+A[k][j]<A[i][j]){
                    A[i][j]=A[i][k]+A[k][j];
                }
            }
        }
    }
    min=MAXLEN;k=0;
    for(i=0;i<G.vexnum;i++){
        len=0;
        for(j=0;j<G.vexnum;j++) len=len+A[i][j];//求两点之间的路径
        if(len<min){//vi到其余顶点最短路路径是最小的，则vi就是中心顶点
            k=i;min=len;
        }
    }
    return k;//返回顶点坐标
}
int main(){
    AdjList G;
    CreateDG(&G);
    DeleteVertex(&G,'A');
}