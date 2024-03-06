#include <stdio.h>
int main()
{
  char a[100];
  int i,j,k;
  printf("Enter message to be encrypted:");
  for(i=0;(a[i]=getchar())!='\n';i++);
  printf("Enter shift amount(1-25):");
  scanf("%d",&k);
  printf("Encrypted message:");
  for(i=0;a[i]!='\n';i++)
  {
    if(a[i]>='A'&&a[i]<='Z'||a[i]>='a'&&a[i]<='z')
    {
      if(a[i]>='A'&&a[i]<='Z')
      {
        if(a[i]+k>='A'&&a[i]+k<='Z')
        printf("%c",a[i]+k);
        else printf("%c",a[i]-(26-k));
      }
      if(a[i]>='a'&&a[i]<='z')
      {
        if(a[i]+k>='a'&&a[i]+k<='z')
        printf("%c",a[i]+k);
        else printf("%c",a[i]-(26-k));
      }
    }
    else printf("%c",a[i]);
  }
  return 0;
}