#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTEX_NUM 20//最多顶点个数
#define INFINITY 32768//极大值无穷大

typedef enum{DG,DN,UDG,UDN} GraphKind;//DG有向图，DN有向网，UDG无向图，UDN无向网
typedef int AdjType;
typedef int OtherInfo;
typedef char VertexData;//顶点数据类型

typedef struct ArcNode{
    AdjType adj;//对无权图，1,0来表示是否相邻；对带权图来表示为权值类型
    OtherInfo info;//权值
}ArcNode;
typedef struct{
    VertexData vertex[MAX_VERTEX_NUM];//顶点向量
    ArcNode arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];//邻接矩阵
    int vexnum,arcnum;//顶点数，弧数
    GraphKind kind;//图种类
}AdjMatrix;

char c;
void Visit(VertexData v){
    printf("%c ",v);
}

int LocateVertex(AdjMatrix *G,VertexData v){//求顶点位置
    for(int k=0;k<G->vexnum;k++){
        if(G->vertex[k]==v) return k;
    }
    return -1;
}
bool CreateDG(AdjMatrix *G){//创建有向图
    int i,j,k;
    VertexData v1,v2;
    printf("输入顶点数和弧数:");
    scanf("%d,%d",&G->vexnum,&G->arcnum);
    for(i=0;i<G->vexnum;i++)
        for(j=0;j<G->vexnum;j++) 
            G->arcs[i][j].adj=false;
    c=getchar();
    printf("输入所有顶点数据:");
    for(i=0;i<G->vexnum;i++) scanf("%c",&G->vertex[i]);
    printf("输入有向边始点以及终点:");
    for(k=0;k<G->arcnum;k++){
        c=getchar();
        scanf("%c%c",&v1,&v2);
        i=LocateVertex(G,v1);
        j=LocateVertex(G,v2);
        G->arcs[i][j].adj=true;
    }
    G->kind=DG;
    return true;
}
bool CreateDN(AdjMatrix *G){//创建有向网
    int i,j,k,weight;
    VertexData v1,v2;
    printf("输入顶点数和弧数:");
    scanf("%d,%d",&G->vexnum,&G->arcnum);
    for(i=0;i<G->vexnum;i++)
        for(j=0;j<G->vexnum;j++){
            G->arcs[i][j].adj=false;
            if(i==j) G->arcs[i][j].info=0;
            else G->arcs[i][j].info=INFINITY;//每个条弧之间都是无穷大，初始化
        }
    c=getchar();
    printf("输入所有顶点数据:");
    for(i=0;i<G->vexnum;i++) scanf("%c",&G->vertex[i]);
    printf("输入始点终点以及之间的权值:");
    for(k=0;k<G->arcnum;k++){
        c=getchar();
        scanf("%c%c%d",&v1,&v2,&weight);
        i=LocateVertex(G,v1);
        j=LocateVertex(G,v2);
        G->arcs[i][j].info=weight;
        G->arcs[i][j].adj=true;
    }
    G->kind=DN;
    return true;
}
bool CreateUDG(AdjMatrix *G){//创建无向图
    int i,j,k;
    VertexData v1,v2;
    printf("输入顶点数和弧数:");
    scanf("%d,%d",&G->vexnum,&G->arcnum);
    for(i=0;i<G->vexnum;i++)
        for(j=0;j<G->vexnum;j++) 
            G->arcs[i][j].adj=false;//每个条弧之间都是无穷大，初始化
    c=getchar();
    printf("输入所有顶点数据:");
    for(i=0;i<G->vexnum;i++) scanf("%c",&G->vertex[i]);
    printf("输入相邻两顶点:");
    for(k=0;k<G->arcnum;k++){
        c=getchar();
        scanf("%c%c",&v1,&v2);
        i=LocateVertex(G,v1);
        j=LocateVertex(G,v2);
        G->arcs[i][j].adj=true;
        G->arcs[j][i].adj=true;
    }
    G->kind=UDG;
    return true;
}
bool CreateUDN(AdjMatrix *G){//创建无向网
    int i,j,k,weight;
    VertexData v1,v2;
    printf("输入顶点数和弧数:");
    scanf("%d,%d",&G->vexnum,&G->arcnum);
    for(i=0;i<G->vexnum;i++)
        for(j=0;j<G->vexnum;j++){
            G->arcs[i][j].adj=false;
            if(i==j) G->arcs[i][j].info=0;
            else G->arcs[i][j].info=INFINITY;//每个条弧之间都是无穷大，初始化
        }
    c=getchar();
    printf("输入所有顶点数据:");
    for(i=0;i<G->vexnum;i++) scanf("%c",&G->vertex[i]);
    printf("输入两个顶点以及权值:");
    for(k=0;k<G->arcnum;k++){
        c=getchar();
        scanf("%c%c%d",&v1,&v2,&weight);
        i=LocateVertex(G,v1);
        j=LocateVertex(G,v2);
        G->arcs[i][j].info=weight;
        G->arcs[i][j].adj=true;
        G->arcs[j][i].info=weight;
        G->arcs[j][i].adj=true;
    }
    G->kind=UDN;
    return true;
}

