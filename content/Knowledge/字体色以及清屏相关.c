#include <stdio.h>
#include <windows.h>//system以及sleep函数在这里
//\033[参数1;参数2;参数3m
//显示方式 字体颜色 背景色
/*
\033[nA 光标上移n行 光标的移动配合scanf函数使用，然后它的输入会覆盖之前的内容
\033[nB 光标下移n行
\033[nC 光标右移n列
\033[nD 光标左移n列
\033[y:xH 设置光标的位置（y行，x列）
\033[s 保存光标的位置
\033[u 恢复光标的位置
\033[?25l 隐藏光标
\033[?25h 显示光标
*/

void ziti(void)
{
   printf("\033[30m黑色\t");//字体
   printf("\033[31m红色\t");
   printf("\033[32m绿色\t");
   printf("\033[33m黄色\t");
   printf("\033[34m蓝色\t");
   printf("\033[35m紫色\t");
   printf("\033[36m浅蓝色\t");
   printf("\033[37m白色\t");
   printf("\033[1m高亮\t");
   printf("\033[2m低亮\t");
   printf("\033[4m下划线\t");
   printf("\033[5m闪烁\t");
   printf("\033[7m反显\t");//没啥卵用，只是白底黑字
   printf("\033[8m消隐\t");//TM没了似乎把PS那一行也消没了
}
void beijing(void)
{
   printf("\033[40m");//字的背景颜色之黑
   printf("\033[41m");//红
   printf("\033[42m");//绿
   printf("\033[43m");//黄
   printf("\033[44m");//蓝
   printf("\033[45m");//紫
   printf("\033[46m");//浅蓝
   printf("\033[47m");//白
}

int main()
{
   printf("\033[2J");//清屏函数
   system("HELP");
   printf("请输入一串数字hhh\033[3D");
   int m;
   scanf("%d",&m);
   return 0;         
}   