//基础串，就和平常的没区别
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXSIZE 40
typedef struct{
    char ch[MAXSIZE];
    int len;
}SString;

bool StrAssign(SString *s,char *chars){ //将chars字符串常量赋到s中,
    int len=0;
    while(chars[len]!='\0') len++;
    for(int i=0;i<len;i++){
        s->ch[i]=chars[i];
    }
    s->len=len;
    if(s->len) return true;
}
bool StrInsert(SString *s,int pos,SString t){//在pos处向s串中插入t串
    int i;
    if(pos<0||pos>s->len) return false;//位置不符合要求
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
        for(i=MAXSIZE-1;i>=t.len+pos;i--){
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
    return true;
}
bool StrDelete(SString *s,int pos,int len){//从指定位置开始删除字符串，长度len
    int i;
    if(pos<0||pos+len>s->len) return false;
    for(i=pos+len;i<s->len;i++){
        s->ch[i-len]=s->ch[i];//覆盖
    }
    s->len=s->len-len;
    return true;
}
bool StrCopy(SString *s,SString t){//将t复制到s中
    if(s->len<=0) return false;
    for(int i=0;i<t.len;i++){
        s->ch[i]=t.ch[i];
    }
    s->len=(s->len>=t.len)?s->len:t.len;
    return true;
}
bool StrEmpty(SString s){//判空
    if(s.len<=0) return false;
    else return true;
}
int StrCompare(SString s,SString t){//字符串比较
    int r;
    int i=0;
    for(;s.ch[i]!='\0'&&t.ch[i]!='\0';i++){
        if(s.ch[i]>='A'&&s.ch[i]<='Z'){
            if(t.ch[i]>='A'&&t.ch[i]<='Z'){
                
                if(s.ch[i]==t.ch[i]) r=0;
                else if(s.ch[i]>t.ch[i]) {r=1;break;}
                else {r=-1;break;}
                
            }else{
                
                if(s.ch[i]-'A'==t.ch[i]-'a') r=0;
                else if(s.ch[i]>t.ch[i]){r=1;break;}
                else {r=-1;break;}
                
            }
        }
        else{
            if(t.ch[i]>='A'&&t.ch[i]<='Z'){
                
                if(s.ch[i]-'a'==t.ch[i]-'A') r=0;
                else if(s.ch[i]>t.ch[i]) {r=1;break;}
                else {r=-1;break;}
                
            }else{
                
                if(s.ch[i]==t.ch[i]) r=0;
                else if(s.ch[i]>t.ch[i]){r=1;break;}
                else {r=-1;break;}
                
            }
        }
    }
    if(s.ch[i]!='\0'&&t.ch[i]=='\0') r=1;
    if(t.ch[i]!='\0'&&s.ch[i]=='\0') r=-1;
    return r;
}
int StrLength(SString s){//返回长度
    return s.len;
}
void StrClear(SString *s){//清空,感觉也可以算销毁字符串
    s->len=0;
}
bool StrCat(SString *s,SString t){//将t接在s后面
    if(s->len<=0||t.len<=0) return false;
    for(int i=0;i<t.len;i++){
        s->ch[s->len+i]=t.ch[i];
    }
    s->len+=t.len;
    return true;
}
bool SubString(SString *sub,SString s,int pos,int len){//返回从pos起到len的字符串
    if(s.len<=0) return false;//串不存在
    if(pos<0||pos>s.len-1) return false;//位置不符
    if(len<1||len>s.len-pos+1) return false;//长度不符
    for(int i=0;i<len;i++){
        sub->ch[i]=s.ch[pos+i];
    }
    sub->len=len;
    return true;
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
bool StrReplace(SString *s,SString t,SString v){//用v取代s与t相等的部分
    if(s->len==0||t.len==0||v.len==0) return false;
    SString sub;
    sub.len=0;//每次赋值，都加一
    int i=0;
    while (i<s->len){
        int pos;
        pos=StrIndex(*s,i,t);//找出位置
        if(pos>=0){
            for(;i<pos;i++){//复制
                sub.ch[(++sub.len)-1]=s->ch[i];
            }
            for(int j=0;j<v.len;j++){//替换
                sub.ch[(++sub.len)-1]=v.ch[j];
            }
            i=pos+t.len;
        }else{
            for(;i<s->len;i++){
                sub.ch[(++sub.len)-1]=s->ch[i];
            }
        }
    }
    for(int i=0;i<sub.len;i++){//修改s串
        s->ch[i]=sub.ch[i];
    }
    s->len=sub.len;
    return true;
}

void Visit(SString s){
    printf("结果:");
    for(int i=0;i<s.len;i++){
        printf("%c",s.ch[i]);
    }
}
void Menu(void){
    printf("\n1:插入新串\t2:删除指定长度字符串\t\n3:复制串\t4:比较串\t\n5:拼接串\t6:返回某段字符串\t\n7:查找位置\t8:取代\n");
    printf("请选择测试函数(0:退出):\n");
}
int main(){
    SString s;
    int len;
    printf("输入s串长度:");
    scanf("%d",&len);
    printf("输入串:");
    char chars[len];
    scanf("%s",chars);
    StrAssign(&s,chars);//初始化s串

    printf("判空:%d",StrEmpty(s));
    printf("长度:%d",StrLength(s));

    while (1){
        Menu();
        int i;
        scanf("%d",&i);
        switch (i){//跳过实例化，加个大括号
        case 0:exit(1);
        case 1:{
            SString t;
            int len;
            printf("输入t串长度:");
            scanf("%d",&len);
            printf("输入t串:");
            char chars[len];
            scanf("%s",chars);
            StrAssign(&t,chars);//初始化t串

            printf("输入插入位置:");
            int pos;
            scanf("%d",&pos);

            StrInsert(&s,pos,t);
            Visit(s);}
        break;
        case 2:{
            printf("输入删除位置:");
            int pos;
            scanf("%d",&pos);
            printf("输入删除长度:");
            int len;
            scanf("%d",&len);
            
            StrDelete(&s,pos,len);
            Visit(s);}
        break;
        case 3:{
            SString t;
            int len;
            printf("输入t串长度:");
            scanf("%d",&len);
            printf("输入t串:");
            char chars[len];
            scanf("%s",chars);
            StrAssign(&t,chars);//初始化t串

            StrCopy(&s,t);
            Visit(s);}
        break;
        case 4:{
            SString t;
            int len;
            printf("输入t串长度:");
            scanf("%d",&len);
            printf("输入t串:");
            char chars[len];
            scanf("%s",chars);
            StrAssign(&t,chars);//初始化t串

            printf("比较结果:");
            int a=StrCompare(s,t);
            if(a>0) printf("s串大");
            else if(a<0) printf("t串大");
            else printf("一样大");}
        break;
        case 5:{
            SString t;
            int len;
            printf("输入t串长度:");
            scanf("%d",&len);
            printf("输入t串:");
            char chars[len];
            scanf("%s",chars);
            StrAssign(&t,chars);//初始化t串

            StrCat(&s,t);
            Visit(s);}
        break;
        case 6:{
            SString sub;
            printf("输入起始位置:");
            int pos;
            scanf("%d",&pos);
            printf("输入长度:");
            int len;
            scanf("%d",&len);

            SubString(&sub,s,pos,len);
            Visit(sub);}
        break;
        case 7:{
            SString t;
            int len;
            printf("输入t串长度:");
            scanf("%d",&len);
            printf("输入t串:");
            char chars[len];
            scanf("%s",chars);
            StrAssign(&t,chars);//初始化t串

            printf("输入查找起始位置:");
            int pos;
            scanf("%d",&pos);
            printf("查找结果:%d",StrIndex(s,pos,t));}
        break;
        case 8:{
            SString t;
            int len;
            printf("输入t串长度:");
            scanf("%d",&len);
            printf("输入t串:");
            char chars[len];
            scanf("%s",chars);
            StrAssign(&t,chars);//初始化t串

            SString v;
            int lenx;
            printf("输入v串长度:");
            scanf("%d",&lenx);
            printf("输入v串:");
            char charsx[lenx];
            scanf("%s",charsx);
            StrAssign(&v,charsx);//初始化t串

            StrReplace(&s,t,v);
            Visit(s);}
        break;
        }
    }
}