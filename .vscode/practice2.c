#include <stdio.h>
#include <math.h>
#include <string.h>
int main() {
    char *string4="The value is 3.1415926";
    char *string5="1234567890";
    printf("The number is:%d\n",strcspn(string4,string5));
    printf("%s",string4);
    return 0;
}
