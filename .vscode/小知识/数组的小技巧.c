#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 7
void strange(const int b)//const是将形参值固定，这样被调用的函数就无法改变数组里面的值了。
{
    b[0]=1;//这是错的。
}
int main()
{
    int frequency[SIZE]={0};
    srand(time(NULL));
    for(int roll=1;roll<=60000000;roll++)
    {
        int face=1+rand()%6;
        frequency[face]++;//注意这个数组里面的值还可以这样够用，省去Switch语句了，比较方便。
    }
    printf("%s%17s\n","Face","Frequency");
    for(int face=1;face<SIZE;face++)
    {
        printf("%4d%17d\n",face,frequency[face]);
    }
    int i;
    scanf("%d",&i);
    int a[i];//可以自定义数组长度了，这个顺序似乎不能变。
    
}