#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
typedef enum{
    HASH_OK,
    HASH_ERROR,
    HASH_ADDED,//key不存在，则需要添加
    HASH_REPLACED_VALUE,//添加的key存在，且value已经存在但要取代
    HASH_ALREADY_ADDED,//添加的key存在，且value也已经存在
    HASH_DELETED,//删除某个key及value
    HASH_NOT_FOUND,//未找到
} HASH_RESULT;//各种结果值
typedef struct HashEntry{
    union{
        char  *strValue;
        double dblValue;
        int       intVvalue;
    } key;//简单来讲，就是键，用来查找，用到了union可以是多种类型
    union{
        char  *strValue;
        double dblValue;
        int       intValue;
        long   longValue;
        void  *ptrValue;
    } value;//简单来讲，就是值，可以是多种类型
    struct HashEntry *next;//下一个
}HashEntry;
typedef struct HashTable{
    HashEntry **bucket;//储存值的数组，每个数组都是一个链表，每个数组存放键加工过后正好是i的所有键值对      
    int size;//大小
    HASH_RESULT last_error;//结果
}HashTable;

long hashString(const char *str){//求键
    long hash = 5381;
    int c;
    while (c = *str++) hash = ((hash << 5) + hash) + c; 
    if(hash < 0)
        hash *= -1;
    return hash;
}
HashTable* createHash(int size){//创建大小为hash_size的哈希表，创建成功后返回HashTable类型的指针，否则返回NULL
    HashTable *ht=(HashTable *)malloc(sizeof(HashTable));//先给予空间
    if(ht==NULL) return NULL;
    ht->bucket=(HashEntry **)malloc(size*sizeof(HashEntry*));//给放值的地方开辟空间
    if(ht->bucket==NULL){
        free(ht);
        return NULL;
    }
    ht->size=size;
    ht->last_error=HASH_OK;
    return ht;
}
HASH_RESULT hashAddInt(HashTable *table, const char *key, int value){//向哈希表中添加元素，其中键类型为char*， 元素类型为int
    long x=hashString(key);//获得键
    int i=x%table->size;//获得所在数组位置i，双重加密（有点抽象的说）
    HashEntry *t=table->bucket[i];
    while(t!=NULL){
        if(strcmp(t->key.strValue,key)==0){//比较值
            if(t->value.intValue==value){
                return HASH_ALREADY_ADDED;//已有
            }else{
                t->value.intValue=value;
                return HASH_REPLACED_VALUE;//取代
            }
        }
        t=t->next;//遍历
    }
    HashEntry *p=(HashEntry*)malloc(sizeof(HashEntry));//没有则新建
    if(p==NULL) return HASH_ERROR;
    p->key.strValue=(char*)malloc(sizeof(char)*(strlen(key)+1));//开辟空间赋值
    if(p->key.strValue==NULL){
        free(p);
        return HASH_ERROR;
    }
    strcpy(p->key.strValue,key);//赋值
    p->value.intValue=value;
    p->next=table->bucket[i];//找到指定位置的进行插入
    table->bucket[i]=p;
    return HASH_ADDED;
}
HASH_RESULT hashFind(HashTable table,const char *key,int *value){//查找
    long x=hashString(key);
    int i=x%table.size;
    HashEntry *t=table.bucket[i];
    while(t!=NULL){
        if(strcmp(t->key.strValue,key)==0){
            *value=t->value.intValue;    
            return HASH_OK;
        }
        t=t->next;
    }
    return HASH_NOT_FOUND;
}
HASH_RESULT hashDel(HashTable *table,const char *key,int value){
    long x=hashString(key);
    int i=x%table->size;
    HashEntry *t=table->bucket[i];
    HashEntry *ft=NULL;
    while(t!=NULL){
        if(strcmp(t->key.strValue,key)==0){
            if(t->value.intValue==value) break;//找到后跳出循环
        }
        ft=t;
        t=t->next;//遍历
    }
    if(t==NULL) return HASH_NOT_FOUND;
    if(ft==NULL) table->bucket[i]=t->next;    
    else ft->next=t->next;
    free(t);
    return HASH_DELETED;
}
int main(){
    printf("输入字符串:");
    char s[10];
    scanf("%s",s);
    printf("%d",hashSstring(s));
}