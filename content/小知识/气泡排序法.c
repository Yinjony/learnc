//n个人，年龄不同，将年龄从大到小排列//
#include <stdio.h>
int main()
{
    int a[10];
    int i,j,t;
    printf("input 10 numbers:\n");
    for(i=0;i<10;i++)
    scanf("%d",&a[i]);
    printf("\n");
    for(j=0;j<9;j++)          //9次循环，9次比较
      for(i=0;i<9-j;i++)      //每次比较，进行9-j次比较（10个数，比较9次）
      if(a[i]>a[i+1])
      {
        t=a[i];
        a[i]=a[i+1];
        a[i+1]=t;
      }
      printf("the sorted numbers:\n");
      for(i=0;i<10;i++)
      printf("%d",a[i]);
      printf("\n");
    return 0;
}