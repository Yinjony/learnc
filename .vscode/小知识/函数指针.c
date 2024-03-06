#include <stdio.h>
void f1(int a)
void f2(int b)
void f2(int c)
max(int a,int b)
int main()
{
    void(*f[3])(int)={f1,f2,f3};//进行函数指针的定义。
    int choice;
    scanf("%d",&choice);
    (*f[choice])(choice);//输入数字来选择运行的函数。
    int (*p)(int int);//定义指向函数的指针，所以同样的函数都可以放在一个指针函数数组中
    p=max;//将函数的地址赋给p
    return 0;
}