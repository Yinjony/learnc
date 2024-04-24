#include <stdio.h>
int main ()
{
    int f,c;
    printf("Enter a wind speed:");
    scanf("%d",&f);
    if(f<1) c=0;
    if(f>=1&&f<=3) c=1;
    if(f>=4&&f<=27) c=2;
    if(f>=28&&f<=47) c=3;
    if(f>=48&&f<=63) c=4;
    if(f>63) c=5;
    switch(c)
    {
        case 0:printf("Calm");break;
        case 1:printf("Light air");break;
        case 2:printf("Breeze");break;
        case 3:printf("Gale");break;
        case 4:printf("Storm");break;
        case 5:printf("Hurricane");break;
    }
    return 0;
}