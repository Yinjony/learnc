#include <stdio.h>
int main()
{
  char a[10];
  puts("Enter string");
  scanf("%9[aeiou]",a);//扫描集%n[]，方括号里的数据相同的便会录入到字符串里，直到遇到第一个不相同的字符停止录入，此外还有[^]逆扫描集，不同的字符录入。
  printf("%s",a);
  int month=0,day=0,year=0;
  puts("Enter a date in the form mm-dd-yyyy: ");
  scanf("%d%*c%d%*c%d",&month,&day,&year);//*赋值抑制字符，可以停止录入这个字符
  printf("month=%d,day=%d,year=%d",month,day,year);
  return 0;
}