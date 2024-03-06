#include <stdio.h>
int main()
{
  char a[100];
  int i,j;
  printf("Enrter a message:");
  for(i=0;(a[i]=getchar())!='\n';i++);
  printf("Reversal is:");
  for(;i-1>=0;i--)
  printf("%c",a[i-1]);
  return 0;
}