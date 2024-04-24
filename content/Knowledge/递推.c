//用递推的方法求n！
#include <stdio.h>
long fac(int n)
{
    int i;
    long fac=1;
    for(i=1;i<=n;i++)
        fac=fac*i;
    return fac;
}
int main()
{
    long fac (int n);
    int n;
    long fact=0;
    printf("please input a integer number:");
    scanf("%d",&n);
    fact=fac(n);
    printf("%d!=%ld\n",n,fact);
    return 0;
}