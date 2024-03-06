#include <stdio.h>
int main()
{   int I,t;
    char c;
    printf("Enter phone number:");
    for(;(c=getchar())!='\n';)
    {if (c>='A'&&c<='Z') 
      { switch (c)
      {
      case 'A':
      case 'B':
      case 'C':c=2;break;
      case 'D':
      case 'E':
      case 'F':c=3;break;
      case 'G':
      case 'H':
      case 'I':c=4;break;
      case 'J':
      case 'K':
      case 'L':c=5;break;
      case 'M':
      case 'N':
      case 'O':c=6;break;
      case 'P':
      case 'Q':
      case 'R':
      case 'S':c=7;break;
      case 'T':
      case 'U':
      case 'V':c=8;break;
      case 'W':
      case 'X':
      case 'Y':
      case 'Z':c=9;break;
      default:
         break;
      }
        printf("%d",c);
      } 
    if(c=='0') printf("0");
    if(c=='1') printf("1");
    if(c=='2') printf("2");
    if(c=='3') printf("3");
    if(c=='4') printf("4");
    if(c=='5') printf("5");
    if(c=='6') printf("6");
    if(c=='7') printf("7");
    if(c=='8') printf("8");
    if(c=='9') printf("9");
    if(c=='-')printf("%c",c);
    }
    return 0;   
}