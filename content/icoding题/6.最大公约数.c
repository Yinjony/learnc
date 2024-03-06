#include<stdio.h>
int main ()
{
    int m,n,GCD,t;
    printf("Enter two integers:");
    scanf("%d %d",&m,&n);
    for (;n!=0;) {t=m%n;m=n;n=t;}
    printf("Greatest common divisor:%d",m);
    return 0; 

}