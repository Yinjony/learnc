//基础串，就和平常的没区别
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 40
typedef struct{
    char ch[MAXSIZE];
    int len;
}SString;
int StrInsert(SString *s,int pos,SString t){//在pos处向s串中插入t串
    int i;
    if(pos<0||pos>s->len) return 0;//位置不符合要求
    if(s->len+t.len<=MAXSIZE){//插入后的长度小于最大长度
        for(i=s->len+t.len-1;i>=t.len+pos;i--){
            s->ch[i]=s->ch[i-t.len];//先空出一定长度
        }
        for(i=0;i<t.len;i++){
            s->ch[i+pos]=t.ch[i];//开始填充
        }
        s->len=s->len+t.len;
    }
    else if(pos+t.len<=MAXSIZE){//插入后长度超了，但是插入部分没超
        for(i=MAXSIZE-1;i>t.len+pos-1;i--){
            s->ch[i]=s->ch[i-t.len];
        }
        for(i=0;i<t.len;i++){
            s->ch[i+pos]=t.ch[i];
        }
        s->len=MAXSIZE;
    }
    else{//插入部分也超了
        for(i=0;i+pos<MAXSIZE;i++){
            s->ch[i+pos]=t.ch[i];
        }
        s->len=MAXSIZE;
    }
    return 1;
}
int StrDelete(SString *s,int pos,int len){//从指定位置开始删除字符串，长度len
    int i;
    if(pos<0||pos+len>s->len)return 0;
    for(i=pos+len;i<s->len;i++){
        s->ch[i-len]=s->ch[i];//覆盖
    }
    s->len=s->len-len;
    return 1;
}
int StrCompare(SString s,SString t){//字符串比较
    int i;
    for(i=0;i<s.len&&i<t.len;i++){
        if(s.ch[i]!=t.ch[i]){
            return 0;
        }
    }
    return s.len-t.len;//长度大小比较
}
int StrIndex(SString s,int pos,SString t){//匹配从pos开始s中与t相同的部分，并返回起始值
    int i,j,start;//Brute——Force算法
    if(t.len==0) return 0;
    start=pos;i=start;j=0;//ij分别是s与t的指针
    while(i<s.len&&j<t.len){
        if(s.ch[i]==t.ch[j]){
            i++;
            j++;
        }
        else {
            start++;//切换起始值，再次循环
            i=start;
            j=0;
        }
    }
    if(j>=t.len) return start;
    else return -1;
}
// 除此之外，还有
// StrAssign(S,chars)将chars字符串赋到S中
// StrCopy(S,T)将T赋到S中
// StrEmpty(S)判空
// StrLength(S)返回长度
// StrClear(S)清空
// StrCat(S,T)将T接在S后面
// SubString(Sub,S,pos,len)返回从pos起到len的字符串
// StrReplace(S,T,V)用V取代S与T相等的部分
// StrDestroy(S)销毁字符串S