int FirstAdjVertex(AdjMatrix *G,VertexData v){//找到第一个邻接点，认为有向图中出度的才是连接点 
    int l=LocateVertex(G,v);
    for(int i=0;i<G->vexnum;i++){
        if(G->arcs[l][i].adj==true) return i;
    }
    return -1;
}
int NextAdjVertex(AdjMatrix *G,VertexData v,VertexData w){//找到w邻接点之后的，（w也是v的邻接点）v的下一个邻接点
    int l=LocateVertex(G,v);
    int k=LocateVertex(G,w);
    for(int i=k+1;i<G->vexnum;i++){
        if(G->arcs[l][i].adj==true) return i;
    }
    return -1;
}

void InsertVertex(AdjMatrix *G,VertexData u){//增加顶点
    for(int i=0;i<G->vexnum;i++){
        if(G->vertex[i]==u) return;
    }
    G->vertex[G->vexnum++]=u;
}
void DeleteVertex(AdjMatrix *G,VertexData v){//删除顶点
    int l=LocateVertex(G,v);
    if(l==-1) return;
    for(int i=l,j=i+1;j<G->vexnum;i++,j++){//删除点
        G->vertex[i]=G->vertex[j];
    }
    for(int i=0;i<G->vexnum;i++){//计算
        if(G->arcs[i][l].adj==true) G->arcnum--;
        if(G->arcs[l][i].adj==true) G->arcnum--;
    }
    for(int i=0;i<G->vexnum;i++){//删除边
        for(int j=0;j<G->vexnum;j++){
            if(i<l){
                if(j>l) G->arcs[i][j-1]=G->arcs[i][j]; 
            }else{
                if(j<l) G->arcs[i-1][j]=G->arcs[i][j];
                else G->arcs[i-1][j-1]=G->arcs[i][j];
            }
        }
    }
    G->vexnum--;
}

void InsertArc(AdjMatrix *G,VertexData v,VertexData w){//增加边
    int i=LocateVertex(G,v);
    int j=LocateVertex(G,w);
    if(i==-1||j==-1) return;
    if(G->kind==DG||G->kind==DN) {//有向图和无向图分别操作
        if(G->arcs[i][j].adj==true){
            printf("已经有边了");
        }else{
            G->arcs[i][j].adj=true;
        }
    }else{
        if(G->arcs[i][j].adj==true){
            printf("已经有边了");
        }else{
            G->arcs[i][j].adj=true;
            G->arcs[j][i].adj=true;
        }
    }
}
void DeleteArc(AdjMatrix *G,VertexData v,VertexData w){//删除边
    int i=LocateVertex(G,v);
    int j=LocateVertex(G,w);
    if(i==-1||j==-1) return;
    if(i==-1||j==-1) return;
    if(G->kind==DG||G->kind==DN) {
        G->arcs[i][j].adj=false;
    }else{
        G->arcs[i][j].adj=false;
        G->arcs[j][i].adj=false;
    }
}

