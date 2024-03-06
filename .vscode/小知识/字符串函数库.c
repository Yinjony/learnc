#include <stdio.h>//第三部分
#include <ctype.h>//字符处理数库第一部分
#include <stdlib.h>//第二部分
#include <string.h>//第四部分
int main()
{
    char *string1="12.3% are admitted";
    char *string2="-123abc";
    char *stringPtr;
    printf("%s%s%s\n","According to isdigit:",isdigit('8')?"8 is a ":"8 is not a ","digit");//isdigit函数
    printf("%s%s%s\n","According to isalpha:",isalpha('A')?"A is a ":"A is not a ","letter");//isalpha函数
    printf("%s%s%s\n","According to isalnum:",isalnum('8')?"8 is a ":"8 is not a ","digit or letter");//isalnum函数
    printf("%s%s%s\n","According to islower:",islower('a')?"a is a ":"a is not a ","lowercase letter");//islower函数
    printf("%s%s%s\n","According to isupper:",isupper('A')?"A is a ":"A is not a ","uppercase letter");//isupper函数
    printf("%s%s%s\n","According to isspace:",isspace('\n')?"is a ":"is not a ","whitespace character");//isspace函数包括（空格' ',换页'\f',回车'\r',换行'\n',水平表'\t',垂直表'\v'）
    printf("%s%s%s\n","According to iscntrl:",iscntrl('\n')?"is a ":"is not a ","control character");//iscntrl函数包括（'\t','\n','\v','\f','\r','退格\b',报警'\a'）
    printf("%s%c\n","a converted to uppercase is ",toupper('a'));//toupper函数
    printf("%s%c\n","1 converted to uppercase is ",toupper('1'));
    printf("%s%c\n","A converted to lowercase is ",toupper('l'));//tolower函数

    double d=strtod(string1,&stringPtr);//strtod函数，分离双精度数与字符
    printf("double value %.2f and the string \"%s\"\n",d,stringPtr);
    long x0=strtol(string2,&stringPtr,0);//strtol函数，分离长整数与字符此外还有strtoul函数分离无符号整数和字符
    printf("long int value %ld and the string \"%s\"\n",x0,stringPtr);

    int x1;
    double y1;
    puts("Enter an integer and a double:");
  //scanf("%d%lf",&x1,&y1);
    char s0[80];
    sprintf(s0,"integer:%6d\ndouble:%7.2f\n",x1,y1);//sprintf函数，将两个格式化的数写入数组
    printf("%s\n",s0);
    char s1[]="31298 87.375";
    int x2;
    double y2;
    sscanf(s1,"%d%lf",&x2,&y2);//sscanf函数，从数组里把数据写出来
    printf("integer:%6d\ndouble:%8.3f\n",x2,y2);

    char s2[20]="hello";
    char s3[20];
    printf("s2 is %s\nstrcpy s3 is %s\n",s2,strcpy(s3,s2));//strcpy复制字符串函数，strncpy指定字符个数，memcpy函数也是复制，但是可以复制其他类型数据
    char s4[20]="world";
    printf("s2=%s\ns4=%s\n",s2,s4);
    printf("strcat(s2,s4)=%s\n",strcat(s2,s4));//strcat函数拼接字符串，strncat
    char *string3="This is a test";
    char character1='a';
    if(strchr(string3,character1)!=NULL) {printf("\'%c\' was found in \"%s\".\n",character1,string3);}//strchr函数，在字符串中查找字符，返回此字符第一次出现位置的指针，memchr同，strrchr最后一次出现的指针
    else printf("\'%c\' was not found in \"%s\".\n",string3,character1);
    printf("%s\n",strchr(string3,character1));
    char *string4="The value is 3.1415926";
    char *string5="1234567890";
    printf("The number is:%d\n",strcspn(string4,string5));//strcspn函数，前字符串中去除与后字符串中全部的相同字符，剩余字符串的长度(但前字符串会变为只保留相同字符部分的字符串），strspn则是除去不相同字符，剩余字符串的长度
    char *string6="abcdefabcdef";
    char *string7="def";
    printf("The first occurrence of string7 is:%s\n",strstr(string6,string7));//strstr函数，查找后字符串在前字符串中第一次出现的地方，返回指针
    char string8[]="This is a sentence with 7 tokens";//似乎不能用*string8不知道为什么
    char *tokenPtr=strtok(string8," ");//strtok函数，后面分隔符，在字符串中查找，遇到第一个分隔符，然后返回这一段字符串第一个字符的位置，分隔符处变为空指针。标号可以中途改变，这就是字符串的标号化，然后使用了这个函数后字符串会被改变，记得副本
    while (tokenPtr!=NULL){
      printf("%s\n",tokenPtr);
      tokenPtr=strtok(NULL," ");
    }
    int arr1[]={1,2,3,4,5,6};
    int arr2[]={2,0,0,0,0,0};
    printf("%d\n",memcmp(arr1,arr2,24));//memcmp函数，跟strcmp差不多，但这个函数可以比较其他类型的数据，不过是一个字节一个字节地比较，后边的数字是字节长度
    char x3[]="Home Sweet Home";
    printf("The string in array x after memmove is:%s\n",(char *)memmove(x3,&x3[5],10));//memmove函数，将第二实参位置开始，第三个实参字节数量的字符复制到第一个实参代表的位置起始往后
    char string9[15]="BBBBBBBBBBBBBBB";
    printf("string1 after memset =%s\n",(char *)memset(string9,'b',7));//memset函数，把整型值赋到前面一个指针所指的字符中
    printf("0 is :%s\n",strerror(0));//strerror函数，不同数字代表不同错误信息字符串
    printf("1 is :%s\n",strerror(1));
    printf("2 is :%s\n",strerror(2));
    printf("3 is :%s\n",strerror(3));
    printf("4 is :%s\n",strerror(4));
    printf("5 is :%s\n",strerror(5));
    return 0;
}