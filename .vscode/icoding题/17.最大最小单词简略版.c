#include <stdio.h>
#include <string.h>
int main()
{
  char a[10][20];
  int i,j,t,k;
  char (*p)[20],(*S)[20],(*L)[20];
  p=a+1,S=a,L=a;
  for(i=0;;i++)
  {
    printf("Enter word:");
    for(j=0;(a[i][j]=getchar())!='\n';j++);
    if(j==4) break;
  }
  for(t=1;t<=i;t++)
  {
    if(k=strcmp(*S,*p)>=0){S=p;p=a+1+t;}
    else {S=S;p=a+1+t;}
  }
  p=a+1;
  for(t=1;t<=i;t++)
  {
    if(k=strcmp(*L,*p)<=0){L=p;p=a+1+t;}
    else {L=L;p=a+1+t;} 
  }
  printf("Smallest word:%s",*S);
  printf("Largest word:%s",*L);
  return 0;
}