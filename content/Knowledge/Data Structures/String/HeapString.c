//堆串，动态申请字符串的长度
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct{
    char *ch;
    int len;
}HString;
void StrInit(HString *s){//需要初始化
    s->ch=NULL;
    s->len=0;
}

bool StrInsert(HString *s,int pos,HString *t){//堆串插入函数
    int i;
    char *temp;
    if(pos<0||pos>s->len||s->len==0) return false;//判断是否合理
    
    temp=(char*)malloc(s->len+t->len);//整一个更长的长度
    if(temp==NULL) return false;

    for(i=0;i<pos;i++) temp[i]=s->ch[i];//开始进行填入
    for(i=0;i<t->len;i++) temp[i+pos]=t->ch[i];
    for(i=pos;i<s->len;i++) temp[i+t->len]=s->ch[i];

    s->len+=t->len;
    free(s->ch);//需要销毁原字符串
    s->ch=temp;
    return true;
}

bool StrAssign(HString *s,char *tval){//堆串赋值函数
    int len,i=0;
    if(s->ch!=NULL) free(s->ch);//初始化字符串

    while (tval[i]!='\0') i++;//测量长度
    len=i;

    if(len){
        s->ch=(char*)malloc(len);//给个空间
        if(s->ch==NULL) return false;
        for(i=0;i<len;i++) s->ch[i]=tval[i];//赋值
    }else s->ch=NULL;
    s->len=len;
    return true;
}

void Visit(HString s){
    // printf("%s",s.ch);
    for(int i=0;i<s.len;i++){
        printf("%c",s.ch[i]);
    }
}
int main(){//测试
    HString s;
    StrInit(&s);
    printf("输入长度:");
    int len;
    scanf("%d",&len);
    char tval[len];
    printf("输入串:");
    scanf("%s",tval);

    StrAssign(&s,tval);
    Visit(s);
    
    HString t;
    StrInit(&t);
    printf("输入插入串长度:");
    int lenx;
    scanf("%d",&lenx);
    char tvalx[lenx];
    printf("输入插入串:");
    scanf("%s",tvalx);

    StrAssign(&t,tvalx);

    printf("输入插入位置:");
    int pos;
    scanf("%d",&pos);
    StrInsert(&s,pos,&t);
    Visit(s);
}