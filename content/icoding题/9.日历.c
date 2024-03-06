#include <stdio.h>
int main ()
{   
    int d,p,i,t;
    printf("Enter number of days in month:");
    scanf("%d",&d);
    printf("Enter starting day of the week(1=Sun,7=Sat):");
    scanf("%d",&p);
    printf("日一二三四五六\n");
    for (i=1;i<=3*(p-1)-2;i++)printf(" ");
    for (t=1;t<=d;t++)
    {
        printf("%2d",t);
        if((t+p-1)%7==0) printf("\n");
    }
    return 0;
}