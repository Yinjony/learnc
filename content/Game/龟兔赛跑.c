#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define H "      H"
#define T "      T"
#define TIE "   OUCH"
#define NONE "       "
int tortoise(void)//乌龟的移动方式
{
   srand(time(NULL));
   int i=rand()%10+1;
   if(i>=1&&i<=5){
      puts("乌龟快速爬行。");
      return 3;
   }
   else if(i>=6&&i<=7){
      puts("乌龟滑倒。");
      return -6;
   }
   else if(i>=8&&i<=10){
      puts("乌龟缓慢爬行。");
      return 1;
   }
   else {
      puts("错误！");
      return 0;
   }
}
int hare(void)//兔子的移动方式
{
   srand(time(NULL));
   int i=rand()%10+1;
   if(i>=1&&i<=2){
      puts("兔子睡觉。");
      return 0;
   }
   else if(i>=3&&i<=4){
      puts("兔子大跳。");
      return 9;
   }  
   else if(i==5){
      puts("兔子严重滑倒。");
      return -12;
   }
   else if(i>=6&&i<=8){
      puts("兔子小跳。");
      return 1;
   }
   else if(i>=9&&i<=10){
      puts("兔子轻微滑倒。");
      return -2;
   }
   else {
      puts("错误!");
      return 0;
   }
}
int move(char *place[70],int *t,int *h)//进行移动
{
   place[(*t)-1]=NONE;
   place[(*h)-1]=NONE;
   *t+=tortoise();
   *h+=hare();
   if(*t<1){
      *t=1;
   }
   if(*h<1){
      *h=1;
   }
   if(*t>=70&&*h>=70){
      puts("It's a tie.");
      return 0;
   }
   else if(*t>=70){
      puts("TORTOISE WINS!!!YAY!!!");
      return 0;
   }
   else if(*h>=70){
      puts("Hare wins.Yuch!");
      return 0;
   }
   if(*t==*h){//相等
      place[*t-1]=TIE;
   }
   else {
      place[*t-1]=T;
      place[*h-1]=H;
   }
   return 1;
}
void print(char *place[70])//打印赛道
{
   int num=1;
   for(int i=0;i<7;i++){
      for(int j=0;j<10;j++){
         printf("═════════╦");
      }
      for(int j=0;j<10;j++){
         //printf("%2d%7s‖",num++,place[i*10+j]);
         printf("%2d",num++);
         printf("\033[31m%7s\033[0m‖",place[i*10+j]);
      }
      for(int j=0;j<10;j++){
         printf("═════════╩");
      }
   }
}
int main()
{
   printf("\033[2J");//清屏。
   int t=1,h=1;
   int *p=&t,*q=&h;//使用了指针和字符串数组
   char *place[70];
   place[0]=TIE;
   for(int i=1;i<70;i++){//初始化字符串数组
      place[i]=NONE;
   }
   puts("温馨提示:进行移动(1)/终止比赛(0)");
   puts("BANG !!!");
   puts("AND THEY'RE OFF !!!!!");
   print(place);
   int a;
   do{
      scanf("%d",&a);
      if(a!=1&&a!=0){
         puts("请重新输入！");
         continue;
      }
      else if(a==1){
         if(move(place,p,q)){
            print(place);
         }
         else exit(EXIT_SUCCESS);
      }
      else exit(EXIT_SUCCESS);
   }while(1);
   return 0;
}