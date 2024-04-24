#include <stdio.h>
int main()
{
   int t1,t2,a;
   printf("Enter a 24-hour time:");
   scanf("%d:%d",&t1,&t2);
   if(t1==0) a=0;
   if(t1>0&&t1<12) a=1;
   if(t1==12) a=2;
   if(t1>12) a=3;
   switch (a)
   {
   case 0:printf("Equivalent 12-hour time:12:%02d AM",t2); break;
   case 1:printf("Equivalent 12-hour time:%d:%02d AM",t1,t2); break;
   case 2:printf("Equivalent 12-hour time:12:%02d PM",t2); break;
   case 3:printf("Equivalent 12-hour time:%d:%02d PM",t1-12,t2); break;
   
   default:
      break;
   }
   return 0;
}