#include<stdio.h>
#include<math.h>
int main ()
{
    int i=2,a;
    printf("Enter a number:");
    scanf("%d",&a);
    while (i<=sqrt(a))
    {
        printf("%d\n",i*i);
        i += 2;
    }
    return 0;
}