int visited[MAX_VERTEX_NUM];//访问过的顶点
void DepthFirstSearch(AdjMatrix G,int v0){//深度优先搜索算法
    Visit(G.vertex[v0]);
    visited[v0]=true;
    for(int vj=0;vj<G.vexnum;vj++){
        if(!visited[vj]&&G.arcs[v0][vj].adj==1){//该点没有被访问过然后并且与之前的那个顶点相邻
            DepthFirstSearch(G,vj);
        }
    }
}
typedef struct node{
    int data;
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
bool IsEmptyQueue(Queue Q){
    if(Q.rear==Q.front) return true;
    else return false;
}
bool EnterQueue(Queue *Q,int x){
    Node *newp;
    newp=(Node*)malloc(sizeof(Node));
    if(newp!=NULL){
        newp->data=x;
        newp->next=NULL;
        Q->rear->next=newp;
        Q->rear=newp;
        return true;
    }else return false;
}
bool DeleteQueue(Queue *Q,int *x){//出队列
    Node *p;
    if(Q->front==Q->rear) 
        return false;
    
    p=Q->front->next;
    Q->front->next=p->next;//第一个元素出列
    if(Q->rear==p){//如果p就是最后一个结点
        Q->rear=Q->front;
    }
    *x=p->data;
    free(p);
    return true;
}
void BreadthFirstSearch(AdjMatrix G,int v0){//广度优先搜索联通子图
    Visit(G.vertex[v0]);
    visited[v0]=true;
    Queue Q;
    InitQueue(&Q);
    EnterQueue(&Q,v0);//队头元素入列
    while(!IsEmptyQueue(Q)){
        int v;
        DeleteQueue(&Q,&v);
        int w=FirstAdjVertex(&G,G.vertex[v]);//找第一个邻接点
        while(w!=-1){
            if(!visited[w]){
                Visit(G.vertex[w]);
                visited[w]=true;
                EnterQueue(&Q,w);//入队
            }
            w=NextAdjVertex(&G,G.vertex[v],G.vertex[w]);//找到下一个邻接点
        }
    }
}
bool TraverseGraph(AdjMatrix G){//遍历所有结点
    int num=0;
    for(int vi=0;vi<G.vexnum;vi++) visited[vi]=false;//对每一个结点表示没有进行访问
    for(int vi=0;vi<G.vexnum;vi++){
        if(!visited[vi]){//如果没有访问就进行深度优先搜索算法
            DepthFirstSearch(G,vi);
            // BreadthFirstSearch(G,vi);
            num++;
        }
    }
    if(num==G.vexnum) return true;//连通
    else return false;
}

int pre[MAX_VERTEX_NUM];
void print_path(int pre[MAX_VERTEX_NUM],int v,AdjMatrix G){//pre数组便是用于查找上一个访问的位置
    while(v!=pre[v]){
        Visit(G.vertex[v]);
        v=pre[v];
    }
    Visit(G.vertex[0]);
}
void DFS(AdjMatrix G,int u,int v){//深度优先进行搜索，目测是会找出所有通路来
    if(u==v){//如果找到了，就打印出来
        print_path(pre,v,G);
        return;
    }
    int w=FirstAdjVertex(&G,G.vertex[u]);//找第一个邻接点
    while(w!=-1){
        if(pre[w]==-1){//没有被访问过
            pre[w]=u;
            DFS(G,w,v);
        }
        w=NextAdjVertex(&G,G.vertex[u],G.vertex[w]);//转向下一个邻接点
    }
}
void Path(AdjMatrix G,int u,int v){//深度优先找出从u到v的简单路径
    for(int i=0;i<MAX_VERTEX_NUM;i++) pre[i]=-1;
    pre[u]=u;
    DFS(G,u,v);
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
void MiniSpanTree_Prim(AdjMatrix G,int u){//求最小生成树Prim算法
    Closedge closedge;
    closedge[u].adjvex=u;
    closedge[u].lowcost=0;
    for(int i=0;i<G.vexnum;i++){//初始化数组
        if(i!=u){
            closedge[i].adjvex=u;
            closedge[i].lowcost=G.arcs[u][i].info;
        }
    }
    for(int e=1;e<=G.vexnum-1;e++){
        int v=Minium(G.vexnum,closedge);
        int u=closedge[v].adjvex;//找到最小值
        printf("%c,%c ",G.vertex[u],G.vertex[v]);//找到当前最小边
        closedge[v].lowcost=0;
        for(int i=0;i<G.vexnum;i++){
            if(G.arcs[v][i].info<closedge[i].lowcost){//根据第二个结点，接着寻找其各个边值，对closedge数组进行修改
                closedge[i].lowcost=G.arcs[v][i].info;
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

void FindID(AdjMatrix G,int indegree[MAX_VERTEX_NUM]){//求入度
    int i;ArcNode *p;
    for(i=0;i<G.vexnum;i++) indegree[i]=0;
    for(i=0;i<G.vexnum;i++){
        for(int j=0;j<G.vexnum;j++){
            if(G.arcs[i][j].adj==true) indegree[j]++;
        }
    }
}
bool TopoSort(AdjMatrix G){//拓扑排序
    int count=0,i;
    int indegree[MAX_VERTEX_NUM];
    Stack S;
    InitStack(&S);
    FindID(G,indegree);//得到入度序列
    for(i=0;i<G.vexnum;i++){
        if(indegree[i]==0) Push(&S,i);//找到入度为0的顶点，然后入栈
    }
    while (!IsEmptyStack(&S)){
        Pop(&S,&i);//弹栈，然后输出
        printf("%c",G.vertex[i]);
        count++;//已经输出的顶点数
        for(int j=0;j<G.vexnum;j++){
            if(G.arcs[i][j].adj==true) {
                indegree[j]--;//删点，减入度
                if(indegree[j]==0)  Push(&S,j);//入度为0再次入栈
            }
        }
    }
    if(count<G.vexnum) return false;//输出数小于顶点数，说明无法进行拓扑排序，具有回路
    else return true;
}
int ve[MAX_VERTEX_NUM];//最早发生时间的数组，也就是从源点到该点的最长路径
bool TopoOrder(AdjMatrix G,Stack *T){//新拓扑，最早事件
    int count=0,i,j;
    int indegree[MAX_VERTEX_NUM];
    Stack S;
    InitStack(T);InitStack(&S);
    FindID(G,indegree);
    for(i=0;i<G.vexnum;i++){
        if(indegree[i]==0) Push(&S,i);
    }
    for(i=0;i<G.vexnum;i++) ve[i]=0;//初始化均为0
    while (!IsEmptyStack(&S)){
        Pop(&S,&i);
        Push(T,i);//按照拓扑排序入栈
        count++;
        for(j=0;j<G.vexnum;j++){
            if(G.arcs[i][j].adj==true) {
                indegree[j]--;
                if(indegree[j]==0)  Push(&S,j);
            }
            if(G.arcs[i][j].adj==true&&ve[i]+G.arcs[i][j].info>ve[j]) ve[j]=ve[i]+G.arcs[i][j].info;//找到最长路径
        }
    }
    if(count<G.vexnum) return false;
    else return true;
}
bool CriticalPath(AdjMatrix G){//利用新拓扑求关键路径
    int i,j,ei,li;
    char tag;
    int vl[MAX_VERTEX_NUM];//最晚发生时间的数组
    Stack T;
    if(!TopoOrder(G,&T)) return false;//先用拓扑排序得到逆拓扑序列T栈
    for(i=0;i<G.vexnum;i++) vl[i]=ve[i];//各个顶点事件vl值初始化为汇点的ve值
    while(!IsEmptyStack(&T)){//逆拓扑排序求各个顶点的vl值
        Pop(&T,&i);
        for(j=0;j<G.vexnum;j++){
            if(G.arcs[i][j].adj==true){
                if(vl[j]-G.arcs[i][j].info<vl[i]) vl[i]=vl[j]-G.arcs[i][j].info;//逆推，取小值
            }
        }
    }
    for(i=0;i<G.vexnum;i++){
        for(j=0;j<G.vexnum;j++){
            if(G.arcs[i][j].adj==true){//ve值等于vl值则是关键路径
                ei=ve[i];li=vl[j]-G.arcs[i][j].info;
                tag=(ei==li)?'*':' ';//'*'标志是关键路径
                printf("%c,%c,%d,%d,%d,%c\n",G.vertex[i],G.vertex[j],G.arcs[i][j].info,ei,li,tag);
            }
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
void ShortestPath_DJS(AdjMatrix G,int v0,WeightType dist[MAX_VERTEX_NUM],SeqList path[MAX_VERTEX_NUM]){
    SeqList S;//已找到最短路径的顶点的集合
    int k;
    for(int i=0;i<G.vexnum;i++){
        InitList(&path[i]);//path里存的是从v0到这个顶点最短的路径
        dist[i]=G.arcs[v0][i].info;//储存距离
        if(dist[i]<INFINITY){
            AddTail(&path[i],G.vertex[v0]);//如果可以相邻，则加进去
            AddTail(&path[i],G.vertex[i]);
        }
    }
    InitList(&S);//再初始化一个表
    AddTail(&S,G.vertex[v0]);//v0当作找到了最短路径
    for(int t=1;t<=G.vexnum-1;t++){//求v0到其他点的最短路径
        int min=INFINITY;
        for(int i=0;i<G.vexnum;i++){
            if(!Member(G.vertex[i],&S)&&dist[i]<min){//该顶点未找到最短路径，找到距离v0最近的顶点k
                k=i;min=dist[i];
            }
        }
        if(min==INFINITY) return;//没有说明没有路径，回退
        AddTail(&S,G.vertex[k]);//k点就是找到了最短路径
        for(int i=0;i<G.vexnum;i++){//以刚找到的k点为基础，再比较以k点为中介到i点的路径长，更短则就换
            if(!Member(G.vertex[i],&S)&&G.arcs[k][i].info!=INFINITY&&(dist[k]+G.arcs[k][i].info<dist[i])){
                dist[i]=dist[k]+G.arcs[k][i].info;
                path[i]=path[k];//换了之后说明i点找到了更短路径，则进行交换
                AddTail(&path[i],G.vertex[i]);//再加上i点
            }
        }
    }
}
void ShortestPath_Floyd(AdjMatrix G,WeightType dist[MAX_VERTEX_NUM][MAX_VERTEX_NUM],SeqList path[MAX_VERTEX_NUM][MAX_VERTEX_NUM]){
    for(int i=0;i<G.vexnum;i++){//初始化dist和path
        for(int j=0;j<G.vexnum;j++){
            InitList(&path[i][j]);
            dist[i][j]=G.arcs[i][j].info;
            if(dist[i][j]<INFINITY){
                AddTail(&path[i][j],G.vertex[i]);
                AddTail(&path[i][j],G.vertex[j]);
            }
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

void bfsKLevel(AdjMatrix G,int v0,int K){//无向图，距离顶点v0的最短路径长度为K的所有顶点
    int v,w;
    Queue Q1,Q2;
    InitQueue(&Q1);//存已访问顶点
    InitQueue(&Q2);//存已访问顶点层号
    for(int i=0;i<G.vexnum;i++){
        visited[i]=false;//初始化访问数组
    }
    visited[v0]=true;int Level=1;
    EnterQueue(&Q1,v0);
    EnterQueue(&Q2,Level);//入队列
    while(!IsEmptyQueue(Q1)){
        DeleteQueue(&Q1,&v);//取出已访问的顶点号
        DeleteQueue(&Q2,&Level);//取出已访问的层号
        w=FirstAdjVertex(&G,G.vertex[v]);//找到第一个顶点
        while(w!=-1){
            if(!visited[w]){
                visited[w]=true;
                if(Level==K) printf("%d",w);//符合条件
                else{
                    EnterQueue(&Q1,w);//不符合就入队，之后再取出来进行循环判断
                    EnterQueue(&Q2,Level+1);
                }
            }
            w=NextAdjVertex(&G,G.vertex[v],G.vertex[w]);//找其余的顶点
        }
    }
}
int path[MAX_VERTEX_NUM];//路径
int n=0;//路径上的顶点数
bool DepthFirstSearchOfHamilton(AdjMatrix G,int v0){
    visited[v0]=true;
    n++;
    path[n]=v0;
    if(n==G.vexnum){//说明找到了路径
        for(int i=1;i<=G.vexnum;i++){
            printf("%d",path[i]);
        }
        return true;
    }
    int w=FirstAdjVertex(&G,G.vertex[v0]);//找第一个邻接点
    while(w!=-1){
        if(!visited[w]&&DepthFirstSearchOfHamilton(G,w)==1) return true;//w没被访问过，再次深度寻找
        w=NextAdjVertex(&G,G.vertex[v0],G.vertex[w]);//如果碰壁则转下一个邻接点，
    }
    visited[v0]=false;//没有邻接点，并且也没找全，那么就换条路，回退顶点
    n--;
    return false;
}
void Hamilton(AdjMatrix G){//求哈密顿路径
    int i=0;
    for(i=0;i<G.vexnum;i++) visited[i]=false;
    n=0;//初始化访问顶点数
    for(i=0;i<G.vexnum;i++) if(DepthFirstSearchOfHamilton(G,i)==true) return;//递归
}

#define MAXLEN 3E38//最大浮点数
int CenterVex(AdjMatrix G){//求中心顶点
    int i,j,k;
    float min,len;
    float A[MAX_VERTEX_NUM][MAX_VERTEX_NUM];//储存i与j之间的最短路径

    for(i=0;i<G.vexnum;i++){//初始化
        for(j=0;j<G.vexnum;j++){
            A[i][j]=G.arcs[i][j].info;
        }
        A[i][i]=0;
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
    printf("1:有向图\n2:无向图\n3:有向网\n4:无向网\n输入想要创建的图:");
    int x;
    scanf("%1d",&x);
    AdjMatrix G;
    switch(x){
        case 1:CreateDG(&G);break;
        case 2:CreateUDG(&G);break;
        case 3:CreateDN(&G);break;
        case 4:CreateUDN(&G);break;
    }
    // printf("深度优先搜索:");
    // DepthFirstSearch(G,0);
    // printf("广度有限搜索:");
    // BreadthFirstSearch(G,0);
    // Path(G,0,4);
    // MiniSpanTree_Prim(G,0);
    // TopoSort(G);
    // CriticalPath(G);
    WeightType dist1[MAX_VERTEX_NUM],dist2[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
    SeqList path1[MAX_VERTEX_NUM],path2[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
    // ShortestPath_DJS(G,0,dist1,path1);
    // for(int i=0;i<G.vexnum;i++){
    //     for(int j=0;j<path1[i].size;j++){
    //         printf("%c",path1[i].a[j]);
    //     }
    //     printf("\n");
    // }
    ShortestPath_Floyd(G,dist2,path2);
    for(int i=0;i<G.vexnum;i++){
        for(int j=0;j<G.vexnum;j++){
            for(int k=0;k<path2[i][j].size;k++){
                printf("%c",path2[i][j].a[k]);
            }
            printf("\n");
        }
    }

    // bfsKLevel(G,1,1);
    // Hamilton(G);
    // printf("中心点坐标:%d",CenterVex(G));
}