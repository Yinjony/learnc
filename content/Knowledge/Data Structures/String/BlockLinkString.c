/*块链串，字符ch部分储存字符，但可以是任意数量的字符，也就是把一个串切成几个块储存，
用链表串起来，BLOCK_SIZE大小为1的时候，存储密度很低，但要是大于1，就大了*/

//操作方法与链表相同
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define BLOCK_SIZE 4

typedef struct Block{
    char ch[BLOCK_SIZE];
    struct Block *next;
} Block;

typedef struct BLString{
    Block *head;
    Block *tail;
    int len;
}BLString;

void Init(BLString *s){
    s->head=NULL;
    s->tail=NULL;
    s->len=0;
}

void Visit(BLString s){
    Block *p=s.head;
    for(int i=0;i<s.len;i++){//一般
        if(i%BLOCK_SIZE==0&&i!=0) p=p->next;
        printf("%c",p->ch[i%BLOCK_SIZE]);
    }
    // int i=0;//傻逼icoding
    // while(i<s.len){
    //     for(int j=0;j<BLOCK_SIZE;i++,j++){
    //         printf("%c",p->ch[j]);
    //     }
    //     p=p->next;
    // }
}

void Create(BLString *s){
    printf("输入长度:");
    scanf("%d",&(s->len));
    int i=0;
    char c=getchar();
    printf("输入串:");
    Block *p;
    while(i<s->len){
        Block *temp=(Block*)malloc(sizeof(Block));
        temp->next=NULL;
        for(int j=0;j<BLOCK_SIZE&&i<s->len;j++,i++) temp->ch[j]=getchar();
        if(i<=BLOCK_SIZE){
            s->head=temp;
            s->tail=temp;
            p=s->head;
        }else{
            p->next=temp;
            s->tail=temp;
            p=p->next;
        }
    }
}

bool blstr_substr(BLString s, int pos, int len, BLString *sub){//子串查找
    if(s.len<=0) return false;
    if(pos<0||pos>s.len-1) return false;
    if(len<1) return false;

    sub->len=(len>s.len-pos+1)?s.len-pos+1:len;//判断长度
    Block *p=s.head;
    for(int i=0;i<pos;i++){//找到位置
        if((i+1)%BLOCK_SIZE==0&&i!=0){
            p=p->next;
        }
    }

    Block *q;
    int i=0;
    while(i<len){
        Block *temp=(Block*)malloc(sizeof(Block));
        temp->next=NULL;
        int j=0;
        for(;j<BLOCK_SIZE&&i<len&&i+pos<s.len;j++,i++){//赋值
            temp->ch[j]=p->ch[(i+pos)%BLOCK_SIZE];
            if((i+pos)%BLOCK_SIZE==3) p=p->next;//到头换块
        }
        if(j==0) break;//已经赋完值
        for(;j<BLOCK_SIZE;j++,i++){//有空白进行填补
            temp->ch[j]='#';
        }
        if(i<=BLOCK_SIZE){//头结点
            sub->head=temp;
            sub->tail=temp;
            q=sub->head;
        }else{//其余结点
            q->next=temp;
            sub->tail=temp;
            q=q->next;
        }
    }
    return true;
}

int main(){
    BLString s;
    Init(&s);
    Create(&s);
    printf("输入查找位置:");
    int pos;
    scanf("%d",&pos); 
    printf("输入sub长度:");
    int len;
    scanf("%d",&len);
    BLString sub;
    blstr_substr(s,pos,len,&sub);
    Visit(sub);
}