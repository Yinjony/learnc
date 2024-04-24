#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <math.h>
#define WALL '#'
#define ROUTE '.'
#define RANK 0
void migongbuild(char maze[12][12])//打印迷宫
{
    Sleep(500);
    for(int i=0;i<12;i++){
        for(int j=0;j<12;j++){
            if(maze[i][j]!=WALL&&maze[i][j]!=ROUTE&&maze[i][j]!='\n'){
                printf("\033[31m%3c\033[0m",'X');
            }
            else {
                printf("%3c",maze[i][j]);
            }
            if(j==11){
                printf("\n");
            }
        }
    }
}
void mazeGenerator(char maze[12][12],int i,int j)//生成迷宫
{
   maze[i][j]=ROUTE;
   int direction[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
   for(int i=0;i<4;i++){
    Sleep(100);
    srand(time(NULL));
    int r=rand()%4;
    int t=direction[0][0];
    direction[0][0]=direction[r][0];
    direction[r][0]=t;

    t=direction[0][1];
    direction[0][1]=direction[r][1];
    direction[r][1]=t;
   }
   for(int k=0;k<4;k++){
    int x=i,y=j;
    int range=1+(RANK==0?0:rand()%RANK);
    for(;range>0;range--){
        x+=direction[k][0];
        y+=direction[k][1];
        if(maze[x][y]==ROUTE){
            break;
        }
        int num=0;
        for(int dx=x-1;dx<x+2;dx++){
            for(int dy=y-1;dy<y+2;dy++){
                if(abs(dx-x)+abs(dy-y)==1&&maze[dx][dy]==ROUTE){
                    num++;
                }
            }
        }
        if(num>1){
            break;
        }
        range--;
        maze[x][y]=ROUTE;
    }
    if(range<=0){
        migongbuild(maze);
        mazeGenerator(maze,x,y);
    }
   }
}
void mazeTraverse(char maze[12][12],int i,int j)//走出迷宫的算法用到了递归，所以每次用完函数都要return，这样才能停下来
{
    if(j==11){
        maze[i][j]='X';
        migongbuild(maze);
        return;
    }
    if(j==0){
        maze[i][j]='X';
        migongbuild(maze);
        mazeTraverse(maze,i,j+1);
        return;
    }
    if(maze[i][j]==ROUTE){//顺时针判断
        if(maze[i][j-1]=='X'){
            if(maze[i+1][j]==ROUTE){
                maze[i][j]='X';
                migongbuild(maze);
                mazeTraverse(maze,i+1,j);
                return;
            }
            else if(maze[i][j+1]==ROUTE){
                maze[i][j]='X';
                migongbuild(maze);
                mazeTraverse(maze,i,j+1);
                return;
            }
            else if(maze[i-1][j]==ROUTE){
                maze[i][j]='X';
                migongbuild(maze);
                mazeTraverse(maze,i-1,j);
                return;
            }
            else {
                maze[i][j]='Y';
                migongbuild(maze);
                mazeTraverse(maze,i,j-1);
                return;
            }
        }
        else if(maze[i-1][j]=='X'){
            if(maze[i][j-1]==ROUTE){
                maze[i][j]='X';
                migongbuild(maze);
                mazeTraverse(maze,i,j-1);
                return;
            }
            else if(maze[i+1][j]==ROUTE){
                maze[i][j]='X';
                migongbuild(maze);
                mazeTraverse(maze,i+1,j);
                return;
            }
            else if(maze[i][j+1]==ROUTE){
                maze[i][j]='X';
                migongbuild(maze);
                mazeTraverse(maze,i,j+1);
                return;
            }
            else {
                maze[i][j]='Y';
                migongbuild(maze);
                mazeTraverse(maze,i-1,j);
                return;
            }
        }
        else if(maze[i][j+1]=='X'){
            if(maze[i-1][j]==ROUTE){
                maze[i][j]='X';
                migongbuild(maze);
                mazeTraverse(maze,i-1,j);
                return;
            }
            else if(maze[i][j-1]==ROUTE){
                maze[i][j]='X';
                migongbuild(maze);
                mazeTraverse(maze,i,j-1);
                return;
            }
            else if(maze[i+1][j]==ROUTE){
                maze[i][j]='X';
                migongbuild(maze);
                mazeTraverse(maze,i+1,j);
                return;
            }
            else {
                maze[i][j]='Y';
                migongbuild(maze);
                mazeTraverse(maze,i,j+1);
                return;
            }
        }
        else if(maze[i+1][j]=='X'){
            if(maze[i][j+1]==ROUTE){
                maze[i][j]='X';
                migongbuild(maze);
                mazeTraverse(maze,i,j+1);
                return;
            }
            else if(maze[i-1][j]==ROUTE){
                maze[i][j]='X';
                migongbuild(maze);
                mazeTraverse(maze,i-1,j);
                return;
            }
            else if(maze[i][j-1]==ROUTE){
                maze[i][j]='X';
                migongbuild(maze);
                mazeTraverse(maze,i,j-1);
                return;
            }
            else {
                maze[i][j]='Y';
                migongbuild(maze);
                mazeTraverse(maze,i+1,j);
                return;
            }
        }
    }
    if(maze[i][j]=='X'){//同上
        if(maze[i][j-1]==ROUTE){
            mazeTraverse(maze,i,j-1);
            return;
        }
        else if(maze[i+1][j]==ROUTE){
            mazeTraverse(maze,i+1,j);
            return;
        }
        else if(maze[i][j+1]==ROUTE){
            mazeTraverse(maze,i,j+1);
            return;
        }
        else if(maze[i-1][j]==ROUTE){
            mazeTraverse(maze,i-1,j);
            return;
        }
        else if(maze[i][j-1]=='Y'){
            if(maze[i+1][j]=='X'){
                maze[i][j]='Y';
                mazeTraverse(maze,i+1,j);
                return;
            }
            else if(maze[i][j+1]=='X'){
                maze[i][j]='Y';
                mazeTraverse(maze,i,j+1);
                return;
            }
            else if(maze[i-1][j]=='X'){
                maze[i][j]='Y';
                mazeTraverse(maze,i-1,j);
                return;
            }
        }
        else if(maze[i-1][j]=='Y'){
            if(maze[i][j-1]=='X'){
                maze[i][j]='Y';
                mazeTraverse(maze,i,j-1);
                return;
            }
            else if(maze[i+1][j]=='X'){
                maze[i][j]='Y';
                mazeTraverse(maze,i+1,j);
                return;
            }
            else if(maze[i][j+1]=='X'){
                maze[i][j]='Y';
                mazeTraverse(maze,i,j+1);
                return;
            }
        }
        else if(maze[i][j+1]=='Y'){
            if(maze[i-1][j]=='X'){
                maze[i][j]='Y';
                mazeTraverse(maze,i-1,j);
                return;
            }
            else if(maze[i][j-1]=='X'){
                maze[i][j]='Y';
                mazeTraverse(maze,i,j-1);
                return;
            }
            else if(maze[i+1][j]=='X'){
                maze[i][j]='Y';
                mazeTraverse(maze,i+1,j);
                return;
            }
        }
        else if(maze[i+1][j]=='Y'){
            if(maze[i][j+1]=='X'){
                maze[i][j]='Y';
                mazeTraverse(maze,i,j+1);
                return;
            }
            else if(maze[i-1][j]=='X'){
                maze[i][j]='Y';
                mazeTraverse(maze,i-1,j);
                return;
            }
            else if(maze[i][j-1]=='X'){
                maze[i][j]='Y';
                mazeTraverse(maze,i,j-1);
                return;
            }
        }
    }
}
int main()
{
    printf("\033[2J");//清屏
    /*char maze[12][12]={{WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL},
                       {WALL,ROUTE,ROUTE,ROUTE,WALL,ROUTE,ROUTE,ROUTE,ROUTE,ROUTE,ROUTE,WALL},
                       {ROUTE,ROUTE,WALL,ROUTE,WALL,ROUTE,WALL,WALL,WALL,WALL,ROUTE,WALL},
                       {WALL,WALL,WALL,ROUTE,WALL,ROUTE,ROUTE,ROUTE,ROUTE,WALL,ROUTE,WALL},
                       {WALL,ROUTE,ROUTE,ROUTE,ROUTE,WALL,WALL,WALL,ROUTE,WALL,ROUTE,ROUTE},
                       {WALL,WALL,WALL,WALL,ROUTE,WALL,ROUTE,WALL,ROUTE,WALL,ROUTE,WALL},
                       {WALL,ROUTE,ROUTE,WALL,ROUTE,WALL,ROUTE,WALL,ROUTE,WALL,ROUTE,WALL},
                       {WALL,WALL,ROUTE,WALL,ROUTE,WALL,ROUTE,WALL,ROUTE,WALL,ROUTE,WALL},
                       {WALL,ROUTE,ROUTE,ROUTE,ROUTE,ROUTE,ROUTE,ROUTE,ROUTE,WALL,ROUTE,WALL},
                       {WALL,WALL,WALL,WALL,WALL,WALL,ROUTE,WALL,WALL,WALL,ROUTE,WALL},
                       {WALL,ROUTE,ROUTE,ROUTE,ROUTE,ROUTE,ROUTE,WALL,ROUTE,ROUTE,ROUTE,WALL},
                       {WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL},};*/
    char maze[12][12];//初始化
    for(int i=0;i<12;i++){
        maze[i][0]=WALL;
        maze[11][i]=WALL;
        maze[0][i]=WALL;
        maze[i][11]=WALL;
    }
    srand(time(NULL));
    int enter=rand()%10+1;
    int exit=rand()%10+1;
    int i=enter,j=1;
    mazeGenerator(maze,i,j);
    migongbuild(maze);
    mazeTraverse(maze,enter,0);
}
/*     原路返回的算法
       else if(maze[i][j-1]=='X'){
            maze[i][j]='Y';
            migongbuild(maze);
            mazeTraverse(maze,i,j-1);
            return;
        }
        else if(maze[i+1][j]=='X'){
            maze[i][j]='Y';
            migongbuild(maze);
            mazeTraverse(maze,i+1,j);
            return;
        }
        else if(maze[i][j+1]=='X'){
            maze[i][j]='Y';
            migongbuild(maze);
            mazeTraverse(maze,i,j+1);
            return;
        }
        else if(maze[i-1][j]=='X'){
            maze[i][j]='Y';
            migongbuild(maze);
            mazeTraverse(maze,i-1,j);
            return;
        }*/
        /*srand(time(NULL));
    int enter=rand()%10+1;//标定入口
    maze[enter][0]=ROUTE;
    maze[enter-1][0]=WALL;
    maze[enter+1][0]=WALL;
    maze[enter][1]=ROUTE;
    int t;
    for(int i=enter,j=1;;){//出口路线
        Sleep(100);//让时间改变。
        srand(time(NULL));
        t=rand()%3;
        if(t==0&&maze[i-1][j]!=ROUTE&&maze[i-1][j]!=WALL&&i-1>0){
            //migongbuild(maze);
            maze[i-1][j]=ROUTE;
            if(maze[i][j-1]!=ROUTE){
                maze[i][j-1]=WALL;
            }
            else {
                maze[i+1][j]=WALL;
                maze[i+1][j+1]=WALL;
            }
            if(maze[i][j+1]!=ROUTE){
                maze[i][j+1]=WALL;
            }
            i--;
        }
        if(t==1&&maze[i][j+1]!=ROUTE&&maze[i][j+1]!=WALL&&j+1<12){
            //migongbuild(maze);
            maze[i][j+1]=ROUTE;
            if(maze[i-1][j]!=ROUTE){
                maze[i-1][j]=WALL;
            }
            else {
                maze[i][j-1]=WALL;
                maze[i+1][j-1]=WALL;
            }
            if(maze[i+1][j]!=ROUTE){
                maze[i+1][j]=WALL;
            }
            else {
                maze[i][j-1]=WALL;
                maze[i-1][j-1]=WALL;
            }
            j++;
        }
        if(t==2&&maze[i+1][j]!=ROUTE&&maze[i+1][j]!=WALL&&i+1<11){
            //migongbuild(maze);
            maze[i+1][j]=ROUTE;
            if(maze[i][j+1]!=ROUTE){
                maze[i][j+1]=WALL;
            }
            if(maze[i][j-1]!=ROUTE){
                maze[i][j-1]=WALL;
            }
            else {
                maze[i-1][j]=WALL;
                maze[i-1][j+1]=WALL;
            }
            i++;
        }
        if(j==11){
            maze[i-1][j]=WALL;
            maze[i+1][j]=WALL;
            break;
        }
    }
    for(int j=0;j<12;j++){
        maze[0][j]=WALL;
        maze[11][j]=WALL;
    }
    for(int i=0;i<12;i++){
        if(maze[i][0]!=ROUTE){
            maze[i][0]=WALL;
        }
        if(maze[i][11]!=ROUTE){
            maze[i][11]=WALL;
        }
    }*/
    