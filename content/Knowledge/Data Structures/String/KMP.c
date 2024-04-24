//KMP算法
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAXSIZE 100
typedef struct
{
    char data[MAXSIZE];
    int length;
}SqString;

//建议推一下"aaaaab"和"abcabmn"
void GetNext(SqString t,int next[]){//求子串的next数组
    int j=0,k=-1;
    next[0]=-1;//赋初值
    while(j<t.length-1){
        if(k==-1||t.data[j]==t.data[k]){//相同，则均向后移一位，然后next[j]被赋值
            j++;
            k++;
            next[j]=k;
        }else{//不相同，则k的位置回溯到最初相同的位置，跟与主串比对过程类似
            k=next[k];
        }
    }
}
//改进，想理解请推"ababaab"
void GetNextval(SqString t,int nextval[]){
    int j=0,k=-1;
    nextval[0]=-1;//赋初值
    while(j<t.length-1){
        if(k==-1||t.data[j]==t.data[k]){//相同，则均向后移一位
            j++;
            k++;
            if(t.data[j]!=t.data[k]){//各自后移后如果字符不同，也就是回溯后的字符与原字符不同，则正常赋值
                nextval[j]=k;
            }else{//但如果相同，则没有必要在从那个位置比较，因为原字符就已经不与主串里的字符相同了
                nextval[j]=nextval[k];//所以此处直接获得k处字符的next值
            }
        }else{//不相同，则k的位置回到最初相同的位置，跟与主串比对过程类似
            k=nextval[k];
        }
    }
}

int KMPIndex(SqString s,SqString t){//使用KMP算法
    int nextval[MAXSIZE],i=0,j=0;
    GetNextval(t,nextval);//获得nextval数组（这里使用的是改进后的KMP算法）
    // GetNext(t,nextval);
    while(i<s.length&&j<t.length){
        if(j==-1||s.data[i]==t.data[j]){//相同则向后移
            i++;
            j++;
        }else j=nextval[j];//不同则子串回溯，有可能会回溯到-1，然后两个串再各自后移
    }
    if(j>=t.length) return i-t.length;
    else return -1;
}

int main(){//测试
    SqString s,t;
    char c;
    printf("输入主串长度：");
    scanf("%d",&(s.length));
    printf("输入主串：");
    c=getchar();//这里输入字符，会读入换行符，要提前读入
    for(int i=0;i<s.length;i++){
        s.data[i]=getchar();
    }
    
    printf("输入子串长度：");
    scanf("%d",&(t.length));
    printf("输入子串：");
    c=getchar();
    for(int i=0;i<t.length;i++){
        t.data[i]=getchar();
    }
    printf("比对结果:%d",KMPIndex(s,t));
}