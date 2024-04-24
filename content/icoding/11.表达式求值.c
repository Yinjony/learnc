#include <stdio.h>
int main ()
{
  int i;
  float a1,a2,t;
  char a;
  printf("Enter an expression:");
  for(i=1;;i++)
  {
    if(i=1)scanf("%f",&a1);
    for(;;)
    {
      a=getchar();
      if(a=='\n')break;
      scanf("%f",&a2);
      switch(a)
      {
        case '+':a1=a1+a2;break;
        case '-':a1=a1-a2;break;
        case '*':a1=a1*a2;break;
        case '/':a1=a1/a2;break;
      }
    }
    if(a=='\n')break;
  }
  printf("%.1f",a1);
  return 0;
}