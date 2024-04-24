#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define LIST_SIZE 20
#define BLOCKNUM 3
typedef int KeyType;
typedef char OtherType;

typedef struct{
    KeyType key;
    OtherType other_data;
}RecordType;
typedef struct{
    RecordType r[LIST_SIZE+1];
    int length;
}RecordList;//把要查找的数据放到线性表中

int SeqSearch(RecordList l,KeyType key){
    l.r[0].key=key;int i=l.length;//设置监视哨，l.r[0]为监视哨，倒序进行查找
    while(l.r[i].key!=key) i--;
    return i;//返回位置

    // int i=length;//不设置监视哨
    // while(i>=1&&l.r[i].key!=key) i--;
    // if(i>=1) return i;
    // else return 0;
}

int BinSearch(RecordList l,KeyType key){//折半查找，一是顺序表，二是按关键字大小进行有序排列
    int low=1,high=l.length;
    while(low<high){
        int mid=(low+high)/2;
        if(key==l.r[mid].key) return mid;
        else if(key<l.r[mid].key) high=mid-1;
        else low=mid+1;
    }
    return 0;
}

typedef struct{
    KeyType MaxKey;
    int Index;
}IndexList;
void CreateIndexList(IndexList index[BLOCKNUM],RecordList l){//创建索引表
    int t=l.length/BLOCKNUM;//分块大小
    int k=1;//索引值
    for(int i=0;i<BLOCKNUM;i++){//寻找每一块的最大关键字
        index[i].Index=k;
        index[i].MaxKey=l.r[k].key;
        while(k-i*t<=t){
            index[i].MaxKey=(index[i].MaxKey>l.r[k].key)?index[i].MaxKey:l.r[k].key;
            k++;
        }
    }
    if(k<=l.length){//四舍五入有剩余
        while(k<=l.length){
            index[BLOCKNUM-1].MaxKey=(index[BLOCKNUM-1].MaxKey>l.r[k].key)?index[BLOCKNUM-1].MaxKey:l.r[k].key;
            k++;
        }
    }
}
int BlockSearch(RecordList l,KeyType key){//分块查找
    IndexList index[BLOCKNUM];
    CreateIndexList(index,l);
    for(int i=0;i<BLOCKNUM;i++){
        if(key>index[i].MaxKey) continue;//大于就跳过
        else {//不大于说明在这个块内
            for(int j=index[i].Index;j<l.length/BLOCKNUM+index[i].Index;j++){
                if(key==l.r[j].key) return j;
            }
        }
    }
    return 0;
}
int main(){
    RecordList l;
    printf("输入长度:");
    scanf("%d",&l.length);
    printf("输入数据:");
    for(int i=1;i<=l.length;i++){
        scanf("%d",&l.r[i].key);
    }
    printf("输入目标数据:");
    int key;
    scanf("%d",&key);
    printf("结果1:%d",SeqSearch(l,key));
    printf("\n结果2:%d",BinSearch(l,key));
    printf("\n结果3:%d",BlockSearch(l,key));
}