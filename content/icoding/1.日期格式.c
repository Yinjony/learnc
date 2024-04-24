#include <stdio.h>
int main()
{   
   int m,y,d;
   printf("Enter a date:");
   scanf("%d/%d/%d",&m,&d,&y);
   printf("You entered the date%d%02d%02d",y,m,d);
   return 0;
}