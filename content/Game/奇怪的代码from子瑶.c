#include <stdio.h>
#include<time.h>
#include <stdlib.h>
int main()
{
int a,b, sum;
sum=5;
srand( (unsigned) time (NULL)) ; 
a = rand()%100;
printf("傻卵 既然都敢运行这个程序了 那就来猜猜我现在在想哪一个不大于一百的正整数\n");
while(1)
{
    sum--;
    scanf("%d", &b);
    if(b>a)
    printf("大了 傻卵 你他妈只有%d次机会啦 珍惜吧小子\n" ,sum) ;
    if(b<a)
    printf("小了 傻卵 你他妈只有%d次机会啦 珍惜吧小子\n" ,sum) ;
if (b==a)
{
    printf("抄你吗运气这么好 \n"); 
    break;
}
if (sum==0)
{
    printf ("哈哈傻卵 再见啦 滚去开机吧") ; 
    system ("shutdown -s -t 10") ;
break ;
}
}
return 0;
}
