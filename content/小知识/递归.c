//用递归的方法求n！
#include <stdio.h>
long fac(int n)
{
    long f;
    if(n<0)
          printf("n<0,data error!");
    else if(n==0,n==1)
          f=1;
    else f=fac(n-1)*n;
    return(f);
}
int main()
{
    int n,y;
    printf("input an integer nummber:");
    scanf("%d",&n);
    y=fac(n);
    printf("%d!=%ld\n",n,y);
    return 0;
}