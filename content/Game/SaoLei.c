#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include <time.h>
#define ROW 8
#define COL 8
#define BOOMNUM 10
#define BOOM '*'
#define FLAG 'P' 
int SCORE=0;

void Create(char arr[ROW][COL]){//创建雷阵
    srand((unsigned)time(NULL));
    for(int i=0;i<ROW;i++){
        for(int j=0;j<COL;j++){
            arr[i][j]='0';
        }
    }
    int i=0;
    while(i<BOOMNUM){
        int m=rand()%ROW;
        int n=rand()%COL;//随机数
        if(arr[m][n]!=BOOM){//防止重复
            arr[m][n]=BOOM;
            i++;

            if(m-1>=0&&arr[m-1][n]!=BOOM) arr[m-1][n]++;//计算
            if(n-1>=0&&arr[m][n-1]!=BOOM) arr[m][n-1]++;
            if(m+1<ROW&&arr[m+1][n]!=BOOM) arr[m+1][n]++;
            if(n+1<COL&&arr[m][n+1]!=BOOM) arr[m][n+1]++;
            if(m-1>=0&&n-1>=0&&arr[m-1][n-1]!=BOOM) arr[m-1][n-1]++;
            if(m-1>=0&&n+1<COL&&arr[m-1][n+1]!=BOOM) arr[m-1][n+1]++;
            if(m+1<ROW&&n-1>=0&&arr[m+1][n-1]!=BOOM) arr[m+1][n-1]++;
            if(m+1<ROW&&n+1<COL&&arr[m+1][n+1]!=BOOM) arr[m+1][n+1]++;
        }
    }

}

void Init(char show[ROW][COL]){//初始化展示的雷阵
    for(int i=0;i<ROW;i++){
        for(int j=0;j<COL;j++){
            show[i][j]=' ';
        }
    }
}

void Print(char show[ROW][COL]){//普通打印
    printf("╔═══╦═══╦═══╦═══╦═══╦═══╦═══╦═══╦═══╗\n");
    for(int i=0;i<=ROW;i++){
        if(i==0) printf("║\033[31m%2d\033[0m ║",i);//坐标轴
        else printf("\033[31m%2d\033[0m ║",i);
    }
    printf("\n╠═══╬═══╬═══╬═══╬═══╬═══╬═══╬═══╬═══╣\n");
    for(int i=0;i<ROW;i++){
        printf("║\033[31m%2d\033[0m ",i+1);//坐标轴
        for(int j=0;j<COL;j++){
            if(j==0) {
                if(show[i][j]==FLAG){
                    printf("║\033[32m%2c\033[0m ║",show[i][j]);
                }else printf("║%2c ║",show[i][j]);
            }
            else{
                if(show[i][j]==FLAG){
                    printf("\033[32m%2c\033[0m ║",show[i][j]);
                }else printf("%2c ║",show[i][j]);
            } 
        }
        printf("\n");
        if(i<ROW-1) printf("╠═══╬═══╬═══╬═══╬═══╬═══╬═══╬═══╬═══╣\n");
        else printf("╚═══╩═══╩═══╩═══╩═══╩═══╩═══╩═══╩═══╝\n");
    }
}
void PrintFlase(char show[ROW][COL],char arr[ROW][COL]){//失败时候的打印
    printf("╔═══╦═══╦═══╦═══╦═══╦═══╦═══╦═══╦═══╗\n");
    for(int i=0;i<=ROW;i++){
        if(i==0) printf("║\033[31m%2d\033[0m ║",i);
        else printf("\033[31m%2d\033[0m ║",i);
    }
    printf("\n╠═══╬═══╬═══╬═══╬═══╬═══╬═══╬═══╬═══╣\n");
    for(int i=0;i<ROW;i++){
        printf("║\033[31m%2d\033[0m ",i+1);
        for(int j=0;j<COL;j++){
            if(j==0) {
                if(show[i][j]==FLAG){
                    printf("║\033[32m%2c\033[0m ║",show[i][j]);
                }else if(arr[i][j]==BOOM){//打印雷
                    printf("║\033[31m%2c\033[0m ║",arr[i][j]);
                }else printf("║%2c ║",show[i][j]);
            }
            else{
                if(show[i][j]==FLAG){
                    printf("\033[32m%2c\033[0m ║",show[i][j]);
                }else if(arr[i][j]==BOOM){
                    printf("\033[31m%2c\033[0m ║",arr[i][j]);
                }
                else printf("%2c ║",show[i][j]);
            } 
        }
        printf("\n");
        if(i<ROW-1) printf("╠═══╬═══╬═══╬═══╬═══╬═══╬═══╬═══╬═══╣\n");
        else printf("╚═══╩═══╩═══╩═══╩═══╩═══╩═══╩═══╩═══╝\n");
    }
}
void Digui(char arr[ROW][COL],char show[ROW][COL],int row,int col){//递归算法
    show[row][col]=arr[row][col];
    if(arr[row][col]=='0'){//开始递归
        if(show[row+1][col+1]==' ') Digui(arr,show,row+1,col+1);
        if(show[row+1][col]==' ') Digui(arr,show,row+1,col);
        if(show[row+1][col-1]==' ') Digui(arr,show,row+1,col-1);
        if(show[row][col+1]==' ') Digui(arr,show,row,col+1);
        if(show[row][col-1]==' ') Digui(arr,show,row,col-1);
        if(show[row-1][col+1]==' ') Digui(arr,show,row-1,col+1);
        if(show[row-1][col]==' ') Digui(arr,show,row-1,col);
        if(show[row-1][col-1]==' ') Digui(arr,show,row-1,col-1);
    }else{
        return;
    }
}

bool Game(char arr[ROW][COL],char show[ROW][COL],int row,int col,int x){
    if(x==1){//插旗
        show[row][col]=FLAG;
        if(arr[row][col]==BOOM) SCORE++;
        return true;
    }else if(arr[row][col]==BOOM){//爆炸
        for(int i=0;i<ROW;i++){
                for(int j=0;j<COL;j++){
                    if(arr[i][j]==BOOM){
                        show[i][j]=BOOM;//全部雷显示
                    }
                }
            }
        return false;
    }else{
        Digui(arr,show,row,col);//递归
        return true;
    }
}



int main(){//主函数
    char arr[ROW][COL];//雷阵
    Create(arr);
    char show[ROW][COL];//用来显示的雷阵
    Init(show);
    int row,col;
    int x;
    do{
        printf("\033[2J");//清屏
        Print(show);
        printf("请输入操作位置:");
        scanf("%1d%1d",&row,&col);

        while(row<1||row>ROW||col<1||col>COL){
            printf("位置不正确请重新输入:");
            scanf("%1d%1d",&row,&col);
        }

        while(show[row-1][col-1]!=' '){
            printf("此位置已操作请重新输入:");
            scanf("%1d%1d",&row,&col);
        }
        
        printf("请输入操作(1插旗/0点击):");
        scanf("%1d",&x);
    }while(Game(arr,show,row-1,col-1,x)&&SCORE<BOOMNUM);

    if(SCORE<BOOMNUM) {
        PrintFlase(show,arr);
        printf("失败...\n得分:%d",SCORE);
    }
    else printf("成功!\n得分:%d",SCORE);
}

