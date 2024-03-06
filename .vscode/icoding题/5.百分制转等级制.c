#include <stdio.h>
int main ()
{
    int c,t;
    printf("Enter numerical grade:");
    scanf("%d",&c);
    if(c>=90&&c<=100) t=0;
    if(c>=80&&c<=89) t=1;
    if(c>=70&&c<=79) t=2; 
    if(c>=60&&c<=69) t=3;
    if(c>=0&&c<=59) t=4;
    if(c<0|| c>100) t=5;
    switch(t)
    {
        case 0:printf("Letter grade:A");break;
        case 1:printf("Letter grade:B");break;
        case 2:printf("Letter grade:C");break;
        case 3:printf("Letter grade:D");break;
        case 4:printf("Letter grade:F");break;
        case 5:printf("Error,grade must be between 0 and 100");break;
    }
    return 0;
}